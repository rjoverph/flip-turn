<?php
/**
 * Another example of how to build an
 * XML Document with the WML support
 * that phpHtmlLib provides.
 *
 *
 * $Id: example6.php 2986 2007-09-27 23:41:06Z hemna $
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

//
//

/**
 * WML helpers aren't included in the
 * autoload.inc by default
 */
include_once(PHPHTMLLIB.'/src/wml/WMLTAGS.inc');
/**
 * load the wml tag utility functions
 */
include_once(PHPHTMLLIB.'/src/wml/wml_utils.inc');

//build the wml document object.
$wmldoc = new WMLDocument;

//turn off the rendering of the http Content-type
//so we can see the output in a non WAP browser.
$wmldoc->show_http_header(FALSE);

$card1 = wml_card("Testing", "card1");
$card1->add(wml_do("accept", wml_go("#card2")));

$options = array("Testing1" => "test1",
                 "Testing2" => "test2",
                 "Foo" => "bar");
$card1->add( html_p( form_select("name", $options) ) );
$wmldoc->add( $card1 );


$card2 = wml_card("Foo", "card2");
$card2->add( html_p( "This is card #2!"));
$wmldoc->add( $card2 );

//this will render the entire page
print $wmldoc->render();
?>
