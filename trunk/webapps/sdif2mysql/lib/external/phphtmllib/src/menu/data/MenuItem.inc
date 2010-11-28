<?php
/**
 * The MenuItem base class.
 * 
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */


/**
 * This is the menu item
 * that handles single menu item data
 *
 * $Id: MenuItem.inc 3029 2007-10-07 21:19:12Z brianrue $
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */
class MenuItem extends Menu implements IteratorAggregate {

    /**
     * Menu item position in the menu
     *
     * @var int
     */
    protected $position;

    /**
     * Menu item displayed name
     *
     * @var string
     */
    protected $name;

    /**
     * Menu item target name
     *
     * @var string
     */
    protected $target;

    /**
     * Target parameters
     *
     * @var array
     */
    protected $params;

    /**
     * Holds the icon name
     * for the menu
     *
     * @var string
     */
    protected $icon;


    /**
     * Container to hold MenuItems that
     * have been added (for submenus)
     * 
     * @var array
     */
    protected $menus = array();

    /**
     * Constructor
     *
     * @param string $name
     * @param string $target
     * @param array $params
     * @param int $position
     * @param string $icon
     */
    public function __construct($name, $target = null, $params = null,
                                $position = 0, $icon = null) {

        $this->name = $name;
        $this->target = $target;
        $this->params = $params;
        $this->position = $position;
        $this->icon = $icon;
    }

    /**
     * Returns menu item position
     *
     * @return int
     */
    public function get_position() {
        return $this->position;
    }

    /**
     * Returns display name
     *
     * @return string
     */
    public function get_name() {
        return $this->name;
    }

    /**
     * Returns icon to
     * be used
     *
     * @return string
     */
    public function get_icon() {
        return $this->icon;
    }

    /**
     * Returns menu item
     * target
     *
     * @param string
     */
    public function get_target() {
        return $this->target;
    }

    /**
     * Returns target parameters
     *
     * @return array
     */
    public function get_params() {
        return $this->params;
    }


    /**
     * This method is used to determine if
     * we have any internal (sub) menus
     *
     * @return boolean
     */
    public function has_menus() {
        return (is_array($this->menus) && (count($this->menus) > 0));
    }


    /**
     * This method is used to add a submenu item
     * 
     * @param string $name
     * @param MenuItem $item
     */
    public function add(MenuItem $item) {
        $this->menus[] = $item;
    }

    /**
     * this method gets all of the entries out
     * 
     * @return array
     */
    public function get_menus() {
        return $this->menus;
    }

    /**
     * This method is used to get a handle (reference)
     * to a particular menu, so you can add new items later
     * 
     * @param string $name
     * @return array
     *
    public function &get($name) {
        if (!array_key_exists($name, self::$menus)) {
            throw new phphtmllibException('Invalid menu name '.$name);
        }

        return self::$menus[$name];
    }*/


    /**
     * For the interator
     * 
     * @return Iterator
     */
    public function getIterator() {
        return new ArrayIterator($this->menus);
    }

}