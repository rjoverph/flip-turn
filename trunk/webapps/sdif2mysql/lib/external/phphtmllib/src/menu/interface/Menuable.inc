<?php
/**
 * The Menuable interface.
 * 
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */

/**
 * This interface provides menu functionality
 * for pages
 *
 * Page classes impementing this interface
 * will have their menu items added to the
 * main navigation menu
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Menu
 *
 */
interface Menuable {

    /**
     * This function populates the main navigation
     * menu that appears for all the pages
     * all the time
     *
     * It adds menu items to the provided MenuBar
     * object that will be used by menu widgets
     * to render the menu
     *
     * @param MenuBar $mb
     */
    public static function menu(MenuBar &$mb);

}

?>