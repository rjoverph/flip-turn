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

// * Include the phphtmllib libraries
include("includes.inc") ;

//  Include the page layout
include_once("page.class.php") ;
include_once("swimmeets.class.php") ;

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
class SwimMeetsPage extends FlipTurnLayoutPermissionsPage
{
    function content_block()
    {
        //  Add the InfoTableCSS so the tables look right
	    $this->add_head_css(new DefaultGUIDataListCSS) ;
	    
        $container = container() ;

        $swimmeets = new SwimMeetsAdminDataList("Swim Meets", 800, "swimmeetid") ;
        $div = html_div() ;
        $div->set_id("swimmeetsgdl") ;
        $div->add($swimmeets) ;
        $container->add($div) ;

	    return $container ;
    }
}

//  Create the page and render it.
$page = new SwimMeetsPage("Swim Meets") ;
print $page->render() ;
?>
