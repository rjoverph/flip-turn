<?php
/**
 * This file contains the FEYearsListBox class
 *
 * $Id: FEYearsListBox.inc 2399 2007-02-22 21:38:46Z hemna $
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
 * This class builds a FEDataList that shows a select box listing a range of years
 *
 * @author Culley Harrelson <culley@fastmail.fm>
 * @see FEDate
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 */

class FEYearsListBox extends FEListBox {

    /**
     * The constructor
     *
     * @param string text label for the element
     * @param boolean is this a required element?
     * @param int element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int element height in px
     * @param int min_year
     * @param int max_year
     */
    function __construct($label, $required = TRUE, $width = NULL, $height = NULL, $min_year = 2006, $max_year = 2010) {
        // this will be cleaner in php5 with array_combine()
        $list = range($min_year, $max_year);
        $years = array_combine($list, $list);
        parent::__construct($label, $required, $width, $height, $years);
    }
}

?>