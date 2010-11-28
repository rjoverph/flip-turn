<?php
/**
 * This file contains the TabListCSS
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
class TabListCSS extends CSSBuilder {

    function user_setup() {
        $this->add_entry(".tablist", "",
                         array(
                             "margin" => "0px",
                             "padding" => "0px",
                             "font-family" => "sans-serif",
                             "font-size" => "12px",
                             ) );

        $this->add_entry(".tablist", ".tab_selected",
                         array(
                             "font-weight" => "bold",
                             "padding" => "2px 4px 2px 4px",
                             "color" => "#FFFFFF",
                             "background-color" => "#999999",
                             "border-right" => "1px solid #828282",
                             "border-top" => "1px solid #828282"
                             ) );

        $this->add_entry(".tablist", ".tab_default",
                         array(
                             "padding" => "2px 4px 2px 4px",
                             "color" => "#FFFFFF",
                             "background-color" => "#e1e1e1",
                             "border-left" => "1px solid #828282",
                             "border-right" => "1px solid #828282",
                             "border-top" => "1px solid #828282",
                             "border-bottom" => "1px solid #828282"
                             ));

        $this->add_entry(".tablist", ".tab_spacer",
                         array(
                             "margin" => "0px",
                             "padding" => "0px",
                             "background-color" => "#ffffff",
                             "border-bottom" => "1px solid #828282",
                             ));

        $this->add_entry(".tablist", ".tab_spacer_last",
                         array(
                             "margin" => "0px",
                             "padding" => "0px",
                             "background-color" => "#ffffff",
                             "border-bottom" => "1px solid #828282"
                             ));


        $this->add_entry(".tablist", ".tab_data",
                         array(
                             "margin" => "0px",
                             "background-color" => "#ffffff",
                             "border-left" => "1px solid #828282",
                             "border-right" => "1px solid #828282",
                             "border-bottom" => "1px solid #828282"
                             ));


        $this->add_entry(".tablist", ".subtab",
                         array(
                             "margin" => "0px",
                             "padding" => "2px 10px 2px 2px",
                             "background-color" => "#999999",
                             "white-space" => "nowrap"
                             ));


        /**
         * The href links
         */
        $this->add_entry(".tablist", ".tab_link_selected",
                         array(
                             "text-decoration" => "none",
                             "color" => "#ffffff",
                             "font-weight" => "bold"
                             ));

        $this->add_entry(".tablist", ".tab_link_selected:hover",
                         array(
                             "text-decoration" => "none",
                             "color" => "#efefef",
                             "font-weight" => "bold"
                             ));

        $this->add_entry(".tablist", ".tab_link_default",
                         array(
                             "text-decoration" => "none",
                             "color" => "#828282",
                             ));
        $this->add_entry(".tablist", ".tab_link_default:hover",
                         array(
                             "text-decoration" => "none",
                             "color" => "#ffffff",
                             ));


        $this->add_entry(".tablist", ".subtab_link_selected",
                         array(
                             "text-decoration" => "none",
                             "color" => "#ffffff",
                             "font-weight" => "bold"
                             ));

        $this->add_entry(".tablist", ".subtab_link_selected:hover",
                         array(
                             "text-decoration" => "none",
                             "color" => "#efefef",
                             "font-weight" => "bold"
                             ));

        $this->add_entry(".tablist", ".subtab_link_default",
                         array(
                             "text-decoration" => "underline",
                             "color" => "#e1e1e1",
                             ));
        $this->add_entry(".tablist", ".subtab_link_default:hover",
                         array(
                             "text-decoration" => "none",
                             "color" => "#ffffff",
                             ));

    }
}

?>
