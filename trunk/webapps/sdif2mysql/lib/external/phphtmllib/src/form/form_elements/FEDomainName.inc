<?php
/**
 * This file contains the FEDomainName class
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
 * This is the DomainName FormElement which builds a
 * text input field.
 * It validates as is_domainname().
 *
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEDomainName extends FEText {

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_domainname().
     * 
     * @return void
     */
    public function validate() {
        NetworkValidator::is_domainname($this->get_value());
    }
}

?>