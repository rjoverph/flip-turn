<?php

/**
 * This contains the SVGDocumentClass
 *
 * $Id: SVGDocument.inc 3017 2007-09-29 05:13:20Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 *
 */

/**
 *
 * This class lets you build a complete
 * SVG document.
 *
 * SVG = Scalable Vector Graphics
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 */
class SVGDocument extends XMLDocument {

    protected $_show_http_header = TRUE;

    /**
     * The constructor to building a SVG document.
     *
     * @param string - the svg tag's width attribute
     * @param string - the svg tag's height attribute
     */
    function __construct($width="100%", $height="100%") {
        //make sure we render everything as XHTML
        define("HTML_RENDER_TYPE", phphtmllib::XHTML);
        $this->set_doctype_source("PUBLIC");
        parent::__construct("svg","-//W3C//DTD SVG 1.0//EN");
        $this->set_doctype_link("http://www.w3.org/TR/2001/REC-SVG-20010904/DTD/svg10.dtd");

        $this->set_root_attributes(
            array("width" => $width, "height" => $height,
                  "xmlns" => "http://www.w3.org/2000/svg",
                  "xmlns:xlink" => "http://www.w3.org/1999/xlink"));

        //turn off the character encoding
        //$this->show_character_encoding( FALSE );

        //set the correct content-type
        $this->set_http_content_type( "image/svg+xml" );
    }
}
?>
