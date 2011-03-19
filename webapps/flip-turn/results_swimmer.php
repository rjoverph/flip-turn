<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * Swim Meets
 *
 * $Id$
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage SwimmerResults
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
 * @subpackage SwimmerResults
 *
 */
class SwimmerResultsPage extends FlipTurnLayoutPage
{
    function content_block()
    {
        //  Add the InfoTableCSS so the tables look right
	    $this->add_head_css(new DefaultGUIDataListCSS) ;

        //  This allows passing arguments eithers as a GET or a POST

        $scriptargs = array_merge($_GET, $_POST) ;

        //  The ussid is the argument which must be
        //  dealt with differently for GET and POST operations

        if (array_key_exists("ussid", $scriptargs))
            $ussid = $scriptargs["ussid"] ;
        else if (array_key_exists("_ussid", $scriptargs))
            $ussid = $scriptargs["_ussid"] ;
        else if (array_key_exists(FT_DB_PREFIX . "radio", $scriptargs))
            $ussid = $scriptargs[FT_DB_PREFIX . "radio"][0] ;
        else
            $ussid = null ;
	    
        //  Need better error handling but for now just die!
        if (is_null($ussid))
            die('Bad USS Id:  ' . basename(__FILE__) . '::' . __LINE__) ;

        $container = container() ;

        //$container->add($ussid) ;

        //$it = new SwimmerResultInfoTable('Swim Meet Details', '500') ;
        //$it->setSwimmerResultId($ussid) ;
        //$it->BuildInfoTable(false) ;

        //$container->add($it, html_br(2)) ;

        //  Complex order by clause to make sure DQ and NS are shown
        //  after valid times.
        $swimresults = new SwimResultsDataList('Results', '100%', 'event_number,
            case when finals_time_ft = 0.0 then 1 else 0 end, finals_time_ft',
            null, null, null, sprintf('uss_new="%s"', $ussid)) ;
        $swimresults->set_save_vars(array('ussid' => $ussid)) ;
        $div = html_div() ;
        $div->set_id("swimresultsgdl") ;
        $div->add($swimresults) ;
        $container->add($div) ;

        $container->add(FlipTurnGUIButtons::getBackHomeButtons()) ;

	    return $container ;
    }
}

//  Create the page and render it.
$page = new SwimmerResultsPage("Swimmer Results") ;
print $page->render() ;
?>
