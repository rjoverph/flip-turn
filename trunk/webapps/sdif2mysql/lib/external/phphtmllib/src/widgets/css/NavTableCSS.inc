<?php
/**
 * This file contains the NavTableCSS
 * object
 * 
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */

/**
 * This class defines the css used by the
 * FooterNav Object.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib 
 */
class NavTableCSS extends CSSBuilder {

    function user_setup() {
        $this->add_entry(".navtable", NULL,
                         array("font-family" => "arial,verdana,helvetica") );

        $this->add_entry(".navtable", ".title",
                         array("font-size" => "10pt",
                               "font-weight" => "bold",
                               "text-align" => "center",
                               "color" => "#FFFFFF",
                               "background-color" => "#999999",
                               "width" => "98%") );

        $this->add_entry(".navtable", ".barleft",
                         array("background-image" => "url('/phphtmllib/widgets/images/top-left-corner.gif')",
                               "background-repeat" => "no-repeat",
                               "background-color" => "#999999",
                               "width" => "1%"));

        $this->add_entry(".navtable", ".barright",
                         array("background-image" => "url('/phphtmllib/widgets/images/top-right-corner.gif')",
                               "background-repeat" => "no-repeat",
                               "background-color" => "#999999",
                               "width" => "1%"));

        $this->add_entry(".navtable", ".content",
                         array("border" => "1px solid #777777",
                               "background-color" => "#FFFFFF") );

        $this->add_entry(".navtable", ".subtitle",
                         array("font-size" => "8pt",
                               "font-weight" => "bold",
                               "text-align" => "center",
                               "color" => "#777777",
                               "background-color" => "#eeeeee") );

        $this->add_entry(".navtable", ".bullet",
                         array("width" => "1%",
                               "font-size" => "10pt",
                               "padding-left" => "5px"));

        $this->add_entry(".navtable", ".link",
                         array("width" => "99%",
                               "font-size" => "10pt",
                               "line-height" => "11pt"));

        $this->add_entry(".navtable", "a:active,a:link,a:visited",
                         array("font-weight" => "bold",
                               "color" => "#505dd8") );
        $this->add_entry(".navtable", "a:hover",
                         array("color" => "#505dd8",
                               "background-color" => "#eeeeee",
                               "text-decoration" => "none") );
    }   
}
?>
