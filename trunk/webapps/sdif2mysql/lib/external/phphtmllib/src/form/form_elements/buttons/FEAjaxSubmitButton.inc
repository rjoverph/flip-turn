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
 * This class builds a submit button using ajax
 *
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
class FEAjaxSubmitButton extends FESubmitButton {

    protected $_type = 'button';

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
        return null;
    }

    /**
     * This function return the javaScript code for
     * an onClick event
     *
     * @return string - javascript code
     */
    public function onClick() {
        return "this.form._form_action.value='".$this->get_value()."';".
               'ar_fp_u(this.form,\''.$this->get_ajax_replacement_divid() .
                '\');' .
                "$('" . $this->get_element_id() . "').disabled=true;";

    }

    /**
     * This function creates element name
     * used in the form based on the text label
     * or any other parameters
     *
     */
    protected function create_element_name() {
        $this->set_element_name($this->_sanitize_string($this->get_label_text()));
    }

    /**
     * set the div id to replace
     *
     * @param string $id
     */
    public function set_ajax_replacement_divid($id) {
        $this->id = $id;
    }

    /**
     * gets the div id to use.
     *
     * @return string
     */
    public function get_ajax_replacement_divid() {
        if (!$this->id) {
            $this->id = 'id' . $this->_form_name;
        }
        return $this->id;
    }
}


?>