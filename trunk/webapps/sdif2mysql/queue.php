<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * SDIF (.sd3) Queue Processing
 *
 * $Id$
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip Turn
 * @subpackage Queue
 *
 */ 

// * Include the phphtmllib libraries
include("includes.inc") ;

//  Include the page layout
include_once("page.class.php") ;
include_once("queue.class.php") ;

/**
 * Present the data in the SDIF Queue in a
 * GUI Data List.  From the GDL the user can
 * execute a number of processing actions.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage SDIF-Queue 
 *
 */
class SDIFQueuePage extends FlipTurnLayoutPage
{
    function content_block()
    {
        //  Add the InfoTableCSS so the tables look right
	    $this->add_head_css(new DefaultGUIDataListCSS) ;
	    
        $container = container() ;

        $sdifqueue = new SDIFQueueDataList("SDIF Queue", 800, "sdifrecordid") ;
        $div = html_div() ;
        $div->set_id("sdifqueuegdl") ;
        $div->add($sdifqueue) ;
        $container->add($div) ;

	    return $container ;
    }
}

//  Create the page and render it.
$page = new SDIFQueuePage("SDIF Queue") ;
print $page->render() ;
?>
