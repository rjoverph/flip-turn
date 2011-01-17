<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 *
 * $Id$
 *
 * Swim Team Classes
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
class SwimTeam extends SDIFC1Record
{
    /**
     * Swim Team Id
     */
    var $_swimteamid ;

    /**
     * Timestamp
     */
    var $_timestamp ;

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
     * Get the swim team id
     *
     * @return int id of the team
     */
    function getSwimTeamId()
    {
        return $this->_swimteamid ;
    }

    /**
     * Set the timestamp
     *
     * @param string timestamp
     */
    function setTimestamp($ts)
    {
        $this->_timestamp = $ts ;
    }

    /**
     * Get the timestamp
     *
     * @return string timestamp
     */
    function getTimestamp()
    {
        return ($this->_ts) ;
    }

    /**
     * Check if a id already exists in the database
     * and return a boolean accordingly.
     *
     * @param int optional id
     * @return boolean existance of team by id
     */
    function SwimTeamExistsById($swimteamid = null)
    {
        if (is_null($swimteamid)) $swimteamid = $this->getSwimTeamId() ;

	    //  Is id already in the database?

        $query = sprintf("SELECT swimteamid FROM %s WHERE swimteamid = \"%s\"",
            FT_SWIMTEAMS_TABLE, $swimteamid) ;

        $this->setQuery($query) ;
        $this->runSelectQuery(false) ;

	    //  Make sure id doesn't exist

        return (bool)($this->getQueryCount() > 0) ;
    }

    /**
     * Check if a team already exists in the database
     * by comparing names and return a boolean accordingly.
     *
     * @param string team name
     * @return boolean existance of team by name
     */
    function SwimTeamExistsByName($teamname = null)
    {
        if (is_null($teamname)) $teamname = $this->getTeamName() ;

	    //  Is name already in the database?

        $query = sprintf("SELECT swimteamid FROM %s WHERE team_name = \"%s\"",
            FT_SWIMTEAMS_TABLE, $teamname) ;

        $this->setQuery($query) ;
        $this->runSelectQuery(false) ;

	    //  Make sure name doesn't exist

        return (bool)($this->getQueryCount() > 0) ;
    }

    /**
     * Get Swim Team Id by Name
     *
     * @param string team name
     * @return int swim team id
     */
    function GetSwimTeamIdByName($teamname = null)
    {
        if (is_null($teamname)) $teamname = $this->getTeamName() ;

	    //  Is name already in the database?

        $query = sprintf("SELECT swimteamid FROM %s WHERE team_name = \"%s\"",
            FT_SWIMTEAMS_TABLE, $teamname) ;

        $this->setQuery($query) ;
        $this->runSelectQuery() ;

	    //  Make sure name doesn't exist

        return ($this->getQueryCount() > 0) ?
            $this->getQueryResult() : array('swimteamid' => null) ;
    }

    /**
     *
     * Load team record by Id
     *
     * @param int optional team id
     */
    function LoadSwimTeamById($swimteamid = null)
    {
        if (is_null($swimteamid)) $swimteamid = $this->getSwimTeamId() ;

        //  Dud?
        if (is_null($swimteamid)) return false ;

        $this->setSwimTeamId($swimteamid) ;

        //  Make sure it is a legal team id
        if ($this->SwimTeamExistsById($swimteamid))
        {
            $query = sprintf("SELECT * FROM %s WHERE swimteamid=\"%s\"",
                FT_SWIMTEAMS_TABLE, $swimteamid) ;

            $this->setQuery($query) ;
            $this->runSelectQuery() ;

            $result = $this->getQueryResult() ;

            $this->setSwimTeamId($result['swimteamid']) ;
            $this->setOrgCode($result['org_code']) ;
            $this->setFutureUse1($result['future_use_1']) ;
            $this->setTeamCode($result['team_code']) ;
            $this->setTeamName($result['team_name']) ;
            $this->setTeamNameAbrv($result['team_name_abrv']) ;
            $this->setTeamAddress1($result['team_address_1']) ;
            $this->setTeamAddress2($result['team_address_2']) ;
            $this->setTeamCity($result['team_city']) ;
            $this->setTeamState($result['team_state']) ;
            $this->setTeamPostalCode($result['team_postal_code']) ;
            $this->setTeamCountryCode($result['team_country_code']) ;
            $this->setRegionCode($result['region_code']) ;
            $this->setFutureUse2($result['future_use_2']) ;
            $this->setTeamCode5($result['team_code_5']) ;
            $this->setFutureUse3($result['future_use_3']) ;
            $this->setTimestamp($result['timestamp']) ;
        }

        $idExists = (bool)($this->getQueryCount() > 0) ;

	    return $idExists ;
    }

    /**
     * Add Swim Team to database
     *
     * @return boolean successful query
     */
    function AddSwimTeam()
    {
        $this->setQuery(sprintf("INSERT INTO %s SET
            org_code=\"%s\",
            future_use_1=\"%s\",
            team_code=\"%s\",
            team_name=\"%s\",
            team_name_abrv=\"%s\",
            team_address_1=\"%s\",
            team_address_2=\"%s\",
            team_city=\"%s\",
            team_state=\"%s\",
            team_postal_code=\"%s\",
            team_country_code=\"%s\",
            region_code=\"%s\",
            future_use_2=\"%s\",
            team_code_5=\"%s\",
            future_use_3=\"%s\"",
            FT_SWIMTEAMS_TABLE,
            $this->getOrgCode(),
            $this->getFutureUse1(),
            $this->getTeamCode(),
            $this->getTeamName(),
            $this->getTeamNameAbrv(),
            $this->getTeamAddress1(),
            $this->getTeamAddress2(),
            $this->getTeamCity(),
            $this->getTeamState(),
            $this->getTeamPostalCode(),
            $this->getTeamCountryCode(),
            $this->getRegionCode(),
            $this->getFutureUse2(),
            $this->getTeamCode5(),
            $this->getFutureUse3())) ;

        $success = $this->runInsertQuery() ;

        return $success ;
    }

    /**
     * Update Swim Team in database
     *
     * @return boolean successful query
     */
    function UpdateSwimTeam()
    {
        $this->setQuery(sprintf("UPDATE %s SET
            org_code=\"%s\",
            future_use_1=\"%s\",
            team_code=\"%s\",
            team_name=\"%s\",
            team_name_abrv=\"%s\",
            team_address_1=\"%s\",
            team_address_2=\"%s\",
            team_city=\"%s\",
            team_state=\"%s\",
            team_postal_code=\"%s\",
            team_country_code=\"%s\",
            region_code=\"%s\",
            future_use_2=\"%s\",
            team_code_5=\"%s\",
            future_use_3=\"%s\"
            WHERE swimteamid=\"%s\"",
            FT_SWIMTEAMS_TABLE,
            $this->getOrgCode(),
            $this->getFutureUse1(),
            $this->getTeamCode(),
            $this->getTeamName(),
            $this->getTeamNameAbrv(),
            $this->getTeamAddress1(),
            $this->getTeamAddress2(),
            $this->getTeamCity(),
            $this->getTeamState(),
            $this->getTeamPostalCode(),
            $this->getTeamCountryCode(),
            $this->getRegionCode(),
            $this->getFutureUse2(),
            $this->getTeamCode5(),
            $this->getFutureUse3(),
            $this->getSwimTeamId())) ;

        $success = $this->runUpdateQuery() ;

        return $success ;
    }

}

/**
 * SwimTeamsDataList class
 *
 * Child GUIDataList class to present the Swim Teams in a
 * GUIDataList widget to allow the user to take some action
 * against it.
 *
 *
 * @author Mike Walsh - mike_walsh@mindspring.com
 * @access public
 * @see DefaultGUIDataList
 *
 */
class SwimTeamsDataList extends DefaultGUIDataList
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

        $this->add_header_item("Team Name",
            "500", "team_name", SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("City",
            "100", "team_city", SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("State",
            "100", "team_state", SORTABLE, SEARCHABLE, "left") ;
        
        $this->_db_setup() ;
        $this->set_show_empty_datalist_actionbar(true) ;

        //  This GDL is a form so actions can be performed on the data.

        //turn on the 'collapsable' search block.
        //The word 'Search' in the output will be clickable,
        //and hide/show the search box.
        $this->_collapsable_search = true ;

        //lets add an action column of checkboxes,
        //and allow us to save the checked items between pages.
        $this->add_action_column('radio', 'FIRST', 'swimteamid') ;

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
            $this->action_button('Details', 'swimteam_details.php'),
            _HTML_SPACE,
            $this->action_button('Results', 'swimteam_results.php'),
            _HTML_SPACE,
            $this->action_button('Update', 'swimteam_update.php')) ;

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
            $this->action_button('Add', "swimteam_add.php")) ;

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
        $columns = "swimteamid, team_name, team_city, team_state" ;
        $tables = FT_SWIMTEAMS_TABLE ;
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
        switch ($col_name)
        {
            case "Timestamp":
                $obj = date("m/d/Y h:i A", strtotime($row_data["timestamp"])) ;
                break;
            default:
                $obj = DefaultGUIDataList::build_column_item($row_data, $col_name) ;
                break;
        }

        return $obj ;
    }    
}

/**
 * Class definition of a team info table
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see SwimTeamInfoTable
 */
class SwimTeamInfoTable extends FlipTurnInfoTable
{
    /**
     * Property to hold the team id
     */
    var $_swimteamid ;

    /**
     * Set Swim Team Id
     *
     * @param int - $id - Id of the swim team
     */
    function setSwimTeamId($id)
    {
        $this->_swimteamid = $id ;
    }

    /**
     * Get Swim Team Id
     *
     * @return int - Id of the swimteam
     */
    function getSwimTeamId()
    {
        return $this->_swimteamid ;
    }

    /**
     * Construct a summary of the active season.
     *
     */
    function BuildInfoTable($swimteamid = null)
    {
        //  Alternate the row colors
        $this->set_alt_color_flag(true) ;

        $team = new SwimTeam() ;

        if (is_null($swimteamid)) $swimteamid = $this->getSwimTeamId() ;

        if (!is_null($swimteamid) || $team->SwimTeamExistsById($swimteamid))
        {
            $team->LoadSwimTeamById($swimteamid) ;
    
            $this->add_row(html_b("Organization"), SDIFCodeTables::GetOrgCode($team->getOrgCode())) ;
            $this->add_row(html_b("Team Code"), $team->getTeamCode()) ;
            $this->add_row(html_b("Team Name"), $team->getTeamName()) ;
            $this->add_row(html_b("Team Name Abbreviation"), $team->getTeamNameAbrv()) ;
            $this->add_row(html_b("Team Addresss 1"), $team->getTeamAddress1()) ;
            $this->add_row(html_b("Team Addresss 2"), $team->getTeamAddress2()) ;
            $this->add_row(html_b("City"), $team->getTeamCity()) ;
            $this->add_row(html_b("State"), $team->getTeamState()) ;
            $this->add_row(html_b("Postal Code"), $team->getTeamPostalCode()) ;
            $this->add_row(html_b("Country"), SDIFCodeTables::GetCountryCode($team->getTeamCountryCode())) ;
            $this->add_row(html_b("Region"), SDIFCodeTables::GetRegionCode($team->getRegionCode())) ;
            $this->add_row(html_b("Team Code 5th Character"), $team->getTeamCode5()) ;
        }
        else
        {
            $this->add_row("No swim team details available.") ;
        }
    }
}
?>
