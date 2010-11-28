<?php
/**
 * This file contains the FEHoursListBox class
 *
 * $Id: FEHoursListBox.inc 2399 2007-02-22 21:38:46Z hemna $
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
 * displaying Hours.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
class FEHoursListBox extends FEListBox {

    /**
     * Flag to tell us to use 12 or 24 hour format
     */
    protected $_extended_hours = TRUE;

    /**
     * The constructor
     *
     * @param string $label the label
     * @param boolean $required required flag or not
     * @param boolean $extended_hours show 24 hour format?
     */
    function __construct($label = 'Hours', $required = FALSE, $extended_hours = TRUE) {
        if ($extended_hours) {
            $hours = array('00'=>0, '01'=>1, '02'=>2, '03'=>3, '04'=>4, '05'=>5,
                           '06'=>6, '07'=>7, '08'=>8, '09'=>9, '10'=>10, '11'=>11,
                           '12'=>12, '13'=>13, '14'=>14, '15'=>15, '16'=>16, '17'=>17,
                           '18'=>18, '19'=>19, '20'=>20, '21'=>21, '22'=>22, '23'=>23);
        } else {
            $hours = array('00'=>0, '01'=>1, '02'=>2, '03'=>3, '04'=>4, '05'=>5,
                           '06'=>6, '07'=>7, '08'=>8, '09'=>9, '10'=>10, '11'=>11,
                           '12'=>12);
        }

        parent::__construct($label, $required, null, null, $hours);
    }
}

?>
