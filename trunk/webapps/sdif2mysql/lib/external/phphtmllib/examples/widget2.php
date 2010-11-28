<?php

/**
 * This example illustrates the use of the
 * InfoTable widget.
 *
 *
 * $Id: widget2.php 2394 2007-02-22 21:27:08Z hemna $
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
$page = new HTMLDocument("phpHtmlLib Widgets - InfoTable",
                         phphtmllib::XHTML_TRANSITIONAL);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}
$page->add_css_link( "/css/widgets.php" );


//create the InfoTable Object
//create the widget with a
//title of "Some lame title"
//overall width of 300 pixels ( u can use % as well )
$infotable = new InfoTable("Some lame title", "300");

$infotable->add_row("this is a","test");
$infotable->add_row("this is a test", "&nbsp;");
$infotable->add_row("this is a","test");
$infotable->add_row("this is a test", "&nbsp;");

$page->add( $infotable );

print $page->render();
?>
