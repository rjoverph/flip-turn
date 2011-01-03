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

        //  This allows passing arguments eithers as a GET or a POST

        $scriptargs = array_merge($_GET, $_POST) ;

        //  The swimteamid is the argument which must be
        //  dealt with differently for GET and POST operations

        if (array_key_exists("swimteamid", $scriptargs))
            $swimteamid = $scriptargs["swimteamid"] ;
        else if (array_key_exists("_swimteamid", $scriptargs))
            $swimteamid = $scriptargs["_swimteamid"] ;
        else if (array_key_exists(FT_DB_PREFIX . "radio", $scriptargs))
            $swimteamid = $scriptargs[FT_DB_PREFIX . "radio"][0] ;
        else
            $swimteamid = null ;
	    
        $container = container() ;

        $it = new SwimTeamInfoTable("Swim Team Details") ;
        $it->setSwimTeamId($swimteamid) ;
        $it->BuildInfoTable() ;

        $container->add($it) ;
        $container->add(FlipTurnGUIButtons::getBackHomeButtons()) ;
        

	    return $container ;
    }
}

//  Create the page and render it.
$page = new SwimTeamsPage("Swim Teams") ;
print $page->render() ;
?>
