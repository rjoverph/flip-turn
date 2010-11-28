<?php

/**
 * This class is used to render a JSON array output that gets
 * put back to the browser.
 */


/**
 * JSONWidget is used when you want the controller
 * to be able to call a "renderable" object that
 * simply returns JSON.
 * 
 * @author waboring
 *
 */
abstract class JSONWidget {
	
	protected $data = null;
	
	public function __construct() {		
		$this->init();	
	}		
	
	
	public function render() {
		header("Content-type:text/javascript");		
		$data = $this->build_object();		
		return json_encode($data);		
	}
	
	/**
	 * called at constructor time to do something.
	 * @return none
	 */
	abstract public function init();
	
	/**
	 * This method is used to build the object
	 * that will be converted to json and 
	 * returned to the request
	 * @return mixed
	 */
	abstract public function build_object();
		
}
?>