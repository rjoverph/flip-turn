<?php
/**
 * Base DBDataObject class
 *
 * Abstract DBDataObject class implements
 * database specific I/O functions
 *
 * This is the only way to access
 * and manipulate DB data through
 * business layer.
 *
 * @author Suren Markosian
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib-framework
 * @subpackage Data
 *
 */

/**
 * This is the DataBase row abstraction layer
 * for phphtmllib.  It is used to manage single
 * or multiple rows of data from a database.
 * If enabled, it will use a cache object to cache
 * the values of the individual row to save DB reads.
 *
 * Abstract DBDataObject class implements
 * database specific I/O functions
 *
 * This is the preferred way to access and
 * manipulate DB data through business layer.
 *
 * @author Suren Markosian
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib-framework
 * @subpackage Data
 *
 */

abstract class DBDataObject extends DataObject implements Iterator {
    /**
     * Defines metadata for our
     * DataObject
     *
     * This array lists all fields and
     * their types in an array
     */
    protected $meta_data;

    /**
     * Do we also cache all
     * the find queries?
     *
     * @var bool
     */
    protected $allow_find_cache = true;

    /**
     * The array index in meta_data
     * to access the type
     */
    const META_TYPE = 0;

    /**
     * The array index in meta_data
     * to access the size
     */
    const META_SIZE = 1;

    /**
     * The array index in meta_data
     * to access the values for enum
     */
    const META_VALUES = 0;

    /**
     * Defines database table
     * name for this class
     *
     * @var string
     */
    protected $table_name;

    /**
     * Name of the primary
     * key field of the main
     * parent table
     *
     * @var string
     */
    protected $primary_key;

    /**
     * Holds DB object instance
     * that we use for all our DB
     * operations
     *
     * @var DataBase object
     */
    protected $db;

    /**
     * Holds cached related data objects
     *
     * @var array
     */
    protected $related_data_objects = array();

    /**
     * Holds cached related data object
     * collections
     *
     * @var array
     */
    protected $related_data_object_collections = array();

    /* ----------------------------------------------------------- */

    /**
     * We override the constructor
     * to set the database object
     *
     * @param int $id
     */
    public function __construct($id = null) {

        $this->cache = $this->get_cache_object();

        //initialize the data object
        //so we can call set w/o load
        $this->data = new stdClass;

        if ($id !== null) {
            $this->data->{$this->primary_key} = $id;
            $this->load();
        } else {
            $this->new_record = true;
        }
    }

    /**
     * This abstract method is supposed to
     * set the $this->db object
     *
     */
    abstract protected function set_db_object();

    /**
     * Returns unique identifier
     * value for the loaded data set
     *
     * @return int
     */
    public final function get_id() {
        return $this->data->{$this->primary_key};
    }

    /**
     * Sets unique identifier
     * value
     *
     * @param int $id
     */
    public final function set_id($id) {
        $this->data->{$this->primary_key} = $id;
    }

    /**
     * Returns object's meta data
     *
     * @return array
     */
    public final function get_meta_data() {
        return $this->meta_data;
    }

    /* -- PROTECTED FUNCTIONS -------------------------------------------------------- */

    /**
     * Sets a field to a given value
     *
     * @param string $name
     * @param string $value
     */
    protected final function set($name, $value) {

        if (isset($this->meta_data[$name])) {
            if ($name == $this->primary_key && !empty($this->data->$name)) {
                    //we should thrown an exception.
                    //can't really change the pkey value if it's
                    //already set
                    throw new DataObjectException('Primary key value cannot be changed',
                                                  phphtmllibException::DBDATAOBJECT_PKEY_CHANGE);
            } else if (!isset($this->data->$name) || $this->data->$name != $value) {
                    // validate the field
                    Validator::type($value,
                                    $this->meta_data[$name][self::META_TYPE], // type
                                    $this->meta_data[$name][self::META_SIZE]  // size
                                   );

                    parent::set($name, $value);
           }
        } else {
            throw new DataObjectException('Field ' . $name . ' does not exist in metadata',
                                          phphtmllibException::DBDATAOBJECT_INVALID_FIELD);
        }
    }

    /**
     * Returns a value by name
     *
     * @param string $name
     */
    protected final function get($name) {
        // we make sure that $name is
        // declared in the metadata
        if (isset($this->meta_data[$name])) {
            return parent::get($name);
        } else {
            throw new DataObjectException('Field ' . $name . ' does not exist in metadata',
                                          phphtmllibException::DBDATAOBJECT_INVALID_FIELD);
        }
    }

    /**
     * This function replaces the data
     * with a new data set
     *
     * Dangerous and should only be used by other classes
     * and object collections
     *
     * @param StdClass $data
     */
    public function set_data(StdClass $data) {
        parent::set_data($data);
        if (!isset($this->data->{$this->primary_key})) {
            $this->new_record = true;
        } else {
            $this->new_record = false;
        }
    }

    /**
     * This function implements
     * data loading from a data
     * source
     *
     * @throws DataObjectException
     *
     */
    protected function load_data() {
        // no sense in trying to load any
        // data if the id is null
        if ($this->data->{$this->primary_key}) {
            try {
                $this->data = $this->db->queryBindOneRow('select * from ' .
                                                         $this->table_name . ' where ' .
                                                         $this->primary_key . '=:id',
                                                         array(':id' => $this->data->{$this->primary_key}));
                $this->new_record = false;
            } catch (PDOException $e) {
                throw new DataObjectException('No results for ' . $this->table_name,
                                              phphtmllibException::DBDATAOBJECT_FIND_NOT_FOUND);
            }

            if (!$this->data) {
                throw new DataObjectException('No results for ' . $this->table_name,
                                              phphtmllibException::DBDATAOBJECT_FIND_NOT_FOUND);
            }
        }
    }

    /**
     * This function implements
     * data saving back to data
     * source
     *
     * It looks at list of changed
     * fields to determine
     * what was changed
     *
     * @return int last insert id
     */
    protected function save_data() {

        if (count($this->changed_fields) > 0) {

            $fields = array();

            if (!$this->new_record) {
                // data already exists
                // we update it
                foreach($this->changed_fields as $key => $dummy) {
                    $fields[$key] = $this->data->$key;
                }

                // save any updates
                try {
                    $this->db->update($this->table_name, $fields,
                                      $this->primary_key . '=:' . $this->primary_key,
                                      array(':' . $this->primary_key => $this->data->{$this->primary_key}));
                } catch (DataBaseException $e) {
                      throw new DataObjectException('Failed to UPDATE record for TABLE '.
                                                    $this->table_name . '(' . $this->primary_key . '=' . $this->data->{$this->primary_key} . ') '.
                                                    $e->getMessage(),
                                                    phphtmllibException::DBDATAOBJECT_UPDATE_FAILED);
                }
            }
            else {
                // this is a new data set
                // we insert it
                foreach ($this->changed_fields as $key => $dummy) {
                    $fields[$key] = $this->data->$key;
                }

                try {
                    $this->data->{$this->primary_key} = $this->db->insert($this->table_name, $fields);

                } catch (PDOException $e) {
                      throw new DataObjectException('Failed to insert new record for TABLE '.$this->table_name,
                                                    phphtmllibException::DBDATAOBJECT_INSERT_FAILED);
                }
            }
        }

        // save all related data objects that
        // were loaded and manupulated
        foreach ($this->related_data_objects as $field => $do) {
            /* @var $do DBDataObject */

            $get_func = 'get_' . $field . '_id';

            // we need to sync the foreign key in the current
            // dataobject with the primary key of the related
            // data object
            $this->set($field . '_id', $do->$get_func());

            $do->save();
        }

        // save objects living in data collections

        $get_func = 'get_' . $this->primary_key;
        $set_func = 'set_' . $this->primary_key;

        foreach ($this->related_data_object_collections as $collection) {
            /* @var $collection DataObjectCollection */
            foreach ($collection as $do) {
                // make sure we sync the connecting foreign
                // key of the related object with the primary
                // key of this object
                $do->$set_func($this->$get_func());

                // save the data object
                $do->save();
            }
        }

        return $this->data->{$this->primary_key};
    }

    /**
     * This function is responsible for
     * deleting the data in the DB.
     *
     */
    protected function delete_data() {
        try {
            $this->db->delete($this->table_name,
                              $this->primary_key . '=:id',
                              array(':id' => $this->data->{$this->primary_key}));

        } catch (PDOException $e) {
              throw new DataObjectException('Failed to delete record for TABLE '.$this->table_name,
                                            phphtmllibException::DBDATAOBJECT_DELETE_FAILED);
        }
    }

    /**
     * Generates unique key for
     * caching
     *
     * @return string
     */
    protected function get_cache_key() {
        return $this->table_name . '_' . $this->primary_key . '_' . $this->data->{$this->primary_key};
    }

    /**
     * Called before loading data
     *
     * We init our db object here
     * and connect to the DB
     *
     */
    protected function before_load() {
        $this->set_db_object();
    }

    /**
     * Called before saving data
     *
     * We init our db object here
     * and connect to the DB
     *
     */
    protected function before_save() {
        if (!$this->db) {
            // only init the DB object if
            // it has not been initialized before
            $this->set_db_object();
        }

        // set reserved database row values
        if (isset($this->meta_data['date_modified']) && !empty($this->changed_fields)) {
            $this->set('date_modified', time());
        }

        if (isset($this->meta_data['date_created']) && $this->new_record) {
            $this->set('date_created', time());
        }

    }

    /**
     * Called before deleting data
     *
     * We init our db object here
     * and connect to the DB
     *
     */
    protected function before_delete() {
        if (!$this->db) {
            // only init the DB object if
            // it has not been initialized before
            $this->set_db_object();
        }
    }

    /* -- DATA RETRIEVAL FUNCTIONS -------------------------------------------------------- */

    /**
     * looks for an instance in the db via
     * a generic where clause and bind vars.
     *
     * @param string $where ie. 'foo=:foo'
     * @param array $bind_vars
     * @param bool $is_primary
     *
     * @throws DataObjectException
     *
     */
    protected function _find($where, $bind_vars=array()) {

        // generate a cache key
        // this key should store the original main id cache key
        // that stores the actual data
        $key = 'find_' . $this->table_name . '_' . implode(':', array_keys($bind_vars)) . '_' . implode(':', $bind_vars);

        if ($this->allow_find_cache && $this->data->{$this->primary_key} = $this->cache->get($key)) {
            // found this id in the cache
            // let's load by id
            $this->load();
        }
        else {

            $this->set_db_object();

            try {
                $data = $this->db->queryBindOneRow('select * from ' .
                                                   $this->table_name . ' where ' . $where,
                                                   $bind_vars);

            } catch (PDOException $e) {
                throw new DataObjectException('No results for ' . $this->table_name . ' where ' . $where,
                                              phphtmllibException::DBDATAOBJECT_FIND_NOT_FOUND);
            }

            if (!$data) {
                throw new DataObjectException('No results for ' . $this->table_name . ' where ' . $where,
                                              phphtmllibException::DBDATAOBJECT_FIND_NOT_FOUND);
            }

            $this->set_data($data);

            if ($this->allow_find_cache) {
                // cache the key
                $this->cache->set($key, $this->data->{$this->primary_key});
            }
        }
    }

    /**
     * This method finds all entries in the db
     * and returns a collection.
     *
     * @param string $where ie. 'foo=:foo'
     * @param array $bind_vars
     * @param string $limit_clause 'limit 10,2'
     *
     * @return DataObjectCollection
     */
    protected function _find_all($where_clause, $bind_vars=array(),
                                 $order_clause=NULL, $limit_clause=NULL) {
        $this->set_db_object();

        try {
            if ($where_clause) {
                $where_clause = ' where '.$where_clause;
            }
            $stmt = $this->db->queryBind('select * from ' .
                                         $this->table_name . $where_clause . ' ' .
                                         $order_clause . ' ' . $limit_clause,
                                         $bind_vars);
        } catch (PDOException $e) {
            throw new DataObjectException('No results for ' . $this->table_name . ' where ' . $where_clause,
                                          phphtmllibException::DBDATAOBJECT_FIND_NOT_FOUND);
        }

        $collection = new DataObjectCollection();
        while ($row = $stmt->fetch()) {
            $class = get_class($this);
            $class = new $class;
            $class->set_data($row);
            $collection->add($class);
        }

        return $collection;
    }

    /**
     * Find a single data object by doing a join query
     * on this data object's table and one or more other
     * tables (in the $tables array).
     * The where clause may contain the special bind var
     * :self, which will not be bound but instead replaced
     * with this object's table name.
     *
     * $tables is a simple array of values; the values are
     * the table names to join and the keys are meaningless.
     * The table names may include aliases, i.e.
     * array('member m','message ms') which will be utilized
     * by the where clause.
     *
     * @param array $tables
     * @param string $where
     * @param array $bind_vars
     */
    protected function _join($tables, $where, $bind_vars=array()) {
        // generate a cache key
        // this key should store the original main id cache key
        // that stores the actual data
        $key = 'join_' . $this->table_name . '|' . implode('|', $tables) . '_' . implode(':', array_keys($bind_vars)) . '_' . implode(':', $bind_vars);

        if ($this->allow_find_cache && $this->data->{$this->primary_key} = $this->cache->get($key)) {
            // found this id in the cache
            // let's load by id
            $this->load();
        }
        else {

            $this->set_db_object();

            $where = str_replace(':self', $this->table_name, $where);


            $tables[] = $this->table_name;

            $tables = implode(', ', $tables);

            try {
                $data = $this->db->queryBindOneRow('select ' . $this->table_name . '.* from ' .
                                                   $tables .
                                                   ' where ' . $where,
                                                   $bind_vars);

            } catch (PDOException $e) {
                throw new DataObjectException('No results for ' . $tables . ' where ' . $where,
                                              phphtmllibException::DBDATAOBJECT_FIND_NOT_FOUND);
            }

            if (!$data) {
                throw new DataObjectException('No results for ' . $tables . ' where ' . $where,
                                              phphtmllibException::DBDATAOBJECT_FIND_NOT_FOUND);
            }

            $this->set_data($data);

            if ($this->allow_find_cache) {
                // cache the key
                $this->cache->set($key, $this->data->{$this->primary_key});
            }
        }
    }

    /**
     * Find all data objects matching a join query
     * on this data object's table and one or more other
     * tables (in the $tables array).
     * The where clause may contain the special bind var
     * :self, which will not be bound but instead replaced
     * with this object's table name.
     *
     * $tables is a simple array of values; the values are
     * the table names to join and the keys are meaningless.
     * The table names may include aliases, i.e.
     * array('member m','message ms') which will be utilized
     * by the where clause.
     *
     * @param array $tables
     * @param string $where_clause
     * @param array $bind_vars
     * @param string $order_clause
     * @param string $limit_clause
     * @return DataObjectCollection
     */
    protected function _join_all($tables, $where_clause, $bind_vars=array(),
                                 $order_clause=NULL, $limit_clause=NULL) {
        $this->set_db_object();

        $where_clause = str_replace(':self', $this->table_name, $where_clause);
        $order_clause = str_replace(':self', $this->table_name, $order_clause);


        $tables[] = $this->table_name;

        $tables = implode(', ', $tables);

        try {
            if ($where_clause) {
                $where_clause = ' where '.$where_clause;
            }
            if ($order_clause) {
                $order_clause = ' order by ' . $order_clause;
            }
            $stmt = $this->db->queryBind('select distinct ' . $this->table_name . '.' . $this->primary_key . ' as ' . $this->primary_key . '_distinct, ' .
                                         $this->table_name . '.* from ' .
                                         $tables . $where_clause . ' ' .
                                         $order_clause . ' ' . $limit_clause,
                                         $bind_vars);
        } catch (PDOException $e) {
            throw new DataObjectException('No results for ' . $tables . ' where ' . $where_clause,
                                          phphtmllibException::DBDATAOBJECT_FIND_NOT_FOUND);
        }

        $collection = new DataObjectCollection();
        while ($row = $stmt->fetch()) {
            $class = get_class($this);
            $class = new $class;
            $class->set_data($row);
            $collection->add($class);
        }

        return $collection;
    }

    /**
     * Returns a related data object
     * by object name
     *
     * This function should never be used or
     * called directly - this is for auto-generated
     * templates only
     *
     * @param string $field
     *
     * @return DBDataObject
     */
    protected function get_related_data_object($field) {
        if (!isset($this->related_data_objects[$field])) {
            $class = $this->build_class_name($field) . 'DataObject';
            $func = 'get_' . $field . '_id';
            $this->related_data_objects[$field] = new $class($this->$func());
        }

        $this->changed = true;

        return $this->related_data_objects[$field];
    }

    /**
     * Sets a related data object
     *
     * This function should never be used or
     * called directly - this is for auto-generated
     * templates only
     *
     * @param string $field
     * @param DataObject $obj
     */
    protected function set_related_data_object($field, DataObject $obj) {
        $this->changed = true;
        $this->related_data_objects[$field] = $obj;
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

    /* -- STATIC FUNCTIONS -------------------------------------------------------- */

    /**
     * This looks for 1 individual row in the DB
     * via a search in the DB for
     * the id based upon the query params.
     *
     * It then creates a dataobject with that id.
     * This helps make sure we use the cache
     * mechanism built in to the DataObject.
     *
     * @param string $class_name
     * @param string $where_clause 'foo = :bar'
     * @param array $bind_vars
     *
     * @return DBDataObject
     */
    public static function find($class_name, $where_clause, $bind_vars=array()) {
        $obj = new $class_name();
        $obj->_find($where_clause, $bind_vars);
        return $obj;
    }

    /**
     * This looks for 1 individual row in the DB
     * via a search in the DB for
     * the id based upon a specific field matching
     * a specific value
     *
     * It then creates a dataobject with that id.
     * This helps make sure we use the cache
     * mechanism built in to the DataObject.
     *
     * @param string $class_name
     * @param string $field_name
     * @param string $field_value
     *
     * @return DBDataObject
     */
    public static function find_by_field($class_name, $field_name, $field_value) {
        return DBDataObject::find($class_name, $field_name . '=:' . $field_name,
                                  array(':' . $field_name => $field_value));
    }

    /**
     * This method tries to find all entries for a
     * DBDataObject table in the db and returns a
     * collection.
     *
     * NOTE: for limit support, you must pass in the
     *       full limit clause.
     *       example: limit 10,20
     *
     * @param string $class_name
     * @param string $where_clause 'foo = :bar'
     * @param array $bind_vars
     * @param string $order_clause 'order by foo'
     * @param string $limit_clause 'limit 10,2'
     *
     * @return DataObjectCollection
     */
    public static function find_all($class_name, $where_clause, $bind_vars=array(),
                                    $order_clause=NULL,$limit_clause=NULL) {
        $obj = new $class_name();

        // we need this to get all of the ids
        return $obj->_find_all($where_clause, $bind_vars,
                               $order_clause, $limit_clause);
    }

    /**
     * Find a single data object by doing a join query
     * on this data object's table and one or more other
     * tables (in the $tables array).
     * The where clause may contain the special bind var
     * :self, which will not be bound but instead replaced
     * with this object's table name.
     *
     * $tables is a simple array of values; the values are
     * the table names to join and the keys are meaningless.
     * The table names may include aliases, i.e.
     * array('member m','message ms') which will be utilized
     * by the where clause.
     *
     * @param array $tables
     * @param string $where
     * @param array $bind_vars
     */
    public static function join($class_name, $tables, $where_clause, $bind_vars=array()) {
        $obj = new $class_name();
        $obj->_join($tables, $where_clause, $bind_vars);
        return $obj;
    }

    /**
     * Find all data objects matching a join query
     * on this data object's table and one or more other
     * tables (in the $tables array).
     * The where clause may contain the special bind var
     * :self, which will not be bound but instead replaced
     * with this object's table name.
     *
     * $tables is a simple array of values; the values are
     * the table names to join and the keys are meaningless.
     * The table names may include aliases, i.e.
     * array('member m','message ms') which will be utilized
     * by the where clause.
     *
     * @param array $tables
     * @param string $where_clause
     * @param array $bind_vars
     * @param string $order_clause
     * @param string $limit_clause
     * @return DataObjectCollection
     */
    public static function join_all($class_name, $tables, $where_clause, $bind_vars=array(),
                                    $order_clause=NULL,$limit_clause=NULL) {
        $obj = new $class_name();

        return $obj->_join_all($tables, $where_clause, $bind_vars, $order_clause, $limit_clause);
    }

    /* -- SERIALIZE FUNCTIONS -------------------------------------------------------- */

    /**
     * This method is called only when this class
     * is deserialized.
     *
     */
    public function __wakeup() {
        //do nothing.
    }

    /**
     * This method is called only when this class
     * is serialized.
     *
     */
    public function __sleep() {
        //reset this to NULL to force a reconnect
        //when it is really needed.
        $this->db = NULL;
        return array_keys( get_object_vars( $this ) );
    }

    /* -- Iterator functions -------------------------------------------------------*/
    
    /**
     * This Iterator method
     * rewinds the index array
     *
     */
	public function rewind() {
        reset($this->meta_data);
    }

    /**
     * This Iterator method
     * gets the current value
     *
     * @return unknown
     */
    public function current() {
    	$var = key($this->meta_data);
    	if ($var) {
    		$value = $this->get($var);
    	} else {
    		$value = false;
    	}
        return $value;
    }
    
    
	/**
	 * This Iterator method gets the
	 * current key
	 *
	 * @return unknown
	 */
    public function key() {
        $var = key($this->meta_data);
        return $var;
    }

    /**
     * This Iterator method
     * advances the index
     *
     * @return unknown
     */
    public function next() {
        $var = next($this->meta_data);
        return $var;
    }

    /**
     * This Iterator method
     * ensures the current value is valid.
     *
     * @return unknown
     */
    public function valid() {
        $var = $this->current() !== false;
        return $var;
    }
}

?>