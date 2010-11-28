#!/usr/local/bin/php
<?php
/**
 * This script generates the autoload.inc file
 *
 * @package sdif2mysql
 */

$lib_path = realpath('../lib');
ini_set('include_path', '.:/usr/local/lib:'.$lib_path);

define('PHPHTMLLIB', realpath('../lib/external/phphtmllib'));
$GLOBALS['path_base'] = realpath('..');
require_once('external/phphtmllib/required_includes.inc');
require_once('external/phphtmllib/src/generator/AutoloadGenerator.inc');

$path = realpath('../lib');
$gen = new AutoloadGenerator($path);
$gen->set_project_name('sdif2mysql');
$gen->set_autoload_path($path.'/');
$gen->set_include_path($path);
$gen->add_form_content_parent('AjaxStandardFormContent');
$gen->set_debug_mode(true);

$gen->execute();
?>
