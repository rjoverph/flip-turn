<?php
/**
 * This file contains the ImageThumbnailWidgetCSS
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
class ImageThumbnailWidgetCSS extends CSSBuilder {

    function user_setup() {
        $this->add_entry(".imagethumbnail", "",
                         array("margin" => "0px 0px 0px 0px",
                               "font-family" => "arial, helvetica, sans-serif",
                               "font-size" => "10pt",
                               "border" => "1px solid #999999") );

        $this->add_entry(".imagethumbnail", "legend",
                         array("font-size" => "10pt",
                               "font-weight" => "bold",
                               "color" => "#000000"));

        $this->add_entry(".imagethumbnail", "a.thumblink:active,a.thumblink:link,a.thumblink:visited",
                         array("font-size" => "10pt",
                               "font-weight" => "bold",
                               "color" => "#999999",
                               "background" => "#FFFFFF"));

        $this->add_entry(".imagethumbnail", "a.thumblink:hover",
                         array("font-size" => "10pt",
                               "font-weight" => "bold",
                               "color" => "#4141FF",
                               "background" => "#eeeeee",
                               "text-decoration" => "none"));
        $this->add_entry(".imagethumbnail", "table",
                         array("padding-left" => "5px"));
    }   
}
?>
