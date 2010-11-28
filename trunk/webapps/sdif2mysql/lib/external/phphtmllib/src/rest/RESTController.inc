<?php
/**
 * The Base Controller
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Controller
 */


/**
 * This class handles dealing with REST requests.
 * It makes sure the target can handle a REST specific request
 * for each of the REST type of requests
 *
 * GET/PUT/DELETE/POST
 *
 */
class RESTController extends Controller {
	
	//TODO create mechanism to show 
	//list of REST services.
	//which will become the default 
	//target.
	
	protected $default_target = "TODO";


	function __construct($prefix) {			
		
		if ($prefix) {
			// set directory prefix to use
			// all our requests will go here
			RequestBuilder::set_file($prefix);
		}
		
		if (!($this->target = Request::singleton()->get_target())) {
            // no target specified
            // use default target
            $this->target = $this->default_target;
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

	function execute() {

		//make sure the target object implements the REST interface
		$class = new ReflectionObject($this->obj);
		
		$request = Request::Singleton();
		
		$request->register($this->obj->request_vars());

		switch ($request->get_request_method()) {
			case Request::METHOD_GET:
				$request->register($this->obj->request_get_vars());
				$this->obj->do_GET();
				break;

			case Request::METHOD_POST:
				$request->register($this->obj->request_post_vars());
				$this->obj->do_POST();
				break;

			case Request::METHOD_PUT:
				$request->register($this->obj->request_put_vars());
				$this->obj->do_PUT();
				break;

			case Request::METHOD_DELETE:
				$request->register($this->obj->request_delete_vars());
				$this->obj->do_DELETE();
				break;
		}

	}


}
?>