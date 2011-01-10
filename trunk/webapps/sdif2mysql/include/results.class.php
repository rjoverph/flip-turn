<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 *
 * $Id$
 *
 * Swim Result Classes
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
class SwimResult extends SDIFD0Record
{
    /**
     * Result Id property
     */
    var $_resultid ;

    /**
     * Swim Meet Id property
     */
    var $_swimmeetid ;

    /**
     * Swimmer Id property
     */
    var $_swimmerid ;

    /**
     * Timestamp
     */
    var $_timestamp ;

    /**
     * Set the swim result id
     *
     * @param int id of the result
     */
    function setResultId($id)
    {
        $this->_resultid = $id ;
    }

    /**
     * Get the swim result id
     *
     * @return int id of the result
     */
    function getResultId()
    {
        return $this->_resultid ;
    }

    /**
     * Set the swim meet id
     *
     * @param int id of the swim meet
     */
    function setSwimMeetId($id)
    {
        $this->_swimmeetid = $id ;
    }

    /**
     * Get the swim meet id
     *
     * @return int id of the swim meet
     */
    function getSwimMeetId()
    {
        return $this->_swimmeetid ;
    }

    /**
     * Set the swim team id
     *
     * @param int id of the swim team
     */
    function setSwimTeamId($id)
    {
        $this->_swimteamid = $id ;
    }

    /**
     * Get the swim team id
     *
     * @return int id of the swim team
     */
    function getSwimTeamId()
    {
        return $this->_swimteamid ;
    }

    /**
     * Set the swimmer id
     *
     * @param int id of the swim meet
     */
    function setSwimmerId($id)
    {
        $this->_swimmerid = $id ;
    }

    /**
     * Get the swimmer id
     *
     * @return int id of the swim meet
     */
    function getSwimmerId()
    {
        return $this->_swimmerid ;
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
        return $this->_timestamp ;
    }

    /**
     * Check if a id already exists in the database
     * and return a boolean accordingly.
     *
     * @param int optional id
     * @return boolean existance of result by id
     */
    function ResultExistsById($resultid = null)
    {
        if (is_null($resultid)) $resultid = $this->getResultId() ;

	    //  Is id already in the database?

        $query = sprintf("SELECT resultid FROM %s WHERE resultid = \"%s\"",
            FT_RESULTS_TABLE, $resultid) ;

        $this->setQuery($query) ;
        $this->runSelectQuery(false) ;

	    //  Make sure id doesn't exist

        return (bool)($this->getQueryCount() > 0) ;
    }

    /**
     * Check if a result already exists in the database
     * by comparing names and return a boolean accordingly.
     *
     * @param string result name
     * @return boolean existance of result by name
     */
    function ResultExistsByName($resultname = null)
    {
        if (is_null($resultname)) $resultname = $this->getResultName() ;

	    //  Is name already in the database?

        $query = sprintf("SELECT resultid FROM %s WHERE result_name = \"%s\"",
            FT_RESULTS_TABLE, $resultname) ;

        $this->setQuery($query) ;
        $this->runSelectQuery(false) ;

	    //  Make sure name doesn't exist

        return (bool)($this->getQueryCount() > 0) ;
    }

    /**
     *
     * Load result record by Id
     *
     * @param int optional result id
     */
    function LoadResultById($resultid = null)
    {
        if (is_null($resultid)) $resultid = $this->getResultId() ;

        //  Dud?
        if (is_null($resultid)) return false ;

        $this->setResultId($resultid) ;

        //  Make sure it is a legal result id
        if ($this->ResultExistsById($resultid))
        {
            $query = sprintf("SELECT * FROM %s WHERE resultid=\"%s\"",
                FT_RESULTS_TABLE, $resultid) ;

            $this->setQuery($query) ;
            $this->runSelectQuery() ;

            $result = $this->getQueryResult() ;

            $this->setResultId($result['resultid']) ;
            $this->setOrgCode($result['org_code']) ;
            $this->setFutureUse1($result['future_use_1']) ;
            $this->setResultCode($result['result_code']) ;
            $this->setResultName($result['result_name']) ;
            $this->setResultNameAbrv($result['result_name_abrv']) ;
            $this->setResultAddress1($result['result_address_1']) ;
            $this->setResultAddress2($result['result_address_2']) ;
            $this->setResultCity($result['result_city']) ;
            $this->setResultState($result['result_state']) ;
            $this->setResultPostalCode($result['result_postal_code']) ;
            $this->setResultCountryCode($result['result_country_code']) ;
            $this->setRegionCode($result['region_code']) ;
            $this->setFutureUse2($result['future_use_2']) ;
            $this->setResultCode5($result['result_code_5']) ;
            $this->setFutureUse3($result['future_use_3']) ;
            $this->setTimestamp($result['timestamp']) ;
        }

        $idExists = (bool)($this->getQueryCount() > 0) ;

	    return $idExists ;
    }

    /**
     * Check for results based on Swim Meet Id, Swim Team Id
     * and other fields to determine uniqueness.
     *
     * @return boolean existance of result
     */
    function ResultExistsByMeetTeamAndSwimmer()
    {
        return false ;
    }

    /**
     * Add Swim Result to database
     *
     * @return boolean successful query
     */
    function AddResult()
    {
        $this->setQuery(sprintf('INSERT INTO %s SET
            swimmeetid="%s",
            swimteamid="%s",
            swimmerid="%s",
            org_code="%s",
            future_use_1="%s",
            swimmer_name="%s",
            uss="%s",
            uss_new="%s",
            uss_old="%s",
            attach_code="%s",
            citizen_code="%s",
            birth_date="%s",
            age_or_class="%s",
            gender="%s",
            event_gender="%s",
            event_distance="%s",
            stroke_code="%s",
            event_number="%s",
            event_age_code="%s",
            swim_date="%s",
            seed_time="%s",
            seed_course_code="%s",
            prelim_time="%s",
            prelim_course_code="%s",
            swim_off_time="%s",
            swim_off_course_code="%s",
            finals_time="%s",
            finals_time_ft="%s",
            finals_course_code="%s",
            prelim_heat_numner="%s",
            prelim_lane_number="%s",
            finals_heat_number="%s",
            finals_lane_number="%s",
            prelim_place_ranking="%s",
            finals_place_ranking="%s",
            finals_points="%s",
            event_time_class_code="%s",
            swimmer_flight_status="%s",
            future_use_2="%s"',
            FT_RESULTS_TABLE,
            $this->getSwimmeetid(),
            $this->getSwimteamid(),
            $this->getSwimmerid(),
            $this->getOrgCode(),
            $this->getFutureUse1(),
            $this->getSwimmerName(),
            $this->getUSS(),
            $this->getUSSNew(),
            $this->getUSSOld(),
            $this->getAttachCode(),
            $this->getCitizenCode(),
            $this->getBirthDate(true),
            $this->getAgeOrClass(),
            $this->getGender(),
            $this->getEventGender(),
            $this->getEventDistance(),
            $this->getStrokeCode(),
            $this->getEventNumber(),
            $this->getEventAgeCode(),
            $this->getSwimDate(true),
            $this->getSeedTime(),
            $this->getSeedCourseCode(),
            $this->getPrelimTime(),
            $this->getPrelimCourseCode(),
            $this->getSwimOffTime(),
            $this->getSwimOffCourseCode(),
            $this->getFinalsTime(),
            $this->getFinalsTime(true),
            $this->getFinalsCourseCode(),
            $this->getPrelimHeatNumber(),
            $this->getPrelimLaneNumber(),
            $this->getFinalsHeatNumber(),
            $this->getFinalsLaneNumber(),
            $this->getPrelimPlaceRanking(),
            $this->getFinalsPlaceRanking(),
            $this->getFinalsPoints(),
            $this->getEventTimeClassCode(),
            $this->getSwimmerFlightStatus(),
            $this->getFutureUse2())) ;

        $success = $this->runInsertQuery() ;

        return $success ;
    }

    /**
     * Tweak Swim Results to database
     *
     * After all D0 records have been processed, replace any finals_time_ft fields
     * that contain 0.0 with a NULL value so they can be sorted such that no time,
     * no swim, or DQ are shown after valid times.
     *
     * @return boolean successful query
     */
    function TweakResults()
    {
        $this->setQuery(sprintf('UPDATE %s SET
            finals_time_ft=NULL WHERE finals_time=0.0', FT_RESULTS_TABLE)) ;
        $success = $this->runUpdateQuery() ;

        return $success ;
    }

    /**
     * Update Swim Result in database
     *
     * @return boolean successful query
     */
    function UpdateResult()
    {
        $this->setQuery(sprintf("UPDATE %s SET
            org_code=\"%s\",
            future_use_1=\"%s\",
            result_code=\"%s\",
            result_name=\"%s\",
            result_name_abrv=\"%s\",
            result_address_1=\"%s\",
            result_address_2=\"%s\",
            result_city=\"%s\",
            result_state=\"%s\",
            result_postal_code=\"%s\",
            result_country_code=\"%s\",
            region_code=\"%s\",
            future_use_2=\"%s\",
            result_code_5=\"%s\",
            future_use_3=\"%s\"
            WHERE resultid=\"%s\"",
            FT_RESULTS_TABLE,
            $this->getOrgCode(),
            $this->getFutureUse1(),
            $this->getResultCode(),
            $this->getResultName(),
            $this->getResultNameAbrv(),
            $this->getResultAddress1(),
            $this->getResultAddress2(),
            $this->getResultCity(),
            $this->getResultState(),
            $this->getResultPostalCode(),
            $this->getResultCountryCode(),
            $this->getRegionCode(),
            $this->getFutureUse2(),
            $this->getResultCode5(),
            $this->getFutureUse3(),
            $this->getResultId())) ;

        $success = $this->runUpdateQuery() ;

        return $success ;
    }

}

/**
 * ResultsDataList class
 *
 * Child GUIDataList class to present the Swim Results in a
 * GUIDataList widget to allow the user to take some action
 * against it.
 *
 *
 * @author Mike Walsh - mike_walsh@mindspring.com
 * @access public
 * @see DefaultGUIDataList
 *
 */
class SwimResultsDataList extends DefaultGUIDataList
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

        $this->add_header_item("Swimmer Name",
            "200", "swimmer_name", SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("Event",
            "50", "event_number", SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("Distance",
            "150", "event_distance", SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("Stroke",
            "100", "stroke_code", SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("Heat",
            "50", "finals_heat_number", SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("Lane",
            "50", "finals_lane_number", SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("Time",
            "50", "finals_time_ft", SORTABLE, SEARCHABLE, "left") ;
        
        $this->_db_setup() ;
        $this->set_show_empty_datalist_actionbar(true) ;

        //  This GDL is a form so actions can be performed on the data.

        //turn on the 'collapsable' search block.
        //The word 'Search' in the output will be clickable,
        //and hide/show the search box.
        $this->_collapsable_search = true ;

        //lets add an action column of checkboxes,
        //and allow us to save the checked items between pages.
        $this->add_action_column('radio', 'FIRST', 'resultid') ;

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
            $this->action_button('Details', 'result_details.php'),
            _HTML_SPACE,
            $this->action_button('Update', 'result_update.php')) ;

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
            $this->action_button('Add', "result_add.php")) ;

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
        $columns = "*" ;
        $tables = FT_RESULTS_TABLE ;
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
            case "Time":
                $obj = $row_data['finals_time'] ;
                break ;

            case "Distance" :
                $obj = $row_data['event_distance'] . ' ' .
                    SDIFCodeTables::getCourseCode($row_data['finals_course_code'], true) ;
                break ;

            case "Stroke" :
                $obj = SDIFCodeTables::getStrokeCode($row_data['stroke_code']) ;
                break ;

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
 * Class definition of a result info table
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see ResultInfoTable
 */
class SwimResultInfoTable extends FlipTurnInfoTable
{
    /**
     * Property to hold the result id
     */
    var $_resultid ;

    /**
     * Set Swim Result Id
     *
     * @param int - $id - Id of the swim result
     */
    function setResultId($id)
    {
        $this->_resultid = $id ;
    }

    /**
     * Get Swim Result Id
     *
     * @return int - Id of the result
     */
    function getResultId()
    {
        return $this->_resultid ;
    }

    /**
     * Construct a summary of the active season.
     *
     */
    function BuildInfoTable($resultid = null)
    {
        //  Alternate the row colors
        $this->set_alt_color_flag(true) ;

        $result = new Result() ;

        if (is_null($resultid)) $resultid = $this->getResultId() ;

        if (!is_null($resultid) || $result->ResultExistsById($resultid))
        {
            $result->LoadResultById($resultid) ;
    
            $this->add_row(html_b("Organization"), SDIFCodeTables::GetOrgCode($result->getOrgCode())) ;
            $this->add_row(html_b("Result Code"), $result->getResultCode()) ;
            $this->add_row(html_b("Result Name"), $result->getResultName()) ;
            $this->add_row(html_b("Result Name Abbreviation"), $result->getResultNameAbrv()) ;
            $this->add_row(html_b("Result Addresss 1"), $result->getResultAddress1()) ;
            $this->add_row(html_b("Result Addresss 2"), $result->getResultAddress2()) ;
            $this->add_row(html_b("City"), $result->getResultCity()) ;
            $this->add_row(html_b("State"), $result->getResultState()) ;
            $this->add_row(html_b("Postal Code"), $result->getResultPostalCode()) ;
            $this->add_row(html_b("Country"), SDIFCodeTables::GetCountryCode($result->getResultCountryCode())) ;
            $this->add_row(html_b("Region"), SDIFCodeTables::GetRegionCode($result->getRegionCode())) ;
            $this->add_row(html_b("Result Code 5th Character"), $result->getResultCode5()) ;
        }
        else
        {
            $this->add_row("No swim result details available.") ;
        }
    }
}
?>
