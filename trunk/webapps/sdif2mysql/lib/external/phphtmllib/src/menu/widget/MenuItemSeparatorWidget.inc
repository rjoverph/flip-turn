<?php
/**
 * This file shows 1 way to render a MenuItemSeparator object
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */

/**
 * This object renders a seperator for a
 * menu bar.
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */
class MenuItemSeparatorWidget extends HTMLWidget {

    public function render($indent_level=0, $output_debug=0) {
        $div = new DIVtag(array('class' => 'menuItemSep'));
        return $div->render($indent_level, $output_debug);
    }
}
?>
