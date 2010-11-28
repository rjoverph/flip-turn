<?php
/**
 * The project generator
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Generator
 */

/**
 * This script helps to generate
 * a project based on the framework.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Generator
 */
class ProjectGenerator {

    /**
     * Standard input stream.
     *
     * @var filehandle
     */
    protected $stdin;

    /**
     * Standard output stream.
     *
     * @var filehandle
     */
    protected $stdout;

    /**
     * Standard error stream.
     *
     * @var filehandle
     */
    protected $stderr;

    /**
     * Associated controller name.
     *
     * @var string
     */
    protected $controllerName = null;


    /**
     * DataBase Connection parameters
     *
     */
    protected $db_options = array('type' => 'mysql',
                                  'host' => 'localhost',
                                  'port' => '',
                                  'username' => '',
                                  'password' => '',
                                  'name' => ''
                                  );
    /**
     * The full path to the base directory
     * of the project
     *
     */
    protected $project_path;


    /**
     * The project name
     */
    protected $project_name;

    /**
     * project class name
     */
    protected $project_class_name;

    /**
     * The local config object
     *
     */
    protected $config;

    /**
     * connected DataBase object
     *
     */
    protected $db;

    public function __construct() {
        $this->stdin = fopen('php://stdin', 'r');
        $this->stdout = fopen('php://stdout', 'w');
        $this->stderr = fopen('php://stderr', 'w');
        $this->config = new Config;
        $this->welcome();
        $this->help();
    }

    /**
     * Outputs an ASCII art banner to standard output.
     *
     */
    private function welcome() {
        $this->stdout('');

        $this->stdout(' __  _  _  __  _  _  ___ _  _         _  __ ');
        $this->stdout('|__] |__| |__] |__|   |  |\/| |   |   | |__|');
        $this->stdout('|    |  | |    |  |   |  |  | |__ |__ | |__|');

        $this->hr();
        $this->stdout('');
    }

    /**
     * Outputs usage text on the standard output.
     *
     */
    public function help() {
        $this->stdout('phpHtmlLib Project Generator:');
        $this->hr();
        $this->stdout('This script generates the base application layout to help you');
        $this->stdout('build web applications with the phpHtmlLib framework.');
        $this->stdout('');
        $this->stdout('To cancel at any time, hit CTRL-C.');
        $this->stdout('');
        $this->hr('');
        $this->stdout('commands:');
        $this->stdout('  project  -- build a new starter project');
        //$this->stdout('  autoload -- rebuild an existing project autoload.inc file.');
        //$this->stdout('  data -- rebuild the dataobject templates from DataBase.');
        $this->stdout('  quit -- quit.');
        $this->stdout('');
    }



    /**
     * execute the generation of the project.
     *
     */
    public function execute() {

        //ask for project name.
        $command = $this->getInput("Enter Command",
                                   array('project',
                                         /*'autoload',
                                         'data',*/
                                         /*'database',*/
                                         'quit'));
        switch (strtolower($command)) {
        case 'project':
        case 'p':
            //create a brand new project
            $this->project();
            break;

        case 'database':
            $this->database();
            break;

       /* case 'autoload':
        case 'a':
            //regenerate autoload.inc
            $this->autoload();
            break;

        case 'data':
        case 'd':
            //build or rebuild DataObject templates
            $this->dataobjects();
            break;
            */

        case 'quit':
        case 'q':
            exit;
            return;
        }
    }


    /**
     * This method is used to generate an entirely new project
     *
     */
    public function project() {
        $this->stdout("Build a new project");

        //get the project name.
        $this->ask_project_name();

        $path = realpath($this->getInput("Enter install path (ie. /var/www will create /var/www/<project name>) "));
        $project_path = $path.'/'.$this->project_name;

        if (file_exists($project_path)) {
            //looks like the path exists already.
            //double check to make sure it's empty.
            if (file_exists($project_path.'/lib') ||
                file_exists($project_path.'/dev') ||
                file_exists($project_path.'/htdocs')) {
                //ok it looks like it's not empty.
                $this->stderr("Project directory is not empty! Aborting. check ".$project_path."\n");
                exit;
            }
        } else {
            //we need to create the project path
            $res = mkdir($project_path,0755,TRUE);
            if (!$res) {
                $this->stderr("Couldn't create $poject_path base directory.");
                exit;
            }
        }

        //we have a valid, empty project directory
        //lets create everything now.
        $this->stdout("Creating ".$this->project_name." Project directory structure in ".$project_path);

        //build all of the project directories
        $this->init_project_directories($project_path);

        //setup any config options we want to be in the
        //final config.inc
        $this->init_project_config($project_path);

        //now start creating the files from the templates

        //start with the dev dir
        //$this->copy_template('dev/project.php', $project_path.'/dev/');
        $this->build_autoload_generator($project_path, $this->project_name);

        //for now, lets just copy all of phphtmlib into the
        //lib/external dir.
        $this->stdout("Copying phphtmllib install to project ".$project_path."/lib/external/phphtmllib");
        $this->dircopy(PHPHTMLLIB, $project_path."/lib/external/phphtmllib");

        //copy the phphtmllib images over
        $this->stdout("Copying phphtmllib images to ".$project_path."/htdocs/images");
        $this->dircopy($project_path."/lib/external/phphtmllib/data/images/widgets",
                       $project_path."/htdocs/images");

        //Manage the database setup and dataobjects
        $use_db = $this->database($project_path);

        $this->copy_project_files($project_path);

        //done w/ the creation of the project.
        //lets run the autoloader.
        $this->autoload($project_path);

        //lets write out the config.inc to disk
        $this->write_project_config($project_path);

        //now write the init
        $this->write_project_init($project_path);

        if ($use_db) {
        	//build the DataObjects
        	$this->dataobjects( $project_path );
        }


        //regenerate autoload.inc file
        //because we have new classes
        $this->autoload($project_path);


        //How about generating the documentation?
        $this->documentation($project_path);


        //tell the user how to point apache to the new dir.
        $this->stdout("The new project is now complete.  You can add the following settings to your apache config");

        $apache = "<VirtualHost localhost:80>
  DocumentRoot \"$project_path/htdocs\"
  ServerName $this->project_name

  <Directory \"$project_path/htdocs\">
     Options Indexes FollowSymLinks
     AllowOverride None
     Order allow,deny
     Allow from all
  </Directory>
</VirtualHost>";
        $this->stdout($apache);
    }

    /**
     * This method creates all of the normal project
     * directories
     *
     * @param string $project_path
     */
    protected function init_project_directories($project_path) {

        $this->create_path($project_path.'/apidocs');
        $this->create_path($project_path.'/cache', 0777);
        $this->create_path($project_path.'/dev');
        $this->create_path($project_path.'/db');

        $this->create_path($project_path.'/htdocs/js');
        $this->create_path($project_path.'/htdocs/css');
        $this->create_path($project_path.'/htdocs/images');

        $this->create_path($project_path.'/lib/core/data/dataobjects');
        $this->create_path($project_path.'/lib/core/datalist');
        $this->create_path($project_path.'/lib/core/db');
        $this->create_path($project_path.'/lib/core/page');

        $this->create_path($project_path.'/lib/modules/home');
        $this->create_path($project_path.'/lib/modules/home/page');

        $this->create_path($project_path.'/lib/external');
    }

    /**
     * This method is used to setup the default
     * project config.inc entries needed by any
     * phphtmllib project/app
     *
     */
    protected function init_project_config($project_path) {
        $this->config->set('widget_image_path', '/images/widgets');
        $this->config->set('file_cache_dir', $project_path.'/cache');
        $this->config->set('controller_request_debug', true);
        $this->config->set('cache_enabled', true);
        $this->config->set('uncaught_exception_trace_depth', 5);
        $this->config->set('uncaught_exception_output', 'html');

        $this->config->set('DB_TYPE', 'mysql');
        $this->config->set('DB_HOST', 'localhost');
        $this->config->set('DB_PORT', '');
        $this->config->set('DB_NAME', '');
        $this->config->set('DB_USERNAME', '');
        $this->config->set('DB_PASSWORD', '');

    }

    /**
     * This method is used to copy the needed project files
     * to the new project directory
     */
    protected function copy_project_files($project_path) {

        //the css files
        $this->copy_template('htdocs/css/main.css', $project_path.'/htdocs/css');
        $this->copy_template('htdocs/css/fonts.css', $project_path.'/htdocs/css');

        //copy the js links over
        //$cmd = "cp ".$project_path."/lib/external/phphtmllib/src/js/ajax.js ".$project_path."/htdocs/js";
        copy($project_path."/lib/external/phphtmllib/src/js/ajax.js", $project_path."/htdocs/js/ajax.js");
        //passthru($cmd);

        //$cmd = "cp -a ".$project_path."/lib/external/phphtmllib/src/js/scriptaculous-js-1.7.0 ".$project_path."/htdocs/js";
        $this->dircopy($project_path."/lib/external/phphtmllib/src/js/scriptaculous-js-1.7.0",
                       $project_path."/htdocs/js/scriptaculous-js-1.7.0");
        //passthru($cmd);

        //write the main page class out
        $this->copy_template('lib/core/page/projectPage.inc', $project_path.'/lib/core/page',
                             array('XX_PROJECT_NAME_XX' => $this->project_name,
                                   'XX_PROJECT_CLASS_NAME_XX' => $this->project_class_name),
                             $this->project_class_name.'Page.inc');

        //write the main controller point
        $this->copy_template('htdocs/index.php', $project_path.'/htdocs',
                             array('XX_PROJECT_NAME_XX' => $this->project_name));


        //write the main page class out
        $this->copy_template('lib/core/datalist/projectAjaxDefaultHTMLDataList.inc', $project_path.'/lib/core/datalist',
                             array('XX_PROJECT_NAME_XX' => $this->project_name,
                                   'XX_PROJECT_DB_NAME_XX' => $this->project_class_name.'DB',
                                   'XX_PROJECT_DL_NAME_XX' => $this->project_class_name.'AjaxDefaultHTMLDataList'),
                             $this->project_class_name.'AjaxDefaultHTMLDataList.inc');

        //write the main page class out
        $this->copy_template('lib/core/db/projectDB.inc', $project_path.'/lib/core/db',
                             array('XX_PROJECT_NAME_XX' => $this->project_name,
                                   'XX_PROJECT_DB_NAME_XX' => $this->project_class_name.'DB',
                                   'XX_DB_CACHE_SINGLETON_XX' => 'FileCache::singleton()'),
                             $this->project_class_name.'DB.inc');

        $this->copy_template('lib/modules/home/page/HomePage.inc', $project_path.'/lib/modules/home/page',
                             array('XX_PROJECT_NAME_XX' => $this->project_name,
                                   'XX_PROJECT_CLASS_NAME_XX' => $this->project_class_name));
    }

    /**
     * This method is used to
     * regenerate the autoload.inc file
     *
     */
    public function autoload($project_path = null) {

        $project_path = $this->test_project_path($project_path);
        if (!$project_path) {
            return ;
        }

        //make sure there is a dev dir with the autoload_generator.php in it
        $dev = $project_path.'/dev';
        if (!file_exists(realpath($dev))) {
            $this->stderr("No $dev directory exsists.  The autoload_generator.php file should live there.");
            $answer = $this->getInput("Would you like to create the $dev directory and autoload_generator.php?", array("yes", "no"));
            if ($answer == 'yes') {
                //create the dev dir.
                $this->build_autoload_generator($project_path);
            } else {
                //we are done
                $this->stderr("autoload generation cannot continue.");
                $this->execute();
            }
        }

        $autoload_gen = $project_path.'/dev/autoload_generator.php';

        if (!file_exists(realpath($autoload_gen))) {
            $this->stderr("$autoload_gen file doesn't exist");
            $this->execute();
        }

        //ok we know the autoload_generator exists
        //lets execute it.
        $this->stdout("Executing ".$project_path."/dev/autoload_generator.php");
        $cmd = "cd ".$project_path."/dev; php -f autoload_generator.php";
        //$this->stdout($cmd);
        passthru($cmd);
    }


    /**
     * This function is used to build the autoload_generator.php
     * script for a project.
     *
     * @param string $project_base_dir
     */
    public function build_autoload_generator($project_path, $project_name=null) {
        if (!file_exists(realpath($project_path.'/dev'))) {
            $this->create_path($project_path.'/dev');
        }

        if ($project_name == null) {
            $project_name = trim($this->getInput("Enter Project Name"));
        }

        //now build the file from template.
        $this->copy_template('dev/autoload_generator.php', $project_path.'/dev',
                             array('XX_PROJECT_NAME_XX' => $project_name));

        $this->stdout("\n".$project_path."/dev/autoload_generator.php script created.\n\n".
                      "This script is used to build the php __autload() function with it's\n".
                      "mapping of classes that are in your project.  When you add new classes\n".
                      "to your project, just re-run the ".$project_path."/dev/autoload_generator.php\n".
                      "script and your classes wil automatically be included properly.\n\n");
    }



    /**
     * This method handles setting up the DataBase
     * objects for the project
     *
     * @param string $project_path
     * @param boolean $prompt
     */
    public function database($project_path = null, $prompt=true) {

    	//Ask if they want database support
    	$answer = $this->getInput("Would you like to setup your project to talk to a Database?", array("yes", "no"));
    	if ($answer == 'no') {
            return false;
        }
    	
        //test to make sure the project exists
        if (!$this->test_project_path($project_path)) {
            return false;
        }

        //make sure the dev dir is there
        if (!$this->test_path($project_path.'/dev', true)) {
            $this->stderr("The project dev dir doesn't exist and/or couldn't be created in ".$project_path.'/dev');
            $this->execute();
        }

        //make sure the lib dir is there
        if (!$this->test_path($project_path.'/lib', true)) {
            $this->stderr("The project lib dir doesn't exist and/or couldn't be created in ".$project_path.'/lib');
            $this->execute();
        }

        //make sure the lib/db dir is there
        if (!$this->test_path($project_path.'/lib/db', true)) {
            $this->stderr("The project lib/db dir doesn't exist and/or couldn't be created in ".$project_path.'/lib/db');
            $this->execute();
        }

        if ($prompt) {
            $this->stdout("\n\nThis portion of the project generator is used for setting up the DataBase class and any\n".
                          "DataObjects that map to tables in an already existing database.  You will be asked for the\n".
                          "connection parmeters to your database.  This script currently only supports mysql or postgres.\n".
                          "After the settings are entered this script will try to make a connection to the database \n".
                          "and then extract any tables and create DataObjects for those tables.");
        }

        $default = $this->config->get('DB_TYPE', 'mysql');
        $db_type = $this->getInput('What Type of database server?', array('mysql', 'pgsql'), $default);
        $this->config->set('DB_TYPE', $db_type);

        $default = $this->config->get('DB_HOST', 'localhost');
        $db_host = $this->getInput('What is the host/ip of the database server?',null, $default);
        $this->config->set('DB_HOST', $db_host);

        if ($this->config->get('DB_PORT')) {
            $default = $this->config->get('DB_PORT');
        } else {
            if ($db_type == 'mysql') {
                $default = 3306;
            } else {
                $default = 5432;
            }
        }

        $db_port = $this->getInput('What is the Database port?',null, $default);
        $this->config->set('DB_PORT', $db_port);

        $default = $this->config->get('DB_NAME', '');
        $db_name = $this->getInput('What is the db schema/name ?', null, $default);
        $this->config->set('DB_NAME', $db_name);

        $default = $this->config->get('DB_USERNAME', '');
        $db_username = $this->getInput('Enter DataBase username', null, $default);
        $this->config->set('DB_USERNAME', $db_username);

        $default = $this->config->get('DB_PASSWORD', '');
        $db_password = $this->getInput('Enter DataBase password', null, $default);
        $this->config->set('DB_PASSWORD', $db_password);

        //lets test the connection to the db.
        $db_connection_flag = $this->test_db_connection($project_path);

        if (!$db_connection_flag) {
            $this->stdout("\nNot able to connect to the database.  Bypassing DataObject creation.");
        }

    }


    /**
     * This method is used to test the connection to the DB
     * This assumes the local config is setup properly
     */
    protected function test_db_connection($project_path) {
        $this->stdout("Testing Database connection");
        $GLOBALS['config'] = $this->config;
        $dsn = DataBase::dsn($this->config->get('DB_TYPE'),
                             $this->config->get('DB_NAME'),
                             $this->config->get('DB_HOST'));
        try {
            $this->db = new DataBase($dsn,
                                     $this->config->get('DB_USERNAME'),
                                     $this->config->get('DB_PASSWORD'));
            $this->stdout("Connection success.");
            return true;
        } catch (Exception $e) {
            $this->stderr("Couldn't connect to database :".$e->getMessage());
            //lets try again
            $answer = $this->getInput("Try again to connect to the database?", array('yes', 'no'));
            if ($answer == 'yes') {
                return $this->database($project_path, false);
            } else {
                return false;
            }
        }
    }


    /**
     * This method is used to generate an entirely new project
     *
     */
    public function dataobjects($project_path = null) {
        $this->stdout("Build/Rebuild the DataObjects");

        //test to make sure the project exists
        $project_path = $this->test_project_path($project_path);
        if (!$project_path) {
            return;
        }

        //lets test the connection to the db.
        $db_connection_flag = $this->test_db_connection($project_path);

        if (!$db_connection_flag) {
            $this->stdout("\nNot able to connect to the database.  Bypassing DataObject creation.");
        }

        //lets inquire from the connected db.
        //assume a connected DB for now.

        //write out the xml file
        $this->build_dot_config($project_path);


        //wrote out the DataBaseObject base class
        $this->copy_template('lib/core/data/projectDBDataObject.inc', $project_path.'/lib/core/data/',
                             array('XX_PROJECT_NAME_XX' => $this->project_name,
                                   'XX_PROJECT_DB_NAME_XX' => $this->project_class_name.'DB',
                                   'XX_PROJECT_DB_DO_NAME_XX' => $this->project_class_name.'DBDataObject',
                                   'XX_DB_DO_CACHE_SINGLETON_XX' => 'FileCache::singleton()'),
                                   $this->project_class_name.'DBDataObject.inc');

        //write out the data object template generator script
        $this->copy_template('dev/dot_generator.php', $project_path.'/dev/',
                             array('XX_PROJECT_NAME_XX' => $this->project_name,
                                   'XX_PARENT_CLASS_NAME_XX' => $this->project_class_name,
                                   'XX_PROJECT_DB_DO_NAME_XX' => $this->project_class_name.'DBDataObject'));

        //ok now that the dot_config.xml is built
        //we need to exec the dot_generator.php
        $this->stdout("\nGenerating DataObjects and DataObjectTemplate Classes.\n".
                      "If you add more tables to the database make sure to edit the\n".
                      $project_path."/dev/".$this->project_name.".xml file and add the table name.\n".
                      "Then you can run the ".$project_path."/dev/dot_generator.php to rebuild the\n".
                      "DataObjects that phphtmllib supports.  (Note: This will only overwrite the \n".
                      "DataObjectTemplate classes, not the child classes that you can modify).\n\n");
        sleep(1);
        $this->stdout("Executing ".$project_path."/dev/dot_generator.php");
        $cmd = 'cd '.$project_path. '/dev; php -f ./dot_generator.php';
        passthru($cmd);
    }

    /**
     * This method walks the user through
     * questions to create a data object template
     * generator config dot_config.xml
     *
     * @param string $path
     */
    protected function build_dot_config($project_path) {

        $tables = $this->db->meta_tables();
        $found_tables = '';
        $count = 1;
        foreach($tables as $table) {
            $found_tables .= $table.', ';

            if (($count % 3) == 0) {
                $found_tables = substr($found_tables, 0, strlen($found_tables)-2)."\n";
            }
            $count++;
        }
        $this->stdout("We found the following tables\n".$found_tables);

        //var_dump($tables);
        $tables_xml = new XMLTagClass('tables', array('parent'=>$this->project_class_name.'DBDataObject'));
        foreach($tables as $table) {
            $tables_xml->add(new XMLTagClass('table', array('name' => $table)));
        }

        $db_xml = new XMLTagClass('database');
        $connection_xml = new XMLTagClass('connection');
        $db_info = $this->db->get_connection_info();
        $connection_xml->add(new XMLTagClass('host',array(), $db_info['host']),
                             new XMLTagClass('driver', array(), $db_info['driver']),
                             new XMLTagClass('name', array(),$db_info['dbname']),
                             new XMLTagClass('user', array(), $db_info['username']),
                             new XMLTagClass('password', array(), $db_info['password']));

        $db_xml->add($connection_xml, $tables_xml);


        $doc = new XMLDocument('config');
        $doc->add($db_xml);

        $filename = $project_path.'/dev/'.$this->project_name.'.xml';
        file_put_contents($filename, $doc->render());

        $this->stdout("Created ".$filename." which contains the DataObject generator config.");
        return true;
    }



    /**
     * This method tries to generate
     * the api docs the first time
     * @param string $project_path
     */
    protected function documentation($project_path, $prompt = true) {
        if ($prompt) {
            $this->stdout("\n\nNow we will try and generate the api documentation for your\n".
                          "new project the first time.");
        }

        $answer = $this->getInput("Which documentation generator would you like to use?", array('doxygen', 'phpdoc', 'skip'));
        switch(strtolower($answer)) {
            case 'skip':
                $this->stdout('Skipping documentation build.');
                return;
            case 'doxygen':
                $doxygen = $this->getInput("Please provide full path to doxygen executable (ie. /usr/bin/doxygen)", null, 'cancel');
                if ($doxygen == 'cancel') {
                    $this->documentation($project_path, false);
                } else {
                    if (!file_exists($doxygen)) {
                        $this->stderr("Couldn't find doxygen at ".$doxygen);
                        $this->documentation($project_path, false);
                    }
                    //we need to copy the Doxygen.conf template first
                    $this->copy_template('apidocs/Doxygen.conf', $project_path.'/apidocs',
                                         array('XX_PROJECT_NAME_XX' => $this->project_name,
                                               'XX_PROJECT_DIR' => $project_path));
                    //now execute
                    $cmd = "cd ".$project_path."/apidocs; ".$doxygen." Doxygen.conf";
                    passthru($cmd);

                    $this->stdout("\n\nYou can now view the generated documentation by pointing your browser to\n".
                                  $project_path."/apidocs/html/index.hml\n");
                }
                break;
            case 'phpdoc':
                $phpdoc = $this->getInput("Please provide full path to phpdoc executable (ie. /usr/local/bin/phpdoc)", null, 'cancel');
                if ($phpdoc == 'cancel') {
                    $this->documentation($project_path, false);
                } else {
                    if (!file_exists($phpdoc)) {
                        $this->stderr("Couldn't find phpdoc at ".$phpdoc);
                        $this->documentation($project_path, false);
                    }
                    //we need to copy the Doxygen.conf template first
                    $this->copy_template('apidocs/docit.sh', $project_path.'/apidocs',
                                         array('XX_PROJECT_NAME_XX' => $this->project_name,
                                               'XX_PHPDOC_PATH_XX' => $phpdoc));
                    //now execute
                    $cmd = "cd ".$project_path."/apidocs; sh docit.sh;";
                    passthru($cmd);
                }
                break;
        }

    }



    /**
  ;   * This method writes over the project's
     * config.inc file
     *
     *
     */
    protected function write_project_config($project_path) {
        $config_file = $project_path."/lib/config.inc";
        if (file_exists($config_file)) {
            $answer = $this->getInput("Overwrite config file? (".$config_file.")", array('yes','no'));
            if ($answer == 'no') {
                $this->stderr("leaving ".$config_file." alone.");
                return;
            }
        }

        $contents = '$GLOBALS[\'config\'] = Config::singleton();'."\n\n";
        foreach($this->config as $name => $value) {
            $contents .= '$config->set(\''.$name.'\', \''.$value."');\n";
        }


        $this->copy_template('lib/config.inc', $project_path.'/lib',
                             array('XX_PROJECT_NAME_XX' => $this->project_name,
                                   'XX_CONFIG_XX' => $contents));
    }


    /**
     * This writes the project init.inc file out.
     */
    protected function write_project_init($project_path) {

        $this->copy_template('lib/init.inc', $project_path.'/lib',
                             array('XX_PROJECT_NAME_XX' => $this->project_name));
    }


    /**
     * This method is used to set
     * the project name
     *
     * @param string $name
     */
    public function set_project_name($name) {

        $this->project_name = $name;

        //generate the OO version of the project name
        $this->project_class_name = $this->generate_project_class_name($this->project_name);
    }


    /**
     * This method asks for the project name
     * Once it gets it, it will set the project
     * name and the project_class name
     */
    protected function ask_project_name() {
        $project_name = trim($this->getInput("Enter Project Name (ie. myproject not www.myproject.com).\n".
                                             "The project name is used as base class object name (ie. myprojectDB)."));
        //make sure there aren't any spaces in the name
        if (strstr($project_name, ' ')) {
            //we found a space!  doh
            $this->stderr("Project names can't have spaces in them.  Try again.");
            $this->ask_project_name();
        }

        $this->set_project_name($project_name);
    }


    /**
     * Some general purpose methods
     *
     */


    /**
     * This method is used to create a dir path on disk
     *
     * @param string $path
     * @param int $permissions defaults to 0755
     */
    protected function create_path($dir, $permissions = 0755) {
        $this->stdout($dir);
        mkdir($dir, $permissions, TRUE);
        //because php sucks at times
        chmod($dir, $permissions);
    }


    /**
     * This method tests to see if the project directory
     * exists.  It tries to make sure it's there.
     *
     * @param string $project_path
     */
    protected function test_project_path($project_path=null) {
        if ($project_path == null) {
            $project_path = realpath($this->getInput("Enter full path to project location (ie /var/www/myproject) "));
        }

        //make sure the project dir exists.
        if (!file_exists($project_path)) {
            $this->stderr("Couldn't find path to project: '".$project_path."'");
            return false;
        }

        $this->project_path = $project_path;
        return $project_path;
    }


    /**
     * Test to see if the specified path exists
     * and optionally create it, if it doesn't exist
     *
     * @param string $path
     */
    protected function test_path($path, $create=false) {
        if (!file_exists($path)) {
            if ($create) {
                $this->create_path($path);
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    }


    /**
     * This method is used to copy a template file
     * to the final destination and replace any
     * template variables.
     *
     * @param string $source_file
     * @param string $destination
     * @param array $template_vars
     * @param string $filename
     */
    protected function copy_template($source, $destination, $template_vars=array(),
                                     $filename=null) {
        $source_file = PHPHTMLLIB.'/src/generator/project_templates/'.$source;
        if (!file_exists(realpath($source_file))) {
            $this->stderr("Failed to find source template ".$source_file);
            exit;
        }

        $source_file_contents = file_get_contents($source_file);

        if (!empty($template_vars)) {
            foreach($template_vars as $var => $value) {
                $source_file_contents = str_replace($var, $value, $source_file_contents);
            }
        }

        //now write the file to it's destination.
        if ($filename == null) {
            $filename = basename($source);
        }

        $out_filename = $destination.'/'.$filename;
        file_put_contents($out_filename, $source_file_contents);
    }

    /**
     * This function is used to copy an entire
     * directory from one location to another
     *
     * @param string $srcdir
     * @param string $dstdir
     * @param boolean $verbose
     * @return unknown
     */
    protected function dircopy($srcdir, $dstdir, $verbose = false) {
        $num = 0;
        if (!is_dir($dstdir)) {
            mkdir($dstdir);
        }
        if ($curdir = opendir($srcdir)) {
            //var_dump($curdir);
            while($file = readdir($curdir)) {
                //var_dump($file);
                if ($file != '.' && $file != '..' & $file != '.svn') {
                    $srcfile = $srcdir . '/' . $file;
                    $dstfile = $dstdir . '/' . $file;
                    if (is_file($srcfile)) {
                        if ($verbose) {
                            echo "Copying '$srcfile' to '$dstfile'...";
                        }
                        if (copy($srcfile, $dstfile)) {
                              touch($dstfile, filemtime($srcfile)); $num++;
                              if ($verbose) {
                                  echo "OK\n";
                              }
                        } else {
                              echo "Error: File '$srcfile' could not be copied!\n";
                        }
                      } else if (is_dir($srcfile)) {
                          $num += $this->dircopy($srcfile, $dstfile, $verbose);
                      }
                 }
            }
        closedir($curdir);
  }
  return $num;
}


    /**
     * This method generates a php OO class name from
     * the project name (string).
     *
     * @param string $project_name
     * @return string
     */
    protected function generate_project_class_name($project_name) {
        return str_replace(' ', '', $project_name);
    }

    /**
     * Prompts the user for input, and returns it.
     *
     * @param string $prompt Prompt text.
     * @param mixed $options Array or string of options.
     * @param string $default Default input value.
     * @return Either the default value, or the user-provided input.
     */
    protected function getInput($prompt, $options = null, $default = null) {
        if (!is_array($options)) {
            $print_options = '';
        } else {
            $print_options = '(' . implode(',', $options) . ')';
        }

        if ($default === null) {
            $this->stdout('');
            $this->stdout($prompt . " $print_options \n" . '> ', false);
        } else {
            $this->stdout('');
            $this->stdout($prompt . " $print_options \n" . "[$default] > ", false);
        }
        $result = trim(fgets($this->stdin));

        if (empty($result)) {
            //see if there is a default
            if ($default !== null) {
                return $default;
            } else {
                //there is no default
                //and there was no response.
                //try again
                $this->stderr('Invalid Response.  Try again');
                return $this->getInput($prompt, $options, $default);
            }
        } else {
            //the response wasn't empty
            //make sure it's valid.
            if (!empty($options)) {
                //options aren't empty
                //make sure the response
                //was valid
                if (is_array($options)) {
                    if (!in_array($result, $options)) {
                        $this->stderr('Invalid Response.  Try again');
                        return $this->getInput($prompt, $options, $default);
                    } else {
                        return $result;
                    }
                } else {
                    //only 1 option
                    if (strcasecmp($options, $result) != 0) {
                        $this->strerr('Invalid Response. Try again');
                        return $this->getInput($prompt, $options, $default);
                    }
                }
            } else {
                //no options
                return $result;
            }
        }
    }

    /**
     * Outputs to the stdout filehandle.
     *
     * @param string $string String to output.
     * @param boolean $newline If true, the outputs gets an added newline.
     */
    protected function stdout($string, $newline = true) {
        if ($newline) {
            $string .= "\n";
        }

        fwrite($this->stdout, $string);
    }

    /**
     * Outputs to the stderr filehandle.
     *
     * @param string $string Error text to output.
     */
    protected function stderr($string) {
        fwrite($this->stderr, $string);
    }


    /**
     * Outputs a series of minus characters to the standard output, acts as a visual separator.
     *
     */
    function hr() {
        $this->stdout('---------------------------------------------------------------');
    }
}


?>
