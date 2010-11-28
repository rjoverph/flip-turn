<?php

/**
 * This file contains the HTMLWidget class
 *
 * $Id: HTMLWidget.inc 2736 2007-05-16 06:02:12Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 *
 */

/**
 * this is the base widget class, that all widgets
 * are based off of.  It provides some basic
 * members and methods
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */
class HTMLWidget extends Container implements HTMLWidgetInterface {

    /**
     * The title of the table.
     * @access public
     * @var string
     */
    protected $title='';

    /**
     * the width of the widget
     * @access public
     * @var string
     */
    protected $width="100%";

    /**
     * The widget wide alignment
     * value.
     * @access private
     * @var string
     */
    protected $_align = NULL;

    /**
     * hold the data for this
     * widget.  can be anything,
     * depends on the child class.
     * defaults to an array.
     * @access private
     * @var array
     */
    protected $data = array();

    /**
     * The image path prefix.
     * If an image lives on the server in
     * /images/foo/blah.jpg
     * then this prefix should be
     * /images/foo
     */
    protected $_image_prefix;

    /**
     * id value of the wrapper div
     */
    protected $id;

    /**
     * The constructor to help setup the
     * widget image path
     */
    public function __construct() {
        $this->_image_prefix = $GLOBALS['config']->get('widget_image_path', '/images/widgets');
    }

    /**
     * Function for returning the raw javascript
     * that is required for this widget.
     *
     * @return string - the raw javascript
     */
    public function get_javascript() {
        return NULL;
    }

    /**
     * Set the title for the widget.
     * this is just a generic title string
     * that can be used however the child class
     * wants to use it.
     *
     * @param string - $title
     */
    public function set_title( $title ) {
        $this->title = $title;
    }

    /**
     * Function for accessing the
     * title of this widget
     *
     * @return string - the title
     */
    public function get_title() {
        return $this->title;
    }

    /**
     * Set the width for the widget.
     * this is meant to be the overall
     * width expected to be used to
     * control the generated html.
     *
     * @param string - $width (ie. 80, 100%)
     */
    public function set_width( $width ) {
        $this->width = $width;
    }

    /**
     * Function for getting the current
     * widget width setting.
     *
     * @return string - the width
     */
    public function get_width() {
        return $this->width;
    }

    /**
     * This function sets the align attribute
     * for the outer table.
     *
     * @param string - $align - the align value
     */
    public function set_align( $align ) {
        $this->_align = $align;
    }

    /**
     * This gets the alignment value
     * for the outer table
     *
     * @return string - the alignment
     */
    public function get_align() {
        return $this->_align;
    }

    /**
     * This function is used to set the
     * image path prefix.
     *
     * @param string
     */
    public function set_image_path_prefix($path) {
        $this->_image_prefix = $path;
    }

    /**
     * Get the id value
     *
     * @return string
     */
    public function get_id() {
        return $this->id;
    }

    /**
     * set the id
     *
     * @param string $id
     */
    public function set_id($id) {
        $this->id = $id;
    }
}
?>
