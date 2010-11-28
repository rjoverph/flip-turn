<?php
/**
 * This file contains the FormContent class.
 *
 * $Id: FormContent.inc 3029 2007-10-07 21:19:12Z brianrue $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 * @todo add an autogenerator to prebuild FormContent child classes
 *       that map to a table in the db, and call a specific BusinessObject
 *       child's setter and save().
 *
 */

/**
 * This class is used to build and render the form.
 * It builds a form by creating FormElement objects
 * which have automatic validation.  It leaves the
 * layout of the form up to the child class.  It has
 * a mechanism in place to automagically show a
 * confirmation 'page' after the data has been submitted
 * and validated.  It also provides a hook for any
 * 'back end' validation of data.  Finally, it provides
 * a function for handling the action of the form, which
 * only gets call after ALL validation has passed.
 *
 * Functions:
 *
 * form_init_elements() - This function is used to
 *   build the FormElement objects that will be used
 *   by the form.  This function is called EVERY time
 *   the FormContent class is instantiated.  After you
 *   create the FormElement, you call the
 *   FormContent::add_element() method, to add the
 *   FormElement object to the form.  You will then
 *   call the 2 methods FormContent::element_label() and
 *   FormContent::element_form() to get access to the
 *   FormElement's label and form field respectively.
 *
 * form_init_data() - This is called only the first time
 *   the form is encountered.  It Allows you to populate
 *   the FormElements with data from a DB for example.
 *   You would use FormContent::set_element_value() or
 *   FormContent::set_hidden_element_value() inside here.
 *
 * form() - This is the method that gets called to build
 *   the layout for your form.  Typically you use a table
 *   and add the label in the first <td> and the form field
 *   itself in the 2nd <td>.  So there are 2 methods in
 *   the FormContent object that allow u to get access to
 *   the FormElements label, and form field.
 *   FormContent::element_label() and
 *   FormContent::element_form().
 *
 *
 * form_backend_validation() - This method enables you to
 *   do any "back end" validation of data.  Such as, check
 *   for a duplicate in the DB on a create/new form.  This
 *   is called after the FormElement's validation methods have
 *   passed.
 *
 * form_action() - This method is called after ALL validation
 *   was successfull, including each FormElement object's
 *   validation methods, as well as the FormContent::form_backend_validation()
 *
 *
 *
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
abstract class FormContent implements IteratorAggregate {

    /**
     * some constants for the default buttons
     */
    const BUTTON_SAVE = 'Save';
    const BUTTON_SUBMIT = 'Submit';
    const BUTTON_EDIT = 'Edit';
    const BUTTON_CANCEL = 'Cancel';
    const BUTTON_CONFIRM = 'Confirm';
    const BUTTON_DELETE = 'Delete';

    /**
     * This holds the name of the form
     * for js that needs it
     */
    protected $_form_name;

    /**
     * This holds the array of
     * hidden form elements
     * used in this form
     */
    protected $_hidden_elements = array();

    /**
     * This holds the array of
     * non-hidden elements
     */
    protected $_elements = array();

    /**
     * this holds the array of buttons
     * used in this form.
     */
    protected $_buttons = array();

    /**
     * This holds the default
     * css class for form field
     * label text.
     *
     */
    protected $_default_label_class = "formlabel";

    /**
     * This is the css class used
     * for fields that have an error
     *
     */
    protected $_error_label_class = "formlabelerror";

    /**
     * Sets to true if there are
     * errors on the form
     *
     * @var bool
     */
    protected $has_errors = false;

    /**
     * flag to let the FormProcessor
     * object know this form has a
     * confirmation page that is required
     */
    protected $_has_confirm = false;

    /**
     * The message that is set
     * during the form_action
     */
    protected $_action_message = "";

    /**
     * The action to take upon clicking
     * the "Cancel" button
     */
    protected $_cancel_action = null;

    /**
     * The action taken in the form
     */
    protected $action = NULL;

    /**
     * Text to show denoted required
     * fields for the form.
     *
     */
    protected $_required_field_text = " - required field";

    /**
     * marker for the required field
     *
     */
    protected $_required_field_marker = "*";

    /**
     * The form Element's flag to add the :
     * character at the end of the label.
     */
    protected $_label_colon_flag = false;

    /**
     * Flag to mark this as having a
     * File Form Element (child of FEFile)
     */
    protected $_has_file_element = false;

    /**
     * Index names of all of the file
     * form elements (if any).
     */
    protected $_file_elements = array();

    /**
     * The onsubmit value for the form
     * tag. FormElement childs can
     * automatically add to this
     * by implementing the
     * onSubmit() method
     */
    protected $_onSubmit = '';

    /**
     * This is the FormValidation object
     * used to validate the form elements
     */
    protected $_FormValidation = null;

    /**
     * Indicates this entire FormContent
     * is in readonly mode.  This forces
     * all of the FormElement to be in
     * readonly mode.
     *
     */
    protected $_is_readonly = false;

    /**
     * Allow us to tell the Form processor
     * that we want to render the form
     * after we successfully process.
     */
    protected $form_success_render = true;

    /**
     * some form element types
     */
    const FETYPE_NORMAL = 0;
    const FETYPE_HIDDEN = 1;
    const FETYPE_BUTTON = 2;
    const FETYPE_CONFIRM_BUTTON = 3;


    /*****************************/
    /*          methods          */
    /*****************************/


    /**
     * Constructor
     *
     * @param string $width
     * @param string $cancel_action
     */
    function __construct($cancel_action=null) {
        $this->set_cancel_action($cancel_action);

        // set unique form content prefix
        FormElement::set_prefix(get_class($this));
    }

    /**
     * This method is what is called to
     * build the list of FormElements that
     * will be used by this form.
     *
     */
    abstract public function form_init_elements();

    /**
     * This method is where you populate your
     * buttons for the form.
     *
     */
    abstract public function form_init_buttons();

    /**
     * This method is involved to make sure that we
     * initialize/create all of our elements and buttons
     *
     */
    public function init() {
        $this->form_init_elements();
        $this->form_init_buttons();
    }

    /**
     * This method is called by the
     * Form Processor to allow this
     * class to do any fetching of
     * data to prepopulate the
     * form field values.
     * You typically use this to
     * read data from a DB.
     *
     * This method is only called once
     * when the form is first hit.
     *
     */
    public function form_init_data() {
    }

    /**
     * This method builds the html form.
     * It is up to the child class to define
     * the layout of the form and return it
     * in a phpHtmllib container.
     *
     * @return Container
     */
    abstract public function form();

    /**
     * This method lets you provide any javascript
     * that is associated with the form content.
     * The FormProcessor will automatically call
     * this and wrap it in a script tag.
     *
     * @return string raw js
     */
    public function javascript() {
        return null;
    }

    /**
     * This method allows this class to do any
     * data munging prior to the form_confirm
     * method being called @ render time.
     *
     * @return true = success
     *         false if u want to trigger an error
     */
    public function pre_confirm() {
        return true;
    }

    /**
     * This is a 'hidden' version of pre_confirm
     * to allow calling the form elements pre_confirm
     * methods.  This is needed for forms that have
     * a confirmation requirement and has file inputs.
     * If the file input FormElement doesn't save off
     * the uploaded file, then the confirmation page
     * will not get the file. apache may nuke the temp
     * file in /tmp.
     *
     */
    protected function _pre_confirm() {
        foreach($this->_file_elements as $name) {
            $this->_elements[$name]->_pre_confirm();
        }
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
    public function form_confirm($title = "Form Confirmation", $show_buttons = true) {
        $table = new InfoTable($title, '100%');

        $this->build_confirm_table($table);

        //now add the confirmation button
        $td = new TDtag(array("colspan" => 2,
                              "class" => "contentnovertical",
                              "align" => "center"),
                              $this->add_element(new FESubmitButton("Confirm")));

        if ($this->_cancel_action) {
            $td->add(phphtmllib::_HTML_SPACE, $this->get_cancel());
        }

        if ($show_buttons) {
            $table->add_row($td);
        }

        return $table;
    }

    /**
     * This method allows the child to ovveride the
     * default confirm data.  By default the form_confirm()
     * will show ALL FormElements.  This is prolly not good
     * in case of a form where a password exists.
     *
     * @param InfoTable object
     */
    protected function build_confirm_table(&$table) {
        foreach($this->_elements as $label => $element) {
            $c = Container::factory(phphtmllib::_HTML_SPACE, $element->get_value_text());
            $c->set_collapse();
            $div = DIVtag::factory("", $element->get_label($this));
            $div->set_style("white-space:nowrap;");
            $table->add_row($div, $c);
        }
    }

    /**
     * This method is called after the FormElements
     * have all been validated, and the form_confirm
     * has been confirmed.  It enables the form to
     * validate any data against a DB or other backend
     * processing.  This will always get called
     * before the form_action method is called to ensure
     * that all form data is valid before form_action()
     * is called.
     *
     *
     * @return boolean true if successfull
     *                 false if errors were detected.
     */
    public function form_backend_validation() {
        return true;
    }

    /**
     * This method handles the
     * action (submit button) that
     * was submitted.  This method
     * only gets called AFTER all
     * data has been validated.
     * This includes the backend
     * validation.  If the form
     * has the confirmation on,
     * then this method will be
     * called after the confirmation
     * has been accepted.
     *
     * NOTE : return true if the action
     *        was succesfully handled.
     *        If false is returned, the
     *        form will be displayed again
     *        with the error message.
     *
     * @param array - array of errors if any
     * @return boolean true = success
     *                 false = failed.
     */
    abstract public function form_action();

    /**
     * This method is called when the form_action()
     * was successfull, and the form wants to render
     * some kind of message
     *
     * @return mixed
     */
    public function form_success() {
        if ($this->_action_message != "") {
            return $this->_action_message;
        } else {
            return null;
          }
    }

    /**
     * This function turns on the ability to
     * render the form after the success
     * of the action.  Normally this feature
     * is off
     *
     */
    public function set_render_form_after_success($flag=true) {
        $this->form_success_render = $flag;
    }

    /**
     * This function turns on the ability to
     * render the form after the success
     * of the action.  Normally this feature
     * is off
     *
     */
    public function get_render_form_after_success($flag=true) {
        return $this->form_success_render;
    }

    /*****************************/
    /*     error handling        */
    /*****************************/

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
        return new FormErrorsWidget();
    }

    /**
     * This function is used to render the errors
     * for the form.  The error data comes
     * from the FormProcessor or the FormValidation.
     *
     * @return HTMLWidget
     */
    public function form_errors() {

        $c = $this->get_errors_widget();

        $errors = false;

        //walk each visible form element and see if there is an error in it
        foreach($this->_elements as $label => $element) {
            if ($element->has_error()) {
                $this->has_errors = true;
                $e_errors = $element->get_errors();
                foreach($e_errors as $err) {
                    $id = $element->get_element_id();
                    $anchor = Atag::factory('#l'.$id, $err['label'],
                                     'formanchor');
                    $anchor->set_tag_attribute('onclick',
                                               "javascript:getElementById('".$id."').focus();");
                    $c->add($anchor, $err['message']);
                }
                $errors = true;
            }
        }
        if ($errors) {
            return $c;
        } else {
            return null;
        }
    }

    /**
     * This method returns an array of errors
     * for all the errors.
     *
     * @return array
     */
    protected function get_error_array() {
        $ret = array();
        //walk each visible form element and see if there is an error in it
        foreach($this->_elements as $label => $element) {
            if ($element->has_error()) {
                $errors = $element->get_errors();
                foreach ($errors as $err) {
                    $ret[$err['label']] = $err['message'];
                }
            }
        }
        return $ret;
    }

    /*****************************/
    /*     form element methods  */
    /*****************************/

    /**
     * This method is used to add a
     * form element
     *
     * @param FormElement object
     */
    protected function add_element(FormElement $element) {

        //in case the element needs it for js
        $element->set_form_name($this->_form_name);
        $name = $element->get_label_text();
        $this->_elements[$name] = &$element;

        //do we have a File form element?
        if ($element instanceof FEFile) {
            $this->_has_file_element = true;
            $this->_file_elements[] = $name;
        }

        // add onSubmit js
        $this->_onSubmit .= $element->onSubmit();

        // add js validation
        $this->_onSubmit .= $element->js_validate();

        // propagate settings down to the element
        $element->set_colon_flag($this->_label_colon_flag);
    }

    /**
     * This method is used to add a
     * hidden form field
     *
     * @param FormElement object
     */
    protected function add_hidden_element($label, $value=null) {
        $element = new FEHidden($label, $value);
        $element->set_form_name($this->_form_name);
        $this->_hidden_elements[$label] = &$element;
    }

    /**
     * This method is used to add a new
     * button to the form
     *
     * @param FormElement $button
     */
    protected function add_button(FEButton $button) {
        $button->set_form_name($this->_form_name);
        $this->_buttons[self::FETYPE_BUTTON][$button->get_label_text()] = &$button;
    }

    /**
     * This method is used to get the button with
     * a specific label
     *
     * @param string $label
     * @return FormElement object
     */
    protected function get_button($label) {
        $this->_test_element($label, 'get_button', self::FETYPE_BUTTON);
        return $this->_buttons[self::FETYPE_BUTTON][$label];
    }

    /**
     * This method is used to add a new
     * button to the form
     *
     * @param FormElement $button
     */
    protected function add_confirm_button(FEButton $button) {
        $button->set_form_name($this->_form_name);
        $this->_buttons[self::FETYPE_CONFIRM_BUTTON][$button->get_label_text()] = &$button;
    }

    /**
     * This method is used to get the button with
     * a specific label
     *
     * @param string $label
     * @return FormElement object
     */
    protected function get_confirm_button($label) {
        $this->_test_element($label, 'get_button', self::FETYPE_CONFIRM_BUTTON);
        return $this->_buttons[self::FETYPE_CONFIRM_BUTTON][$label];
    }

    /**
     * This method returns the label object
     * for a visible form element.
     *
     * @param string - the element's label
     * @return Object
     */
    protected function element_label($label) {
        $this->_test_element($label, "element_label");
        return $this->_elements[$label]->get_label($this);
    }

    /**
     * This method returns the label object
     * for a visible form element.
     *
     * @param string - the element's label
     * @return Object
     */
    protected function hidden_element_label($label) {
        $this->_test_element($label, "hidden_element_label", self::FETYPE_HIDDEN);
        return $this->_hidden_elements[$label]->get_label($this);
    }

    /**
     * This method returns the actual form
     * object that renders the form field.
     * Such as an INPUTtag object.
     *
     * @param string - the element's label
     * @return Object
     */
    protected function element_form($label) {
        $this->_test_element($label, "element_form", self::FETYPE_NORMAL);
        return $this->_elements[$label]->get_form_element($this->is_readonly());
    }

    /**
     * This method returns the FormElement
     * based on the label.
     *
     * @param string - the element's label
     * @return FormElement
     */
    public function get_element($label) {
        $this->_test_element($label, "get_element", self::FETYPE_NORMAL);
        return $this->_elements[$label];
    }

    /**
     * Returns all elements in the
     * form content
     *
     * @return array
     */
    public final function get_elements() {
        return $this->_elements;
    }

    /**
     * Returns all hidden elements in the
     * form content
     *
     * @return array
     */
    public final function get_hidden_elements() {
        return $this->_hidden_elements;
    }

    /**
     * Returns all hidden elements in the
     * form content
     *
     * @return array
     */
    public final function get_hidden_element($label) {
        $this->_test_element($label, "get_element", self::FETYPE_HIDDEN);
        return $this->_hidden_elements[$label];
    }

    /**
     * This method is used to set
     * the value for a non hidden
     * element
     *
     * @param string - the form label
     * @param value - the new value
     */
    protected function set_element_value($label, $value) {
        $this->_test_element($label, "set_element_value", self::FETYPE_NORMAL);
        $this->_elements[$label]->set_value($value);
    }

    /**
     * This method is used to get
     * the value for a non hidden
     * element
     *
     * @param string - the form label
     * @return value - the new value
     */
    protected function get_element_value($label) {
        $this->_test_element($label, "get_element_value", self::FETYPE_NORMAL);
        return $this->_elements[$label]->get_value();
    }

    /**
     * This method is used to set
     * the value for a hidden element
     *
     * @param string - the form label
     * @param value - the new value
     */
    protected function set_hidden_element_value($label, $value) {
        $this->_test_element($label, "set_hidden_element_value", self::FETYPE_HIDDEN);
        $this->_hidden_elements[$label]->set_value($value);
    }

    /**
     * This method is used to get
     * the value for a hidden element
     *
     * @param string - the form label
     * @return value - the new value
     */
    protected function get_hidden_element_value($label) {
        $this->_test_element($label, "get_hidden_element_value", self::FETYPE_HIDDEN);
        return $this->_hidden_elements[$label]->get_value();
    }

    /**
     * This method is a helper method to set the
     * FormElement's tabindex.
     *
     * @param string - the form label
     * @param int - the FormElement's tabindex
     * @return none
     */
    protected function set_form_tabindex($label, $index) {
        $this->_test_element($label, "set_form_tabindex", self::FETYPE_NORMAL);
        $this->_elements[$label]->set_tabindex($index);
    }

    /**
     * This method is a helper method to get the
     * FormElement's tabindex.
     *
     * @param string - the form label
     * @param int - the FormElement's tabindex
     * @return the FormElement's current tabindex
     */
    protected function get_form_tabindex($label, $index) {
        $this->_test_element($label, "set_form_tabindex", self::FETYPE_NORMAL);
        return $this->_elements[$label]->get_tabindex();
    }

    /**
     * This method is used to test
     * if the element exists in a form
     *
     * @param string - the form label
     * @return bool
     */
    protected function element_exists($label) {
        return (isset($this->_elements[$label]) || isset($this->_hidden_elements[$label]));
    }

    /**
     * This method is used to create a new error element
     * during the call to form_action().  This enables us
     * to do error handling during a transaction into
     * a DB.
     *
     * @param string - the label
     * @param string - the error message
     */
    protected function add_error($label, $message) {
        if (isset($this->_elements[$label])) {
            $this->_elements[$label]->set_error_message($message);
        } else {
            $this->add_element(new FEError($label, $message));
        }
    }

    /**
     * This sets the readonly flag.
     * When this flag is set, all of the
     * FormElements will be set to readonly.
     *
     * @param bool true = readonly
     */
    public function set_readonly($flag=true) {
        $this->_is_readonly = $flag;
    }

    /**
     * Is this form in read only mode?
     *
     * @return bool
     */
    public function is_readonly() {
        return $this->_is_readonly;
    }


    /*****************************/
    /*       Util methods        */
    /*****************************/

    /**
     * Sets the form name
     *
     * @param string $name
     */
    public function set_form_name($name) {
        $this->_form_name = $name;
    }

    /**
     * Returns the form name
     *
     * @return string
     */
    public function get_form_name() {
        return $this->_form_name;
    }

    /**
     * Set the action for the form
     *
     * @param string $action
     */
    public function set_action($action) {
        $this->action = $action;
    }

    /**
     * Get the current status of the
     * action
     *
     * @return string
     */
    public function get_action() {
        return $this->action;
    }

    /**
     * This function is used to set the
     * default CSS class used on
     * form field text when there is no
     * error on that field
     *
     * @param string - the css class to use
     */
    protected function set_label_class($css) {
        $this->_default_label_class = $css;
    }

    /**
     * This function returns the
     * default css class used for
     * NON error text.
     *
     * @return string - the current default css
     */
    protected function get_label_class() {
        return $this->_default_label_class;
    }

    /**
     * This function is used to set the
     * css class that is used on text
     * when an error on that field is
     * detected.
     *
     * @param string - the css class to use.
     */
    protected function set_error_label_class($css) {
        $this->_error_label_class = $css;
    }

    /**
     * This sets the $this->_has_confirmation
     * flag.  to let the object know it has
     * a required confirmation page, which
     * should get called after the validation
     * is successfull, and before the action is
     * handled on the back-end.
     *
     * @param boolean - the flag value true/false
     */
    public function set_confirm($flag = true) {
        $this->_has_confirm = $flag;
    }

    /**
     * This gets the value of the confirmation flag.
     * which tells the caller that this object
     * has/doesn't have a required confirmation
     * page.
     *
     * @return boolean
     */
    public function has_confirm() {
        return $this->_has_confirm;
    }

    /**
     * This sets the action message.
     * This is called from withint the
     * form_action() method
     *
     * @param string - the action message
     */
    protected function set_action_message($message) {
        $this->_action_message = $message;
    }

    /**
     * This method sets the javasript action
     * to be taken when the cancel button
     * is clicked.  Calling this method
     * w/ a non null value automatically enables
     * the Cancel button.
     *
     * @param string - the javascript cancel action
     */
    public function set_cancel_action($action) {
        $this->_cancel_action = $action;
    }

    /**
     * This method sets the flag to have ALL of the
     * FormElement's labels be appended with a :
     * character.  Some folks like this for some
     * completely unexplained reason.
     */
    protected function set_colon_flag($flag=true) {
        $this->_label_colon_flag = $flag;
    }

    /**
     * build a cancel button with a url
     * to go to
     *
     * @param string - the cancel action
     * @return form button
     */
    protected function get_cancel($label='Cancel') {
        return new FEActionButton($label, 'document.location=\''.$this->_cancel_action.'\'');
    }

    /**
     * This function is used to set the required field marker
     *
     * @param string - the marker
     */
    public function set_required_marker($marker) {
         $this->_required_field_marker = $marker;
     }

    /**
     * This function is used to get the required field marker
     *
     * @return string - the marker
     */
    public function get_required_marker() {
        if (is_object($this->_required_field_marker)) {
            return $this->_required_field_marker->render();
        } else {
            return $this->_required_field_marker;
        }
    }

    /**
     * This sets the required text
     *
     * @param string
     */
     public function set_required_text($text) {
         $this->_required_field_text = $text;
     }

    /**
       * Returns true if this form content
       * has a file upload element inside
       *
       * @return bool
       */
    public function has_file_element() {
          return $this->_has_file_element;
      }

    /**
       * Returns onSubmit value of the
       * form
       *
       * @return string
       */
    public function onSubmit() {
          return $this->_onSubmit;
      }

    /**
     * This method tests to see if we
     * have an element named $label,
     * so we can operate on it.
     *
     * @param string - the element's label
     * @param string - the name of the method that called us
     * @param int - which type of element to test
     *
     * @todo throw a ValidatorException to help localize the error.
     */
    function _test_element($label, $method, $type=self::FETYPE_NORMAL) {
        $failed = FALSE;

        switch ($type) {
        case self::FETYPE_NORMAL:
            if (!isset($this->_elements[$label])) {
                $failed = TRUE;
            }
            break;
        case self::FETYPE_HIDDEN:
            if (!isset($this->_hidden_elements[$label])) {
                $failed = TRUE;
            }
            break;
        case self::FETYPE_BUTTON:
            if (!isset($this->_buttons[self::FETYPE_BUTTON][$label])) {
                $failed = TRUE;
            }
            break;
        case self::FETYPE_CONFIRM_BUTTON:
            if (!isset($this->_buttons[self::FETYPE_CONFIRM_BUTTON][$label])) {
                $failed = TRUE;
            }
            break;
        }

        if ($failed) {
            throw new phphtmllibException("FormContent::".$method."() - '".$label."' element doesn't exist");
        }
    }

    /**
     * Return the values of all visible
     * form elements as an array
     *
     * @return array
     *
     */
    public function get_all_element_values() {

        foreach ($this->_elements as $element) {
            $data[$element->get_element_name()] = $element->get_value();
        }

        return $data;
    }

    /**
     * This method is used to keep a local reference
     * of the FormProcessor's FormValidation object
     *
     * @param FormValidation object
     */
    public function set_validation_object(&$FormValidation) {
        $this->_FormValidation =& $FormValidation;
    }

    /**
     * Implements iterator interface
     *
     * @return Iterator
     */
    function getIterator() {
       return new ArrayIterator(array_merge($this->_elements, $this->_hidden_elements));
    }
}

?>