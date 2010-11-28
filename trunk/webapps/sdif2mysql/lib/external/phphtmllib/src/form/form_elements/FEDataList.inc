<?php
/**
 * This file contains the base FEDataList class
 *
 * $Id: FEDataList.inc 1821 2006-08-03 23:52:31Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * This is the DataList FormElement which builds a
 * a complex FEBoxElement. It has no validation method.
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEDataList extends FEBoxElement {

    /**
     * Holds the list of available
     * data elements
     *
     */
    protected $_data_list = array();

    /**
     * The list of disabled items
     * (if any)
     */
    protected $_disabled_items = array();

    /**
     * The constructor
     *
     * @param string $label text label for the element
     * @param boolean $required is this a required element?
     * @param int $width element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int $height element height in px
     * @param array $data_list list of data elements (name=>value)
     */
    function __construct($label, $required = TRUE, $width = NULL, $height = NULL, $data_list = array()) {
        $this->set_list_data($data_list);
        parent::__construct($label, $required, $width, $height);
    }

    /**
     * This function sets the array of data
     * to be used in the data list
     *
     * @param array data_list - list of data elements (name=>value)
     */
    public function set_list_data($data_list = array()) {
        $this->_data_list = $data_list;
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
        $value = $this->get_value();
        $flip = array_flip($this->_data_list);
        if (array_key_exists($value, $flip)) {
            return $flip[$value];
        } else {
            return NULL;
        }
    }

    /**
     *
     * This function is responsible for performing complete
     * validation and setting the appropriate error message
     * in case of a failed validation
     *
     */
    public function validate() {
        // we make sure that the value is in the data list
        $values = $this->get_value();
        if (is_array($values)) {
            foreach($values as $value) {
                if (!in_array($value, $this->_data_list)) {
                    Validator::error(ValidatorException::STR_INVALID_FIELD);
                }
            }
        } else {
            if (!in_array($values, $this->_data_list)) {
                Validator::error(ValidatorException::STR_INVALID_FIELD);
            }
        }
    }

    /**
     * This method allows you to disable one of the items
     * in the list of checkboxes.
     *
     * @param string the name of the checkbox to disable
     * @return none
     */
    public function disable_item($name) {
        $this->_disabled_items[$name] = 1;
    }
}

?>