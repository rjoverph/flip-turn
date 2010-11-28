<?php
/**
 * DataObjectException
 * 
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Data
 */


/**
 * This is an exception
 * child class
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Data
 */
class DataObjectException extends phphtmllibException {

    /**
     * This abstract method is used
     * to return the extra info as a string
     *
     * @return string
     */
    public final function get_extra_as_string() {
        return NULL;
    }

}

?>