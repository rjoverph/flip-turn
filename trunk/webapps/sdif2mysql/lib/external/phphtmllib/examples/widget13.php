<?php

/**
 * This example illustrates the use of the
 * permissions checking mechanism built into the
 * PageWidget object.
 *
 *
 * $Id: widget13.php 2781 2007-05-18 17:52:38Z hemna $
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


/**
 *
 * This page class shows how to do simple
 * permissions check.
 *
 * @package phpHtmlLib
 * @subpackage widget-examples
 */
class PermissionsCheckTestPage extends HTMLPage {


    function __construct($title) {
        //turn on the ability to do a permissions check
        $this->allow_permissions_checks(TRUE);

        parent::__construct($title, phphtmllib::HTML);

        //we need this for the css defined for the InfoTable
        //for the DialogWidget.  The DialogWidget uses InfoTable.
        $this->add_css_link("/css/widgets.php");
    }

    function head_content() {

    }

    /**
     * This method is called during constructor time to check
     * to make sure the page is allowed to build and render
     * any content.
     *
     * @return boolean FALSE = not allowed.
     */
    function permission() {
        //If you want to see a 'permissions' error
        //on this page then pass in the query string
        //variable 'failed=1' on the url to this script.
        if (isset($_REQUEST["failed"])) {
            //ok we 'failed'.  Lets set the specialized
            //error message with a link to go back.
            $this->set_permissions_message(
                Container::factory("You don't have permissions!",
                          BRtag::factory(2),
                          Atag::factory($_SERVER["PHP_SELF"],"GO BACK")));
            return false;
        }
        return true;
    }

    /**
     * This will only get called if we have permissions to
     * build and render the content for this page object.
     *
     * @return object
     */
    function body_content() {
        $this->add( new MessageBoxWidget("Some title", "400",
                                         Container::factory("This is a message",
                                                            BRtag::factory(2),
                                                            "Want to see a permissions error?",
                                                            BRtag::factory(),
                                                            Atag::factory($_SERVER["PHP_SELF"]."?failed=1","Click Here"))
                                         ));
    }
}

//build the Page object and try and
//render it's content.
//the permissions checking happens at
//'constructor' time.
$page = new PermissionsCheckTestPage("testing");

//the render method will not call the
//content building methods if the permissions
//fail.
print $page->render();
?>
