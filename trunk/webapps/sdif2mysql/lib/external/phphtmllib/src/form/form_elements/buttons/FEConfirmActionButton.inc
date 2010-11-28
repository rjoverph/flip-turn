<?php
/**
 * This file contains the FEConfirmActionButton class
 *
 * $Id: FEConfirmActionButton.inc 1573 2005-09-19 20:58:11Z suren2 $
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
 * This builds a button that will do a JS popup
 * question, asking for yes/no.  if yes, it submits
 * the form.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEConfirmActionButton extends FEButton {

    function __construct($label, $value, $message = NULL, $width = NULL, $height = NULL) {
        $action = "if (confirm('".$message."')) {this.form.".FORM_ACTION.".value='".$value."'; submit();}";
        parent::__construct($label, $value, $action, $width, $height);
    }
}

?>