<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * Swim Teams
 *
 * $Id$
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage SwimTeams
 *
 */ 

// * Include the phphtmllib libraries
include("includes.inc") ;

//  Include the page layout
include_once("page.class.php") ;
include_once("swimteams.class.php") ;

/**
 * Present the data in the SDIF Queue in a
 * GUI Data List.  From the GDL the user can
 * execute a number of processing actions.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage SwimTeams
 *
 */
class SwimTeamsPage extends FlipTurnLayoutPage
{
    function content_block()
    {
        //  Add the InfoTableCSS so the tables look right
	    $this->add_head_css(new DefaultGUIDataListCSS) ;
	    
        $container = container() ;

        $swimteams = new SwimTeamsDataList("Swim Teams", 800, "swimteamid") ;
        $div = html_div() ;
        $div->set_id("swimteamsgdl") ;
        $div->add($swimteams) ;
        $container->add($div) ;

	    return $container ;
    }
}

//  Create the page and render it.
$page = new SwimTeamsPage("Swim Teams") ;
print $page->render() ;
?>
