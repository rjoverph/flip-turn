<?php
/**
 * This file contains the FEListBox, FEMultiListBox
 *
 * $Id: FEWeekdaysListBox.inc 2399 2007-02-22 21:38:46Z hemna $
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
 * This Form Element builds a list box of the days of the week.
 *
 * Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
class FEWeekdaysListBox extends FEListBox {

    protected $_weekdays = array('Sunday' => 0,
                                 'Monday' => 1,
                                 'Tuesday' => 2,
                                 'Wednesday' => 3,
                                 'Thursday' => 4,
                                 'Friday' => 5,
                                 'Saturday' => 6);

    function __construct($label='Weekdays', $required=FALSE) {
        parent::__construct($label, $required, null,null, $this->_weekdays);
    }
}

?>