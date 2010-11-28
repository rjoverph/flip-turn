<?php
/**
 * This file contains the AutoloadGenerator class
 * that is used to build the autoload.inc file for
 * the libs as well as an app.
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Generator
 */

/**
 * This is a class for automatically
 * generating autoload.inc file for your
 * project under phphtmllib framework.
 *
 * This will scan all directories and build
 * a ClassMap with a list of all classes as well as
 * special classes like renderable, soapable...
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Generator
 */
class AutoloadGenerator {

    /**
     * No hashing, exposing class name
     * debugging mode
     *
     */
    const HASH_NONE = 0;

    /**
     * Hashing in search engine
     * optimized mode
     *
     */
    const HASH_SEO = 1;

    /**
     * Hashing in numerical
     * increments
     *
     */
    const HASH_NUMERIC = 2;

    /**
     * Hashing in md5
     *
     */
    const HASH_MD5 = 3;

    /**
     * Hashing in rot13 style
     *
     */
    const HASH_ROT13 = 4;

    /**
     * File name to use for autoload file
     * There should be no need to change this
     *
     */
    const AUTOLOAD_FILENAME = 'autoload.inc';

    /**
     * This is used by a temporary __autoload
     * function in order to load required
     * classes for reflection usage
     *
     * @var array
     */
    public static $autoload_data = array();

    /**
     * Holds your project name here
     *
     */
    protected $project_name = 'phpHtmlLib';

    /**
     * If this is enabled, debug mode
     * will add error checking to __autoload function
     * and will collect and report on included classes
     * in the debug panel
     *
     * @var bool
     */
    protected $debug_mode = false;

    /**
     * Main lib directory of the project
     * where to start scanning for autoload
     * files.
     * This directory should live outside of the
     * web server accessible area
     */
    protected $scan_dir = array();

    /**
     * Optional directory prefix for
     * each included file
     *
     * @var string
     */
    protected $include_path = '';

    /**
     * Specifies the path where
     * to store autoload.inc file
     *
     * @var string
     */
    protected $autoload_path = '';

    /**
     * the autoload function name
     */
    protected $autoload_name = "__autoload";

    /**
     * Tells us what type of target
     * hashing to use for target
     * obfuscation
     */
    protected $hash_type = AutoloadGenerator::HASH_SEO;

    /**
     * Used for numeric target hash
     */
    private $hash_counter = 1;

    /**
     * Holds class information
     *
     * @var array
     */
    protected $data = array();

    /**
     * Keeps a list of warning messages
     *
     * @var array
     */
    protected $messages = array();

    /**
     * Show warning messages?
     *
     * @var bool
     */
    protected $enable_warnings = true;

    /**
     * Used internally to generate the
     * class map
     *
     * @var array
     */
    protected $class_map = array('class' => array(),
                                 'target' => array(),
                                 'menuable' => array(),
                                 'soapable' => array(),
                                 'soapapi' => array());

    /**
     * List of extensions to scan
     *
     * @var array
     */
    protected $allowed_extensions = array('.inc', '.php');

    /**
     * List of class names that are if extended
     * will be directly renderable by the application
     *
     * @var array
     */
    protected $renderable_parents = array('Container','HTMLPage', 'HTMLWidget', 'HTMLDataList',
                                          'JSONWidget');

    /**
     * list of class names that if extended will
     * be added to the list of form_content classes
     *
     * @var array
     */
    protected $formcontent_parents = array('FormContent', 'StandardFormContent');

    /**
     * Keeps a list of files and directories to
     * be excluded from the autoload
     *
     * @var array
     */
    protected $excluded_files = array('CVS',
                                      '.svn',
                                      'autoload.inc',
                                      'init.inc',
                                      'config.inc',
                                      'local_includes',
                                      'phphtmllib/src/generator/project_templates',
                                      //'phphtmllib/widgets/svg/',
                                      'phphtmllib/widgets/images/',
                                      //'phphtmllib/widgets/wml/',
                                      'phphtmllib/doc/',
                                      'phphtmllib/examples/',
                                      'phphtmllib/images/',
                                      'phphtmllib/css/',
                                      'phphtmllib/src/tag_classes/',
                                      'phphtmllib/src/tag_utils/',
                                      'phphtmllib/test/',
                                      'phphtmllib/tutorial/',
                                      'htdocs/',
                                      'PEAR');

    /**
     * contains the resulting output string
     */
    protected $output = '';


    /**
     * Constructor
     *
     * @param string $scan_dir
     */
    public function __construct($scan_dir) {
        $this->include_path = $scan_dir;
        $this->add_scan_dir($scan_dir);
    }

    /**
     * Adds an error message
     *
     * @param string $message
     * @param string $file
     */
    public function add_message($message, $file = '') {
        if ( $file ) {
            $message = 'File: ' . $file . "\n" . $message;
        }
        $this->messages[] = $message;
    }

    /**
     * Add an excluded file or directory path
     *
     * @param string
     */
    public function add_exclude($path) {
        $this->excluded_files[] = $path;
    }

    /**
     * Adds another path to traverse
     *
     * @param string
     */
    public function add_scan_dir($dir) {
        $path = realpath($dir);
        if ($path) {
            $this->scan_dir[] = $path;
        } else {
            print ("Ignoring invalid ".$dir);
        }

    }

    /**
     * Enable showing of warning messages?
     *
     * @param bool $flag
     */
    public function enable_warnings($flag) {
        $this->enable_warnings = $flag;
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
     * Sets hash type for target
     * obfuscation
     *
     * @param int $hash_type
     */
    public function set_hash_type($hash_type) {
        $this->hash_type = $hash_type;
    }

    /**
     * Sets debug generation mode
     *
     * If this is enabled, it will add error
     * checking to __autoload function
     * and will collect and report on included
     * classes in the debug panel
     *
     * @param bool $flag
     */
    public function set_debug_mode($flag) {
        $this->debug_mode = $flag;
    }

    /**
     * This method allows you to add a new
     * allowed extension to the list of
     * acceptable files.
     *
     * @param string $extension (ie. .php)
     */
    public function add_extension($extension) {
        $this->allowed_extensions[] = $extension;
    }

    /**
     * Sets the path where to store the new
     * autoload.inc file
     *
     * @param string $path
     */
    public function set_autoload_path($path) {
        $this->autoload_path = $path;
    }

    /**
     * Sets the name of the autoload function
     * to generate.  This allows you to add the
     * generated autoload function to your own
     * __autoload() function.
     *
     * @param string $path
     */
    public function set_autoload_name($name) {
        $this->autoload_name = $name;
    }

    /**
     * Sets the path that will be stripped out
     * of all files in the autoload.inc
     * Normally this would be the include_path
     * from php.ini
     *
     * @param string $path
     */
    public function set_include_path($path) {
        $this->include_path = $path;
    }

    /**
     * add an entry to the list of Renderable
     * parent classes
     *
     * @param string $class_name
     */
    public function set_renderable_parents($parents) {
        $this->renderable_parents = $parents;
    }

    /**
     * add an entry to the list of FormContent
     * parent classes
     *
     * @param string $class_name
     */
    public function add_form_content_parent($class_name) {
        $this->formcontent_parents[] = $class_name;
    }

    /**
     * Resolves class name to its target hash
     *
     * @param string $class_name
     * @return string
     */
    protected function get_target_hash($class_name) {

        switch ($this->hash_type) {

            case AutoloadGenerator::HASH_NONE:
                return $class_name;

            case AutoloadGenerator::HASH_SEO:
                return $this->get_seo_name($class_name);

            case AutoloadGenerator::HASH_NUMERIC:
                return $this->hash_counter++;

            case AutoloadGenerator::HASH_MD5:
                return md5($class_name);

            case AutoloadGenerator::HASH_ROT13:
                return str_rot13($class_name);

            default:
                throw new Exception('Unknown hash type ' . $this->hash_type);
                break;
        }

    }

    /**
     * Builds and returns a search optimized
     * target class name
     *
     * @param string $name
     *
     * @return string
     */
    protected function get_seo_name($name) {

        $reflect = new ReflectionClass($name);
        if ( $id = $reflect->getConstant('ID') ) {
            $str = $id;
        }
        else {
            $name = str_replace(array('Page', 'FormContent', 'Widget', 'DataList', 'AjaxAction'),
                                array('',     '-fc',         '-w',     '-dl',      '-aa'),
                                $name);
            $str = '';
            $len = strlen($name);
            $low_found = false;

            for ($i=0; $i<$len; $i++) {

                $char = $name[$i];

                if (strtoupper($char) == $char) {
                    if ($low_found) {
                        $str .= '-';
                    }
                }
                else if (!$low_found) {
                    $low_found = true;
                    if ($i>3) {
                        $str = substr($str, 0, strlen($str) - 1) . '-' . substr($str, strlen($str)-1);

                    }
                }

                $str .= strtolower($char);
            }
        }

        while (isset($this->class_map[$str])) {
            $str .= '0';
        }

        $str = str_replace('--', '-', $str);

        return $str;
    }

    /**
     * Prints an error message and exits
     *
     * @param string $str
     */
    protected function print_error($str) {
        print("\n" . $str . "\n");
        exit;
    }

    /**
     * This function scans the
     * given start directory
     *
     */
    protected function scan($dir_name) {
        $found = 0;

        $dir = dir($dir_name);
        if (!$dir) {
            //bogus
            return;
        }

        while ( $item = $dir->read() ) {
            if ( $item == '.' || $item == '..' ) {
                continue;
            }

            $file_name = $dir_name . '/' . $item;            
            $continue_file = FALSE;
            $continue_dir = FALSE;

            // check if we need to exclude this item
            foreach ($this->excluded_files as $excluded_file) {
                if ( strstr($file_name, $excluded_file) ) {
                    $continue_file = TRUE;
                    continue;
                } else if ( strstr($dir_name . '/' .$item, $excluded_file) ) {
                    $continue_dir = TRUE;
                    continue;
                }
            }            
            

            if ( $continue_file ) {
                // this file or directory is excluded
                //var_dump('skipping FILE '. $file_name);
                continue;
            } else if ( $continue_dir ) {
                //var_dump('skipping DIR '. $dir_name . '/'.$item);
                continue;
            }
            
        

            if ( is_dir($dir_name . '/' . $item) ) {
                // this is a directory, recurse inside
                //var_dump('scan dir '. $dir_name . '/' .$item);
                $found += $this->scan($dir_name . '/' . $item);
            } else {
                $extension = substr($item, strlen($item)-4, 4);                          

                if ( in_array($extension, $this->allowed_extensions) ) {
                    $class_name = substr($item, 0, strlen($item) - 4);
                                    

                    // check if this is actually a class and it matches the file name
                    $content = file_get_contents($file_name);
                    if ( !strstr($content, 'class ' . $class_name) &&
                         !strstr($content, 'interface ' . $class_name) ) {
                             if ($this->debug_mode) {
                                 if (!strstr($file_name, 'external')) {
                                     $this->add_message("Couldn't find classname that matches the filename in file ".$file_name, $file_name);
                                 }
                             }              
                        continue;
                    }
                

                    if ( !strstr($file_name, 'phphtmllib/') ) {
                        // some basic guidelines check
                        if ( (strstr($content, '$_REQUEST') || strstr($content, '$_GET')) && $this->enable_warnings) {
                            $this->add_message('Should not be using global $_REQUEST/$_GET/$_POST for direct access to the variables. Please use Request::singleton()->get() instead.', $file_name);
                        }

                        if ( strstr($content, 'index.php') ) {
                            $this->add_message('Does this file contain direct reference to index.php? Should be using RequestBuilder object to build URLs.',  $file_name);
                        }

                        if ( strstr($content, '<br>') && $this->enable_warnings) {
                            $this->add_message('Does this file contain hardcoded HTML tags? Should be using appropriate tag objects for building HTML tags.',  $file_name);
                        }
                    }

                    if ( isset($this->data[$class_name]) ) {
                        $this->print_error('Duplicate class found: ' . $file_name . ' conflicts with ' .
                                           $this->data[$class_name]['FILE_NAME']);
                    } else {
                        $this->add_file($class_name, $file_name);
                        $found++;
                    }
                }
            }
        }
        return $found;
    }

    /**
     * This method adds a new entry to the autoload table.
     *
     * @param string $class_name
     * @param string $file_name
     */
    protected function add_file($class_name, $file_name) {
        $this->data[$class_name] = array('FILE_NAME' => $file_name);

        // here we store autoload data used
        // by our temporary autoload function
        self::$autoload_data[$class_name] = $file_name;
    }

    /**
     * This method allows us to filter where the file gets
     * placed in the classmap.
     *
     * @param ReflectionClass $reflect
     * @param string $class_name
     */
    protected function place_class($reflect, $class_name) {

        if ( $reflect->implementsInterface('Menuable') ) {
            $this->class_map['menuable'][$class_name] = $class_name;
        }

        if ($reflect->implementsInterface('SOAPable')) {
            $this->class_map['soapable'][$this->get_target_hash($class_name)] = $class_name;
        }

        if ($reflect->implementsInterface('SOAPAPI')) {
            $this->class_map['soapapi'][$this->get_target_hash($class_name)] = $class_name;
        }

        foreach ($this->renderable_parents as $parent) {
            if ( $reflect->isSubclassOf($parent) && !in_array($class_name, $this->class_map['target'])) {
                $this->class_map['target'][$this->get_target_hash($class_name)] = $class_name;
            }
        }

        foreach($this->formcontent_parents as $parent) {
            if ( $reflect->isSubclassOf($parent) && !in_array($class_name, $this->class_map['target'])) {
                $this->class_map['target'][$this->get_target_hash($class_name)] = $class_name;
            }
        }

    }

    /**
     * Writes the autload.inc file
     *
     */
    protected function write_autoload() {
        $str = "<?php\n" .
               "/**\n" .
               " * This is an auto-generated file. Please do not modify!\n" .
               " * Generated on " . date(DATE_W3C) . " by AutoloadGenerator\n" .
               " *\n" .
               " * @package $this->project_name\n".
               " */\n";

        $str .= "class ClassMap {\n\n";

        // for debug mode, need to always have it
        $str .= 'static $included = array();' . "\n\n";

        $lookup_str = 'static $target_lookup = array(' . "\n";
        foreach ($this->class_map as $key => $data) {
            $str .= 'static $' . $key . " = array(\n";

            if (count($data)>0) {

                foreach ($data as $hash => $cname) {
                    if ($key != 'menuable') {
                        $str .= "'" . $hash . "'=>'" . $cname . "',\n";
                        if ($key == 'target') {
                            $lookup_str .= "'" . $cname . "'=>'" . $hash . "',\n";
                        }
                    }
                    else {
                        $str .= "'" . $cname . "',\n";
                    }
                }

                $str = substr($str, 0, strlen($str) - 2);
            }

            $str .= "\n);\n";
        }

        $lookup_str = substr($lookup_str, 0, strlen($lookup_str) - 2);
        $str .= $lookup_str  . "\n);";

        $str .= "\n\n}\n\n".
                'function '.$this->autoload_name.'($c) {';

        if ( $this->debug_mode ) {
            // add debugging information
            $str .= 'if (!isset(ClassMap::$class[$c])) {throw new Exception("Class $c does not exist in ClassMap");}$t = microtime(1);';
        }

        $str .= 'require(ClassMap::$class[$c]);';

        if ( $this->debug_mode ) {
            // add debugging information
            $str .= 'ClassMap::$included[$c] = number_format((microtime(1) - $t)*1000, 3) . \' ms\';';
        }

        $str .= "}\n?>";

        $path = $this->autoload_path . self::AUTOLOAD_FILENAME;
        echo $path;
        $this->output = $str;
        file_put_contents($path, $str);
    }

    /**
     * This function builds the
     * actual autoload.inc file
     *
     */
    public function execute() {
        //set this to a large value so we can include every single file in the application.
        ini_set('memory_limit', '64M');        

        print ("\n");
        foreach( $this->scan_dir as $scan_dir) {
            if ($scan_dir) {
                print('Scanning ' . $scan_dir . ' (' . $this->scan($scan_dir). ') ...');
                print("\n");
            }
        }

        print("\nAnalyzing classes ...(".count($this->data).")");
        
     if ( count($this->messages) > 0 ) {
            print("\n\n");
            foreach ($this->messages as $message) {
                print($message . "\n\n");
            }
            print('---- ' . count($this->messages) . " problem(s) found ----\n\n");
        }

        ksort($this->data);
        // now we analyze each class that we found
        foreach ($this->data as $class_name=>$data) {
            $class_path = str_replace($this->include_path, '', $data['FILE_NAME']);
            if ($class_path[0] == '/') {
                $class_path = substr($class_path, 1);
            }

            $this->class_map['class'][$class_name] = $class_path;

            require_once($data['FILE_NAME']);
            $reflect = new ReflectionClass($class_name);

            // we do not analyze abstract classes
            if ( !$reflect->isAbstract() ) {
                $this->place_class($reflect, $class_name);
            }
        }

        print ("\n");       

        print('Writing autoload file ...');
        uksort($this->class_map['class'], 'strnatcasecmp');
        uksort($this->class_map['menuable'], 'strnatcasecmp');
        uksort($this->class_map['target'], 'strnatcasecmp');
        $this->write_autoload();

        print("\n\n");
        print("Total " . count($this->data) . " classes processed\n\n");

        if ( $this->debug_mode ) {
            print("---- WARNING: AutoloadGenerator was run in DEBUG MODE. You do not want this in production. ----\n\n");
        }
    }

}

ini_set('error_prepend_string', '');
ini_set('error_append_string', "\n");

function __autoload($c) {
    if (!isset(AutoloadGenerator::$autoload_data[$c])) {
        //var_dump(AutoloadGenerator::$autoload_data);
        throw new Exception("Class $c does not exist in ClassMap");
    }
    require(AutoloadGenerator::$autoload_data[$c]);
}

?>