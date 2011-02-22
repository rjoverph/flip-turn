<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * Swimmer Update
 *
 * $Id$
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip Turn
 * @subpackage Swimmer
 *
 */ 

// Setup the Flip-Turn application
include('ft-setup.php') ;

//  Include the page layout
include_once("page.class.php") ;
include_once("swimmers.forms.class.php") ;

/**
 * Build a page with the SDIF Queue Purge form
 * and associated form processing.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage Swimmer
 *
 */
class SwimmerUpdatePage extends FlipTurnLayoutPage
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

	    //  Create the form
        //$form = new SwimmerUpdateForm("Update Swimmer", $_SERVER['PHP_SELF'], 600) ;
        $form = new SwimmerUpdateForm("Update Swimmer", null, 600) ;
        $form->setSwimmerId($swimmerid) ;

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
            $swimmers = new SwimmersDataList("Swimmers", '100%', "swimmerid") ;
            $div = html_div() ;
            $div->set_id("swimmersgdl") ;
            $div->add($swimmers) ;
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
$page = new SwimmerUpdatePage("Swimmer Update") ;
print $page->render() ;
?>
