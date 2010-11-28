<?php
/**
 * The Base Controller
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Controller
 */


/**
 * This is the application controller
 * that controls and executes a
 * renderable class
 *
 * This is the entry point of the application
 * and all requests from outside world are passed
 * by this class
 *
 * It is using a global ClassMap class and the
 * Request object to resolve target into
 * renderable class names
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Controller
 *
 * @todo make calls to target obj static
 * @todo add observer pattern support
 *
 */
class Controller {

    /**
     * Holds instance of the
     * class to be executed
     *
     * @var object
     */
    protected $obj;

    /**
     * If true we will enable
     * debugging and track time
     * and variables
     *
     * @var bool
     */
    protected $debug = false;

    /**
     * The target to use
     *
     * @var string
     */
    protected $target;

	/**
     * The character set for
     * http header to set.
     */
    protected $charset = "utf-8";

    /**
     * The default content type
     * for the response
     */
    protected $content_type = "text/html";

    /**
     * Here we resolve and create an instance
     * of our controlled class
     *
     * @param string $default_target - in case no target is provided
     *                                 we use the default one
     * @param string $prefix         - this is a directory prefix
     *                               - in case the code app lives in a
     *                                 web server sub-tree
     *
     */
    public function __construct($default_target = null, $prefix = null) {

        if (!($this->target = Request::singleton()->get_target($default_target))) {
            // no target specified
            // use default target
            $this->target = $default_target;
        }

        if ($prefix) {
            // set directory prefix to use
            // all our requests will go here
            RequestBuilder::set_file($prefix);
        }

        // instantiate the object
        $this->obj = new $this->target;

        // register request variables
//        Request::singleton()->register($this->obj->request_vars());

        if ($this->obj instanceof FormContent) {
            // this is a form content
            // let's wrap it into FormProcessor
            $this->obj = $this->get_form_processor_object($this->obj);
        }
    }

    /**
     * This method is used to build the FormProcessor
     * needed to handle the FormContent target.
     *
     * By default it uses the FormProcessor class
     * but this can be replaced with a FormProcessor
     * child class
     *
     * @param string $target
     *
     * @return FormProcessor
     */
    protected function get_form_processor_object(FormContent $obj) {
        return new AjaxFormProcessor($obj, true);
    }

    /**
     * Returns default cache object
     * to use for caching
     *
     * @return Cache
     */
    protected function get_cache_object() {
        return FileCache::singleton();
    }

    /**
     * Sets the debugging flag
     *
     * @param bool $flag
     */
    public final function set_debug($flag) {
        $this->debug = $flag;
    }

    /**
     * This function is used to output any http headers
     */
    protected function http_headers() {
		header("Content-type: ".$this->content_type."; charset=".$this->charset.";");
    }

    /**
     * This function simply prints
     * render output of the controlled
     * class
     *
     */
    public function execute() {

        $time = microtime(true);

	    if (method_exists($this->obj, "http_headers")) {
            $this->obj->http_headers();
        } else {
        	$this->http_headers();
        }

        if (Cache::cache_enabled() &&
            $this->obj instanceof Cacheable &&
            $this->obj->is_cacheable()) {

            // let's see if we can pull the content out of the cache
            $cache_key = $this->obj->get_cache_key() . (int)Request::singleton()->is_ajax();
            $cache_obj = $this->get_cache_object();

            //if this was a flush request...lets flush it first
            //this will force the get to fail and rebuild
            if (Request::singleton()->is_flush_cache_request()) {
                $cache_obj->delete($cache_key);
            }

            if (!($html = $cache_obj->get($cache_key))) {
                // not found or expired
                // we will cache it
                $html = $this->obj->render();
                $cache_obj->set($cache_key, $html, $this->obj->get_cache_lifetime());
            }
        }
        else {
            // this object is not cacheable
            $html = $this->obj->render();
        }

        print $html;

        if ($GLOBALS['config']->get('controller_request_debug',false)) {
        	if (method_exists($this->obj, "controller_debug_allowed")) {
        		if ($this->obj->controller_debug_allowed()) {
        			print $this->get_debug_panel($this->target, $this->obj, $html, (microtime(true) - $time))->render();
        		}        		
        	} else {
            	print $this->get_debug_panel($this->target, $this->obj, $html, (microtime(true) - $time))->render();
        	}
        }
    }

    /**
     * this method is used for getting the DebugPanelWidget
     *
     * @param string $target
     * @param obj $object
     * @param string $html
     * @param int render time
     * @return DebugPanelWidget
     */
    protected function get_debug_panel($target, $object, $html, $time) {
        return new DebugPanelWidget($target, $object, $html, $time);
    }


}

?>
