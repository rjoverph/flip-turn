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
 * (c) 2007 by Mike Walsh for WpFlipTurn.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Wp-FlipTurn
 * @subpackage db
 * @version $Revision$
 * @lastmodified $Date$
 * @lastmodifiedby $Author$
 *
 */

//  Need the DB defintions so everything will work

require_once('db.include.php') ;
include_once(PHPHTMLLIB_ABSPATH . "/widgets/data_list/includes.inc") ;

/**
 * Class for managing the FlipTurn the database interface.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 *
 */

class FlipTurnDBI
{
    /**
     * Property to store the db connection handle
     */
    var $_conn = null ;

    /**
     * Property to store the query to be exectued.
     */
    var $_query ;

   /**
    * Property to store the results of the query
    * assuming the query submitted was a SELECT query.
    */
    var $_queryResults ;

   /**
    * Property to store the number of rows returned by
    * a select query.
    */
    var $_queryCount ;

   /**
    * Property to store the ID of an INSERT query.
    */
    var $_insertId ;

   /**
    * Property to store the affected rows from a DELETE,
    * REPLACE, or UPDATE query.
    */
    var $_affectedRows ;

   /**
    * Property to store an error message from the ADOdb interface.
    */
    var $_errorMsg ;

   /**
    * Property to record set from the ADOdb interface.
    */
    var $_rs ;

   /**
    * Mode to fetch query results through the ADO DB
    * class.  By default, use associative mode which
    * constructs rows indexed by the column headers as
    * opposed to numeric index.
    */
    var $_output = ADODB_FETCH_ASSOC ;

    /**
     * Flip-Turn database die method - terminate processing
     *
     * @param string filename
     * @param string line number
     * @param string error
     */
    function ft_db_die($file, $line, $msg)
    {
        die(sprintf('%s::%s  %s', basename($file), $line, $msg)) ;
    }


    /**
     * Get empty record set
     *
     * @return mixed record set
     */
    function getEmptyRecordSet($table, $column)
    {
        $this->setQuery(sprintf("SELECT * FROM %s WHERE %s=-1", $table, $column)) ;
        $this->runSelectQuery() ;

        return $this->_rs ;
    }

    /**
     * Get the connection handle
     *
     * @return mixed connection
     */
    function getConnection()
    {
        return $this->_conn ;
    }

    /**
     * Set the error message
     *
     * @param string message text
     */
    function setErrorMsg($msg)
    {
        $this->_errorMsg = $msg ;
    }

    /**
     * Get the error message
     *
     * @return string message text
     */
    function getErrorMsg()
    {
        return $this->_errorMsg ;
    }

    /**
     * Open a database connection
     *
     * @return boolean success
     */
    function openConnection()
    {
        $success = true ;

        //  No need to open a connection if it is
        //  already open - just use the existing one!
 
        if ($this->_conn == null)
        {
            try
            { 
                $this->_conn = ADONewConnection(FT_DB_DSN) ;
            }
            catch (exception $e)
            { 
                $success = false ;
                $this->setErrorMsg($this->_conn->ErrorMsg()) ;

                if (FT_DEBUG)
                {
                    var_dump($e); 
                    adodb_backtrace($e->gettrace());
                }
            }
        }

        $this->_conn->debug = FT_DEBUG ;
        $this->_conn->SetFetchMode($this->getOutput())  ;

        return $success ;
    }

    /**
     * Close a database connection
     *
     * @return boolean success
     */
    function closeConnection()
    {
        $this->_conn->Close() ;
        $this->_conn = null ;

        return true ;
    }

    /**
     * Set the DB fetch mode.
     *
     * @param int - mode to fetch data in
     */
    function setOutput($mode = ADODB_FETCH_ASSOC)
    {
        $this->_output = $mode ;
    }

    /**
     * Get the DB fetch mode.
     *
     * @return int - mode to fetch data in
     */
    function getOutput()
    {
        return $this->_output ;
    }

    /**
     * Set the query string to be executed.
     *
     * @param string - query string
     */
    function setQuery($query)
    {
        $this->_query = $query ;
    }

    /**
     * Get the query string to be executed.
     *
     * @return string - query string
     */
    function getQuery()
    {
        return $this->_query ;
    }

    /**
     * Run an update query
     *
     * @return boolean - query insert id
     */
    function runInsertQuery()
    {
        $this->openConnection() ;

        if ($this->_conn == null)
            $this->ft_db_die(__FILE__, __LINE__, "No database connection.") ;

        //  Execute the query
 
        $rs = $this->_conn->Execute($this->getQuery()) ;

        if (!$rs)
        {
            $success = false ;
            $this->setErrorMsg($rs->ErrorMsg()) ;
        }
        else
        {
            $success = true ;
            $this->_insertId = $this->_conn->Insert_ID() ;
        }

        //$this->closeConnection() ;

        return $success ;
    }

    /**
     * Run a delete query
     *
     * @return int affected row count
     */
    function runDeleteQuery()
    {
        return $this->runDeleteReplaceOrUpdateQuery() ;
    }

    /**
     * Run a replace query
     *
     * @return int affected row count
     */
    function runReplaceQuery()
    {
        return $this->runDeleteReplaceOrUpdateQuery() ;
    }

    /**
     * Run an update query
     *
     * @return int affected row count
     */
    function runUpdateQuery()
    {
        return $this->runDeleteReplaceOrUpdateQuery() ;
    }

    /**
     * Run a delete, replace, or update query
     *
     * @return int affected row count
     */
    function runDeleteReplaceOrUpdateQuery()
    {
        $this->openConnection() ;

        if ($this->_conn == null)
            $this->ft_db_die(__FILE__, __LINE__, "No database connection.") ;

        //  Execute the query
 
        $rs = $this->_conn->Execute($this->getQuery()) ;

        if (!$rs)
        {
            $success = false ;
            $this->setErrorMsg($rs->ErrorMsg()) ;
        }
        else
        {
            $success = true ;
            $this->_affectedRows = $this->_conn->Affected_Rows() ;
        }

        //$this->closeConnection() ;

        return $success ;
    }

    /**
     * Execute a SELECT query
     *
     * @param boolean - retrieve the results or simply perform the query
     *
     */
    function runSelectQuery($retrieveResults = true)
    {
        $this->openConnection() ;

        if ($this->_conn == null)
            $this->ft_db_die(__FILE__, __LINE__, "No database connection.") ;

        //  Make sure the mode is set
        $this->_conn->SetFetchMode($this->getOutput()) ;

        //  Execute the query
 
        $this->_rs = $this->_conn->Execute($this->getQuery()) ;

        if (!$this->_rs)
        {
            $success = false ;
            $this->setErrorMsg($rs->ErrorMsg()) ;
        }
        else
        {
            $success = true ;
            $this->setQueryCount($this->_rs->RecordCount()) ;

            if ($retrieveResults)
            {
                if ($this->getOutput() == ADODB_FETCH_ASSOC)
                    $this->setQueryResults($this->_rs->GetArray()) ;
                else
                    $this->setQueryResults($this->_rs->GetRows()) ;
            }
        }

        //$this->closeConnection() ;

        return $success ;
    }

    /**
     * Return the Id value of the last Insert
     *
     */
    function getInsertId()
    {
        return $this->_insertId ;
    }

    /**
     * Return the affected rows from the last DELETE,
     * REPLACE, or UPDATE query.
     *
     */
    function getAffectedRows()
    {
        return $this->_affectedRows ;
    }

    /**
     * Set the number of rows matched by the last query.
     */
    function setQueryCount($count)
    {
        $this->_queryCount = $count ;
    }

    /**
     * Return the number of rows matched by the last query.
     */
    function getQueryCount()
    {
        return $this->_queryCount ;
    }

    /**
     * Return the result of the last query.  Since the query
     * results are stored in an array, a query which has one
     * result is stored in an array containtining one element
     * which in turn contains the query result.
     *
     * This is a shortcult to return the result of a single row.
     */
    function getQueryResult()
    {
        return $this->_queryResults[0] ;
    }

    /**
     * Set the results of the submitted query.
     */
    function setQueryResults($results)
    {
        $this->_queryResults = $results ;
    }

    /**
     * Return the results of the submitted query.
     */
    function getQueryResults()
    {
        return $this->_queryResults ;
    }

    /**
     * Display the database error condition
     *
     * @param string - the error source
     */
    function dbError($errorSource = "Database Error")
    {
        if (mysql_errno() || mysql_error())      
            trigger_error("MySQL error: " . mysql_errno() .
	        " : " . mysql_error() . "({$errorSource})", E_USER_ERROR) ;
        else 
            trigger_error("Could not connect to FlipTurn Database ({$errorSource})", E_USER_ERROR) ;
    }
}
?>
