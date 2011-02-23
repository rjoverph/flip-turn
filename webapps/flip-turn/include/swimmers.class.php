<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 *
 * $Id$
 *
 * Swimmer Classes
 *
 * This information is based on the United States Swimming Interchange
 * format version 3 document revision F.  This document can be found on
 * the US Swimming web site at:  http://www.usaswimming.org/
 *
 * (c) 2010 by Mike Walsh
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage SDIF
 * @version $Revision$
 * @lastmodified $Date$
 * @lastmodifiedby $Author$
 *
 */

include_once('db.class.php') ;
include_once('sdif.include.php') ;
include_once('sdif.class.php') ;
include_once('widgets.class.php') ;

include_once(PHPHTMLLIB_ABSPATH . "/widgets/data_list/includes.inc") ;


/**
 * SDIF record base class
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 */
class Swimmer extends SDIFD1Record
{
    /**
     * Swimmer Id
     */
    var $_swimmerid ;

    /**
     * Swim Team Id
     */
    var $_swimteamid ;

    /**
     * Swimmer Last Name
     */
    var $_lastname ;

    /**
     * Swimmer First Name
     */
    var $_firstname ;

    /**
     * Swimmer Middle Name
     */
    var $_middlename ;

    /**
     * Set the swimmer id
     *
     * @param int id of the swimmer
     */
    function setSwimmerId($id)
    {
        $this->_swimmerid = $id ;
    }

    /**
     * Get the swimmer id
     *
     * @return int id of the swimmer
     */
    function getSwimmerId()
    {
        return $this->_swimmerid ;
    }

    /**
     * Set the swim team id
     *
     * @param int id of the team
     */
    function setSwimTeamId($id)
    {
        $this->_swimteamid = $id ;
    }

    /**
     * Get the swim swimmer id
     *
     * @return int id of the swimmer
     */
    function getSwimTeamId()
    {
        return $this->_swimteamid ;
    }

    /**
     * Set the swimmer last name
     *
     * @param string swimmer last name
     */
    function setSwimmerLastName($txt)
    {
        $this->_lastname = $txt ;
    }

    /**
     * Get the swimmer last name
     *
     * @return string swimmer last name
     */
    function getSwimmerLastName()
    {
        return $this->_lastname ;
    }

    /**
     * Set the swimmer first name
     *
     * @param string swimmer first name
     */
    function setSwimmerFirstName($txt)
    {
        $this->_firstname = $txt ;
    }

    /**
     * Get the swimmer first name
     *
     * @return string swimmer first name
     */
    function getSwimmerFirstName()
    {
        return $this->_firstname ;
    }

    /**
     * Set the swimmer middle name
     *
     * @param string swimmer middle name
     */
    function setSwimmerMiddleName($txt)
    {
        $this->_middlename = $txt ;
    }

    /**
     * Get the swimmer middle name
     *
     * @return string swimmer middle name
     */
    function getSwimmerMiddleName()
    {
        return $this->_middlename ;
    }

    /**
     * Check if a id already exists in the database
     * and return a boolean accordingly.
     *
     * @param int optional id
     * @return boolean existance of swimmer by id
     */
    function SwimmerExistsById($swimmerid = null)
    {
        if (is_null($swimmerid)) $swimmerid = $this->getSwimmerId() ;

	    //  Is id already in the database?

        $query = sprintf("SELECT swimmerid FROM %s WHERE swimmerid = \"%s\"",
            FT_SWIMMERS_TABLE, $swimmerid) ;

        $this->setQuery($query) ;
        $this->runSelectQuery(false) ;

	    //  Make sure id doesn't exist

        return (bool)($this->getQueryCount() > 0) ;
    }

    /**
     * Check if a swimmer already exists in the database
     * by comparing names and return a boolean accordingly.
     *
     * @param string swimmer name
     * @return boolean existance of swimmer by name
     */
    function SwimmerExistsByName($first = null, $middle = null, $last = null)
    {
        if (is_null($first)) $first = $this->getSwimmerFirstName() ;
        if (is_null($middle)) $first = $this->getSwimmerMiddleName() ;
        if (is_null($last)) $last = $this->getSwimmerLastName() ;

	    //  Is name already in the database?

        $query = sprintf("SELECT swimmerid FROM %s WHERE lastname=\"%s\" AND
            firstname=\"%s\" AND middlename=\"%s\"", FT_SWIMMERS_TABLE, $last,
            $middle, $first) ;

        $this->setQuery($query) ;
        $this->runSelectQuery(false) ;

	    //  Make sure name doesn't exist

        return (bool)($this->getQueryCount() > 0) ;
    }

    /**
     * Get Swimmer Id by Name
     *
     * @param string swimmer name
     * @return int swim swimmer id
     */
    function GetSwimmerIdByName($swimmername = null)
    {
        if (is_null($swimmername)) $swimmername = $this->getTeamName() ;

	    //  Is name already in the database?

        $query = sprintf("SELECT swimmerid FROM %s WHERE swimmer_name = \"%s\"",
            FT_SWIMMERS_TABLE, $swimmername) ;

        $this->setQuery($query) ;
        $this->runSelectQuery() ;

	    //  Make sure name doesn't exist

        return ($this->getQueryCount() > 0) ?
            $this->getQueryResult() : array('swimmerid' => null) ;
    }

    /**
     * Check if a swimmer already exists in the database
     * by comparing names and return a boolean accordingly.
     *
     * @param string uss new
     * @return boolean existance of swimmer
     */
    function SwimmerExistsByUSSNew($uss = null)
    {
        if (is_null($uss)) $uss = $this->getUSSNew() ;

	    //  Is swimmer already in the database?

        $query = sprintf("SELECT swimmerid FROM %s WHERE
            uss_new = \"%s\"", FT_SWIMMERS_TABLE, $uss) ;

        $this->setQuery($query) ;
        $this->runSelectQuery(false) ;

	    //  determine existance status

        return (bool)($this->getQueryCount() > 0) ;
    }

    /**
     * Check if a swimmer already exists in the database
     * by comparing names and return a boolean accordingly.
     *
     * @param string uss new
     * @param string int swim team id
     * @return boolean existance of swimmer
     */
    function SwimmerExistsByUSSNewAndSwimTeamId($uss = null, $swimteamid = null)
    {
        if (is_null($uss)) $uss = $this->getUSSNew() ;
        if (is_null($swimteamid)) $swimteamid = $this->getSwimTeamId() ;

	    //  Is swimmer already in the database?

        $query = sprintf("SELECT swimmerid FROM %s WHERE uss_new = \"%s\"
            AND swimteamid=\"%s\"", FT_SWIMMERS_TABLE, $uss, $swimteamid) ;

        $this->setQuery($query) ;
        $this->runSelectQuery(false) ;

	    //  determine existance status

        return (bool)($this->getQueryCount() > 0) ;
    }

    /**
     * Get Swimmer Id by USS and team id
     *
     * @param string uss new
     * @param string int swim team id
     * @return int swim swimmer id
     */
    function GetSwimmerIdByUSSNewAndSwimTeamId($uss = null, $swimteamid = null)
    {
        if (is_null($uss)) $uss = $this->getUSSNew() ;
        if (is_null($swimteamid)) $swimteamid = $this->getSwimTeamId() ;

	    //  Is swimmer already in the database?

        $query = sprintf("SELECT swimmerid FROM %s WHERE uss_new = \"%s\"
            AND swimteamid=\"%s\"", FT_SWIMMERS_TABLE, $uss, $swimteamid) ;

        $this->setQuery($query) ;
        $this->runSelectQuery() ;

	    //  Make sure name doesn't exist

        return ($this->getQueryCount() > 0) ?
            $this->getQueryResult() : array('swimmerid' => null) ;
    }

    /**
     *
     * Load swimmer record by Id
     *
     * @param int optional swimmer id
     */
    function LoadSwimmerById($swimmerid = null)
    {
        if (is_null($swimmerid)) $swimmerid = $this->getSwimmerId() ;

        //  Dud?
        if (is_null($swimmerid)) return false ;

        $this->setSwimmerId($swimmerid) ;

        //  Make sure it is a legal swimmer id
        if ($this->SwimmerExistsById($swimmerid))
        {
            $query = sprintf("SELECT * FROM %s WHERE swimmerid=\"%s\"",
                FT_SWIMMERS_TABLE, $swimmerid) ;

            $this->setQuery($query) ;
            $this->runSelectQuery() ;

            $result = $this->getQueryResult() ;

            $this->setSwimmerId($result['swimmerid']) ;
            $this->setSwimTeamId($result['swimteamid']) ;
            $this->setSwimmerLastName($result['lastname']) ;
            $this->setSwimmerFirstName($result['firstname']) ;
            $this->setSwimmerMiddleName($result['middlename']) ;
            $this->setBirthDate($result['birth_date'], true) ;
            $this->setUSS($result['uss']) ;
            $this->setUSSNew($result['uss_new']) ;
            $this->setGender($result['gender']) ;
            $this->setTimestamp($result['timestamp']) ;
        }

        $idExists = (bool)($this->getQueryCount() > 0) ;

	    return $idExists ;
    }

    /**
     * Add Swimmer to database
     *
     * @return boolean successful query
     */
    function AddSwimmer()
    {
        $this->setQuery(sprintf("INSERT INTO %s SET
            swimteamid=\"%s\",
            lastname=\"%s\",
            firstname=\"%s\",
            middlename=\"%s\",
            birth_date=\"%s\",
            uss=\"%s\",
            uss_new=\"%s\",
            gender=\"%s\"",
            FT_SWIMMERS_TABLE,
            $this->getSwimTeamId(),
            $this->getSwimmerLastName(),
            $this->getSwimmerFirstName(),
            $this->getSwimmerMiddleName(),
            $this->getBirthDate(true),
            $this->getUSS(),
            $this->getUSSNew(),
            $this->getGender())) ;

        $success = $this->runInsertQuery() ;

        if ($success)
            $this->setSwimmerId($this->getInsertId()) ;
        else
            $this->setSwimmerId(null) ;

        return $success ;
    }

    /**
     * Update Swimmer in database
     *
     * @return boolean successful query
     */
    function UpdateSwimmer()
    {
        $this->setQuery(sprintf("UPDATE %s SET
            swimteamid=\"%s\",
            lastname=\"%s\",
            firstname=\"%s\",
            middlename=\"%s\",
            birth_date=\"%s\",
            uss=\"%s\",
            uss_new=\"%s\",
            gender=\"%s\"
            WHERE swimmerid=\"%s\"",
            FT_SWIMMERS_TABLE,
            $this->getSwimTeamId(),
            $this->getSwimmerLastName(),
            $this->getSwimmerFirstName(),
            $this->getSwimmerMiddleName(),
            $this->getBirthDate(),
            $this->getUSS(),
            $this->getUSSNew(),
            $this->getGender(),
            $this->getSwimmerId())) ;

        $success = $this->runUpdateQuery() ;

        return $success ;
    }

    /**
     * Purge swim swimmers records from the database
     *
     * @return int number of records purged
     */
    function PurgeSwimmers()
    {
        $this->setQuery(sprintf("DELETE FROM %s", FT_SWIMMERS_TABLE)) ;
        $this->runDeleteQuery() ;

        return $this->getAffectedRows() ;
    }
}

/**
 * SwimmersDataList class
 *
 * Child GUIDataList class to present the Swimmers in a
 * GUIDataList widget to allow the user to take some action
 * against it.
 *
 *
 * @author Mike Walsh - mike_walsh@mindspring.com
 * @access public
 * @see DefaultGUIDataList
 *
 */
class SwimmersDataList extends DefaultGUIDataList
{
    /**
     * default rows per page property
     * overload the # of rows to display to 15 from 10
     *
     */
    var $_default_rows_per_page = 15 ;

    /**
     * This method is used to setup the options
     * for the DataList object's display. 
     * Which columns to show, their respective 
     * source column name, width, etc. etc.
     *
     * The constructor automatically calls 
     * this function.
     *
     */
    function user_setup()
    {
        //  add the columns in the display that you want to view.
        //  The API is:  Title, width, DB column name, field SORTABLE?,
        //  field  SEARCHABLE?, align

        $this->add_header_item("Last Name",
            "100", "lastname", SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("First Name",
            "100", "firstname", SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("Middle Name",
            "100", "middlename", SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("USS",
            "100", "uss_new", SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("Team Name",
            "100", "swimteamid", SORTABLE, SEARCHABLE, "left") ;
        
        $this->_db_setup() ;
        $this->set_show_empty_datalist_actionbar(true) ;

        //  This GDL is a form so actions can be performed on the data.

        //turn on the 'collapsable' search block.
        //The word 'Search' in the output will be clickable,
        //and hide/show the search box.
        $this->_collapsable_search = true ;

        //lets add an action column of checkboxes,
        //and allow us to save the checked items between pages.
        $this->add_action_column('radio', 'FIRST', 'swimmerid') ;

        //we have to be in POST mode, or we could run out
        //of space in the http request with the saved
        //checkbox items
        $this->set_form_method('POST') ;

        //set the flag to save the checked items
        //between pages.
        $this->save_checked_items(true) ;
    }

    /**
     * Define the action bar - actions which can be performed on
     * the data in the GDL.
     *
     * @return container
     */
    function actionbar_cell()
    {
        $c = container() ;
        $t = html_table("") ;

        //  Add the buttons ...

        $t->add_row(
            $this->action_button('Add', 'swimmer_add.php'),
            _HTML_SPACE,
            $this->action_button('Details', 'swimmer_details.php'),
            _HTML_SPACE,
            $this->action_button('Results', 'swimmer_results.php'),
            _HTML_SPACE,
            $this->action_button('Update', 'swimmer_update.php'),
            _HTML_SPACE,
            $this->action_button('Purge', 'swimmers_purge.php')) ;

        $c->add($t) ;

        return $c ;
    }

    /**
     * Action Bar - build a set of Action Bar buttons
     *
     * @return container - container holding action bar content
     */
    function empty_datalist_actionbar_cell()
    {
        $c = container() ;
        $t = html_table("") ;

        //  Add the buttons ...

        $t->add_row(
            $this->action_button('Add', "swimmer_add.php")) ;

        $c->add($t) ;

        return $c ;
    }

    /**
     * Build this method so we can override it in the child class
     * for the advanced search capability.
     * 
     * @return VOID
     */
    function _db_setup()
    {
        $columns = "swimmerid, lastname, firstname, middlename, uss_new, swimteamid" ;
        $tables = FT_SWIMMERS_TABLE ;
        $where_clause = "";
        $this->_datasource->setup_db_options($columns, $tables, $where_clause) ;
    }

    /**
     * This function is called automatically by
     * the DataList constructor.  It must be
     * extended by the child class to actually
     * set the DataListSource object.
     *
     * 
     */
    function get_data_source()
    {
        //  Build the ADO DB object and connect to the database.
        $db = &ADONewConnection(FT_DB_DSN) ;

        //  Create the DataListSource object and pass in the ADO DB object
        $source = new ADODBSQLDataListSource($db) ;

        //  Set the DataListSource for this DataList
        //  Every DataList needs a Source for it's data.
        $this->set_data_source($source) ;

        //  set the prefix for all the internal query string 
        //  variables.  You really only need to change this
        //  if you have more then 1 DataList object per page.
        $this->set_global_prefix(FT_DB_PREFIX) ;
    }

    /**
     * This is the basic function for letting us
     * do a mapping between the column name in
     * the header, to the value found in the DataListSource.
     *
     * NOTE: this function is can be overridden
     *       so that you can return whatever you want for
     *       any given column.  
     *
     * @param array - $row_data - the entire data for the row
     * @param string - $col_name - the name of the column header
     *                             for this row to render.
     * @return  mixed - either a HTMLTag object, or raw text.
     */
    function build_column_item($row_data, $col_name)
    {
        include_once('swimteams.class.php') ;
        $swimteam = new SwimTeam() ;

        switch ($col_name)
        {
            case "Timestamp":
                $obj = date("m/d/Y h:i A", strtotime($row_data["timestamp"])) ;
                break;
            case "Team Name":
                $swimteam->LoadSwimTeamById($row_data['swimteamid']) ;
                $obj = $swimteam->getTeamName() ;
                break ;
            default:
                $obj = DefaultGUIDataList::build_column_item($row_data, $col_name) ;
                break ;
        }

        return $obj ;
    }    
}

/**
 * Class definition of a swimmer info table
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see SwimmerInfoTable
 */
class SwimmerInfoTable extends FlipTurnInfoTable
{
    /**
     * Property to hold the swimmer id
     */
    var $_swimmerid ;

    /**
     * Set Swimmer Id
     *
     * @param int - $id - Id of the swim swimmer
     */
    function setSwimmerId($id)
    {
        $this->_swimmerid = $id ;
    }

    /**
     * Get Swimmer Id
     *
     * @return int - Id of the swimmer
     */
    function getSwimmerId()
    {
        return $this->_swimmerid ;
    }

    /**
     * Construct a summary of the active season.
     *
     */
    function BuildInfoTable($swimmerid = null)
    {
        include_once('swimteams.class.php') ;

        //  Alternate the row colors
        $this->set_alt_color_flag(true) ;

        $swimmer = new Swimmer() ;

        if (is_null($swimmerid)) $swimmerid = $this->getSwimmerId() ;

        if (!is_null($swimmerid) || $swimmer->SwimmerExistsById($swimmerid))
        {
            $swimmer->LoadSwimmerById($swimmerid) ;
    
            $swimteam = new SwimTeam() ;
            $swimteam->LoadSwimTeamById($swimmer->getSwimTeamId()) ;
            $this->add_row(html_b("Team Name"), $swimteam->getTeamName()) ;
            $this->add_row(html_b("Last Name"), $swimmer->getSwimmerLastName()) ;
            $this->add_row(html_b("First Name"), $swimmer->getSwimmerFirstName()) ;
            $this->add_row(html_b("Middle Name"), $swimmer->getSwimmerMiddleName()) ;
            $this->add_row(html_b("Birth Date"), $swimmer->getBirthDate(true)) ;
            $this->add_row(html_b("USS"), $swimmer->getUSS()) ;
            $this->add_row(html_b("USS (calculated)"), $swimmer->getUSSNew()) ;
            $this->add_row(html_b("Gender"), SDIFCodeTables::GetGenderCode($swimmer->getGender())) ;
        }
        else
        {
            $this->add_row("No swim swimmer details available.") ;
        }
    }
}
?>
