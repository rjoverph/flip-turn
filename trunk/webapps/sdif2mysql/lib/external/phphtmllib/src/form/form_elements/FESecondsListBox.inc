<?php
/**
 * This file contains the FESecondsListBox class
 *
 * $Id: FESecondsListBox.inc 2399 2007-02-22 21:38:46Z hemna $
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
 * this class is used for building a listbox for
 * displaying Seconds.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
class FESecondsListBox extends FEMinutesListBox {

    /**
     * The constructor
     *
     * @param string $label the label (default = 'Seconds')
     * @param boolean $required required or not
     */
    function __construct($label = 'Seconds', $required = FALSE) {
        parent::__construct($label, $required);
    }
}

?>