<?php
/**
 * DarkBlueTheme
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


class DarkBlueTheme extends StandardTheme {

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
                                 "#999999", "#0E1661");
        $this->update_all_values("background-color",
                                 "#eeeeee", "#ced4ff");

        //update all the color defs
        $this->update_all_values("color",
                                 "#777777", "#08074f");
        $this->update_all_values("color",
                                 "#828282", "#30669a");

        //update all the border defs
        $this->update_all_values("border",
                                 "1px solid #999999",
                                 "1px solid #30669a");
        $this->update_all_values("border-left",
                                 "1px solid #999999",
                                 "1px solid #30669a");
        $this->update_all_values("border-bottom",
                                 "1px solid #999999",
                                 "1px solid #30669a");
        $this->update_all_values("border-top",
                                 "1px solid #999999",
                                 "1px solid #30669a");
        $this->update_all_values("border-right",
                                 "1px solid #999999",
                                 "1px solid #30669a");

        $this->update_all_values("border-left",
                                 "1px solid #828282",
                                 "1px solid #8e9dff");
        $this->update_all_values("border-bottom",
                                 "1px solid #828282",
                                 "1px solid #8e9dff");
        $this->update_all_values("border-top",
                                 "1px solid #828282",
                                 "1px solid #8e9dff");
        $this->update_all_values("border-right",
                                 "1px solid #828282",
                                 "1px solid #8e9dff");

        $this->update_all_values("border",
                                 "1px solid #a1a1a1",
                                 "1px solid #30669a");
        $this->update_all_values("border-left",
                                 "1px solid #a1a1a1",
                                 "1px solid #30669a");
        $this->update_all_values("border-bottom",
                                 "1px solid #a1a1a1",
                                 "1px solid #30669a");
        $this->update_all_values("border-top",
                                 "1px solid #a1a1a1",
                                 "1px solid #30669a");
        $this->update_all_values("border-right",
                                 "1px solid #a1a1a1",
                                 "1px solid #30669a");
    }
}

?>
