<?php
/**
 * This file contains the FEZipcode class
 *
 * $Id: FEZipcode.inc 2399 2007-02-22 21:38:46Z hemna $
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
 * This is the FEZipcode class.
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
class FEZipcode extends FEText {
    /**
     * The constructor
     *
     * @param label string - text label for the element
     * @param bool required - is this a required element
     * @param int required - element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int required - maximum number of chars allowed to type in
     */
    function __construct($label, $required=false, $width = NULL, $maxlength = 5) {
        parent::__construct($label, $required, $width, $maxlength);
    }


    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_name().
     * @return void
     */
    public function validate() {
        Validator::is_zip($this->get_value());
    }
}

?>