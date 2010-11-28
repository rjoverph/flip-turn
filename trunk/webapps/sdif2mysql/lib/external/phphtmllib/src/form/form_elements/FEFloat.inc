<?php
/**
 * This file contains the FEFloat class
 *
 * $Id: FEFloat.inc 1821 2006-08-03 23:52:31Z hemna $
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
 * This is the float FormElement which builds a
 * text input field.
 * It validates as is_float().
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEFloat extends FEText {

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_float().
     * @return void
     */
    public function validate() {
        Validator::is_float($this->get_value());
    }
}

?>