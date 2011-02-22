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
            $this->setSwimMeetId($result['swimmeetid']) ;
            $this->setSwimTeamId($result['swimteamid']) ;
            $this->setSwimmerId($result['swimmerid']) ;
            $this->setOrgCode($result['org_code']) ;
            $this->setFutureUse1($result['future_use_1']) ;
            $this->setSwimmerName($result['swimmer_name']) ;
            $this->setUSS($result['uss']) ;
            $this->setUSSNew($result['uss_new']) ;
            $this->setUSSOld($result['uss_old']) ;
            $this->setAttachCode($result['attach_code']) ;
            $this->setCitizenCode($result['citizen_code']) ;
            $this->setBirthDate($result['birth_date'], true) ;
            $this->setAgeOrClass($result['age_or_class']) ;
            $this->setGender($result['gender']) ;
            $this->setEventGender($result['event_gender']) ;
            $this->setEventDistance($result['event_distance']) ;
            $this->setStrokeCode($result['stroke_code']) ;
            $this->setEventNumber($result['event_number']) ;
            $this->setEventAgeCode($result['event_age_code']) ;
            $this->setSwimDate($result['swim_date'], true) ;
            $this->setSeedTime($result['seed_time']) ;
            $this->setSeedCourseCode($result['seed_course_code']) ;
            $this->setPrelimTime($result['prelim_time']) ;
            $this->setPrelimCourseCode($result['prelim_course_code']) ;
            $this->setSwimOffTime($result['swim_off_time']) ;
            $this->setSwimOffCourseCode($result['swim_off_course_code']) ;
            $this->setFinalsTime($result['finals_time'], true) ;
            $this->setFinalsCourseCode($result['finals_course_code']) ;
            $this->setPrelimHeatNumber($result['prelim_heat_number']) ;
            $this->setPrelimLaneNumber($result['prelim_lane_number']) ;
            $this->setFinalsHeatNumber($result['finals_heat_number']) ;
            $this->setFinalsLaneNumber($result['finals_lane_number']) ;
            $this->setPrelimPlaceRanking($result['prelim_place_ranking']) ;
            $this->setFinalsPlaceRanking($result['finals_place_ranking']) ;
            $this->setFinalsPoints($result['finals_points']) ;
            $this->setEventTimeClassCode($result['event_time_class_code']) ;
            $this->setSwimmerFlightStatus($result['swimmer_flight_status']) ;
            $this->setFutureUse2($result['future_use_2']) ;
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
    function ResultExistsByMeetTeamAndSwimmer($swimmeetid = null,
        $swimteamid = null, $uss = null)
    {
        if (is_null($swimmeetid)) $swimmeetid = $this->getSwimMeetId() ;
        if (is_null($swimteamid)) $swimteamid = $this->getSwimTeamId() ;
        if (is_null($uss)) $uss = $this->getUSSNew() ;

	    //  Is id already in the database?

        $query = sprintf("SELECT resultid FROM %s WHERE swimmeetid=\"%s\"
            AND swimteamid=\"%s\" AND uss_new=\"%s\"",
            FT_RESULTS_TABLE, $swimmeetid, $swimteamid, $uss) ;

        $this->setQuery($query) ;
        $this->runSelectQuery(false) ;

	    //  Make sure id doesn't exist

        return (bool)($this->getQueryCount() > 0) ;
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
            prelim_heat_number="%s",
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

    /**
     * Purge results records from the database
     *
     * @return int number of records purged
     */
    function PurgeResults()
    {
        $this->setQuery(sprintf("DELETE FROM %s", FT_RESULTS_TABLE)) ;
        $this->runDeleteQuery() ;

        return $this->getAffectedRows() ;
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
 * @see FlipTurnGUIDataList
 *
 */
class SwimResultsDataList extends FlipTurnGUIDataList
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
        $this->add_header_item("Date",
            "50", "swim_date", SORTABLE, SEARCHABLE, "left") ;
        
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
            $this->action_button('Details', 'results_details.php')) ;

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
        $where_clause = $this->getWhereClause() ;
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
                    SDIFCodeTables::GetCourseCode($row_data['finals_course_code'], true) ;
                break ;

            case "Stroke" :
                $obj = SDIFCodeTables::GetStrokeCode($row_data['stroke_code']) ;
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
 * SwimResultsDataList class
 *
 * Child GUIDataList class to present the Swim Results in a
 * GUIDataList widget to allow the user to take some action
 * against it.
 *
 *
 * @author Mike Walsh - mike_walsh@mindspring.com
 * @access public
 * @see FlipTurnGUIDataList
 *
 */
class SwimResultsByEventDataList extends FlipTurnGUIDataList
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

        $this->add_header_item("Gender",
            "150", "event_gender", SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("Age Group",
            "150", "event_age_code", SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("Stroke",
            "100", "stroke_code", SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("Distance",
            "150", "event_distance", SORTABLE, SEARCHABLE, "left") ;
        
        $this->_db_setup() ;
        $this->set_show_empty_datalist_actionbar(true) ;

        //  This GDL is a form so actions can be performed on the data.

        //turn on the 'collapsable' search block.
        //The word 'Search' in the output will be clickable,
        //and hide/show the search box.
        $this->_collapsable_search = true ;

        //lets add an action column of checkboxes,
        //and allow us to save the checked items between pages.
        $this->add_action_column('radio', 'FIRST', 'eventid') ;

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
            $this->action_button('Results', 'results_event.php')) ;

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
        $columns = "DISTINCT CONCAT(event_gender, '-', event_age_code, '-', stroke_code, '-',
            event_distance) AS eventid, event_gender, event_age_code, stroke_code,
            event_distance, finals_course_code" ;
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
 
        //  Set up the custom count based on distinct event combinations.
        $source->set_count_column('distinct event_gender, event_age_code, stroke_code, event_distance') ;

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
            case "Gender" :
                $obj = SDIFCodeTables::getGenderCode($row_data['event_gender'], true) ;
                break ;

            case "Age Group" :
                $a = &$row_data['event_age_code'] ;
                $obj = substr($a, 0, 2) . ' - ' . substr($a, 2, 2) ;
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
 * SwimResultsBySwimmerDataList class
 *
 * Child GUIDataList class to present the Swim Results in a
 * GUIDataList widget to allow the user to take some action
 * against it.
 *
 *
 * @author Mike Walsh - mike_walsh@mindspring.com
 * @access public
 * @see FlipTurnGUIDataList
 *
 */
class SwimResultsBySwimmerDataList extends FlipTurnGUIDataList
{
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

        $this->add_header_item("Name",
            "150", "swimmer_name", SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("Gender",
            "150", "gender", SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("USS",
            "150", "uss_new", SORTABLE, SEARCHABLE, "left") ;
        
        $this->_db_setup() ;
        $this->set_show_empty_datalist_actionbar(true) ;

        //  This GDL is a form so actions can be performed on the data.

        //turn on the 'collapsable' search block.
        //The word 'Search' in the output will be clickable,
        //and hide/show the search box.
        $this->_collapsable_search = true ;

        //lets add an action column of checkboxes,
        //and allow us to save the checked items between pages.
        $this->add_action_column('radio', 'FIRST', 'uss_new') ;

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
            $this->action_button('Results', 'results_swimmer.php')) ;

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
        $columns = 'DISTINCT swimmer_name, uss_new, gender' ;
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
 
        //  Set up the custom count based on distinct event combinations.
        $source->set_count_column('DISTINCT uss_new') ;

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
            case "Gender" :
                $obj = SDIFCodeTables::getGenderCode($row_data['gender'], true) ;
                break ;

            case "Age Group" :
                $a = &$row_data['event_age_code'] ;
                $obj = substr($a, 0, 2) . ' - ' . substr($a, 2, 2) ;
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
 * SwimResultsDataList class
 *
 * Child GUIDataList class to present the Swim Results in a
 * GUIDataList widget to allow the user to take some action
 * against it.
 *
 *
 * @author Mike Walsh - mike_walsh@mindspring.com
 * @access public
 * @see SwimResultsDataList
 *
 */
class SwimResultsAdminDataList extends SwimResultsDataList
{
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
            $this->action_button('Details', 'results_details.php'),
            _HTML_SPACE,
            $this->action_button('Update', 'results_update.php'),
            _HTML_SPACE,
            $this->action_button('Purge', 'results_purge.php')) ;

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
}

/**
 * Class definition of a result info table
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see ResultInfoTable
 */
class SwimResultsInfoTable extends FlipTurnInfoTable
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

        $result = new SwimResult() ;

        if (is_null($resultid)) $resultid = $this->getResultId() ;

        if (!is_null($resultid) || $result->ResultExistsById($resultid))
        {
            $result->LoadResultById($resultid) ;
    
            $this->add_row(html_b("Swim Meet Id"), $result->getSwimmeetid()) ;
            $this->add_row(html_b("Swim Team Id"), $result->getSwimteamid()) ;
            $this->add_row(html_b("Swimmer Id"), $result->getSwimmerid()) ;
            $this->add_row(html_b("Organization"), SDIFCodeTables::GetOrgCode($result->getOrgCode())) ;
            $this->add_row(html_b("Swimmer Name"), $result->getSwimmerName()) ;
            $this->add_row(html_b("USS"), $result->getUSS()) ;
            $this->add_row(html_b("USS (new)"), $result->getUSSNew()) ;
            $this->add_row(html_b("USS (old)"), $result->getUSSOld()) ;
            $this->add_row(html_b("Attached"), SDIFCodeTables::GetAttachedCode($result->getAttachCode())) ;
            $this->add_row(html_b("Citizen"), SDIFCOdeTables::GetCitizenCode($result->getCitizenCode())) ;
            $this->add_row(html_b("Birth Date"), $result->getBirthDate(true)) ;
            $this->add_row(html_b("Age or Class"), $result->getAgeOrClass()) ;
            $this->add_row(html_b("Gender"), SDIFCodeTables::GetGenderCode($result->getGender())) ;
            $this->add_row(html_b("Event Gender"), SDIFCodeTables::GetEventGenderCode($result->getEventGender())) ;
            $this->add_row(html_b("Event Distance"), $result->getEventDistance()) ;
            $this->add_row(html_b("Stroke Code"), SDIFCodeTables::GetStrokeCode($result->getStrokeCode())) ;
            $this->add_row(html_b("Event Number"), $result->getEventNumber()) ;
            $this->add_row(html_b("Event Age Code"), $result->getEventAgeCode()) ;
            $this->add_row(html_b("Swim Date"), $result->getSwimDate(true)) ;
            $this->add_row(html_b("Seed Time"), $result->getSeedTime()) ;
            $this->add_row(html_b("Seed Course"), SDIFCodeTables::GetCourseCode($result->getSeedCourseCode())) ;
            $this->add_row(html_b("Prelim Time"), $result->getPrelimTime()) ;
            $this->add_row(html_b("Prelim Course"), SDIFCodeTables::GetCourseCode($result->getPrelimCourseCode())) ;
            $this->add_row(html_b("Swim Off Time"), $result->getSwimOffTime()) ;
            $this->add_row(html_b("Swim Off Course"), SDIFCodeTables::GetCourseCode($result->getSwimOffCourseCode())) ;
            $this->add_row(html_b("Finals Time"), $result->getFinalsTime()) ;
            $this->add_row(html_b("Finals Course"), SDIFCodeTables::GetCourseCode($result->getFinalsCourseCode())) ;
            $this->add_row(html_b("Prelim Heat Number"), $result->getPrelimHeatNumber()) ;
            $this->add_row(html_b("Prelim Lane Number"), $result->getPrelimLaneNumber()) ;
            $this->add_row(html_b("Finals Heat Number"), $result->getFinalsHeatNumber()) ;
            $this->add_row(html_b("Finals Lane Number"), $result->getFinalsLaneNumber()) ;
            $this->add_row(html_b("Prelim Place Ranking"), $result->getPrelimPlaceRanking()) ;
            $this->add_row(html_b("Finals Place Ranking"), $result->getFinalsPlaceRanking()) ;
            $this->add_row(html_b("Finals Points"), $result->getFinalsPoints()) ;
            $this->add_row(html_b("Event Time Class Code"), $result->getEventTimeClassCode()) ;
            $this->add_row(html_b("Swimmer Flight Status"), $result->getSwimmerFlightStatus()) ;
        }
        else
        {
            $this->add_row("No swim result details available.") ;
        }
    }
}

/**
 * Class definition of a event result info table
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnInfoTable
 */
class EventEventInfoTable extends FlipTurnInfoTable
{
    /**
     * Property to hold the event id
     */
    var $_eventid ;

    /**
     * Set Swim Event Id
     *
     * @param int - $id - Id of the swim event
     */
    function setEventId($id)
    {
        $this->_eventid = $id ;
    }

    /**
     * Get Swim Event Id
     *
     * @return int - Id of the event
     */
    function getEventId()
    {
        return $this->_eventid ;
    }

    /**
     * Construct a summary of the active season.
     *
     */
    function BuildInfoTable($eventid = null)
    {
        //  Alternate the row colors
        $this->set_alt_color_flag(true) ;

        $result = new SwimResult() ;

        if (is_null($eventid)) $eventid = $this->getEventId() ;

        if (!is_null($eventid) || $event->EventExistsById($eventid))
        {
            $event = explode($eventid, '-') ;
            $result->setEventCode($event[0]) ;
            $result->setAgeGroupCode($event[1]) ;
            $result->setEventCode($event[2]) ;

            //$event->LoadEventById($eventid) ;
    
            $this->add_row("Event details available.") ;
            //$this->add_row(html_b("Organization"), SDIFCodeTables::GetOrgCode($event->getOrgCode())) ;
            //$this->add_row(html_b("Event Code"), $event->getEventCode()) ;
            //$this->add_row(html_b("Event Name"), $event->getEventName()) ;
            //$this->add_row(html_b("Event Name Abbreviation"), $event->getEventNameAbrv()) ;
            //$this->add_row(html_b("Event Addresss 1"), $event->getEventAddress1()) ;
            //$this->add_row(html_b("Event Addresss 2"), $event->getEventAddress2()) ;
            //$this->add_row(html_b("City"), $event->getEventCity()) ;
            //$this->add_row(html_b("State"), $event->getEventState()) ;
            //$this->add_row(html_b("Postal Code"), $event->getEventPostalCode()) ;
            //$this->add_row(html_b("Country"), SDIFCodeTables::GetCountryCode($event->getEventCountryCode())) ;
            //$this->add_row(html_b("Region"), SDIFCodeTables::GetRegionCode($event->getRegionCode())) ;
            //$this->add_row(html_b("Event Code 5th Character"), $event->getEventCode5()) ;
        }
        else
        {
            $this->add_row("No event details available.") ;
        }
    }
}
?>
