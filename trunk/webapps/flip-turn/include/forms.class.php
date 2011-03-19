<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 *
 * $Id$
 *
 * Form classes.  These classes manage the
 * entry and display of the various forms used
 * by the Flip-Turn web application.
 *
 * (c) 2010 by Mike Walsh for FlipTurn.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage forms
 * @version $Revision$
 * @lastmodified $Date$
 * @lastmodifiedby $Author$
 *
 */

include_once('ft.include.php') ;
include_once('options.class.php') ;

/**
 * Include the Form Processing objects
 *
 */
include_once(PHPHTMLLIB_ABSPATH . "/form/includes.inc") ;

/**
 * FlipTurn Form Base Class - extension of StandardFormContent
 *
 * @author Mike Walsh <mike_walsh@mindspirng.com>
 * @access public
 * @see StandardFormContent
 */
class FlipTurnSimpleForm extends FormContent
{
    /**
     * Constructor
     *
     * @param string width
     * @param cancel action
     *
     */
    function FlipTurnSimpleForm($width = "100%", $cancel_action = null)
    {
        //  Turn of default confirmation

        $this->set_confirm(false) ;
        
        //  Use a 'dagger' character to denote required fields.

        $this->set_required_marker('&#134;');

        //  Turn on the colons for all labels.

	    $this->set_colon_flag(true) ;

        //  Call the parent constructor

        $this->FormContent($width, $cancel_action) ;
    }
}

/**
 * FlipTurn Form Base Class - extension of StandardFormContent
 *
 * @author Mike Walsh <mike_walsh@mindspirng.com>
 * @access public
 * @see StandardFormContent
 */
class FlipTurnForm extends StandardFormContent
{
    /**
     * Overload the standard action message function
     * so action messages are displayed in a consistent
     * Wordpress format.
     *
     * @param String message content
     */
    
    function get_action_message()
    {
        return $this->_action_message ;
    }

    /**
     * Overload the standard action message function
     * so action messages are displayed in a consistent
     * Wordpress format.
     *
     * @param String message content
     */
    
    function set_action_message2($message, $class = "ft-note-msg")
    {
        parent::set_action_message(html_div($class, $message)) ;
    }

    /**
     * Overload the build a cancel button with a button
     * that performs a Javascript history.go(-1) action 
     * when the cancel redirect is null.
     *
     * @param string - 'Cancel' string
     * @return form button
     */
    function add_cancel($cancel = "Cancel")
    {
        if ($this->_cancel_action === null)
        {
            $cancel_button = form_button("cancel",
                $cancel, array( "type"=>"button" ,"style"=>"width: 90px;",
                "onclick"=> "javascript:history.go(-1)")) ;
            $cancel_button->set_style("vertical-align:middle") ;
        }
        else
        {
            $cancel_button = parent::add_cancel($cancel) ;
        }

        return $cancel_button ;
    }

    /**
     * Provide a mechanism to overload form_content_buttons() method
     * to have the button display "Go" instead of "Save" and not
     * display the cancel button.
     *
     * @return HTMLTag object
     */
    function form_content_buttons_Go()
    {
        $div = new DIVtag(array("style" => "background-color: #eeeeee;".
            "padding-top:5px;padding-bottom:5px", "align"=>"center", "nowrap"),
            $this->add_action("Go")) ;

        return $div;
    }

    /**
     * Provide a mechanism to overload form_content_buttons() method
     * to have the button display "Filter" instead of "Save" and not
     * display the cancel button.
     *
     * @return HTMLTag object
     */
    function form_content_buttons_Filter()
    {
        $div = new DIVtag(array("style" => "background-color: #eeeeee;".
            "padding-top:5px;padding-bottom:5px", "align"=>"center", "nowrap"),
            $this->add_action("Filter")) ;

        return $div;
    }

    
    /**
     * Provide a mechanism to overload form_content_buttons() method
     * to have the button display "Ok" instead of "Save" and not
     * display the cancel button.
     *
     * @return HTMLTag object
     */
    function form_content_buttons_Ok()
    {
        $div = new DIVtag(array("style" => "background-color: #eeeeee;".
            "padding-top:5px;padding-bottom:5px", "align"=>"center", "nowrap"),
            $this->add_action("Ok")) ;

        return $div;
    }


    /**
     * Provide a mechanism to overload form_content_buttons() method
     * to have the button display "Login" instead of "Save" and not
     * display the cancel button.
     *
     * @return HTMLTag object
     */
    function form_content_buttons_Login()
    {
        $div = new DIVtag(array("style" => "background-color: #eeeeee;".
            "padding-top:5px;padding-bottom:5px", "align"=>"center", "nowrap"),
            $this->add_action("Login")) ;

        return $div;
    }


    /**
     * Provide a mechanism to overload form_content_buttons() method
     * to have the button display "Login" instead of "Save".
     *
     * @return HTMLTag object
     */
    function form_content_buttons_Login_Cancel()
    {
        $div = new DIVtag(array("style" => "background-color: #eeeeee;".
            "padding-top:5px;padding-bottom:5px", "align"=>"center", "nowrap"),
            $this->add_action("Login"), _HTML_SPACE, $this->add_cancel()) ;

        return $div;
    }

    /**
     * Provide a mechanism to overload form_content_buttons() method
     * to have the button display "Upload" instead of "Save".
     *
     * @return HTMLTag object
     */
    function form_content_buttons_Upload_Cancel()
    {
        $div = new DIVtag(array("style" => "background-color: #eeeeee;".
            "padding-top:5px;padding-bottom:5px", "align"=>"center", "nowrap"),
            $this->add_action("Upload"), _HTML_SPACE, $this->add_cancel()) ;

        return $div;
    }

    /**
     * Provide a mechanism to overload form_content_buttons() method
     * to have the button display "Confirm" instead of "Save".
     *
     * @return HTMLTag object
     */
    function form_content_buttons_Confirm_Cancel()
    {
        $div = new DIVtag(array("style" => "background-color: #eeeeee;".
            "padding-top:5px;padding-bottom:5px", "align"=>"center", "nowrap"),
            $this->add_action("Confirm"), _HTML_SPACE, $this->add_cancel()) ;

        return $div;
    }

    /**
     * Provide a mechanism to overload form_content_buttons() method
     * to have the button display "Confirm" instead of "Save".
     *
     * @return HTMLTag object
     */
    function form_content_buttons_Confirm_Only()
    {
        $div = new DIVtag(array("style" => "background-color: #eeeeee;".
            "padding-top:5px;padding-bottom:5px", "align"=>"center", "nowrap"),
            $this->add_action("Confirm")) ;

        return $div;
    }

    /**
     * Provide a mechanism to overload form_content_buttons() method
     * to have the button display "Delete" instead of "Save".
     *
     * @return HTMLTag object
     */
    function form_content_buttons_Delete_Cancel()
    {
        $div = new DIVtag(array("style" => "background-color: #eeeeee;".
            "padding-top:5px;padding-bottom:5px", "align"=>"center", "nowrap"),
            $this->add_action("Delete"), _HTML_SPACE, $this->add_cancel()) ;

        return $div;
    }

    /**
     * Provide a mechanism to overload form_content_buttons() method
     * to have the button display "Open" instead of "Save".
     *
     * @return HTMLTag object
     */
    function form_content_buttons_Open_Cancel()
    {
        $div = new DIVtag(array("style" => "background-color: #eeeeee;".
            "padding-top:5px;padding-bottom:5px", "align"=>"center", "nowrap"),
            $this->add_action("Open"), _HTML_SPACE, $this->add_cancel()) ;

        return $div;
    }

    /**
     * Provide a mechanism to overload form_content_buttons() method
     * to have the button display "Close" instead of "Save".
     *
     * @return HTMLTag object
     */
    function form_content_buttons_Close_Cancel()
    {
        $div = new DIVtag(array("style" => "background-color: #eeeeee;".
            "padding-top:5px;padding-bottom:5px", "align"=>"center", "nowrap"),
            $this->add_action("Close"), _HTML_SPACE, $this->add_cancel()) ;

        return $div;
    }

    /**
     * Provide a mechanism to overload form_content_buttons() method
     * to have the button display "Add" instead of "Save".
     *
     * @return HTMLTag object
     */
    function form_content_buttons_Add_Cancel()
    {
        $div = new DIVtag(array("style" => "background-color: #eeeeee;".
            "padding-top:5px;padding-bottom:5px", "align"=>"center", "nowrap"),
            $this->add_action("Add"), _HTML_SPACE, $this->add_cancel()) ;

        return $div;
    }

    /**
     * Provide a mechanism to overload form_content_buttons() method
     * to have the button display "Register" instead of "Save".
     *
     * @return HTMLTag object
     */
    function form_content_buttons_Register_Cancel()
    {
        $div = new DIVtag(array("style" => "background-color: #eeeeee;".
            "padding-top:5px;padding-bottom:5px", "align"=>"center", "nowrap"),
            $this->add_action("Register"), _HTML_SPACE, $this->add_cancel()) ;

        return $div;
    }

    /**
     * Provide a mechanism to overload form_content_buttons() method
     * to have the button display "Unregister" instead of "Save".
     *
     * @return HTMLTag object
     */
    function form_content_buttons_Unregister_Cancel()
    {
        $div = new DIVtag(array("style" => "background-color: #eeeeee;".
            "padding-top:5px;padding-bottom:5px", "align"=>"center", "nowrap"),
            $this->add_action("Unregister"), _HTML_SPACE, $this->add_cancel()) ;

        return $div;
    }

    /**
     * Provide a mechanism to overload form_content_buttons() method
     * to have the button display "Lock" instead of "Save".
     *
     * @return HTMLTag object
     */
    function form_content_buttons_Lock_Cancel()
    {
        $div = new DIVtag(array("style" => "background-color: #eeeeee;".
            "padding-top:5px;padding-bottom:5px", "align"=>"center", "nowrap"),
            $this->add_action("Lock"), _HTML_SPACE, $this->add_cancel()) ;

        return $div;
    }

    /**
     * Provide a mechanism to overload form_content_buttons() method
     * to have the button display "Unlock" instead of "Save".
     *
     * @return HTMLTag object
     */
    function form_content_buttons_Unlock_Cancel()
    {
        $div = new DIVtag(array("style" => "background-color: #eeeeee;".
            "padding-top:5px;padding-bottom:5px", "align"=>"center", "nowrap"),
            $this->add_action("Unlock"), _HTML_SPACE, $this->add_cancel()) ;

        return $div;
    }

    /**
     * Provide a mechanism to overload form_content_buttons() method
     * to have the button display "Unlock" instead of "Save".
     *
     * @return HTMLTag object
     */
    function form_content_buttons_Generate_Cancel()
    {
        $div = new DIVtag(array("style" => "background-color: #eeeeee;".
            "padding-top:5px;padding-bottom:5px", "align"=>"center", "nowrap"),
            $this->add_action("Generate"), _HTML_SPACE, $this->add_cancel()) ;

        return $div;
    }

    /**
     * Provide a mechanism to overload form_content_buttons() method
     * to have the button display "Assign" instead of "Save".
     *
     * @return HTMLTag object
     */
    function form_content_buttons_Assign_Cancel()
    {
        $div = new DIVtag(array("style" => "background-color: #eeeeee;".
            "padding-top:5px;padding-bottom:5px", "align"=>"center", "nowrap"),
            $this->add_action("Assign"), _HTML_SPACE, $this->add_cancel()) ;

        return $div;
    }

    /**
     * Constructor
     *
     * @param string - title
     * @param string - cancel page redirect
     * @param string - width of form
     */
    function FlipTurnForm($title, $cancel_action = null, $width = "100%")
    {
        $this->StandardFormContent($title, $cancel_action, $width) ;

        //  Turn of default confirmation

        $this->set_confirm(false) ;
        
        //  Use a 'dagger' character to denote required fields.

        $this->set_required_marker('&#134;');

        //  Turn on the colons for all labels.

	    $this->set_colon_flag(true) ;
    }

    //  Overload form_action() due to a bug with form confirmation
    //  as "Save" isn't handled when form confirmation is turned off.

    /**
     * This method handles the form action.
     * 
     * @return boolean TRUE = success
     *                 FALSE = failed.
     */
    function form_action() {
        switch ($this->get_action()) {
        case "Edit":
            return FALSE;
            break;
            
        case "Save":
        case "Login":
        case "Confirm":
        case "Register":
        case "Unregister":
            if ($this->has_confirm())
                return $this->confirm_action();
            else
                return true ;
            break;

        default:
            return FALSE;
            break;
        }
    }
}

/**
 * Construct the Swim Meet Import Results form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnSwimMeetForm
 */
class FlipTurnFileUploadForm extends FlipTurnForm
{
    /**
     * File Info property
     */
    var $__fileInfo ; 

    /**
     * File Info Table property
     */
    var $__fileInfoTable ; 

    /**
     * Upload File Label property
     */
    var $__uploadFileLabel = "Filename" ;

    /**
     * setUploadFileLabel()
     *
     * @param label - string
     */
    function setUploadFileLabel($label)
    {
        $this->__uploadFileLabel = $label ;
    }

    /**
     * getUploadFileLabel()
     *
     * @return label - string
     */
    function getUploadFileLabel()
    {
        return $this->__uploadFileLabel ;
    }

    /** 
     * This method returns the InfoTable widget. 
     */ 
    function get_file_info()
    { 
        return $this->__fileInfo ; 
    } 

    /** 
     * This method creates an InfoTable widget which 
     * is used to display information regarding the  
     * uploaded file. 
     */ 
    function set_file_info($fileInfo)
    { 
        $this->__fileInfo = $fileInfo ;
    }

    /** 
     * This method returns the InfoTable widget. 
     */ 
    function get_file_info_table()
    { 
        return $this->__fileInfoTable ; 
    } 

    /** 
     * This method creates an InfoTable widget which 
     * is used to display information regarding the  
     * uploaded file. 
     */ 
    function set_file_info_table($fileInfo)
    { 
        $it = new InfoTable("File Upload Summary", 400) ; 

        $lines = file($fileInfo['tmp_name']) ; 

        $it->add_row("Filename", $fileInfo['name']) ; 
        if (FT_DEBUG)
            $it->add_row("Temporary Filename", $fileInfo['tmp_name']) ; 
        $it->add_row("File Size", filesize($fileInfo['tmp_name'])) ; 
        $it->add_row("Lines", count($lines)) ; 

        unset($lines) ; 

        $this->__fileInfoTable = &$it ; 
    } 

    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        $uploadedfile = new FEFile($this->getUploadFileLabel(), true, "400px") ; 
        $uploadedfile->set_max_size(10240000000) ; 
        $uploadedfile->set_temp_dir(ini_get('upload_tmp_dir')) ; 

        $this->add_element($uploadedfile) ;
    }

    /**
     * This method is called only the first time the form
     * page is hit.  This enables u to query a DB and 
     * pre populate the FormElement objects with data.
     *
     */
    function form_init_data()
    {
    }

    /**
     * This is the method that builds the layout of where the
     * FormElements will live.  You can lay it out any way
     * you like.
     *
     */
    function form_content()
    {
        $table = html_table($this->_width,0,4) ;
        $table->set_style("border: 0px solid") ;

        $table->add_row($this->element_label($this->getUploadFileLabel()),
            $this->element_form($this->getUploadFileLabel())) ;

        $this->add_form_block(null, $table) ;
    }

    /**
     * This method gets called after the FormElement data has
     * passed the validation.  This enables you to validate the
     * data against some backend mechanism, say a DB.
     *
     */
    function form_backend_validation()
    {
	    return true ;
    }

    /**
     * This method is called ONLY after ALL validation has
     * passed.  This is the method that allows you to 
     * do something with the data, say insert/update records
     * in the DB.
     */
    function form_action()
    {
        $success = true ;

        $this->set_action_message(html_div('ft-note-nsg', 'File "' . 
            $this->get_element_value($this->getUploadFileLabel()) .
            '" successfully uploaded.')) ; 
        $file = $this->get_element($this->getUploadFileLabel()) ; 
        $fileInfo = $file->get_file_info() ; 

        $this->set_file_info($fileInfo) ; 
        $this->set_file_info_table($fileInfo) ; 

        //  Delete the file so we don't keep a lot of stuff around. 

        if (!unlink($fileInfo['tmp_name'])) 
            $this->add_error($this->getUploadFileLabel(),
                "Unable to remove uploaded file."); 

        $this->set_action_message(html_div('ft-note-msg', 'File successfully uploaded.')) ;

        return $success ;
    }

    /**
     * Overload form_content_buttons() method to have the
     * button display "Upload" instead of the default "Save".
     *
     */
    function form_content_buttons()
    {
        return $this->form_content_buttons_Upload_Cancel() ;
    }
}

/**
 * Construct the Flip Turn Admin login/logout form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnForm
 */
class FlipTurnAdminLoginForm extends FlipTurnForm
{
    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        $password = new FEPassword("Password", true, "225px") ; 
        $this->add_element($password) ;
    }

    /**
     * This is the method that builds the layout of where the
     * FormElements will live.  You can lay it out any way
     * you like.
     *
     */
    function form_content()
    {
        $table = html_table($this->_width,0,4) ;
        $table->set_style("border: 0px solid") ;

        $table->add_row($this->element_label('Password'),
            $this->element_form('Password')) ;

        $this->add_form_block(null, $table) ;
    }

    /**
     * This method gets called after the FormElement data has
     * passed the validation.  This enables you to validate the
     * data against some backend mechanism, say a DB.
     *
     */
    function form_backend_validation()
    {
        return ($this->get_element_value('Password') == FT_PASSWORD) ;
    }

    /**
     * This method is called ONLY after ALL validation has
     * passed.  This is the method that allows you to 
     * do something with the data, say insert/update records
     * in the DB.
     */
    function form_action()
    {
        if (session_id() == "") session_start() ;

        $_SESSION[FT_LOGIN_STATUS] = true ;
        $this->set_action_message(html_div('ft-note-msg', 'Admin login successful.')) ;

        return true ;
    }

    /**
     * Overload form_content_buttons() method to have the
     * button display "Upload" instead of the default "Save".
     *
     */
    function form_content_buttons()
    {
        return $this->form_content_buttons_Confirm_Cancel() ;
    }
}

/**
 * Construct the Flip Turn Admin login/logout form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnForm
 */
class FlipTurnAdminLogoutForm extends FlipTurnForm
{
    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        $logout = new FEYesNoRadioGroup('Confirm Logout') ;
        $this->add_element($logout) ;
    }

    /**
     * This is the method that builds the layout of where the
     * FormElements will live.  You can lay it out any way
     * you like.
     *
     */
    function form_content()
    {
        $table = html_table($this->_width,0,4) ;
        $table->set_style("border: 0px solid") ;

        $table->add_row($this->element_label('Confirm Logout'),
            $this->element_form('Confirm Logout')) ;

        $this->add_form_block(null, $table) ;
    }

    /**
     * This method gets called after the FormElement data has
     * passed the validation.  This enables you to validate the
     * data against some backend mechanism, say a DB.
     *
     */
    function form_backend_validation()
    {
        return ($this->get_element_value('Confirm Logout') == 'yes') ;
    }

    /**
     * This method is called ONLY after ALL validation has
     * passed.  This is the method that allows you to 
     * do something with the data, say insert/update records
     * in the DB.
     */
    function form_action()
    {
        if (session_id() == "") session_start() ;

        $_SESSION[FT_LOGIN_STATUS] = false ;

        $this->set_action_message(html_div('ft-note-msg', 'Admin logout successful.')) ;
        return true ;
    }

    /**
     * Overload form_content_buttons() method to have the
     * button display "Upload" instead of the default "Save".
     *
     */
    function form_content_buttons()
    {
        return $this->form_content_buttons_Confirm_Cancel() ;
    }
}

/**
 * Construct the Genereic Purge form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnForm
 */
class FlipTurnPurgeForm extends FlipTurnForm
{
    /**
     * Purge Label
     */
    var $_purge_label = 'Purge' ;

    /**
     * Purge Message
     */
    var $_purge_message = 'Purging will delete all records
        currently stored in the  database.  This action cannot be
        reversed.  Make sure all data has been saved appropriately
        prior to performing this action.' ;

    /**
     * Set Purge Label
     *
     * @param string label
     */
    function setPurgeLabel($label = 'Purge')
    {
        $this->_purge_label = $label ;
    }

    /**
     * Get Purge Label
     *
     * @return string label
     */
    function getPurgeLabel()
    {
        return $this->_purge_label ;
    }

    /**
     * Set Purge Message
     *
     * @param string message
     */
    function setPurgeMessage($message = 'Purge')
    {
        $this->_purge_message = $message ;
    }

    /**
     * Get Purge Message
     *
     * @return string message
     */
    function getPurgeMessage()
    {
        return $this->_purge_message ;
    }

    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        $confirm = new FECheckBox($this->getPurgeLabel()) ;
        $this->add_element($confirm) ;
    }

    /**
     * This method is called only the first time the form
     * page is hit.  This enables u to query a DB and 
     * pre populate the FormElement objects with data.
     *
     */
    function form_init_data()
    {
    }

    /**
     * This is the method that builds the layout of where the
     * FormElements will live.  You can lay it out any way
     * you like.
     *
     */
    function form_content()
    {
        $table = html_table($this->_width,0,4) ;
        $table->set_style("border: 0px solid") ;

        $msg = html_div("ft_form_msg") ;
        $msg->add(html_p($this->getPurgeMessage(), html_br())) ;

        $table->add_row($msg) ;
        $table->add_row($this->element_form($this->getPurgeLabel())) ;

        $this->add_form_block(null, $table) ;
    }

    /**
     * This method gets called after the FormElement data has
     * passed the validation.  This enables you to validate the
     * data against some backend mechanism, say a DB.
     *
     */
    function form_backend_validation()
    {
        $valid = true ;

        //  User must tick the checkbox to proceed!

        if (is_null($this->get_element_value($this->getPurgeLabel())))
        {
            $valid = false ;
            $this->add_error($this->getPurgeLabel(), "Checkbox not selected.") ;
        }

	    return $valid ;
    }

    /**
     * This method is called ONLY after ALL validation has
     * passed.  This is the method that allows you to 
     * do something with the data, say insert/update records
     * in the DB.
     */
    function form_action()
    {
        user_error("FlipTurnPurgeForm::form_action() - Child must override") ;
    }

    /**
     * Overload form_content_buttons() method to have the
     * button display "Confirm" instead of the default "Save".
     *
     */
    function form_content_buttons()
    {
        return $this->form_content_buttons_Confirm_Only() ;
    }
}

/**
 * Construct the Genereic EditPage form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnForm
 */
class FlipTurnEditPageForm extends FlipTurnForm
{
    /**
     * Edit Page Label
     */
    var $_edit_page_label = 'Edit Page' ;

    /**
     * Set Edit Page Label
     *
     * @param string label
     */
    function setEditPageLabel($label = 'EditPage')
    {
        $this->_edit_page_label = $label ;
    }

    /**
     * Get Edit Page Label
     *
     * @return string label
     */
    function getEditPageLabel()
    {
        return $this->_edit_page_label ;
    }

    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        $content = new FETinyMCETextArea($this->getEditPageLabel(),
            true, 30, 132, '100%', '500px') ;
        $this->add_element($content) ;
    }

    /**
     * This method is called only the first time the form
     * page is hit.  This enables u to query a DB and 
     * pre populate the FormElement objects with data.
     *
     */
    function form_init_data()
    {
    }

    /**
     * This is the method that builds the layout of where the
     * FormElements will live.  You can lay it out any way
     * you like.
     *
     */
    function form_content()
    {
        $table = html_table($this->_width,0,4) ;
        $table->set_style("border: 0px solid") ;

        $table->add_row($this->element_label($this->getEditPageLabel())) ;
        $table->add_row($this->element_form($this->getEditPageLabel())) ;

        $this->add_form_block(null, $table) ;
    }

    /**
     * This method gets called after the FormElement data has
     * passed the validation.  This enables you to validate the
     * data against some backend mechanism, say a DB.
     *
     */
    function form_backend_validation()
    {
        $valid = true ;

	    return $valid ;
    }

    /**
     * This method is called ONLY after ALL validation has
     * passed.  This is the method that allows you to 
     * do something with the data, say insert/update records
     * in the DB.
     */
    function form_action()
    {
        user_error("FlipTurnEditPageForm::form_action() - Child must override") ;
    }

}

/**
 * Construct the About Edit Page form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnForm
 */
class FlipTurnEditAboutPageForm extends FlipTurnEditPageForm
{
    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        $this->setEditPageLabel('Edit About Page') ;
        parent::form_init_elements() ;
    }

    /**
     * This method is called only the first time the form
     * page is hit.  This enables u to query a DB and 
     * pre populate the FormElement objects with data.
     *
     */
    function form_init_data()
    {
        $content = new FlipTurnOptionMeta() ;

        //  Account for no data in the options table
        if ($content->existOptionMetaByKey(FT_ABOUT_PAGE_OPTION))
        {
            $content->loadOptionMetaByKey(FT_ABOUT_PAGE_OPTION) ;
            $this->set_element_value($this->getEditPageLabel(), $content->getOptionMetaValue()) ;
        }
        else
            $this->set_element_value($this->getEditPageLabel(), FT_ABOUT_PAGE_OPTION_DEFAULT_CONTENT) ;
    }

    /**
     * This method is called ONLY after ALL validation has
     * passed.  This is the method that allows you to 
     * do something with the data, say insert/update records
     * in the DB.
     */
    function form_action()
    {
        $content = new FlipTurnOptionMeta() ;
        $content->setOptionMetaKey(FT_ABOUT_PAGE_OPTION) ;
        $content->setOptionMetaValue(htmlspecialchars($this->get_element_value($this->getEditPageLabel()))) ;
        $content->saveOptionMeta() ;
        $this->set_action_message(html_div('ft-note-msg', 'About page content updated.')) ;
        return true ;
    }
}

/**
 * Construct the Legal Edit Page form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnForm
 */
class FlipTurnEditLegalPageForm extends FlipTurnEditPageForm
{
    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        $this->setEditPageLabel('Edit Legal Page') ;
        parent::form_init_elements() ;
    }

    /**
     * This method is called only the first time the form
     * page is hit.  This enables u to query a DB and 
     * pre populate the FormElement objects with data.
     *
     */
    function form_init_data()
    {
        $content = new FlipTurnOptionMeta() ;

        //  Account for no data in the options table
        if ($content->existOptionMetaByKey(FT_LEGAL_PAGE_OPTION))
        {
            $content->loadOptionMetaByKey(FT_LEGAL_PAGE_OPTION) ;
            $this->set_element_value($this->getEditPageLabel(), $content->getOptionMetaValue()) ;
        }
        else
            $this->set_element_value($this->getEditPageLabel(), FT_LEGAL_PAGE_OPTION_DEFAULT_CONTENT) ;
    }

    /**
     * This method is called ONLY after ALL validation has
     * passed.  This is the method that allows you to 
     * do something with the data, say insert/update records
     * in the DB.
     */
    function form_action()
    {
        $content = new FlipTurnOptionMeta() ;
        $content->setOptionMetaKey(FT_LEGAL_PAGE_OPTION) ;
        $content->setOptionMetaValue(htmlspecialchars($this->get_element_value($this->getEditPageLabel()))) ;
        $content->saveOptionMeta() ;
        $this->set_action_message(html_div('ft-note-msg', 'Legal page content updated.')) ;
        return true ;
    }
}

/**
 * Construct the Privacy Edit Page form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnForm
 */
class FlipTurnEditPrivacyPageForm extends FlipTurnEditPageForm
{
    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        $this->setEditPageLabel('Edit Privacy Page') ;
        parent::form_init_elements() ;
    }

    /**
     * This method is called only the first time the form
     * page is hit.  This enables u to query a DB and 
     * pre populate the FormElement objects with data.
     *
     */
    function form_init_data()
    {
        $content = new FlipTurnOptionMeta() ;

        //  Account for no data in the options table
        if ($content->existOptionMetaByKey(FT_PRIVACY_PAGE_OPTION))
        {
            $content->loadOptionMetaByKey(FT_PRIVACY_PAGE_OPTION) ;
            $this->set_element_value($this->getEditPageLabel(), $content->getOptionMetaValue()) ;
        }
        else
            $this->set_element_value($this->getEditPageLabel(), FT_PRIVACY_PAGE_OPTION_DEFAULT_CONTENT) ;
    }

    /**
     * This method is called ONLY after ALL validation has
     * passed.  This is the method that allows you to 
     * do something with the data, say insert/update records
     * in the DB.
     */
    function form_action()
    {
        $content = new FlipTurnOptionMeta() ;
        $content->setOptionMetaKey(FT_PRIVACY_PAGE_OPTION) ;
        $content->setOptionMetaValue(htmlspecialchars($this->get_element_value($this->getEditPageLabel()))) ;
        $content->saveOptionMeta() ;
        $this->set_action_message(html_div('ft-note-msg', 'Privacy page content updated.')) ;
        return true ;
    }
}

/**
 * Construct the Home Edit Page form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnForm
 */
class FlipTurnEditHomePageForm extends FlipTurnEditPageForm
{
    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        $this->setEditPageLabel('Edit Home Page') ;
        parent::form_init_elements() ;
    }

    /**
     * This method is called only the first time the form
     * page is hit.  This enables u to query a DB and 
     * pre populate the FormElement objects with data.
     *
     */
    function form_init_data()
    {
        $content = new FlipTurnOptionMeta() ;

        //  Account for no data in the options table
        if ($content->existOptionMetaByKey(FT_HOME_PAGE_OPTION))
        {
            $content->loadOptionMetaByKey(FT_HOME_PAGE_OPTION) ;
            $this->set_element_value($this->getEditPageLabel(), $content->getOptionMetaValue()) ;
        }
        else
            $this->set_element_value($this->getEditPageLabel(), FT_HOME_PAGE_OPTION_DEFAULT_CONTENT) ;
    }

    /**
     * This method is called ONLY after ALL validation has
     * passed.  This is the method that allows you to 
     * do something with the data, say insert/update records
     * in the DB.
     */
    function form_action()
    {
        $content = new FlipTurnOptionMeta() ;
        $content->setOptionMetaKey(FT_HOME_PAGE_OPTION) ;
        $content->setOptionMetaValue(htmlspecialchars($this->get_element_value($this->getEditPageLabel()))) ;
        $content->saveOptionMeta() ;
        $this->set_action_message(html_div('ft-note-msg', 'Home page content updated.')) ;
        return true ;
    }
}

/**
 * This is the TinyMCETextArea FormElement which builds a 
 * textarea field with TinyMCE controls. It has no validation method.
 * 
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FETextArea
 *
 * @copyright LGPL - See LICENCE
 */
class FETinyMCETextArea extends FETextArea
{
    /**
     * The constructor
     *
     * @param label string - text label for the element
     * @param bool required - is this a required element
     * @param int required - the rows attribute
     * @param int required - the cols attribute
     * @param int optional - element width in pixels (px), percentage (%) or elements (em)
     * @param int optional - element height in pixels (px), percentage (%) or elements (em)     
     * @param int optional - the number of characters to limit the value to.
     */
    function FETinyMCETextArea($label, $required = TRUE, $rows,
        $cols, $width = NULL, $height = NULL, $limit_char_count=-1)
    {        
        parent::FETextArea($label, $required, $rows, $cols, $width, $height, $limit_char_count) ;
    }

    /**
     * Javascript for the TinyMCE Text Area
     *
     * @return mixed container
     */
    function javascript()
    {
        $js = 'tinyMCE.init({
            mode : "exact", elements : "' .  $this->get_element_name() . '",
            theme : "advanced",
            skin : "o2k7",
		    plugins : "pagebreak,style,layer,table,save,advhr,advimage,advlink,emotions,iespell,insertdatetime,preview,media,searchreplace,print,contextmenu,paste,directionality,fullscreen,noneditable,visualchars,nonbreaking,xhtmlxtras,template,inlinepopups,autosave",
            // Theme options
		    theme_advanced_buttons1 : "save,newdocument,|,bold,italic,underline,strikethrough,|,justifyleft,justifycenter,justifyright,justifyfull,styleselect,formatselect,fontselect,fontsizeselect",
		    theme_advanced_buttons2 : "cut,copy,paste,pastetext,pasteword,|,search,replace,|,bullist,numlist,|,outdent,indent,blockquote,|,undo,redo,|,link,unlink,anchor,image,cleanup,help,code,|,insertdate,inserttime,preview,|,forecolor,backcolor",
		    theme_advanced_buttons3 : "tablecontrols,|,hr,removeformat,visualaid,|,sub,sup,|,charmap,emotions,iespell,media,advhr,|,print,|,ltr,rtl,|,fullscreen",
		    theme_advanced_buttons4 : "insertlayer,moveforward,movebackward,absolute,|,styleprops,|,cite,abbr,acronym,del,ins,attribs,|,visualchars,nonbreaking,pagebreak,restoredraft",
   	        theme_advanced_toolbar_location : "top",
		    theme_advanced_toolbar_align : "left",
            theme_advanced_statusbar_location : "bottom"
        });' ;

        return $js ;
    }
}
?>
