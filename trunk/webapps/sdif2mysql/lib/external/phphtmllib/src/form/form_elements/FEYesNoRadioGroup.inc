<?php
/**
 * This file contains the FEYesNoRadioGroup class
 *
 * $Id: FEYesNoRadioGroup.inc 1747 2006-06-07 21:25:42Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * This is the Yes/No Radio Button Group FormElement.
 * It builds a FERadioGroup with 2 radio buttons labeled
 * "Yes" and "No".
 *
 * It has no validation method.
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEYesNoRadioGroup extends FERadioGroup {

    /**
     * The constructor
     *
     * @param label string - text label for the element
     * @param bool required - is this a required element
     * @param string - the value to use for the 'yes' radio
     *                 NOTE: default is 'yes'
     * @param string - the value to use for the 'no' radio
     *                 NOTE: default is 'no'
     */
    function __construct($label, $required = TRUE,
                         $yes_value="yes", $no_value="no") {

        $datalist = array('Yes' => $yes_value,
                          'No' => $no_value);
        parent::__construct($label, $datalist, $required);
    }
}

?>