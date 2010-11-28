<?php
/**
 * This file contains the FEEmailMany class
 *
 * $Id: FEEmailMany.inc 1823 2006-08-04 21:17:44Z hemna $
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
 * This is the EmailMany FormElement which builds a
 * text input field.  This allows for multiple email
 * addresses in 1 text input field seperated by commas.
 *
 * It validatest he data as is_manyemails()
 *
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEEmailMany extends FEText {

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_manyemails().
     * @param FormValidation object.
     */
    public function validate() {
        NetworkValidator::is_manyemails($this->get_value());
    }
}

?>