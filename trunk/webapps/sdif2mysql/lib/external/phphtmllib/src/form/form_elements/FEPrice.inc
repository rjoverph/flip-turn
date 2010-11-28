<?php
/**
 * This file contains the FEPrice class
 *
 * $Id: FEPrice.inc 1821 2006-08-03 23:52:31Z hemna $
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
 * This is the Price FormElement which builds a
 * text input field.
 * It validates as is_price().
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEPrice extends FEText {

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_price().
     * @return void
     */
    public function validate() {
        Validator::is_price($this->get_value());
    }
}

?>