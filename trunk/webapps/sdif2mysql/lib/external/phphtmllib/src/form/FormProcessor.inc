<?php
/**
 * This file contains the FormProcessor class.
 *
 * $Id: FormProcessor.inc 2824 2007-05-29 19:24:49Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * This is the main engine for the processing
 * of Forms.  It builds the form tag, and calls
 * the appropriate FormContent methods to build
 * the FormElement's and validation, as well as
 * backend processing to do the action after the
 * data has been validated.
 *
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
class FormProcessor extends Container {

    /**
     * Name of the form action hidden variable
     *
     */
    const FORM_ACTION = '_form_action';

    /**
     * Name of the form visited hidden variable
     *
     */
    const FORM_VISITED = '_form_visited';

    /**
     * Name of the form confrm hidden variable
     *
     */
    const FORM_CONFIRM = 'form_confirm';

    /**
     * Name of the form name hidden var
     */
    const FORM_NAME = 'form_name';

    /**
     * This array holds the FORMtag
     * attributes for this form
     *
     */
    protected $_form_attributes = array('method' => 'post',
                                        'action' => '',
                                        'name' => 'myform',
                                        'id' => '',
                                        'target' => '',
                                        'onsubmit' => '');

    /**
     * This holds the FormContent Object
     * that knows how to render the
     * form.
     */
    protected $_form_content;

    /**
     * This flag lets us know there
     * were errors during processing or
     * validating the form.
     */
    protected $_has_errors = false;

    /**
     * Flag to let us know the form
     * has been confirmed.
     */
    protected $_confirmed = false;

    /**
     * Flag to let us know if we should
     * render the form after it was
     * successfully processed
     */
    protected $_form_success_render = true;


    /**
     * The action that was taken
     * for the form
     */
    protected $_form_submit_action;

    /**
     * The form was processed and passed
     * the confirmation if any, and
     * it was successfull ?
     */
    protected $_confirmed_successful = false;

    /**
     * This tells us to show or not to
     * show the form errors autmatically.
     * The user of the FormProcessor
     * may want to deal with errors manually
     */
    protected $_auto_show_errors = true;

    /**
     * The constructor for the FormProcessor
     *
     * @param FormContent $form_content
     * @param string the form name
     * @param string the form name
     */
    function __construct(&$form_content, $form_name = "myform",
                         $form_action = NULL) {

        $this->_form_content = &$form_content;
        $this->set_form_name($form_name);
        $this->set_form_id(md5(uniqid()));
        $this->_form_content->set_form_name($form_name);

        if ($form_action != NULL) {
            $this->set_form_action($form_action);
        } else {
            $this->set_form_action($_SERVER["PHP_SELF"]);
        }

        $this->_init_form_content();

        //now process the form
        if (Request::singleton()->get(self::FORM_NAME) == $form_name) {
            $this->_process_form();
        }
    }


    /**
     * This method does the logic of
     * doing the form processing
     */
    protected function _process_form() {

        //we only need to process the form
        //if it has been visited. Otherwise
        //it just gets rendered.
        if (isset($_REQUEST[self::FORM_VISITED]) &&
            $_REQUEST[self::FORM_VISITED] == 1) {
            $this->_set_action();

            //let see if this was a confirmation page.
            if (isset($_REQUEST[self::FORM_CONFIRM]) &&
                $_REQUEST[self::FORM_CONFIRM] == 1) {
                    //looks like this was a submit on a
                    //confirmation page.  we don't need
                    //to do form field validation.
                    $this->_confirmed = true;
            }

            if ($this->_form_content->has_confirm()) {
                    //the form content has a confirmation
                    //we need to process
                    $this->_has_errors = !$this->_pre_confirm();
            }

            //we haven't been confirmed, so we
            //need to validate the form
            if ($this->can_validate()) {
                //looks like we should do validation
                $this->do_validation();
            }
            if (!$this->_has_errors) {
                //no errors were found
                //make sure we don't have any backend errors
                $this->_has_errors = !$this->_form_content->form_backend_validation();
                if (!$this->_has_errors && (($this->_form_content->has_confirm()
                                             && $this->_confirmed) || !$this->_form_content->has_confirm())) {
                    // process action only at the final stage
                    $this->_has_errors = !$this->_process_action();

                    if (!$this->_has_errors) {
                        $this->_set_confirmed_success(true);
                    }
                }
            }
        }
    }

    /**
     * This function is responsible for
     * processing the form action
     * after validation, and form confirmation
     * happens.
     *
     */
    private function _process_action() {
        //There were no validation errors.
        return $this->_form_content->form_action();
    }

    /**
     * This method calls the FormContent
     * to let it do any data munging before the
     * confirmation page is rendered
     */
    protected function _pre_confirm() {

        if ($this->_form_content->has_file_element()) {
            //we need to allow any/all of the file elements
            //save the temp files during a confirmation.
            //if we don't, then the web server may delete
            //them before confirmation has been accepted.
            $this->_form_content->_pre_confirm();
        }

        //call the user defineable FormContent pre_confirm.
        return $this->_form_content->pre_confirm();
    }

    /**
     * This method walks the FormContent's visible elements
     * and calls the validation function for the element
     *
     */
    public function do_validation() {
        foreach($this->_form_content as $element) {
            if (!$element->is_disabled() && !$element->do_validation($this->_FormValidation)) {
                $this->_has_errors = true;
            } else {
                //detect disabled field hack attempts
                if ($element->has_error()) {
                    $this->_has_errors = true;
                }
            }
        }
    }

    /**
     * This method is called to render the form's html
     *
     * @param int $indent_level
     * @param int $output_debug
     *
     * @return string
     */
    public function render($indent_level=0, $output_debug=0) {
        if ($this->_has_errors) {
            //we need to render the form errors
            //and then the form
            return $this->render_form($indent_level, $output_debug);
        } else {
            //there are no errors!
            if (Request::singleton()->get(self::FORM_NAME) == $this->get_form_name() &&
                isset($_REQUEST[self::FORM_VISITED]) &&
                $_REQUEST[self::FORM_VISITED] == 1) {
                //looks like the form has been processed?
                if ($this->_form_content->has_confirm() && !$this->_confirmed) {
                    return $this->render_confirm($indent_level, $output_debug);
                } else {

                    if ($this->_form_content->get_render_form_after_success()) {
                        return $this->render_form($indent_level, $output_debug, TRUE);
                    } else {
                        $success = $this->_form_content->form_success();
                        if (!is_string($success) && method_exists($success, 'render')) {
                            //looks like this is an object.
                            //we'll assume it has a render function.
                            return $success->render($indent_level, $output_debug);
                        } else {
                            //since its not an object,
                            //lets just display it.
                            return $success;
                        }
                    }
                }
            } else {
                return $this->render_form($indent_level, $output_debug);
            }
        }
    }

    /**
     * This renders the form
     *
     * @param int - $indent_level
     * @param int - $output_debug
     *
     * @return string
     */
    protected function render_form($indent_level=0, $output_debug=0, $do_success=false) {

        //build the $this->_form object.
        $this->_build_form_tag();

        //check to see if the form_content
        //has any js, or any of the form elements
        //have js.
        $form_js = $this->_javascript();
        if (strlen($form_js) > 0) {
            $script = SCRIPTtag::factory();
            $script->add($form_js);
            //$this->_form->add($script);
        }

        if ($this->_has_errors) {
            $this->_form->add($this->render_error($indent_level, $output_debug));
        }

        if ($do_success) {
            $this->_form->add($this->_form_content->form_success());
        }
        $this->_form->add($this->_form_content->form());

        //add the FormContent's hidden declared
        //hidden form fields.
        $this->_add_hidden_fields();

        //Ok lets add our hidden vars
        $this->__hidden_fields();

        if (isset($script)) {
            $c = Container::factory($script, $this->_form);
            return $c->render($indent_level, $output_debug);
        } else {
            return $this->_form->render($indent_level, $output_debug);
        }

    }

    /**
     * This function renders the confirmation
     * page.  This page sits in between the
     * front end form, and the action handler.
     * This only gets called after a form
     * and its data has been successfully
     * validated.
     *
     * @param int $indent_level
     * @param int $output_debug
     *
     * @return string
     */
    protected function render_confirm($indent_level=0, $output_debug=0) {
        //build the $this->_form object.
        $this->_build_form_tag();

        //add the confirm object/html
        $confirm = &$this->_form_content->form_confirm();
        $this->_form->add($confirm);

        //ok add all of the submitted data as hidden form fields
        $this->_add_confirm_data();

        //Ok lets add our hidden vars
        $this->__hidden_fields();

        return $this->_form->render($indent_level, $output_debug);
    }

    /**
     * This renders the error table
     * and then the form with the fields
     *
     * @param int $indent_level
     * @param int $output_debug
     *
     * @return string
     */
    protected function render_error($indent_level=0, $output_debug=0) {

        if ($this->_auto_show_errors) {
            //Ok first lets build the error table
            $wrapper = new DIVtag;
            $errors = &$this->_form_content->form_errors();
            if ($errors != NULL) $wrapper->add($errors);
            return $wrapper->render($indent_level, $output_debug);
        } else {
            return NULL;
        }

    }


    //***********************************************//
    //*       utility functions for this class      *//
    //***********************************************//


    /**
     * This method lets us turn on/off the
     * ability to do validation for the form
     *
     * @return bool
     */
    public function can_validate() {
        return true;
    }

    /**
     * This function turns on the ability to
     * render the form after the success
     * of the action.  Normally this feature
     * is off
     *
     */
    public function set_render_form_after_success($flag=true) {
        $this->_form_success_render = $flag;
    }

    /**
     * This is used to test to see if the form action
     * was processed succesfully.
     * This is usefull for external entities to determine
     * if the form was processed, and it was successful.
     *
     * @return bool
     */
    protected function is_action_successful() {
        return $this->_confirmed_successful;
    }

    /**
     * This flag sets the flag that tells
     * if we successfully confirmed the form,
     * and processed the action
     *
     * @param boolean
     */
    protected function _set_confirmed_success($flag=true) {
        $this->_confirmed_successful = $flag;
    }

    /**
     * This sets the flag that tells this class
     * to automatically call the form contents
     * form errors and display it or not
     *
     * @param boolean - show errors?
     */
    public function set_auto_error_display($flag=true) {
        $this->_auto_show_errors = $flag;
    }

    /**
     * This gets the current value of the flag
     * that tells us to show form errors automatically
     * or not
     *
     * @return bool
     */
    function get_auto_error_display() {
        return $this->_auto_show_errors;
    }

    /**
     * This method allows us to get access to the
     * errors display object that is generated by
     * the form content.  This is the display
     * object that is meant to be rendered directly.
     * If there are no errors. we will return NULL
     *
     * @return Container
     */
    function &get_error_display_object() {
        if ($this->_has_errors) {
            return $this->_form_content->form_errors();
        } else {
            return NULL;
        }
    }

    /**
     * This method returns an array of errors that
     * happened in the form.
     *
     * @return array
     */
    function get_error_array() {
        return $this->_form_content->get_error_array();
    }

    /**
     * This returns the flag that tells us that
     * the form has errors during processing
     *
     * @return bool
     */
    function has_errors() {
        return $this->_has_errors;
    }


    //************************************************//
    //*       FORMtag Attributes for this class      *//
    //************************************************//


    /**
     * This function is used to set the
     * form name
     *
     * @param string
     */
    public function set_form_name($name) {
        $this->_form_attributes["name"] = $name;
    }

    /**
     * This function is used to get
     * the form name
     *
     * @return string
     */
    public function get_form_name() {
        return $this->_form_attributes["name"];
    }

    /**
     * This function is used to set the
     * form id
     *
     * @param string
     */
    public function set_form_id($id) {
        $this->_form_attributes["id"] = $id;
    }

    /**
     * This function is used to get
     * the form id
     *
     * @return string
     */
    public function get_form_id() {
        return $this->_form_attributes["id"];
    }

    /**
     * This function is used to set the
     * form target
     *
     * @param string
     */
    public function set_form_target($target) {
        $this->_form_attributes["target"] = $target;
    }

    /**
     * This function is used to get
     * the form target
     *
     * @return string
     */
    public function get_form_target() {
        return $this->_form_attributes["target"];
    }

    /**
     * This function is used to set the
     * form method
     *
     * @param string (POST or GET)
     */
    public function set_form_method($method) {
        if (strcasecmp($method,"GET") !=0 && strcasecmp($method,"POST") !=0) {
            user_error("FormProcessor::set_form_method() - INVALID Form method ".$method);
        } else {
            $this->_form_attributes["method"] = $method;
        }
    }

    /**
     * This function is used to get
     * the form method
     *
     * @return string
     */
    public function get_form_method() {
        return $this->_form_attributes["method"];
    }

    /**
     * Sets the form action
     *
     * @param string
     */
    public function set_form_action($action) {
        $this->_form_attributes["action"] = $action;
    }

    /**
     * This function is used to get
     * the form action
     *
     * @return string
     */
    public function get_form_action() {
        return $this->_form_attributes["action"];
    }

    /**
     * Sets the form enctype
     *
     * @param string
     */
    public function set_form_enctype($enctype) {
        $this->_form_attributes["enctype"] = $enctype;
    }

    /**
     * This function is used to get
     * the form enctype value
     *
     * @return string
     */
    public function get_form_enctype() {
        return $this->_form_attributes["enctype"];
    }

    /**
     * This is used to set the action
     * submitted by the user
     *
     */
    protected function _set_action() {
        $this->_form_submit_action = $_REQUEST[self::FORM_ACTION];
        $this->_form_content->set_action($this->_form_submit_action);
    }

    /**
     * This is used to get the action that was
     * processed by the form
     *
     * @return string
     */
    public function get_action() {
        return $this->_form_submit_action;
    }

    /**
     * Set the onsubmit attribute to the form
     * NOTE: The FormContent child can automatically
     * set this value depending on the FormElement
     * children it contains.
     *
     * @param string $js
     */
    public function set_onsubmit($js) {
        $this->_form_attributes["onsubmit"] = $js;
    }

    /**
     * Gets the current value of the form tag's
     * onsubmit value
     *
     * @return string
     */
    protected function onSubmit() {
        return $this->_form_attributes["onsubmit"];
    }

    /**
     * Set a random attribute on the form tag.
     * You should know what you are doing as this
     * might invalidate the output html with the
     * W3C validator.
     *
     * @param string the key
     * @param string the value
     */
    public function set_form_attribute($key, $value) {
        $this->_form_attributes[$key] = $value;
    }


    //************************************//
    //*       Some protected methods     *//
    //************************************//


    /**
     * This method initializes the FormContent
     * during processing.
     *
     */
    protected function _init_form_content() {
        //let the form build the FormElement objects
        //that will be used by the form
        $this->_form_content->init();

        //first we need to
        if (!@$_REQUEST[self::FORM_VISITED]) {
            $this->_form_content->form_init_data();
        }

        //see if the form content has a child of the
        //FEFile element, so we can automatically
        //add the enctype to the form tag attribute
        if ($this->_form_content->has_file_element()) {
            $this->set_form_enctype("multipart/form-data");
        }
    }

    /**
     * This function builds the FORMtag object
     * and its attributes.
     *
     * @return FORMtag
     */
    private function _build_form_tag() {
        //see if we need to add the onsubmit attribute to the form
        //this only needs to happen on the non-confirmation
        //portion of the forms.
        if (!isset($_REQUEST[self::FORM_VISITED]) || !$_REQUEST[self::FORM_VISITED]) {
            $this->set_onsubmit($this->_form_content->onSubmit() . $this->onSubmit());
        } else {
            //re-rendering the form and it has errors.
            //we need the onsubmit if they have it.
            if (isset($_REQUEST[self::FORM_VISITED]) && $this->_has_errors) {
                $this->set_onsubmit($this->_form_content->onSubmit() . $this->onSubmit());
            } else if (isset($_REQUEST[self::FORM_CONFIRM]) && $_REQUEST[self::FORM_CONFIRM] == 1) {
                //form has been confirmed lets add it
                //in case we are showing the form again
                $this->set_onsubmit($this->_form_content->onSubmit() . $this->onSubmit());
            }
        }

        $form_attrs = array();
        foreach($this->_form_attributes as $name => $value) {
            if ($value) {
                $form_attrs[$name] = $value;
            }
        }
        $this->_form = new FORMtag($form_attrs);
    }

    /**
     * This adds all of the submitted data as
     * hidden form fields
     *
     */
    private function _add_confirm_data() {
        foreach ($this->_form_content as $element) {
            //make sure the element isn't disabled.
            if (!$element->is_disabled()) {
                $this->_form->add($element->get_confirm_element());
            }
        }
    }

    /**
     * This function adds the form content's
     * hidden form fields to the
     * form automatically
     *
     */
    protected function _add_hidden_fields() {
        //Lets add the form's hidden vars it wants
        foreach ($this->_form_content->get_hidden_elements() as $element) {
            if ($element instanceof FEHidden) {
                $this->_form->add($element->get_element());
            }
        }
    }

    /**
     * This method adds the processor specific
     * hidden fields.
     *
     */
    protected function __hidden_fields() {
        $this->_form->add(INPUTtag::factory('hidden', self::FORM_VISITED,1));
        $this->_form->add(INPUTtag::factory('hidden', self::FORM_NAME,$this->get_form_name()));

        if ($this->_form_content->has_confirm() && !$this->_confirmed) {
            if (@!$_REQUEST[self::FORM_VISITED] || $this->_has_errors) {
                $this->_form->add(INPUTtag::factory('hidden', self::FORM_CONFIRM, 0));
            } else {
                $this->_form->add(INPUTtag::factory('hidden', self::FORM_CONFIRM, 1));
            }
        } else if ($this->_form_content->has_confirm() && !$this->_confirmed) {
            //reset this so they can submit again
            $this->_form->add(INPUTtag::factory('hidden', self::FORM_CONFIRM, 0));
        }
    }

    /**
     * This method is used to build any Javascript
     * that is used by the form and/or the form elements
     * used in the form.
     *
     * @return string
     */
    protected function _javascript() {
        $js = $this->_form_content->javascript();

        //now walk each form element and try to get any js
        foreach($this->_form_content as $element) {
            $js .= $element->javascript();
        }

        return $js;
    }

}

?>