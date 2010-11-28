<?php
/**
 * This file contains the phphtmllib
 * framework DataBase object,
 * which uses PDO internally.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage DataBase
 */


/**
 * This class uses the built in php PDO class
 * to provide a consistent API for the Data Objects
 * and to allow debugging.  It supports debug output,
 * cached queries and automatic reconnections.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage DataBase
 */
class DataBase {

    /**
     * static member to hold the debug flag
     */
    public static $debug = FALSE;

    /**
     * Holds the timer class
     */
    protected $timer = NULL;

    /**
     * Timer reference count for
     * nested calls to methods
     */
    protected static $timer_count=0;

    /**
     * The cache object that is used
     * to get/set cache queries
     */
    protected $cache_obj = NULL;

    /**
     * The PDO object
     */
    private $db = NULL;


    /**
     * The dsn
     */
    private $dsn;

    /**
     * The username
     */
    private $username;

    /**
     * The password
     */
    private $password;

    /**
     * The PDO driver connection options;
     */
    private $driver_options;


    /**
     * reconnect tries
     */
    private $reconnect_tries = 2;

    /**
     * delay between reconnect tries
     * in seconds.
     */
    private $reconnect_delay = 1;


    /**
     * The contructor
     *
     * @param string $dns
     * @param string $username
     * @param string $password
     * @param string $driver_options
     * @param boolean $connect connect to the database?
     * @param int $reconnect_tries
     * @param int $reconnect_delay
     */
    public function __construct($dsn, $username='', $password='',
                                $driver_options=array(), $connect = TRUE,
                                $reconnect_tries=2, $reconnect_delay=1) {

        $this->dsn = $dsn;
        $this->username = $username;
        $this->password = $password;
        $this->driver_options = $driver_options;
        $this->reconnect_tries = $reconnect_tries;
        $this->reconnect_delay = $reconnect_delay;

        if ($connect) {
            $this->connect($dsn, $username, $password, $driver_options);
        }

        $this->init_cache();
        
        self::$debug = $GLOBALS['config']->get('db_debug', false);
    }


    /**
     * This method is used to connect to the DataBase.
     * @param string $dns
     * @param string $username
     * @param string $password
     * @param string $driver_options
     * @param int $max_connection_attempts
     * @param int $connect_retry_delay
     *
     * @return boolean FALSE = failure
     *
     * @todo do something with the exception when failure.
     */
    public function connect($dsn, $username, $password, $driver_options=array()) {

        $attempt = 0;

        while ($attempt < $this->reconnect_tries) {
            try {
                $this->db = new PDO($dsn, $username, $password, $driver_options);

                //change the Statement Class that PDO uses.
                $this->db->setAttribute(PDO::ATTR_STATEMENT_CLASS, array('DataBaseStatement', array($this->db)));
                $this->db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );

                //fix multiple queries w/ mysql so we don't have to create
                //multiple objects.
                $this->db->setAttribute(PDO::MYSQL_ATTR_USE_BUFFERED_QUERY, TRUE);

                //force lower case return column names
                $this->db->setAttribute( PDO::ATTR_CASE, PDO::CASE_LOWER );

                $return = TRUE;
                break;
            } catch (Exception $e) {
                $return = FALSE;
            }

            sleep($this->reconnect_delay);
            $attempt++;
        }

        if ($return == FALSE) {
            //we should throw an exception here?
            throw $e;
        }
        return $return;
    }

    /**
     * disconnect from the DB
     * @return void
     */
    public function disconnect() {
        unset($this->db);
    }

    /**
     * This function is used to disconnect
     * and then reconnect to the DB
     *
     * @return boolean
     */
    public function reconnect() {
        $this->disconnect();
        return $this->connect($this->dsn, $this->username,
                              $this->password, $this->driver_options);
    }

    /**
     * Use this method to get access to the
     * adodb db object.
     *
     * NOTE: This is dangerous!
     *
     * @return PDO object
     */
    public function get_pdo_object() {
        return $this->db;
    }

    /**
     * This abstract method is called in the constructor to
     * populate the cache object, if used.
     *
     * This will use FileCache by default or NoCache
     * if cache is disabled globally.
     * You can override this method to use your preferred
     * cache mechanism.
     *
     */
    protected function init_cache() {
        //set up the cache for cached queries.
        if (Cache::cache_enabled()) {
            $cache = FileCache::singleton();
        } else {
            $cache = NoCache::singleton();
        }
        $this->set_cache_obj($cache);
    }

    /**
     * This static method builds a proper formated DSN to connect
     * to a DB.
     *
     * @param string $driver_name of the database (mysql)
     * @param string $dbname / schema (users_db)
     * @param string $host (localhost)
     * @param int    $port Defaults to the driver's default
     * @return string
     */
    public static function dsn($driver_name, $dbname, $host, $port = null) {
        $dsn_port = '';
        if (!is_null($port) && is_numeric($port)) {
            $dsn_port = ';port='.$port;
        }
        return $driver_name.':dbname='.$dbname.';host='.$host.$dsn_port;
    }

    /**
     * This method is used to set the cache object
     * used for cache queries (select only)
     *
     * @param Cache $cache_obj
     */
    public function set_cache_obj(Cache $cache) {
        $this->cache_obj = $cache;
    }

    /**
     * This method is used to INSERT a new record into a table.
     *
     * @param string  the table name
     * @param array the array of column name => value pairs
     * @param string the where clause condition
     *        NOTE: this doesn't include the 'where' word.
     *        Example: 'siteid=2 and foo='bar''
     *
     * @return int last insert id
     */
    public function insert($table, $values) {
        $this->startTimer();

        //make sure we have some columns to actually update
        if ( empty($values) ) {
            throw new PDOException('No Values Defined.');
        }

        $sql = 'INSERT INTO '.$table. ' (';
        $keys = array_keys($values);
        $sql .= implode(',',$keys);
        $sql .= ') VALUES (:';

        $sql .= implode(',:', $keys) . ')';

        //we now have to prepare the query
        //and bind all of the values.
        try {
            $stmt = $this->db->prepare($sql);
        } catch (PDOException $e) {
            //check for failed connection first.
            $err = $this->db->errorInfo();
            if ($err[1] == 2006 ||
                $err[1] == 31) {
                //we lost the db connection
                if (!$this->reconnect()) {
                    throw new DataBaseException($e->getMessage(),
                                                phphtmllibException::DB_CONNECTION_FAILED,
                                                $sql);
                }
                //try again
                return $this->insert($table, $values);
            } else {
                throw new DataBaseException($e->getMessage(),
                                            phphtmllibException::DB_QUERY_PREPARE_FAILED,
                                            $sql);
            }
        }

        //ok now bind the parameters
        $bind_vars = array();
        foreach($values as $key => $value) {
            $bind_vars[':'.$key] = $value;
            $stmt->bindValue(':'.$key, $value);
        }

        //and now execute it!
        try {
            $res = $stmt->execute();
        } catch (PDOException $e) {
            throw new DataBaseException($e->getMessage(),
                                        phphtmllibException::DB_QUERY_EXECUTE_FAILED,
                                        $sql, $bind_vars);
        }

        //get the last inserted id.
        $id = $this->db->lastInsertId();

        $this->dumpTimer(__FUNCTION__,$sql, $bind_vars, $stmt->rowCount());
        return $id;
    }

    /**
     * This method is used to UPDATE a specific record in a
     * table.
     *
     * @param string  the table name
     * @param array the array of column name => value pairs
     * @param string the where clause condition
     *        NOTE: this doesn't include the 'where' word.
     *        Example: 'siteid=:siteid and foo=:foo'
     * @param array the bind vars that live in the where clause
     *        Example: array(':siteid' => 69,
     *                       ':foo' => 'blah blah');
     * @return boolean TRUE = success
     */
    public function update($table, $values,
                           $where_condition, $bind_vars=array()) {
        $this->startTimer();

        //make sure we have some columns to actually update
        if ( empty($values) ) {
            throw new DataBaseException('No Values Defined.',
                                        phphtmllibException::DB_UPDATE_NO_VALUES);
        }

        $sql = 'UPDATE '.$table.' SET ';
        foreach ($values as $key => $value) {
            $sql .= $key.'=:'.$key. ',';
        }

        //pull the ending , out
        $sql = substr($sql, 0, strlen($sql)-1);

        //add the where clause
        if ( !is_null($where_condition) ) {
            $sql .= ' WHERE '.$where_condition;
        }

        //we now have to prepare the query
        //and bind all of the values.
        try {
            $stmt = $this->db->prepare($sql);
        } catch (PDOException $e) {
            //check for failed connection first.
            $err = $this->db->errorInfo();
            if ($err[1] == 2006 ||
                $err[1] == 31) {
                //we lost the db connection
                if (!$this->reconnect()) {
                    throw new DataBaseException($e->getMessage(),
                                                phphtmllibException::DB_CONNECTION_FAILED,
                                                $sql, $bind_vars);
                }
                //try again
                return $this->update($table, $values, $where_condition, $bind_vars);
            } else {
                throw new DataBaseException($e->getMessage(),
                                            phphtmllibException::DB_QUERY_PREPARE_FAILED,
                                            $sql, $bind_vars);
            }
        }


        //ok now bind the parameters
        //first bind the user provided vars
        foreach($bind_vars as $key => $value) {
            $stmt->bindValue($key, $value);
        }

        //now bind the update vars
        foreach($values as $key => $value) {
            $bind_vars[':'.$key] = $value;
            $stmt->bindValue(':'.$key, $value);
        }

        //and now execute it!
        try {
            $res = $stmt->execute();
        } catch (PDOException $e) {
            throw new DataBaseException($e->getMessage(),
                                        phphtmllibException::DB_QUERY_EXECUTE_FAILED,
                                        $sql, $bind_vars);
        }

        $this->dumpTimer(__FUNCTION__,$sql, $bind_vars, $stmt->rowCount());
        return $res;
    }

    /**
     * This method is used to delete record(s) from
     * a table in the db.
     *
     * @param string the table name
     * @param string the where clause condition
     *        NOTE: this doesn't include the 'where' word.
     *        Example: 'siteid=:siteid and foo=:foo'
     * @param array the bind vars that live in the where clause
     *        Example: array(':siteid' => 69,
     *                       ':foo' => 'blah blah');
     * @return boolean TRUE = success
     */
    public function delete($table, $where_condition=NULL, $bind_vars=array()) {
        $this->startTimer();

        $sql = 'DELETE FROM '.$table;

        if (!is_null($where_condition)) {
            $sql .= ' WHERE '.$where_condition;

            //we now have to prepare the query
            //and bind all of the values.
            try {
                $stmt = $this->db->prepare($sql);
            } catch (PDOException $e) {
                //check for failed connection first.
                $err = $this->db->errorInfo();
                if ($err[1] == 2006 ||
                    $err[1] == 31) {
                    //we lost the db connection
                    if (!$this->reconnect()) {
                        throw new DataBaseException($e->getMessage(),
                                                phphtmllibException::DB_CONNECTION_FAILED,
                                                $sql, $bind_vars);
                    }
                    //try again
                    return $this->delete($table, $where_condition, $bind_vars);
                } else {
                    throw new DataBaseException($e->getMessage(),
                                            phphtmllibException::DB_QUERY_PREPARE_FAILED,
                                            $sql, $bind_vars);
                }
            }

            //ok now bind the parameters
            //first bind the user provided vars
            foreach($bind_vars as $key => $value) {
                $stmt->bindValue($key, $value);
            }
        } else {
            //we now have to prepare the query
            //and bind all of the values.
            $stmt = $this->db->prepare($sql);
        }

        //and now execute it!
        $res = $stmt->execute();
        $this->dumpTimer(__FUNCTION__,$sql, $bind_vars, $stmt->rowCount());
        return $res;
    }

    /**************************/
    /* QUERY (SELECT) methods */
    /**************************/

    /**
     * This method is used to do a raw exec on
     * a sql query.
     * @param string the sql query
     * @return DataBaseStatement
     */
    public function exec($sql) {
        $this->startTimer();

        //we now have to prepare the query
        //and bind all of the values.
        try {
            $stmt = $this->db->exec($sql);
        } catch (PDOException $e) {
            //check for failed connection first.
            $err = $this->db->errorInfo();
            if ($err[1] == 2006 ||
                $err[1] == 31) {
                //we lost the db connection
                if (!$this->reconnect()) {
                    throw new DataBaseException($e->getMessage(),
                                                phphtmllibException::DB_CONNECTION_FAILED,
                                                $sql);
                }
                //try again
                return $this->exec($sql);
            } else {
                throw new DataBaseException($e->getMessage(),
                                            phphtmllibException::DB_QUERY_EXECUTE_FAILED,
                                            $sql);
            }
        }


        $this->dumpTimer(__FUNCTION__,$sql, array());
        return $stmt;
    }

    /**
     * This method is used to do a select query.
     * @param string the sql query
     * @return DataBaseStatement
     */
    public function query($sql) {
        $this->startTimer();

        //we now have to prepare the query
        //and bind all of the values.
        try {
            $stmt = $this->db->query($sql);
        } catch (PDOException $e) {
            //check for failed connection first.
            $err = $this->db->errorInfo();
            if ($err[1] == 2006 ||
                $err[1] == 31) {
                //we lost the db connection
                if (!$this->reconnect()) {
                    throw new DataBaseException($e->getMessage(),
                                                phphtmllibException::DB_CONNECTION_FAILED,
                                                $sql);
                }
                //try again
                return $this->query($sql, $bind_vars);
            } else {
                throw new DataBaseException($e->getMessage(),
                                                phphtmllibException::DB_QUERY_FAILED,
                                                $sql);
            }
        }


        $this->dumpTimer(__FUNCTION__,$sql, array(), $stmt->rowCount());
        return $stmt;
    }

    /**
     * This method is used to do a select query with bind variabls.
     * This is the preferred method to use when talking to the DB for
     * queries to help aleviate sql injection issues.  If the mysqli
     * interface is loaded, then it will speed things up a big.
     *
     * Instead of manually placing values in the query, use a ?
     * and then pass in the values in the bind_vars array.
     *
     * ie.
     *   select * from foo where blah='test1' and blah2='test2';
     *
     *   is replaced by
     *
     *   select * from foo where blah=? and blah2=?
     *   $bind_vars = array('test1', 'test2');
     *
     * @param string the sql query with the bind vars
     * @param array the array of bind vars
     * @return DataBaseStatement
     */
    public function queryBind($sql, $bind_vars=array()) {
        $this->startTimer();

        //we now have to prepare the query
        //and bind all of the values.
        try {
            $stmt = $this->db->prepare($sql);
        } catch (PDOException $e) {
            $err = $this->db->errorInfo();
            //check for failed connection first.\
            if ($err[1] == 2006 ||
                $err[1] == 31) {
                //we lost the db connection
                if (!$this->reconnect()) {
                    throw new DataBaseException($e->getMessage(),
                                                phphtmllibException::DB_CONNECTION_FAILED,
                                                $sql, $bind_vars);
                }
                //try again
                return $this->queryBind($sql, $bind_vars);
            } else {
                throw new DataBaseException($e->getMessage(),
                                                phphtmllibException::DB_QUERY_PREPARE_FAILED,
                                                $sql, $bind_vars);
            }
        }


        //ok now bind the parameters
        //first bind the user provided vars
        foreach($bind_vars as $key => $value) {
            $stmt->bindValue($key, $value);
        }

        //and now execute it!
        try {
            $stmt->execute();
        }  catch (PDOException $e) {
            //must have been something wrong in the
            //constructed SQL
            throw new DataBaseException($e->getMessage(),
                                        phphtmllibException::DB_QUERY_EXECUTE_FAILED,
                                        $sql, $bind_vars);
        }

        $this->dumpTimer(__FUNCTION__,$sql, $bind_vars, $stmt->rowCount());
        return $stmt;
    }

    /**
     * This method uses bind variabls to return exactly one row
     * of data from the bind query.
     *
     * @param string the sql query with the bind vars
     * @param array the array of bind vars
     * @return stdClass
     */
    public function queryBindOneRow($sql, $bind_vars=array()) {
        $this->startTimer();

        //make sure we are using the new mysqli interface
        $stmt = $this->queryBind($sql, $bind_vars);
        if ( $stmt ) {
            $obj = $stmt->fetch();
        }

        $this->dumpTimer(__FUNCTION__,$sql, $bind_vars, $stmt->rowCount());
        return $obj;
    }

    /**
     * This method executes a bind query, then returns the first
     * value of the result set.  It assumes you only wanted 1 column
     * back from the query.  If multiple columns are fetched from the
     * select, then only the first column's value will be returned.
     *
     * @param string the sql query with the bind vars
     * @param array the array of bind vars
     * @return mixed FALSE on error or 1 column value
     */
    public function queryBindOneValue($sql, $bind_vars=array()) {
        $this->startTimer();
        $res = $this->queryBindOneRow($sql, $bind_vars);
        if ( $res ) {
            list($name, $res) = each( $res );
        }

        $this->dumpTimer(__FUNCTION__,$sql, $bind_vars);
        return $res;
    }

    /**
     * This function is used to limit the select bind query.
     * Don't use this for anything other then a
     * select
     *
     * @param string the sql statement to execute
     * @param int number of rows to limit the results to
     * @param int offset into the result set to start from
     *
     * @see http://troels.arvin.dk/db/rdbms/#select-limit-offset
     */
    public function queryBindLimit($sql, $bind_vars=array(), $nrows=-1, $offset=-1) {
        $this->startTimer();

        //first we have to build the sql query

        switch ($this->get_driver_name()) {
        case 'mysql':
            //build mysql specific limit
            $offsetStr =($offset>=0) ? ((integer)$offset)."," : '';
            $sql .= " LIMIT $offsetStr".((integer)$nrows);

            //$offsetStr = ($offset>=0) ? " OFFSET ".$offset : '';
            //$sql .= ' LIMIT '.((integer)$nrows). $offsetStr;
            break;

        case 'pgsql':
            $offsetStr = ($offset >= 0) ? " OFFSET ".((integer)$offset) : '';
            $limitStr  = ($nrows >= 0)  ? " LIMIT ".((integer)$nrows) : '';
            $sql .= $limitStr.$offsetStr;
            break;

        case "oracle":
            $sql = "select * from (".$sql.") where rownum <= :offset";
            $bind_vars[':offset'] = $nrows;
            break;


        default:
            //we don't support this driver yet
            throw new DataBaseException('Unsupported driver for queryBindLimit',
                                        phphtmllibException::DB_UNSUPPORTED_DRIVER,
                                        $sql, $bind_vars);
            break;
        }

        $stmt = $this->queryBind($sql, $bind_vars);
        $this->dumpTimer(__FUNCTION__,$sql, $bind_vars, $stmt->rowCount());
        return $stmt;
    }

    /************************/
    /*  Cache query methods */
    /************************/

    /**
     * This is identical to queryBindOneRow but that it can
     * cache the results and return cached results if it's in the cache.
     *
     * @see queryBindOneRow
     *
     * This method uses bind variabls to return exactly one row
     * of data from the bind query.
     *
     * @param string the sql query with the bind vars
     * @param array the array of bind vars
     * @param int $timeout (in seconds, Default: 60)
     * @return stdClass
     */
    public function queryBindOneRowCache($sql, $bind_vars=array(), $timeout=60) {
        if (is_null($this->cache_obj)) {
            throw new DataBaseException("No Cache object set",
                                        phphtmllibException::DB_QUERY_CACHE_MISSING,
                                        $sql, $bind_vars);
        }

        $key = $this->construct_cache_key($sql, $bind_vars);
        $value = $this->cache_obj->get($key);
        if (!$value) {
            $value = $this->queryBindOneRow($sql, $bind_vars);
            $this->cache_obj->set($key, $value, $timeout);
        }
        return $value;
    }


    /**
     * This method is used to cache ALL rows in a select query.
     *
     * @param string the sql query with the bind vars
     * @param array the array of bind vars
     * @param int $timeout (in seconds, Default: 60)
     * @return array of stdClass objects
     */
    public function queryBindAllRowsCache($sql, $bind_vars=array(), $timeout=60) {
        if (is_null($this->cache_obj)) {
            throw new DataBaseException("No Cache object set",
                                        phphtmllibException::DB_QUERY_CACHE_MISSING,
                                        $sql, $bind_vars);
        }

        $key = $this->construct_cache_key($sql, $bind_vars);
        $values = $this->cache_obj->get($key);
        if (!$values) {
            $stmt = $this->queryBind($sql, $bind_vars);
            $values = array();
            while ($row = $stmt->fetch()) {
                $values[] = $row;
            }
            $this->cache_obj->set($key, $values, $timeout);
        }
        return $values;
    }

    /**
     * This is identical to queryBindOneValue but that it can
     * cache the results and return cached results if it's in the cache.
     *
     * @see queryBindOneValue
     *
     * This method executes a bind query, then returns the first
     * value of the result set.  It assumes you only wanted 1 column
     * back from the query.  If multiple columns are fetched from the
     * select, then only the first column's value will be returned.
     *
     * @param string the sql query with the bind vars
     * @param array the array of bind vars
     * @param int $timeout (in seconds, Default: 60)
     * @return mixed FALSE on error or 1 column value
     */
    public function queryBindOneValueCache($sql, $bind_vars=array(), $timeout=60) {
        if (is_null($this->cache_obj)) {
            throw new DataBaseException("No Cache object set",
                                        phphtmllibException::DB_QUERY_CACHE_MISSING,
                                        $sql, $bind_vars);
        }

        $key = $this->construct_cache_key($sql, $bind_vars);
        $value = $this->cache_obj->get($key);
        if (!$value) {
            $value = $this->queryBindOneValue($sql, $bind_vars);
            $this->cache_obj->set($key, $value, $timeout);
        }
        return $value;
    }

    /**
     * This method is used to contruct a cache key based on
     * $sql, bind vars
     *
     * @param string $sql
     * @param array $bind
     * @return string
     */
    protected function construct_cache_key($sql, $bind) {
        $key = $sql;
        foreach($bind as $name => $value) {
            $key .= $name.':'.$value;
        }

        return str_replace(' ', '', $key);
    }

    /**************************/
    /*  HELPER public methods */
    /**************************/

    /**
     * This is a short cut function that returns a row
     * as an array
     *
     * @param string $table
     * @param string $name
     * @param string $value
     *
     * @return array
     */
    public function getRowByField($table, $name, $value, $fields = '*') {
        $obj = $this->queryBindOneRow('select ' . $fields . ' from ' . $table . ' where ' . $name . '=?', array($value));
        return $stmt->fetch(PDO::FETCH_ASSOC);
    }

    public function isRowExists($table, $name, $value) {
        $stmt = $this->queryBind('select ' . $name . ' from ' . $table . ' where ' . $name. '=?', array($name=>$value));
        return $stmt->rowCount();
    }

    /************************/
    /*  MISC public methods */
    /************************/

    /**
     * Allow us to turn on/off the debug flag
     * for this object and/or adodb.
     *
     * @param mixed boolean TRUE/FALSE for on/off or
     *              an integer for the debug LEVEL
     * @param boolean Flag for adodb object.
     * @return none
     */
    public static function set_debug_flag($flag=TRUE) {
        self::$debug = $flag;
    }

    /**
     * This method is a shortcut to retrieve all of the
     * support attributes and their values from a connected
     * db object.
     *
     * @return array
     */
    public function get_all_attributes() {
        $attributes = array(
            "AUTOCOMMIT", "ERRMODE", "CASE", "CLIENT_VERSION", "CONNECTION_STATUS",
            "DRIVER_NAME", "ORACLE_NULLS", "PERSISTENT", "PREFETCH", "SERVER_INFO",
            "SERVER_VERSION", "TIMEOUT"
        );

        $vals = array();
        foreach ($attributes as $val) {
            $key = "PDO::ATTR_".$val;
            try {
                $vals[$key] = $this->db->getAttribute(constant($key));
            } catch (Exception $e) {
                $vals[$key] = 'NOT SUPPORTED';
            }
        }

        return $vals;
    }

    /**
     * This method returns the autocommit attribute
     *
     * NOTE: from PDO::ATTR_AUTOCOMMIT attribute
     *
     * @return string
     */
    public function get_autocommit() {
        return $driver = $this->db->getAttribute(PDO::ATTR_AUTOCOMMIT);
    }

    /**
     * This method returns the ERRMODE being used.
     *
     * NOTE: from PDO::ATTR_ERRMODE attribute
     *
     * @return string
     */
    public function get_error_mode() {
        return $driver = $this->db->getAttribute(PDO::ATTR_ERRMODE);
    }

    /**
     * This method returns the case the columns
     * being return from queries return as.
     *
     * NOTE: from PDO::ATTR_CASE attribute
     *
     * @return string
     */
    public function get_case() {
        return $driver = $this->db->getAttribute(PDO::ATTR_CASE);
    }

    /**
     * This method returns the client version being
     * used.
     *
     * NOTE: from PDO::ATTR_CLIENT_VERSION attribute
     *
     * @return string
     */
    public function get_client_version() {
        return $driver = $this->db->getAttribute(PDO::ATTR_CLIENT_VERSION);
    }

    /**
     * This method returns the connection status
     *
     * NOTE: from PDO::ATTR_CONNECTION_STATUS attribute
     *
     * @return string
     */
    public function get_connection_status() {
        return $driver = $this->db->getAttribute(PDO::ATTR_CONNECTION_STATUS);
    }

    /**
     * This method returns the underlying driver
     * type being used.
     *
     * NOTE: from PDO::ATTR_DRIVER_NAME attribute
     *
     * @return string
     */
    public function get_driver_name() {
        return $driver = $this->db->getAttribute(PDO::ATTR_DRIVER_NAME);
    }

    /**
     * This method returns the persistent flag for
     * the current connection.
     *
     * NOTE: from PDO::ATTR_PERSISTENT attribute
     *
     * @return string
     */
    public function get_persistent() {
        return $driver = $this->db->getAttribute(PDO::ATTR_PERSISTENT);
    }

    /**
     * This method returns the prefect flag for
     * the current connection.
     *
     * NOTE: from PDO::ATTR_PREFETCH attribute
     *
     * @return string
     */
    public function get_prefetch() {
        return $driver = $this->db->getAttribute(PDO::ATTR_PREFETCH);
    }

    /**
     * This method returns the server info for
     * the current connection.
     *
     * NOTE: from PDO::ATTR_SERVER_INFO attribute
     *
     * @return string
     */
    public function get_server_info() {
        return $driver = $this->db->getAttribute(PDO::ATTR_SERVER_INFO);
    }

    /**
     * This method returns the server version for
     * the current connection.
     *
     * NOTE: from PDO::ATTR_SERVER_VERSION attribute
     *
     * @return string
     */
    public function get_server_version() {
        return $driver = $this->db->getAttribute(PDO::ATTR_SERVER_VERSION);
    }

    /**
     * This method returns the timeout for
     * the current connection.
     *
     * NOTE: from PDO::ATTR_SERVER_TIMEOUT attribute
     *
     * @return string
     */
    public function get_timeout() {
        return $driver = $this->db->getAttribute(PDO::ATTR_TIMEOUT);
    }

    /**
     * Returns an array of the connection information
     *
     * @return array
     */
    public function get_connection_info() {
        $info = array('driver' => $this->get_driver_name(),
                      'host' => '',
                      'dbname' => '',
                      'port' => '',
                      'username'=>$this->username,
                      'password'=>$this->password);
        $dsn = substr($this->dsn, 6);
        $bits = explode(';',$dsn);
        foreach($bits as $bit) {
            $parts = explode('=', $bit);
            $info[$parts[0]] = $parts[1];
        }

        return $info;
    }


    /*********************************/
    /* Metadata functions            */
    /* PDO currently doesn't support */
    /* Metadata functions.           */
    /*********************************/

    /**
     * This method gets the list of
     * tables in the currently
     * conected database
     *
     * @return array
     */
    public function meta_tables() {
        switch ($this->db->getAttribute(PDO::ATTR_DRIVER_NAME)) {
            case 'mysql':
            default:
                $sql = 'SELECT table_name FROM INFORMATION_SCHEMA.TABLES where table_schema=:schema';
                $dsn = substr($this->dsn, 6);
                $bits = explode(';',$dsn);
                $dbname = '';
                foreach($bits as $bit) {
                    $parts = explode('=', $bit);
                    if ($parts[0] == 'dbname') {
                        $dbname = $parts[1];
                        break;
                    }
                }

                if ($dbname == '') {
                    //we couldn't find the schema name
                    throw new DataBaseException("Couldn't find connected schema name",
                                        phphtmllibException::DB_META_TABLES_NO_SCHEMA,
                                        $sql);
                }

                $stmt = $this->queryBind($sql, array(':schema'=>$dbname));
                $tables = array();
                foreach($stmt as $table) {
                    $tables[] = $table->table_name;
                }
                return $tables;
                break;
        }


    }


    /**
     * This method returns the metadata about
     * a single table in the db.
     *
     * @param string $table
     * @return array
     */
    public function meta_table($table) {
        switch ($this->db->getAttribute(PDO::ATTR_DRIVER_NAME)) {
            case 'mysql':
                $sql = 'show columns from '.$table;

                $stmt = $this->db->query($sql);

                $columns = array();
                foreach($stmt as $column) {
                    $columns[] = $column;
                }
                return $columns;
                break;
        }
    }

    /************************/
    /* MISC private methods */
    /************************/

    /**
     * Start the timer for debugging purposes
     *
     */
    protected function startTimer() {
        if ( (defined('FORCE_DB_DEBUG') && FORCE_DB_DEBUG === TRUE) ||
             DataBase::$debug != false ) {

            //don't dump if we are a nested call
            if (DataBase::$timer_count > 0) {
                DataBase::$timer_count++;
                return;
            }
            DataBase::$timer_count++;

            if ( !isset($this->timer) ) {
                $this->timer = new Timer();
            }
            $this->timer->start();
        }
    }

    /**
     * Dump the timing information
     *
     * @param string $func the function/method called
     * @param string $sql the sql query executed
     * @param array $bind_vars the bind variables.
     * @param int $rowcount the # of rows effected by query
     * @return none.
     */
    protected function dumpTimer($func, $sql, $bind_vars=array(), $rowcount="unknown") {

        if ( (defined('FORCE_DB_DEBUG') && FORCE_DB_DEBUG === TRUE) ||
             (DataBase::$debug != false) ) {
            //don't dump if we are a nested call
            if (DataBase::$timer_count > 1) {
                DataBase::$timer_count--;
                return;
            }

            DataBase::$timer_count--;

            $this->timer->stop();
            $elapsed = $this->timer->get_elapsed();

            $c = DIVtag::factory('');
            $c->set_style('border:1px solid red;background-color:#efefef;margin:6px;padding:10px;');
            $c->add(Btag::factory(__CLASS__.'::'.$func),' Exec in ');
            $c->set_collapse();

            $span = SPANtag::factory("", $elapsed);
            if ( $elapsed > 0.2 ) {
                $span->set_style('color:red;font-weight:bold;');
            }
            $c->add( $span, "s - ");

            //number of records
            $records = SPANtag::factory('', "( ".$rowcount." )");
            $records->set_style('color:green;font-weight:bold;');
            $records->set_tag_attribute('title', $rowcount.' rows for query');
            $c->add( $records );

            $c->add(new DIVtag(array('style' => 'color:blue;font-weight:bold;padding-top:4px;'), htmlspecialchars($sql)));

            if ( isset($bind_vars) ) {
                $bind_div = new DIVtag(array('style' => 'padding-top:5px;padding-left:10px;'));

                $msg = '';
                if ( is_string($bind_vars) ) {
                    $bind_div->add($bind_vars." = '".$bind_value."'" );
                } else {
                    reset($bind_vars);
                    while ( list($k, $v) = each($bind_vars) ) {
                        $bind_div->add( $k." = '".$v."'", BRtag::factory() );
                    }
                }
                $c->add($bind_div);
            }

            if ( DataBase::$debug === "trace" ) {
                $this->_execute[] = "Exec in ".$elapsed;
            } else {
                echo( $c->render());
                flush();
            }
        }
    }

}

?>
