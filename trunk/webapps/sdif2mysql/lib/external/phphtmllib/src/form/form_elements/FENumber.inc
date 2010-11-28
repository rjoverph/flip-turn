<?php

/**
 * This file contains the FENumber class
 *
 * $Id: FENumber.inc 1821 2006-08-03 23:52:31Z hemna $
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
 * This is the FormElement which builds a
 * text input field that validates
 * It validates as is_number().
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FENumber extends FEText {

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_float().
     * @return void
     */
    public function validate() {
        Validator::is_number($this->get_value());
    }
}

?>