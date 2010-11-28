<?php
/**
 * This file contains the FEDateListBox class
 *
 * $Id: FEDateListBox.inc 2399 2007-02-22 21:38:46Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * This class builds a widget that shows a group of select boxes (FEYearsListBox, FEMonthsListBox, FEDaysListBox) representing a date.
 *
 * FEDate will display three drop down lists representing a date.  You can set
 * the order in which these elements are displayed and the minimum and maximum
 * years displayed.
 *
 * Like in FEMonths you should use the built in php {@link http://www.php.net/manual/en/function.setlocale.php setlocale}
 * function to affect the language used for the month list.
 *
 * Example as it would appear in FormContent::form_init_elements():
 * <code>
 *      // set the locale to dutch
 *      setlocale(LC_TIME, 'nl_NL');
 *      $date_element = new FEDate("FEDate label", false, null, null, 'Fdy', 1970, 1975);
 * </code>
 *
 * the $format parameter conforms the the php {@link http://www.php.net/manual/en/function.setlocale.php date} function
 * format argument specification (for years, months and days only).
 *
 * @author Culley Harrelson <culley@fastmail.fm>
 * @author Suren Markosian <suren@emicron.net>
 * @see FEMonthsListBox
 * @see FEDaysListBox
 * @see FEYearsListBox
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 */
class FEDateListBox extends FEBoxElement {

    /**
     * The earliest year shown in the year list.
     */
    protected $_min_year;

    /**
     * The latest year shown in the year list.
     */
    protected $_max_year;

    /**
     * The order in which to show the elements.  This variable must be 3
     * characters long and contain only one m only one d and only one y.
     *
     */
    protected $_format = 'mdy';

    /**
     * A printf style format string used to add punctuation to the confirmation
     * display.  Defaults to space separated.  The placeholders are filled
     * according to the order set in $_format
     *
     */
    protected $_text_format = '%s %s %s';

    /**
     * The year form element
     *
     */
    protected $_year;

    /**
     * The month form element
     *
     */
    protected $_month;

    /**
     * The day form element
     *
     */
    protected $_day;

    /**
     * The constructor
     *
     * @param string text label for the element
     * @param boolean is this a required element?
     * @param int element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int element height in px
     * @param string date format string.  M m F Y y d D are valid. 3 characters max.
     * @param int min value for year drop down list
     * @param int max value for year drop down list
     * @see FEDate for an example
     * @todo we need to blow up somehow if the format string is bogus
     *
     */

    function __construct($label, $required = TRUE, $width = NULL, $height = NULL,
                         $format = 'mdy', $min_year = 2000, $max_year = 2010) {

        $this->_set_format($format);
        $this->_min_year = $min_year;
        $this->_max_year = $max_year;


        //call the parent constructor first
        //so the element_name is built.
        parent::__construct($label, $required, $width, $height);

        //now create the child elements.
        $this->_year = new FEYearsListBox($this->_element_name . '_years', $required, null, null, $min_year, $max_year);
        $this->_month = new FEMonthsListBox($this->_element_name . '_months', $required, null, null, preg_replace('/[dy]/i', '', $this->_format));
        $this->_day = new FEDaysListBox($this->_element_name . '_days', $required, null, null);
    }

    /**
     * We need to override this so we get
     * the form name set in the child elements
     * so the id attributes are set correctly.
     */
    function set_form_name($name) {
        $this->_form_name = $name;
        $this->_year->set_form_name($name);
        $this->_month->set_form_name($name);
        $this->_day->set_form_name($name);
    }

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    public function get_element() {

        $container = Container::factory();

        // add the elements in the order specified.
        $chars = preg_split('//', $this->_format, -1, PREG_SPLIT_NO_EMPTY);
        foreach ($chars as $char) {
            switch ($char) {
            case 'y':
                $container->add($this->_year->get_element());
                break;
            case 'm':
            case 'F':
                $container->add($this->_month->get_element());
                break;
            case 'd':
                $container->add($this->_day->get_element());
                break;
            }
        }

        return $container;
    }

    /**
     * This function will return the elements value as an array or month, day and year
     *
     * @return array
     */
    public function get_value() {
        $value= array("day"=>$this->_day->get_value(),
                      "month"=>$this->_month->get_value(),
                      "year"=>$this->_year->get_value());

        return $value;


    }

    /**
     * Set the value of the element
     *
     * This function sets the default values for the date element  The
     * parameter should be a string representation of the date in ISO 8601
     * format.
     *
     * @param string
    */
    public function set_value($value) {
        if ($value) {
            if (is_array($value)) {
                $this->_year->set_value($value['year']);
                $this->_month->set_value($value['month']);
                $this->_day->set_value($value['day']);
            } else {
                $date_parts = explode('-', $value);
                $this->_year->set_value($date_parts[0]);
                $this->_month->set_value($date_parts[1]);
                $this->_day->set_value($date_parts[2]);
            }
        }


    }

    /**
     * This returns a formatted string used for the confirmation display (and possibly elsewhere)
     *
     * @return string
     */
    public function get_value_text() {

        // loop through the characters in $_format to properly set the placeholders
        // determined in $_text_format
        $chars = preg_split('//', $this->_format, -1, PREG_SPLIT_NO_EMPTY);
        $i = 1;
        foreach ($chars as $char) {

            switch ($char) {
            case 'y':
                $value = $this->_year->get_value_text();
                break;
            case 'm':
            case 'F':
                $value = $this->_month->get_value_text();
                break;
            case 'd':
                $value = $this->_day->get_value_text();
                break;
            }

            switch ($i) {
            case 1:
                $one = $value;
                break;
            case 2:
                $two = $value;
                break;
            case 3:
                $three = $value;
                break;
            }

            $i++;
        }

        return sprintf($this->_text_format, $one, $two, $three);
    }

    /**
     *
     * This function is responsible for performing complete
     * validation and setting the appropriate error message
     * in case of a failed validation
     *
     * @return void
     */
    public function validate() {
        $value = $this->get_value();

        DateValidator::is_date($value['month'], $value['day'], $value['year']);
    }

    /**
     * this method sets the display order for the elements in the widget
     *
     * @param string
     * @return bool success or failure
     */
    private function _set_format($format) {

        // must be 2 or 3 characters
        if (strlen($format) != 3) {
            return FALSE;
        }

        // month can be represented by F m or M
        if (strstr($format, 'F')) {
            $month = 'f';
        } else {
            $month = 'm';
        }

        // compare the characters sent with the characters needed.  only set
        // the property if one of each is present
        $search_for = array ('y', $month, 'd');
        $chars = preg_split('//', strtolower($format), -1, PREG_SPLIT_NO_EMPTY);

        if (count(array_diff($search_for, $chars)) > 0) {
            return FALSE;
        }

        $this->_format = $format;
        return TRUE;


    }

    /**
     * Set the text format for confirmation
     *
     * this method sets the format string used in get_value_text().  Use this
     * method to set special punctuation for the confirmation display.  It is
     * fed through sprintf
     *
     * Examples:
     * <code>
     *  $date_element->set_text_format("%s %s, %s");
     *  $date_element->set_text_format("%04d-%02d-%02d");
     * </code>
     *
     * @param string
     * @link http://www.php.net/manual/en/function.sprintf.php
     *
     */
    public function set_text_format($format) {
        $this->_text_format = $format;
    }

    /**
     * This method returns the hidden version of this element for a confirmation page.
     *
     * NOTE: This is called by the FormProcessor only.
     * It shouldn't be called manually.
     *
     * @return container
     */
    public function get_confirm_element() {
        $element_name = $this->get_element_name();

        $c = Container::factory();
        $c->add(form_hidden($this->_year->get_element_name(), $this->_year->get_value()));
        $c->add(form_hidden($this->_month->get_element_name(), $this->_month->get_value()));
        $c->add(form_hidden($this->_day->get_element_name(), $this->_day->get_value()));
        return $c;
    }


    /**
     * Sets the disabled element flag
     *
     * @param bool disabled
     */
    public function set_disabled($flag) {
        $this->_is_disabled = $flag;
        $this->_year->set_disabled($flag);
        $this->_month->set_disabled($flag);
        $this->_day->set_disabled($flag);
    }

}

?>