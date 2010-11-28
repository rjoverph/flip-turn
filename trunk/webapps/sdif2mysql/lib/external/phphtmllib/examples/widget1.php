<?php

/**
 * This example illustrates the use of the
 * NavTable widget.
 *
 *
 * $Id: widget1.php 2394 2007-02-22 21:27:08Z hemna $
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
$page = new HTMLDocument("phpHtmlLib Widgets - NavTable", phphtmllib::XHTML_TRANSITIONAL);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}


//add the css link to the default theme which will
//automatically generate the css classes used
//by the Navtable widget, as well as the other widgets.
$page->add_css_link( "/css/widgets.php" );


//create the NavTable Object
//create the widget with a
//title of "Some lame title"
//subtitle of "some subtitle"
//overall width of 300 pixels ( u can use % as well )
$nav = new NavTable("Some lame title", "some subtitle", "300");

$nav->add("#", "Some Link", "This is title text");
$nav->add("#", "Another");
$nav->add_blank();
$nav->add("#", "Some Link", "This is title text");
$nav->add("#", "Another");

$page->add( $nav );


//this will render the entire page
//with the content you have added
//wrapped inside all the required
//elements for a complete HTML/XHTML page.
//NOTE: all the objects in phphtmllib have
//      the render() method.  So you can call
//      render on any phphtmlib object.
print $page->render();
?>
