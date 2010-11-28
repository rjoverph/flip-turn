<?php
/**
 * The DBDataObjectTemplateGenerator
 *
 * @author Walter A. Boring IV
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Generator
 */

/**
 * This file contains the DataObjectTemplateGenerator
 * class that is used by a project to build
 * DataObjectTemplate classes based upon database table
 * metadata.
 *
 * This class is used to generate DBDataObjectTemplate
 * classes based upon a Database table metadata
 *
 * @author Walter A. Boring IV
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Generator
 */
class DBDataObjectTemplateGenerator {

    protected $skip_field_functions = array('id',
                                            'date_created',
                                            'date_modified');

    /**
     * contains the config xml string.
     */
    protected $config_xml = NULL;

    /**
     * The base path where to place the templates
     */
    protected $base_path = NULL;

    /**
     * Holds your project name here
     *
     */
    protected $project_name = 'phpHtmlLib';

    /**
     * Holds your project name here
     *
     */
    protected $parent_name = 'DBDataObject';

    /**
     * Holds foreign keys
     *
     * @var array
     */
    protected $foreign_keys = array();

    /**
     * Stores relations between tables
     *
     * @var array
     */
    protected $relations = array();

    /**
     * Generate relation helper functions?
     *
     * @var bool
     */
    protected $relation_helper_functions = true;


    /**
     * Constructor that builds the object
     */
    public function __construct($config_xml) {
        $this->parse_xml($config_xml);
    }

    /**
     * This method is used to set the base path
     * of where the generated template files will
     * exist
     *
     * @param string $path
     */
    public function set_base_path($path) {
        $this->base_path = $path;
    }

    /**
     * This method is used to set the Project
     * name.
     *
     * @param string $name
     */
    public function set_project_name($name) {
         $this->project_name = $name;
    }

    /**
     * This method is used to set the parent class
     * name.
     *
     * @param string $name
     */
    public function set_parent_name($name) {
         $this->parent_name = $name;
    }

    /**
     * Generate relation helper functions?
     *
     * @param $flag bool
     */
    public function generate_relation_helpers($relation_helper_functions) {
        $this->relation_helper_functions = $relation_helper_functions;
    }

    /**
     * process the xml string
     *
     * @param string $config_xml
     */
    protected function parse_xml($config_xml) {
        Validator::singleton()->is_notempty($config_xml);
        if (!extension_loaded('simplexml')) {
            throw new ValidatorException('simplexml extension is NOT loaded',
                                         ValidatorException::STR_INVALID_FIELD);
        }
        $dom = simplexml_load_string($config_xml);

        //make sure we have at least 1 database tag
        $db = $dom->xpath('//database');
        if (empty($db)) {
            throw new ValidatorException('no database defined in xml config',
                                         ValidatorException::ERR_EMPTY);
        }

        //validate some of the dom elements
        foreach ($dom->xpath('//database') as $db) {
            $conn = $db->xpath('//connection');
            if (empty($conn)) {
                throw new ValidatorException('no database defined in xml config',
                                             ValidatorException::ERR_EMPTY);
            }
        }

        unset($dom);
        $this->config_xml = $config_xml;

    }

    /**
     * This method execute the generation
     * based upon the configuration parameters
     *
     */
    public function execute() {

        //make sure the base path exists
        if (is_null($this->base_path) || !is_dir($this->base_path)) {
            throw new phphtmllibException("Base path (".$this->base_path.") isn't set or invalid.  call set_base_path(\$path)");
        }

        $this->config_xml = simplexml_load_string($this->config_xml);
        $dbs = array();

        /**
         * this code really sucks.  I had to do 2 loops
         * because php was segfaulting
         */
        foreach($this->config_xml as $database) {
            //ok now that we are connected, lets get to work.
            $dbname = (string)$database->connection->name;
            $dsn = DataBase::dsn((string)$database->connection->driver,
                                 (string)$database->connection->name,
                                 (string)$database->connection->host,
                                 (string)$database->connection->port);
            $dbs[$dbname]['config'] = array('dsn' => $dsn,
                                            'user' => (string)$database->connection->user,
                                            'pwd' => (string)$database->connection->password);

            //look for a parent class name
            if (isset($database->tables['parent'])) {
                $parent = (string)$database->tables['parent'];
            } else {
                $parent = $this->parent_name;
            }

            foreach($database->tables->table as $table) {
                $info = array('name' => (string)$table['name'],
                              'parent' => $parent);

                $dbs[$dbname]['tables'][] = $info;
            }
        }

        //because of segfaults....lame
        unset($this->config_xml);
        foreach($dbs as $dbname => $dbdata) {
            echo "\nStart Processing DB: ".$dbname."\n\n";
            $db = new DataBase($dbdata['config']['dsn'], $dbdata['config']['user'],
                               $dbdata['config']['pwd']);
            $str = '';
            //make sure we have the directory
            $this->prep_destination($dbname);

            // figure out all foreign key
            // dependencies
            $this->build_dependencies($db, $dbdata['tables']);

            foreach($dbdata['tables'] as $table) {
                echo $dbname."::".$table['name']." ... \t\t";

                $tmp_class = $this->build_class_name($table['name']);
                $class_name = $tmp_class . 'DataObjectTemplate';
                $child_name = $tmp_class . 'DataObject';
                $this->write_file($class_name,
                                  $this->build_template_class($db, $dbname, $table, $class_name,
                                                              $table['parent'], $child_name),
                                  $dbname);
                //check to see if the child already exists.
                //if it does, we don't overwrite it.
                if (!$this->child_exists($dbname, $child_name)) {
                    echo "writing ".$child_name." class to disk\n";
                    $this->write_file($child_name, $this->build_child_class($child_name, $class_name),
                                      $dbname, TRUE);
                }
                echo "done\n";
            }
            echo "\n" . $dbname." processing complete\n\n";
        }
    }

    /**
     * Build the DBDataObject template
     * for a table.
     *
     * @param DataBase $db connected object.
     * @param string $dbname the name of the db
     * @param SimpleXMLElement $table
     * @param string the parent dbdataobject class name
     * @return string
     */
    protected function build_template_class($db, $dbname, $table, $class_name,
                                            $parent_name, $child_name) {


        $access_block_set =
'
    /**
     * @param {FIELD_TYPE} $value
     */
    public function set_{FIELD}($value) { $this->set(\'{FIELD}\', $value); }
';

        $access_block_get =
'
    /**
     * @return {FIELD_TYPE}
     */
    public function get_{FIELD}() { return $this->get(\'{FIELD}\'); }
';

    // DATA OBJECTS RELATED TEMPLATE

    $relation_function = '
    /**
     * @return {DO_NAME}DataObject
     */
    public function {DO_NAME}DataObject() { return $this->get_related_data_object(\'{COL_NAME}\'); }

    /**
     * @param {DO_NAME}DataObject $obj
     */
    public function set_{DO_NAME}DataObject({DO_NAME}DataObject $obj) {
        $this->set_{COL_NAME}_id($obj->get_{COL_NAME}_id());
        $this->set_related_data_object(\'{COL_NAME}\', $obj);
    }
    ';

    //  Helper functions to make the api
    //  look easier to use
    $relation_add_function = '
    /**
     * this method adds a new {CHILD} relation.
     *
     * @param {CHILD}DataObject
     */
    public function add_{CHILD}({CHILD}DataObject $obj) {
        $this->{CHILD}DataObjectCollection()->add($obj);

    }';

    // DATA OBJECT COLLECTIONS TEMPLATE

    $do_collections_function = '
    /**
     * @return DataObjectCollection
     */
    public function {CHILD}DataObjectCollection() {

        if (!isset($this->related_data_object_collections[\'{CHILD}\'])) {
            try {
                $this->related_data_object_collections[\'{CHILD}\'] = {CHILD}DataObject::find_all(\'{PARENT}_id=:key\', array(\':key\' => $this->get_{PARENT}_id()));
            }
            catch (DataObjectException $e) {
                $this->related_data_object_collections[\'{CHILD}\'] = new DataObjectCollection();
            }
        }

        $this->changed = true;

        return $this->related_data_object_collections[\'{CHILD}\'];
    }
    ';
    
    //for __toString()
    $to_string_function = '
    /**
     * This method returns a string representation
     * of the DataObject
     *
     * @return string
     */
     public function __toString() {
         return {TO_STRING};
     }    
    ';

        //first get the metadata for the table
        $meta = $this->get_metadata($db, $table);

        $access_block = '';
        $to_string_block = '';

        foreach($meta['cols'] as $col) {

            $field_name = strtolower($col['name']);

            $info[] = '\'' . $field_name . '\'' . ' => array(' . $col['type'] . ', ' . $col['size']. ')';

            if (!in_array($field_name, $this->skip_field_functions)) {
                $access_block .= str_replace(array('{FIELD}', '{FIELD_TYPE}'),
                                             array($field_name, $this->convert_to_php_type($col['db_field_type'])), $access_block_set);				
            }
            
            //we can't override get_id, as it's final.
            if ($field_name != "id") {
            	$access_block .= str_replace(array('{FIELD}', '{FIELD_TYPE}'),
                	                         array($field_name, $this->convert_to_php_type($col['db_field_type'])), $access_block_get);
            }

            
                                         
            $to_string_block .= '" '.$field_name.' = ". $this->get_'.$field_name.'(). ';                                         
        }
        
        $to_string_block = substr($to_string_block, 0, strlen($to_string_block)-2);
        $to_string_function = str_replace( '{TO_STRING}', $to_string_block, $to_string_function);

        // build foreign key data object functions (relations)
        $relations_block = '';

        if ($meta['fkeys']) {
            foreach ($meta['fkeys'] as $foreign_key) {
                $field_name = str_replace('_id', '', $foreign_key);
                $relations_block .= str_replace(array('{DO_NAME}', '{COL_NAME}'),
                                                array($this->build_class_name($field_name),
                                                      $field_name),
                                                $relation_function);
           }
        }



        //helper methods
        $relation_add_block = '';


        // build data object collection function
        $do_collections_block = '';

        if (isset($this->relations[$table['name']])) {

            foreach ($this->relations[$table['name']] as $child) {
                $child = $this->build_class_name($child);

                if ($this->relation_helper_functions) {
                    $relation_add_block .= str_replace('{CHILD}', $child, $relation_add_function);
                }
                $do_collections_block .= str_replace(array('{PARENT}', '{CHILD}'), array($table['name'], $child), $do_collections_function);
            }
        }

        $dot =
'<?php
/**
 * Auto-generated meta data definition file
 *
 * Generated {TIMESTAMP}
 *
 * @package {PROJECT_NAME}
 * @subpackage generated
 *
 */
abstract class {CLASS_NAME} extends {PARENT_NAME} {

    protected $meta_data = {META_DATA};

    protected $related_data_objects = array();

    protected $table_name = \'{TABLE_NAME}\';

    protected $primary_key = \'{PRIMARY_KEY}\';

    /**
     * This method finds a single data object
     *
     * @param string $where ie. \'foo=:foo\'
     * @param array $bind_vars
     * @return {CHILD_NAME}
     */
    public static function find($where_clause, $bind_vars=array()) {
        return DBDataObject::find(\'{CHILD_NAME}\', $where_clause, $bind_vars);
    }

    /**
     * This method finds a single data object
     * by a specific field and value
     *
     * @param string $field_name
     * @param string $field_value
     * @return {CHILD_NAME}
     */
    public static function find_by_field($field_name, $field_value) {
        return DBDataObject::find_by_field(\'{CHILD_NAME}\', $field_name, $field_value);
    }

    /**
     * This method finds a single data object
     * populates it and returns it.
     *
     * @param string $where ie. \'foo=:foo\'
     * @param array $bind_vars
     * @param string $order_clause \'order by foo\'
     * @param string $limit clause \'limit 10,20\'
     * @return DataObjectCollection
     */
    public static function find_all($where_clause, $bind_vars=array(), $order_clause=NULL, $limit_clause=NULL) {
        return DBDataObject::find_all(\'{CHILD_NAME}\', $where_clause, $bind_vars, $order_clause, $limit_clause);
    }

    /**
     * This method finds a single data object
     * using a join
     *
     * @param array $tables
     * @param string $where ie. \'foo=:foo\'
     * @param array $bind_vars
     * @return {CHILD_NAME}
     */
    public static function join($tables, $where_clause, $bind_vars=array()) {
        return DBDataObject::join(\'{CHILD_NAME}\', $tables, $where_clause, $bind_vars);
    }

    /**
     * This method finds all matching
     * data objects using a join
     *
     * @param array $tables
     * @param string $where ie. \'foo=:foo\'
     * @param array $bind_vars
     * @param string $order_clause \'order by foo\'
     * @param string $limit clause \'limit 10,20\'
     * @return DataObjectCollection
     */
    public static function join_all($tables, $where_clause, $bind_vars=array(), $order_clause=NULL, $limit_clause=NULL) {
        return DBDataObject::join_all(\'{CHILD_NAME}\', $tables, $where_clause, $bind_vars, $order_clause, $limit_clause);
    }



    // ------------- DATA ACCESS FUNCTIONS ---------------
{ACCESS_BLOCK}

    // ------------- RELATED DATA OBJECTS ----------------
{RELATIONS_BLOCK}

    // ------------- RELATIONS ADD METHODS ----------------
{RELATION_ADD_BLOCK}

    // ------------- DATA OBJECT COLLECTIONS -------------
{DO_COLLECTIONS_BLOCK}

  // -------- MISC --------
  {TO_STRING_FUNCTION}
}
?>';

        // our template vars
        $replace = array('{CLASS_NAME}' => $class_name,
                         '{PARENT_NAME}' => $parent_name,
                         '{CHILD_NAME}' => $child_name,
                         '{PROJECT_NAME}' => $this->project_name,
                         '{DB_NAME}' => $dbname,
                         '{TABLE_NAME}' => $table['name'],
                         '{PRIMARY_KEY}' => $meta['index'],
                         '{TIMESTAMP}' => date('d/m/Y H:i:s'),
                         '{META_DATA}' => 'array(' . implode(",\n                                 ", $info) . ')',
                         '{ACCESS_BLOCK}' => $access_block,
                         '{RELATIONS_BLOCK}' => $relations_block,
                         '{RELATION_ADD_BLOCK}' => $relation_add_block,
                         '{DO_COLLECTIONS_BLOCK}' => $do_collections_block,
                         '{TO_STRING_FUNCTION}' => $to_string_function
                         );

        $code = str_replace(array_keys($replace), array_values($replace), $dot);
        return $code;
    }

    /**
     * This method builds the child of the template class
     * that a user can modify.  This will only be generated
     * once as we don't want to nuke any existing version.
     *
     * @param string $child_name
     * @param string $parent_name
     * @return string
     */
    protected function build_child_class($child_name, $parent_name) {


                $dot =
'<?php
/**
 * Auto-generated meta data definition file
 *
 * Generated {TIMESTAMP}
 *
 * @package {PROJECT_NAME}
 * @subpackage BusinessObjectTemplate
 *
 */
class {CLASS_NAME} extends {PARENT_NAME} {
}
?>';

        // our template vars
        $replace = array('{CLASS_NAME}' => $child_name,
                         '{PARENT_NAME}' => $parent_name,
                         '{PROJECT_NAME}' => $this->project_name,
                         '{TIMESTAMP}' => date('d/m/Y H:i:s')
                         );

        //var_dump($meta);
        $code = str_replace(array_keys($replace), array_values($replace), $dot);
        return $code;
    }

    /**
     * This function takes a table name, strips out any _
     * and upper cases the first char in the word
     *
     * @param string $table_name
     * @return string
     */
    private function build_class_name($table_name) {
        $words = explode('_', strtolower($table_name));

        $class_name = '';
        $i=0;
        foreach($words as $word) {
            if ($i == 0) {
                $class_name = $word;
            } else {
                $class_name .= ucfirst($word);
            }
            $i++;
        }

        return $class_name;
    }

    /**
     * Builds fkey dependencies
     *
     * @param DataBase $db
     * @param array $tables
     */
    protected function build_dependencies($db, $tables) {

        foreach ($tables as $table) {

            $stmt = $db->query('show keys from ' . $table['name']);

            while ($row = $stmt->fetch()) {

                if (substr($row->column_name, strlen($row->column_name)-3) == '_id') {
                    $ftable = substr($row->column_name, 0, strlen($row->column_name)-3);
                    if ($ftable != $table['name'] &&
                        !@in_array($table['name'],$this->relations[$ftable])) {
                        $this->relations[$ftable][] = $table['name'];
                    }
                }
            }

        }

    }

    /**
     * This method builds the child class of the template

    /**
     * get the meta data information about the table
     *
     * @param DataBase $db connected object.
     * @param array $table
     *
     * @todo add saving of enum values metadata to test against during setter calls.
     */
    protected function get_metadata($db, $table) {
        $meta = array();

        $row = array();
        $foreign_keys = array();
        $columns = $db->meta_table($table['name']);

        $primary_key = FALSE;
        foreach($columns as $row) {

            $primary_key = NULL;

            if ($row->extra == 'auto_increment') {
                $primary_key = strtolower($row->field);
            }
            if ($row->key == 'MUL' && substr($row->field, strlen($row->field)-3) == '_id') {
                $foreign_keys[$row->field] = $row->field;
            }

            $type = explode("(", $row->type);

            $row_type = $type[0];

            switch($row_type) {
            //Integers
            case 'bit':
                $row_type = 'Validator::TYPE_INT';
                $row_size = ceil(intval(explode(")", $type[1])) / 8);
                break;
                
            case 'tinyint':
                $row_type = 'Validator::TYPE_INT';
                $row_size = 1;
                break;

            case 'smallint':
                $row_type = 'Validator::TYPE_INT';
                $row_size = 2;
                break;

            case 'mediumint':
                $row_type = 'Validator::TYPE_INT';
                $row_size = 3;
                break;

            case 'int':
                $row_type = 'Validator::TYPE_INT';
                $row_size = 4;
                break;

            case 'bigint':
                $row_type = 'Validator::TYPE_INT';
                $row_size = 8;
                break;

            //Floating-point numbers
            case 'float':
            case 'decimal':
                $row_type = 'Validator::TYPE_FLOAT';
                $row_size = 4;
                break;

            case 'double':
            case 'real':
                $row_type = 'Validator::TYPE_FLOAT';
                $row_size = 8;
                break;

            //time mysql specific *sigh*
            case 'datetime':
            case 'timestamp':
                $row_type = 'Validator::TYPE_DATETIME';
                $row_size = 19;
                break;

            //char
            case 'varchar':
                $row_type = 'Validator::TYPE_STRING';
                $row_size = explode(")", $type[1]);
                if (is_numeric($row_size[0])) {
                    $row_size = $row_size[0];
                }
                break;

            case 'char':
                $row_type = 'Validator::TYPE_CHAR';
                $row_size = explode(")", $type[1]);
                if (is_numeric($row_size[0])) {
                    $row_size = $row_size[0];
                }
                break;

            //text
            case 'text':
            case 'date':
            case 'longtext':
            case 'mediumtext':
            case 'tinytext':
                $row_type = 'Validator::TYPE_TEXT';
                $row_size = 0;
                break;

            //misc
            case 'enum':
                $row_type = 'Validator::TYPE_ENUM';
                $row_size = 0;
                $values = substr(trim($type[1]),5);
                $values = substr($values, 0, strlen($values) -1 );
                $values = explode(',', $values);
                break;

            //blob
            case 'tinyblob':
            case 'blob':
            case 'mediumblob':
            case 'longblob':
                $row_type = 'Validator::TYPE_BLOB';
                $row_size = 0;
                break;
                
                
            //Geo spatial types    
            case 'point':
            	$row_type = 'Validator::TYPE_POINT';
            	$row_size = 0;
            	break;
            	
            case 'multipoint':
            	$row_type = 'Validator::TYPE_MULTIPOINT';
            	$row_size = 0;
            	break;	
            	
            case 'linestring':
            	$row_type = 'Validator::TYPE_LINESTRING';
            	$row_size = 0;
            	break;
            	
            case 'polygon':
            	$row_type = 'Validator::TYPE_POLYGON';
            	$row_size = 0;
            	break;            	            
            	
            case 'multilinestring':
            	$row_type = 'Validator::TYPE_MULTILINESTRING';
            	$row_size = 0;
            	break;
            	
            case 'multipolygon':
            	$row_type = 'Validator::TYPE_MULTIPOLYGON';
            	$row_size = 0;
            	break;
            	
            case 'GeometryCollection':
            	$row_type = 'Validator::TYPE_GEOMETRYCOLLECTION';
            	$row_size = 0;
            	break;

            default:
                die('Unknown type ' . $row->type);
                break;
            }

            // if the column can be null, insert that into the type
            // e.g. Validator::TYPE_STRING becomes Validator::TYPE_NULL_STRING
            if ($row->null == 'YES') {
                $row_type = str_replace('TYPE_', 'TYPE_NULL_', $row_type);
            }

            // no primary key?
            // try to find one
            if (!$primary_key) {
                foreach($db->query('show keys from '.$table['name'], PDO::FETCH_ASSOC) as $pk_row) {
                    if ($pk_row->key_name == 'PRIMARY') {
                        $primary_key = $pk_row->column_name;
                        break;
                    }
                }
            }

            if (!$primary_key) {
                $primary_key = 'no_id';
            }

            $meta['cols'][] = array('name' => $row->field,
                                    'type' => $row_type,
                                    'size' => $row_size,
                                    'db_field_type' => $type[0]);
        }

        $meta['index'] = strtolower($primary_key);
        $meta['fkeys'] = $foreign_keys;
        return $meta;
    }

    /**
     * This method translates a db column type
     * to a php variable type
     *
     * @param string
     * @return string
     */
    protected function convert_to_php_type($type) {
        switch ($type) {
            case 'bit':
            case 'tinyint':
            case 'smallint':
            case 'mediumint':
            case 'int':
            case 'bigint':
                $php = 'integer';
                break;

            case 'datetime':
            case 'varchar':
            case 'char':

            case 'text':
            case 'date':
            case 'longtext':
            case 'mediumtext':
            case 'enum':

            case 'blob':
            case 'mediumblob':

                $php = 'string';
                break;


            default:
                $php = 'string';
                break;
        }

        return $php;
    }

    /**
     * This method tries to find out if the child of the
     * template class already exists on disk.
     *
     * @param string $dbname
     * @param string $class_name
     * @return boolean
     */
    protected function child_exists($dbname, $class_name) {
        $file = $this->get_child_path($dbname, $class_name);
        return file_exists($file);
    }

    /**
     * This method gets the path of where the child of
     * the template object lives.
     *
     * @param string
     * @return string
     */
    private function get_child_path($dbname, $class_name) {
        return realpath($this->base_path).'/'.$dbname.'/'.$class_name.'.inc';
    }

    /**
     * This method writes the file to disk
     *
     * @param string $class_name
     * @param string $source
     * @param string $dbname
     * @param boolean $child - is this for a child class?
     */
    protected function write_file($class_name, $source, $dbname, $child=FALSE) {
        if (!$child) {
            $path = realpath($this->base_path).'/'.$dbname.'/templates/'.$class_name.'.inc';
        } else {
            $path = $this->get_child_path($dbname, $class_name);
        }

        $fp = fopen($path, 'w');
        if (!$fp) {
            throw new phphtmllibException("Failed to open file ".$path);
            fclose($fp);
        }

        $size = fwrite($fp, $source);
        fclose($fp);
    }

    /**
     * This method makes sure the destination exists
     * to place the class files we are going to generate
     *
     * @param string $dbname
     */
    protected function prep_destination($dbname) {
        $path = realpath($this->base_path).'/'.$dbname;

        if (!is_dir($path)) {
            $res = mkdir($path);
            if (!$res) {
                throw new phphtmllibException("Couldn't create destination ".$path);
            }
        }

        $path = realpath($this->base_path).'/'.$dbname.'/templates';

        if (!is_dir($path)) {
            $res = mkdir($path);
            if (!$res) {
                throw new phphtmllibException("Couldn't create destination ".$path);
            }
        }

    }
}

?>