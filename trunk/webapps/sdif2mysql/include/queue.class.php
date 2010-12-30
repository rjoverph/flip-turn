<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 *
 * $Id$
 *
 * Form classes.  These classes manage the
 * entry and display of the various forms used
 * by the Wp-FlipTurn plugin.
 *
 * (c) 2010 by Mike Walsh for Flip-Turn.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package FlipTurn
 * @subpackage SDIF-Queue
 * @version $Revision$
 * @lastmodified $Date$
 * @lastmodifiedby $Author$
 *
 */

include_once("db.class.php") ;
include_once(PHPHTMLLIB_ABSPATH . "/widgets/data_list/includes.inc") ;

//  Add the include path for adodb - assumed in the document root.  Where
//  is document root?  Count the number of slahes in PHPHTMLLIB_RELPATH and
//  back track up the hierarchy the appropriate number of times.

$relpath = "/" ;
$nodes = explode("/", PHPHTMLLIB_RELPATH) ;

if (!empty($nodes) && $nodes[0] == "") array_shift($nodes) ;

foreach($nodes as $node) $relpath .= "../" ;

require_once(PHPHTMLLIB_ABSPATH . $relpath . "external/adodb5/adodb.inc.php" );

include_once(PHPHTMLLIB_ABSPATH . "/form/includes.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/data_list/ADODBSQLDataListSource.inc");

/**
 * SDIFQueue
 *
 * Child class to manage the SDIF Queue.
 *
 * @author Mike Walsh - mike_walsh@mindspring.com
 * @access public
 * @see FlipTurnDBI
 *
 */
class SDIFQueue extends FlipTurnDBI
{
    /**
     *  Property to store error messages
     */
    var $_sdif_queue_status_msg ;

    /**
     * Set error message
     *
     * @param string error message
     */
    function set_status_message($msg)
    {
        $this->_sdif_queue_status_msg = $msg ;
    }

    /**
     * Get error message
     *
     * @return string error message
     */
    function get_status_message()
    {
        return $this->_sdif_queue_status_msg ;
    }

    /**
     * Validate SDIF Queue
     *
     * @return boolean verified
     */
    function ValidateQueue()
    {
        $valid = true ;
        $this->openConnection() ;

        $rs = $this->getEmptyRecordSet() ;

        $this->setQuery(sprintf('SELECT recordtype FROM %s WHERE recordtype="B1"',
            FT_SDIFQUEUE_TABLE)) ;
        $this->runSelectQuery() ;

        //  A valid meet file loaded into the SDIF queue will have
        //  exactly 1 B1 record.  Any amount != 1 invalidates the queue.

        if ($this->getQueryCount() != 1)
        {
            $valid = false ;
            $this->set_status_message(sprintf('Error:  %d \"B1\" records found in the SDIF queue.',
                $this->getRecordCount())) ;
        }

        $this->closeConnection() ;

        return $valid ;
    }

    /**
     * Purge SDIF records from the Queue
     *
     * @return int number of records purged
     */
    function PurgeQueue()
    {
        $this->openConnection() ;

        $this->setQuery(sprintf("DELETE FROM %s", FT_SDIFQUEUE_TABLE)) ;
        $this->runDeleteQuery() ;

        $this->closeConnection() ;

        return $this->getAffectedRows() ;
    }

    /**
     * Purge SDIF records from the Queue
     *
     * @return int number of records purged
     */
    function ProcessQueue()
    {
        $this->openConnection() ;

        //  Need B1 record to add or update the swim meet
 
        $this->setQuery(sprintf('SELECT sdifrecord FROM %s WHERE recordtype="B1"', FT_SDIFQUEUE_TABLE)) ;
        $this->runSelectQuery(true) ;

        $sdifrecord = new SDIFB1Record() ;
        $debug = html_h3(basename(__FILE__) . "::" . __LINE__) ;
        print $debug->render() ;
        $rslt = $this->getQueryResult() ;
        $sdifrecord->setSDIFRecord($rslt["sdifrecord"]) ;
        $sdifrecord->ParseRecord() ;
        $sdifrecord->AddMeet() ;

        $this->closeConnection() ;

        return $this->getAffectedRows() ;
    }

    /**
     * Get empty record set
     *
     * @return mixed record set
     */
    function getEmptyRecordSet()
    {
        return parent::getEmptyRecordSet(FT_SDIFQUEUE_TABLE, 'sdifrecordid') ;
    }
}

/**
 * SDIFQueueDataList class
 *
 * Child GUIDataList class to present the SDIF data in the queue in a
 * GUIDataList widget to allow the user to take some action against it.
 *
 *
 * @author Mike Walsh - mike_walsh@mindspring.com
 * @access public
 * @see DefaultGUIDataList
 *
 */
class SDIFQueueDataList extends DefaultGUIDataList
{
    /**
     * default rows per page property
     * overload the # of rows to display to 20 from 10
     *
     */
    var $_default_rows_per_page = 20 ;

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

        $this->add_header_item("Line<br/>Number",
            "50", "linenumber", NOT_SORTABLE, SEARCHABLE, "center") ;
        $this->add_header_item("Record<br/>Type",
            "50", "recordtype", NOT_SORTABLE, SEARCHABLE, "center") ;
        $this->add_header_item("SDIF Record",
            "500", "sdifrecord", NOT_SORTABLE, SEARCHABLE, "left") ;
        $this->add_header_item("Timestamp",
            "100", "timestamp", NOT_SORTABLE, NOT_SEARCHABLE, "left") ;
        
        $this->_db_setup() ;
        $this->set_show_empty_datalist_actionbar(true) ;

        //  This GDL is a form so actions can be performed on the data.

        //turn on the 'collapsable' search block.
        //The word 'Search' in the output will be clickable,
        //and hide/show the search box.
        $this->_collapsable_search = true ;

        //lets add an action column of checkboxes,
        //and allow us to save the checked items between pages.
        $this->add_action_column('checkbox', 'FIRST', 'sdifrecordid') ;

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
            $this->action_button('Process Queue', 'queue_process.php'),
            _HTML_SPACE,
            $this->action_button('Purge Queue', 'queue_purge.php')) ;

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
            $this->action_button('Upload SDIF', "queue_upload.php")) ;

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
        $columns = "*";
        $tables = FT_SDIFQUEUE_TABLE ;
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
        //$this->set_global_prefix("ft_");
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
?>
