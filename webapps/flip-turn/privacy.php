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
include_once("ft-setup.php") ;
include_once("page.class.php") ;
include_once("options.class.php") ;

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

        $content = new FlipTurnOptionMeta() ;

        //  Account for no data in the options table
        if ($content->existOptionMetaByKey(FT_PRIVACY_PAGE_OPTION))
        {
            $content->loadOptionMetaByKey(FT_PRIVACY_PAGE_OPTION) ;
            $container->add(htmlspecialchars_decode($content->getOptionMetaValue())) ;
        }
        else
            $container->add(FT_PRIVACY_PAGE_OPTION_DEFAULT_CONTENT) ;

        //  Allow the Admin to Edit the page content
 
        if ($this->user_is_logged_in())
            $container->add(div_font8bold(html_a('privacy_edit.php', 'Edit'))) ;

	    return $container ;
    }
}


$page = new FlipTurnPrivacyPage("Privacy") ;

print $page->render() ;
?>
