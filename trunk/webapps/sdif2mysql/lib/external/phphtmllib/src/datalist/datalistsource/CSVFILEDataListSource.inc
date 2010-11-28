<?php
/**
 * This file contains the DataListSource class
 * that gets the data from a CSV formatted file.
 *
 *
 * $Id: CSVFILEDataListSource.inc 2401 2007-02-22 21:44:39Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage DataList
 */



/**
 *
 * This DataListSource child class gets the data from a
 * CSV (comma seperated values) file on disk.
 *
 * The CSV MUST have a 'header' line before any data.
 * The 'header' line is a CSV line that provides a name
 * for each column of data in the file.
 *
 * All lines that start with '#' or '//' are ignored as
 * comments.
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage DataList
 */
class CSVFILEDataListSource extends ArrayDataListSource {


    /**
     * The csv file name/path on disk
     *
     */
    private $_filename = NULL;

    /**
     * The file descriptor pointer
     *
     */
    private $_fp = NULL;


    /**
     * this holds the headers read
     * from the top of the csv file
     */
    private $_csv_headers = array();

    /**
     * The length of the longest
     * line in the csv file
     * (so we read the line properly)
     */
    private $_maxlinelength=4096;
    


    /**
     * The constructor.
     *
     * @param string - the path to the CSV file on
     *                 on disk to use as the data source.
     *
     */
    function __construct( $filename, $maxline=4096 ) {
        if (!file_exists($filename)) {
            user_error("CSVFILEDataListSource:: (".$filename.") ".
                       "can't be found.");
        } else {
            $this->_filename = $filename;
            $this->_fp = fopen( $filename, 'r');
            if (!$this->_fp) {
                user_error("CSVFILEDataListSource:: (".$filename.") ".
                           "cannot be opened");
            }
        }
        $this->_maxlinelength = $maxline;
    }


    /**
     * The prequery.  We use this to read the file
     * into memory so we can do operations on the data
     * (search, sort, etc.)
     */
    function prequery() {
        $this->_get_header();
    }

    /**
     * This function does the query
     * and search/sort
     */
    function execute_query() {

        //we always want to filter.
        //because we read the entry,
        //then filter it.
        $this->_prequery_filter();

        $count = count($this->_data);

        if ($count > 0) {
            $this->set_total_rows( $count );
            $this->sort();
            return TRUE;
        } else {
            return FALSE;
        }
    }

    /**
     * Lets walk the file and read the entry, and
     * filter what we don't want.
     *
     */
    function _prequery_filter() {
        $count=0;
        while ($line = fgets($this->_fp, $this->_maxlinelength)) {
            if ($this->add_data_row( $this->_construct_row(trim($line)))) {
                $count++;
            }
        }

        //close the file
        fclose($this->_fp);
    }


    /**
     * This file trys to get the CSV header.
     *
     */
    function _get_header() {
        $done = FALSE;
        while (!$done) {
            $line = trim(fgets($this->_fp,$this->_maxlinelength));
            if (strncmp('#', $line, 1) != 0 &&
                strncmp('//', $line, 2) != 0 && !empty($line)) {
                $this->_csv_headers = explode(',', $line);
                $done = TRUE;
            }
        }
    }

    
    /**
     * this is used to build a row
     * from a csv line
     *
     * @param string - the original csv line from the file
     * @return array
     */
    function _construct_row( $line ) {
        $row = NULL;
        if (strncmp('#', $line, 1) != 0 &&
            strncmp('//', $line, 2) != 0 && !empty($line)) {
            $tmp = explode(",", $line);
            
            $row = array();
            foreach( $this->_csv_headers as $index => $name ) {
                $row[$name] = $tmp[$index];
            }
        }
        return $row;
    }
    


    /**
     * This function adds a row of data
     * if necesarry to the data array
     *
     */
    function add_data_row($row) {
        if ($row != NULL) {
            if ($this->get_searchby_value()) {
                //user wants to search the data
                if ($this->_find_data($row) ) {
                    $this->_data[] = $row;
                    return TRUE;
                } else {
                    return FALSE;
                }
            } else {
                $this->_data[] = $row;
                return TRUE;
            }
        } else {
            return FALSE;
        }
    }
}
?>
