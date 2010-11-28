<?php
/**
 * This file contains the RoundTitleTableCSS
 * object
 * 
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */



/**
 * This class defines the css used by the
 * RoundTitleTable Object.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib 
 */
class RoundTitleTableCSS extends CSSBuilder {

    function user_setup() {
        $this->add_entry(".roundtitletable", NULL,
                         array("font-family" => "arial,verdana,helvetica") );

        $this->add_entry(".roundtitletable", ".title",
                         array("font-size" => "10pt",
                               "font-weight" => "bold",
                               "text-align" => "center",
                               "color" => "#FFFFFF",
                               "background-color" => "#999999",
                               "width" => "98%") );

        $this->add_entry(".roundtitletable", ".barleft",
                         array("background-image" => "url('/phphtmllib/widgets/images/top-left-corner.gif')",
                               "background-repeat" => "no-repeat",
                               "background-color" => "#999999",
                               "width" => "1%"));

        $this->add_entry(".roundtitletable", ".barright",
                         array("background-image" => "url('/phphtmllib/widgets/images/top-right-corner.gif')",
                               "background-repeat" => "no-repeat",
                               "background-color" => "#999999",
                               "width" => "1%"));

        $this->add_entry(".roundtitletable", ".content",
                         array("border" => "1px solid #777777;",
                               "background-color" => "#FFFFFF") );

        $this->add_entry(".roundtitletable", ".subtitle",
                         array("font-size" => "8pt",
                               "font-weight" => "bold",
                               "text-align" => "center",
                               "color" => "#777777",
                               "background-color" => "#eeeeee") );
    }   
}
?>
