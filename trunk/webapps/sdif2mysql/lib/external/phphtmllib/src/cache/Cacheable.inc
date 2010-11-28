<?php
/**
 * The Cacheable interface file.
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Cache
 */

/**
 * This interface defines API for classes
 * to implement caching capability
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Cache
 */
interface Cacheable {

    /**
     * This function should construct and
     * return a string key to be used to
     * uniquely identify an object/data
     * in the cache
     *
     * @return string
     */
    public function get_cache_key();

    /**
     * This function should return cache
     * lifetime in seconds
     *
     * @return int
     */
    public function get_cache_lifetime();

    /**
     * This method should return if caching
     * is enabled or not
     *
     * @return boolean
     */
    public function is_cacheable();
}

?>