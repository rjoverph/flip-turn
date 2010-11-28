<?php
/**
 * build the darkbluetheme
 * 
 * @package phpHtmlLib
 * @subpackage css
 */

/**
 * get the includes
 */
include_once("includes.inc.php");

require_once(PHPHTMLLIB."/widgets/html/includes.inc.php");

//cache this
Header("Cache-Control: public");

print $css_container->render();
?>
