<?php

/**
 * This example illustrates the use of the
 * RoundTitleTable widget.
 *
 *
 * $Id: widget12.php 2394 2007-02-22 21:27:08Z hemna $
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
$page = new HTMLDocument("phpHtmlLib Widgets - MessageBoxWidget",
                         phphtmllib::HTML);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}

//add the css link to the default theme which will
//automatically generate the css classes used
//by the Navtable widget, as well as the other widgets.
$page->add_css_link( "/css/widgets.php" );
$page->add_css_link( "/css/fonts.css" );


//create the RoundTitleTable Object
//create the widget with a
//title of "Some lame title"
//overall width of 300 pixels ( u can use % as well )
$dialog = new MessageBoxWidget("Some title", "300",
                               "This is a message");
//$dialog->add_button("test", "index.php");

$page->add( $dialog );


//this will render the entire page
//with the content you have added
//wrapped inside all the required
//elements for a complete HTML/XHTML page.
//NOTE: all the objects in phphtmllib have
//      the render() method.  So you can call
//      render on any phphtmlib object.
print $page->render();
?>
