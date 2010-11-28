<?php
/**
 * This file contains the REST Interface class
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Controller
 */


/**
 * This interface describes methods that must be
 * implemented to handle REST requests.
 *
 */
interface RESTInterface {
	
	/**
	 * This method is called to handle a GET
	 * query.
	 *
	 */
	public function do_GET();
	
	/**
	 * This method is called to handle a POST
	 * request.
	 *
	 */
	public function do_POST();
	
	/**
	 * This method is called to handle a PUT
	 * request
	 *
	 */
	public function do_PUT();
	
	
	/**
	 * This method is called to handle a DELETE
	 *
	 */
	public function do_DELETE();
}
?>