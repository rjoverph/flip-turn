<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This is the base PageWidget child class for all pages.
 *
 *
 * $Id$
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage PageLayout
 * @version 1.0.0
 *
 */

include_once('ft.include.php') ;

/**
 * This is Flip-Turn Child of the PageWidget
 * class that is used for the base page layout
 * throughout the Flip-Turn web application.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see PageWidget
 *
 */
class FlipTurnLayoutPage extends PageWidget
{
	/**
	 * This is the constructor.
	 *
	 * @param string - $title - the title for the page and the
	 *                 titlebar object.
	 * @param - string - The render type (HTML, XHTML, etc. )	 
     *
	 */
    function FlipTurnLayoutPage($title, $render_type = HTML)
    {
        $this->PageWidget("Flip-Turn :: " . $title, $render_type) ;

		//add some css links
		//assuming that phphtmllib is installed in the doc root
		$this->add_css_link("/css/main.css") ;
		$this->add_css_link("/css/flip-turn.css") ;
		//$this->add_css_link(PHPHTMLLIB_RELPATH . "/examples/css/main.css");
		$this->add_css_link(PHPHTMLLIB_RELPATH . "/css/fonts.css") ;
		$this->add_css_link(PHPHTMLLIB_RELPATH . "/css/colors.css") ;
		
		//add the phphtmllib widget css
		$this->add_css_link(PHPHTMLLIB_RELPATH . "/css/bluetheme.php" ) ;
    }

	/**
	 * This builds the main content for the
	 * page.
	 *
	 */
    function body_content()
    {		
		//add the header area
		$this->add( html_comment( "HEADER BLOCK BEGIN") );
		$this->add( $this->header_block() );
		$this->add( html_comment( "HEADER BLOCK END") );		

		//add it to the page
		//build the outer wrapper div
		//that everything will live under
		$wrapper_div = html_div();
		$wrapper_div->set_id( "phphtmllib" );

		//add the main body
		$wrapper_div->add( html_comment( "MAIN BLOCK BEGIN") );
		$wrapper_div->add( $this->main_block() );
		$wrapper_div->add( html_comment( "MAIN BLOCK END") );

		$this->add( $wrapper_div );

		//add the footer area.
		$this->add( html_comment( "FOOTER BLOCK BEGIN") );
		$this->add( $this->footer_block() );
		$this->add( html_comment( "FOOTER BLOCK END") );        
		
	}


    /**
     * This function is responsible for building
     * the header block that lives at the top
     * of every page.
     *
     * @return HTMLtag object.
     */
    function header_block()
    {
        $header = html_div("pageheader");

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
    function main_block()
    {
		$main = html_div();
		$main->set_id("maincontent");

		$table = html_table("100%",0);
		$left_div = html_div("leftblock", $this->left_block() );		

		$table->add_row( html_td("leftblock", "", $left_div ),
						 html_td("divider", "", "&nbsp;"),
						 html_td("rightblock", "", $this->content_block() ));
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
    function left_block()
    {
		$div = html_div();
		$div->set_style("padding-left: 6px;");

		$navtable = new VerticalCSSNavTable("Results", "", "90%") ;
		
   		//  End User actions
		$navtable->add("/", "Home", "Flip-Turn Home") ;
		$navtable->add("results_by_event.php", "By Event", "By Event") ;
		$navtable->add("results_by_meet.php", "By Swim Meet", "By Swim Meet") ;
		$navtable->add("results_by_swimmer.php", "By Swimmer", "By Swimmer") ;

		$div->add( $navtable, html_br());

   		//  Administrative actions
		$navtable = new VerticalCSSNavTable("Administration", "", "90%") ;
		
		$navtable->add("swimmeets.php", "Swim Meets", "Swim Meets") ;
		$navtable->add("queue.php", "SDIF Queue", "SDIF Processing Queue") ;
		$navtable->add("upload.php", "Upload SDIF", "Upload SDIF File") ;

		$div->add( $navtable, html_br());

     return $div;
    }



    /**
     * this function returns the contents
     * of the right block.  It is already wrapped
     * in a TD
     *
     * @return HTMLTag object
     */
    function content_block()
    {
		$container = container( "CONTENT BLOCK", html_br(2),
								html_a($_SERVER["PHP_SELF"]."?debug=1", 
									   "Show Debug source"),
								html_br(10));
		return $container;
    }


    /**
     * This function is responsible for building
     * the footer block for every page.
     *
     * @return HTMLtag object.
     */
    function footer_block()
    {
        $f = new FooterNav("Flip-Turn.com") ;
        $f->set_date_string(date("Y")) ;
        $f->add("index.php", "Home") ;
        $f->add("about.php", "About") ;
        $f->add("legal.php", "Legal") ;

        return $f ;
    }

    /**
     * Error Message
     *
     * @param string error
     * @return mixed container
     */
    function error_message($msg)
    {
        $c = container() ;
        $c->add(html_div("fterrormsg", $msg)) ;

        return $c ;
    }
}
?>
