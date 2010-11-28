<?php
/**
 * This contains the TextNav widget
 *
 * $Id: MessageBoxWidget.inc 2738 2007-05-16 06:03:02Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 *
 */


/**
 * This is the MessageBoxWidget
 * 
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */
class MessageBoxWidget extends StandardDialogWidget {

    /**
     * The _message to display
     */
    var $_message = NULL;

    /**
     * Do we need to render a form?
     *
     */
    var $_has_form = FALSE;

    /**
     * The form method type
     * GET or POST only
     */
    var $_form_method = "POST";

    /**
     * This stores additionnal hidden variables.
     */
    var $_hidden_vars = array();

    /**
     * constructor
     *
     * @param string - the title of the window
     * @param mixed - the width of the object
     * @param string - the message string
     */
    function __construct($title, $width="600", $message="") {
        $this->set_message($message);
        parent::__construct($title, $width, 'center');
    }

    /**
     * We override the render function
     * because we want to wrap the table
     * inside a form tag
     */
    function render($indent_level=1, $output_debug=0) {

        // add the messages
        $this->add_block(NULL, $this->get_message());

        if ($this->_has_form) {
            // we need to render a form
            $form = new FORMtag(array("method" => $this->_form_method,
                                      "action" => $_SERVER["PHP_SELF"]));

            $form->add(parent::render($indent_level, $output_debug));

            $vars = array_merge($_REQUEST, $this->_hidden_vars);
            foreach ($vars as $key=>$value) {
                if (is_array($value)) {
                    foreach ($value as $k => $v) {
                        $form->add(form_hidden($key."[".$k."]", $v));
                    }
                } else {
                    $form->add(form_hidden($key, $value));
                }
            }

            return $form->render($indent_level, $output_debug);
        }

        else return parent::render($indent_level, $output_debug);

    }

    /**
     * This sets the _message for the _message
     * window.
     *
     * @param string - the _message to display
     */
    function set_message($mesg) {
        $this->_message = $mesg;
    }

    /**
     * Gets the current value of the _message
     *
     * @return string
     */
    function get_message() {
        if (is_string($this->_message))
            return str_replace("\n", "<br>", $this->_message);
        else
            return $this->_message;
    }

    /**
     * Add a single extra hidden variable
     *
     * @param string - key of the hidden variable
     * @param string - value of the variable
     */
    function add_hidden_variable($key, $value) {
        $this->_hidden_vars[$key] = $value;
    }

    /**
     * Add extra hidden variables
     *
     * @param array an array of key => value hidden
     *              variables
     * @return none
     */
    function add_hidden_variables($vars) {
        if (!empty($vars)) {
            foreach( $vars as $key => $value) {
                $this->_hidden_vars[$key] = $value;
            }
        }
    }

    /**
     * Adds a single button to the dialog
     * that will be display at the bottom
     * of the widget
     *
     * @param string - button title
     * @param string - button action, if NULL, then submit button is created
     * @access public
     */
    function add_button($title, $action=NULL) {

        if ((strstr($action, ".php") || strstr($action, ".html")) && !strstr($action, "javascript")) {
            if (strstr($action, "&")) {
                $js = "window.location='" . $action ."'";
            } else {
                $js = "document.forms[0].action='".$action . "';";
                $js .= "document.forms[0].submit();";

                $this->_has_form = TRUE;
            }
            $action = "javascript: ".$js;
        } else {
            $action = $action;
        }

        if (empty($action)) {
            $action = "document.forms[0].submit();";
            $this->_has_form = TRUE;
        }

        parent::add_button($this->form_action_button($title, $action));
    }

    /**
     * build an tag of type button
     * which executes a javaScript function
     *
     * @param string  $content
     * @param string  $action
     * @param array  $attrib - additional attributes
     *
     * @return object
     */
    function form_action_button($content, $action = NULL, $attrib = NULL) {
        $attributes = array("type" => "button",
                            "value" => $content);
        if (!isset($attrib["style"])) {
            $attributes["style"] = "width:90px;";
        }

        $attributes["onclick"] = $action;

        if ($action) $attributes["type"] = "button";
        else $attributes["type"] = "submit";

        if (is_array($attrib)) {
            $attributes = array_merge($attributes, $attrib);
        }

        $button = new INPUTtag($attributes);

        return $button;
    }
}

?>
