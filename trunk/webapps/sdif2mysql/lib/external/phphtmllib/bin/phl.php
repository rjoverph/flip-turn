#!/usr/local/bin/php
<?php
/**
 * This script builds the phphtmllib autoload.inc file.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @todo update to generate the lib's autoload.inc file
 */


/**
 * build the correct path
 */
$path = realpath('..');
ini_set('include_path', '.:'.$path);

define('PHPHTMLLIB', $path);
require_once('autoload.inc');
require_once('src/generator/ProjectGenerator.inc');

function __autoload($c) {
    return phphtmllib_autoload($c);
}

$autoload_path = $path.'/';

$gen = new ProjectGenerator();
$gen->execute();

?>
