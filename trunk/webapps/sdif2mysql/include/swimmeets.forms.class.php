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
 * Construct the base SwimMeet form
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
 * Construct the Add SwimMeet form
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
    function form_backend_validation($checkexists = true)
    {
        $valid = true ;

        //  Make sure swim meet is unique

        //$meet = new SwimMeet() ;

        //$meet->setSeasonId($this->get_element_value("Season")) ;
        //$meet->setOpponentSwimClubId($this->get_element_value("Opponent")) ;
        //$meet->setMeetType($this->get_element_value("Meet Type")) ;
        //$meet->setParticipation($this->get_element_value("Participation")) ;
        //$meet->setMeetDescription($this->get_element_value("Description")) ;
        //$meet->setLocation($this->get_element_value("Location")) ;
        //$meet->setMeetDate($this->get_element_value("Date")) ;

        //$time = $this->get_element_value("Time") . ":" .
            //$this->get_element_value("Minutes") . ":00" ;
        //$meet->setMeetTime($time) ;

        //  Check existance?
 
        //if ($checkexists)
        //{
            //if ($meet->getSwimMeetExists())
            //{
                //$this->add_error("Season", "Similar swim meet already exists.");
                //$this->add_error("Opponent", "Similar swim meet already exists.");
                //$this->add_error("Date", "Similar swim meet already exists.");
                //$valid = false ;
            //}
        //}

        //  Make sure dates are reasonable - is it during the season?
        
        //$season = new SwimTeamSeason() ;
        //$season->loadSeasonById($meet->getSeasonId()) ;

        //$s = $season->getSeasonStartAsArray() ;
        //$st = strtotime(sprintf("%04s-%02s-%02s", $s["year"], $s["month"], $s["day"])) ;

        //$e = $season->getSeasonEndAsArray() ;
        //$et = strtotime(sprintf("%04s-%02s-%02s", $e["year"], $e["month"], $e["day"])) ;

        //$d = $meet->getMeetDate() ;
        //$dt = strtotime(sprintf("%04s-%02s-%02s", $d["year"], $d["month"], $d["day"])) ;
 
        //  Date before season start or after season end?

        //if (($dt < $st) || ($dt > $et))
        //{
            //$this->add_error("Date", "Date occurs outside of season.") ;
            //$valid = false ;
        //}

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
        $swimmeet = new SwimMeet() ;

        $swimmeet->setOrgCode($this->get_element_value("Organization")) ;
        $swimmeet->setMeetName($this->get_element_value("Meet Name")) ;
        $swimmeet->setMeetAddress1($this->get_element_value("Meet Address 1")) ;
        $swimmeet->setMeetAddress2($this->get_element_value("Meet Address 2")) ;
        $swimmeet->setMeetState($this->get_element_value("Meet State")) ;
        $swimmeet->setMeetCountry($this->get_element_value("Meet Country")) ;
        $swimmeet->setMeetCode($this->get_element_value("Meet Code")) ;

        $date = $this->get_element_value("Meet Start") ;
        $swimmeet->setMeetStart($date['month'] . $date['day'] . $date['year']) ;

        $date = $this->get_element_value("Meet End") ;
        $swimmeet->setMeetEnd($date['month'] . $date['day'] . $date['year']) ;

        $swimmeet->setPoolAltitude($this->get_element_value("Pool Altitude")) ;
        $swimmeet->setCourseCode($this->get_element_value("Course Code")) ;

        $success = $swimmeet->AddSwimMeet() ;

        //  If successful, store the added age group id in so it can be used later.

        if ($success) 
        {
            $meet->setMeetId($success) ;
            $this->set_action_message("Swim Meet successfully added.") ;
        }
        else
        {
            $this->set_action_message("Swim Meet was not successfully added.") ;
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
 * Construct the Update SwimMeet form
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

        $swimmeet = new SwimMeet() ;
        $swimmeet->LoadSwimMeetById($this->getSwimMeetId()) ;

        $this->set_hidden_element_value('swimmeetid', $swimmeet->getSwimMeetId()) ;

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
        $valid = parent::form_backend_validation(false) ;

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
        $meet = new SwimMeet() ;

        $swimmeet = new SwimMeet() ;

        $swimmeet->setOrgCode($this->get_element_value("Organization")) ;
        $swimmeet->setMeetName($this->get_element_value("Meet Name")) ;
        $swimmeet->setMeetAddress1($this->get_element_value("Meet Address 1")) ;
        $swimmeet->setMeetAddress2($this->get_element_value("Meet Address 2")) ;
        $swimmeet->setMeetState($this->get_element_value("Meet State")) ;
        $swimmeet->setMeetCountry($this->get_element_value("Meet Country")) ;
        $swimmeet->setMeetCode($this->get_element_value("Meet Code")) ;

        $date = $this->get_element_value("Meet Start") ;
        $swimmeet->setMeetStart($date['month'] . $date['day'] . $date['year']) ;

        $date = $this->get_element_value("Meet End") ;
        $swimmeet->setMeetEnd($date['month'] . $date['day'] . $date['year']) ;

        $swimmeet->setPoolAltitude($this->get_element_value("Pool Altitude")) ;
        $swimmeet->setCourseCode($this->get_element_value("Course Code")) ;

        $success = $meet->UpdateSwimMeet() ;

        //  If successful, store the updated meet id in so it can be used later.

        if ($success) 
        {
            $meet->setMeetId($success) ;
            $this->set_action_message("Swim Meet successfully updated.") ;
        }
        else
        {
            $this->set_action_message("Swim Meet was not successfully updated.") ;
        }

        return $success ;
    }
}

/**
 * Construct the Delete SwimMeet form
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
            $this->set_action_message("SwimMeet successfully deleted.") ;
        else
            $this->set_action_message("SwimMeet was not successfully deleted.") ;

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
?>
