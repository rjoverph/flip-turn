<?php
/**
 * Validator class used to validate
 * data fields in our application
 *
 * @author Suren Markosian
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Validation
 *
 * @todo Since these are generated from MySQL Schema, one might consider
 *       implementing all of the possible MySQL Data types (TIMESTAMP
 *       comes to mind...)
 */



/**
 * This is the new Validation engine for
 * phphtmllib.  It replaces the older
 * FormValidation and FormErrors use
 * in the Form Engine.  It is used by
 * the FormProcessor, FormContent,
 * FormElements as well as any
 * other object that needs to validate
 * data, and their types.
 *
 * All is_* functions will now throw
 * a ValidatorException upon error.
 * The ValidatorException will contain
 * the error code as well as the
 * error message.
 *
 * The Error strings are looked up in
 * the ValidatorErrors object.
 *
 * @link ValidatorErrors
 * @link ValidatorException
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Validation
 */
class Validator {

    /**
     * The Errors object
     */
    protected static $err = NULL;

    const TYPE_ID = 0;
    const TYPE_INT = 1;
    const TYPE_CHAR = 2;
    const TYPE_STRING = 3;
    const TYPE_BOOL = 4;
    const TYPE_ARRAY = 5;
    const TYPE_DATETIME = 6;
    const TYPE_TEXT = 7;
    const TYPE_ENUM = 8;
    const TYPE_BLOB = 9;
    const TYPE_FLOAT = 10;
    const TYPE_POINT = 20;
    const TYPE_MULTIPOINT = 21;
    const TYPE_LINESTRING = 22;
    const TYPE_MULTILINESTRING = 23;
    const TYPE_POLYGON = 24;
    const TYPE_MULTIPOLYGON = 25;
    const TYPE_GEOMETRYCOLLECTION = 26;

    const TYPE_NULL_INT = 101;
    const TYPE_NULL_CHAR = 102;
    const TYPE_NULL_STRING = 103;
    const TYPE_NULL_BOOL = 104;
    const TYPE_NULL_ARRAY = 105;
    const TYPE_NULL_DATETIME = 106;
    const TYPE_NULL_TEXT = 107;
    const TYPE_NULL_ENUM = 108;
    const TYPE_NULL_BLOB = 109;
    const TYPE_NULL_FLOAT = 110;
    const TYPE_NULL_POINT = 200;
    const TYPE_NULL_MULTIPOINT = 201;
    const TYPE_NULL_LINESTRING = 202;
    const TYPE_NULL_MULTILINESTRING = 203;
    const TYPE_NULL_POLYGON = 204;
    const TYPE_NULL_MULTIPOLYGON = 205;
    const TYPE_NULL_GEOMETRYCOLLECTION = 206;

    const VALIDATE_MAXSIZE = 40;
    const VALIDATE_EMAIL_LENGTH =  256;
    const VALIDATE_MAX_HOSTNAME_LENGTH =  255;
    const SXVALIDATE_MAX_HOSTNAME_ELEMENT_LENGTH = 63;
    const VALIDATE_MAX_HOSTNAME_ELEMENT_LENGTH = 255;


    /**
     * The constructor
     *
     * @param Errors object
     */
    private function __construct() {
    }


    /**
     * This function is used to publicly set
     * the ValidatorErrors class that is
     * used to build the human readable strings
     * based on the error code in the phphtmllibException
     * that was thrown.
     *
     * @param ValidatorErrors object
     */
    public static function set_error_object(ValidatorErrors $obj) {
        self::$err = $obj;
    }

    /**
     * This method has to be called at least once
     * in the life of validation.  It is at least
     * called by the Validator::error() method.
     *
     * @return ValidatorErrors object
     */
    public static function get_error_object() {
        if (is_null(self::$err)) {
            self::set_error_object(new ValidatorErrors);
        }
        return self::$err;
    }


    /**
     * This static method ensure that we
     * only have 1 instance of this object
     * at a time.
     *
     * @return Validator
     */
    public static function singleton() {
        static $obj = NULL;

        if (is_null($obj)) {
            $obj = new Validator;
        }

        return $obj;
    }

    /**
     * This function makes sure the
     * data is not empty
     *
     * @param mixed
     * @return void.
     */
    public function is_notempty($value) {
        if ( $this->array_hasempty($value) ) {
            self::error(phphtmllibException::ERR_EMPTY);
        }
    }


    /*********************/
    /* STRING functions  */
    /*********************/

    /**
     * This function checks if the given string contains
     * alphabetical characters or numbers.
     * It also checks for the allowed additional characters.
     *
     * @param string - the string to check
     * @param string - list of individual characters to allow
     *                 besides a-zA-Z
     * @param int phphtmllibException error code.
     *
     * @return void
     */
    public static function is_alphanum($str, $from = "", $err=NULL) {

        if ($err == NULL) {
            $err = phphtmllibException::STR_INVALID_ALPHANUM;
        }

        // If the given string is only white spaces, return false
        if ( ereg("^[[:space:]]*$", $str) ) {
            self::error($err);
        }

        $to = "";
        $len = strlen($from);
        for ( $i = 0; $i < $len; ++$i ) {
            $to .= "a";
        }
        $str = strtr($str, $from, $to);
        $substr = eregi_replace("[a-z0-9]+", "", $str);
        if ( !self::array_hasempty($substr) ) {
            self::error($err);
        }
    }


    /**
     * This method validates a string as containing
     * only letters and numbers
     *
     * @param string - the value to validate
     */
    public static function is_alphanumstring( $str ) {
        self::is_alphanum($str);
    }

    /**
     * This tests a string to make sure it is a
     * valid number.
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_number($value) {
        self::is_num($value, '', phphtmllibException::STR_INT_INVALID_NUMBER);
    }


    /**
     * Validate if the string matches a regex
     *
     * @param string - the regex string
     * @param string - the value to validate
     * @return void
     */
    public static function is_regex($regex, $str) {
        if (!preg_match($regex, $str)) {
            self::error(phphtmllibException::STR_INVALID_FIELD);
        }
    }



    /**
     * This method validates a string as a
     * path to a file.
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_path ($path) {
        //DOS related checks are also needed
        self::is_alphanum($path, "-_/:.,", phphtmllibException::STR_INVALID_PATH_CHARACTERS);
    }

    /**
     * This validates a string as a valid proper name.
     * The string can't be longer then VALIDATE_MAXSIZE in
     * length, and it can only contain letters and numbers
     *
     * @param string - the value to validate
     * @param int - the maximum allowable length
     *              DEFAULT : VALIDATE_MAXSIZE
     * @param string - any additional allowed characters.
     * @return void
     */
    public static function is_name ($name, $maxsize=self::VALIDATE_MAXSIZE,
                                    $additional_chars='') {
        //letters & numbers only
        self::is_alphanum($name,
                          ".- '??????????????????????????????????????????????????????????????????????????????????????????????????????????????????????".
                          $additional_chars,
                          phphtmllibException::STR_INVALID_NAME_CHARACTERS);

        // VALIDATE_MAXSIZE
        $len = strlen($name);
        if ( $len > $maxsize ) {
            self::error(phphtmllibException::STR_INVALID_LENGTH_40);
        }
    }

    /**
     * This validates a string as a valid Company name.
     * It is the same as is_name, with the exception
     * of allowing .
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_companyname($name) {
        $name = eregi_replace("[\. @\&,_]+","",$name);
        self::is_name($name);
    }

    /**
     * This method tests to see if a string value
     * is a valid 'account' name.  The string can't
     * be larger then VALIDATE_MAXSIZE, and can only
     * contain alphanum characters
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_username ($username) {

        self::is_alphanum($username, "_", phphtmllibException::STR_INVALID_LOGIN_NAME_CHARACTERS);

        // VALIDATE_MAXSIZE
        $len = strlen($username);
        if ( $len > self::VALIDATE_MAXSIZE ) {
            self::error(phphtmllibException::STR_INVALID_LOGIN_NAME_LENGTH);
        }
    }

    /**
     * This tries to validate a string as a password
     * It can't be empty and has to be less then
     * VALIDATE_MAXSIZE characters in length
     *
     * NOTE: password is case sensitive, and spaces are
     *       ignored.
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_password ($password) {
        $len = strlen($password);
        if ( $len > self::VALIDATE_MAXSIZE || $len < 6) {
            self::error(phphtmllibException::STR_INVALID_PASSWORD_LENGTH);
        }

        if (!preg_match('/^[a-z0-9\!\@\#\$\%\&]+$/iD', $password)) {
            self::error(phphtmllibException::STR_INVALID_PASSWORD_CHARACTERS);
        }
    }

    /**
     * This makes sure that 2 password strings are exactly alike.
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_confirm_password ($confirmpassword, $password) {
        //confirm pswd value must match pswd value
        if ( strcmp($password, $confirmpassword) != 0 ) {
            self::error(phphtmllibException::STR_PASSWORD_CONFIRM_NO_MATCH);
        }
    }

    /**
     * This is just a wrapper for
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_firstname($firstname) {
        self::is_name($firstname);
    }

    /**
     * This is just a wrapper for
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_lastname($lastname) {
        self::is_name($lastname);
    }

    /**
     * This validates a string as a valid zipcode
     *
     * numbers, whitespace allowed
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_zip ($zip) {
        self::is_alphanum($zip, "- ", phphtmllibException::STR_INVALID_ZIP);
    }

    /**
     * This tests a string as a valid
     * credit card expiration date.
     * You can pass in an optional date delimiter
     * string.  The default is -
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_ccexp($value, $split_by="-") {

        self::is_date_str($value, $split_by);

        $x = explode($split_by, $value);
        $year = $x[0];
        $month = $x[1];
        $day = $x[2];

        $d = explode(",",date("Y,m,d"));
        $today = $d[0] * 10000 + $d[1];
        $exp = $year * 10000 + $month;
        if ( $exp <  $today ) {
            self::error(phphtmllibException::STR_CCEXP);
        }
        if ( $year - $d[0] > 30 ) {
            self::error(phphtmllibException::STR_CCEXP_TOO_FAR);
        }
    }

    /**
     * This validates a string as a valid "country code"
     * which is a 2 alphanumerical character string
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_countrycode($value) {
        self::is_alphanum($value);

        if ( strlen($value) != 2 ) {
            self::error(phphtmllibException::STR_INVALID_FIELD);
        }
    }


    /**
     * Validate if the string is a good candidate
     * to become an Title
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_title($name) {
        self::is_alphanum($name," ");
    }





    /*********************/
    /* NUMBER functions  */
    /*********************/


    /**
     * This static method tests a value
     * to make sure it's an integer
     * and possibly within a rage of values.
     *
     * @param int $value
     * @param int $start start range
     * @param int $end ending rage value
     * @param int $size maximum size
     * @return none
     */
    public static function int($value, $start=NULL, $end=NULL, $size=NULL, $nonzero=FALSE) {
        if (!is_null($start)) {
            //looks like we want to test a range
            self::is_range($value, $size, $start, $end);
        } else {
            //test for a simple integer.
            self::is_num($value);
        }
    }

    /**
     * This function checks if the given string contains
     * numerical digit characters.
     * It also checks for the allowed additional characters.
     *
     * @param string - the string to check
     * @param string - list of individual characters to allow
     *                 besides a-zA-Z
     * @param int phphtmllibException error code
     */
    public static function is_num($str, $from = "", $err = NULL) {

        if ($err == NULL) {
            $err = phphtmllibException::INT_INVALID;
        }

        // If the given string is only white spaces, return false
        if ( ereg("^[[:space:]]*$", $str) ) {
            self::error($err);
        }

        //now do another simple check
        if ($from == '' && !is_numeric($str)) {
            self::error($err);
        }

        $to = "";
        $len = strlen($from);
        for ( $i = 0; $i < $len; ++$i ) {
            $to .= "0";
        }
        $str = strtr($str, $from, $to);
        $substr = eregi_replace("[-0-9]+", "", $str);
        if ( !self::array_hasempty($substr) ) {
            self::error($err);
        }
    }

    /**
     * is_range
     *
     * This is the range check that the can be used in checks_array.
     * Valarray should be:
     *    array('val'  => $val,
     *          'size' => $size  OPTIONAL
     *          'min'  => $min,
     *          'max'  => $max,
     *          )
     */
    public static function is_range($value, $size, $min, $max) {
        self::is_within_range($value, $size, $min, $max);
    }

    /**
     * This method makes sure a value lies within
     * a given range of values.
     * The error message can be customized by passing in
     * a customer error code
     *
     * @param mixed - the value u want to check
     * @param int - the size
     * @param mixed - the lower bound value
     * @param mixed - the upper bound value
     * @param string - the error code if any
     *
     */
    public static function is_within_range($value, $size, $start, $end, $error=FALSE) {
        try {
            self::is_num($value);
        } catch (ValidatorException $e) {
            if ($error) {
                self::error($error);
            } else {
                throw $e;
            }
        }

        if ( $size ) {
            if ( strlen($value) != $size ) {
                if ( $error ) {
                    self::error($error);
                } else {
                    self::error(phphtmllibException::INT_INVALID,
                                 "Number too large (".$size." digits max)");
                }
            }
        }

        if ( (($start != NULL) && ($value < $start)) ||
             (($end != NULL)   && ($value > $end)) ) {
            if ( $error ) {
                    self::error($error);
                } else {
                    self::error(phphtmllibException::INT_INVALID,
                                 "Value out of range (".$start."-".$end.")");
                }
        }
    }

    /**
     * Make sure this is a positive integer
     * in a range
     *
     * @param int $value
     * @return none
     */
    public static function is_positive_int_range($value, $start=NULL, $end=NULL, $size=NULL) {
        self::int($value, $start, $end, $size);

        if ($value <=0) {
            self::error(phphtmllibException::INT_NOT_POSITIVE);
        }

    }

    /**
     * Make sure this is a positive integer
     *
     * @param int $value
     * @return void
     */
    public static function is_positive_int($value) {
        self::is_positive_int_range($value);
    }

    /**
     * Make sure this is a negative integer
     * in a range
     *
     * @param int $value
     * @return void
     */
    public static function is_negative_int_range($value, $start=NULL, $end=NULL, $size=NULL) {
        self::int($value, $start, $end, $size);

        if ($value >=0) {
            self::error(phphtmllibException::INT_NOT_NEGATIVE);
        }
    }

    /**
     * Make sure this is a negative integer
     *
     * @param int $value
     * @return void
     */
    public static function is_negative_int($value) {
        self::is_negative_int_range($value);
    }

    /**
     * This static method tests a value
     * to make sure it is a numeric
     * database id/sequence
     *
     * @param int $value
     * @return void
     */
    public static function is_db_id($value) {
        if (!ctype_digit($value) || $value<0) {
            self::error(phphtmllibException::INT_INVALID_DB_ID);
        }
    }


    /**
     * This method tests a string to make sure it is
     * in a valid money format.
     * either $x or $x.cents
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_money($money) {

        try {
            self::is_num($money, ".");
        } catch (phphtmllibException $e) {
            self::error(phphtmllibException::INT_INVALID_MONEY);
        }

        // Check for dollar.cent pattern
        if ( ereg("^[0-9]*\.[0-9][0-9]?$", $money) ) {
            return TRUE;
        }

        // Or It can be just dollars
        if ( ereg("^[0-9]+$", $money) ) {
            return TRUE;
        }

        self::error(phphtmllibException::INT_INVALID_MONEY);
    }

    /**
     * This method tries to validate a string as
     * a valid price.  It can't be zero (a la free!)
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_price($price) {
        self::is_money($price);

        // Should be more than just 0s and .s
        if ( ereg("^0*\.*0*$", $price) ) {
            self::error(phphtmllibException::INT_INVALID_MONEY);
        }

    }

    /**
     * This method validates a string as a valid
     * float formatted number.  x.xx
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_float($number) {

        try {
            self::is_num($number, ".");
        } catch (ValidatorException $e) {
            self::error(phphtmllibException::INT_INVALID_FLOAT);
        }

        // Number of the form x.y
        if ( ereg("^[0-9]*\.[0-9]+$", $number) ) {
            return TRUE;
        }

        // Number of the form x
        if ( ereg("^[0-9]+$", $number) ) {
            return TRUE;
        }

        self::error(phphtmllibException::INT_INVALID_FLOAT);
    }


    /**
     * This validates a string as a valid number
     * between 0 and 100
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_zero_onehundred($value) {

        try {
            self::is_num($value);
        } catch (ValidatorException $e) {
            self::error(phphtmllibException::INT_INVALID);
        }

        if ( !($value > 0 && $value <= 100) ) {
            self::error("INVALID_ZERO_HUNDRED_NUMBER");
        }

    }


    /**
     * This method validates a string as a number
     * greater then 0.
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_higherzeronumber($value) {
        self::positive_int($value);
    }


    /**
     * This method validates a string against the
     * 'datetime' format
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_datetime( $value ) {
        If (!preg_match('{\d\d\d\d-[01]\d-[0-3]\d [012]\d:[0-5]\d:[0-5]\d}', $value)) {
            self::error(phphtmllibException::STR_INVALID_DATETIME);
            // ok
        }
    }


    /**
     * This function performs validation
     * of a parameter based on its type
     *
     * @todo Implement TYPE_DATETIME validation (and any other missing types)
     *
     * @param mixed $value
     * @param int $type
     */
    public static function type($value, $type, $size = 0) {

        $failed = false;
        switch ($type) {

            case self::TYPE_ID:
                // has to be int and greater than 0
                if (!ctype_digit($value) || $value<0) {
                    $failed = true;
                }
                break;

            case self::TYPE_INT:
                // has to be an int
                if (!ctype_digit($value) && $value) {
                    $failed = !((is_string($value) || is_int($value)) &&
                                ctype_digit((string) $value));
                }
                break;

            case self::TYPE_FLOAT:
                // has to be a number; scientific notation is OK but hex (0xFF) is NOT ok.
                $failed = !(is_numeric($value) && !preg_match('/0x[0-9a-f][0-9a-f]/i', $value));
                break;

            case self::TYPE_CHAR:
                // has to be a single byte char
                if (strlen($value) > $size) {
                    $failed = true;
                }
                break;

            case self::TYPE_STRING:
            case self::TYPE_BLOB:
            case self::TYPE_TEXT:
                $failed = !is_string($value);
                break;

            case self::TYPE_BOOL:
                // has to be 0 or 1
                if ($value != 1 && $value != 0) {
                    $failed = true;
                }
                break;

            case self::TYPE_ENUM:
                break;

            case self::TYPE_ARRAY:
                // has to be an array
                if (!is_array($value)) {
                    $failed = true;
                }
                break;

            case self::TYPE_DATETIME:
                // REQUIRES IMPLEMENTATION!
                break;

            case self::TYPE_NULL_INT:
                // if not null, has to be an int
                if (!is_null($value) && !ctype_digit($value) && $value) {
                    $failed = !((is_string($value) || is_int($value)) &&
                                ctype_digit((string) $value));
                }
                break;

            case self::TYPE_NULL_FLOAT:
                // if not null, has to be a number; scientific notation is OK but hex (0xFF) is NOT ok.
                $failed = !(is_null($value) || (is_numeric($value) && !preg_match('/0x[0-9a-f][0-9a-f]/i', $value)));
                break;

            case self::TYPE_NULL_CHAR:
                // has to be a single byte char
                if (!is_null($value) && strlen($value) > $size) {
                    $failed = true;
                }
                break;

            case self::TYPE_NULL_STRING:
            case self::TYPE_NULL_BLOB:
            case self::TYPE_NULL_TEXT:
                $failed = (!is_null($value) && !is_string($value));
                break;

            case self::TYPE_NULL_BOOL:
                // has to be 0 or 1
                if (!is_null($value) && $value != 1 && $value != 0) {
                    $failed = true;
                }
                break;

            case self::TYPE_NULL_ENUM:
                break;

            case self::TYPE_NULL_ARRAY:
                // has to be an array
                if (!is_null($value) && !is_array($value)) {
                    $failed = true;
                }
                break;

            case self::TYPE_NULL_DATETIME:
                // REQUIRES IMPLEMENTATION!
                break;

        default:
            self::error(phphtmllibException::INVALID_TYPE,
                        'Unknown validation type ' . $type);
            break;
        }

        if ($failed) {
            self::error(phphtmllibException::INVALID_TYPE,
                        'Validation failed: ' . $value . ' of type ' . $type . ', size ' . $size);
        }
        else {
            return true;
        }
    }




    /************/
    /* INTERNAL */
    /************/

    /**
     * A wrapper method to set the error message and
     * error code before throwing a phphtmllibException.
     *
     * @param int $code the error code
     * @param string $message the customized error message
     * @param string $label optional
     * @param array $args number index of replacement values in error message
     *              array(1 => "15 max characters", 2 => "10 allowed");
     * @return void
     */
    public static final function error($code, $message=NULL, $label=NULL, $args=NULL) {
        if ($message == NULL) {
            $message = self::singleton()->get_error_object()->get_error_msg($code, $args);
        }
        throw new ValidatorException($message, $code, $label);
    }


    /**
     * This method checks to make sure an array doesn't have
     * an empty element.
     *
     */
    public static function array_hasempty($a) {
        if ( is_array($a) ) {
            foreach ( $a as $key => $value ) {
                if ( $value == '' ) {
                    return TRUE;
                }
            }
            return FALSE;
        } else {
            return $a == '';
        }
    }

}

?>
