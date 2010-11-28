<?php
/**
 * This example illustrates the use of the
 * ActiveTab Widget.  This widget gives you
 * the ability to build content for n # of tabs
 * and have the browser switch between the tabs
 * without a request to the server.
 *
 * $Id: widget8.php 3088 2007-11-01 22:47:18Z hemna $
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
include("includes.inc");

//create the page object
$page = new HTMLDocument("phpHtmlLib Widgets - ActiveTab Example",
                         phphtmllib::XHTML_TRANSITIONAL);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}
//use the default theme
$page->add_css_link( "/css/widgets.php" );
$page->add_js_link("/js/scriptaculous-js-1.7.0/lib/prototype.js");


//build the active tab widget
//with a width of 500 pixels wide
$tab = new ActiveTab(500);

//build a NavTable widget
$navtable = new NavTable("NavTable", "Widget", "200");
$navtable->add("#", "Some Link", "This is title text");
$navtable->add("#", "Another");
$navtable->add_blank();
$navtable->add("#", "Some Link", "This is title text");
$navtable->add("#", "Another");

//build a VerticalCSSNavTable widget
$cssnavtable = new VerticalCSSNavTable("VerticalCSSNavTable", "Widget", "300");
$cssnavtable->add("#", "Some Link", "This is title text");
$cssnavtable->add("#", "Another");
$cssnavtable->add("#", "Another", "This is title text");

//build a form for one of the tabs
$formname = "fooform";
$form = html_form($formname, "#");
$form->add( form_active_checkbox("foo", "some foo text", "ass"),html_br() );
$form->add( form_active_checkbox("bar", "some bar text", "bar"),html_br() );
$form->add( form_active_checkbox("blah", "some blah text", "blah"), html_br() );
$form->add( html_br(2) );

$form->add( form_active_radio("assradio", array("foo"=>1, "bar"=>2), 2, FALSE ) );
$form->add( html_br(2),
			form_active_radio("assradio2", array("foo"=>1, "bar"=>2, "testing"=> 3), 2 ));


//now add the tabs and their content.
$tab->add("Foo Tab", $navtable);
$tab->add("Bar", $form);
$tab->add("Hemna", $cssnavtable, TRUE);
$tab->add("Walt", Container::factory("Walt tab content"));

//add the tab to the page and render everything.
$page->add( $tab );
print $page;
?>
