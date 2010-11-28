<?php
/**
 * class the constructs and renders an entire
 * HTML/XHTML document.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */

/**
 * This class is used to build a fully
 * qualified html page.  This is typically
 * a base class.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
class HTMLDocument {

    /**
     * HEADtag object that holds all content
     * for the head.
     * @var object
     */
    private $_head = NULL;

    /**
     * Holds the title of the page
     *
     * @var string
     */
    private $_title = NULL;

    /**
     * SCRIPTtag object that holds javascript
     * code for the head tag.
     * @var SCRIPTtag
     */
    private $_head_js = NULL;

    /**
     * STYLEtag object that holds css code
     * for the head.
     * @var STYLEtag
     */
    private $_head_style = NULL;

	/**
     * The default content type
     * for the response
     */
    protected $_content_type = "text/html";

    /**
     * character set to be used in this
     * page.  This gets automatically
     * placed in the Content-Type
     * META tag
     *
     * @var string
     */
    protected $_charset = 'utf-8';

    /**
     * The encoding of the XHTML
     * XML tag
     *
     * @var string
     */
    protected $_xml_encoding = 'UTF-8';

    /**
     * BODYtag object that holds all content
     * for the body tag.
     *
     * @var BODYtag
     */
    protected $_body = NULL;

    /**
     * DOCTYPEtag object that sets the document
     * type.  This gets rendered prior to <html>
     *
     * @var DOCTYPEtag
     */
    protected $_doctype = NULL;

    /**
     * flag to tell the class to try and
     * change the http headers to output
     * document of type text, instead of
     * html.  This is helpfull for debugging.
     *
     * @var boolean
     */
    protected $_text_debug = FALSE;

    /**
     * This holds a FRAMESETtag object.
     * This is used if the person is trying
     * to render a frameset page.
     *
     * @var FRAMESETtag
     */
    protected $_frameset = NULL;

    /**
     * This holds the text used to display
     * a body content when a browser doesn't
     * support framesets
     *
     * @var string
     */
    protected $_noframes_text = 'Sorry, your browser does not support frames';

    /**
     * This holds the attributes for the
     * <html> tag.
     *
     * @var array
     */
    private $_html_attributes = array();

    /**
     * keeps track of which widgets we have
     * automatically pulled in css for
     *
     * @var array
     */
    private $_widget_css_auto = array();

    /**
     * keeps track of which widgets we have
     * automatically pulled in js for
     *
     * @var array
     */
    private $_widget_js_auto = array();

    /**
     * Holds the value of the indent
     * style the user wants to render
     * the page w/
     *
     * @var int
     */
    private $_indent_style = 0;

    /**
     * keeps track of the html
     * render type.
     *
     * @var string
     */
    private $_html_render_type = phphtmllib::HTML;

    /**
     * The favicon params
     *
     * @var array
     */
    private $_favicon = array('href' => '/favicon.ico',
                              'type' => 'images/x-ico',
                              'enabled' => FALSE);


    /**
     * Class Constructor
     * @param string $title Title string for the page
     * @param string $html_type one of 3 types of html to render.  Setting this will
     *                          make the object declare the gobal define which tells
     *                          all of the tag objects what type of html tags to render.
     *                          some tags support special features.  such as the <IMG>
     *                          tag.  If xhtml is selected, the the IMGtag object and all
     *                          utility functions will not render 'border=0' as a default
     *                          attribute, since this is not proper xhtml.
     *                          'html' - HTML 4.0 (default)
     *                          'xhtml_transitional' - render xhtml instead of html
     *                                               - doctype is XHTML transitional.
     *                          'xhtml_strict' - render xhtml instead of html 4.0.
     *                                         - doctype is XHTML strict.
     * @param int $indent_style one of 2 types.  INDENT_NICE or INDENT_LEFT_JUSTIFY
     *                          This tells the page how to render the indenting of the
     *                          output.  By default it is set to INDENT_NICE, which nicely
     *                          indents each nested tag.  You can have all tags rendered
     *                          left justified (smaller size in output) by using
     *                          INDENT_LEFT_JUSTIFY
     *
     */
    public function __construct($title=NULL, $html_type=phphtmllib::HTML, $indent_style=phphtmllib::INDENT_NICE) {

        switch ($html_type) {

        case phphtmllib::HTML:
        default:
            $this->build_doctype('-//W3C//DTD HTML 4.01 Transitional//EN',
                                 'http://www.w3.org/TR/html4/loose.dtd');
            $this->_html_render_type = $GLOBALS['HTML_RENDER_TYPE'] = phphtmllib::HTML;
            break;

        case phphtmllib::XHTML_STRICT:
            $this->build_doctype('-//W3C//DTD XHTML 1.0 Strict//EN',
                                 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd');
            $this->_html_render_type = $GLOBALS['HTML_RENDER_TYPE'] = phphtmllib::XHTML_STRICT;
            $this->set_html_attributes( array( 'xmlns' => 'http://www.w3.org/1999/xhtml',
                                               'xml:lang' => 'en',
                                               'lang' => 'en') );
            break;

        case phphtmllib::XHTML:
        case phphtmllib::XHTML_TRANSITIONAL:
            $this->build_doctype('-//W3C//DTD XHTML 1.0 Transitional//EN',
                                 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd');
            $this->_html_render_type = $GLOBALS['HTML_RENDER_TYPE'] = phphtmllib::XHTML;
            $this->set_html_attributes( array( 'xmlns' => 'http://www.w3.org/1999/xhtml',
                                               'xml:lang' => 'en',
                                               'lang' => 'en') );
            break;

            // What else needs to be done to properly support
            // XHTML frameset?  TODO LIST for 1.1
        case phphtmllib::XHTML_FRAMESET:
            $this->build_doctype('-//W3C//DTD XHTML 1.0 Frameset//EN',
                                 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-frameset.dtd');
            $this->_html_render_type = $GLOBALS['HTML_RENDER_TYPE'] = phphtmllib::XHTML_FRAMESET;
            break;
        }

        $this->_head = new HEADtag();
        $this->_body = new BODYtag(array( 'id'=>'body' ));

        if ($title != NULL) {
            $this->set_title( $title );
        }

        $this->_indent_style = $indent_style;
    }

    // **************************************************
    // * HEAD tag related functions
    // **************************************************

    /**
     * this adds content to the head tag
     * of the page
     *
     * @param mixed - any content to add
     */
    public function add_head_content( ) {
        $num_args = func_num_args();
        for ($i=0;$i<$num_args;$i++) {
            $this->_head->add(func_get_arg($i));
        }
    }

    /**
     * adds raw javascript to the head which
     * will automatically get wrapped in a
     * <script language='JavaScript'> tag.
     * @param mixed $content - raw javascript code to add to the head
     */
    public function add_head_js( $content ) {
        if (!$this->_head_js) {
            // make sure it's set
            $this->_head_js = SCRIPTtag::factory();
        }

        $this->_head_js->add( $content );
    }

    /**
     * this function adds raw css to the
     * <head> tag.  It will automatically
     * be wrapped in a <style type='text/css'>
     *
     * @param string - the raw css
     */
    public function add_head_css( $css ) {
        if (!$this->_head_style) {
            // make sure it's set
            $this->_head_style = STYLEtag::factory();
        }

        $this->_head_style->add( $css );
    }

    /**
     *  Set the title of the page output
     *
     *  @param string $title - the title of the html page
     *
     */
    public function set_title( $title ) {
        $this->_title = $title;
    }

    /**
     *  Returns the title of the page
     *
     *  @return string
     *
     */
    public function get_title() {
        return $this->_title;
    }

    /**
     * Adds a css external reference to the head area
     *
     * @param string $link link tag object or $url for a css.
     * @param string $media the media attribute (if any)
     */
    public function add_css_link( $link, $media=FALSE ) {
        $css = LINKtag::factory($link, 'stylesheet', 'text/css');
        if ($media) {
            $css->set_tag_attribute('media', $media);
        }
        $this->_head->add($css);
    }

    /**
     * This adds a link to an external Javascript
     * file, which will get rendered in the head.
     *
     * @param string $link script tag object or $url of .js file.
     */
    public function add_js_link( $link ) {
        $this->_head->add(SCRIPTtag::factory($link));
    }

    /**
     * Automatically set a page meta tag refresh
     * @param int     $time - time in seconds to refresh
     * @param string  $url - the url to go to.
     */
    public function set_refresh( $time, $url=NULL ) {
        if ($url) {
            $time .= ';url=$url';
        }
        $this->_head->add(METAtag::factory($time, 'refresh'));
    }

    /**
     * set the character set
     * @param string  $charset - the charset for the meta tag
     *
     */
    public function set_charset( $charset ) {
        $this->_charset = $charset;
    }

    /**
     * This sets the encoding type for
     * XHTML documents
     *
     * @param string - the encoding parameter
     */
    public function set_encoding( $encoding ) {
        $this->_xml_encoding = $encoding;
    }

    /**
     * This method sets the lang, and xml:lang
     * setting in the HTML tag.
     *
     * @param string - the language
     */
    public function set_language( $language ) {
        $this->_html_attributes['xml:lang'] = $language;
        $this->_html_attributes['lang'] = $language;
    }

    /**
     * This function is used to set the FRAMSETtag
     * object for this page.  This automatically
     * sets the output for this page object to
     * be a frameset.
     *
     * @param FRAMESETtag object - $frameset
     */
    public function set_frameset( FRAMESETtag $frameset ) {
        $this->_frameset = $frameset;
    }

    /**
     * This function returns the
     * attributes to be used for the
     * <html> tag.
     *
     * @return array();
     */
    public function get_html_attributes() {
        return $this->_html_attributes;
    }

    /**
     * This function sets the attributes
     * for the <html> tag
     *
     * @param array - the name=>value
     *                pair for the
     *               attributes
     */
    public function set_html_attributes( $attributes ) {
        $this->_html_attributes = $attributes;
    }

    /**
     * this builds the content type meta tag.
     *
     */
    private function _build_content_type_tag() {
        $content_type = 'text/html; charset=' . $this->_charset;
        return METAtag::factory($content_type, 'Content-Type');
    }

    /**
     * This is used to enable the ability to add the
     * favicon link in the head of the document.
     * By default it is off.
     *
     * @param boolean TRUE = enable
     */
    public function set_favicon_flag($flag=TRUE) {
        $this->_favicon['enabled'] = $flag;
    }

    /**
     * This allows you to change the default url/path
     * for where the favicon.ico lives.
     * NOTE: calling this method automatically enables the
     *       link in the head to be created.
     *
     * @param string the url to the favicon.ico file
     * @param string the type of the image.
     *               NOTE: Default is image/x-ico
     */
    public function set_favicon($path, $type='image/x-ico') {
        $this->_favicon['href'] = $path;
        $this->_favicon['type'] = $type;
        $this->set_favicon_flag( TRUE );
    }

    // **************************************************
    // * BODY tag related functions
    // **************************************************

    /**
     * This function adds content to the <body>
     * area of the page.
     *
     * @param mixed - any # of parameters
     */
    public function add() {
        $num_args = func_num_args();
        for ($i=0;$i<$num_args;$i++) {
            $arg = func_get_arg($i);

            // see if the arg is an object
            // and a child of HTMLWidget
            if (is_object($arg) && $arg instanceof HTMLWidget) {
                // see if they have an js they need to include
                $js = '';
                $js = $arg->get_javascript();
                $class_name = get_class($arg);
                if ($js != '' && !isset($this->_widget_js_auto[$class_name])) {
                    $this->add_head_js( str_replace(chr(9),'', $js) );
                    $this->_widget_js_auto[$class_name] = TRUE;
                }
            }
            $this->_body->add(func_get_arg($i));
        }
    }

    /**
     * set attributes of body tag
     * @param array $attributes the name=>value pairs
     *
     */
    public function set_body_attributes( $attributes ) {
        if (!is_object( $this->_body )) {
            $this->_create_body();
        }
        $this->_body->set_tag_attributes( $attributes );
    }

    /**
     * function to set a single body attribute
     *
     * @param string attribute name
     * @param string attribute value
     */
    public function set_body_attribute($name, $value) {
        if (!is_object( $this->_body )) {
            $this->_create_body();
        }
        $this->_body->set_tag_attribute($name, $value);
    }

    /**
     * This function is used to build the DOCTYPE
     * tag for the page.  It will automatically
     * create a DOCTYPE with a document_element of 'html'
     * and a source of 'PUBLIC'
     *
     * @param string - link1
     * @param string - link2
     */
    public function build_doctype($link1, $link2=NULL) {
        $this->_doctype = DOCTYPEtag::factory('html', 'PUBLIC', $link1, $link2);
    }


    /**
     * This static method returns a block of text
     * wrapped as an html comment
     *
     * @param string $text
     * @return string
     */
    public static function comment($text) {
        return '<!-- ' . $text . ' //-->';
    }

    // **************************************************
    // * General functions
    // **************************************************

    /**
     * set the $_text_debug flag
     * @param boolean $flag
     */
    public function set_text_debug( $flag ) {
        $this->_text_debug = $flag;
    }

    // **************************************************
    // * RENDERING of content related functions
    // **************************************************

    /**
     *  builds the head object and its content.
     *
     */
    protected function _build_head() {

        $this->_head->add( $this->_build_content_type_tag() );

        if ($this->_title) {
            $this->_head->add(TITLEtag::factory($this->_title));
        }

        if ($this->_favicon['enabled']) {
            $this->_head->add(LINKtag::factory($this->_favicon['href'],
                                               'shortcut icon',
                                               $this->_favicon['type']));
        }

        if ($this->_head_style) {
            $this->_head->add( $this->_head_style );
        }
        if ($this->_head_js) {
            $this->_head->add( $this->_head_js );
        }
    }

    /**
     * This builds a frameset body tag
     * wrapped in a <noframes> tag.
     *
     * @return NOFRAMEStag object.
     */
    private function _frameset_wrap_body() {
        $noframes = new NOFRAMEStag;
        $body = new BODYtag;
        $body->add( $this->_noframes_text );
        $noframes->add( $body );
        return $noframes;
    }

    /**
     * render the page.
     *
     *
     * @return string the raw html output.
     */
    public function render() {

        // make sure the render type is correctly
        // set
        $GLOBALS['HTML_RENDER_TYPE'] = $this->_html_render_type;

        // lets use ourself to render the debug page!
        if ($this->_text_debug) {
            $page = new HTMLDocument;
            $css = ".purple {
    font-family: arial, helvetica, verdana;
    font-weight: bold;
    color: #8b0aa8;
}

.blue {
   font-family: arial, helvetica, verdana;
   font-weight: bold;
   color: #0000FF;
}

.black {
   font-family: arial, helvetica, verdana;
   font-weight: bold;
   color: #000000;
}";
            $page->add_head_css($css);
        }

        $attributes = $this->get_html_attributes();
        $html = new HTMLtag( $attributes );
        $this->_build_head();
        $html->add( $this->_head );

        // Check to see if we are rendering
        // a frameset page.
        if ($this->_frameset != NULL) {
            // Looks like they have set the frameset
            // member, so we are rendering a frameset
            // we will automatically wrap the <body>
            $html->add( $this->_frameset );
            $html->add( $this->_frameset_wrap_body() );
        } else {
            $html->add( $this->_body );
        }

        if ($this->_text_debug) {
            if ($GLOBALS['HTML_RENDER_TYPE'] == phphtmllib::XHTML_STRICT) {
                $xml = new XMLtag(array('version' => '1.0',
                                        'encoding'=>$this->_xml_encoding));
                $page->add( $xml->render(0,1) );
            }
            $page->add( $this->_doctype->render(0,1) );
            $page->add( $html->render($this->_indent_style,1) );
            return $page->render();
        } else {
            $output = '';
            if ($GLOBALS['HTML_RENDER_TYPE'] == phphtmllib::XHTML_STRICT) {
                $xml = new XMLtag(array('version' => '1.0',
                                        'encoding'=>$this->_xml_encoding));
                $output = $xml->render(0);
            }
            $output .= $this->_doctype->render();
            $output .= $html->render($this->_indent_style);
            return $output;
        }
    }

    /**
     * This method allows you to print this object directly.
     * It's a wrapper for render();
     *
     * @return string
     */
    public function __toString() {
        return $this->render();
    }

}

?>