<?php
/**
 * This file contains the FEUrl class
 *
 * $Id: FEUrl.inc 1823 2006-08-04 21:17:44Z hemna $
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
 * This is the URL FormElement which builds a
 * text input field.
 * It validates as is_url().
 *
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEUrl extends FEText {

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_url().
     * @return void
     */
    public function validate() {
        NetworkValidator::is_url($this->get_value());
    }
}

?>