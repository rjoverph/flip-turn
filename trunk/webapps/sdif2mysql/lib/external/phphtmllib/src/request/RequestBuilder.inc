<?php
/**
 * RequestBuilder.
 *
 * This class handles building of
 * a request URL to a Controller
 * script with a particular target.
 *
 * @see Controller
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Request
 *
 */
class RequestBuilder extends Request {

    /**
     * Target class name to
     * use for the request
     *
     * @var string
     */
    protected $target = null;

    /**
     * This is the main controller
     * script name (typically index.php)
     *
     * @var string
     */
    protected static $file = '';

    /**
     * The default request protocol
     */
    protected $protocol = Request::PROTOCOL_HTTP;

    /**
     * The default request url type
     */
    protected $url_type = Request::URL_TYPE_RELATIVE;

    /**
     * Query parameter seperator
     * @var string
     */
    protected $var_separator = '&';
    
    
    /**
     * Stores the server to connect to.
     * If this isn't set, then we pull it
     * from the $_REQUEST
     *
     */
    protected $server = null;
    
    /**
     * the server port.
     */
    protected $port = null;


    /**
     * Public constructor
     *
     * @param string $target       - request target which is
     *                               the name of the page/widget
     *                               to be executed
     * @param array $values        - array of key=>value pairs to add.
     *
     *
     */
    public function __construct($target, $values=array()) {
        $this->set_target($target);
        $this->set_data($values);
    }

    /**
     * This function adds/sets a
     * request variable
     *
     * @param string $key
     * @param string $value
     */
    public function set($key, $value) {
        $this->data[$key] = $value;
    }

    /**
     * This function sets all request
     * variables at once
     *
     * @param array $data
     */
    public function set_data($data) {
        $this->data = $data;
    }

    /**
     * This method sets the remote file/script to request
     *
     * @param string
     */
    public static function set_file($file) {
        self::$file = $file;
    }

    /**
     * gets the controller script name
     * to use in this mvc request.
     *
     * @param string $prefix
     */
    public function get_file() {
        return self::$file;
    }

    /**
     * This method is used to set the desired
     * Target object that is to handle this request.
     * The Controller class will instantiate the
     * target.
     *
     * @param string $target
     */
    public function set_target($target) {
        if (!isset(ClassMap::$target_lookup[$target])) {
            // target not found
            throw new phphtmllibException('Target "' . $target . '" not found in ClassMap::$target_lookup');
        }

        $this->target = $target;
    }

    /**
     * This method returns the target set
     *
     * @return string
     */
    public function get_target() {
        return $this->target;
    }

    /**
     * This method is used to tell the class
     * what type of url to build...relative or absolute.
     *
     * @see Request::TYPE_ABSOLUTE
     * @see Request::TYPE_RELATIVE
     *
     * @param int $type Request::URL_TYLE_ABSOLUTE or URL_TYLE_RELATIVE
     */
    public function set_url_type($type = Request::URL_TYPE_ABSOLUTE) {
        $this->url_type = $type;
    }

    /**
     * Get the currently set request url type
     * relative or absolute
     *
     * @return int
     */
    public function get_url_type() {
        return $this->url_type;
    }

    /**
     * What type of http request to make.
     * http or https
     *
     * @see Request::TYPE_UNSECURE
     * @see Request::TYPE_SECURE
     *
     * @param string $type Request::PROTOCOL_HTTP or
     *                     Request::PROTOCOL_HTTPS
     */
    public function set_protocol($type = Request::PROTOCOL_HTTP) {
        $this->protocol = $type;
    }

    /**
     * Gets the currently set protocol.
     * This is typically http or https
     *
     * @return string
     */
    public function get_protocol() {
        return $this->protocol;
    }

    /**
     * This method sets the host/server to connect to
     *
     * @param string $host
     */
    public function set_server($host) {
        $this->server = $host;
    }

    /**
     * Get the currently set server
     *
     * @return string
     */
    public function get_server() {
        //if it's not set...
        //we assume we can use the
        //current hostname
        if (!$this->server) {
            $this->server = $_SERVER['SERVER_NAME'];
        }

        return $this->server;
    }
    
    
    /**
     * Set the port for the request.
     * @param $port
     */
    public function set_port($port) {
    	$this->port = $port;
    }
    
    /**
     * get the port for the request.
     * 
     * @return int
     */
    public function get_port() {
    	if (!$this->port) {
    		$this->port = $_SERVER["SERVER_PORT"];
    		if ($this->port == 80) {
    			$this->port = null;
    		}
    	}
    	return $this->port;
    }

    /**
     * This method builds the entire query string.
     *
     * @return  string
     */
    public function get_query_string() {

        if (count($this->data) > 0) {
            return $this->get_query_start().$this->get_query_params_as_string();
        } else {
            return '';
        }
    }

    /**
     * This method is used to convert
     * the data array into a query string.
     *
     * @return string
     */
    public function get_query_params_as_string() {
        $q = array();

        foreach ($this->data as $key => $value) {
            $q[] = urlencode( $key ) . '=' . urlencode($value);
        }

        //return htmlentities( implode($this->var_separator, $q));
        return implode($this->var_separator, $q);
    }

    /**
     * Simple function to return the start of the
     * query string.
     *
     * @return string
     */
    public function get_query_start() {
        return Request::QUERY_STRING_START;
    }

    /**
     * Imports one single variable from request
     * into the current object
     *
     * @param string $name
     */
    public function import_var($name) {
        if ($value = Request::singleton()->get($name)) {
            $this->set($name, $value);
        }
    }

    /**
     * This method enables the importing of the
     * request parameters.
     *
     */
    public function import_request() {
        $data = $this->data;
        $this->data = array();
        $this->init();

        $this->data = array_merge($this->data, $data);
    }

    /**
     * This function will build
     * string URL for the request
     *
     * It will handle re-mapping keys to
     * obfuscate real variable names in the
     * request query string
     *
     * @return string
     *
     */
    public function get_url() {
        $this->set('target', ClassMap::$target_lookup[$this->get_target()]);

        //properly build the url
        if ($this->url_type == Request::URL_TYPE_ABSOLUTE) {
            //this is an absolute request.
            $url = $this->get_protocol().$this->get_server();
            $port = $this->get_port();
            if ($port) {
            	$url .= ":".$port;
            }
            $file = $this->get_file();
            if ($file) {
            	$url .= Request::SLASH.$this->get_file();
            }
            if (($query = $this->get_query_string()) && $query != '?') {
                $url .= Request::SLASH.$this->get_query_string();
            }
            return $url;
        } else {
            //this is a relative url request.
            $file = $this->get_file();
            if ($file) {
                $url = $file;
                if (($query = $this->get_query_string()) && $query != '?') {
                $url .= Request::SLASH.$this->get_query_string();
            }
            return $url;
            } else {
                return Request::SLASH.$this->get_query_string();
            }

        }
    }

    /**
     * This is a simple wrapper for setting
     * the url type, then calling get_url
     *
     * @return string
     */
    public function get_absolute_url() {
        $this->set_url_type(Request::URL_TYPE_ABSOLUTE);
        return $this->get_url();
    }

    /**
     * Some static methods to build build urls
     */

    /**
     * This method is a static function to build a relative
     * url to a target.
     *
     * @param string $target       - request target which is
     *                               the name of the page/widget
     *                               to be executed
     * @param array $values        - array of key=>value pairs to add.
     *
     * @return string the url with query params.
     */
    public static function build_url($target, $values=array()) {
        $r = new RequestBuilder($target, $values);
        return $r->get_url();
    }

    /**
     * This method is a static function to build an absolute
     * url to a target.
     *
     * @param string $target       - request target which is
     *                               the name of the page/widget
     *                               to be executed
     * @param array $values        - array of key=>value pairs to add.
     *
     * @return string the url with query params.
     */
    public static function build_absolute_url($target, $values=array()) {
        $r = new RequestBuilder($target, $values);
        $r->set_url_type(Request::URL_TYPE_ABSOLUTE);
        return $r->get_url();
    }

    /**
     * This method is a static function to build a relative url
     * to a target and import the existing query string parameters
     * from the previous request.
     *
     * @param string $target       - request target which is
     *                               the name of the page/widget
     *                               to be executed
     * @param array $values        - array of key=>value pairs to add.
     *
     * @return string the url with query params.
     */
    public static function build_url_with_request($target, $values=array()) {
        $r = new RequestBuilder($target, $values);
        $r->import_request();
        return $r->get_url();
    }

    /**
     * This method is a static function to build a relative url
     * to a target and import the existing query string parameters
     * from the previous request.
     *
     * @param string $target       - request target which is
     *                               the name of the page/widget
     *                               to be executed
     * @param array $values        - array of key=>value pairs to add.
     *
     * @return string the url with query params.
     */
    public static function build_absolute_url_with_request($target, $values=array()) {
        $r = new RequestBuilder($target, $values);
        $r->set_url_type(Request::URL_TYPE_ABSOLUTE);
        $r->import_request();
        return $r->get_url();
    }

    /**
     * Redirects to a different target
     *
     * @param string $url
     */
    public function redirect($force_js = false) {
        if (Request::singleton()->is_ajax() || headers_sent() || $force_js) {
            print "<script>document.location.href='" . $this->get_absolute_url() . "';</script>";
        }
        else {
            header('Location: ' . $this->get_absolute_url());
        }
        exit;

    }

}

?>
