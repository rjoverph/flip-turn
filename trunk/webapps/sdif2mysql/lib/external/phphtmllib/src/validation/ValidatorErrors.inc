<?php
/**
 * This class is the parent Error code to
 * string lookup class.  It's used for
 * mapping ValidatorException errors to
 * readable strings.
 *
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Validation
 */
class ValidatorErrors {
    /**
     * error array from the FormValidation
     * class.
     */
    public $error_array = array(
         ValidatorException::ERR_OK => 0,
         ValidatorException::ERR_EMPTY => "This field cannot be empty",

         //string based
         ValidatorException::STR_INVALID_ALPHANUM => "This field may contain only numbers and letters.",
         ValidatorException::STR_INVALID_FIELD => "This field's value is invalid.",
         ValidatorException::STR_INVALID_WHITESPACE => "This field only contains whitespace.",
         ValidatorException::STR_INVALID_LENGTH => "Entry has exceeded allowed length.",
         ValidatorException::STR_INT_INVALID_NUMBER => "This field must contain a valid number.",
         ValidatorException::STR_INVALID_IP => "The IP address you have entered is not in a valid format",
         ValidatorException::STR_INVALID_PATH_CHARACTERS => "The path field may contain only letters and numbers.",
         ValidatorException::STR_INVALID_NAME_CHARACTERS => "The name may contain only letters and numbers.",
         ValidatorException::STR_INVALID_LENGTH_40 => "This field must not exceed 40 characters in length.",
         ValidatorException::STR_INVALID_LOGIN_NAME_CHARACTERS  => "The User Name field may contain only letters and numbers.",
         ValidatorException::STR_INVALID_LOGIN_NAME_LENGTH => "The User Name must be less than 40 characters.",
         ValidatorException::STR_INVALID_PASSWORD_LENGTH => "The Password should be between 6 and 40 characters long.",
         ValidatorException::STR_PASSWORD_CONFIRM_NO_MATCH => "The password and confirmation password you have typed do not match. Please try again.",
         ValidatorException::STR_INVALID_EMAIL => "The email address is not properly formatted.",
         ValidatorException::STR_INVALID_EMAIL_MISSING_BRACKETS => "The long form email address must contain the < > characters, such as \"Foo Bar &lt;foo@bar.com&gt;\".",
         ValidatorException::STR_INVALID_LENGTH_256 => "This field must not exceed 256 characters in length.",
         ValidatorException::STR_NOT_LEAPYEAR => "The year is not a leapyear",
         ValidatorException::STR_INVALID_MONTH => "You have entered an invalid month.",
         ValidatorException::STR_INVALID_DAY => "You have entered an invalid day.",
         ValidatorException::STR_INVALID_DATETIME => "You have entered an invalid datetime format.",
         ValidatorException::STR_INVALID_YEAR => "You have entered an invalid year.",
         ValidatorException::STR_INVALID_DATE => "Invalid Date.",
         ValidatorException::STR_INVALID_ZIP => "Invalid zip code",
         ValidatorException::STR_CCEXP => "Credit card expired already",
         ValidatorException::STR_CCEXP_TOO_FAR => "Credit card expires in more than 30 years?",
         ValidatorException::STR_INVALID_URL => "URL must be in the form of http[s]://hostip [:port number] [path]",
         ValidatorException::STR_INVALID_DOMAIN_NAME => "This domain name you have entered is not valid.",
         ValidatorException::STR_INVALID_HOST_NAME => "The host name is invalid.",
         ValidatorException::STR_INVALID_STANDALONE_HOST_NAME => "You have entered an invalid host name. Please enter a Hostname without the domainname.",
         ValidatorException::STR_EMPTY_UPLOAD_FILE => "The uploaded file was unexpectedly empty.",
         ValidatorException::STR_FILE_MAX_SIZE => "The uploaded file exceeds the maximum file size of %1 bytes.",
         ValidatorException::STR_FILE_PARTIAL_UPLOAD => "The uploaded file was only partially uploaded.",
         ValidatorException::STR_FILE_MISSING => "No file was uploaded.",
         ValidatorException::STR_FILE_TYPE_INVALID => "Not a valid file type.",
         ValidatorException::STR_INVALID_HOST_WITH_PORT => "This field cannot be empty, if the Port is filled out",
         ValidatorException::STR_INVALID_HEX_COLOR => "Color values must start with a #, then 6 hexedecimal digits. ex. #FF00FF",




         //Integer based
         ValidatorException::INT_INVALID => "This field must contain a valid number.",
         ValidatorException::INT_INVALID_MONEY => "This must be a valid amount in dollars and cents.",
         ValidatorException::INT_INVALID_PRICE => "Price must be a valid, non-zero amount in dollars and cents.",
         ValidatorException::INT_INVALID_FLOAT => "This must be a valid floating point number.",
         ValidatorException::INT_INVALID_ZERO_HUNDRED_NUMBER => "This number must be between 0 and 100.",
         ValidatorException::INT_INVALID_HOUR => "You have entered an invalid hour.",
         ValidatorException::INT_INVALID_MINUTES => "You have entered invalid mintues.",
         ValidatorException::INT_INVALID_SECONDS => "You have entered invalid seconds.",
         ValidatorException::INT_INVALID_PORT_NUM => "The port number is invalid.",
         ValidatorException::INT_NOT_POSITIVE => "Not a positive integer",
         ValidatorException::INT_NOT_NEGATIVE => "Not a negative Integer",
         ValidatorException::INT_INVALID_DB_ID => "Not a valid database sequence ID",

         //MISC
         ValidatorException::STR_INVALID_LOGIN_NAME_EMPTY => "The User Name field must not be blank.",
         ValidatorException::STR_INVALID_PASSWORD_EMPTY => "The Password field must not be blank.",
         ValidatorException::STR_INVALID_PASSWORD_CHARACTERS => "The Password field contains invalid characters",
         ValidatorException::STR_INVALID_PATH_LENGTH => "The path field does not meet the requirements. It must be less than 40 characters.",
         ValidatorException::STR_INVALID_PATH_EMPTY => "The path field must not be blank.",
         ValidatorException::STR_INVALID_LENGTH_N => "This field must not exceed %1 characters in length.  The character count is %2",
         ValidatorException::STR_INVALID_NAME_EMPTY => "The name must not be empty.",
         ValidatorException::STR_INVALID_IP_EMPTY => "The IP Address must not be empty.",
         ValidatorException::STR_INVALID_EMAIL_EMPTY => "The email address can not be empty.",
         ValidatorException::STR_INVALID_PHONE => "The phone number you have entered is not properly formatted.",
         ValidatorException::STR_INVALID_STATE => "You must specify a 2 letter state code (ie. 'CA' for California).",
         ValidatorException::STR_INVALID_TIME_FORMAT => "You have entred an invalid date/time format.",

         ValidatorException::INT_ONLY_DIGITS => "Only numeric digits are allowed in this field.",
         ValidatorException::INT_INVALID_LEAP_DAY => "The year you have entered is not a leap year. February only has 28 days.",
         ValidatorException::INT_INVALID_30_DAY => "There are only 30 days in this month.",
         ValidatorException::INT_INVALID_YEAR_DATE_1990_3000 => "The year must be between 1990 and 3000",
         ValidatorException::INT_NOT_IN_RANGE => "Value not in range.",
         );

    /**
     * This returns the appropriate error message
     * based on the error #.
     *
     * @param string - the error code
     * @return string - the error string.
     *
     */
    function get_error_msg($err, $args=NULL) {
        $str = $this->error_array[$err];
        if (is_array($args)) {
            $count = count($args);
            for($i=1; $i<=$count; $i++) {
                $str = str_replace("%$i", $args[$i-1], $str);
            }
        }

        return $str;

    }
}

?>
