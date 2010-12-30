<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * SDIF Queue Process
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
include_once("sdif.class.php") ;
include_once("sdif.forms.class.php") ;

/**
 * Build a page with the SDIF Queue Process form
 * and associated form processing.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage SDIF-Queue 
 *
 */
class SDIFQueueProcessPage extends FlipTurnLayoutPage
{
    function content_block()
    {
        //  Build the FormProcessor, and add the
        //  form content object that the FormProcessor 
        //  will use.
        //
	    $container = container() ;

        if (0) {
        //  Establish a database connection
 
        try
        { 
            $conn = ADONewConnection(FT_DB_DSN) ;
        }
        catch (exception $e)
        { 
            $success = false ;
            $container->add("Unable to connect to database.") ;
            return $container ;
            //var_dump($e); 
            //adodb_backtrace($e->gettrace());
        }

        
        //  Need a B1 record to obtain meet details.

        $rs = $conn->Execute('SELECT * FROM sdifqueue WHERE recordtype="B1"') ;
        //  Multiple B1 records?
        if ($rs->RecordCount() > 1)
        {
            $container->add($this->error_message('Multiple \"B1\" records found in SDIF queue.')) ;

            return $container ;
        }

        //  No B1 records?
        if ($rs->RecordCount() < 1)
        {
            $container->add($this->error_message('Missing \"B1\" records in SDIF queue.')) ;

            return $container ;
        }
        }

        $sdifqueue = new SDIFQueue() ;
        $sdifqueue->openConnection() ;

        if (!$sdifqueue->ValidateQueue())
        {
            $container->add($this->error_message($sdifqueue->get_status_message())) ;

            return $container ;
        }


	    //  Create the form
        $form = new SDIFQueueProcessForm("Process SDIF Queue", $_SERVER['PHP_SELF'], 600) ;

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
$page = new SDIFQueueProcessPage("Flip-Turn :: Process SDIF Queue") ;
print $page->render() ;
?>
