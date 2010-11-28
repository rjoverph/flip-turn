<?php
/**
 * This class is nothing more then a
 * container widget.  It lets you
 * push data into it, and it will
 * render each item indented properly
 * so it works with the rest of the libs.
 *
 * This is helpfull when you have a function
 * that wants to return multiple Tag Objects
 * or widgets.  Just wrap them in this container
 * and they will all get rendered with the
 * current indentation level.
 *
 * Base Class for phpHtmlLib
 *
 * @link http://phphtmllib.sourceforge.net
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @tutorial Container.cls
 *
 */


/**
 * This is a base class for phpHtmlLib
 * that is used to contain things that can
 * be 'rendered'
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 */
class Container implements phphtmllib {

    /**
     * Tag content as a stack
     * ie <span> content here </span>
     * @var  array
     */
    //protected $_content = array();

    /**
     * The flags that tell us
     * how to render the tag
     * its contents, and the close
     */
    protected $_flags = phphtmllib::_FLAGS_DEFAULT;


    /**
     * The constructor.
     *
     * This lets you pass in data
     * that you want automatically
     * added to the container.  This
     * works in the same manner as
     * the push() method.
     *
     * {@source }
     *
     * @tutorial Container.cls#constructor
     */
    public function __construct() {
        //We do the adding to the content var
        //here instead of calling $this->push()
        //to save some cpu cycles.
        $num = func_num_args();
        if ($num > 0) {
            $arg = func_get_arg(0);
            if (is_array($arg)) {
                $this->_content = $arg;
            } else {
                for ($i=0;$i<$num;$i++) {
                    $arg = func_get_arg($i);
                    $this->_content[] = $arg;
                }
            }
        }


        //set the flag bitmask
        //$this->_set_flags();
    }

    /**
     * This method is used to create a Container
     * object and populate it with data
     *
     *
     * @return Container
     */
    public static function factory() {
        $args = func_get_args();
        $c = new Container($args);
        return $c;
    }

    /**
     * This function is compatible with the
     * rest of the phpHtmllib API spec.
     * It just walks through each of the
     * class' data and renders it with the
     * appropriate indentation.
     *
     * {@source }
     *
     * @param int - the indentation level for
     *              the container.
     * @param int - the output debug flag to
     *              maintain compatibility w/ the API.
     *
     * @return string the raw html output.
     */
    public function render($indent_level=0, $output_debug=0) {
        $html = '';
        //help avoid multiple calls
        $indent = $this->_render_indent($indent_level, $output_debug);

        $count = count($this->_content);
        for ($x=0; $x<$count; $x++) {
            $item = &$this->_content[$x];
            if (is_object($item) && method_exists($item, "render") ) {
                if (($this->_flags & phphtmllib::_COLLAPSE) && method_exists($item, "set_collapse")) {
                    $item->set_collapse(TRUE, FALSE);
                }
                $html .= $item->render($indent_level, $output_debug);
            } else {
                if ($this->_flags & phphtmllib::_COLLAPSE) {
                    $html .= $item;
                } else {
                    $html .= $indent.$item;
                    if ($this->_flags & phphtmllib::_NEWLINEAFTERCONTENT) {
                        $html .= "\n";
                    }
                }
            }
        }
        if ($this->_flags & phphtmllib::_COLLAPSE) {
            if ($this->_flags & phphtmllib::_NEWLINEAFTERCONTENT) {
                if ($output_debug) {
                    $html = $indent . $html . "<br>\n";
                } else {
                    $html = $indent . $html . "\n";
                }
            } else {
                $html = $indent . $html;
            }

        }
        return $html;
    }

    /**
     * This method is a nice php5 way of doing a render call.
     *
     * @return string
     */
    public function __toString() {
        return $this->render();
    }

    /***************************/
    /* DATA specific functions */
    /***************************/

    /**
     * add content onto content stack
     *
     * adds content to tag as a FIFO.
     * You can have n number of parameters.
     * each one will get added in succession to the content.
     *
     * {@source }
     *
     * @tutorial Container.cls#add
     *
     * @param   mixed   $content - either string, or tag object.
     */
    public function add(  ) {
        $args = func_get_args();
        foreach( $args as $arg ) {
            $this->_content[] = $arg;
        }
    }

    /**
     * destroy existing content and start with new content.
     *
     * {@source }
     *
     * @param   mixed   $content    can be tag object, or raw (string).
     */
    public function reset_content( ) {
        $this->_content = array();
        $args = func_get_args();
        call_user_func_array( array(&$this, "add"), $args);
    }

    /**
     * counts the number of content objects
     *
     * {@source }
     * @return  int
     */
    public function count_content( ) {
        return count($this->_content);
    }

    /**
     * get the nth element from content array
     *
     * {@source }
     *
     * @param   int   $cell   the cell to get
     * @return  mixed
     */
    public function &get_element( $cell ) {
        return $this->_content[$cell];
    }

    /**
     * This method is used to set the bitmask
     * flags for this tag.  It tells the
     * class how to render the tag.
     *
     * NOTE: the child class can override this
     *       to set the options
     *
     * {@source }
     *
     */
    protected function _set_flags() {
        $this->_flags = phphtmllib::_NEWLINEAFTERCONTENT | phphtmllib::_INDENT;
    }

    /**
     * function to set the indent flag
     *
     * {@source }
     *
     * @param   boolean     $flag  TRUE or FALSE
     */
    protected function set_indent_flag( $flag ) {
        if ($flag) {
            $this->_flags |= phphtmllib::_INDENT;
        } else {
            $this->_flags &= ~phphtmllib::_INDENT;
        }
    }

    /**
     * This flag gets the current value
     * of the indent flag
     *
     * {@source }
     *
     * @return boolean
     */
    protected function get_indent_flag() {
        return $this->_flags & phphtmllib::_INDENT;
    }

    /**
     * This method returns the bitflags for this object
     *
     * @return int
     */
    public function get_flags() {
        return $this->_flags;
    }

    /**
     * This function turns on the collapse flag
     *
     * {@source }
     *
     * @param boolean - the collapse flag
     * @param boolean - the indent flag
     *                  DEFAULT: TRUE;
     */
    public function set_collapse($collapse=TRUE, $indent=TRUE) {
        if ($collapse) {
            $this->_flags |= phphtmllib::_COLLAPSE;
        } else {
            $this->_flags &= ~phphtmllib::_COLLAPSE;
        }

        if (!$indent) {
            $this->set_indent_flag($indent);
            $this->_flags &= ~phphtmllib::_NEWLINEAFTERCONTENT;
        }
    }

    /**
     * returns leading indent for tag
     *
     * {@source }
     *
     * @param   int     the indentation level for this tag.
     * @return  string
     */
    protected function _render_indent($indent_level, $debug_flag=0) {
        static $_indent = array();

        //try and static cache this so we don't
        //repeat on the way back out of the stack or
        //on the same level.
        if (isset($_indent[$indent_level])) {
            return $_indent[$indent_level];
        } else {
            $indent = "";
            if ( $debug_flag && $indent_level > 0) {
                $indent_level *=2;
            }
            if ( ($this->_flags & phphtmllib::_INDENT) && $indent_level > 0) {
                $indent = str_repeat(phphtmllib::_INDENT_STR, $indent_level);
            }

            if ( $debug_flag && $indent_level > 0) {
                $indent = str_replace(phphtmllib::_INDENT_STR, phphtmllib::_HTML_SPACE, $indent);
            }

            $_indent[$indent_level] = $indent;
            return $indent;
        }
    }

    /**
     * This function will return an empty
     * string for the tag name
     *
     * @return string
     */
    public function get_tag_name() {
        return '';
    }
}

?>