#!/usr/bin/php
<?php
/**
 * This file is a sample script on how to use
 * the DBDataObjectTemplateGenerator class
 *
 * @package XX_PROJECT_NAME_XX
 *
 * @see DBDataObjectTemplateGenerator
 */

$lib_path = realpath('../lib');
ini_set('include_path', ini_get('include_path').':'.$lib_path);

$GLOBALS['path_base'] = realpath('..');

require_once('autoload.inc');
require_once('init.inc');

$xml = file_get_contents('XX_PROJECT_NAME_XX.xml');
$gen = new DBDataObjectTemplateGenerator($xml);
$gen->set_base_path('../lib/core/data/dataobjects');
$gen->set_project_name('XX_PROJECT_NAME_XX');
$gen->set_parent_name('XX_PROJECT_DB_DO_NAME_XX');

$gen->execute();
?>
