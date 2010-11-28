<?php
/**
 * This file contains the
 * DataBaseException object
 * for inspecting why a
 * DataBase operation failed.
 *
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage DataBase
 */


/**
 * This phphtmllibException child class
 * is used for inspecting why a query or
 * DataBase operation has failed.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage DataBase
 */

class DataBaseException extends phphtmllibException {
    /**
     * modified constructor to allow us to pass in
     * the sql query (if any) and bind vars (if any)
     *
     * @param string $message
     * @param int $code
     * @param string $sql
     * @param array $bind_vars
     */
    public function __construct($message, $code=0,
                                 $sql='', $bind_vars=array()) {
        $this->extra['sql'] = $sql;
        $this->extra['bind_vars'] = $bind_vars;
        parent::__construct($message,$code);
    }


    /**
     * Return the string version of the 'extra' information
     * about this Exception
     *
     * @return string
     */
    public function get_extra_as_string() {
        $str = "SQL = '".$this->extra['sql']."'\n";
        $str .= "Bind Vars = \n".var_export($this->extra['bind_vars'], TRUE);
        return $str;
    }
}

?>
