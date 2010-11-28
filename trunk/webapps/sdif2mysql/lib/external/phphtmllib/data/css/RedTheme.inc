<?php
/**
 * RedTheme
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage css
 */

/**
 * This file builds a class that is used
 * to render the default/standard theme
 * css for the phphtmllib widgets
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage css
 */


class RedTheme extends StandardTheme {

    /**
     * This method is used to set/update the theme
     * colors which are diffs from the standard theme
     * settings that are defined in the CSS objects
     * 
     * @return none
     */
    protected function add_theme() {
        //update all the background-color defs
        $this->update_all_values("background-color",
                                 "#999999", "#d31919");
        $this->update_all_values("background-color",
                                 "#eeeeee", "#ffa8a8");

        //update all the color defs
        $this->update_all_values("color",
                                 "#777777", "#d31919");
        $this->update_all_values("color",
                                 "#828282", "#d31919");

        //update all the border defs
        $this->update_all_values("border",
                                 "1px solid #999999",
                                 "1px solid #d31919");
        $this->update_all_values("border-left",
                                 "1px solid #999999",
                                 "1px solid #d31919");
        $this->update_all_values("border-bottom",
                                 "1px solid #999999",
                                 "1px solid #d31919");
        $this->update_all_values("border-top",
                                 "1px solid #999999",
                                 "1px solid #d31919");
        $this->update_all_values("border-right",
                                 "1px solid #999999",
                                 "1px solid #d31919");

        $this->update_all_values("border-left",
                                 "1px solid #828282",
                                 "1px solid #700000");
        $this->update_all_values("border-bottom",
                                 "1px solid #828282",
                                 "1px solid #700000");
        $this->update_all_values("border-top",
                                 "1px solid #828282",
                                 "1px solid #700000");
        $this->update_all_values("border-right",
                                 "1px solid #828282",
                                 "1px solid #700000");

        $this->update_all_values("border",
                                 "1px solid #a1a1a1",
                                 "1px solid #d31919");
        $this->update_all_values("border-left",
                                 "1px solid #a1a1a1",
                                 "1px solid #d31919");
        $this->update_all_values("border-bottom",
                                 "1px solid #a1a1a1",
                                 "1px solid #d31919");
        $this->update_all_values("border-top",
                                 "1px solid #a1a1a1",
                                 "1px solid #d31919");
        $this->update_all_values("border-right",
                                 "1px solid #a1a1a1",
                                 "1px solid #d31919");
    }
}

?>
