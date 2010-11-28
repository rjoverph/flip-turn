<?php
/**
 * This file contains the FEDays class
 *
 * $Id: FEDaysListBox.inc 2399 2007-02-22 21:38:46Z hemna $
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
 * This class builds a FEDataList that shows a select box listing the days of the month
 *
 * @author Culley Harrelson <culley@fastmail.fm>
 * @see FEDate
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 */
class FEDaysListBox extends FEListBox {

    /**
     * The constructor
     *
     * @param string text label for the element
     * @param boolean is this a required element?
     * @param int element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int element height in px
     */

    function __construct($label, $required = TRUE, $width = NULL, $height = NULL){

        // this will be cleaner in php5 with array_combine()
        $list = range(1, 31);
        foreach ($list as $day) {
            // pad the single digit days with zeros
            $new_day = sprintf('%02d', $day);
            $days[$new_day] = $day;
        }
        parent::__construct($label, $required, $width, $height, $days);


    }
}

?>