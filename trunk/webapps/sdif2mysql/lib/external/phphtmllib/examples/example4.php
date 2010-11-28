<?php

/**
 * Another example of how to build a
 * parent PageWidget object to provide
 * a base class for building a consistent
 * look/feel accross a web application.
 *
 *
 * $Id: example4.php 2778 2007-05-18 17:17:06Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage examples
 * @version 3.0.0
 *
 */

/**
 * Include the phphtmllib libraries
 */
include_once("includes.inc");

/**
 * use the class we defined from
 * Example 3.
 */
include_once("MyLayoutPage.inc");

//enable the automatic detection of debugging
define("DEBUG", TRUE);

/**
 * define a child class that only changes the
 * content in the left block
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage examples
 * @version 3.0.0
 *
 */
class LeftBlockPage extends MyLayoutPage {

    /**
     * this function returns the contents
     * of the left block.  It is already wrapped
     * in a TD
     *
     * @return HTMLTag object
     */
    function left_block() {
        $div = new DIVtag();
        $div->set_style("padding-left: 6px;");

        //now add our list of examples
        $navtable = new VerticalCSSNavTable("LEFT BLOCK", "", "90%");

        $navtable->add("http://www.slashdot.org", "Slashdot",
                       "Go to /. in another window", "_slash");
        $navtable->add("http://www.freshmeat.net", "Freshmeat",
                       "Go To Freshmeat in another window", "_fm");
        $navtable->add("http://www.php.net", "PHP.net",
                       "Go To the Source for php", "_php");
        $navtable->add("http://www.zend.com", "Zend.com",
                       "Go to Zend", "_zend");

        $div->add( $navtable, BRtag::factory());

        return $div;
    }
}



$page = new LeftBlockPage("phpHtmlLib Example 4 - MyLayoutPage child");


//this will render the entire page
print $page->render();
?>
