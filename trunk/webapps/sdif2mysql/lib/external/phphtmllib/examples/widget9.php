<?php

/**
 * This example illustrates the use of the
 * RoundTitleTable widget.
 *
 *
 * $Id: widget9.php 2781 2007-05-18 17:52:38Z hemna $
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
$page = new HTMLDocument("phpHtmlLib Widgets - RoundTable",
                         phphtmllib::XHTML_TRANSITIONAL);

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
//subtitle of "some subtitle"
//overall width of 300 pixels ( u can use % as well )
$nav = new RoundTitleTable("Some lame title", "some subtitle", "300");

$img_div = DIVtag::factory("font10",
                    IMGtag::factory("http://phphtmllib.newsblob.com/images/phphtmllib_logo.png") );
$img_div->set_style("text-align:center;");


$nav->add(DIVtag::factory("font10bold", "foo bar blah"),
          BRtag::factory(2), $img_div);

$page->add( $nav );


//this will render the entire page
//with the content you have added
//wrapped inside all the required
//elements for a complete HTML/XHTML page.
//NOTE: all the objects in phphtmllib have
//      the render() method.  So you can call
//      render on any phphtmlib object.
print $page;
?>
