<?php
/**
 * This file contains the InfoTableCSS
 * object
 * 
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */

/**
 * This class defines the css used by the
 * InfoTableCSS Object.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
class InfoTableCSS extends CSSBuilder {

    function user_setup() {
        $this->add_entry(".infotable", NULL,
                         array("margin" => "0px 0px 0px 0px",
                               "font-family" => "arial, helvetica, sans-serif",
                               "font-size" => "10pt",
                               "border-left" => "1px solid #999999",
                               "border-right" => "1px solid #999999",
                               "border-bottom" => "1px solid #999999") );

        $this->add_entry(".infotable", "caption.title",
                         array("font-size" => "10pt",
                               "font-weight" => "bold",
                               "padding" => "2px 5px 2px 5px",
                               "color" => "#FFFFFF",
                               "background-color" => "#999999",
                               "border-top" => "1px solid #999999",
                               "border-left" => "1px solid #999999",
                               "border-right" => "1px solid #999999"));

        $this->add_entry(".infotable", "td.header",
                         array("font-weight" => "bold",
                               "border-top" => "1px solid #999999",
                               "border-right" => "1px solid #999999"));

        $this->add_entry(".infotable", "td.headerlast",
                         array("font-weight" => "bold",
                               "border-top" => "1px solid #999999"));

        $this->add_entry(".infotable", "td.contentnovertical",
                         array("border-top" => "1px solid #999999"));

        $this->add_entry(".infotable", "td.contentvertical",
                         array("border-top" => "1px solid #999999",
                               "border-right" => "1px solid #999999"));
    }
}
?>
