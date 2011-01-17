<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * Swim Meets
 *
 * $Id$
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage Results
 *
 */ 

// Setup the Flip-Turn application
include('ft-setup.php') ;

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
 * @subpackage Results
 *
 */
class SwimResultsPage extends FlipTurnLayoutPermissionsPage
{
    function content_block()
    {
        //  Add the InfoTableCSS so the tables look right
	    $this->add_head_css(new DefaultGUIDataListCSS) ;
	    
        $container = container() ;

        $results = new SwimResultsAdminDataList("Swim Results", '100%', "resultid") ;
        $div = html_div() ;
        $div->set_id("resultsgdl") ;
        $div->add($results) ;
        $container->add($div) ;

	    return $container ;
    }
}

//  Create the page and render it.
$page = new SwimResultsPage("Swim Results") ;
print $page->render() ;
?>
