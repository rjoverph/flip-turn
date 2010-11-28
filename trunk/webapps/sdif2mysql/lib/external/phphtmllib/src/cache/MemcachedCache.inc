<?php
/**
 * The MemcachedCache object file.
 *
 * @author Walter A. Boring IV
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Cache
 */

/**
 * This is the MemcachedCache object.  This is a wrapper for
 * the PECL memcache 2 extension.
 * The extension can be obtained from
 *
 * @link http://www.php.net/memcache
 * @link http://pecl.php.net/package/memcache
 *
 * It requires libmemcached to be installed
 * on the webserver as well.  libmemcache can be obtained from
 * http://people.freebsd.org/~seanc/libmemcache/
 *
 *
 * @author Walter A. Boring IV
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Cache
 *
 */
class MemcachedCache extends Cache {

    /**
     * The memcache object that manages
     * the connection
     * 
     * @var Memcache
     */
    protected $cache_obj;

    /**
     * Holds instance of the class
     *
     * @var object
     */
    static private $instance = null;

    /**
     * List of servers to connect.
     */
    protected $servers = array('localhost' => array(self::PORT=>11211,
                                                    self::PERSIST => TRUE,
                                                    self::TIMEOUT => 0));

    const PORT = 0;
    const PERSIST = 1;
    const TIMEOUT = 2;
    const WEIGHT = 3;

    /**
     * Are we connected?
     */
    protected $connected = FALSE;


    /**
     * Singleton function that returns
     * the global class object
     *
     * @return MemcachedCache
     */
    public static function singleton() {
        if (!Cache::$cache_enabled) {
            return NoCache::singleton();
        }
        
        if (!self::$instance) {
            self::$instance = new MemcachedCache();
        }

        return self::$instance;
    }

    /**
     * This function initializes
     * the cache if neccessary
     *
     */
    protected function init_cache() {
        parent::init_cache();
        $this->cache_obj = new Memcache();

        //allow a child class to override this
        //to setup servers prior to connecting
        $this->setup_servers();

        //connect to the servers
        //and add all to the pool
        $this->connect();
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
        //$this->add_server('localhost');
    }

    /**
     * This method is used to connect to one
     * of the memcache servers in the pool
     *
     */
    protected function connect() {
        //get one server and connect to it.
        if (empty($this->servers)) {
            throw new CacheException('No servers specified to connect to',
                                     phphtmllibException::CACHE_MEMCACHED_NO_SERVERS);
        }

        $x = 0;
        foreach($this->servers as $ip => $params) {
            if (!$x) {
                if (!($this->cache_obj->pconnect($ip, $params[self::PORT]))) {
                    throw new CacheException('Memcache connection failed',
                                             phphtmllibException::CACHE_MEMCACHED_CONNECT_FAILED);
                }
                $this->connected = TRUE;
                $x++;
            } else {
                $this->cache_obj->addServer($ip, $params[self::PORT], $params[self::PERSIST]);
            }
        }
    }

    /**
     * This method is used to add a server
     * to the list of servers
     *
     * @param string $ip
     * @param string $port
     * @param boolean keep connection persistent?
     */
    protected function add_server($ip, $port='11211', $persist=TRUE) {

        $this->servers[$ip] = array(self::PORT => $port,
                                    self::PERSIST => $persist);
        if ($this->connected) {
            $ret = $this->cache_obj->addServer($ip, $port, $persist);
            if (!$ret) {
                throw new CacheException('Failed to add server '.$ip.':'.$port,
                                         phphtmllibException::CACHE_MEMCACHED_ADD_SERVER_FAILED);
            }
        }
    }

    /**
     * This method is used to save an
     * entry into the cache
     *
     * @param string $key
     * @param string $data
     * @param int $lifetime (in seconds)
     * @param boolean $compress (use Zlib to compress data?)
     */
    protected function set_data($key, $data, $lifetime = 0, $compress = FALSE) {
        if (!$this->cache_obj->add($key, $data, $compress, $lifetime)) {
            //looks like it already exists....lets replace it
            if (!$this->cache_obj->replace($key, $data, $compress, $lifetime)) {
                throw new CacheException('Memcache set ('.$key.') failed.  Could not replace key.',
                                         phphtmllibException::CACHE_MEMCACHED_SET_DATA_FAILED);
            }
        }
    }
    
    /**
     * Increment the $key by $value; don't create
     * if it doesn't exist, set to $value if can't convert
     * to a number
     *
     * @param string $key
     * @param int $value
     * 
     * @return mixed The new value, or FALSE on failure
     */
    protected function increment_data($key, $value = 1) {
        $ret = $this->cache_obj->increment($key, $value); 
        
        if ($ret === false) {
            throw new CacheException('Memcached increment ('.$key.') failed.',
                                     phphtmllibException::CACHE_MEMCACHED_INCREMENT_DATA_FAILED);
        }
        
        return $ret;
    }

    /**
     * This method is used to get a value from the memcache
     *
     * If a single string was passed, then the function returns
     * the value found in the cache, or FALSE for a cache miss.
     * If FALSE is the value stored in the cache, then it is
     * indistinguishable, from a miss, if you need to store
     * FALSE in the cache, then you should pass an Array() with
     * just one string in it to get() in order to trigger the
     * behavior listed below.
     *
     * When the passed argument was an array, the return value
     * will be an array as well.  This array will contain an
     * entry for each key that was successfully found in the cache.
     * If a miss occurs, then there will simply be no entry in the
     * array for the key. So imagine you
     * call->get(Array('key1', 'key2', 'key3'));
     *
     * If key1 and key3 are found, but key2 is a miss the return value is
     * Array('key1'=>'key1 value', 'key3'=>'key3 value');
     *
     * @param $key mixed either a single string as an argument
     *             (the key to retrieve), or an array of
     *             strings (multiple keys to retrieve)
     *
     * @return mixed
     */
    protected function get_data($key) {
        return $this->cache_obj->get($key);
    }

    /**
     * This method is used to delete
     * an existing entry from the cache
     *
     * @param string $key

     * @return bool
     */
    protected function delete_data($key) {
        return $this->cache_obj->delete($key);
    }

    /**
     * This method 'deletes' ALL KEYS FROM ALL SERVERS.
     *
     * The deletion doesn't happen immediatly.  What happens
     * is that all the current keys in the cache are marked as
     * invalid, and are eventually freed up on successive set
     * calls when a 'garbage' collection happens.
     *
     * @return bool
     */
    public function delete_all() {
        return $this->cache_obj->flush();
    }

    /**
     * This method is used to get the internal stats
     * array from memcache.
     *
     * @return array
     */
    public function get_stats() {
        return $this->cache_obj->getExtendedStats();
    }

}

?>