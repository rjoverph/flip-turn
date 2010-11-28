<?php

/**
 * This contains the WMLDocumentClass
 *
 * $Id: WMLDocument.inc 3017 2007-09-29 05:13:20Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 *
 */

/**
 *
 * This class lets you build a complete
 * WML document and render it
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 */
class WMLDocument extends XMLDocument {

    protected $_show_http_header = TRUE;

	function __construct() {
		$this->set_doctype_source("PUBLIC");
		parent::__construct("wml","-//WAPFORUM//DTD WML 1.1//EN");
		$this->set_doctype_link("http://www.wapforum.org/DTD/wml_1.1.xml");

		//by default we want to output the
		//http Content-type header
		//$this->show_http_header(TRUE);

		//set the correct content-type
		$this->set_http_content_type( "text/vnd.wap.wml" );
	}
}
?>
