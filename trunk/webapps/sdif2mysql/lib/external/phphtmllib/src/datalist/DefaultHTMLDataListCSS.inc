<?php
/**
 * This class defines the css used by the
 * FooterNav Object.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage DataList
 */


/**
 * The CSSBuilder class for the DataList
 * 
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage DataList
 */
class DefaultHTMLDataListCSS extends CSSBuilder {

    function user_setup() {
        $this->add_entry(".datalist_col_head", "",
                         array("font-family" => "arial, helvetica, sans-serif",
                               "font-size" => "10pt",
                               "font-weight" => "bold",
                               "color" => "#000000",
                               "background-color" => "#CCCCCC",
                               "text-align" => "left",
                               "white-space" => "nowrap",
                               "height" => "20px",
                               "vertical-align" => "middle",
                               "border-left" => "1px solid white",
                               "border-top" => "1px solid white",
                               "border-right" => "1px solid gray",
                               "border-bottom" => "1px solid gray",
                               "padding-left" => "3px",
                               "padding-right" => "3px") );

        $this->add_entry(".datalist_col_head", "a.head_link:active,a.head_link:visited,a.head_link:link",
                         array("color" => "#000000",
                               "font-family" => "arial, helvetica, sans-serif",
                               "font-size" => "10pt",
                               "font-weight" => "bold",
                               "text-decoration" => "none"));

        $this->add_entry(".datalist_col_head_hover", "",
                         array("font-family" => "arial, helvetica, sans-serif",
                               "font-size" => "10pt",
                               "font-weight" => "bold",
                               "color" => "#000000",
                               "background-color" => "#dcdcdc",
                               "text-align" => "left",
                               "white-space" => "nowrap",
                               "height" => "20px",
                               "vertical-align" => "middle",
                               "border-left" => "1px solid white",
                               "border-top" => "1px solid white",
                               "border-right" => "1px solid gray",
                               "border-bottom" => "1px solid gray",
                               "padding-left" => "3px",
                               "padding-right" => "3px") );

        $this->add_entry(".datalist_col_head_clicked", "",
                         array("font-family" => "arial, helvetica, sans-serif",
                               "font-size" => "10pt",
                               "font-weight" => "bold",
                               "color" => "#000000",
                               "background-color" => "#dddddd",
                               "text-align" => "left",
                               "white-space" => "nowrap",
                               "height" => "20px",
                               "vertical-align" => "middle",
                               "border-left" => "1px solid white",
                               "border-top" => "1px solid white",
                               "border-right" => "1px solid gray",
                               "border-bottom" => "1px solid gray",
                               "padding-left" => "3px",
                               "padding-right" => "3px") );

        $this->add_entry( ".datalist_border", "",
                          array("border" => "1px solid #999999"));

        $this->add_entry( ".datalist_title", "",
                          array("font-family" => "arial",
                                "font-size" => "10pt",
                                "font-weight" => "bold",
                                "color" => "#FFFFFF",
                                "background-color" => "#999999",
                                "white-space" =>"nowrap"));

        $this->add_entry( ".datalist_data_cell", "",
                          array(
                               "font-family" => "arial",
                               "font-size" => "10pt",
                               "background-color" => "#ffffff",
                               "padding-left" => "3px",
                               "padding-right" => "3px",
                               "border-top" => "1px solid #dddddd"));

        $this->add_entry( ".datalist_data_cell_selected", "",
                          array(
                               "font-family" => "arial",
                               "font-size" => "10pt",
                               "background-color" => "#f7f7f7",
                               "padding-left" => "3px",
                               "padding-right" => "3px",
                               "border-top" => "1px solid #dddddd"));

        $this->add_entry( ".datalist_data_cell_odd", "",
                          array(
                               "font-family" => "arial",
                               "font-size" => "10pt",
                               "background-color" => "#fafafa",
                               "padding-left" => "3px",
                               "padding-right" => "3px",
                               "border-top" => "1px solid #dddddd"));

        $this->add_entry( ".datalist_data_cell_odd_selected", "",
                          array(
                               "font-family" => "arial",
                               "font-size" => "10pt",
                               "background-color" => "#f7f7f7",
                               "padding-left" => "3px",
                               "padding-right" => "3px",
                               "border-top" => "1px solid #dddddd"));

        $this->add_entry( ".datalist_actionbar", "",
                          array(
                               "border" => "1px solid #999999") );

        $this->add_entry( ".datalist_actionbar_data_cell", "",
                          array(
                               "font-family" => "arial",
                               "font-size" => "10pt",
                               "background" => "#CCCCCC",
                               "padding-left" => "3px",
                               "padding-right" => "3px",
                               "border-top" => "1px solid #dddddd"));

        $this->add_entry( ".datalist_bottom_seperator", "",
                          array(
                               "font-size" => "5px",
                               "line-height" =>  "5px",
                               "background" => "#CCCCCC",
                               "text-align" => "left",
                               "white-space" => "nowrap",
                               "height" => "5px",
                               "border-left" => "1px solid #FFFFFF",
                               "border-top" => "1px solid #FFFFFF",
                               "border-right" => "1px solid #dddddd",
                               "border-bottom" => "1px solid #dddddd",
                               "padding-left" =>  "3px",
                               "padding-right" => "3px"));
    }
}
?>
