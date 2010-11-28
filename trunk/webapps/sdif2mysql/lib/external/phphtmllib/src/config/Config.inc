<?php
/**
 * This is the main phpHtmlLib config
 * class.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Config
 */


/**
 * This is the base Config object that can be used to setup
 * application variables.
 *
 * It's an iterator and can be counted.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Config
 */
class Config implements Countable, Iterator {

    /**
     * The iterator index
     */
    protected $index;

    /**
     * The number of elements in the Config
     */
    protected $count;

    /**
     * The config data.
     */
    protected $data = array();

    /**
     * The constructor
     *
     * @param array $data
     */
    public function __construct() {
        //reset the index.
        $this->index = 0;
        //set the count to 0.
        $this->count = 0;
    }

    /**
     * Singleton method to get the instance of
     * the Config object
     *
     * @return Config
     */
    public static function singleton() {
        static $config = null;

        if (!$config) {
            $config = new Config;
        }

        return $config;
    }

    protected function convert_array_to_class($data) {
        $obj = new StdClass;
        if (is_array($data )) {
            foreach($data as $key => $value) {
                $obj->$key = $this->convert_array_to_class($value);
            }
            return $obj;
        } else {
            return $data;
        }
    }

    /**
     * This method tries to return the value for
     * a config key.
     *
     * overload the __get() so that
     * $config->foo will work.
     *
     * @param string $name
     * @return mixed not found == null
     */
    public function __get($name) {
       return $this->get($name);
    }


    /**
     * This method can be used to get a
     * value in the config.
     *
     * @param $name
     * @return mixed
     */
    public function get($name, $default=null) {
        if (!isset($this->data[$name])) {
            return $default;
        } else {
            return $this->data[$name];
        }
    }


    /**
     * This method does the actual setting of the
     * config value.  It's an override so that
     *
     * $config->foo = $value  works.
     *
     * @param string $name
     * @param mixed $value
     */
    public function __set($name, $value) {
        $this->set($name, $value);
    }


    /**
     * This method can be used to set a value
     *
     * @param string $name
     * @param mixed $value
     */
    public function set($name, $value) {
        if ($this->_is_valid_name($name)) {
            $this->data[$name] = $value;
        } else {
            throw new phphtmllibException("Cache set() Invalid key: '$name'");
        }
    }

    /**
     * Support isset() overloading on PHP 5.1
     *
     * @param string $name
     * @return boolean
     */
    public function __isset($name) {
        return isset($this->data[$name]);
    }

    /**
     * Defined by Countable interface
     *
     * @return int
     */
    public function count() {
        $this->count = count($this->data);
        return $this->count;
    }

    /**
     * Defined by Iterator interface
     *
     * @return mixed
     */
    public function current(){
        return current($this->data);
    }

    /**
     * Defined by Iterator interface
     *
     * @return mixed
     */
    public function key() {
        return key($this->data);
    }

    /**
     * Defined by Iterator interface
     *
     */
    public function next() {
        next($this->data);
        $this->index++;
    }

    /**
     * Defined by Iterator interface
     *
     */
    public function rewind() {
        reset($this->data);
        $this->index = 0;
    }

    /**
     * Defined by Iterator interface
     *
     * @return boolean
     */
    public function valid() {
        //make sure count is set.
        if (!$this->count) {
            $this->count();
        }
        return $this->index < $this->count;
    }


    /**
     * Ensure that the key is a valid PHP property name
     *
     * @param string $name
     * @return boolean
     */
    protected function _is_valid_name($name) {
        return (boolean) preg_match('/^[a-zA-Z_\x7f-\xff][a-zA-Z0-9_\x7f-\xff]*$/', $name);
    }


}
 ?>
