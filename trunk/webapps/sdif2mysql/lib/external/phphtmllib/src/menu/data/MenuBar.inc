<?php
/**
 * The MenuBar
 * 
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */

/**
 * This is the menu item
 * that handles single menu item data
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */
class MenuBar implements IteratorAggregate {

    /**
     * List of menu bar entries
     *
     * @var array
     */
    protected static $menus = array();

    /**
     * Adds a new menu item to
     * a menu under the menu bar
     *
     * @param string $name
     * @param MenuItem $item
     */
    public function add($name, MenuItem $item) {
        if (!isset(self::$menus[$name])) {
            throw new phphtmllibException('Invalid menu name');
        }

        self::$menus[$name][] = $item;
    }

    /**
     * Implements iterator interface
     *
     * @return Iterator
     */
    function getIterator() {
        return new ArrayIterator(self::$menus);
   }

   /**
    * This static method is used to initialize the main
    * menu structure of the app
    * 
    * @param array
    */
    public static function init_menu($menu) {
        MenuBar::$menus = $menu;
    }

    /**
     * This method is used to get a handle (reference)
     * to a particular menu, so you can add new items later
     * 
     * @param string $name
     * @return array
     *
    public function &get($name, $item=NULL) {
        if (!array_key_exists($name, self::$menus)) {
            throw new phphtmllibException('Invalid menu name '.$name);
        }

        //does the user want the entire menu?
        if (is_null($item_name)) {
            return self::$menus[$name];
        } else {
            //they want a specific menu inside it.

        }
    }*/

}
?>