<?php
/**
 * This is the Email FormElement which builds a
 * text input field.
 * It validatest he data as is_email()
 *
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */

/**
 * This is the FEEmail FormElement which builds a
 * text input field.
 * It validates as is_email().
 *
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEEmail extends FEText {

    /** Holds the flag to indicate
      * whether we allow email in
      * the long name format like
      * Foo Bar <email@email.com>
      */
    protected $_allow_name = false;

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_email().
     *
     * @return void
     */
    public function validate() {
        NetworkValidator::is_email($this->get_value(), $this->_allow_name);
    }

    /**
     * Sets the flag to indicate
     * whether we allow email in
     * the long name format like
     * Foo Bar <email@email.com>
     *
     * @param bool
     */
    public function set_allow_name($flag) {
        $this->_allow_name = $flag;
    }
}

?>