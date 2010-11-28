<?php

/**
 * Another example of how to build an
 * XML Document with the XML support
 * that phpHtmlLib provides.
 *
 *
 * $Id: example5.php 2807 2007-05-22 18:50:33Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage examples
 * @version 2.0.0
 *
 */

/**
 * Include the phphtmllib libraries
 */
include_once("includes.inc");

//build the xml document object with a
//root xml tag of <example5>, and a <!DOCTYPE>
//link attribute of "some doctype link"
$xmldoc = new XMLDocument("example5", "http://foo.com/DTDS/mail.dtd");

//add some tags to the root element
$xmldoc->add( XMLTagClass::factory("testing", array(), "foo",
					  XMLTagClass::factory("blah", array("value" => 1)) ) );

//build an array that represents
//xml tags and their values.
$arr = array("Foo" => array("bar" => "bleh",
							"bar" => array("testing" => "php")));
//add those tags from the array
$xmldoc->add( array_to_xml_tree( $arr ) );

//this will render the entire page
print $xmldoc->render();
?>
