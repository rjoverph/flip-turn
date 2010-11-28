<?php
/**
 * This file contains the FEIPAddressWithPort class
 *
 * $Id: FEIPAddressWithPort.inc 1823 2006-08-04 21:17:44Z hemna $
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
class FEIPAddressWithPort extends FEHostNameWithPort {

    /**
     * this validates the ip address field only
     *
     * @param string $value the ip.
     * @return void
     */
    protected function _validate_hostname($value) {
        NetworkValidator::is_ip($value);
    }
}

?>