<?php
/**
 * This builds the NoCache object.
 * 
 * @author Walter A. Boring IV
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Cache
 */


/**
 * This NoCache class does
 * not do any caching whatsoever
 *
 * This is to be used when caching is disabled
 * system wide or in some instances
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Cache
 */
class NoCache extends Cache {

    /**
     * Holds instance of the class
     *
     * @var object
     */
    static private $instance = null;

    /**
     * Singleton function that returns
     * the global class object
     *
     * @return NoCache
     */
    public static function singleton() {
        if (!self::$instance) {
            self::$instance = new NoCache();
        }

        return self::$instance;
    }

    /**
     * This function does nothing
     *
     * @param string $key
     * @param string $data
     * @param int $lifetime (0 for never expires)
     * @param array $parameters an array of specific parameters
     *                          can be passed to child objects
     */
    protected function set_data($key, $data, $lifetime = 0, $parameters = null) {
    }
    
    /**
     * This function always returns false
     * since we are not caching anything
     *
     * @param string $key
     * @param int $value
     * 
     * @return bool
     */
    protected function increment_data($key, $value = 1) {
        return false;
    }

    /**
     * This function always returns false
     * since we are not caching anything
     *
     * @param string $key
     *
     * @return bool
     */
    protected function get_data($key) {
        return false;
    }

    /**
     * This function does nothing
     *
     * @param string $key
     */
    protected function delete_data($key) {
    }
}

?>