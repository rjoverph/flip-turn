<?php
/**
 * This file contains the FENumberInRange class
 *
 * $Id: FENumberInRange.inc 3161 2008-10-06 22:13:32Z hemna $
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
 * This is the Number Range FormElement which builds a
 * text input field.
 * It validates as is_within_rage().
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FENumberInRange extends FEText {

    /**
     * The minimum #
     */
    protected $_min = 0;
    /**
     * The maximum #
     */
    protected $_max = 100;

    /**
     * Add the range to the label automatically?
     */
    protected $_label_flag = TRUE;

    /**
     * The 'Range' text
     */
    protected $_range_text = "Range";

    /**
     * The constructor
     *
     * @param label string - text label for the element
     * @param bool required - is this a required element
     * @param int required - element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int maximum number of chars allowed to type in the field
     * @param int the minimum value allowable
     * @param int the maximum value allowable
     * @param boolean - add the range to the label automatically?
     *
     */
    function __construct($label, $required = TRUE, $width = NULL,
                           $maxlength = NULL, $min=0, $max=100, $label_flag=TRUE) {
        parent::__construct($label, $required, $width, $maxlength);
        $this->_min = $min;
        $this->_max = $max;
        $this->_label_flag = $label_flag;
    }    
    
    function get_label_text() {    
    	return $this->_label_text . "&nbsp;".$this->get_range_string();
    }



    /**
     * This function builds a string for the range display
     *
     * @return string
     */
    public function get_range_string($include_range=TRUE) {
        if ($include_range) {
            $str = $this->_range_text.": ";
        } else {
            $str = '';
        }

        return "(".$str.$this->_min."-".$this->_max.")";
    }

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_price().
     * @return void
     */
    public function validate() {
        Validator::is_range($this->get_value(), NULL, $this->_min, $this->_max);
    }
}

?>