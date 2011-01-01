<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * include files needed by the Flip-Turn web application
 *
 * @package Flip-Turn
 * @author Mike Walsh
 */
 
define('PHPHTMLLIB_RELPATH', "/phphtmllib") ;
include_once("phphtmllib/phpHtmlLib.inc") ;
include_once(PHPHTMLLIB_ABSPATH . "/includes.inc");

$ft_inc_path = realpath('./include') ;
ini_set('include_path', ini_get('include_path') .  PATH_SEPARATOR .
    $ft_inc_path . PATH_SEPARATOR . PHPHTMLLIB_ABSPATH . "/external/adodb") ;

?>
