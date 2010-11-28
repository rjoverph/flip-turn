<?php

/**
 * This class is designed to handle returning proper 
 * http result headers for a REST target.
 * 
 * 
 * @author waboring
 *
 */
class RESTTarget implements RESTInterface {
	
	const HTTP_400 = "400 Bad Request";
	const HTTP_404 = "404 Not Found";
	const HTTP_415 = "415 Unsupported Media Type";
	
	
	
	/**
	 * This contains an array of vars used by all
	 * REST requests. 
	 * 
	 * The child class defines this to register
	 * these vars as requred for EVERY request.
	 */
	protected $request_vars = array();
	
	/**
	 * request variables required by a POST 
	 * @var array
	 */
	protected $post_vars = array();
	
	/**
	 * request variables required by a GET
	 * 
	 * @var array
	 */
	protected $get_vars = array();
	
	/**
	 * request variables required by a PUT
	 * @var array
	 */
	protected $put_vars = array();
	
	/**
	 * request variables required by a DELETE
	 * @var array
	 */
	protected $delete_vars = array();
	
	/**
	 * If we are called here,
	 * that means the child doesn't support GET
	 * 
	 * @see lib/external/phphtmllib/src/rest/RESTInterface#do_GET()
	 */
	public function do_GET() {
		$this->error(RESTTarget::HTTP_404);
	}
	
	/**
	 * If we are called here,
	 * that means the child doesn't support PUT
	 * 
	 * @see lib/external/phphtmllib/src/rest/RESTInterface#do_PUT()
	 */
	public function do_PUT() {
		$this->error(RESTTarget::HTTP_404);
	}
	
	/**
	 * If we are called here,
	 * that means the child doesn't support POST
	 * 
	 * @see lib/external/phphtmllib/src/rest/RESTInterface#do_POST()
	 */
	public function do_POST() {
		$this->error(RESTTarget::HTTP_404);
	}
	
	/**
	 * If we are called here,
	 * that means the child doesn't support DELETE
	 * 
	 * @see lib/external/phphtmllib/src/rest/RESTInterface#do_DELETE()
	 */
	public function do_DELETE() {
		$this->error(RESTTarget::HTTP_404);
	}
	
	
	/**
	 * This method returns an array of
	 * request variable names that
	 * are required for any REST request
	 * 
	 * @return unknown_type
	 */
	public function request_vars() {
		return $this->request_vars;
	}
	
	/**
	 * This method is called by the RESTController
	 * to get the list of required variables
	 * for a GET
	 * 
	 * @return unknown_type
	 */
	public function request_get_vars() {
		return $this->get_vars;
	}
	
	/**
	 * This method is called by the RESTController
	 * to get the list of required variables
	 * for a POST
	 * 
	 * @return unknown_type
	 */
	public function request_post_vars() {
		return $this->post_vars;
	}
	
	/**
	 * This method is called by the RESTController
	 * to get the list of required variables
	 * for a PUT
	 * 
	 * @return unknown_type
	 */
	public function request_put_vars() {
		return $this->put_vars;
	}
	
	/**
	 * This method is called by the RESTController
	 * to get the list of required variables
	 * for a DELETE
	 * 
	 * @return unknown_type
	 */
	public function request_delete_vars() {
		return $this->delete_vars;
	}

	/**
	 * Throw out an http error code and exit
	 * 
	 * @param String $code
	 * @return none
	 */
	protected function error($code) {		
		header("HTTP/1.0 ".$code);
		exit;
	}
}
?>