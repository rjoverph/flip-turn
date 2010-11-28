<?php
/**
 * This is the base abstact class for
 * cache management
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Cache
 */

/**
 * This is the base Cache class.
 *
 * This class defines API used by all
 * cache classes in the framework
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Cache
 */
abstract class Cache {

    /**
     * Whether we want to enable cache
     * globally
     *
     * @var bool
     */
    public static $cache_enabled = true;

    /**
     * Default cache lifetime in seconds for
     * this cache object
     *
     * @var int
     */
    protected $default_cache_lifetime = 0;

    /**
     * A private constructor
     * Neither this class nor its childs are
     * supposed to be instantiated directly,
     * only via a singleton
     *
     */
    protected function __construct() {
        // make sure we init the
        // cache system (if needed)
        $this->init_cache();
    }

    /**
     * This function will return a data
     * from the cache or false if no data
     * was found or cache is disabled.
     * It relies on childs implementation of
     * get_data() function
     *
     * @param string $key
     * @return bool
     */
    public final function get($key) {
        return $this->get_data($this->make_key($key));
    }

    /**
     * This function will store data
     * in the cache if caching is enabled
     *
     * It relies on childs implementation of
     * set_data() function which can throw a
     * CacheException if something goes bad
     *
     * @throws CacheException
     *
     * @param string $key
     * @param string $data
     * @param int $lifetime (0 for never expires)
     * @param array $parameters an array of specific parameters
     *                          can be passed to child objects
     */
    public final function set($key, $data, $lifetime = 0, $parameters = null) {
        $this->set_data($this->make_key($key),
                        $data,
                        $lifetime,
                        $parameters);
    }
    
    /**
     * This function will increment the
     * key by $value (default 1). If the key does
     * not exist, it will NOT be created. If the
     * current value is not numeric and cannot be converted
     * to a number, it will be set to $value.
     *
     * @param string $key
     * @param int $value Amount to increment by (default 1)
     * 
     * @return mixed The new item's value, or FALSE on failure
     */
    public final function increment($key, $value = 1) {
        $this->increment_data($this->make_key($key), $value);
    }

    /**
     * Abstact implementation of cache
     * deletion based on the provided
     * key
     *
     * This function can either delete the cache
     * entry or invalidate it depending on
     * the implementation
     *
     * @param string $key
     */
    public final function delete($key) {
        $this->delete_data($this->make_key($key));
    }

    /**
     * This function is used to transform the
     * key if neccessary (generate a key based on
     * the original provided key).
     *
     * This function also makes sure that the
     * cache key passed is valid. It gets
     * called before set/get/delete operation
     * is executed.
     *
     * Should throw a ValidatorException if key is bad.
     *
     * @param string $key
     * @return string
     *
     * @throws CacheException
     */
    protected function make_key($key) {
        return $key;
    }

    /**
     * This function initializes
     * the cache if neccessary
     *
     */
    protected function init_cache() {
        self::$cache_enabled = $GLOBALS['config']->get('cache_enabled', true);
    }

    /**
     * Used to enable/disable cache
     * globally. If this is set to false the entire
     * cache system is disabled including all child
     * cache classes
     *
     * This function can be used in a config or init file
     * like this - Cache::enable_cache(false);
     *
     * @param bool $flag
     */
    public static function enable_cache($flag) {
        self::$cache_enabled = $flag;
    }

    /**
     * Is cache enabled?
     *
     * @return bool
     */
    public static function cache_enabled() {
        return self::$cache_enabled;
    }

    /** ABSTRACT METHODS ******************************************/

    /**
     * Abstract implementation of
     * cache write based on the provided
     * key
     *
     * @param string $key
     * @param string $data
     * @param int $lifetime (0 for never expires)
     * @param array $parameters an array of specific parameters
     *                          can be passed to child objects
     */
    abstract protected function set_data($key, $data, $lifetime = 0, $parameters = null);

    /**
     * Abstract implementation of cache
     * read
     *
     * @param string $key
     *
     * @return mixed
     */
    abstract protected function get_data($key);
    
    /**
     * Abstract implementation of cache 
     * increment - increments $key by $value.
     * The item will NOT be created if it does not exist;
     * if the key is not numeric, it will be changed to $value.
     *
     * @param string $key
     * @param int $value Amount to increment (default is 1)
     * 
     * @return mixed The new item's value, or FALSE on failure
     */
    abstract protected function increment_data($key, $value = 1);

    /**
     * Abstact implementation of cache
     * deletion based on the provided
     * key
     *
     * This function can either delete the cache
     * entry or invalidate it depending on
     * the implementation
     *
     * @param string $key
     */
    abstract protected function delete_data($key);

}

?>