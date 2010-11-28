<?php
/**
 * This file contains the FERegEx class
 *
 * $Id: FERegEx.inc 1821 2006-08-03 23:52:31Z hemna $
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
 * This is the RegEx FormElement which builds a text input field, and validates
 * against the is_regex() method.
 *
 * Example as it would appear in FormContent::form_init_elements():
 * <code>
 *      $this->add_element( new FERegEx("FERegEx label", false, '200px', 3, '/^pattern to match$/', 'error message when pattern does not match') );
 * </code>
 *
 * @author Culley Harrelson <culley@fastmail.fm>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FERegEx extends FEText {

    private $_regex;
    protected $_error_message;

    /**
     * The constructor
     *
     * @param label string - text label for the element
     * @param required bool- is this a required element
     * @param width int - element width in characters, pixels (px), percentage (%) or elements (em)
     * @param maxlength int- maximum number of chars allowed to type in
     * @param regex string - a valid regular expression i.e. '/[a-z]+$/i'
     * @param error_message string - error message for failure to match the regex
     */
    function __construct($label, $required=false, $width = NULL, $maxlength = NULL, $regex, $error_message) {
        parent::__construct($label, $required, $width, $maxlength);
        $this->_regex = $regex;
        $this->_error_message = $error_message;
    }

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_regex().
     * 
     * @return void
     */
    public function validate() {
        Validator::is_regex($this->_regex, $this->get_value());
    }
}

?>