<?php
/**
 * This class handles request
 * parsing and processing
 *
 * It handles HTTP request coming
 * from HTTP/SOAP interfaces
 *
 * This is a read-only class and the
 * request variables cannot be modified
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Request
 *
 */
class Request {

    const METHOD_GET  = 'GET';
    const METHOD_POST = 'POST';

    const URL_TYPE_RELATIVE = 0;
    const URL_TYPE_ABSOLUTE = 1;

    const PROTOCOL_HTTP = 'http://';
    const PROTOCOL_HTTPS = 'https://';

    const QUERY_STRING_START = '?';
    const SLASH = '/';


    /**
     * Holds request data
     *
     * @var array
     */
    protected $data = array();

    /**
     * Here we keep a list of all
     * registered variables
     * and their properties
     *
     * @var array
     */
    protected $registeredVars = array('target' => Validator::TYPE_STRING,
                                      'id'     => Validator::TYPE_ID,
                                      'ajax'   => Validator::TYPE_BOOL,
                                      'ajaxid' => Validator::TYPE_STRING,
                                      'flushcache' => Validator::TYPE_BOOL);

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
     * @return Request
     */
    public static function singleton() {
        if (!self::$instance) {
            self::$instance = new Request();
        }

        return self::$instance;
    }

    /**
     * Constructor should
     * not be called directly,
     * we use singletons
     *
     */
    protected function __construct() {
        $this->init();
    }

    /**
     * Assign inital values
     * to our data
     *
     */
    protected function init() {
        //we don't want cookies
        $this->data = array_merge($_POST, $_GET);
    }

    /**
     * This returns the method of the last
     * request that was made.
     *
     * @return string
     */
    public function get_request_method() {
        return $_SERVER['REQUEST_METHOD'];
    }

    /**
     * Was the current request done
     * via ajax or not?
     *
     * @param string $ajaxId - was the ajax target divid this?
     * @return boolean
     */
    public function is_ajax($ajaxId = NULL) {

        if ($ajaxId) {
            return ($this->get('ajax') && $this->get('ajaxid') == $ajaxId);
        }
        else {
            return $this->get('ajax');
        }
    }

    /**
     * Was the current request done
     * via ajax or not?
     *
     * @param string $ajaxId - was the ajax target divid this?
     * @return boolean
     */
    public function is_flush_cache_request($ajaxId = NULL) {
        return $this->get('flushcache');
    }

    /**
     * Returns a single request variable
     * or false if not found
     *
     * @param string $key
     * @param mixed $default value if not found
     * @return mixed
     * @todo fix the validation.
     */
    public function get($key, $default=false) {

/*        if (!isset($this->registeredVars[$key])) {
            throw new phphtmllibException('Request parameter is not registered: ' . $key);
        }

        else */
        if (isset($this->data[$key])) {
            /*if (!$this->validate($this->data[$key], $this->registeredVars[$key])) {
                throw new phphtmllibException('Request parameter validation failed: ' .
                                    $key . ' of type ' . $this->registeredVars[$key]);
            }*/
            return $this->data[$key];
        }
        else {
            return $default;
        }
    }

    /**
     * Returns current target
     *
     * @param string default target name if no target exists.
     * @return string
     */
    public function get_target($default=NULL) {
        if (!isset($this->data['target']) || $this->data['target'] == '') {
            if ($default) {
                $this->data['target'] = ClassMap::$target_lookup[$default];
                return $default;
            } else {
                return false;
            }
        } else if (isset(ClassMap::$target[$this->data['target']])) {
            return ClassMap::$target[$this->data['target']];
        }
        else {
            throw new phphtmllibException('Target ' . $this->data['target'] . ' does not exist',
                                phphtmllibException::ERR_REQUEST_INVALID_TARGET);
        }
    }

    /**
     * Delete a key from the request.
     *
     * @param string $key
     */
    public function delete($key) {
        if (isset($this->data[$key])) {
            unset($this->data[$key]);
        }
    }

    /**
     * This function lets you register
     * allowed request variables
     * and their types
     *
     * @param array $varDef hash array; key: string name for the request var;
     *                                value: Validator::TYPE for request var value validation
     */
    public function register($varDef) {
        if (is_array($varDef)) {
            $this->registeredVars = array_merge($this->registeredVars, $varDef);
        }
    }

    /**
     * Adds a new registered variable
     * to the request object
     *
     * @param string $name
     * @param string $type
     */
    public function register_var($name, $type) {
        $this->registeredVars[$name] = $type;
    }

    /**
     * This function performs validation
     * of a parameter based on its type
     *
     * @param mixed $value
     * @param int $type
     */
    private function validate($value, $type) {
        return Validator::type($value, $type);
    }

}

?>