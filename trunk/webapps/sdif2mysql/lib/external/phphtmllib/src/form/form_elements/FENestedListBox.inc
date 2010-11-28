<?php
/**
 * This file contains the FENestedListBox
 *
 * $Id: FENestedListBox.inc 1821 2006-08-03 23:52:31Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * This class builds a nested select box that
 * is used to select an entry from nested levels.
 *
 * NOTE: The data array must be in the format
 *       array("test" => "testvalue",
 *             "nestedtest" => array("value" => "nestedtestvalue",
 *                                   "items" => array( "foo" => "foovalue",
 *                                                     "bar" => "barvalue"));
 *
 * Example
 * $data = array("Test" => 1,
 *               "Foo" => array("value" => 2,
 *                              "items" => array("Blah" => 3,
 *                                               "php" => 4)),
 *               "Bar" => array("value" => 5,
 *                              "items" => array("testing" => array("value" => 6,
 *                                                                  "items" => array("ugh" => 7)),
 *                                               "again" => 8)));
 *
 * would result in
 *
 * <select >
 *  <option value="1">Test</option>
 *  <option value="2">Foo</option>
 *  <option value="3">&nbsp;&nbsp;Blah</option>
 *  <option value="4">&nbsp;&nbsp;php</option>
 *  <option value="5">Bar</option>
 *  <option value="6">&nbsp;&nbsp;testing</option>
 *  <option value="7">&nbsp;&nbsp;&nbsp;&nbsp;ugh</option>
 *  <option value="8">&nbsp;&nbsp;again</option>
 * </select>
 *
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FENestedListBox extends FEDataList {

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    public function get_element() {

        $attributes = $this->build_element_attributes();

        if ($this->_height) {
            $attributes["size"] = 5;
        }

        $tag = new SELECTtag($attributes);

        $this->_add_array($this->_data_list, 0, $tag);
        return $tag;
    }


    /**
     *
     * This function is responsible for performing complete
     * validation and setting the appropriate error message
     * in case of a failed validation
     *
     * @return void
     */
    public function validate() {
        // we make sure that the value is in the data list
        $value = $this->get_value();

        if (!$this->_array_search_r($value, $this->_data_list, $temp)) {
            Validator::error(ValidatorException::STR_INVALID_FIELD);
        }
    }


    private function _array_search_r($needle, $haystack, &$item) {

        $match = FALSE;

        foreach($haystack as $name=>$value) {
            if (is_array($value)) {
                if ($value["value"] == $needle) {
                    $item = $name;
                    $match = TRUE;
                } else {
                    $match = $this->_array_search_r($needle, $value["items"], $item);
                    $item = $name."::".$item;
                }
            } else if ($value==$needle) {
                $item = $name;
                $match = TRUE;
            }

            if ($match)
                return TRUE;
        }
        return $match;
    }


    /**
     * This provides a method
     * for the FormContent
     * to get access to the
     * text associated with a
     * field.  This is only available
     * on FormElements that have text
     * associated with a field.
     * It is used during Confirmation
     *
     * @return string - the text associated
     */
    public function get_value_text() {
        $ret = $this->_array_search_r($this->get_value(),
                                      $this->_data_list, $item);
        return $item;
    }


    /**
     * This is a recursive function used to add
     * an array of layers to the select box.
     *
     * @param array - the next level of name=>value pairs
     * @param int - the level
     * @param SELECTtag - the SELECTtag object to add the options
     * @return none
     */
    private function _add_array($layer_arr, $level, &$tag) {
        if (!is_array($layer_arr)) {
            return;
        }

        foreach( $layer_arr as $name=>$value) {
            if (is_array($value)) {
                $tag->add( $this->_build_option($name, $value["value"], $level));
                $this->_add_array($value["items"], $level+1, $tag);
            } else {

                $tag->add($this->_build_option($name, $value, $level));
            }
        }
    }

    /**
     * This method builds the actual OPTIONtag object
     *
     * @param string the name
     * @param string the value
     * @param int the level
     * @return OPTIONtag object
     */
    private function _build_option($name, $value, $level) {
        $selected_value = $this->get_value();

        $attributes = array("value"=>$value);
        if ($value == $selected_value) {
            $attributes['selected'] = "selected";
        }

        if (isset($this->_disabled_items[$name])) {
            $attributes['disabled'] = "disabled";
        }

        return new OPTIONtag($attributes, $this->_layer_name($name, $level));
    }

    /**
     * This builds a layer's name
     *
     * @param string - original name
     * @param int the layer level
     * @return string the new name
     */
    private function _layer_name($name, $level) {
        $newname = '';

        if ($level == 0) {
            return $name;
        } else {
            $newname .= str_repeat(phphtmllib::_HTML_SPACE, $level*2).$name;
        }

        return $newname;
    }
}

?>