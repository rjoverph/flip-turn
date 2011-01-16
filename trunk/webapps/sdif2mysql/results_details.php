<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * Swim Meets
 *
 * $Id$
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage SwimResultsDetails
 *
 */ 

// * Include the phphtmllib libraries
include("includes.inc") ;

//  Include the page layout
include_once("page.class.php") ;
include_once("results.class.php") ;

/**
 * Present the data in the SDIF Queue in a
 * GUI Data List.  From the GDL the user can
 * execute a number of processing actions.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage SwimResultsDetails
 *
 */
class SwimResultsDetailsPage extends FlipTurnLayoutPage
{
    function content_block()
    {
        //  Add the InfoTableCSS so the tables look right
	    $this->add_head_css(new DefaultGUIDataListCSS) ;

        //  This allows passing arguments eithers as a GET or a POST

        $scriptargs = array_merge($_GET, $_POST) ;

        //  The resultsid is the argument which must be
        //  dealt with differently for GET and POST operations

        if (array_key_exists("resultsid", $scriptargs))
            $resultsid = $scriptargs["resultsid"] ;
        else if (array_key_exists("_resultsid", $scriptargs))
            $resultsid = $scriptargs["_resultsid"] ;
        else if (array_key_exists(FT_DB_PREFIX . "radio", $scriptargs))
            $resultsid = $scriptargs[FT_DB_PREFIX . "radio"][0] ;
        else
            $resultsid = null ;
	    
        $container = container() ;

        $it = new SwimResultsInfoTable("Swim Results Details") ;
        $it->setResultId($resultsid) ;
        $it->BuildInfoTable() ;

        $container->add($it) ;
        $container->add(FlipTurnGUIButtons::getBackHomeButtons()) ;

	    return $container ;
    }
}

//  Create the page and render it.
$page = new SwimResultsDetailsPage("Swim Results Details") ;
print $page->render() ;
?>
