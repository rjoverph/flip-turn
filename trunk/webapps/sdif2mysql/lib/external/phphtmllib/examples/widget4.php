<?php

/**
 * This example illustrates the use of the
 * VerticalCSSNavTable widget.
 *
 *
 * $Id: widget4.php 2394 2007-02-22 21:27:08Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage widget-examples
 * @version 3.0.0
 *
 */

/**
 * Include the phphtmllib libraries
 *
 */
include_once("includes.inc");


//create the page object
$page = new HTMLDocument("phpHtmlLib Widgets - VerticalCSSNavTable",
                         phphtmllib::XHTML_TRANSITIONAL);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}

//add the css
$page->add_css_link( "/css/widgets.php" );

//create the VerticalCSSNavTable Object
//create the widget with
//Title of 'VerticalCSSNavTable' and
//subtitle of 'Widget'
//overall width of 400 pixels ( u can use % as well )
$cssnavtable = new VerticalCSSNavTable("VerticalCSSNavTable", "Widget", 400);
$cssnavtable->add("#", "Some Link", "This is title text");
$cssnavtable->add("#", "Another");
$cssnavtable->add("#", "Another", "This is title text");

$page->add( $cssnavtable );

print $page->render();
?>
