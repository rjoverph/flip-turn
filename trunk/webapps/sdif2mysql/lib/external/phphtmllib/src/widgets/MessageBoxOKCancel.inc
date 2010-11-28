<?php
/**
 * This file contains the ButtonPanelCSS
 * object
 * 
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */

/**
 * This is a class for building a MessageBox with
 * an OK and Cancel button.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */
class MessageBoxOKCancel extends MessageBoxOK {
    /**
     *
     * @param string the title
     * @param string the width
     * @param string the message for the box
     * @param string the ok action to perform.  history.back() by default
     * @param string the cancel action to perform.  history.back() by default
     * @param array an array of hidden form variables to post along with
     *              the form.
     */
    function __construct($title, $width, $message,
                                $ok_action = "",
                                $cancel_action = "javascript: history.back();",
                                $hidden_values = array()) {
        parent::__construct($title, $width, $message, $ok_action);
        $this->add_button("Cancel", $ok_action);
        $this->add_hidden_variables($hidden_values);
    }
}
?>
