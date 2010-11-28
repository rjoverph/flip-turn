<?php
/**
 * This file holds the babw Standard Form Content
 * which is a child of the FormContent object.
 *
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */

/**
 * This provides a "standard" look for the outer
 * wrapper for all forms.
 * All forms have a Save and Cancel button, as well
 * as a Confirmation of the Form.
 *
 *
 * This is a child of the FormContent class to
 * provide a 'standard' look and feel for forms.
 * It also enables a confirmation 'page' by default.
 *
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
abstract class StandardFormContent extends FormContent {

    /**
     * The title used in the wrapping table
     *
     */
    protected $_form_title = "";

    /**
     * the InfoTable wrapper that holds
     * all fields.
     */
    protected $_infotable = NULL;

    /**
     * Allow the default buttons to be shown?
     */
    protected $_allow_actions = TRUE;

    /**
     * The wizard id associated with this content
     * if we are being used inside a wizard
     */
    protected $_wizard_id = NULL;

    protected $_width = '100%';

    /**
     * The constructor
     *
     * @param string $title the title of the form
     * @param string $cancel_action the action to take for canceling (js)
     * @param string $width the overall width of the form.
     */
    public function __construct($title, $cancel_action=NULL, $width="96%") {
        parent::__construct($cancel_action);
        $this->set_form_title( $title );
        $this->set_width($width);
        //each form has a confirmation
        $this->set_confirm(TRUE);
    }

    /**
     * this method sets the form title
     * which is used to wrap the entire form
     *
     * @param string - the form title
     */
    public function set_form_title($title) {
        $this->_form_title = $title;
    }

    /**
     * this builds the main wrapper for the
     * form fields and ads the Save and Cancel buttons
     *
     * @param array - the form data
     * @param array - the form error fields (if any)
     * @return InfoTable widget object
     */
    public function form() {
        $title = $this->_form_title.phphtmllib::_HTML_SPACE;
        $title .="( ".$this->_required_field_marker." ".$this->_required_field_text." )";
        $this->_infotable = new InfoTable($title, $this->_width);
        $this->_infotable->set_cellpadding(0);

        //ok call the Child class to add the
        //form fields inside of form blocks
        $this->form_content();

        if ($this->_allow_actions) {
            $this->_infotable->add_row( $this->form_content_buttons() );
        }

        return $this->_infotable;
    }

    /**
     * Child class MUST override this
     * to provide the form fields
     *
     * @return object
     */
    abstract protected function form_content();

    /**
     * This method is used to set the
     * default form submit buttons in this
     * form.
     *
     */
    public function form_init_buttons() {

        $this->add_button( new FESubmitButton(self::BUTTON_SAVE) );

        //form confirmation
        $this->add_confirm_button( new FESubmitButton(self::BUTTON_EDIT) );
        $this->add_confirm_button( new FESubmitButton(self::BUTTON_CONFIRM) );

        $this->add_button( $this->get_cancel() );
    }

    /**
     * This function is used to show an intermediary
     * confirmation page.  Use this function to
     * show a confirmation of the data that was
     * submitted by the user.
     * This will get called after all of the
     * form data was successfully validated.
     * All of the form data will automatically
     * be created as hidden form fields. All you
     * have to do is show the data, and a confirm
     * submit button.
     *
     * @param string - the title for the table
     * @param boolean - show the action buttons?
     * @return mixed - either raw html, or some
     *                 container HTMLTag object.
     */
    public function form_confirm( $title = "Form Confirmation", $show_buttons=TRUE ) {
        $title = $title.phphtmllib::_HTML_SPACE;

        //only show this if we aren't readonly
        //if we are in read only mode...required doesn't make sense
        if (!$this->is_readonly()) {
            $title .="( ".$this->_required_field_marker." ".$this->_required_field_text." )";
        }

        $table = new InfoTable($title, $this->_width);

        $this->build_confirm_table( $table );

        if ($show_buttons) {
            $table->add_row( new TDtag(array('colspan' => 2),
                                       $this->form_confirmation_buttons()));
        }

        return $table;
    }

    /**
     * This method handles the form action.
     *
     * @return boolean TRUE = success
     *                 FALSE = failed.
     */
    public function form_action() {
        switch ($this->get_action()) {
        case "Edit":
            return FALSE;
            break;

        case "Confirm":
            return $this->confirm_action();
            break;
        }
    }

    /**
     * This method is responsible for handling the
     * confirmation page's Confirm action.
     */
    public function confirm_action() {
        user_error("FormContent::confirm_action() - Child class must override");
        return FALSE;
    }

    /**
     * This function is used to build the standard
     * buttons for a form.
     *
     * @return DIVtag
     */
    protected function form_content_buttons() {
        //$save = new FESubmitButton('Save');
        $div = new DIVtag( array("style" => "background-color: #eeeeee;".
                                            "padding-top:5px;padding-bottom:5px",
                                 "align"=>"center", "nowrap"));

        foreach( $this->_buttons[self::FETYPE_BUTTON] as $name => $button) {
            $div->add($this->get_button($name), phphtmllib::_HTML_SPACE);
        }

        return $div;
    }

    /**
     * This function is used to build the standard
     * buttons for a form.
     *
     * @return DIVtag
     */
    public function form_confirmation_buttons() {
        //$save = new FESubmitButton('Save');
        $div = new DIVtag( array("style" => "background-color: #eeeeee;".
                                            "padding-top:5px;padding-bottom:5px",
                                 "align"=>"center", "nowrap"));

        foreach( $this->_buttons[self::FETYPE_CONFIRM_BUTTON] as $name =>$button) {
            $div->add($this->get_confirm_button($name), phphtmllib::_HTML_SPACE);
        }

        if ($this->_cancel_action) {
            $div->add(phphtmllib::_HTML_SPACE, $this->get_button(self::BUTTON_CANCEL));
        }

        return $div;
    }

    /**
     * This function is used to add a block of
     * form fields inside a table to this form.
     * This table will automatically get wrapped
     * inside a fieldset with a legend tag
     * to label the block
     *
     * @param string - the title for the fieldset
     * @param TABLEtag - the form fields inside a table
     */
    protected function add_form_block( $title=NULL, &$table ) {
        $this->_infotable->add_row( $this->build_form_block( $title, $table ) );
    }

    /**
     * this builds a fieldset and legend and adds the
     * form table to it.
     *
     * @param string - the legend string
     * @param TABLEtag - the form fields in a table
     * @return FIELDSETtag
     */
    protected function &build_form_block( $title=NULL, &$content ) {
        $div = &$this->_div_wrapper( );

        if ($title != NULL) {
            $fs = html_fieldset( $title );
            $fs->add( $content );
            $div->add( $fs );
        } else {
            $div->add( $content );
        }
        return $div;
    }

    protected function &_div_wrapper() {
        $div = html_div();
        $div->set_style("background-color: #eeeeee;padding:5px;");
        return $div;
    }

    protected function _form_content_table($width="100%", $border=0, $cellspacing=0,
                                 $cellpadding=3) {
        $table = html_table($width,$border,$cellspacing,$cellpadding);
        return $table;
    }

    /**
     * This method sets the wizard id.
     * This is called from the FormWizard class
     *
     * @param string
     */
    public function set_wizard_id($id) {
        $this->_wizard_id = $id;
    }

    /**
     * This method gets the wizard id.
     *
     * @return string
     */
    public function get_wizard_id() {
        return $this->_wizard_id;
    }

    /**
     * This method is used to set the width of
     * the form content
     *
     * @param int $width
     */
    public function set_width($width) {
        $this->_width = $width;
    }
}

?>