<?php
/**
 * DateValidator class used to validate
 * date and time data fields in our application
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Validation
 */


/**
 * This child of Validator is responsible for
 * containing the methods related to date and time.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Validation
 */
class DateValidator extends Validator {

    /**
     * This method validates a string as a
     * leap year.
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_leapyear($yyyy) {
        if (!($yyyy%4 == 0 && ($yyyy%100 != 0 || $yyyy%400 == 0))) {
            self::error(phphtmllibException::STR_NOT_LEAPYEAR);
        }
    }


    /**
     * This validates a atring as a valid date format
     * You can provide a seperator string that seperates
     * the fields
     *
     * NOTE: date is in YYYY-MO-DY format
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_date_str($value, $split_by="-") {

        $x = explode($split_by, $value);
        $year = $x[0];
        $month = $x[1];
        $day = $x[2];

        self::is_date($month, $day, $year);
    }

    /**
     * This validates a atring as a valid date format
     * You can provide a seperator string that seperates
     * the fields
     *
     * @param string $month
     * @param string $day
     * @param string $year
     * @return void
     */
    public static function is_date($month, $day, $year) {
        self::is_datemonth($month);
        self::is_dateday($day);
        self::is_dateyear($year);

        // Check the overall validity of the date
        if ( !checkdate($month, $day, $year) ) {
            self::error(phphtmllibException::STR_INVALID_DATE);
        }
    }

    /**
     * This validates a string as a valid day of a month
     * It has to be greater then 0 and less then 31
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    public static function is_dateday($day) {
        self::is_within_range($day, 0, 1, 31, phphtmllibException::STR_INVALID_DAY);
    }

    /**
     * This validates a string as a valid month of the year
     * between 1 and 12 inclusive
     * is_datemonth - checks whether its a proper month
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_datemonth($month) {
        self::is_within_range($month, 0, 1, 12, phphtmllibException::STR_INVALID_MONTH);
    }

    /**
     * See if the year is within
     * 1800 and 3000
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_dateyear($year) {
        self::is_within_range($year, 0, 1800, 3000, phphtmllibException::STR_INVALID_YEAR);
    }

    /**
     * This validates an array of values as a
     * valid date time
     *
     * NOTE: array must contain
     *       array(
     *             "month" => VALUE,
     *             "day" => VALUE,
     *             "year" => VALUE,
     *             "hour" => VALUE,
     *             "minutes" => VALUE,
     *             "seconds" => VALUE);
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_datetime($value) {
        $month=$value["month"];
        $day=$value["day"];
        $year=$value["year"];

        $time[hour]=$value["hour"];
        $time[minutes]=$value["minutes"];
        $time[seconds]=$value["seconds"];

        $date = $year."-".$month."-".$day;
        self::is_date_str($date);
        self::is_time($time);
    }

    /**
     * This validates an array of fields as a
     * valid time of the day
     *
     * NOTE: array must contain
     *       array(
     *             "hour" => VALUE,
     *             "minutes" => VALUE,
     *             "seconds" => VALUE);
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_time($value) {

        $hour=$value["hour"];
        $minutes=$value["minutes"];
        $seconds=$value["seconds"];

        self::is_within_range($hour, 0, 0, 23, phphtmllibException::INT_INVALID_HOUR);
        self::is_within_range($minutes, 0, 0, 59, phphtmllibException::INT_INVALID_MINUTES);
        self::is_within_range($seconds, 0, 0, 59, phphtmllibException::INT_INVALID_SECONDS);
    }
}
?>
