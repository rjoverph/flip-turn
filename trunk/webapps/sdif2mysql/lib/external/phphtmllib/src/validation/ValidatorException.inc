<?php
/**
 * Validation exception
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Validation
 */


/**
 * This class contains the Validation exception
 * error codes.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Validation
 */
class ValidatorException extends phphtmllibException {

    /**
     * All of the possible Validator Exception codes
     */

    /**
     * store a label to associate w/ the exception
     * to support custom labels in the form engine.
     */
    private $label = NULL;

    const ERR_OK = 0;
    const ERR_EMPTY = 1;
    const ERR = 2;


    /**
     * constructor so we can pass a label
     * to support the form engine
     *
     * @param string $message
     * @param int $code
     * @param string $label
     *
     */
    function __construct($message = null, $code = 0, $label = NULL) {
       parent::__construct($message, $code);
       $this->label = $label;
    }

    /**
     * Get the label (if any)
     *
     * @return string or NULL
     */
    public function get_label() {
        return $this->label;
    }

    public function get_extra_as_string() {
        return "Error (".$this->getCode().") : ".$this->getMessage();
    }

}

?>