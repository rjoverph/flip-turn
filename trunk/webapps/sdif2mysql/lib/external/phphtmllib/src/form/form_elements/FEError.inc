<?php
/**
 * This file contains the FEError class
 *
 * $Id: FEError.inc 1821 2006-08-03 23:52:31Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * This is a way of providing an Error to the FormProcessor.
 * It can be used at any time during FormContent to create
 * a specialized error field and message.
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEError extends FormElement {

    /**
     * The constructor
     *
     * @param string the error label
     * @param string the error message
     */
    function __construct($label, $message) {
        $this->set_label_text($label);
        $this->set_error_message($message);
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
     * Internally use the Validator object to
     * test.  If an error occurs throw a ValidatorException.
     */
    public function validate() {
        throw new ValidatorException($this->get_error_message());
    }

}

?>