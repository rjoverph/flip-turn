<?php
/**
 * This file contains the VerticalCSSNavTableCSS
 * object
 * 
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */

/**
 * This class defines the css used by the
 * VerticalCSSNavTable Object.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib 
 */
class VerticalCSSNavTableCSS extends CSSBuilder {

    function user_setup() {
        $this->add_entry(".verticalcssnav", NULL,
                         array("vertical-align" => "top",
                               "font-family" => "arial, helvetica, sans-serif") );

        $this->add_entry(".verticalcssnav", "caption",
                         array("font-size" => "10pt",
                               "font-weight" => "bold",
                               "color" => "#FFFFFF",
                               "background-color" => "#999999",
                               "border" => "1px solid #999999"));

        $this->add_entry(".verticalcssnav", "div",
                         array("font-size" => "8pt",
                               "color" => "#000000",
                               "padding" => "2px 4px 2px 4px",
                               "border-right" => "1px solid #999999",
                               "border-left" => "1px solid #999999",
                               "border-bottom" => "1px solid #999999"));

        $this->add_entry(".verticalcssnav", "div.subtitle",
                         array("font-size" => "10pt",
                               "font-weight" => "bold",
                               "color" => "#777777",
                               "background-color" => "#eeeeee",
                               "text-align" => "center"));

        $this->add_entry(".verticalcssnav", "a.navurl:active,a.navurl:link,a.navurl:visited",
                         array("display" => "block",
                               "font-family" => "arial, verdana, helvetica, sans-serif",
                               "font-size" => "10pt",
                               "padding" => "2px 4px 2px 4px",
                               "text-decoration" => "none",
                               "color" => "#000000",
                               "background-color" => "#FFFFFF",
                               "border-bottom" => "1px solid #999999",
                               "border-right" => "1px solid #999999",
                               "border-left" => "1px solid #999999"));

        $this->add_entry(".verticalcssnav", "a.navurl:hover",
                         array("color" => "#000000",
                               "background-color" => "#eeeeee"));

    
    }   
}

?>
