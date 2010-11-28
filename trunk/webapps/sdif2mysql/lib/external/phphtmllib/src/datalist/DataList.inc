<?php
/**
 * This is the base class for managing a list
 * of data points.
 *
 * $Id: DataList.inc 2870 2007-08-24 04:22:18Z suren2 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage DataList
 */


/**
 * This object is the base class that can be
 * used to build a widget that shows lists of
 * data from any source via the DataListSource
 * object.  It fetches/builds/gets its data
 * from the DataListSource object, which can
 * be written to support any data source
 * (MySQL, Oracle, comma delimited file, xml, etc.)
 *
 * This base class MUST be extended by a child to
 * actually render the list.  The job of the DataList
 * class is to provide the basic API and abstraction
 * mechanism to handling searching, showing, sorting
 * lists of data.
 *
 * Each column of data is associated with a title and a
 * name.  The title is what is shown to the user for that
 * column.  The name is the mapping between the column and
 * the DataListSource.  Each column can be marked
 * as sortable and searchable.  If a column is sortable,
 * the title is a link that can be clicked on to sort.
 * The sorting is done in the DataListSource object (
 * via the sql query, or sort() functions depending on the
 * data source itself)
 *
 * The DataList object will build the title, the search block
 * (if any), the datalist controls (the links/imges for
 * first, prev, next, last, all).  Then the data columns/labels.
 * Then it will fetch each of the rows of data to display
 * from the DataListSource.
 *
 * The logic of the output calls follows in the order:
 *
 * title
 * search table/block
 * datalist controls (first, prev, next, last, all)
 * data columns/labels
 * data rows x through y
 *
 *
 * REQUIREMENTS:
 *  You must use/define a DataListSource object.
 *  You MUST override/extend the following methods:
 *
 *  * get_data_source() - used to set the DataListSource
 *                         by this class.
 *  * user_setup() - used to set the columns to show and any
 *                   options used by the DataList class and
 *                   DataListSource object.
 *
 *
 *  UI ABSTRACTION METHODS
 *  These methods allow for some level of abstraction for
 *  the layout/look/feel of the actual list of data.
 *
 *
 *  * gui_init() - the function gives the child class a chance
 *                 to do any building of the objects that will
 *                 hold the search area, column headers and the
 *                 rows of data.
 *
 *
 *  * child_add_row_cell() - This function is responsible for adding
 *                           the cell in the current row.  The method
 *                           is responsible for keeping track of the
 *                           location in its UI object for the current
 *                           row.
 *
 *  * child_get_gui() - This method returns the entire UI in 1 object
 *                      or container.  At this point the entire UI
 *                      has been constructed, the entire list of data
 *                      has been walked and inserted.
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
abstract class DataList implements phphtmllib {

    /**
     * This value holds the number
     * of pages of data we have
     * to display.
     *
     */
    protected $_num_pages=1;

    /**
     * The number of rows of data
     * to show per "page".
     * The default is 20.
     *
     */
    protected $_default_rows_per_page = 10;

    /**
     * The max number of rows to
     * show when the user does the
     * "EXPAND" command.
     */
    protected $_max_rows = 200;

    /**
     * Flag to tell us to show every
     * row that comes from the DB or not.
     * By default this is off.
     */
    protected $_show_all_rows = FALSE;

    /**
     * prefix for all list variable
     * names, so we can potentially
     * have more then 1 list per page.
     */
    protected $_global_prefix = '';


    /**
     * some constants
     */
    const VAR_NAME = 0;
    const VAR_VALUE = 1;


    /**
     * Holds an array of all the
     * form vars we need for this
     * class to work.
     *
     * NOTE: Make sure you set the default
     *       value to NULL.
     */
    protected $_vars = array("offsetVar" => array(DataList::VAR_NAME => "offset",
                                                  DataList::VAR_VALUE => NULL),
                             "orderbyVar" => array(DataList::VAR_NAME => "orderby",
                                                   DataList::VAR_VALUE => NULL),
                             "reverseorderVar" => array(DataList::VAR_NAME => "reverseorder",
                                                        DataList::VAR_VALUE => NULL),
                             "numrowsVar" => array(DataList::VAR_NAME => "numrows",
                                                   DataList::VAR_VALUE => NULL),
                             "expandrowsVar" => array(DataList::VAR_NAME => "expandrows",
                                                      DataList::VAR_VALUE => NULL));


    /**
     * Holds the db column name that
     * we want to order by default.
     */
    protected $_default_orderby = '';

    /**
     * Holds a flag to let us know to
     * reverse order the column by default
     */
    protected $_default_reverseorder = "false";


    /**
     * Holds our reference/copy of the
     * DataListSource object which is used to
     * access the data that this object uses
     *
     * @var DataListSource object
     */
    protected $_datalistsource = NULL;

    /**
     * debugging flag for debugging queries.
     *
     */
    private $_debug = FALSE;

    /**
     * This is the message displayed when no data
     * was retrieved from the database
     */
    private $_not_found_message = "No data was found";


    private $_error_flag = FALSE;


    /**
     * The constructor
     *
     *
     * @param string - the column to use as the default sorting order
     * @param boolean - sort the default column in reverse order?
     */
    function __construct($default_orderby='', $default_reverseorder=FALSE) {
        $this->_default_orderby = $default_orderby;
        if ( $default_reverseorder === TRUE ) {
            $default_reverseorder = "true";
        }

        if ( $default_reverseorder === FALSE ) {
            $default_reverseorder = "false";
        }
        $this->_default_reverseorder = $default_reverseorder;

        //Set the global prefix for our variables.
        //want to make sure we can have multiple
        //item lists per html page.
        $this->set_global_prefix('');

        //allow someone to do some generic
        //action before we get the data source
        //and start processing rows.
        $this->do_action();

        //child class MUST override this
        //method to automatically set
        //the DataListSource object.
        //This class doesn't work without it.
        $this->get_data_source();

        //This allows the child to do any initialization
        //prior to executing the queri
        $this->init();

        //now execute the DataSource data prefetch/query
        $this->datalistsource_execute();
    }

    /**
     * This protected abstract function has to be extended in
     * the child class to do any initialization that the child
     * might need to do prior to executing the datalist_source_execute();
     *
     */
    abstract protected function init();


    /**
     * This abstract method requires the child class to
     * set the datalistsource object, so the DataList knows
     * what source to use to fetch data.
     *
     * This method is called by the constructor of the DataList
     * object.
     *
     * NOTE: The extended version uses set_datalistsource();
     */
    abstract protected function get_data_source();

    /**
     * returns the current value of
     * the search field name
     *
     * @return string
     */
    abstract protected function search_field();

    /**
     * returns the current value of
     * te search field value.
     *
     * @return string
     */
    abstract protected function search_value();

    /**
     * returns the current value of the
     * simple search modifier
     *
     * @return string
     */
    abstract protected function search_modifier_value();


    /**
     * This function is used to set the
     * DataListSource object for this instance
     *
     * @param DataListSource object
     */
    function set_data_source( DataListSource $datalistsource ) {
        $this->_datalistsource = &$datalistsource;
    }


    /**
     * This method is called prior to get_data_source
     * and user_setup() to allow you to do some generic
     * action on data.  By default this does nothing.
     *
     * @return boolean TRUE = success;
     */
    protected function do_action() {
        return TRUE;
    }



    /**
     * This function sets a prefix for all
     * variables that are used in the item list
     * table on a page.  This allows you to have
     * multiple itemlists on a single html page.
     *
     * @param string $prefix - the prefix for all vars.
     */
    protected function set_global_prefix($prefix) {
        $this->_global_prefix = $prefix;
        //update all the vars used
        foreach ($this->_vars as $name => $value ) {
            $this->_vars[$name][DataList::VAR_NAME] = $prefix.$value[DataList::VAR_NAME];
        }
    }

    /**
     * returns the current variable prefix
     * string being used.
     *
     * @return string - current global prefix
     */
    protected function get_global_prefix() {
        return $this->_global_prefix;
    }




    /***************************************/
    /*  Some methods for the data output   */
    /***************************************/

    /**
     * This function sets the default # of rows
     * per page to display.  By default its 10.
     * This lets the user override this value.
     *
     * @param int - the # of rows to use.
     */
    protected function set_default_num_rows( $num_rows ) {
        $this->_default_rows_per_page = $num_rows;
    }

    /**
     * This function gets the current default
     * number of rows to display setting.
     *
     * @return int
     */
    protected function get_default_num_rows( ) {
        return $this->_default_rows_per_page;
    }

    /**
     * This returns the Maximum # of rows to
     * display when in expand mode
     *
     * @return int
     */
    protected function get_max_rows() {
        return $this->_max_rows;
    }

    /**
     * This sets the maximum # of rows to
     * display when in expand mode
     *
     * @param int - new # of maximum rows
     *              to display when in 'expand' mode
     *
     */
    protected function set_max_rows( $max ) {
        $this->_max_rows = $max;
    }

    /**
     * This method sets the flag to tell us
     * to show every row found in the DataListSource.
     *
     * @param boolean TRUE = show all rows
     */
    protected function set_showall($flag=TRUE) {
        $this->_show_all_rows = $flag;
    }

    /**
     * This returns the value of the show all rows
     * flag
     *
     * @return boolean
     */
    protected function get_showall() {
        return $this->_show_all_rows;
    }



    /**
     * This function is used to set up any
     * data that needs to be munged before the
     * data is fetched from the DataListSource
     *
     */
    protected function datalistsource_execute() {
        $this->_check_datasource("data_prefetch");

        //try and build the limit correctly
        //based on the max rows that should be displayed.
        if ( $this->expandrows() ) {
            if ($this->get_showall()) {
                $limit = -1;
            } else {
                $this->set_default_num_rows( $this->get_max_rows() );
                $this->set_numrows( $this->get_max_rows() );
                $limit = $this->numrows();
            }
        } else {
            $limit = $this->numrows();
        }


        //set the parameters of the query.
        if ($this->_debug >=2) {
            //lets dump the query params
            $str = '';
            foreach( $this->_vars as $name => $var) {
                $str .= $var[DataList::VAR_NAME].'='.$this->_get($name).'; ';
            }
            ddd($str);
        }
        $this->_datalistsource->set_query_params($this->offset(), $limit,
                                                 $this->orderby(), $this->reverseorder(),
                                                 $this->search_field(), $this->search_value(),
                                                 $this->search_modifier_value(),
                                                 $this->extra_query_params());

        //now execute the query
        $this->_query_worked = $this->_datalistsource->execute();
    }

    /**
     * This method should be extended by the child
     * to pass any extra params to the datalistsource
     * prior to calling datalistsource->execute()
     *
     * @return array
     */
    protected function extra_query_params() {
        return array();
    }


    /**
     * general DataListSource object checker.
     *
     */
    protected function _check_datasource($function_name) {
        if ( !is_object($this->_datalistsource) ) {
            user_error("DataList::".$function_name."() - DataListSource object is not set");
            exit;
        }
    }


    /*********************************************/
    /*     REQUEST VARIABLE SECTION              */
    /*********************************************/


    /**
     * Function used to get the current
     * value of one of the control vars
     * for this class
     *
     * @param string - the name we want to get
     * @param mixed - the default value if not set
     * @return the current value or default if not set
     */
    protected function _get($name, $default_value=NULL) {
        //first make sure it has a value.
        if (is_null($this->_vars[$name][DataList::VAR_VALUE])) {
            //is it in the request?
            if (!isset($_REQUEST[$this->_vars[$name][DataList::VAR_NAME]])) {
                $this->_set($name, $default_value);
            } else {
                //it wasn't set, and isn't in the request
                //we'll use the default value
                $this->_set($name, $_REQUEST[$this->_vars[$name][DataList::VAR_NAME]]);
            }
        }

        return $this->_vars[$name][DataList::VAR_VALUE];
    }

    /**
     * This function is used to set the
     * value of the control var
     *
     * @param string - the name we want to get
     * @param mixed - the new value for it.
     */
    protected function _set($name, $value) {
        $this->_vars[$name][DataList::VAR_VALUE] = $value;
    }

    /**
     * This function returns the current value
     * of the offset variable. This is an offset
     * into the query return data set.
     *
     * @return int - the current value.
     */
    protected function offset() {
        if ($this->get_showall() && $this->expandrows()) {
            return 0;
        } else {
            return (int)$this->_get("offsetVar", 0);
        }
    }

    /**
     * This function is used to set/change
     * the offset for this list.
     *
     * @param int - the new offset.
     */
    protected function set_offset($new_offset) {
        $this->_set("offsetVar", $new_offset);
    }

    /**
     * This function returns the value of the
     * current orderby variable.
     *
     * @return string.
     */
    protected function orderby() {
        return $this->_get("orderbyVar", $this->_default_orderby);
    }

    /**
     * This is used to reset the orderby
     *
     * @param string
     */
    protected function set_orderby($orderby) {
        $this->_set('orderbyVar', $orderby);
    }


    /**
     * This builds a query string var for the
     * orderby value.
     *
     * @return string - "orderby=(thevalue)"
     */
    protected function build_orderby_querystring() {
        $str = $this->_vars["orderbyVar"]."=".urlencode($this->orderby());
        return $str;
    }

    /**
     * This function returns the current value of
     * the reverse order member variable.
     *
     * @return string.
     */
    protected function reverseorder() {
        return $this->_get("reverseorderVar", $this->_default_reverseorder);
    }

    /**
     * This function sets the reverse order flag
     * to a new value.
     *
     * @param string - the new value.
     */
    protected function set_reverseorder($new_value) {
        $this->_set("reverseorderVar", $new_value);
    }

    /**
     * This builds a query string var for the
     * reverseorder value.
     *
     * @return string - "orderby=(thevalue)"
     */
    protected function build_reverseorder_querystring() {
        $str = $this->_vars["reverseorderVar"]."=".urlencode($this->reverseorder());
        return $str;
    }

    /**
     * This function returns the number of rows
     * that the query found.
     *
     * @return int - the number of rows
     */
    protected function numrows() {
        return(int)$this->_get("numrowsVar", $this->_default_rows_per_page);
    }

    /**
     * This function sets the # of rows to display
     * per page.
     *
     * @param int - the # of rows
     */
    protected function set_numrows($new_numrows) {
        $this->_set("numrowsVar", $new_numrows);
    }


    /**
     * returns the current value of the expandrows
     * flag.  This tells us if they want the entire
     * list of data back from the DB.
     *
     * @return string - the current value
     */
    protected function expandrows() {
        if ($this->get_showall()) {
            $default = 1;
        } else {
            $default = 0;
        }
        return (int)$this->_get("expandrowsVar", $default);
    }

    /**
     * This sets the expandrows.
     *
     * @param boolean
     */
    protected function set_expandrows($flag=TRUE) {
        $flag = ($flag ? 1:0);
        $this->_set("expandrowsVar", $flag);
    }




    /**
     * This function is used to set the
     * message displayed when no data is found
     *
     * @param string
     */
    protected function set_not_found_message($mesg) {
        $this->_not_found_message = $mesg;
    }

    /**
     * This function is used to get the
     * message displayed when no data is found
     *
     * @return string
     */
    protected function get_not_found_message() {
        return $this->_not_found_message;
    }


    /**
     * This function is used to set the value
     * of the _show_results_flag
     *
     * @param boolean - TRUE to show the results
     */
    protected function set_show_results( $flag=TRUE ) {
        $this->_show_results_flag = $flag;
    }


    /**
     * This function is used to let render() know
     * that we should show the results or not.
     *
     * @return boolean
     */
    protected function _show_results() {
        return $this->_show_results_flag;
    }



    /**
     * This function returns the current
     * page that the item list is on.
     *
     * @return int
     */
    protected function get_current_page() {
        return((int) ($this->offset() / $this->numrows())) + 1;
    }

    /**
     * This function returns the #
     * of pages that are available
     * for this list of items.
     *
     * @return int
     */
    protected function get_num_pages() {
        $this->_check_datasource("get_num_pages");
        $total_rows = $this->_datalistsource->get_total_rows();

        if ($this->get_showall() && $this->expandrows()) {
            return 1;
        }

        $cnt = (int)($total_rows / $this->numrows());
        if ( (($total_rows % $this->numrows()) != 0) || ($total_rows == 0) ) {
            $cnt++;
        }
        return $cnt;
    }

    /**
     * This calculates the last page #
     * for this list of items
     *
     * @return int
     */
    protected function get_last_page() {
        return $this->get_num_pages();
    }

    /**
     * This function builds the string
     * that describes the current page
     * out of n pages the list is showing
     *
     * @return string (ie. 1 to 10 of 25)
     */
    protected function get_page_info() {
        $offset = $this->offset();
        //hack fix to fix a corner case.
        if ($offset > $this->_datalistsource->get_total_rows() ) {
            $this->set_offset(0);
        }

        $cur_page = $this->get_current_page();
        $low_range = $this->offset() + 1;
        $num_pages = $this->get_num_pages();

        $this->_check_datasource("get_page_info");
        $total_rows = $this->_datalistsource->get_total_rows();

        if ($this->get_showall() && $this->expandrows()) {
            $num_rows_per_page = $total_rows;
        } else {
            $num_rows_per_page = $this->numrows();
        }

        $high_range = $low_range + ($num_rows_per_page - 1);
        if ( $high_range > $total_rows ) {
            $high_range = $total_rows;
        }

        if ( $total_rows == 0 ) {
            $str = "0 of 0";
        } else {
            $str  = $low_range . " to ". $high_range;
            $str .= " of ".$total_rows;
        }

        return $str;
    }


    /**
     * This function is used to set the debug
     * level.
     *
     * @param mixed
     * @return none
     */
    public function set_debug($level=FALSE) {
        $this->_debug = $level;
        //make sure the datasource is set
        $this->_check_datasource('set_debug');
        $this->_datalistsource->set_debug($level);
    }


    /*******************************/
    /* Errors related stuff here   */
    /*******************************/


    /**
     * This method is used to tell the class
     * that we do in fact have errors
     *
     * @param boolean $error_flag
     */
    protected function set_error_flag($error_flag=TRUE) {
        $this->_error_flag = $error_flag;
    }

    /**
     * Do we have errors to display?
     *
     * @return boolean
     */
    public function has_errors() {
        return $this->_error_flag;
    }

    /**
     * This method is abstracted to force the
     * child class to build and return the errors
     * display.
     *
     * @return object/string
     */
    abstract public function build_errors();
}
?>
