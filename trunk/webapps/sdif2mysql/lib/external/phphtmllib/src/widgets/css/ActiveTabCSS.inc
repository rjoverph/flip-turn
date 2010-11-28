<?php
/**
 * This file contains the ActiveTabCSS object
 * 
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */


/**
 * The CSSBuilder object for the ActiveTab widget
 *
 * @package phpHtmlLib
 */
class ActiveTabCSS extends CSSBuilder {
    function user_setup() {
        $this->add_entry(".activetab", "",
                         array("align" => "center") );

        $this->add_entry(".activetab", ".spacer",
                         array("width" => "5px",
                               "border-bottom" => "1px solid #a1a1a1"));
        $this->add_entry(".activetab", ".end",
                         array("border-bottom" => "1px solid #a1a1a1"));

        $this->add_entry(".activetab", ".link:active,.link:hover,.link:link,.link:visited",
                         array("text-decoration" => "none",
                               "color" => "#000000"));

        $this->add_entry(".activetab", ".tabhidden",
                         array("border" => "1px solid #999999",
                               "padding-left" => "5px",
                               "padding-right" => "5px",
                               "background-color" => "#eeeeee",
                               "text-align" => "center",
                               "white-space" => "nowrap",
                               "font-family" => "arial",
                               "font-size" => "10pt"));

        $this->add_entry(".activetab", ".tabselected",
                         array("border-left" => "1px solid #999999",
                               "border-top" => "1px solid #999999",
                               "border-right" => "1px solid #999999",
                               "padding-left" => "5px",
                               "padding-right" => "5px",
                               "text-align" => "center",
                               "white-space" => "nowrap",
                               "font-family" => "arial",
                               "font-size" => "10pt"));

        $this->add_entry(".activetab", ".content",
                         array("border-left" => "1px solid #a1a1a1",
                               "border-right" => "1px solid #a1a1a1",
                               "border-bottom" => "1px solid #a1a1a1",
                               "position" => "relative",
                               "z-index" => "100"));

        $this->add_entry(".activetab", ".content_visible",
                         array("position" => "absolute",
                               "left" => "0px",
                               "top" => "0px",
                               "visibility" => "visible",
                               "z-index" => "50",
                               "padding" => "5px 5px 5px 5px"));

        $this->add_entry(".activetab", ".content_hidden",
                         array("position" => "absolute",
                               "left" => "0px",
                               "top" => "0px",
                               "visibility" => "hidden",
                               "z-index" => "50",
                               "padding" => "5px 5px 5px 5px"));
    }

}
?>
