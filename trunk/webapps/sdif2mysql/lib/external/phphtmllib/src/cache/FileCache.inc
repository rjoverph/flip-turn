<?php
/**
 * FileCache file.
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Cache
 */

/**
 * This is the FileCache object. It manages
 * data cache on the local file system
 *
 * Data is stored as a serialized array of
 * (expiration_time, data)
 *
 * $Id: FileCache.inc 2928 2007-09-13 16:43:50Z brianrue $
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Cache
 */
class FileCache extends Cache {

    /**
     * System path seperator
     * @var string
     * @todo autodetermine from system OS / file system type
     */
    const PATH_SEPERATOR = '/';

    /**
     * Directory where we store
     * our cached data
     *
     * NOTE: This can be set as a default
     *       in the global config by
     *   $GLOBALS['config']->set('file_cache_dir', '/some/dir');
     *   If the global config is set, it will be used.
     */
    protected static $cache_dir;

    /**
     * The default cache dir if
     * $GLOBALS['config']->file_cache_dir isn't set
     *
     */
    private static $default_cache_dir = '/tmp/phphtmllib-cache';

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
     * @return FileCache
     */
    public static function singleton() {
        if (!Cache::$cache_enabled) {
            return NoCache::singleton();
        }

        if (!self::$instance) {
            self::$instance = new FileCache();
        }

        return self::$instance;
    }

    /**
     * Saves data to a file
     *
     * @param string $key
     * @param string $data
     * @param int $lifetime (in seconds)
     *
     */
    protected function set_data($key, $data, $lifetime = 0, $parameters = null) {

        if ($lifetime === 0) {
            $time = 0;
        } else {
            $time = time() + $lifetime;
        }

        $str = serialize(array($time, $data));
        $len = strlen($str);

        $c = file_put_contents($key, $str);

        // make sure cache write did not fail
        if ($c != $len) {
            if (empty($c)) { $c = '0'; }
            throw new CacheException('FileCache write failed (' . $c . ' of ' . $len . ' bytes written)');
        }
    }
    
    /**
     * Increment the $key by $value; don't create
     * if it doesn't exist, set to $value if can't convert
     * to number
     *
     * @param string $key
     * @param int $value
     * 
     * @return mixed The new value, or FALSE on failure
     */
    protected function increment_data($key, $value = 1) {
        
        if (file_exists($key)) {
            // file exists, read it
            $data = unserialize(file_get_contents($key));
            
            // check expiration
            if ($data[0] != 0 && time() > $data[0]) {
                // cache expired, cannot be used
                return false;
            }
            else {
                // convert to int and increment
                $data[1] = (int)$data[1] + $value;
                
                // save to cache
                $str = serialize(array($data[0], $data[1]));
                $len = strlen($str);
                
                $c = file_put_contents($key, $str);
                
                // make sure cache write did not fail
                if ($c != $len) {
                    if (empty($c)) { $c = '0'; }
                    throw new CacheException('FileCache write failed (' . $c . ' of ' . $len . ' bytes written)');
                }
                
                return $data[1];
            }
        } else {
            // file not found
            return false;
        }
    }

    /**
     * Reads data from a file based on key
     *
     * @param string $key
     *
     * @return mixed
     */
    protected function get_data($key) {

        if (file_exists($key)) {
            // file exists, read it
            $data = unserialize(file_get_contents($key));

            // check expiration
            if ($data[0] != 0 && time() > $data[0]) {
                // cache expired, cannot be used
                return false;
            }
            else {
                // return the cached data
                return $data[1];
            }
        }
        else {
            // file not found - no cache
            return false;
        }
    }

    /**
     * This function will delete cache file
     * if any
     *
     * @param string $key
     */
    protected function delete_data($key) {

        if (file_exists($key)) {
            unlink($key);
        }

    }

    /**
     * Sets cache directory
     *
     * @param string $dir
     */
    public static function set_cache_dir($dir) {
        FileCache::$cache_dir = $dir;
    }

    /**
     * This function returns a file name
     * based on the cache key
     *
     * @param string $key
     *
     * @return string
     */
    protected function make_key($key) {
        if (substr(FileCache::$cache_dir, -1, 1) == '/') {
            $seperator = '';
        } else {
            $seperator = FileCache::PATH_SEPERATOR;
        }
        return FileCache::$cache_dir . $seperator . preg_replace("/[^A-Za-z0-9\_\.\-\+\040]/", '', $key) . '.cache';
    }

    /**
     * This function initializes
     * the cache directory
     *
     */
    protected function init_cache() {
        parent::init_cache();
        //if there is a config setting
        //we'll use it.
        $this->set_cache_dir($GLOBALS['config']->get('file_cache_dir',FileCache::$default_cache_dir));

        // make sure the cache directory exists
        if (!file_exists(FileCache::$cache_dir)) {
            if (!mkdir(FileCache::$cache_dir, 0755, TRUE)) {
                throw new CacheException("Failed to create " . FileCache::$cache_dir);
            }
        }
    }

}

?>