<?php
/**
 * The DataCache object file.
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Cache
 */

/**
 * This is the MemcachedCache object.  This is a wrapper for
 * the new memcached extension to php (Not the one in
 * PECL). The extension can be obtained from
 * http://www.klir.com/~johnm/php-mcache
 *
 * It requires libmemcached to be installed
 * on the webserver as well.  libmemcache can be obtained from
 * http://people.freebsd.org/~seanc/libmemcache/
 *
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Cache
 *
 */
class DataCache extends MemcachedCache {

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
     * @return DataCache
     */
    public static function singleton() {
        if (!Cache::$cache_enabled) {
            return NoCache::singleton();
        }

        if (!self::$instance) {
            self::$instance = new DataCache();
        }

        return self::$instance;
    }

    /**
     * This function adds memcache
     * servers to the pool
     *
     * Right now the values are hardcoded,
     * but later the list of servers will be loaded
     * from LocalCache object that in turn
     * gets them from the database
     *
     */
    protected function setup_servers() {
        $this->add_server('127.0.0.1');
    }

}

?>