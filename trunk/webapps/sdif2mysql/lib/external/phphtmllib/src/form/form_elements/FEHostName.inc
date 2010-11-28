<?php
/**
 * This file contains the FEHostName class
 *
 * $Id: FEDomainName.inc 1823 2006-08-04 21:17:44Z hemna $
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
 * This is the HostName FormElement which builds a
 * text input field.
 * It validates as NetworkValidator::is_hostname().
 *
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEHostName extends FEText {

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_hostname().
     * 
     * @return void
     */
    public function validate() {
        NetworkValidator::is_hostname($this->get_value());
    }
}

?>