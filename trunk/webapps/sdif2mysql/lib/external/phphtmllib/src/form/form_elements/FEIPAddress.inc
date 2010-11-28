<?php
/**
 * This file contains the FEIPAddress class
 *
 * $Id: FEIPAddress.inc 1823 2006-08-04 21:17:44Z hemna $
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
 * This is the Ip Address FormElement which builds a
 * text input field.
 * It validates as is_ip().
 *
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEIPAddress extends FEText {

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_ip().
     * @return void
     */
    public function validate() {
        NetworkValidator::is_ip($this->get_value());
    }
}

?>