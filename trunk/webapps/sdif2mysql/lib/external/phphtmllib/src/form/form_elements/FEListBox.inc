<?php
/**
 * This file contains the FEListBox class
 *
 * $Id: FEListBox.inc 1573 2005-09-19 20:58:11Z suren2 $
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
 * This is the ListBox FormElement which builds a
 * select field with all of its options.
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
class FEListBox extends FEDataList {

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

        $selected_value = $this->get_value();

        $tag = new SELECTtag($attributes);

        foreach ($this->_data_list as $name=>$value) {

            $attributes = array("value"=>$value);
            if ($value == $selected_value) {
                $attributes['selected'] = "selected";
            }
            if (isset($this->_disabled_items[$name])) {
                $attributes['disabled'] = "disabled";
            }

            $tag->add(new OPTIONtag($attributes, htmlspecialchars($name)));
        }
        return $tag;
    }
}

?>