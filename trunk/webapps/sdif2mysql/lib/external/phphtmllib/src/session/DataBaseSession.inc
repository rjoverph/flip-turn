<?php
/**
 * This file contains the DataBaseSession class
 * used to store php sessions in a database using
 * the phphtmllib DataBase(PDO) object.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Session
 */

/**
 * This class is used for a DB only Session Handler
 *
 *
 * CREATE TABLE session (
 *  sesskey     CHAR(32)    NOT NULL DEFAULT '',
 *  expiry      INT(11)     NOT NULL DEFAULT 0,
 *  data        LONGTEXT    DEFAULT '',
 *  PRIMARY KEY (sesskey),
 *  INDEX expiry (expiry)
 *  );
 *
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Session
 */
class DataBaseSession extends Session {

    /**
     * The database driver
     */
    public static $dbdriver = 'mysql';

    /**
     * The database host
     */
    public static $dbhost = '';

    /**
     * The database name
     */
    public static $dbname = '';

    /**
     * The database username
     */
    public static $dbuser = '';

    /**
     * The database password
     */
    public static $dbpassword = '';

    /**
     * The database table
     */
    public static $dbtable = 'session';

    /**
     * The connected DB object
     */
    public static $db = NULL;


    /**
     * crc of serialized data to save writes
     */
    protected static $crc = NULL;


    /**
     * This method initializes the ADODB_Session
     * object and connects to the DB.
     *
     * @todo make the connection parameters static members
     *       not defines.
     *
     * @param boolean $init_handler Should we register the
     *                session callbacks?
     * @return none
     */
    public static function init($init_handler=TRUE) {
        if ($init_handler) {
            session_module_name('user');
            session_set_save_handler(
                array('DataBaseSession', 'open'),
                array('DataBaseSession', 'close'),
                array('DataBaseSession', 'read'),
                array('DataBaseSession', 'write'),
                array('DataBaseSession', 'destroy'),
                array('DataBaseSession', 'gc')
                );
        }
    }

    /**
     * Open and test the memcached server to make
     * sure we have room to store
     *
     * @param string the save path
     * @param string the session name
     */
    public static function open($save_path, $session_name) {
        //verify that all of the required connection
        //parameters are set.
        $dsn = DataBase::dsn(DataBaseSession::$dbdriver,
                             DataBaseSession::$dbname,
                             DataBaseSession::$dbhost);

        try {
            DataBaseSession::$db = new DataBase($dsn,
                                                DataBaseSession::$dbuser,
                                                DataBaseSession::$dbpassword);
            return TRUE;
        } catch (Exception $e) {
            throw new phphtmllibException('DataBaseSession::init() failed: ' .
                                "Failed to connect to the DB ".$e->getMessage());
            return FALSE;
        }

        return FALSE;
    }

    /**
     * Don't need to do anything here
     *
     */
    public static function close() {
        return TRUE;
    }

    /**
     * Try and read the session data for $key from
     * the cache
     *
     * @param string the session id/key
     */
    public static function read($key) {

        try {
            $sql = "select * from ".DataBaseSession::$dbtable." where sesskey = :key ".
                   "and expiry >= :time";
            $bind_vars = array(':key' => $key,
                               ':time' => time());
            $row = DataBaseSession::$db->queryBindOneRow($sql, $bind_vars);

            if ($row) {
                DataBaseSession::$crc = strlen($row->data) . crc32($row->data);
                return $row->data;
            } else {
                //didn't find it, it could have expired.
                return '';
            }

        } catch (Exception $e) {
              throw new phphtmllibException('DataBaseSession::read() failed '.
                                  $e->getMessage());
              return '';
        }

        return $data;
    }

    /**
     * This function is used to store session data
     *
     * @param string the session id/key
     * @param string the session data
     */
    public static function write($key, $data) {

        $expiry = time() + (session_cache_expire()*60);

        //no need to write session data to db if it hasn't changed
        if (!is_null(DataBaseSession::$crc) && DataBaseSession::$crc == (strlen($data) . crc32($data))) {
            //crc for data hasn't changed.
            //lets just update the expiry
            try {
                DataBaseSession::$db->update(DataBaseSession::$dbtable,
                                             array('expiry' => $expiry),
                                             'sesskey = :key',
                                             array(':key' => $key));
            } catch (Exception $e) {
                //php doesn't like exceptions being thrown here.
                return false;
                throw new phphtmllibException('DataBaseSession::write() failed to update.'.
                                    $e->getMessage());
            }
        } else {
            //we should insert/update the record.
            //if we don't have a crc yet, we haven't loaded the entry from the db,
            //so we assume it doesn't exist ?
            if (is_null(DataBaseSession::$crc)) {
                //we didn't load it, so let's insert
                try {
                    DataBaseSession::$db->insert(DatabaseSession::$dbtable,
                                                 array('sesskey' => $key,
                                                       'expiry' => $expiry,
                                                       'data' => $data));
                } catch (Exception $e) {
                    //php doesn't like exceptions being thrown here.
                    return false;
                    throw new phphtmllibException('DataBaseSession::write() failed to insert.'.
                                        $e->getMessage());
                }
            } else {
                try {
                    DataBaseSession::$db->update(DatabaseSession::$dbtable,
                                                 array('expiry' => $expiry,
                                                       'data' => $data),
                                                 'sesskey = :key',
                                                 array(':key' => $key));
                } catch (Exception $e) {
                    //php doesn't like exceptions being thrown here.
                    return false;
                    throw new phphtmllibException('DataBaseSession::write() failed to update.'.
                                        $e->getMessage());
                }
            }
        }

    }

    /**
     * This nukes the entry
     */
    public static function destroy($key) {
        //nuke the entry in the DB

        try {
            DataBaseSession::$db->delete(DatabaseSession::$dbtable,
                                         'sesskey = :key',
                                         array(':key' => $key));
        } catch (Exception $e) {
            //something went wrong here?
            //do we care?
        }

        return TRUE;
    }

    /**
     * Garbage collection
     *
     * @param int the max lifetime any session can exist.
     */
    public static function gc($maxlifetime) {
        //nuke all old entries.
        try {
            DataBaseSession::$db->delete(DatabaseSession::$dbtable,
                                         'expiry < :time',
                                         array(':time' => time()));
        } catch (Exception $e) {
            //something went wrong here?
            //do we care?
        }

        return TRUE;
    }



}
?>
