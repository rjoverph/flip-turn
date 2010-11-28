<?php

/**
 * This example illustrates the use of the
 * TextCSSNav widget.
 *
 *
 * $Id: widget3.php 2394 2007-02-22 21:27:08Z hemna $
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
$page = new HTMLDocument("phpHtmlLib Widgets - TextCSSNav",
                         phphtmllib::XHTML_TRANSITIONAL);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}

//add the css
$page->add_css_link( "/css/widgets.php" );

//create the InfoTable Object
//create the widget and enable
//the auto highlighting of the selected Nav
$textcssnav = new TextCSSNav(TRUE);
$textcssnav->add($_SERVER["PHP_SELF"], "TextCSSNav", "Some Link dude");
$textcssnav->add($_SERVER["PHP_SELF"], "Some Link", "Some Link dude");
$textcssnav->add($_SERVER["PHP_SELF"], "Another", "Another link...Click me");
$textcssnav->add($_SERVER["PHP_SELF"], "And another", "Some Link dude");

$page->add( $textcssnav );

print $page->render();
?>
