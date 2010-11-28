<?php
/**
 * This file contains the base
 * Exception class for the
 * phpHtmlLib framework
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 */


/**
 * This is the phphtmllibException
 * class for phphtmllib.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 */
class phphtmllibException extends Exception {
    /**
     * To hold anything extra in the exception
     */
    protected $extra = NULL;

    /**
     * The list of error codes.
     *
     * phpHtmlLib reserves codes 1000 through 10000
     * An application should extend this base Exception
     * class and use 10001 and up for it's codes
     */


    /**
     * Validator Exception codes
     */
    //String related

    const STR_INVALID_ALPHANUM = 1000;
    const STR_INVALID_FIELD = 1001;
    const STR_INVALID_WHITESPACE = 1002;
    const STR_INVALID_LENGTH = 1003;
    const STR_INT_INVALID_NUMBER = 1004;
    const STR_INVALID_IP = 1005;
    const STR_INVALID_PATH_CHARACTERS = 1006;
    const STR_INVALID_NAME_CHARACTERS = 1007;
    const STR_INVALID_LENGTH_40 = 1008;
    const STR_INVALID_LOGIN_NAME_CHARACTERS = 1009;

    const INVALID_TYPE = 1010;

    const STR_INVALID_LOGIN_NAME_LENGTH = 1020;
    const STR_INVALID_PASSWORD_LENGTH = 1021;
    const STR_PASSWORD_CONFIRM_NO_MATCH = 1022;
    const STR_INVALID_EMAIL = 1023;
    const STR_INVALID_EMAIL_MISSING_BRACKETS = 1024;
    const STR_INVALID_LENGTH_256 = 1025;
    const STR_NOT_LEAPYEAR = 1026;
    const STR_INVALID_MONTH = 1027;
    const STR_INVALID_DAY = 1028;
    const STR_INVALID_YEAR = 1029;
    const STR_INVALID_DATE = 1030;
    const STR_INVALID_DATETIME = 1031;
    const STR_INVALID_ZIP = 1032;
    const STR_CCEXP = 1033;
    const STR_CCEXP_TOO_FAR = 1034;
    const STR_INVALID_URL = 1035;
    const STR_INVALID_DOMAIN_NAME = 1036;
    const STR_INVALID_HOST_NAME = 1037;
    const STR_INVALID_STANDALONE_HOST_NAME = 1038;
    const STR_EMPTY_UPLOAD_FILE = 1039;
    const STR_FILE_MAX_SIZE = 1040;
    const STR_FILE_PARTIAL_UPLOAD = 1041;
    const STR_FILE_MISSING = 1042;
    const STR_FILE_TYPE_INVALID = 1043;
    const STR_INVALID_HOST_WITH_PORT = 1044;

    const STR_INVALID_LOGIN_NAME_EMPTY = 1045;
    const STR_INVALID_PASSWORD_EMPTY = 1045;
    const STR_INVALID_PASSWORD_CHARACTERS = 1047;
    const STR_INVALID_PATH_LENGTH = 1048;
    const STR_INVALID_PATH_EMPTY = 1049;
    const STR_INVALID_LENGTH_N = 1050;
    const STR_INVALID_NAME_EMPTY = 1051;
    const STR_INVALID_IP_EMPTY = 1052;
    const STR_INVALID_EMAIL_EMPTY = 1053;
    const STR_INVALID_PHONE = 1054;
    const STR_INVALID_STATE = 1055;
    const STR_INVALID_TIME_FORMAT = 1056;
    const STR_INVALID_HEX_COLOR = 1057;


    //Integer related
    const INT_INVALID = 1100;
    const INT_INVALID_MONEY = 1101;
    const INT_INVALID_PRICE = 1102;
    const INT_INVALID_FLOAT = 1103;
    const INT_INVALID_ZERO_HUNDRED_NUMBER = 1104;
    const INT_INVALID_HOUR = 1105;
    const INT_INVALID_MINUTES = 1106;
    const INT_INVALID_SECONDS = 1107;
    const INT_INVALID_PORT_NUM = 1108;
    const INT_NOT_POSITIVE = 1109;
    const INT_NOT_NEGATIVE = 1110;
    const INT_INVALID_DB_ID = 1111;

    const INT_ONLY_DIGITS = 1112;
    const INT_INVALID_LEAP_DAY = 1113;
    const INT_INVALID_30_DAY = 1114;
    const INT_INVALID_YEAR_DATE_1990_3000 = 1115;
    const INT_NOT_IN_RANGE = 1116;


    /**
     * DataBase Object related
     */
    const DB_CONNECTION_FAILED = 2001;
    const DB_QUERY_CACHE_MISSING = 2002;
    const DB_QUERY_FAILED = 2003;
    const DB_QUERY_BIND_FAILED = 2004;
    const DB_QUERY_PREPARE_FAILED = 2005;
    const DB_QUERY_EXECUTE_FAILED = 2006;
    const DB_INSERT_FAILED = 2007;
    const DB_UPDATE_FAILED = 2008;
    const DB_UPDATE_NO_VALUES = 2009;

    const DB_UNSUPPORTED_DRIVER = 2010;
    const DB_META_TABLES_NO_SCHEMA = 2011;

    /**
     * Cache related
     */

    const CACHE_MEMCACHED_NO_SERVERS = 2500;
    const CACHE_MEMCACHED_CONNECT_FAILED = 2501;
    const CACHE_MEMCACHED_ADD_SERVER_FAILED = 2502;
    const CACHE_MEMCACHED_SET_DATA_FAILED = 2503;
    const CACHE_MEMCACHED_INCREMENT_DATA_FAILED = 2504;
    
    
    /**
     * Logging related
     */
    const LOG_FILE_WRITER_OPEN_FAILED = 2600;



    /**
     * DBDataObject Exception codes
     *
     */

    /**
     * An Invalid DB table column name
     *
     */
    const DBDATAOBJECT_INVALID_FIELD = 5001;

    /**
     * DBDataObject::find() found no results.
     *
     */
    const DBDATAOBJECT_FIND_NOT_FOUND = 5002;

    /**
     * Update failed
     */
    const DBDATAOBJECT_UPDATE_FAILED = 5003;

    /**
     * Insert failed
     */
    const DBDATAOBJECT_INSERT_FAILED = 5004;
    /**
     * Delete failed
     */
    const DBDATAOBJECT_DELETE_FAILED = 5005;
    /**
     * You can't change the value of an existing
     * primary key.
     */
    const DBDATAOBJECT_PKEY_CHANGE = 5006;


    /**
     * Request/Controller Related.
     */
    const ERR_REQUEST_INVALID_TARGET = 6001;


    /**
     * This method is used to get access to the
     * extra info.
     *
     * @return mixed
     */
    public function get_extra() {
        return $this->extra;
    }

    /**
     * This method is used
     * to return the extra info as a string
     *
     * @return string
     */
    public function get_extra_as_string() {
        if (is_string($this->extra)) {
            return $this->extra;
        }
        
        return var_export($this->extra, true);
    }
}
?>
