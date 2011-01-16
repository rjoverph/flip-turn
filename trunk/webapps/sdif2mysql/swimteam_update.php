<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * Swim Team Update
 *
 * $Id$
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip Turn
 * @subpackage Swim Team
 *
 */ 

// * Include the phphtmllib libraries
include("includes.inc") ;

//  Include the page layout
include_once("page.class.php") ;
include_once("swimteams.forms.class.php") ;

/**
 * Build a page with the SDIF Queue Purge form
 * and associated form processing.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage Swim Team
 *
 */
class SwimTeamUpdatePage extends FlipTurnLayoutPage
{
    function content_block()
    {
        //  Build the FormProcessor, and add the
        //  form content object that the FormProcessor 
        //  will use.
        //
	    $container = container() ;
        
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

	    //  Create the form
        //$form = new SwimTeamUpdateForm("Update Swim Team", $_SERVER['PHP_SELF'], 600) ;
        $form = new SwimTeamUpdateForm("Update Swim Team", null, 600) ;
        $form->setSwimTeamId($swimteamid) ;

	    //  Create the form processor
        $fp = new FormProcessor($form) ;

	    //  Don't display the form again if processing was successful.

	    $fp->set_render_form_after_success(false) ;

	    //  Update the Form Processor to the container.

	    //  If the Form Processor was succesful, display
	    //  some statistics about the uploaded file.

	    if ($fp->is_action_successful())
	    {
            //  Add the InfoTableCSS so the tables look right
            $this->add_head_css(new DefaultGUIDataListCSS) ;
            $swimteams = new SwimTeamsDataList("Swim Teams", '100%', "swimteamid") ;
            $div = html_div() ;
            $div->set_id("swimteamsgdl") ;
            $div->add($swimteams) ;
            $container->add($div) ;

	        //  Update the Form Processor to the container.

	        $container->add(html_br(2), $fp) ;
	    }
        else
        {
	        $container->add($fp) ;
        }


	    return $container ;
    }
}

//  Create the page and render it.
$page = new SwimTeamUpdatePage("Swim Team Update") ;
print $page->render() ;
?>
