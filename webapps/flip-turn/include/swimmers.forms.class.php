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
 * (c) 2011 by Mike Walsh
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip_Turn
 * @subpackage Swimmers
 * @version $Revision$
 * @lastmodified $Author$
 * @lastmodifiedby $Date$
 *
 */

require_once('ft.include.php') ;
require_once('sdif.include.php') ;
require_once('forms.class.php') ;
require_once('swimmers.class.php') ;
require_once('swimteams.class.php') ;

/**
 * Construct the base Swimmer form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnForm
 */
class FlipTurnSwimmerForm extends FlipTurnForm
{
    /**
     * team id property - used to track the swim team record
     */
    var $_swimmerid ;

    /**
     * swim team property - used to store an instance
     */
    var $_swimmer = null ;

    /**
     * Set the swim team id property
     */
    function setSwimmerId($id)
    {
        $this->_swimmerid = $id ;
    }

    /**
     * Get the swim team id property
     */
    function getSwimmerId()
    {
        return $this->_swimmerid ;
    }

    /**
     * Set the swim team property
     */
    function setSwimmer($swimmer)
    {
        $this->_swimmer = $swimmer ;
    }

    /**
     * Get the swim team property
     */
    function getSwimmer()
    {
        return $this->_swimmer ;
    }

    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        $this->add_hidden_element("swimmerid") ;

        //  This is used to remember the action
        //  which originated from the GUIDataList.
 
        $this->add_hidden_element("_action") ;
    }
}

/**
 * Construct the Add Swimmer form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnForm
 */
class SwimmerAddForm extends FlipTurnSwimmerForm
{
    /**
     * Get the array of gender key and value pairs
     *
     * @return mixed - array of gender key value pairs
     */
    function GenderSelections()
    {
        //  Gender options and labels are set based on
        //  the plugin options

        $g = array(ucfirst(FT_MALE) => strtoupper(substr(FT_MALE, 0, 1))
            ,ucfirst(FT_FEMALE) => strtoupper(substr(FT_FEMALE, 0, 1))
        ) ;

         return $g ;
    }

    /**
     * Get the array of opponent swim club key and value pairs
     *
     * @return mixed - array of opponent swim club key value pairs
     */
    function SwimTeamSelections()
    {
        //  Swim Club options and labels, seed "None" as an
        //  option as some meet types don't have an opponent.

        $s = array(ucfirst(FT_NONE) => FT_NULL_ID) ;

        $swimteam = new SwimTeam() ;
        $swimteamIds = $swimteam->getAllSwimTeamIds() ;

        //  Make sure we have swim clubs to build a list of!
        if ($swimteamIds != null)
        {
            foreach ($swimteamIds as $swimteamId)
            {
                $swimteam->LoadSwimTeamById($swimteamId['swimteamid']) ;

                $team = $swimteam->getTeamName() ;
                $s[$team] = $swimteam->getSwimTeamId() ;
            }
        }

        return $s ;
    }

    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        $this->add_hidden_element("swimmerid") ;

        //  This is used to remember the action
        //  which originated from the GUIDataList.
 
        $this->add_hidden_element("_action") ;

		//  First Name field

        $firstname = new FEText("First Name", true, "200px");
        $this->add_element($firstname) ;

		//  Middle Name field

        $middlename = new FEText("Middle Name", false, "200px");
        $this->add_element($middlename) ;

		//  Last Name field

        $lastname = new FEText("Last Name", true, "200px");
        $this->add_element($lastname) ;

		//  Birth Date field

        $birthdate = new FEDate("Birth Date", true, null, null,
                "Fdy", date("Y") - 25, date("Y") + 2) ;
        $this->add_element($birthdate) ;

		//  Gender field

        $gender = new FEListBox("Gender", true, "100px");
        $gender->set_list_data($this->GenderSelections()) ;
        $this->add_element($gender) ;

		//  USS field

        $uss = new FEText("USS", true, "200px");
        $this->add_element($uss) ;

		//  Calculated USS field

        $ussnew = new FEText("USS New", false, "200px");
        $ussnew->set_disabled(true) ;
        //$ussnew->set_readonly(true) ;
        $this->add_element($ussnew) ;

		//  Swim Team field

        $swimteam = new FEListBox("Swim Team", true, "300px");
        $swimteam->set_list_data($this->SwimTeamSelections()) ;
        $this->add_element($swimteam) ;
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

        $this->set_element_value("Birth Date", array("year" => date("Y"),
           "month" => date("m"), "day" => date("d"))) ;
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

        $table->add_row($this->element_label("First Name"),
            $this->element_form("First Name")) ;

        $table->add_row($this->element_label("Middle Name"),
            $this->element_form("Middle Name")) ;

        $table->add_row($this->element_label("Last Name"),
            $this->element_form("Last Name")) ;

        $table->add_row($this->element_label("Birth Date"),
            $this->element_form("Birth Date")) ;

        $table->add_row($this->element_label("Gender"),
            $this->element_form("Gender")) ;

        $table->add_row($this->element_label("USS"),
            $this->element_form("USS")) ;

        $table->add_row($this->element_label("USS New"),
            $this->element_form("USS New")) ;

        $table->add_row($this->element_label("Swim Team"),
            $this->element_form("Swim Team")) ;

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

        $this->setSwimmer(new Swimmer()) ;
        $swimmer = $this->getSwimmer() ;

        $first = $this->get_element_value('First Name') ;
        $middle = $this->get_element_value('Middle Name') ;
        $last = $this->get_element_value('Last Name') ;

        $swimmer->setSwimmerFirstName($first) ;
        $swimmer->setSwimmerMiddleName($middle) ;
        $swimmer->setSwimmerLastName($last) ;

        $swimmer->setSwimmerName($last . ',' . $first . ',' . $middle) ;

        $date = $this->get_element_value('Birth Date') ;
        $swimmer->setBirthDate($date['year'] . '-' . $date['month'] . '-' . $date['day'], true) ;
        $swimmer->setGender($this->get_element_value('Gender')) ;

        $swimmer->setUSS($this->get_element_value('USS')) ;
        $swimmer->setUSSNew() ;
        $this->set_element_value('USS New', $swimmer->getUSSNew()) ;
        $swimmer->setSwimTeamId($this->get_element_value('Swim Team')) ;

        if ($swimmer->SwimmerExistsByUSSNew())
        {
            $valid = false ;
            $this->add_error('USS New', 'A swimmer with this name and birthdate already exists in the database') ;
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
        //  should be stored in the Swimmer class instance.

        $swimmer = $this->getSwimmer() ;

        $success = $swimmer->AddSwimmer() ;

        //  If successful, store the added age group id in so it can be used later.

        if ($success) 
        {
            $swimmer->setSwimmerId($success) ;
            $this->set_action_message(html_div('ft-note-msg',
                'Swimmer successfully added.')) ;
        }
        else
        {
            $this->set_action_message(html_div('ft-note-msg',
                'Swimmer was not successfully added.')) ;
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
 * Construct the Update Swimmer form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnSwimmerAddForm
 */
class SwimmerUpdateForm extends SwimmerAddForm
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
        $this->set_hidden_element_value('swimmerid', $this->getSwimmerId()) ;

        $swimmer = new Swimmer() ;
        $swimmer->LoadSwimmerById($this->getSwimmerId()) ;

        $this->set_element_value('First Name', $swimmer->getSwimmerFirstName()) ;
        $this->set_element_value('Middle Name', $swimmer->getSwimmerMiddleName()) ;
        $this->set_element_value('Last Name', $swimmer->getSwimmerLastName()) ;
        $this->set_element_value('Gender', $swimmer->getGender()) ;
        $this->set_element_value('USS', $swimmer->getUSS()) ;
        $this->set_element_value('USS New', $swimmer->getUSSNew()) ;

        $date = $swimmer->getBirthDate(false) ;
        $this->set_element_value('Birth Date', array('year' => substr($date, 4, 4),
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


        //  Need to make sure that the update isn't changing the
        //  swim team to match something which already exists in
        //  the database.

        $this->setSwimmer(new Swimmer()) ;
        $swimmer = $this->getSwimmer() ;

        $swimmer->LoadSwimmerById($this->get_hidden_element_value('swimmerid')) ;
        $oldswimmerussnew = $swimmer->getUSSNew() ;

        $first = $this->get_element_value('First Name') ;
        $middle = $this->get_element_value('Middle Name') ;
        $last = $this->get_element_value('Last Name') ;

        $swimmer->setSwimmerFirstName($first) ;
        $swimmer->setSwimmerMiddleName($middle) ;
        $swimmer->setSwimmerLastName($last) ;

        $swimmer->setSwimmerName($last . ',' . $first . ',' . $middle) ;

        $date = $this->get_element_value('Birth Date') ;
        $swimmer->setBirthDate($date['year'] . '-' . $date['month'] . '-' . $date['day'], true) ;
        $swimmer->setGender($this->get_element_value('Gender')) ;

        $swimmer->setUSS($this->get_element_value('USS')) ;
        $swimmer->setUSSNew() ;
        $this->set_element_value('USS New', $swimmer->getUSSNew()) ;
        $swimmer->setSwimTeamId($this->get_element_value('Swim Team')) ;

        if ($swimmer->SwimmerExistsByUSSNew() && ($oldswimmerussnew != $swimmer->getUSSNew()))
        {
            $valid = false ;
            $this->add_error('USS New', 'A swimmer with this name and birthdate already exists in the database') ;
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
        //  should be stored in the Swimmer class instance.

        $swimmer = $this->getSwimmer() ;

        $success = $swimmer->UpdateSwimmer() ;

        //  If successful, store the updated team id in so it can be used later.

        if ($success) 
        {
            $swimmer->setSwimmerId($success) ;
            $this->set_action_message(html_div('ft-note-msg',
                'Swimmer successfully updated.')) ;
        }
        else
        {
            $this->set_action_message(html_div('ft-note-msg',
                'Swimmer was not successfully updated.')) ;
        }

        return $success ;
    }
}

/**
 * Construct the Delete Swimmer form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnSwimmerUpdateForm
 */
class SwimmerDeleteForm extends SwimmerUpdateForm
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
        $team = new SwimmerSwimmer() ;
        $team->setId($this->get_hidden_element_value("teamid")) ;
        $success = $team->deleteSwimmer() ;

        if ($success) 
            $this->set_action_message(html_div('ft-note-msg',
                'Swimmer successfully deleted.')) ;
        else
            $this->set_action_message(html_div('ft-note-msg',
                'Swimmer was not successfully deleted.')) ;

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
 * Construct the Swimmers Purge form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnSwimmerForm
 */
class SwimmersPurgeForm extends FlipTurnPurgeForm
{
    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        $this->setPurgeLabel('Purge Swimmers') ;
        $this->setPurgeMessage('Purging the Swimmers will delete all
            swimmers currently stored in the database.  This action
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

        $swimmer = new Swimmer() ;
        $swimmer->PurgeSwimmers() ;

        $this->set_action_message(html_div(sprintf('ft-%s-msg',
            $swimmer->getAffectedRows() == 0 ? 'warning' : 'note'),
            sprintf('%d record%s purged from Swimmers database.',
            $swimmer->getAffectedRows(),
            $swimmer->getAffectedRows() == 1 ? '' : 's'))) ;

        unset($swimmer) ;

        return $success ;
    }
}
?>
