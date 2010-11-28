<?php
/**
 * AjaxStandardFormContent
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage FormEngine
 */


/**
 * This class is a child of phphtmllib's StandardFormContent
 * class to provide an Ajax version of the
 * StandardFormContent object.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage FormEngine
 */
abstract class AjaxStandardFormContent extends StandardFormContent implements Ajaxable {

    /**
     * Tell the form block to wrap the block in
     * a fieldset or not.
     */
    private $_fieldset_block = TRUE;

    /**
     * Id of the main object
     * that is used on this form
     *
     * @var int
     */
    protected $id;

    /**
     * Are we using ajax
     */
    protected $ajax = 1;

    protected $ajax_divid = 'pageBody';
    protected $ajax_target = NULL;

    /**
     * This member says we need to
     * render as part of an ajax
     * request
     */
    protected $ajax_mode = FALSE;

    /**
     * Constuctor
     *
     * @param string $title
     * @param string $cancel_action
     * @param string $width
     */
    public function __construct($title = 'form', $cancel_action=NULL, $width="96%") {
        $this->ajax_target = $cancel_action;
        $rb = $this->get_request_builder();
        $cancel_url = $rb->get_url();

        // assign the object id (if any)
        $this->id = Request::singleton()->get('id');

        parent::__construct($title, $cancel_url, $width);
        $this->set_form_title( $title );
        $this->set_confirm(FALSE);
    }

    public function set_form_name( $name ) {
        parent::set_form_name($name);
        $this->ajax_divid = 'id'.$name;
    }


    /**
     * This method is used to set the
     * default form submit buttons in this
     * form.
     *
     */
    public function form_init_buttons() {

        $this->add_button( new FEAjaxSubmitButton(self::BUTTON_SAVE));

        //form confirmation
        $this->add_confirm_button( new FEAjaxSubmitButton(self::BUTTON_EDIT) );
        $this->add_confirm_button( new FEAjaxSubmitButton(self::BUTTON_CONFIRM) );

        $this->add_button( $this->get_cancel() );
    }

    /**
     * This protected method allows us to return
     * the string that is the Target for any
     * ajax requests for urls.
     *
     * @return string
     */
    public function get_ajax_target() {
        if (is_null($this->ajax_target)) {
            return get_class($this);
        } else {
            return $this->ajax_target;
        }
    }

    /**
     * This protected method allows us to return
     * the string that is the Target for any
     * ajax requests for urls.
     *
     * @return string
     */
    public function set_ajax_target($target) {
        $this->ajax_target = $target;
        $this->set_cancel_action($this->get_request_builder()->get_url());
    }

    /**
     * This method is used to set the
     * replacement div id that
     * will get replaced as a result
     * of the ajax request.
     *
     * <div id="idreplace">
     *
     * @param string $divid
     * @return void
     */
    public function set_ajax_replacement_divid($divid) {
        $this->ajax_divid = $divid;
        $this->set_cancel_action($this->get_request_builder()->get_url());
    }

    /**
     * This method is used to get the
     * replacement div id that
     * will get replaced as a result
     * of the ajax request.
     *
     * <div id="idreplace">
     * @return string $divid
     */
    public function get_ajax_replacement_divid() {
        return $this->ajax_divid;
    }

    /**
     * This method is used to construct a
     * RequestBuilder object that uses
     * the replacement divid and ajax target.
     *
     * @param array $vars
     * @return RequestBuilder
     */
    public function get_request_builder($vars=array()) {
        return new RequestBuilder($this->get_ajax_target(),
                                  $vars,
                                  $this->get_ajax_replacement_divid());
    }

    /**
     * this builds the main wrapper for the
     * form fields and adds the Save and Cancel buttons
     *
     * @param array - the form data
     * @param array - the form error fields (if any)
     * @return InfoTable widget object
     */
    public function form() {
        $title = $this->_form_title . phphtmllib::_HTML_SPACE;
        $title .="( ".$this->_required_field_marker." ".$this->_required_field_text." )";
        $this->_infotable = new InfoTable($title, $this->_width, 'center');
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
        $table = parent::form_confirm($title, $show_buttons);
        $table->set_align('center');
        return $table;
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
     * Returns the object that is used
     * for rendering the form errors
     * This object has to be of instance
     * HTMLWidget
     *
     * Child can override this method to
     * return their own custom error
     * rendering widget
     *
     * @return HTMLWidget
     */
    protected function get_errors_widget() {
        return new ErrorBoxWidget('Errors', '70%', 'center');
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
    protected function add_form_block( $title=NULL, $table ) {
        $this->_infotable->add_row( new TRtag(array('class' => 'formblock'),
                                              $this->build_form_block( $title, $table )) );
    }

    /**
     * this builds a fieldset and legend and adds the
     * form table to it.
     *
     * @param string - the legend string
     * @param TABLEtag - the form fields in a table
     * @return FIELDSETtag
     */
    protected function build_form_block( $title=NULL, &$content ) {
        $div = &$this->_div_wrapper( );

        if ($this->_fieldset_block) {
            if ($title != NULL) {
                $fs = html_fieldset( '', new LEGENDtag(array('class'=> 'formlegend'),$title) );
                $fs->add( $content );
                $div->add( $fs );
            } else {
                $div->add( $content );
            }
        } else {
            $div->add($content);
        }
        return $div;
    }

    /**
     * this method sets the flag to enable the wrapping
     * of the form blocks inside the fieldset/legend.
     *
     * @param boolean
     */
    public function enable_fieldset($flag=TRUE) {
        $this->_fieldset_block = $flag;
    }

    protected function _div_wrapper() {
        return new DIVtag(array('style' => 'padding:5px;background-color:#f5f5f5;'));
    }

    /**
     * This method is used to get the button with
     * a specific label
     *
     * @param string $label
     * @return FormElement object
     */
    protected function get_button($label) {
        return $this->build_button($label, FormContent::FETYPE_BUTTON);
    }

    /**
     * This method is used to get the button with
     * a specific label
     *
     * @param string $label
     * @return FormElement object
     */
    protected function get_confirm_button($label) {
        return $this->build_button($label, FormContent::FETYPE_CONFIRM_BUTTON);
    }

    /**
     * get the proper button depending on
     * if you are a confirmation button or not
     *
     * @param string $label
     * @param int $type FormContent::FETYPE_*
     * @return FEButton child
     */
    protected function build_button($label, $type = FormContent::FETYPE_BUTTON) {
        if ($type === FormContent::FETYPE_BUTTON) {
            $button = parent::get_button($label);
        } else {
            $button = parent::get_confirm_button($label);
        }

        if ($button instanceof FEAjaxSubmitButton) {
            //set the replacement divid
            //set the success message
            $button->set_ajax_replacement_divid($this->get_ajax_replacement_divid());
            $button->set_success_message($this->get_success_message());

        }
        return $button;
    }

    /**
     * Builds a Cancel button that redirects the application to
     * a new page without going through the form submission process
     *
     * Note, the styling functionality below matches the FormContent
     * add_action_element special styling functionality.  If that
     * changes, this should change as well.
     *
     * @param string $label Label for the button (default 'Cancel')
     * @param bool $disabled Disables button if true
     * @param array $attributes Attributes for the button
     * @return FEButton
     */
    public function get_cancel($label = 'Cancel', $disabled = false, $attributes = null) {
        if (!strstr($this->_cancel_action, 'javascript:')) {
            $cancel_action = 'document.location=\''.$this->_cancel_action.'\'';
        } else {
            $cancel_action = $this->_cancel_action;
        }
        return new FEActionButton($label, $cancel_action);
    }

    /**
     * Returns a string message that will
     * be dislayed in a special message
     * area upon form success
     *
     * @return string
     */
    public function get_success_message() {
        return null;
    }

    /**
     * Returns an object to be rendered
     * upon success
     *
     * @return Container
     */
    public function get_success_object() {
        return null;
    }

    /**
     * Executed upon form success
     *
     */
    public function form_success() {

       $obj = $this->get_success_object();

       $obj = Container::factory($obj);

        if ($message = $this->get_success_message()) {

            $js = SCRIPTtag::factory();
            $js->add('message_show("' . $message . '",2);');
            $obj->add($js);
        }

        return $obj;
    }
}
?>