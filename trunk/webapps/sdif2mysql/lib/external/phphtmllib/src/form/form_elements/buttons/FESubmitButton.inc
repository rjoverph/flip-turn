<?php
/**
 * This file contains the FESubmitButton class
 *
 * This is the SubmitButton FormElement which builds a
 * input field of type="submit". It has no validation method.
 *
 * NOTE: this also manages doing ajax submissions via the
 * phphtmllib framework's ajax code.
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
 * The normal submit button for a form
 * 
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
class FESubmitButton extends FEButton {

    protected $_type = 'submit';

    /**
     * The replacement div id
     * for the form target
     *
     */
    protected $id = NULL;

    /**
     * The success message to display
     */
    private $message = '';

    /**
     * This function return the javaScript code for
     * an onSubmit event
     *
     * @return string - javascript code
     */
    public function onSubmit() {
        return "document.getElementById('" . $this->get_element_id() . "').readonly=true;";
    }

    /**
     * This function creates element name
     * used in the form based on the text label
     * or any other parameters
     *
     */
    protected function create_element_name() {
        $this->set_element_name(FormProcessor::FORM_ACTION);
    }

    /**
     * This returns the initial value of
     * the element
     *
     * @return mixed
     */
    protected function get_init_value() {
        // always return button label as
        // the value
        return $this->get_label_text();
    }

    /**
     * This method is used to set the success
     * message to use.
     *
     * @param string
     */
    public function set_success_message($message) {
        $this->message = $message;
    }

}

?>