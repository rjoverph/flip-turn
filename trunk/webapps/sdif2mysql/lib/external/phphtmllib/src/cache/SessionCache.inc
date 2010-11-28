<?php
/**
 * The session Cache object.
 * 
 * @author Walter A. Boring IV
 * @author Suren Markosian
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
 * @author Walter A. Boring IV
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Cache
 *
 */
class SessionCache extends MemcachedCache {

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
     * @return SessionCache
     */
    public static function singleton() {
        if (!self::$instance) {
            self::$instance = new SessionCache();
        }

        return self::$instance;
    }

    /**
     * This function adds memcache
     * servers to the pool
     *
     * Right now the values are hardcoded,
     * but later the list of servers will be loaded
     * from FileCache object that in turn
     * gets them from the database
     *
     */
    protected function setup_servers() {
        $this->add_server('127.0.0.1');
    }

}

?>