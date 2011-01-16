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
    
    function set_action_message($message, $class = "ftactionmsg")
    {
        parent::set_action_message(html_div($class, html_h4($message))) ;
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

        $this->set_action_message("File \"" . 
            $this->get_element_value($this->getUploadFileLabel()) .
            "\" successfully uploaded.") ; 
        $file = $this->get_element($this->getUploadFileLabel()) ; 
        $fileInfo = $file->get_file_info() ; 

        $this->set_file_info($fileInfo) ; 
        $this->set_file_info_table($fileInfo) ; 

        //  Delete the file so we don't keep a lot of stuff around. 

        if (!unlink($fileInfo['tmp_name'])) 
            $this->add_error($this->getUploadFileLabel(),
                "Unable to remove uploaded file."); 

        $this->set_action_message("File successfully uploaded.") ;

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
        var_dump(basename(__FILE__) . '::' . __LINE__) ;
        if (session_id() == "") session_start() ;

        $_SESSION[FT_LOGIN_STATUS] = true ;
        $this->set_action_message("Admin login successful.") ;

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
        var_dump(basename(__FILE__) . '::' . __LINE__) ;
        if (session_id() == "") session_start() ;

        $_SESSION[FT_LOGIN_STATUS] = false ;

        $this->set_action_message("Admin logout successful.") ;
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
?>
