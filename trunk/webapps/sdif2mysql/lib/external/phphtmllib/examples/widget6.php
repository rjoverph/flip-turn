<?php

/**
 * This example illustrates the use of the
 * DataList object classes.  This object
 * can show a list of data from any data source
 * and have any GUI layout and provide the
 * features of:
 * searching, sorting, paging of the data.
 *
 * This page shows the Data coming from 2 different
 * types of DB objects.  One from a PEAR::DB object,
 * and another from a ADODB object.
 *
 * $Id: widget6.php 2781 2007-05-18 17:52:38Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage widget-examples
 * @version 3.0.0
 *
 */

/**
 * Include the phphtmllib libraries
 *
 */
include_once("includes.inc");
//uncomment this to make it work locally
//include_once("db_defines.inc");


//include adodb
require_once( "external/adodb/adodb.inc.php" );

//need the PEAR includes
//set this to your pear include path
ini_set('include_path', ini_get('include_path').":/usr/share/php");
require_once( "DB.php");


/**
 * This is an example that shows how to use a PEAR db object
 * as the source for the data to show.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage widget-examples
 * @version 3.0.0
 */
class pearmysqllist extends DefaultHTMLDataList {
    //change the # of rows to display to 20 from 10
    var $_default_rows_per_page = 20;

    /**
     * the default base path to images
     * used by any child of
     * this class.
     */
    protected $_image_path = '/images/widgets/';

    /**
     * This function is called automatically by
     * the DataList constructor.  It must be
     * extended by the child class to actually
     * set the DataListSource object.
     *
     *
     */
    function get_data_source() {
        //build the PEAR DB object and connect
        //to the database.
        $dsn = "mysql://".DB_USERNAME.":".DB_PASSWORD."@".DB_HOSTNAME."/".DB_NAME;
        $db = DB::connect($dsn, TRUE);
        if (DB::isError($db)) {
            die( $db->getMessage() );
        }

        //create the DataListSource object
        //and pass in the PEAR DB object
        $source = new PEARSQLDataListSource($db);

        //set the DataListSource for this DataList
        //Every DataList needs a Source for it's data.
        $this->set_data_source( $source );

        //set the prefix for all the internal query string
        //variables.  You really only need to change this
        //if you have more then 1 DataList object per page.
        $this->set_global_prefix("pear_");
    }

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
    function user_setup() {
        //add the columns in the display that you want to view.
        //The API is :
        //Title, width, DB column name, field SORTABLE?, field SEARCHABLE?, align
        $this->add_header_item("IP", "100", "ip_address", HTMLDataList::SORTABLE,
                               HTMLDataList::SEARCHABLE, "left");
        $this->add_header_item("Version", "100", "version", HTMLDataList::SORTABLE,
                                HTMLDataList::SEARCHABLE,"center");
        $this->add_header_item("Time", "200", "time", HTMLDataList::SORTABLE,
                               HTMLDataList::NOT_SEARCHABLE,"center");


        $this->_db_setup();
    }


    /**
     * Build this method so we can override it in the child class
     * for the advanced search capability.
     *
     * @return VOID
     */
    function _db_setup() {
        $columns = "*";
        $tables = "user_downloads u, versions v";
        $where_clause = "u.version_id=v.version_id";
        $this->_datalistsource->setup_db_options($columns, $tables, $where_clause);
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
    function build_column_item($row_data, $col_name) {
        switch ($col_name) {
        case "Time":
            $obj = date("m/d/Y h:i A", strtotime($row_data["time"]));
            //$obj = $row_data["time"];
            break;
        default:
            $obj = parent::build_column_item($row_data, $col_name);
            break;
        }
        return $obj;
    }
}

/**
 * This is a subclass of the pear mysql list object.
 * The only difference being is the DataListSource object
 * for an ADODB object, instead of a PEAR DB object.
 *
 * @package phpHtmlLib
 * @subpackage widget-examples
 *
 */
class adodbmysqllist extends pearmysqllist {

    /**
     * This function is called automatically by
     * the DataList constructor.  It must be
     * extended by the child class to actually
     * set the DataListSource object.
     *
     *
     */
    function get_data_source() {
        //build the PEAR DB object and connect
        //to the database.
        $db = &ADONewConnection('mysql');  # create a connection
        $db->PConnect(DB_HOSTNAME,DB_USERNAME,DB_PASSWORD,DB_NAME);

        //create the DataListSource object
        //and pass in the PEAR DB object
        $source = new ADODBSQLDataListSource($db);

        //set the DataListSource for this DataList
        //Every DataList needs a Source for it's data.
        $this->set_data_source( $source );

        //set the prefix for all the internal query string
        //variables.  You really only need to change this
        //if you have more then 1 DataList object per page.
        $this->set_global_prefix("adodb_");
    }

    /**
     * Build this method so we can override it in the child class
     * for the advanced search capability.
     *
     * @return VOID
     */
    function _db_setup() {
        $columns = "*";
        $tables = "user_downloads u, versions v";
        $where_clause = "u.version_id=v.version_id";

        $this->_datalistsource->setup_db_options($columns, $tables, $where_clause);
    }
}

/**
 *
 * The Page object.
 *
 * @package phpHtmlLib
 * @subpackage widget-examples
 */
class DataListPage extends HTMLPage {

    protected function permission() {
        return TRUE;
    }

    protected function head_content() {
        //add the css
        //$this->add_head_css( new DefaultGUIDataListCSS );
        $this->add_css_link( "/css/widgets.php" );
    }

    protected function body_content() {

        //build the PEAR list and sort by ip_address by default
        $pearlist = new pearmysqllist("PEAR::MySQL List", 600, "ip_address", TRUE);

        //build the ADODB list using the same exact table in the DB
        //and sort by version by default
        $adodblist = new adodbmysqllist("ADODB::MySQL List", 600, "version", TRUE);

        $this->add( new DIVtag(array(),
                               $pearlist, BRtag::factory(2), $adodblist ));
    }
}


//create the page object
$page = new DataListPage("phpHtmlLib Widgets - DataList Example",
                         phphtmllib::XHTML_TRANSITIONAL);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}



print $page->render();
?>
