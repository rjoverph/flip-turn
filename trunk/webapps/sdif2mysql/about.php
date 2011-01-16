<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * About Page
 *
 * $Id$
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip Turn
 * @subpackage About
 *
 */ 

// Application setup
include("ft-setup.php") ;
include("page.class.php") ;

/**
 * About stuff
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnLayoutPage
 *
 */
class FlipTurnAboutPage extends FlipTurnLayoutPage
{
    function content_block()
    {
        $sdif_spec_doc = 'http://www.usaswimming.org/_Rainbow/Documents/521e8fae-ce81-4c73-a51a-3653a1304a30/Standard%20Data%20Interchange%20Format.doc' ;
        $sdif_spec_url = 'http://www.usaswimming.org/DesktopDefault.aspx?TabId=1792&Alias=Rainbow&Lang=en-US' ;

	    $container = container() ;

        $container->add(html_h3("Overview")) ;
        $container->add(html_p('Flip-Turn is a web based application which allows
            swim teams and/or associations to upload swim results in SDIF format
            and store them in a database.  The results can then viewed intelligently
            (by swim meet, by swimmer, by event, etc.).  SDIF (Swim Data Interchange
            Format) is a USA Swimming standard data format for sharing swim data between
            teams and applications.  While somewhat dated, it remains the defacto standard
            for sharing swim data.  You can find information about SDIF on the',
            html_a($sdif_spec_url, 'USA Swimming web site'), 'where you can also find
            the', html_a($sdif_spec_doc, 'Original Specification'), 'as a Word document.')) ;

        $container->add(html_h3("Requirements")) ;
        $container->add(html_p('Flip-Turn requires the following to successfully
            install and run correctly.')) ;
        $ul = html_ul() ;
        $ul->add(html_li('PHP 5.2 or later.  Flip-Turn has been developed against
            PHP 5.2.14.  PHP 4.x will not work.')) ;
        $ul->add(html_li('MySQL 5.0 or later.  Flip-Turn has been developed and
            tested against MySQL 5.1.46.')) ;
        $container->add($ul) ;

	    return $container ;
    }
}


$page = new FlipTurnAboutPage("About") ;

print $page->render() ;
?>
