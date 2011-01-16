<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * Home Page
 *
 * $Id$
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip Turn
 * @subpackage Home
 *
 */ 

// * Include the phphtmllib libraries
include("ft-setup.php") ;
include("page.class.php") ;

/**
 * Home stuff
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnLayoutPage
 *
 */
class FlipTurnHomePage extends FlipTurnLayoutPage
{
    function content_block()
    {
	    $container = container() ;

        $container->add("Home content goes here.") ;

	    return $container ;
    }
}


$page = new FlipTurnHomePage("Home") ;

print $page->render() ;
?>
