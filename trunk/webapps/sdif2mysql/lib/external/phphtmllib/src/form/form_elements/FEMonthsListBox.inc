<?php
/**
 * This file contains the FEMonthsListBox class
 *
 * $Id: FEMonthsListBox.inc 2410 2007-02-22 21:57:53Z hemna $
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
 * This class builds a FEDataList that shows a select box for Months of the year
 *
 * You should use the built in php 
 * @link http://www.php.net/manual/en/function.setlocale.php
 * function to affect the language used for the month list.
 *
 * @author Culley Harrelson <culley@fastmail.fm>
 * @see FEDate
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */

class FEMonthsListBox extends FEListBox {

    /**
     * The constructor
     *
     * @param string $label text label for the element
     * @param boolean $required is this a required element?
     * @param int $width element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int $height element height in px
     * @param string $format format should be F m or M:  Full month name, digit, abbreviated month name
     *
     */
    function __construct($label, $required = TRUE, $width = NULL, $height = NULL, $format = 'F') {

        // $format should be M m or F.  Default to F if the user passes in garbage.
        switch ($format) {
        case 'M':
            $format = '%b';
            break;
        case 'm':
            $format = '%m';
            break;
        default:
            $format = '%B';
            break;
        }

        for ($i = 1; $i < 13; $i++) {
            $months[$i] = strftime($format, strtotime("$i/12/2004"));
        }

        parent::__construct($label, $required, $width, $height, array_flip($months));


    }
}

?>
