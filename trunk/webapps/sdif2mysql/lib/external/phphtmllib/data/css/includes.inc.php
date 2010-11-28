<?php
/**
 * build the darkbluetheme
 * 
 * @package phpHtmlLib
 * @subpackage css
 */

/**
 * find the doc root
 */
$doc_root = $_SERVER["DOCUMENT_ROOT"];
define('PHPHTMLLIB', $doc_root."/phphtmllib" );
include_once( PHPHTMLLIB."/includes.inc");

//build the $css_container object
include_once( PHPHTMLLIB."/css/css_container.inc.php");

?>
