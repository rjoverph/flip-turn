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
$lib_path = realpath('..');
//var_dump( ini_get('include_path') );
ini_set('include_path', ini_get('include_path').':'.$lib_path);

require_once('src/generator/AutoloadGenerator.inc');

$path = realpath('..');
$autoload_path = realpath('..').'/';

$gen = new AutoloadGenerator($path);

$gen->set_autoload_path($autoload_path);
$gen->set_autoload_name('phphtmllib_autoload');
$gen->execute();

$autoload_file = $autoload_path = $autoload_path.AutoloadGenerator::AUTOLOAD_FILENAME;

//ok lets modify the file to add the 
//required include.
echo $autoload_file."\n";

$contents = implode('', file($autoload_file));

$contents = str_replace(' */', " */\nrequire('required_includes.inc');\n", $contents);

$fp = fopen($autoload_file, 'w');
fwrite($fp, $contents);
fclose($fp);


?>
