<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * SDIF Queue Purge
 *
 * $Id$
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip Turn
 * @subpackage SDIF-Queue
 *
 */ 

// * Include the phphtmllib libraries
include("includes.inc") ;

//  Include the page layout
include_once("page.class.php") ;
include_once("sdif.forms.class.php") ;

/**
 * Build a page with the SDIF Queue Purge form
 * and associated form processing.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage SDIF-Queue 
 *
 */
class SDIFQueuePurgePage extends FlipTurnLayoutPage
{
    function content_block()
    {
        //  Build the FormProcessor, and add the
        //  form content object that the FormProcessor 
        //  will use.
        //
	    $container = container() ;

	    //  Create the form
        $form = new ResultsQueuePurgeForm("Purge Results Queue", $_SERVER['PHP_SELF'], 600) ;

	    //  Create the form processor
        $fp = new FormProcessor($form) ;

	    //  Don't display the form again if processing was successful.

	    $fp->set_render_form_after_success(false) ;

	    //  Add the Form Processor to the container.

	    //  If the Form Processor was succesful, display
	    //  some statistics about the uploaded file.

	    if ($fp->is_action_successful())
	    {
	        //$container->add($form->get_action_message()) ;

	        //  Add the Form Processor to the container.

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
$page = new SDIFQueuePurgePage("SDIF Queue Purge") ;
print $page->render() ;
?>
