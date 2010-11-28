<?php
/**
 * This file contains the main entry point
 * for the web application.  This file was
 * autogenerated by the ProjectGenerator.
 *
 * You may want to alter the include paths and
 * place them in your php.ini
 *
 * @package sdif2mysql
 */

//make sure the lib dir is in the default include path
$lib_path = realpath('../lib');
//ini_set('include_path', '.:/usr/local/lib:'.$lib_path);
ini_set('include_path', ini_get('include_path') . PATH_SEPARATOR . $lib_path);

//need this for external lib paths includes
//that happen outside of autoload.
$GLOBALS['path_base'] = '..';


// autoload function for all our classes
require($GLOBALS['path_base'].'/lib/autoload.inc');

// setup error handling and required parameters
require($GLOBALS['path_base'].'/lib/init.inc');


$c = new Controller('HomePage');
//debugging is enabled for development
//I would recommend turning this off
//for production.
$c->set_debug(TRUE);
$c->execute();

?>
