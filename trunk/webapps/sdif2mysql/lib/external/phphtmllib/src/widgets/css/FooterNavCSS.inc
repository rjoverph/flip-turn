<?php
/**
 * This file contains the FooterNavCSS
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
class FooterNavCSS extends CSSBuilder {

    function user_setup() {
        $this->add_entry("#footernav", NULL,
                         array("font-family" => "arial,verdana,helvetica",
                               "color" => "#4141FF") );

        $this->add_entry("#footernav", "div.links",
                         array("font-size" => "10px",
                               "line-height" => "10px",
                               "margin" => "15px 0px 10px 0px") );

        $this->add_entry("#footernav","A.foot:active, A.foot:link, A.foot:visited",
                         array("font-size" => "12px",
                               "color" => "#4141FF") );

        $this->add_entry("#footernav", "A.foot:hover",
                         array("color" => "#FFFFFF",
                               "background-color" => "#4141FF",
                               "text-decoration" => "none") );

        $this->add_entry("#footernav", "A.notice:active,A.notice:link,A.notice:visited",
                         array("font-size" => "11px",
                               "color" => "#4141FF") );

        $this->add_entry("#footernav", "A.notice:hover",
                         array("color" => "#FFFFFF",
                               "background-color" => "#4141FF",
                               "text-decoration" => "none") );

        $this->add_entry("#footernav", "SPAN.trademark",
                         array("font-size" => "11px",
                               "color" => "#000000"));

    }   
}
?>
