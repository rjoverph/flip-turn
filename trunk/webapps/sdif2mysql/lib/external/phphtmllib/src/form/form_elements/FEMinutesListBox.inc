<?php
/**
 * This file contains the FEMinutesListBox class
 *
 * $Id: FEMinutesListBox.inc 2399 2007-02-22 21:38:46Z hemna $
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
 * displaying Minutes.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
class FEMinutesListBox extends FEListBox {

    /**
     * The constructor
     *
     * @param string the label (default = 'Minutes')
     * @param boolean required flag or not
     */
    function __construct($label = 'Minutes', $required = FALSE) {
        $minutes = array('00'=>0, '01'=>1, '02'=>2, '03'=>3, '04'=>4, '05'=>5,
                         '06'=>6, '07'=>7, '08'=>8, '09'=>9, '10'=>10);

        for($x=11;$x<=59;$x++) {
            $minutes[$x]=$x;
        }

        parent::__construct($label, $required, null, null, $minutes);
    }
}

?>