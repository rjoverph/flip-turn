<?php

/**
 * This example illustrates the use of the
 * FooterNav widget.
 *
 *
 * $Id: widget5.php 2394 2007-02-22 21:27:08Z hemna $
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
$page = new HTMLDocument("phpHtmlLib Widgets - FooterNav Example",
                         phphtmllib::XHTML_TRANSITIONAL);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}

//add the css
$page->add_css_link( "/css/widgets.php" );

//Build the Footer Widget object
$footer = new FooterNav("PHPHtmlLib");

//Set the copyright flag, to automatically show
//a copyright string under the links
$footer->set_copyright_flag( TRUE );

//set the email address for the webmaster
//this will automatically build a clickable
//mailto link for that email address
$footer->set_webmaster_email("waboring@buildabetterweb.com");

//now build a few links that the user can click on
//for a common footer navigational object.
$footer->add("/", "Home");
$footer->add("/downloads.php", "Downloads");
$footer->add($_SERVER["PHP_SELF"]."?debug=1", "Debug");

$page->add( $footer );

print $page->render();
?>
