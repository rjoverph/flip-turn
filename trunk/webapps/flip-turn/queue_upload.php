<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * SDIF (.sd3) File Upload
 *
 * $Id$
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip Turn
 * @subpackage Upload
 *
 */ 

// Setup the Flip-Turn application
include('ft-setup.php') ;

//  Include the page layout
include_once("page.class.php") ;
include_once("sdif.forms.class.php") ;

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
class SDIFFileUploadPage extends FlipTurnLayoutPage
{
    function content_block()
    {
        //  Add the InfoTableCSS so the tables look right
	    $this->add_head_css(new InfoTableCSS) ;
	    
        //  Build the FormProcessor, and add the
        //  form content object that the FormProcessor 
        //  will use.
        //
	    $container = container() ;

	    //  Create the form
        $form = new SDIFFileUploadForm("Upload SDIF File", $_SERVER['PHP_SELF'], 600) ;
        $form->setUploadFileLabel("SDIF Filename") ;

	    //  Create the form processor
        $fp = new FormProcessor($form) ;

	    //  Don't display the form again if processing was successful.

	    $fp->set_render_form_after_success(false) ;

	    //  If the Form Processor was succesful, display
	    //  some statistics about the uploaded file.

	    if ($fp->is_action_successful())
	    {
            $sd3fileinfo = $form->get_file_info() ;
	        $container->add($fp, $form->get_file_info_table()) ;
	    }
        else
        {
	        //  Add the Form Processor to the container.

	        $container->add($fp) ;
        }


	    return $container ;
    }
}

//  Create the page and render it.
$page = new SDIFFileUploadPage("SDIF Upload File") ;
print $page->render() ;
?>
