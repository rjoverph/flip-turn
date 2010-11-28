<?php
/**
 * This file contains the MessageBoxOK widget
 * 
 * 
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */

/**
 * This is a class for building a MessageBox with
 * an OK button.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */
class MessageBoxOK extends MessageBoxWidget {
    /**
     *
     * @param string the title
     * @param string the width
     * @param string the message for the box
     * @param string the ok action to perform.  history.back() by default
     * @param array an array of hidden form variables to post along with
     *              the form.
     */
    function __construct($title, $width, $message,
                          $ok_action = "javascript:history.back();",
                          $hidden_values = array()) {
        parent::__construct($title, $width, $message);
        $this->add_button("OK", $ok_action);
        $this->add_hidden_variables($hidden_values);
    }
}
?>
