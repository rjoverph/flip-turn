<?php
/**
 * This is the example HTMLPage child
 * for the examples pages.
 *
 *
 * $Id: MyLayoutPage.inc 2780 2007-05-18 17:44:45Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage examples
 * @version 2.0.0
 *
 */

/**
 * This is an example Child of the PageWidget
 * class to show how to build a simple application
 * or system wide layout simple to manage and
 * maintain
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage examples
 * @version 2.0.0
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
		$this->add_css_link("/examples/css/main.css");
		$this->add_css_link("/css/fonts.css");
		$this->add_css_link("/css/colors.css");

		//add the phphtmllib widget css
		$this->add_css_link( "/css/widgets.php" );
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
		$wrapper_div = new DIVtag();
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
        $header = DIVtag::factory();
        $header->set_class("pageheader");

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

		$main = new DIVtag();
		$main->set_id("maincontent");

		$table = TABLEtag::factory("100%", 0);
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
		$td = TDtag::factory();
		$td->set_style("padding-left: 6px;");

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
		$footer_div->add("FOOTER BLOCK");

        return $footer_div;
    }
}

?>
