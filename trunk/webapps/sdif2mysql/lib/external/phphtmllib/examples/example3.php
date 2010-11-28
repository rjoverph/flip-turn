<?php

/**
 * Another example of how to build a
 * parent PageWidget object to provide
 * a base class for building a consistent
 * look/feel accross a web application.
 *
 *
 * $Id: example3.php 2777 2007-05-18 17:14:14Z hemna $
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


//Some applications want to provide a
//consistent layout with some common
//elements that always live on each
//page.
//  An easy way to do that is to
//build a child class to the
//PageWidget object that defines the
//layout in logical blocks named as
//methods.

//For example,  A common layout is
//to have a header block at the top,
//followed by a content block, which
//contains a left block, and right block.
//followed by a footer block.

// --------------------------------
// |         header block         |
// --------------------------------
// |       |                      | <- Main
// | left  |    right block       | <- block
// | block |                      | <-
// |       |                      | <-
// --------------------------------
// |         footer block         |
// --------------------------------

//You would then define 6 methods in
//the child to PageWidget named
//body_content() - contains the outer most
//                 layout
//
//header_block() - builds the content for
//                 the header block, which
//                 stays the same among
//                 many pages.
//
//main_block()   - which builds the left
//                 block (typically used for
//                 navigation), and the
//                 main content block
//left_block()   - contains the left
//                 navigational elements
//content_block() - the main content for any
//                  page's specific data.
//
//footer_block() - which contains any
//                 footer information that
//                 remains the same on all
//                 pages.

//The nice thing about this approach is,
//on each page of your application,
//you only have to override the methods
//for the content blocks that are different
//or specific to that page.  The other content
//blocks and layout is automatically built
//from the parent class.

//most of the time your page will only
//override the content_block() method, which
//is the right block content that changes
//from page to page.

//This is exactly how this website is built.

//enable the automatic detection of debugging
define("DEBUG", TRUE);

/**
 * This shows how to do a simple layout child
 * class of HTMLPage
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage examples
 * @version 3.0.0
 */
class MyLayoutPage extends HTMLPage {


    /**
     * This is the constructor.
     *
     * @param string - $title - the title for the page and the
     *                 titlebar object.
     * @param - string - The render type (HTML, XHTML, etc. )
     *
     */
    function __construct($title, $render_type = phphtmllib::HTML) {

        parent::__construct( $title, $render_type );

        //add some css links
        //assuming that phphtmllib is installed in the doc root
        $this->add_css_link("/phphtmllib/examples/css/main.css");
        $this->add_css_link("/phphtmllib/css/fonts.css");
        $this->add_css_link("/phphtmllib/css/colors.css");

        //add the phphtmllib widget css
        $this->add_css_link( "/phphtmllib/css/bluetheme.php" );
    }

    /**
     * The parent class' head_content is defined
     * as abstract, so we need to define it here
     * and return NULL if we don't want to add
     * anything to the head.
     *
     * @return NULL
     */
    protected function head_content() {
        return NULL;
    }

    /**
     * We don't need to do any permissions checking,
     * so we'll return TRUE.  We have to define this method
     * because the parent class defined it as abstract.
     *
     * @return TRUE
     */
    protected function permission() {
        return TRUE;
    }

    /**
     * This builds the main content for the
     * page.
     *
     */
    protected function body_content() {

        //add the header area
        $this->add( HTMLDocument::comment( "HEADER BLOCK BEGIN") );
        $this->add( $this->header_block() );
        $this->add( HTMLDocument::comment( "HEADER BLOCK END") );

        //add it to the page
        //build the outer wrapper div
        //that everything will live under
        $wrapper_div = html_div();
        $wrapper_div->set_id( "phphtmllib" );

        //add the main body
        $wrapper_div->add( HTMLDocument::comment( "MAIN BLOCK BEGIN") );
        $wrapper_div->add( $this->main_block() );
        $wrapper_div->add( HTMLDocument::comment( "MAIN BLOCK END") );

        $this->add( $wrapper_div );

        //add the footer area.
        $this->add( HTMLDocument::comment( "FOOTER BLOCK BEGIN") );
        $this->add( $this->footer_block() );
        $this->add( HTMLDocument::comment( "FOOTER BLOCK END") );

    }


    /**
     * This function is responsible for building
     * the header block that lives at the top
     * of every page.
     *
     * @return HTMLtag object.
     */
    protected function header_block() {
        $header = DIVtag::factory("pageheader");

        $header->add( "HEADER BLOCK AREA" );
        return $header;
    }


    /**
     * We override this method to automatically
     * break up the main block into a
     * left block and a right block
     *
     * @param TABLEtag object.
     */
    protected function main_block() {

        $main = DIVtag::factory();
        $main->set_id("maincontent");

        $table = TABLEtag::factory("100%",0);
        $left_div = DIVtag::factory("leftblock", $this->left_block() );

        $table->add_row( TDtag::factory("leftblock", "", $left_div ),
                         TDtag::factory("divider", "", "&nbsp;"),
                         TDtag::factory("rightblock", "", $this->content_block() ));
        $main->add( $table );

        return $main;
    }


    /**
     * this function returns the contents
     * of the left block.  It is already wrapped
     * in a TD
     *
     * @return HTMLTag object
     */
    protected function left_block() {
        $div = DIVtag::factory();
        $div->set_style("padding-left: 6px;");

        $div->add( "LEFT BLOCK" );
        return $div;
    }



    /**
     * this function returns the contents
     * of the right block.  It is already wrapped
     * in a TD
     *
     * @return Container object
     */
    protected function content_block() {
        return Container::factory( "CONTENT BLOCK", BRtag::factory(2),
                                   Atag::factory($_SERVER["PHP_SELF"]."?debug=1",
                                                 "Show Debug source"),
                                   BRtag::factory(10));
    }


    /**
     * This function is responsible for building
     * the footer block for every page.
     *
     * @return HTMLtag object.
     */
    protected function footer_block() {

        $footer_div = DIVtag::factory();
        $footer_div->set_tag_attribute("id", "footerblock");
        $footer_div->add("FOOTER BLOCK");

        return $footer_div;
    }
}


$page = new MyLayoutPage("phpHtmlLib Example 3 - PageWidget child");


//this will render the entire page
print $page->render();
?>
