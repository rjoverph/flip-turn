<?php
/**
 * This file contains the FEMultiListBox
 *
 * $Id: FEMultiListBox.inc 3029 2007-10-07 21:19:12Z brianrue $
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
 * This is the MultiListBox FormElement which builds a
 * select field with all of its options.  It enables
 * the ability to have multiple selections.
 * It has no validation method.
 *
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEMultiListBox extends FEListBox {

    /**
     * This function creates element name
     * used in the form based on the text label
     * or any other parameters
     *
     * Overriding things function to make sure
     * an array is created instead of a single variable
     */
    protected function create_element_name() {

        parent::create_element_name();

        $this->_element_name .= "[]";
    }

    /**
     * build the string for the confirmation page
     *
     * @return string
     */
    public function get_value_text() {
        $value = $this->get_value();
        if (empty($value)) {
            return '';
        }

        $data_flip = array_flip( $this->_data_list );
        //throw new phphtmllibException('ass');
        //exit;
        foreach( $value as $val ) {
            $ret[] = $data_flip[$val];
        }
        return implode(", ", $ret);
    }

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    public function get_element() {

        $attributes = $this->build_element_attributes();

        $attributes['multiple'] = "multiple";

        if ($this->_height) {
            $attributes["size"] = 5;
        }

        $selected_values = $this->get_value();

        $tag = new SELECTtag($attributes);

        foreach ($this->_data_list as $name=>$value) {

            $attributes = array("value"=>$value);
            if ((is_array($selected_values) && in_array($value, $selected_values)) ||
                (!is_array($selected_values) && $value == $selected_values)) {
                $attributes['selected'] = "selected";
            }
            if (isset($this->_disabled_items[$name])) {
                $attributes['disabled'] = "disabled";
            }

            $tag->add(new OPTIONtag($attributes, $name));
        }
        return $tag;
    }
}

?>