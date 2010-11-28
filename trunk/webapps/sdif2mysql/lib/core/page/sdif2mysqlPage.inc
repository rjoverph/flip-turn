<?php

/**
 * $Id: phphtmllibPage.inc,v 1.8 2005/04/13 19:18:54 waboring Exp $
 *
 * @package sdif2mysql
 */


class sdif2mysqlPage extends AjaxablePage implements Cacheable {

    /**
     * Defines HTML ID for the body
     * div of the page
     *
     */
    const ID_BODY = AjaxablePage::AJAX_ID;

    /**
     * Defines HTML ID for the menu
     * area div
     *
     */
    const ID_MENU = 'idMenu';

    /**
     * Defines HTML ID for the message
     * notification area div
     *
     */
    const ID_MESSAGE = 'idMessage';


    /**
     * where the main content goes
     */
    const ID_CONTENT = 'idMiddleContent';

    /**
     * Where the nav blocks go
     */
    const ID_NAV = 'leftBlock';

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

        //add some meta tags
        $this->add_head_content( html_meta("html, xml, xhtml, php, phphtmllib, open source".
                                           ",LGPL, GPL",
                                           "","keywords"));
    }



    /**
     * This function should return an array
     * of request variable names and their
     * properties in the following format:
     * array('key_name' => type)
     *
     * This function is called by the Controller
     * in order to pass it to the Request object
     *
     * @return array
     */
    public function request_vars() {
        return array();
    }

    /**
     * This method is called when we only want to
     * build the content for an ajax request.
     * Instead of building the entire page layout,
     * just build the 'main content' block that will
     * be replaced on the current page.
     *
     * @return string
     */
    protected function render_ajax_content() {
        return $this->content_block()->render();
    }

    /**
     * This is meant to be extended by the child class
     * to do any generic permissions checking for access
     * to the content that the child builds
     *
     * @return boolean - TRUE = has permissions to build
     *                          and view content.
     */
    protected function permission() {
        return true;
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
        $this->add_css_link("/css/main.css");
        $this->add_css_link("/css/fonts.css");

        $this->add_js_link( '/js/scriptaculous-js-1.7.0/lib/prototype.js' );
        $this->add_js_link( '/js/scriptaculous-js-1.7.0/src/scriptaculous.js' );
        $this->add_js_link( '/js/ajax.js' );
    }

    /**
     * This function is responsible for building
     * the header block that lives at the top
     * of every page.
     *
     * @return HTMLtag object.
     */
    protected function header_block() {
        $header = DIVtag::factory();
        $header->set_class("pageheader");

		$header->add( "HEADER BLOCK AREA sdif2mysql" );
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

		$main = new DIVtag();
		$main->set_id("maincontent");

		$table = TABLEtag::factory("100%", 0);
		$left_div = DIVtag::factory("", $this->left_block() );

		$table->add_row( TDtag::factory("leftblock", "", $left_div ),
						 TDtag::factory("divider", "", "&nbsp;"),
						 TDtag::factory("rightblock", "", $this->content_block() ));
        $main->add( $table );

		return $main;
    }

    /**
     * This builds the main content for the
     * page.
     *
     */
    function body_content() {

        //add the header area
        $this->add( html_comment( "HEADER BLOCK BEGIN") );
        $this->add( $this->header_block() );
        $this->add( html_comment( "HEADER BLOCK END") );

        //add the main body
        $this->add( html_comment( "MAIN BODY BLOCK BEGIN") );
        $this->add( $this->main_block() );
        $this->add( html_comment( "MAIN BODY BLOCK END") );

        //add the footer area.
        $this->add( html_comment( "FOOTER BLOCK BEGIN") );
        $this->add( $this->footer_block() );
        $this->add( html_comment( "FOOTER BLOCK END") );

    }

    /**
     * this function returns the contents
     * of the left block.  It is already wrapped
     * in a TD
     *
     * @return HTMLTag object
     */
    protected function left_block() {
        $td = TDtag::factory();
        $td->set_style("padding: 20px;");

		$td->add( "LEFT BLOCK" );
        return $td;
    }

    /**
     * this function returns the contents
     * of the right block.  It is already wrapped
     * in a TD
     *
     * @return HTMLTag object
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

		$footer_div = new DIVtag();
		$footer_div->set_tag_attribute("id", "footerblock");
		$footer_div->add("FOOTER BLOCK for sdif2mysql");

        return $footer_div;
    }


    /***********************/
    /* Cacheable Interface */
    /***********************/

    public function get_cache_key() {
        return get_class($this);
    }

    public function get_cache_lifetime() {
        return 60;
    }

    /**
     * Enable caching of this page
     * by default
     */
    public function is_cacheable() {
        return TRUE;
    }
}

?>
