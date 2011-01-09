<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 *
 * $Id$
 *
 * Swim Meet Classes
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
class SwimMeet extends SDIFB1Record
{
    /**
     * Swim Meet Id
     */
    var $_swimmeetid ;

    /**
     * Timestamp
     */
    var $_timestamp ;

    /**
     * Set the swim meet id
     *
     * @param int id of the meet
     */
    function setSwimMeetId($id)
    {
        $this->_swimmeetid = $id ;
    }

    /**
     * Get the swim meet id
     *
     * @return int id of the meet
     */
    function getSwimMeetId()
    {
        return $this->_swimmeetid ;
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
     * @return boolean existance of meet by id
     */
    function SwimMeetExistsById($swimmeetid = null)
    {
        if (is_null($swimmeetid)) $swimmeetid = $this->getSwimMeetId() ;

	    //  Is id already in the database?

        $query = sprintf("SELECT swimmeetid FROM %s WHERE swimmeetid = \"%s\"",
            FT_SWIMMEETS_TABLE, $swimmeetid) ;

        $this->setQuery($query) ;
        $this->runSelectQuery(false) ;

	    //  Make sure id doesn't exist

        return (bool)($this->getQueryCount() > 0) ;
    }

    /**
     * Check if a meet already exists in the database
     * by comparing names and return a boolean accordingly.
     *
     * @param string meet name
     * @return boolean existance of meet by name
     */
    function SwimMeetExistsByName($meetname = null)
    {
        if (is_null($meetname)) $meetname = $this->getMeetName() ;

	    //  Is name already in the database?

        $query = sprintf("SELECT swimmeetid FROM %s WHERE meet_name = \"%s\"",
            FT_SWIMMEETS_TABLE, $meetname) ;

        $this->setQuery($query) ;
        $this->runSelectQuery(false) ;

	    //  Make sure name doesn't exist

        return (bool)($this->getQueryCount() > 0) ;
    }

    /**
     * Get Swim Meet Id by Name
     *
     * @param string meet name
     * @return int swim meet id
     */
    function GetSwimMeetIdByName($meetname = null)
    {
        if (is_null($meetname)) $meetname = $this->getMeetName() ;

	    //  Is name already in the database?

        $query = sprintf("SELECT swimmeetid FROM %s WHERE meet_name = \"%s\"",
            FT_SWIMMEETS_TABLE, $meetname) ;

        $this->setQuery($query) ;
        $this->runSelectQuery() ;

	    //  Make sure name doesn't exist

        return ($this->getQueryCount() > 0) ?
            $this->getQueryResult() : array('swimmeetid' => null) ;
    }

    /**
     *
     * Load meet record by Id
     *
     * @param int optional meet id
     */
    function LoadSwimMeetById($swimmeetid = null)
    {
        if (is_null($swimmeetid)) $swimmeetid = $this->getSwimMeetId() ;

        //  Dud?
        if (is_null($swimmeetid)) return false ;

        $this->setSwimMeetId($swimmeetid) ;

        //  Make sure it is a legal meet id
        if ($this->SwimMeetExistsById($swimmeetid))
        {
            $query = sprintf("SELECT * FROM %s WHERE swimmeetid=\"%s\"",
                FT_SWIMMEETS_TABLE, $swimmeetid) ;

            $this->setQuery($query) ;
            $this->runSelectQuery() ;

            $result = $this->getQueryResult() ;

            $this->setSwimMeetId($result['swimmeetid']) ;
            $this->setOrgCode($result['org_code']) ;
            $this->setFutureUse1($result['future_use_1']) ;
            $this->setMeetName($result['meet_name']) ;
            $this->setMeetAddress1($result['meet_address_1']) ;
            $this->setMeetAddress2($result['meet_address_2']) ;
            $this->setMeetCity($result['meet_city']) ;
            $this->setMeetState($result['meet_state']) ;
            $this->setMeetPostalCode($result['meet_postal_code']) ;
            $this->setMeetCountryCode($result['meet_country_code']) ;
            $this->setMeetCode($result['meet_code']) ;
            $this->setMeetStart($result['meet_start'], true) ;
            $this->setMeetEnd($result['meet_end'], true) ;
            $this->setPoolAltitude($result['pool_altitude']) ;
            $this->setFutureUse2($result['future_use_2']) ;
            $this->setCourseCode($result['course_code']) ;
            $this->setFutureUse3($result['future_use_3']) ;
            $this->setTimestamp($result['timestamp']) ;
        }

        $idExists = (bool)($this->getQueryCount() > 0) ;

	    return $idExists ;
    }

    /**
     * Add Swim Meet to database
     *
     * @return boolean successful query
     */
    function AddSwimMeet()
    {
        $this->setQuery(sprintf("INSERT INTO %s SET
            org_code=\"%s\",
            future_use_1=\"%s\",
            meet_name=\"%s\",
            meet_address_1=\"%s\",
            meet_address_2=\"%s\",
            meet_city=\"%s\",
            meet_state=\"%s\",
            meet_postal_code=\"%s\",
            meet_country_code=\"%s\",
            meet_code=\"%s\",
            meet_start=\"%s\",
            meet_end=\"%s\",
            pool_altitude=\"%s\",
            future_use_2=\"%s\",
            course_code=\"%s\",
            future_use_3=\"%s\"",
            FT_SWIMMEETS_TABLE,
            $this->getOrgCode(),
            $this->getFutureUse1(),
            $this->getMeetName(),
            $this->getMeetAddress1(),
            $this->getMeetAddress2(),
            $this->getMeetCity(),
            $this->getMeetState(),
            $this->getMeetPostalCode(),
            $this->getMeetCountryCode(),
            $this->getMeetCode(),
            $this->getMeetStart(true),
            $this->getMeetEnd(true),
            $this->getPoolAltitude(),
            $this->getFutureUse2(),
            $this->getCourseCode(),
            $this->getFutureUse3())) ;

        $success = $this->runInsertQuery() ;

        return $success ;
    }

    /**
     * Update Swim Meet in database
     *
     * @return boolean successful query
     */
    function UpdateSwimMeet()
    {
        $this->setQuery(sprintf("UPDATE %s SET
            org_code=\"%s\",
            future_use_1=\"%s\",
            meet_name=\"%s\",
            meet_address_1=\"%s\",
            meet_address_2=\"%s\",
            meet_city=\"%s\",
            meet_state=\"%s\",
            meet_postal_code=\"%s\",
            meet_country_code=\"%s\",
            meet_code=\"%s\",
            meet_start=\"%s\",
            meet_end=\"%s\",
            pool_altitude=\"%s\",
            future_use_2=\"%s\",
            course_code=\"%s\",
            future_use_3=\"%s\"
            WHERE swimmeetid=\"%s\"",
            FT_SWIMMEETS_TABLE,
            $this->getOrgCode(),
            $this->getFutureUse1(),
            $this->getMeetName(),
            $this->getMeetAddress1(),
            $this->getMeetAddress2(),
            $this->getMeetCity(),
            $this->getMeetState(),
            $this->getMeetPostalCode(),
            $this->getMeetCountryCode(),
            $this->getMeetCode(),
            $this->getMeetStart(true),
            $this->getMeetEnd(true),
            $this->getPoolAltitude(),
            $this->getFutureUse2(),
            $this->getCourseCode(),
            $this->getFutureUse3(),
            $this->getSwimMeetId())) ;

        $success = $this->runUpdateQuery() ;

        return $success ;
    }

}

/**
 * SwimMeetsDataList class
 *
 * Child GUIDataList class to present the Swim Meets in a
 * GUIDataList widget to allow the user to take some action
 * against it.
 *
 *
 * @author Mike Walsh - mike_walsh@mindspring.com
 * @access public
 * @see DefaultGUIDataList
 *
 */
class SwimMeetsDataList extends DefaultGUIDataList
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

        $this->add_header_item("Meet Date",
            "100", "meet_start", SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("Meet Name",
            "500", "meet_name", SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("City",
            "100", "meet_city", SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("State",
            "100", "meet_state", SORTABLE, SEARCHABLE, "left") ;
        
        $this->_db_setup() ;
        $this->set_show_empty_datalist_actionbar(true) ;

        //  This GDL is a form so actions can be performed on the data.

        //turn on the 'collapsable' search block.
        //The word 'Search' in the output will be clickable,
        //and hide/show the search box.
        $this->_collapsable_search = true ;

        //lets add an action column of checkboxes,
        //and allow us to save the checked items between pages.
        $this->add_action_column('radio', 'FIRST', 'swimmeetid') ;

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
            $this->action_button('Details', 'swimmeet_details.php'),
            _HTML_SPACE,
            $this->action_button('Results', 'swimmeet_results.php'),
            _HTML_SPACE,
            $this->action_button('Update', 'swimmeet_update.php')) ;

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
            $this->action_button('Add', "swimmeet_add.php")) ;

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
        $columns = "swimmeetid, meet_name, meet_start, meet_city, meet_state" ;
        $tables = FT_SWIMMEETS_TABLE ;
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
 * Class definition of a meet info table
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see SwimTeamInfoTable
 */
class SwimMeetInfoTable extends FlipTurnInfoTable
{
    /**
     * Property to hold the meet id
     */
    var $_swimmeetid ;

    /**
     * Set Swim Meet Id
     *
     * @param int - $id - Id of the swim meet
     */
    function setSwimMeetId($id)
    {
        $this->_swimmeetid = $id ;
    }

    /**
     * Get Swim Meet Id
     *
     * @return int - Id of the swimmeet
     */
    function getSwimMeetId()
    {
        return $this->_swimmeetid ;
    }

    /**
     * Construct a summary of the active season.
     *
     */
    function BuildInfoTable($swimmeetid = null)
    {
        //  Alternate the row colors
        $this->set_alt_color_flag(true) ;

        $meet = new SwimMeet() ;

        if (is_null($swimmeetid)) $swimmeetid = $this->getSwimMeetId() ;

        if (!is_null($swimmeetid) || $meet->SwimMeetExistsById($swimmeetid))
        {
            $meet->LoadSwimMeetById($swimmeetid) ;
    
            $meetstartdate = date("D M j, Y", strtotime($meet->getMeetStart())) ;
            $meetenddate = date("D M j, Y", strtotime($meet->getMeetEnd(true))) ;
            $meetenddate = date("D M j, Y", strtotime($meet->getMeetEnd(true))) ;

            $this->add_row(html_b("Organization"), SDIFCodeTables::GetOrgCode($meet->getOrgCode())) ;
            $this->add_row(html_b("Meet Name"), $meet->getMeetName()) ;
            $this->add_row(html_b("Meet Addresss 1"), $meet->getMeetAddress1()) ;
            $this->add_row(html_b("Meet Addresss 2"), $meet->getMeetAddress2()) ;
            $this->add_row(html_b("City"), $meet->getMeetCity()) ;
            $this->add_row(html_b("State"), $meet->getMeetState()) ;
            $this->add_row(html_b("Postal Code"), $meet->getMeetPostalCode()) ;
            $this->add_row(html_b("Country"), SDIFCodeTables::GetCountryCode($meet->getMeetCountryCode())) ;
            $this->add_row(html_b("Type"), SDIFCodeTables::GetMeetCode($meet->getMeetCode())) ;
            $this->add_row(html_b("Start Date"), $meetstartdate) ;
            $this->add_row(html_b("End Date"), $meetenddate) ;
            $this->add_row(html_b("Pool Altitude (feet)"), $meet->getPoolAltitude()) ;
            $this->add_row(html_b("Course"), SDIFCodeTables::GetCourseCode($meet->getCourseCode())) ;

            //$this->add_row(html_b("State"), ucfirst($meet->getLocation())) ;
        }
        else
        {
            $this->add_row("No swim meet details available.") ;
        }
    }
}
?>
