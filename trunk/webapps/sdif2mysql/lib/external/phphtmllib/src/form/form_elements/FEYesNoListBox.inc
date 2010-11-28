<?php
/**
 * This file contains the FEYesNoListBox
 *
 * $Id: FEYesNoListBox.inc 2129 2006-10-06 17:34:12Z hemna $
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
 * Build a Yes/No Select box
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEYesNoListBox extends FEListBox {

    protected $options = array("Yes" => 1, "No" => 0);

    /**
     * The Constructor
     *
     * @param label string - text label for the element
     * @param bool required - is this a required element
     * @param array data_list - list of data elements (name=>value)
     * @param int required - element width in characters, pixels (px), percentage (%) or elements (em)
     *
     */
    function __construct($label, $required = TRUE, $width = NULL, $height = NULL) {

        parent::__construct($label, $required, $width, $height, $this->options);
    }
}

?>
