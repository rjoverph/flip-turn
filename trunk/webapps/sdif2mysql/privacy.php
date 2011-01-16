<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * Flip-Turn Privacy Page
 *
 * $Id$
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip Turn
 * @subpackage Privacy
 *
 */ 

// * Include the phphtmllib libraries
include("ft-setup.php") ;
include("page.class.php") ;

/**
 * Privacy stuff
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnLayoutPage
 *
 */
class FlipTurnPrivacyPage extends FlipTurnLayoutPage
{
    function content_block()
    {
	    $container = container() ;

        $container->add("Privacy content goes here.") ;

	    return $container ;
    }
}


$page = new FlipTurnPrivacyPage("Privacy") ;

print $page->render() ;
?>
