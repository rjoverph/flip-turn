<?php
/**
 * This is the main menu bar
 * widget
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */

/**
 * This object renders a full menu bar
 * with menu items.
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */
class MenuBarWidget extends HTMLWidget {

    /**
     * Holds the menu bar object
     *
     * @var MenuBar
     */
    protected $mb;

    /**
     * This function initializes
     * the menu bar object to be used
     *
     */
    protected function init_mb_object() {
        $this->mb = new MenuBar();
    }

    /**
     * This function builds our menu structure
     *
     * @return array
     *
     */
    protected function build_menu_data() {

        $this->init_mb_object();

        foreach (ClassMap::$menuable as $class) {
            $c = new $class;
            $c->menu($this->mb);
        }
    }

    /**
     * Renders our menu bar
     *
     * @return string
     */
    public function render($indent_level=0, $output_debug=0) {

        $this->build_menu_data();

        $c = new Container();

        $menubar_div = new DIVtag(array('id' => 'idMenuBar',
                                        'href' => '#',
                                        'class' => 'menuBar'));

        foreach ($this->mb as $name => $menu) {

            // we need a unique id to identify each menu
            $menu_id = 'mid' . strtolower(str_replace('_', '', $name));

            // add a menu bar item
            $menubar_div->add(new Atag(array('onClick' => 'return buttonClick(event, \'' . $menu_id . '\');',
                                             'onmouseover'=>'buttonMouseover(event, \'' . $menu_id. '\');',
                                             'class' => 'menuButton'
                                            ),
                                       $name));

            $c->add( new MenuWidget($name, $menu) );            

        }

        $c->add($menubar_div);

        return $c->render($indent_level, $output_debug);
    }

}