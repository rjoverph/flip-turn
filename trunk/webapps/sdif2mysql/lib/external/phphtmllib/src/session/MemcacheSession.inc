<?php
/**
 * MemcacheSession manager
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Session
 */


/**
 * This class is used for a DB only Session Handler.
 * It uses the MemcachedCache (memcached) for storage.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Session
 */
class MemcacheSession extends Session {

    /**
     * This static method is used to set up
     * the session save handlers for memached
     *
     */
    public static function init() {
        session_module_name('user');
        session_set_save_handler(
            array('MemcacheSession', 'open'),
            array('MemcacheSession', 'close'),
            array('MemcacheSession', 'read'),
            array('MemcacheSession', 'write'),
            array('MemcacheSession', 'destroy'),
            array('MemcacheSession', 'gc')
        );
    }

    /**
     * Open and test the memcached server to make
     * sure we have room to store
     *
     * @param string the save path
     * @param string the session name
     */
    public static function open($save_path, $session_name) {
        $cache = self::get_cache();
        $stats = $cache->get_stats();
        if ($stats['limit_maxbytes'] <=0 ) {
            //we don't have room to store shit.
            throw new phphtmllibException('There is no room in the memcached to store anything!');
            return FALSE;
        }

        return TRUE;
    }

    /**
     * Don't need to do anything here
     *
     */
    public static function close() {
    }

    /**
     * Try and read the session data for $key from
     * the cache
     *
     * @param string the session id/key
     */
    public static function read($key) {
        $cache = self::get_cache();
        $data = $cache->get($key);
        return $data;
    }

    /**
     * This function is used to store session data
     *
     * @param string the session id/key
     * @param string the session data
     */
    public static function write($key, $data) {
        $cache = self::get_cache();
        $cache->set($key, $data, session_cache_expire()*60);
    }

    /**
     * This nukes the entry
     */
    public static function destroy($key) {
        $cache = self::get_cache();
        $cache->delete($key);
    }

    /**
     * Garbage collection
     *
     * @param int the max lifetime any session can exist.
     */
    public static function gc($maxlifetime) {
        //this takes care of itself due to the lifetime
        //passed in to the set() call
    }

    /**
     * this method returns the cache object to use
     * for storage of session vars
     * 
     * @return MemcachedCache object
     */
    protected static function get_cache() {
        return MemcachedCache::singleton();
    }
}
?>