<?php
/**
 * This file contains the FEName class
 *
 * $Id: FEName.inc 1821 2006-08-03 23:52:31Z hemna $
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
 * This is the Name FormElement which builds a
 * text input field, and validates against the
 * is_name() method.
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEName extends FEText {

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_name().
     * @return void
     */
    public function validate() {
        Validator::is_name($this->get_value());
    }
}

?>