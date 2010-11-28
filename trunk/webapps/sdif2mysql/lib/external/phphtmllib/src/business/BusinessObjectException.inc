<?php
/**
 * This is the BusinessObjectException class' file.
 *
 * @author Walter A. Boring IV
 * @see BusinessObject
 * @package phpHtmlLib-framework
 * @subpackage Business
 */

/**
 * For now just a placeholder until we have a better use
 * for this class.
 *
 * @author Walter A. Boring IV
 * @see BusinessObject
 * @package phpHtmlLib-framework
 * @subpackage Business
 */
class BusinessObjectException extends phphtmllibException {
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