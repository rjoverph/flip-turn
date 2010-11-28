<?php
/**
 *
 * $Id: ErrorBoxWidget.inc 2736 2007-05-16 06:02:12Z hemna $
 *
 * This file contains the ErrorBoxWidget object
 * that is used to display an 'error' display
 * widget in the UI.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */



/**
 * This class is for displaying a standardized
 * look and feel for an 'error' display.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */
class ErrorBoxWidget extends HTMLWidget {

    /**
     * This is the message that gets displayed
     * underneath the image and before the
     * list of errors
     */
    protected $_message = "Please review the following error(s) below.";

    /**
     * The constructor
     *
     * @param string the title used in the error box
     *        Default = 'Errors'
     * @param string the width of the entire object
     */
    public function __construct($title="Error", $width="100%", $align = null) {
        parent::__construct();

        $this->set_title($title);
        $this->set_width($width);
        if ($align !== null) {
            $this->set_align($align);
        }
    }

    /**
     * This method is for changing the default
     * message that gets displayed before the
     * list of errors
     *
     * @param string the message you want displayed
     */
    public function set_message($message) {
        $this->_message = $message;
    }


    /**
     * This method is used to add individual
     * errors.
     *
     * @param string the label for the error
     * @param string the actual error message
     */
    public function add($label, $message) {
        $this->data[] = array('label' => $label,
                              'message' => $message);
    }


    /**
     * This is called to generate the resulting html
     * output
     *
     * @param int
     * @param int
     */
    public function render($indent_level=0, $output_debug=0) {
        $table = TABLEtag::factory($this->get_width(), 0, 0, 2, $this->get_align());
        $table->set_tag_attribute('class', 'errorbox');

        //build the big header and the generic message
        $td = new TDtag(array('colspan' => 2, 'class' => 'errorseparator'),
                        IMGtag::factory($this->_image_prefix.'/icon_alert_triangle.gif'),
                        SPANtag::factory('errortitle', $this->get_title()));

        //generic TEXT
        $td->add(DIVtag::factory('errormessage',$this->_message));
        $table->add_row( $td );

        //walk each visible form element and see if there is an error in it
        foreach( $this->data as $error ) {
            $table->add_row(new TDtag(array('class' => 'errorcell',
                                            'nowrap',
                                            'style' => 'padding-right:10px;'),
                                      $error['label']),

                            new TDtag(array('class' => 'errorcell',
                                            'width' => '90%'),
                                      $error['message']));
        }

        return $table->render($indent_level, $output_debug);
    }
}

?>
