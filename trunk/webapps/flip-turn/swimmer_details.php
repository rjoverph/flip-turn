<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * Swimmers
 *
 * $Id$
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage Swimmers
 *
 */ 

// Setup the Flip-Turn application
include('ft-setup.php') ;

//  Include the page layout
include_once("page.class.php") ;
include_once("swimmers.class.php") ;

/**
 * Present the data in the SDIF Queue in a
 * GUI Data List.  From the GDL the user can
 * execute a number of processing actions.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage Swimmers
 *
 */
class SwimmersPage extends FlipTurnLayoutPage
{
    function content_block()
    {
        //  Add the InfoTableCSS so the tables look right
	    $this->add_head_css(new DefaultGUIDataListCSS) ;

        //  This allows passing arguments eithers as a GET or a POST

        $scriptargs = array_merge($_GET, $_POST) ;

        //  The swimmerid is the argument which must be
        //  dealt with differently for GET and POST operations

        if (array_key_exists("swimmerid", $scriptargs))
            $swimmerid = $scriptargs["swimmerid"] ;
        else if (array_key_exists("_swimmerid", $scriptargs))
            $swimmerid = $scriptargs["_swimmerid"] ;
        else if (array_key_exists(FT_DB_PREFIX . "radio", $scriptargs))
            $swimmerid = $scriptargs[FT_DB_PREFIX . "radio"][0] ;
        else
            $swimmerid = null ;
	    
        $container = container() ;

        $it = new SwimmerInfoTable("Swimmer Details") ;
        $it->setSwimmerId($swimmerid) ;
        $it->BuildInfoTable() ;

        $container->add($it) ;
        $container->add(FlipTurnGUIButtons::getBackHomeButtons()) ;
        

	    return $container ;
    }
}

//  Create the page and render it.
$page = new SwimmersPage("Swimmers") ;
print $page->render() ;
?>
