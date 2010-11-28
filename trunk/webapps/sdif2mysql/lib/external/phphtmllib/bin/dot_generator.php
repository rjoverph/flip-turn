#!/usr/local/bin/php
<?php
/**
 * This file is a sample script on how to use
 * the DBDataObjectTemplateGenerator class
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage scripts
 * 
 * @see DBDataObjectTemplateGenerator
 */

$lib_path = realpath('..');
ini_set('include_path', ini_get('include_path').':'.$lib_path);

/**
 * we need the autoloader Classmap
 */
require_once('autoload.inc');

/**
 * our autoloader
 */
function __autoload($class) {
  phphtmllib_autoload($class);
}

$path = realpath('..');

$xml = implode('',file('config.xml'));
//var_dump($xml);
$gen = new DBDataObjectTemplateGenerator($xml);
$gen->set_base_path('.');

$gen->execute();

?>
