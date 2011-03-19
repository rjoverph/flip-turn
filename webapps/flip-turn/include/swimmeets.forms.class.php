<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 *
 * $Id$
 *
 * Plugin initialization.  This code will ensure that the
 * include_path is correct for phpHtmlLib, PEAR, and the local
 * site class and include files.
 *
 * (c) 2007 by Mike Walsh
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Wp-SwimTeam
 * @subpackage SwimMeets
 * @version $Revision$
 * @lastmodified $Author$
 * @lastmodifiedby $Date$
 *
 */

require_once("ft.include.php") ;
require_once("sdif.include.php") ;
require_once("forms.class.php") ;
require_once("swimmeets.class.php") ;

/**
 * Construct the base Swim Meet form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnForm
 */
class FlipTurnSwimMeetForm extends FlipTurnForm
{
    /**
     * meet id property - used to track the swim meet record
     */

    var $_swimmeetid ;

    /**
     * swim meet property - used to store an instance
     */
    var $_swimmeet = null ;

    /**
     * Set the swim meet id property
     */
    function setSwimMeetId($id)
    {
        $this->_swimmeetid = $id ;
    }

    /**
     * Get the swim meet id property
     */
    function getSwimMeetId()
    {
        return $this->_swimmeetid ;
    }

    /**
     * Set the swim meet property
     */
    function setSwimMeet($swimmeet)
    {
        $this->_swimmeet = $swimmeet ;
    }

    /**
     * Get the swim meet property
     */
    function getSwimMeet()
    {
        return $this->_swimmeet ;
    }

    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        $this->add_hidden_element("swimmeetid") ;

        //  This is used to remember the action
        //  which originated from the GUIDataList.
 
        $this->add_hidden_element("_action") ;
    }
}

/**
 * Construct the Add Swim Meet form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnForm
 */
class SwimMeetAddForm extends FlipTurnSwimMeetForm
{
    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        $this->add_hidden_element("swimmeetid") ;

        //  This is used to remember the action
        //  which originated from the GUIDataList.
 
        $this->add_hidden_element("_action") ;

		//  Org Code field

        $orgcode = new FEListBox("Organization", true, "150px");
        $orgcode->set_list_data(SDIFCodeTableMappings::GetOrgCodes()) ;
        $this->add_element($orgcode) ;

		//  Meet Name field

        $meetname = new FEText("Meet Name", true, "300px");
        $this->add_element($meetname) ;

		//  Meet Address 1 field

        $meetaddress1 = new FEText("Meet Address 1", false, "300px");
        $this->add_element($meetaddress1) ;

		//  Meet Address 2 field

        $meetaddress2 = new FEText("Meet Address 2", false, "300px");
        $this->add_element($meetaddress2) ;

        //  Meet State

        $meetstate = new FEUnitedStates("Meet State", FT_US_ONLY, "150px");
        $this->add_element($meetstate) ;

		//  Meet Postal Code field

        $meetpostalcode = new FEText("Meet Postal Code", false, "200px");
        $this->add_element($meetpostalcode) ;

        //  Meet Country

        $meetcountry = new FEListBox("Meet Country", true, "250px");
        $meetcountry->set_list_data(SDIFCodeTableMappings::GetCountryCodes()) ;
        $meetcountry->set_readonly(FT_US_ONLY) ;
        $this->add_element($meetcountry) ;

		//  Meet Code field

        $meetcode = new FEListBox("Meet Code", true, "150px");
        $meetcode->set_list_data(SDIFCodeTableMappings::GetMeetCodes()) ;
        $this->add_element($meetcode) ;

        //  Meet Start Field

        $meetstart = new FEDate("Meet Start", true, null, null,
                "Fdy", date("Y") - 3, date("Y") + 7) ;
        $this->add_element($meetstart) ;

        //  Meet End Field

        $meetend = new FEDate("Meet End", true, null, null,
                "Fdy", date("Y") - 3, date("Y") + 7) ;
        $this->add_element($meetend) ;

		//  Pool Altitude field

        $poolaltitude = new FENumber("Pool Altitude", true, "150px") ;
        $this->add_element($poolaltitude) ;

		//  Course Code field

        $coursecode = new FEListBox("Course Code", true, "150px");
        $coursecode->set_list_data(SDIFCodeTableMappings::GetCourseCodes()) ;
        $this->add_element($coursecode) ;
    }

    /**
     * This method is called only the first time the form
     * page is hit.  This enables u to query a DB and 
     * pre populate the FormElement objects with data.
     *
     */
    function form_init_data()
    {
        //  Initialize the form fields

        $this->set_hidden_element_value("_action", FT_ACTION_ADD) ;

        $this->set_element_value("Meet Start", array("year" => date("Y"),
            "month" => date("m"), "day" => date("d"))) ;
        $this->set_element_value("Meet End", array("year" => date("Y"),
            "month" => date("m"), "day" => date("d"))) ;

        //  If the config is set to US only, initialize the country

        if (FT_US_ONLY)
            $this->set_element_value("Meet Country",
                FT_SDIF_COUNTRY_CODE_UNITED_STATES_OF_AMERICA_VALUE) ;

        $this->set_element_value("Pool Altitude", "0") ;
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
        $table->set_style("border: 1px solid") ;

        $table->add_row($this->element_label("Organization"),
            $this->element_form("Organization")) ;

        $table->add_row($this->element_label("Meet Name"),
            $this->element_form("Meet Name")) ;

        $table->add_row($this->element_label("Meet Address 1"),
            $this->element_form("Meet Address 1")) ;

        $table->add_row($this->element_label("Meet Address 2"),
            $this->element_form("Meet Address 2")) ;

        $table->add_row($this->element_label("Meet State"),
            $this->element_form("Meet State")) ;

        $table->add_row($this->element_label("Meet Postal Code"),
            $this->element_form("Meet Postal Code")) ;

        $table->add_row($this->element_label("Meet Country"),
            $this->element_form("Meet Country")) ;

        $table->add_row($this->element_label("Meet Code"),
            $this->element_form("Meet Code")) ;

        $table->add_row($this->element_label("Meet Start"),
            $this->element_form("Meet Start")) ;

        $table->add_row($this->element_label("Meet End"),
            $this->element_form("Meet End")) ;

        $table->add_row($this->element_label("Pool Altitude"),
            $this->element_form("Pool Altitude")) ;

        $table->add_row($this->element_label("Course Code"),
            $this->element_form("Course Code")) ;

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

        $this->setSwimMeet(new SwimMeet()) ;
        $swimmeet = $this->getSwimMeet() ;

        $swimmeet->setOrgCode($this->get_element_value('Organization')) ;
        $swimmeet->setMeetName($this->get_element_value('Meet Name')) ;
        $swimmeet->setMeetAddress1($this->get_element_value('Meet Address 1')) ;
        $swimmeet->setMeetAddress2($this->get_element_value('Meet Address 2')) ;
        $swimmeet->setMeetState($this->get_element_value('Meet State')) ;
        $swimmeet->setMeetCountryCode($this->get_element_value('Meet Country')) ;
        $swimmeet->setMeetCode($this->get_element_value('Meet Code')) ;

        $date = $this->get_element_value('Meet Start') ;
        $swimmeet->setMeetStart($date['month'] . $date['day'] . $date['year']) ;

        $date = $this->get_element_value('Meet End') ;
        $swimmeet->setMeetEnd($date['month'] . $date['day'] . $date['year']) ;

        $swimmeet->setPoolAltitude($this->get_element_value('Pool Altitude')) ;
        $swimmeet->setCourseCode($this->get_element_value('Course Code')) ;

        if ($swimmeet->SwimMeetExistsByName())
        {
            $valid = false ;
            $this->add_error('Meet Name', 'A meet with this name already exists in the database') ;
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
        //  After passing validation, all of the meet data
        //  should be stored in the Swim Meet class instance.

        $swimmeet = $this->getSwimMeet() ;

        $success = $swimmeet->AddSwimMeet() ;

        //  If successful, store the added age group id in so it can be used later.

        if ($success) 
        {
            $meet->setMeetId($success) ;
            $this->set_action_message(html_div('ft-note-msg', 'Swim Meet successfully added.')) ;
        }
        else
        {
            $this->set_action_message(html_div('ft-warning-msg', 'Swim Meet was not successfully added.')) ;
        }

        return $success ;
    }

    /**
     * Construct a container with a success message
     * which can be displayed after form processing
     * is complete.
     *
     * @return Container
     */
    function form_success()
    {
        $container = container() ;
        $container->add($this->_action_message) ;

        return $container ;
    }
}

/**
 * Construct the Update Swim Meet form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnSwimMeetAddForm
 */
class SwimMeetUpdateForm extends SwimMeetAddForm
{
    /**
     * This method is called only the first time the form
     * page is hit.  This enables u to query a DB and 
     * pre populate the FormElement objects with data.
     *
     */
    function form_init_data()
    {
        $this->set_hidden_element_value('_action', FT_ACTION_UPDATE) ;
        $this->set_hidden_element_value('swimmeetid', $this->getSwimMeetId()) ;

        $swimmeet = new SwimMeet() ;
        $swimmeet->LoadSwimMeetById($this->getSwimMeetId()) ;

        $this->set_element_value('Organization', $swimmeet->getOrgCode()) ;
        $this->set_element_value('Meet Name', $swimmeet->getMeetName()) ;
        $this->set_element_value('Meet Address 1', $swimmeet->getMeetAddress1()) ;
        $this->set_element_value('Meet Address 2', $swimmeet->getMeetAddress2()) ;
        $this->set_element_value('Meet State', $swimmeet->getMeetState()) ;
        $this->set_element_value('Meet Postal Code', $swimmeet->getMeetPostalCode()) ;
        $this->set_element_value('Meet Country', $swimmeet->getMeetCountryCode()) ;
        $this->set_element_value('Meet Code', $swimmeet->getMeetCode()) ;
        $this->set_element_value('Pool Altitude', $swimmeet->getPoolAltitude()) ;
        $this->set_element_value('Course Code', $swimmeet->getCourseCode()) ;

        $date = $swimmeet->getMeetStart(false) ;
        $this->set_element_value('Meet Start', array('year' => substr($date, 4, 4),
            'month' => substr($date, 0, 2), 'day' => substr($date, 2, 2))) ;

        $date = $swimmeet->getMeetEnd(false) ;
        $this->set_element_value('Meet End', array('year' => substr($date, 4, 4),
            'month' => substr($date, 0, 2), 'day' => substr($date, 2, 2))) ;
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

        $this->setSwimMeet(new SwimMeet()) ;
        $swimmeet = $this->getSwimMeet() ;

        //  Need to make sure that the update isn't changing the
        //  swim meet to match something which already exists in
        //  the database.

        $swimmeet->LoadSwimMeetById($this->get_hidden_element_value('swimmeetid')) ;
        $oldmeetname = $swimmeet->getMeetName() ;

        $swimmeet->setOrgCode($this->get_element_value('Organization')) ;
        $swimmeet->setMeetName($this->get_element_value('Meet Name')) ;
        $swimmeet->setMeetAddress1($this->get_element_value('Meet Address 1')) ;
        $swimmeet->setMeetAddress2($this->get_element_value('Meet Address 2')) ;
        $swimmeet->setMeetState($this->get_element_value('Meet State')) ;
        $swimmeet->setMeetCountryCode($this->get_element_value('Meet Country')) ;
        $swimmeet->setMeetCode($this->get_element_value('Meet Code')) ;

        $date = $this->get_element_value('Meet Start') ;
        $swimmeet->setMeetStart(sprintf("%02s%02s%04s", $date['month'], $date['day'], $date['year'])) ;

        $date = $this->get_element_value('Meet End') ;
        $swimmeet->setMeetEnd(sprintf("%02s%02s%04s", $date['month'], $date['day'], $date['year'])) ;

        $swimmeet->setPoolAltitude($this->get_element_value('Pool Altitude')) ;
        $swimmeet->setCourseCode($this->get_element_value('Course Code')) ;

        if ($swimmeet->SwimMeetExistsByName() && ($oldmeetname != $swimmeet->getMeetName()))
        {
            $valid = false ;
            $this->add_error('Meet Name', 'A meet with this name already exists in the database') ;
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
        //  After passing validation, all of the meet data
        //  should be stored in the Swim Meet class instance.

        $swimmeet = $this->getSwimMeet() ;

        $success = $swimmeet->UpdateSwimMeet() ;

        //  If successful, store the updated meet id in so it can be used later.

        if ($success) 
        {
            $swimmeet->setSwimMeetId($success) ;
            $this->set_action_message(html_div('ft-note-msg', 'Swim Meet successfully updated.')) ;
        }
        else
        {
            $this->set_action_message(html_div('ft-warning-msg', 'Swim Meet was not successfully updated.')) ;
        }

        return $success ;
    }
}

/**
 * Construct the Delete Swim Meet form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnSwimMeetUpdateForm
 */
class SwimMeetDeleteForm extends SwimMeetUpdateForm
{
    /**
     * This method is called only the first time the form
     * page is hit.  This enables u to query a DB and 
     * pre populate the FormElement objects with data.
     *
     */
    function form_init_data($action = FT_ACTION_DELETE)
    {
        parent::form_init_data($action) ;
    }

    /**
     * Validate the form elements.  In this case, there is
     * no need to validate anything because it is a delete
     * operation and the form elements are disabled and
     * not passed to the form processor.
     *
     * @return boolean
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
        $meet = new SwimTeamSwimMeet() ;
        $meet->setId($this->get_hidden_element_value("meetid")) ;
        $success = $meet->deleteSwimMeet() ;

        if ($success) 
            $this->set_action_message(html_div('ft-note-msg', 'Swim Meet successfully deleted.')) ;
        else
            $this->set_action_message(html_div('ft-warning-msg', 'Swim Meet was not successfully deleted.')) ;

        return $success ;
    }

    /**
     * Overload form_content_buttons() method to have the
     * button display "Delete" instead of the default "Save".
     *
     */
    function form_content_buttons()
    {
        return $this->form_content_buttons_Delete_Cancel() ;
    }
}

/**
 * Construct the Swim Meets Purge form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnSwimMeetForm
 */
class SwimMeetsPurgeForm extends FlipTurnPurgeForm
{
    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        $this->setPurgeLabel('Purge Swim Meets') ;
        $this->setPurgeMessage('Purging the Swim Meets will delete all
            swim meets currently stored in the database.  This action
            cannot be reversed.  Make sure all data has been saved
            appropriately prior to performing this action.') ;

        parent::form_init_elements() ;
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

        $swimmeet = new SwimMeet() ;
        $swimmeet->PurgeSwimMeets() ;

        $this->set_action_message(html_div(sprintf('ft-%s-msg',
            $swimmeet->getAffectedRows() == 0 ? 'warning' : 'note'),
            sprintf('%d record%s purged from Swim Meets database.',
            $swimmeet->getAffectedRows(),
            $swimmeet->getAffectedRows() == 1 ? '' : 's'))) ;

        unset($swimmeet) ;

        return $success ;
    }
}
?>
