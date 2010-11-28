<?php
/**
 * This file contains the FEConfirmSubmitButton
 * which allows a confirmation js dialog
 * prior to submitting the action.
 * 
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */



/**
 * This is the SubmitButton FormElement which builds a
 * input field of type="submit". It has no validation method.
 * It provides a confirmation js dialog prior to submitting
 * the action.
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */

class FEConfirmSubmitButton extends FESubmitButton {

    /**
     * stores the message to display in the js
     * popup confirmation.
     * @var string
     */
    protected $message = "Are you Sure?";

    /**
     * constructor to pass in confirmation message
     * 
     * @param label string - text label for the element
     * @param bool required - is this a required element
     * @param int required - element width in pixels (px), percentage (%) or elements (em)
     * @param int required - element height in pixels (px), percentage (%) or elements (em)
     * @param string $message - the confirmation message to display
     */
    public function __construct($label, $required=TRUE, $width=NULL, $height=NULL, $message="Are you Sure?") {
        parent::__construct($label, $required, $width, $height);
        $this->message = $message;
    }

    /**
     * build the element
     * 
     * @return BUTTONtag object
     */
    public function get_element() {
        $button = parent::get_element();

        //ok now add the confirmation.
        $old_onclick = $button->get_tag_attribute('onclick');
        $click = "if (!confirm('".addslashes($this->message)."')) return false;".$old_onclick;
        $button->set_tag_attribute('onclick', $click);

        return $button;
    }

}
?>
