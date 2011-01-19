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
include_once("ft-setup.php") ;
include_once("page.class.php") ;
include_once("options.class.php") ;

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

        $content = new FlipTurnOptionMeta() ;

        //  Account for no data in the options table
        if ($content->existOptionMetaByKey(FT_LEGAL_PAGE_OPTION))
        {
            $content->loadOptionMetaByKey(FT_LEGAL_PAGE_OPTION) ;
            $container->add(htmlspecialchars_decode($content->getOptionMetaValue())) ;
        }
        else
            $container->add(FT_LEGAL_PAGE_OPTION_DEFAULT_CONTENT) ;

        //  Allow the Admin to Edit the page content
 
        if ($this->user_is_logged_in())
            $container->add(div_font8bold(html_a('legal_edit.php', 'Edit'))) ;

	    return $container ;
    }
}


$page = new FlipTurnLegalPage("Legal") ;

print $page->render() ;
?>
