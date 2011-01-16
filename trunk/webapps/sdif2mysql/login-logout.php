<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * Flip Turn Admin
 *
 * $Id$
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip Turn
 * @subpackage Flip Turn
 *
 */ 

// Setup the Flip-Turn application
include('ft-setup.php') ;

//  Include the page layout
include_once("page.class.php") ;
include_once("forms.class.php") ;

/**
 * Build a page with the Login/Logout Form
 * and associated form processing.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage Admin
 *
 */
class FlipTurnAdminPage extends FlipTurnLayoutPage
{
    function content_block()
    {
        //  Build the FormProcessor, and add the
        //  form content object that the FormProcessor 
        //  will use.
        //
	    $container = container() ;
        
	    //  Create the form

        if ($this->user_is_logged_in())
            $form = new FlipTurnAdminLogoutForm("Admin Flip Turn Logout", null, 350) ;
        else
            $form = new FlipTurnAdminLoginForm("Admin Flip Turn Login", null, 350) ;

	    //  Create the form processor
        $fp = new FormProcessor($form) ;

	    //  Don't display the form again if processing was successful.

	    $fp->set_render_form_after_success(false) ;

	    //  Add the Form Processor to the container.

	    //  If the Form Processor was succesful, display
	    //  some a welcome message.

	    if ($fp->is_action_successful())
	    {
           //  Redirect to Member page on successful login

            //die($_SERVER['PHP_SELF']) ;
            $url = 'http://' . $_SERVER['HTTP_HOST'] . '/index.php' ;
            header("Location: {$url}") ;
            exit ;
            
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
$page = new FlipTurnAdminPage("Flip Turn Admin") ;
print $page->render() ;
?>
