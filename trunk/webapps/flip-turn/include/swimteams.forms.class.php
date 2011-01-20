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
 * @subpackage SwimTeams
 * @version $Revision$
 * @lastmodified $Author$
 * @lastmodifiedby $Date$
 *
 */

require_once("ft.include.php") ;
require_once("sdif.include.php") ;
require_once("forms.class.php") ;
require_once("swimteams.class.php") ;

/**
 * Construct the base SwimTeam form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnForm
 */
class FlipTurnSwimTeamForm extends FlipTurnForm
{
    /**
     * team id property - used to track the swim team record
     */
    var $_swimteamid ;

    /**
     * swim team property - used to store an instance
     */
    var $_swimteam = null ;

    /**
     * Set the swim team id property
     */
    function setSwimTeamId($id)
    {
        $this->_swimteamid = $id ;
    }

    /**
     * Get the swim team id property
     */
    function getSwimTeamId()
    {
        return $this->_swimteamid ;
    }

    /**
     * Set the swim team property
     */
    function setSwimTeam($swimteam)
    {
        $this->_swimteam = $swimteam ;
    }

    /**
     * Get the swim team property
     */
    function getSwimTeam()
    {
        return $this->_swimteam ;
    }

    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        $this->add_hidden_element("swimteamid") ;

        //  This is used to remember the action
        //  which originated from the GUIDataList.
 
        $this->add_hidden_element("_action") ;
    }
}

/**
 * Construct the Add SwimTeam form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnForm
 */
class SwimTeamAddForm extends FlipTurnSwimTeamForm
{
    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        $this->add_hidden_element("swimteamid") ;

        //  This is used to remember the action
        //  which originated from the GUIDataList.
 
        $this->add_hidden_element("_action") ;

		//  Org Code field

        $orgcode = new FEListBox("Organization", true, "150px");
        $orgcode->set_list_data(SDIFCodeTableMappings::GetOrgCodes()) ;
        $this->add_element($orgcode) ;

		//  Team Code field

        $teamcode = new FEText("Team Code", true, "100px");
        $this->add_element($teamcode) ;

		//  Team Name field

        $teamname = new FEText("Team Name", true, "300px");
        $this->add_element($teamname) ;

		//  Team Name Abbreviation field

        $teamnameabrv = new FEText("Team Name Abbreviation", true, "200px");
        $this->add_element($teamnameabrv) ;

		//  Team Address 1 field

        $teamaddress1 = new FEText("Team Address 1", false, "300px");
        $this->add_element($teamaddress1) ;

		//  Team Address 2 field

        $teamaddress2 = new FEText("Team Address 2", false, "300px");
        $this->add_element($teamaddress2) ;

        //  Team City

        $teamcity = new FEText("Team City", false, "300px");
        $this->add_element($teamcity) ;

        //  Team State

        $teamstate = new FEUnitedStates("Team State", FT_US_ONLY, "150px");
        $this->add_element($teamstate) ;

		//  Team Postal Code field

        $teampostalcode = new FEText("Team Postal Code", false, "200px");
        $this->add_element($teampostalcode) ;

        //  Team Country

        $teamcountry = new FEListBox("Team Country", true, "250px");
        $teamcountry->set_list_data(SDIFCodeTableMappings::GetCountryCodes()) ;
        $teamcountry->set_readonly(FT_US_ONLY) ;
        $this->add_element($teamcountry) ;

		//  Team Code field

        $regioncode = new FEListBox("Region", true, "150px");
        $regioncode->set_list_data(SDIFCodeTableMappings::GetRegionCodes()) ;
        $this->add_element($regioncode) ;

		//  Team Code 5th Character

        $teamcode5 = new FENumber("Team Code 5th Character", false, "50px") ;
        $this->add_element($teamcode5) ;
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

        //  If the config is set to US only, initialize the country

        if (FT_US_ONLY)
            $this->set_element_value("Team Country",
                FT_SDIF_COUNTRY_CODE_UNITED_STATES_OF_AMERICA_VALUE) ;
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

        $table->add_row($this->element_label("Team Code"),
            $this->element_form("Team Code")) ;

        $table->add_row($this->element_label("Team Name"),
            $this->element_form("Team Name")) ;

        $table->add_row($this->element_label("Team Name Abbreviation"),
            $this->element_form("Team Name Abbreviation")) ;

        $table->add_row($this->element_label("Team Address 1"),
            $this->element_form("Team Address 1")) ;

        $table->add_row($this->element_label("Team Address 2"),
            $this->element_form("Team Address 2")) ;

        $table->add_row($this->element_label("Team City"),
            $this->element_form("Team City")) ;

        $table->add_row($this->element_label("Team State"),
            $this->element_form("Team State")) ;

        $table->add_row($this->element_label("Team Postal Code"),
            $this->element_form("Team Postal Code")) ;

        $table->add_row($this->element_label("Team Country"),
            $this->element_form("Team Country")) ;

        $table->add_row($this->element_label("Region"),
            $this->element_form("Region")) ;

        $table->add_row($this->element_label("Team Code 5th Character"),
            $this->element_form("Team Code 5th Character")) ;

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

        $this->setSwimTeam(new SwimTeam()) ;
        $swimteam = $this->getSwimTeam() ;

        $swimteam->setOrgCode($this->get_element_value('Organization')) ;
        $swimteam->setTeamCode($this->get_element_value('Team Code')) ;
        $swimteam->setTeamName($this->get_element_value('Team Name')) ;
        $swimteam->setTeamNameAbrv($this->get_element_value('Team Name Abbreviation')) ;
        $swimteam->setTeamAddress1($this->get_element_value('Team Address 1')) ;
        $swimteam->setTeamAddress2($this->get_element_value('Team Address 2')) ;
        $swimteam->setTeamCity($this->get_element_value('Team City')) ;
        $swimteam->setTeamState($this->get_element_value('Team State')) ;
        $swimteam->setTeamPostalCode($this->get_element_value('Team Postal Code')) ;
        $swimteam->setTeamCountryCode($this->get_element_value('Team Country')) ;
        $swimteam->setRegionCode($this->get_element_value('Region')) ;
        $swimteam->setTeamCode5($this->get_element_value('Team Code 5th Character')) ;

        if ($swimteam->SwimTeamExistsByName())
        {
            $valid = false ;
            $this->add_error('Team Name', 'A team with this name already exists in the database') ;
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
        //  After passing validation, all of the team data
        //  should be stored in the Swim Team class instance.

        $swimteam = $this->getSwimTeam() ;

        $success = $swimteam->AddSwimTeam() ;

        //  If successful, store the added age group id in so it can be used later.

        if ($success) 
        {
            $swimteam->setSwimTeamId($success) ;
            $this->set_action_message(html_div('ft-note-msg',
                'Swim Team successfully added.')) ;
        }
        else
        {
            $this->set_action_message(html_div('ft-note-msg',
                'Swim Team was not successfully added.')) ;
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
 * Construct the Update SwimTeam form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnSwimTeamAddForm
 */
class SwimTeamUpdateForm extends SwimTeamAddForm
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
        $this->set_hidden_element_value('swimteamid', $this->getSwimTeamId()) ;

        $swimteam = new SwimTeam() ;
        $swimteam->LoadSwimTeamById($this->getSwimTeamId()) ;

        $this->set_element_value('Organization', $swimteam->getOrgCode()) ;
        $this->set_element_value('Team Code', $swimteam->getTeamCode()) ;
        $this->set_element_value('Team Name', $swimteam->getTeamName()) ;
        $this->set_element_value('Team Name Abbreviation', $swimteam->getTeamNameAbrv()) ;
        $this->set_element_value('Team Address 1', $swimteam->getTeamAddress1()) ;
        $this->set_element_value('Team Address 2', $swimteam->getTeamAddress2()) ;
        $this->set_element_value('Team City', $swimteam->getTeamCity()) ;
        $this->set_element_value('Team State', $swimteam->getTeamState()) ;
        $this->set_element_value('Team Postal Code', $swimteam->getTeamPostalCode()) ;
        $this->set_element_value('Team Country', $swimteam->getTeamCountryCode()) ;
        $this->set_element_value('Region', $swimteam->getRegionCode()) ;
        $this->set_element_value('Team Code 5th Character', $swimteam->getTeamCode5()) ;
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

        $this->setSwimTeam(new SwimTeam()) ;
        $swimteam = $this->getSwimTeam() ;

        //  Need to make sure that the update isn't changing the
        //  swim team to match something which already exists in
        //  the database.

        $swimteam->LoadSwimTeamById($this->get_hidden_element_value('swimteamid')) ;
        $oldteamname = $swimteam->getTeamName() ;

        $swimteam->setOrgCode($this->get_element_value('Organization')) ;
        $swimteam->setTeamCode($this->get_element_value('Team Code')) ;
        $swimteam->setTeamName($this->get_element_value('Team Name')) ;
        $swimteam->setTeamNameAbrv($this->get_element_value('Team Name Abbreviation')) ;
        $swimteam->setTeamAddress1($this->get_element_value('Team Address 1')) ;
        $swimteam->setTeamAddress2($this->get_element_value('Team Address 2')) ;
        $swimteam->setTeamCity($this->get_element_value('Team City')) ;
        $swimteam->setTeamState($this->get_element_value('Team State')) ;
        $swimteam->setTeamPostalCode($this->get_element_value('Team Postal Code')) ;
        $swimteam->setTeamCountryCode($this->get_element_value('Team Country')) ;
        $swimteam->setRegionCode($this->get_element_value('Region')) ;
        $swimteam->setTeamCode5($this->get_element_value('Team Code 5th Character')) ;

        if ($swimteam->SwimTeamExistsByName() && ($oldteamname != $swimteam->getTeamName()))
        {
            $valid = false ;
            $this->add_error('Team Name', 'A team with this name already exists in the database') ;
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
        //  After passing validation, all of the team data
        //  should be stored in the Swim Team class instance.

        $swimteam = $this->getSwimTeam() ;
        //var_dump($swimteam) ;

        $success = $swimteam->UpdateSwimTeam() ;

        //  If successful, store the updated team id in so it can be used later.

        if ($success) 
        {
            $swimteam->setSwimTeamId($success) ;
            $this->set_action_message(html_div('ft-note-msg',
                'Swim Team successfully updated.')) ;
        }
        else
        {
            $this->set_action_message(html_div('ft-note-msg',
                'Swim Team was not successfully updated.')) ;
        }

        return $success ;
    }
}

/**
 * Construct the Delete SwimTeam form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnSwimTeamUpdateForm
 */
class SwimTeamDeleteForm extends SwimTeamUpdateForm
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
        $team = new SwimTeamSwimTeam() ;
        $team->setId($this->get_hidden_element_value("teamid")) ;
        $success = $team->deleteSwimTeam() ;

        if ($success) 
            $this->set_action_message(html_div('ft-note-msg',
                'SwimTeam successfully deleted.')) ;
        else
            $this->set_action_message(html_div('ft-note-msg',
                'SwimTeam was not successfully deleted.')) ;

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
 * Construct the Swim Teams Purge form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnSwimTeamForm
 */
class SwimTeamsPurgeForm extends FlipTurnPurgeForm
{
    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        $this->setPurgeLabel('Purge Swim Teams') ;
        $this->setPurgeMessage('Purging the Swim Teams will delete all
            swim teams currently stored in the database.  This action
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

        $swimteam = new SwimTeam() ;
        $swimteam->PurgeSwimTeams() ;

        $this->set_action_message(html_div(sprintf('ft-%s-msg',
            $swimteam->getAffectedRows() == 0 ? 'warning' : 'note'),
            sprintf('%d record%s purged from Swim Teams database.',
            $swimteam->getAffectedRows(),
            $swimteam->getAffectedRows() == 1 ? '' : 's'))) ;

        unset($swimteam) ;

        return $success ;
    }
}
?>
