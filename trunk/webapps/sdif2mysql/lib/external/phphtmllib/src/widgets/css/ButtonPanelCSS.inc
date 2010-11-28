<?php
/**
 * This file contains the ButtonPanelCSS
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
class ButtonPanelCSS extends CSSBuilder {

    function user_setup() {
        $this->add_entry(".button_panel", NULL,
                         array("margin" => "12px 0px 10px 0px",
                               "padding" => "4px",
                               "border" => "1px solid #999999") );
    }
}
?>
