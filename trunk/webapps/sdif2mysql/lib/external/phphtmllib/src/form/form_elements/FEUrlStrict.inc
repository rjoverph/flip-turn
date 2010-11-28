<?php
/**
 * This file contains the FEUrlStrict class
 *
 * $Id: FEUrlStrict.inc 1823 2006-08-04 21:17:44Z hemna $
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
 * This is the URLStrict FormElement which builds a
 * text input field.
 * This is the same as FEUrl, but it requires the http://
 * It validates as is_strict_url().
 *
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEUrlStrict extends FEText {

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_strict_url().
     * @return void
     */
    public function validate() {
        NetworkValidator::is_strict_url($this->get_value());
    }
}

?>