<?php
/**
 * This file shows 1 way to render a MenuUrlItem object
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */

/**
 * This object renders an achor link for
 * a menu.
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */
class MenuUrlItemWidget extends MenuItemWidget {

    public function render($indent_level=0, $output_debug=0) {
        $a = $this->item->get();
        //make sure we set the class
        $a->set_class('menuItem');
        return $a->render($indent_level, $output_debug);
    }
}
?>
