<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * include files needed by the Flip-Turn web application
 *
 * @package Flip-Turn
 * @author Mike Walsh
 */

//  Make sure we have a configuration file!
if (!file_exists('ft-config.php'))
    die('<h2>No Flip-Turn configuration found, unable to proceed.</h2>') ;
 
//  Set up phpHtmlLib library or not much will work
define('PHPHTMLLIB_RELPATH', "/phphtmllib") ;
include_once("phphtmllib/phpHtmlLib.inc") ;
include_once(PHPHTMLLIB_ABSPATH . "/includes.inc");

//  Setup include path to bring in class files and ADODB properly
$ft_inc_path = realpath('./include') ;
ini_set('include_path', ini_get('include_path') .  PATH_SEPARATOR .
    $ft_inc_path . PATH_SEPARATOR . PHPHTMLLIB_ABSPATH . "/external/adodb") ;

?>
