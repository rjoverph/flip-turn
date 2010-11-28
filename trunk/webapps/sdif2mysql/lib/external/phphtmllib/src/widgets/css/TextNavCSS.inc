<?php
/**
 * This file contains the TextNavCSS
 * object
 * 
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */


/**
 * This class defines the css used by the
 * TextNav Object.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib 
 */
class TextNavCSS extends CSSBuilder {

    function user_setup() {

        $this->add_entry("A.textnavlist:hover", "",
                         array("color" => "#FF0000") );

        $this->add_entry("A.textnavlist", "",
                         array("font-family" => "Arial, Helvetica, sans-serif",
                               "font-size" => "10pt",
                               "font-weight" => "bold",
                               "color" => "#FFFFFF",
                               "text-decoration" => "none"));

        $this->add_entry("TD.textnavdivider", "",
                         array("background-image" =>
                               "url('/phphtmllib/widgets/images/dot_div_vert.gif')"));

        $this->add_entry("TD.textnavtd", "",
                         array("background-color" => "#999999"));
    
    }   
}
?>
