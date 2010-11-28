<?php
/**
 * This file contains the base
 * Exception class for the 
 * Daemon object.
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Controller
 */


/**
 * This class is the Exception container
 * for the Daemon class.
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Controller
 */
class DaemonException extends phphtmllibException {

    const ERR_ALREADY_RUNNING = 1;
    const ERR_CANT_FORK = 2;
    const ERR_SETSID_FAILED = 3;
    const ERR_SET_IDENTITY = 4;
    const ERR_PID_FILE_ERROR = 5;

    const ERR_NOT_RUNNING = 6;
    const ERR_CANT_KILL = 7;


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
     * This abstract method is used
     * to return the extra info as a string
     *
     * @return string
     */
    public function get_extra_as_string() {
        return $this->extra;
    }
}
?>
