<?php
/**
 * This is a cache exception
 * class
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Cache
 */

/**
 * This is the exception thrown by all
 * cache classes.
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Cache
 */
class CacheException extends phphtmllibException {

    /**
     * Holds the cache type
     *
     * @var unknown_type
     */
    private $type;

    /**
     * This abstract method is used
     * to return the extra info as a string
     *
     * @return string
     */
    public final function get_extra_as_string() {
        return $this->type;
    }

}

?>
