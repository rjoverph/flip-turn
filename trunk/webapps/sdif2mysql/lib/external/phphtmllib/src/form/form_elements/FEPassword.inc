<?php
/**
 * This file contains the Password FormElement class.
 *
 * $Id: FEPassword.inc 2855 2007-08-03 18:47:21Z hemna $
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
 * This is the Password FormElement which builds a
 * input field of type="password".  It validates
 * the data as is_password().
 *
 * NOTE: this is used in conjunction with the
 *       FEConfirmPassword object to ensure the
 *       user's input is what they wanted.
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEPassword extends FEText {

    /**
     * Try and save the password
     * and reset it on error?
     */
    private $keep_password = FALSE;

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    function get_element() {
        $attributes = $this->build_element_attributes();
        $attributes["type"] = "password";
        if ($this->keep_password) {
            $attributes["value"] = $this->get_value();
        } else {
            $attributes["value"] = '';
        }


        $c = Container::factory(new INPUTtag($attributes));

        if ($this->_js_validation_enabled && $this->js_validate()) {
            // add div for js errors
            $c->add(new DIVtag(array('id' => 'error' . $this->get_element_id(),
                                     'class' => 'inlineError',
                                     'style' => 'display:none;')));
        }
        return $c;
    }


    /**
     * return a string to the user for the
     * confirmation page
     *
     * @return string
     */
    function get_value_text() {
        return str_repeat('*', strlen($this->get_value()));
    }

    /**
     * This function performs the actual validation
     * It is called only if the validation is required by
     * this element
     *
     * This function is responsible for performing complete
     * validation and setting the appropriate error message
     * in case of a failed validation
     *
     * @return void
     */
    public function validate() {
        Validator::is_password($this->get_value());
    }


    /**
     * Should we try and keep the password
     * during an error and reset it?
     *
     * @param boolean $flag
     */
    public function keep_password($flag=TRUE) {
        $this->keep_password = $flag;
    }
}
?>
