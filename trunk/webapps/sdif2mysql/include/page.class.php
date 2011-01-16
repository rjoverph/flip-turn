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

require_once('ft-config.php') ;
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
     * User is logged in?
     *
     * @return boolean status of user login
     */
    function user_is_logged_in()
    {
        if (session_id() == "") session_start() ;

        if (!isset($_SESSION[FT_LOGIN_STATUS]))
            $_SESSION[FT_LOGIN_STATUS] = false ;

        return $_SESSION[FT_LOGIN_STATUS] ;
    }

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
        $header = html_div('pageheader');
		$header->add(html_comment('HEADER BLOCK AREA')) ;
        $logo = html_a('/', html_img('/images/OnYourMarksWhite_080x066.png'), null, null, 'Home') ;
        $logo->set_style('headerimage') ;

        $header->add($logo,
            html_h2(FT_PAGE_HEADER), html_h4(FT_PAGE_SUBHEADER)) ;

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

		$table->add_row(html_td('leftblock', '', $left_div),
            html_td('divider', '', '&nbsp;'), html_td('rightblock',
            '', $this->status_bar(), html_br(), html_div(null, $this->content_block())));
        $main->add( $table );

		return $main;
    }

    /**
     * Status Bar
     *
     * @return container
     */
    function status_bar()
    {
        $c = container() ;
        $c->add(html_div('statusbar', $this->DateMessage(), $this->LoginMessage())) ;

        return $c ;
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

		$navtable = new VerticalCSSNavTable('Browse Results', '', '90%') ;
		
   		//  End User actions
		$navtable->add('/', 'Home', 'Flip-Turn Home') ;
		//$navtable->add("admin.php", $this->user_is_logged_in() ? 'Logout' : 'Login') ;
        //$navtable->add_text(_HTML_SPACE) ;
		$navtable->add("results_by_event.php", "By Event", "By Event") ;
		$navtable->add("results_by_swimmeet.php", "By Swim Meet", "By Swim Meet") ;
		$navtable->add("results_by_swimmer.php", "By Swimmer", "By Swimmer") ;

		$div->add( $navtable, html_br());

        if ($this->user_is_logged_in())
        {
   		    //  Administrative actions
		    $navtable = new VerticalCSSNavTable("Administration", "", "90%") ;
		
		    $navtable->add("swimteams.php", "Swim Teams", "Swim Teams") ;
		    $navtable->add("swimmeets.php", "Swim Meets", "Swim Meets") ;
		    $navtable->add("queue.php", "Results Queue", "Results Queue") ;
		    $navtable->add("queue_upload.php", "Upload Results", "Upload Results") ;

		    $div->add( $navtable, html_br());
        }

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
        $container = container("CONTENT BLOCK",
            html_br(2), html_a($_SERVER["PHP_SELF"]."?debug=1", 
		   "Show Debug source"), html_br(10));
		return $container ;
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
        $f->set_company_name("Flip-Turn.com");
        $f->set_webmaster_email("admin@flip-turn.com");
        $f->set_legalnotice_url("legal.php");
        $f->set_privacypolicy_url("privacy.php");
        
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

    /*
     * This function returns a container with the appropriate "Date"
     * message derived from the current date.
     *
     * @return HTMLTag object
     */

    function DateMessage()
    {
        $dm = html_div() ;
        $dm->set_id("DateMessage") ;
        $dm->set_style("float: right;") ;

        $dm->add(date("l, F jS, Y", time())) ;

        return $dm ;
    }
    /*
     * This function returns a container with the appropriate
     * "Login" or "Logout" message derived from the current status.
     *
     * @return HTMLTag object
     */

    function LoginMessage()
    {
        $lm = html_div() ;
        $lm->set_id("LoginMessage") ;
        $lm->set_style("float: left;") ;

        $welcome = sprintf('Welcome %s - ', $this->user_is_logged_in() ? 'Admin' : 'Guest') ;

        $lm->add($welcome, html_a('admin.php', $this->user_is_logged_in() ? 'Logout' : 'Login')) ;

        return $lm ;
    }
}

/**
 * This is Flip-Turn Child of the PageWidget
 * class that is used for the base page layout
 * throughout the Flip-Turn web application.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnLayoutPage
 *
 */
class FlipTurnLayoutPermissionsPage extends FlipTurnLayoutPage
{
	/**
	 * This is the constructor.
	 *
	 * @param string - $title - the title for the page and the
	 *                 titlebar object.
	 * @param - string - The render type (HTML, XHTML, etc. )	 
     *
	 */
    function FlipTurnLayoutPermissionsPage($title, $render_type = HTML)
    {
        //  Turn on the ability to do a permissions check
        $this->allow_permissions_checks(true) ;
 
        parent::FlipTurnLayoutPage($title, $render_type) ;
    }

    /**
     * This method is called during constructor time to check
     * to make sure the page is allowed to build and render
     * any content.
     * 
     * @return boolean FALSE = not allowed.
     */
    function permission()
    {
        if (session_id() == "") session_start() ;

        $ok = isset($_SESSION[FT_LOGIN_STATUS]) && $_SESSION[FT_LOGIN_STATUS] ;

        //  Is Admin logged in?

        if (!$ok)
        {
            //ok we 'failed'.  Lets set the specialized error message
            $this->set_permissions_message("You do not have permission to view this page.") ;

            return false ;
        }

        return true ;
    }
}
?>
