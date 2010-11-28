<?php

/**
 * This file contains the SQLDataListSource child class
 * that uses the phphtmllib framework DataBase PDO
 *  object to talk to the DB.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib-framework
 * @subpackage DataList
 */

/**
 * This SQLDataListSource child class interacts with
 * with the specific DB via the phphtmllib DataBase
 * (PDO) abstraction objects.
 *
 * How to use?
 * in the DataList child's get_data_source() method
 * you pass in the already connected DataBase object
 * in to the constructor.
 *
 * @package phpHtmlLib-framework
 * @subpackage DataList
 */
class DataBaseSQLDataListSource extends SQLDataListSource {

    /**
     * This var holds the Database object
     * that is used to do the sql queries
     * It is assumed that the db is already
     * connected to, and the object provides
     * 2 methods:
     * query() - execute a sql query
     */
    protected $db = NULL;

    /**
     * This is the active statement object
     * returned from the query
     */
    private $stmt = NULL;

    /**
     * Holds the current row of data
     * from the last query.
     */
    private $row = NULL;

    /**
     * The index into the result set
     */
    private $index = 0;


    /**
     * The constructor is used to pass in the
     * PEAR DB object that has already been
     * created and connected to the db.
     *
     * @param ADONewConnection::Execute object - MUST BE CONNECTED
     */
    function __construct( DataBase $db ) {
        $this->set_db_object( $db );
    }

    /**
     * Set the DB object we will use
     * to talk to the DB.
     *
     * @param   object - $db the babw_db object.
     *
     */
    public function set_db_object( DataBase $db ) {
        $this->db = $db;
    }

    /**
     * This is the function that does the data fetching,
     * and sorting if needed.
     * If the source is a sql database, this is where the
     * query gets called.  This function doesn't actually read the
     * data from the DB yet.  That is what get_next_data_row()
     * does.
     *
     * @return boolean - the query passed/failed.
     */
    public function execute_query() {

        try {
            $bind_vars = array();
            $this->stmt = $this->db->queryBindLimit($this->_query, $bind_vars,
                                                    $this->get_limit(),
                                                    $this->get_offset());
            $this->stmt->setFetchMode(PDO::FETCH_ASSOC);
            return TRUE;

        } catch (Exception $e) {
            $msg = $e->getMessage();
            user_error("DataBaseSQLDataListSource::do_query() - query failed : ".$e->get_extra_as_string().' '.$msg);
            return FALSE;
        }
    }


    /**
     * This method is used to rewind to the start
     * of the array data.
     *
     */
    public function rewind() {
        //ddd('rewind');
        //not sure this is ok?
        if (!$this->executed) {
            //ddd('execute');
            //we need to make sure we execute the query?
            $this->execute();
        }
        $this->index = 0;
        $this->next();
    }

    /**
     * Return the current element.
     * Similar to the current() function for arrays in PHP
     * @return mixed current element from the collection
     */
    public function current() {
        //ddd('current');
        return $this->row;
    }

    /**
     * Return the identifying key of the current element.
     * Similar to the key() function for arrays in PHP
     * @return mixed either an integer or a string
     */
    public function key() {
        //ddd('key '.$this->index);
        return $this->index;
    }

    /**
     * Move forward to next element.
     * Similar to the next() function for arrays in PHP
     * @return void
     */
    public function next() {
        //ddd('next');
        $this->row = $this->stmt->fetch();
        $this->index++;
    }

    /**
     * Check if there is a current element after calls to rewind() or next().
     * Used to check if we've iterated to the end of the collection
     * @return boolean FALSE if there's nothing more to iterate over
     */
    public function valid() {
        if (!$this->stmt) {
            //ddd('valid ? NO');
            return FALSE;
        } else if ($this->row) {
            //ddd('valid ? YES');
            return TRUE;
        }

        return FALSE;
    }


    /**
     * This function builds the limit
     * clause portion of a DB query.
     *
     * @return string - the limit portion of
     *                  the query.
     */
    public function build_limit_clause($offset, $limit) {
        return NULL;
    }

    /**
     * find the number of rows to be returned
     * from a query from a table and where clause
     *
     * @param string $table - the table to count from
     * @param string $where_clause - a where clause
     * @param string $count_clause - any special count?
     * @param string $groupby_clause - any group by
     *
     * @return int the # of rows
     */
    public function count($tables, $where_clause='', $count_clause='*', $groupby_clause=NULL) {
        $query = "select count(".$count_clause.") as XXCOUNTXX from ".$tables." ".$where_clause." ".$groupby_clause;
        try {
            $row = $this->db->queryBindOneRow($query, array());
            $value = $row->xxcountxx;
            return ($value ? (int)$value : NULL);
        } catch (PDOException $e) {
            $msg = $e->getMessage();
            user_error("DataBaseSQLDataListSource::count() - query failed : ".$msg);
        }
    }


    /**
     * This function is used to set the debug
     * level.
     *
     * @param mixed
     * @return none
     */
    public function set_debug($level=FALSE) {
        parent::set_debug($level);
        if ($level) {
            $this->db->debug = TRUE;
        } else {
            $this->db->debug = FALSE;
        }
    }

}

?>
