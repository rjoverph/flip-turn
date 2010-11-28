<?php
/**
 * This file contains the FEActionButton class
 *
 * $Id: FEActionButton.inc 1594 2005-09-29 23:27:42Z suren2 $
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
 * This is the button FormElement which builds a
 * input field of type="button". It has no validation method.
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEActionButton extends FEButton {

    /**
     * Holds the button action
     *
     */
    protected $_action;

    /**
     * Holds the type of the button
     */
    protected $_type = 'button';

    /**
     * The constructor
     *
     * @param string label text label for the element
     * @param string $value button text
     * @param string $action action to perform
     */
    function __construct($label, $action = NULL) {
        parent::__construct($label);

        $this->_action = $action;
    }

    /**
     * This function return the javaScript code for
     * an onClick event
     *
     * @return string - javascript code
     */
    protected function onClick() {
        return $this->_action;
    }

}

?>