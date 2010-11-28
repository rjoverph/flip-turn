<?php
/**
 * This file contains the FEHostNameWithPort class
 *
 * $Id: FEHostNameWithPort.inc 1823 2006-08-04 21:17:44Z hemna $
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
 * This is the DomainName FormElement which builds a
 * text input field. It also includes a port #
 * It validates as is_domainname().
 *
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEHostNameWithPort extends FEText {

    /**
     * flag to tell us to seperate the port
     * value into it's own field
     */
    protected $_seperate_port_flag = FALSE;

    /**
     * The constructor
     *
     * @param label string - text label for the element
     * @param bool required - is this a required element
     * @param int required - element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int required - maximum number of chars allowed to type in
     * @param bool optional - seperate the port value into it's own textarea field
     */
    function __construct($label, $required = TRUE, $width = NULL, $maxlength = NULL,
                                  $seperate_port=FALSE) {

        parent::__construct($label, $required, $width, $maxlength);
        $this->_seperate_port_flag = $seperate_port;
    }

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    public function get_element() {
        $host_attributes = $this->build_element_attributes();
        $host_attributes["type"] = "text";

        $element_name = $this->get_element_name();
        $host_value = $this->get_value();

        if ($this->_seperate_port_flag) {
            $host_attributes["name"] = $element_name."[0]";
            if ($host_value != NULL && !is_array($host_value)) {
                $host_value = explode(":", $host_value );
                $host_attributes["value"] = $host_value[0];
            } else if (is_array($host_value)) {
                $host_attributes["value"] = $host_value[0];
            }

            $port_attributes = $host_attributes;
            $port_attributes["name"] = $element_name."[1]";
            $port_attributes["size"] = 10;
            $port_attributes["maxlenght"] = 5;
            if (@array_key_exists("0", $host_value)) {
                $port_attributes["value"] = $host_value[1];
            }

            $port_label = html_span("formlabel", "Port");
            if ($this->has_error("Port")) {
                $port_label->set_tag_attribute("style","color:red;");
            }

            return Container::factory( new INPUTtag($host_attributes),
                              $port_label,
                              new INPUTtag($port_attributes));
        } else {
            if ($host_value != NULL) {
                $host_attributes["value"] = $host_value;
            }
            return new INPUTtag($host_attributes);
        }
    }

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_domainname().
     * 
     * @return void
     */
    public function validate() {
        $value = $this->get_value();
        if (!is_array($value)) {
            $value = explode(":", $value);
        }

        $valid = $this->_validate_hostname($value[0]);

        //now validate the port
        if ($value[1] != NULL) {
            try {
                Validator::is_number($value[1]);
            } catch (ValidatorException $e) {
                if ($this->_seperate_port_flag) {
                    $port = "Port";
                } else {
                    $port = NULL;
                }
                Validator::error(ValidatorException::INT_INVALID_PORT_NUM, NULL, $port);
            }
            
            //make sure the hostname isn't null
            if ($value[0] == NULL) {
                //we have an error here because
                //they entered a port w/o a hostname
                Validator::error(ValidatorException::STR_INVALID_HOST_WITH_PORT);
            }
        }
    }


    /**
     * this validates the hostname field only
     *
     * @return bool TRUE = valid
     */
    protected function _validate_hostname($value) {
        NetworkValidator::is_hostname($value);
    }
}

?>