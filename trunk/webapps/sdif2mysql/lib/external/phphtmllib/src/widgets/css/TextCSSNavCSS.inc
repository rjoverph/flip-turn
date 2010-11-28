<?php
/**
 * This file contains the TextCSSNavCSS
 * object
 * 
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */

/**
 * This class defines the css used by the
 * FooterNav Object.
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 */
class TextCSSNavCSS extends CSSBuilder {

    function user_setup() {
        $this->add_entry(".textnav", "",
                         array(
                              "margin" => "0px 0px 0px 0px",
                              "padding" => "3px 0px 0px 0px",
                              "height" => "16px",
                              "color" => "#FFFFFF",
                              "font-family" => "sans-serif",
                              "font-size" => "11px",
                              "font-weight" => "bold",
                              ) );

        $this->add_entry(".textnav", "a.normal,a.normal:visited,a.normal:active",
                         array("font-family" => "sans-serif",
                               "text-decoration" => "none",
                               "color" => "#FFFFFF",
                               "background-color" => "#999999",
                               "padding" => "2px 4px 2px 4px",
                               "border-right" => "1px solid #828282",
                               "border-top" => "1px solid #828282",
                               "border-bottom" => "1px solid #828282"
                              ) );

        $this->add_entry(".textnav", "a.first,a.first:visited",
                         array("font-family" => "sans-serif",
                               "text-decoration" => "none",
                               "color" => "#FFFFFF",
                               "background-color" => "#999999",
                               "padding" => "2px 4px 2px 4px",
                               "border-left" => "1px solid #828282",
                               "border-right" => "1px solid #828282",
                               "border-top" => "1px solid #828282",
                               "border-bottom" => "1px solid #828282") );

        $this->add_entry(".textnav", "a.normal:hover,a.first:hover",
                         array("color" => "#000000",
                               "background-color" => "#EEEEEE",
                               "text-decoration" => "none"));

        $this->add_entry(".textnav", "a.selected,a.selected:visited",
                         array("font-family" => "sans-serif",
                               "text-decoration" => "none",
                               "color" => "#828282",
                               "background-color" => "#EEEEEE",
                               "padding" => "2px 4px 2px 4px",
                               "border-right" => "1px solid #828282",
                               "border-top" => "1px solid #828282",
                               "border-bottom" => "1px solid #828282"
                              ) );

        $this->add_entry(".textnav", "a.selectedfirst,a.selectedfirst:visited",
                         array("font-family" => "sans-serif",
                               //"font-size" => "12px",
                               "font-weight" => "bold",
                               "text-decoration" => "none",
                               "color" => "#828282",
                               "background-color" => "#EEEEEE",
                               "padding" => "2px 4px 2px 4px",
                               "border-left" => "1px solid #828282",
                               "border-top" => "1px solid #828282",
                               "border-bottom" => "1px solid #828282") );
    }   
}

?>
