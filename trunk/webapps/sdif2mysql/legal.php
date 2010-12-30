<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * Flip-Turn Legal Page
 *
 * $Id$
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip Turn
 * @subpackage Legal
 *
 */ 

// * Include the phphtmllib libraries
include("includes.inc") ;

include("page.class.php") ;

/**
 * Legal stuff
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnLayoutPage
 *
 */
class FlipTurnLegalPage extends FlipTurnLayoutPage
{
    function content_block()
    {
	    $container = container() ;

        $container->add("Legal content goes here.") ;

	    return $container ;
    }
}


$page = new FlipTurnLegalPage("Legal") ;

print $page->render() ;
?>
