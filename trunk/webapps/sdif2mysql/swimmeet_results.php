<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * Swim Meets
 *
 * $Id$
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage SwimMeets
 *
 */ 

// Setup the Flip-Turn application
include('ft-setup.php') ;

//  Include the page layout
include_once("page.class.php") ;
include_once("swimmeets.class.php") ;
include_once("results.class.php") ;

/**
 * Present the data in the SDIF Queue in a
 * GUI Data List.  From the GDL the user can
 * execute a number of processing actions.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage SwimMeets
 *
 */
class SwimMeetsPage extends FlipTurnLayoutPage
{
    function content_block()
    {
        //  Add the InfoTableCSS so the tables look right
	    $this->add_head_css(new DefaultGUIDataListCSS) ;

        //  This allows passing arguments eithers as a GET or a POST

        $scriptargs = array_merge($_GET, $_POST) ;

        //  The swimmeetid is the argument which must be
        //  dealt with differently for GET and POST operations

        if (array_key_exists("swimmeetid", $scriptargs))
            $swimmeetid = $scriptargs["swimmeetid"] ;
        else if (array_key_exists("_swimmeetid", $scriptargs))
            $swimmeetid = $scriptargs["_swimmeetid"] ;
        else if (array_key_exists(FT_DB_PREFIX . "radio", $scriptargs))
            $swimmeetid = $scriptargs[FT_DB_PREFIX . "radio"][0] ;
        else
            $swimmeetid = null ;
	    
        $container = container() ;

        $it = new SwimMeetInfoTable('Swim Meet Details', '500') ;
        $it->setSwimMeetId($swimmeetid) ;
        $it->BuildInfoTable(false) ;

        $container->add($it, html_br(2)) ;

        //  Complex order by clause to make sure DQ and NS are shown
        //  after valid times.
        $swimresults = new SwimResultsDataList('Results', '100%', 'event_number,
            case when finals_time_ft = 0.0 then 1 else 0 end,
            finals_time_ft') ;
        $swimresults->set_save_vars(array('swimmeetid' => $swimmeetid)) ;
        $div = html_div() ;
        $div->set_id("swimresultsgdl") ;
        $div->add($swimresults) ;
        $container->add($div) ;

        $container->add(FlipTurnGUIButtons::getBackHomeButtons()) ;

	    return $container ;
    }
}

//  Create the page and render it.
$page = new SwimMeetsPage("Swim Meets") ;
print $page->render() ;
?>
