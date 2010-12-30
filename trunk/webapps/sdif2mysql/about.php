<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * About Page
 *
 * $Id$
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip Turn
 * @subpackage About
 *
 */ 

// * Include the phphtmllib libraries
include("includes.inc") ;

include("page.class.php") ;

/**
 * About stuff
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnLayoutPage
 *
 */
class FlipTurnAboutPage extends FlipTurnLayoutPage
{
    function content_block()
    {
	    $container = container() ;

        $container->add("About content goes here.") ;

	    return $container ;
    }
}


$page = new FlipTurnAboutPage("About") ;

print $page->render() ;
?>
