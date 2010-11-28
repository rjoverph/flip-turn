<?php
/**
 * This is the menu widget
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */

/**
 * This is the menu widget
 * that renders list of menu items
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */
class MenuWidget extends HTMLWidget {

    /**
     * Name
     */
    protected $name;

    protected $menu=array();

    /**
     * constructor
     * 
     * @param string $name
     * @param array $menu
     */
    public function __construct($name, $menu) {
        $this->name = $name;
        $this->menu = $menu;
    }

    /**
     * This function is used to
     * arrange menu items in proper
     * order
     *
     * @param MenuItem $a
     * @param MenuItem $b
     */
    private function item_sort(&$a, &$b) {
        if (is_string($a) || is_string($b)) {
            return 0;
        }

       return ($a->get_position()  - $b->get_position());
    }


    /**
     * Renders a single menu widget
     *
     * @return DIVtag
     */
    public function render($indent_level=0, $output_debug=0) {
        $c = Container::factory();

        $menu_id = 'mid' . strtolower(str_replace('_', '', $this->name));

        // the actual menu div
        $menu_div = new DIVtag(array('id' => $menu_id,
                                     'class' => 'menu'));

        //all objects in php5 are references :)
        $c->add($menu_div);

        // lets sort menu items
        usort($this->menu, array($this, 'item_sort'));

        // loop through all menu items
        foreach ($this->menu as $item) {

            if ($item instanceof MenuItemSeparator) {
                // add a menu separator
                $menu_div->add(new MenuItemSeparatorWidget());
            } else if ($item instanceof MenuUrlItem) {                   
                $menu_div->add(new MenuUrlItemWidget($item));
            } else {
                //add the menu item, then add the submenus
                $menu_div->add(new MenuItemWidget($item));
                if ($item->has_menus()) {
                    $c->add(new MenuWidget($item->get_name(),
                                           $item->get_menus()));
                }
                //foreach($item as $menu) {
                //    $c->add(new MenuWidget($item->get_name(), $menu));
                //}
                
            }
        }

        return $c->render($indent_level, $output_debug);
    }

}