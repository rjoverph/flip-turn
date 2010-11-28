<?php

/**
 *
 * include files needed by the examples
 *
 * @package phpHtmlLib
 * @subpackage examples
 */

/**
 * include the autoload.inc first
 */
include_once('../autoload.inc');

/**
 * declare the __autoload() function to do the
 * work of including class files
 * 
 */
function __autoload($class) {
    return phphtmllib_autoload($class);
}

?>
