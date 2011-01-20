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
include_once("ft-setup.php") ;
include_once("page.class.php") ;
include_once("options.class.php") ;

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

         $content = new FlipTurnOptionMeta() ;

        //  Account for no data in the options table
        if ($content->existOptionMetaByKey(FT_HOME_PAGE_OPTION))
        {
            $content->loadOptionMetaByKey(FT_HOME_PAGE_OPTION) ;
            $container->add(htmlspecialchars_decode($content->getOptionMetaValue())) ;
        }
        else
            $container->add(FT_HOME_PAGE_OPTION_DEFAULT_CONTENT) ;

        //  Allow the Admin to Edit the page content
 
        if ($this->user_is_logged_in())
            $container->add(div_font8bold(html_a('home_edit.php', 'Edit'))) ;

        return $container ;

    }
}


$page = new FlipTurnHomePage("Home") ;

print $page->render() ;
?>
