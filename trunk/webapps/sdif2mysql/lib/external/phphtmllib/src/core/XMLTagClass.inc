<?php
/**
 * The XMLTagClass declaration.
 * 
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */


/**
 *
 * This class is used for building and rendering
 * an XML tag.
 *
 * This class is the base class for the
 * HTMLTagClass.
 *
 * This is part of the phphtmllib libraries
 * released under the LGPL license.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
class XMLTagClass extends Container {

    /**
     * Tag definition for class.
     * subclass defines this value.
     * ie var $tag = "<TABLE>";
     * @var  string
     */
    protected $_tag = "";

    /**
     * Tag attributes as an array
     * of name value pairs.
     * ie $attributes["cellspacing"]=2;
     * @var  array
     */
    //protected $_attributes = array();

    /**
     * The default XML flags
     */
    protected $_flags = phphtmllib::_FLAGS_DEFAULT_XMLTAG;

    /**
     * Holds tag attributes as an
     * array of key=>value
     *
     * @var array
     */
    protected $_attributes = null;

    /**
     * Holds tag content. This could be
     * a string or another object
     *
     * @var mixed
     */
    protected $_content = null;

    /**
     * The constructor
     *
     * {@source }
     *
     * @tutorial XMLTagClass.cls#example
     *
     * @param string - the tag name
     * @param array - the attributes array
     *                can be in name => value
     *                or just value
     * @param mixed - n items of content to add
     *
     */
    public function __construct($name, array $attributes=NULL ) {
        $this->set_tag_name( $name );
        if ($attributes !== NULL) {
            $this->set_tag_attributes( $attributes );
        }

        $num_args = func_num_args();

        //try and see if arg 3 is an array
        //to speed up things a tad.
        if ($num_args > 2) {
            $arg = func_get_arg(2);
            if (is_array($arg)) {
                $this->_content = $arg;
            } else {
                for ($i=2;$i<$num_args;$i++) {
                    $this->add(func_get_arg($i));
                }
            }
        }

        //$this->_set_flags();
    }

    /**
     * This is a help factory method
     * for building XML tags
     *
     * @param string - the tag name
     * @param array - the attributes array
     *                can be in name => value
     *                or just value
     * @param mixed - n items of content to add
     * @return XMLTagClass object
     */
    public static function factory($name, $attributes=NULL) {
        $num_args = func_num_args();
        if ($num_args > 2) {
            $arg_list = func_get_args();
            array_shift($arg_list);
            array_shift($arg_list);
            $tag = new XMLTagClass($name, $attributes,
                                   $arg_list);
        } else {
            $tag = new XMLTagClass($name, $attributes);
        }

        return $tag;
    }

    /**
     * This function is responsible
     * for rendering the tag and
     * its contents
     *
     * {@source }
     *
     * @param int - the current indentation
     *              level for the tag
     */
    public function render( $indent_level=0, $output_debug=0 ) {

        //try and guess the indentation flags
        //based on the data
        $this->_prepare_flags();

        //return $xml;
        return $this->_render_open_tag( $indent_level ) .
               $this->_render_content( $indent_level ) .
               $this->_render_close_tag( $indent_level );
    }

    /****************************************/
    /* Some helper routines for building    */
    /* pieces of the xml tag, its           */
    /* attributes and PCDATA                */
    /****************************************/

    /**
     * This method is used to set the bitmask
     * flags for this tag.  It tells the
     * class how to render the tag.
     *
     * NOTE: the child class can override this
     *       to set the options
     */
   // protected function _set_flags() {
        //parent::_set_flags();
        //$this->_flags |= phphtmllib::_NEWLINEAFTEROPENTAG |
        //                 phphtmllib::_NEWLINEAFTERCLOSETAG |
        //                 phphtmllib::_CONTENTREQUIRED |
        //                 phphtmllib::_CLOSETAGREQUIRED;
    //}

    /**
     * This method sets the name of the tag
     *
     * {@source }
     *
     * @param string - the tag name
     */
    public function set_tag_name( $name ) {
        $this->_tag = $name;
    }

    /**
     * This method gets the name of the tag
     *
     * {@source }
     *
     * @return string - the tag name
     */
    public function get_tag_name() {
        return $this->_tag;
    }

    /**
     * add a single attribute (name="value")
     *
     * {@source }
     *
     * @param   string  $name   attribute name
     * @param   mixed   $value  the value.
     * @return none
     */
    public function set_tag_attribute( $name, $value=NULL ) {
        if (!$value) {
            $value = $name;
        }
        $this->_attributes[$name] = $value;
    }

    /**
     * add multiple attributes (name="value")
     *
     * {@source }
     *
     * @param   array   $attributes Associative array of name="value" pairs of
     *                              tag atributes.
     *                              ie array("border"=>"0", "class"=>"hover");
     * @return none
     */
    public function set_tag_attributes( array $attributes=array() ) {
        if (!isset($this->_attributes)) {
            $this->_attributes = array();
        }
        $this->_attributes = array_merge($this->_attributes, $attributes);
    }

    /**
     * This method allows you to get the value for
     * a tag attribute.
     *
     * @param string the attribute you want to find
     * @return mixed.  FALSE if there is no attribute set.
     */
    public function get_tag_attribute($attribute) {
        if (!array_key_exists($attribute, $this->_attributes)) {
            return FALSE;
        } else {
            return $this->_attributes[$attribute];
        }
    }

    /**
     * clear all attributes and start with new attributes
     *
     * {@source }
     *
     * @param   array   Associative array of name="value" pairs of
     *                  tag atributes.
     *                  ie array("border"=>"0", "class"=>"hover");
     * @return void
     */
    public final function reset_attributes( array $attributes=array() ) {
        $this->_attributes = array();
        $this->set_tag_attributes( $attributes );
    }

    /**
     * get the nth element from content array
     *
     * NOTE:
     *    This has been made public in the Container
     *
     * {@source }
     *
     * @param   int   $cell   the cell to get
     * @return  mixed
     */
    protected function &_get_element( $cell ) {
        return $this->get_element($cell);
    }

    //****************************************************************
    // Misc functions
    //****************************************************************

    /**
     * set the newline_after_opentag flag
     *
     * {@source }
     *
     * @param   boolean TRUE or FALSE
     * @return none
     */
    public function set_newline_after_opentag( $flag ) {
        if ($flag) {
            $this->_flags |= phphtmllib::_NEWLINEAFTEROPENTAG;
        } else{
            $this->_flags &= ~phphtmllib::_NEWLINEAFTEROPENTAG;
        }
    }

    /**
     * set the newline_after_content flag
     *
     * {@source }
     *
     * @param   boolean TRUE or FALSE
     * @return none
     */
    public function set_newline_after_closetag( $flag ) {
        if ($flag) {
            $this->_flags |= phphtmllib::_NEWLINEAFTERCLOSETAG;
        } else{
            $this->_flags &= ~phphtmllib::_NEWLINEAFTERCLOSETAG;
        }
    }

    /**
     * This method turns on the automatic wrapping
     * of the tag's content inside the CDATA wrapper
     * for XML
     *
     * {@source }
     * @param   boolean     $flag   TRUE or FALSE
     * @return none
     */
    public function set_cdata_flag($flag) {
        if ($flag) {
            $this->_flags |= phphtmllib::_CDATACONTENTWRAP;
            $this->set_collapse(TRUE);
        } else{
            $this->_flags &= ~phphtmllib::_CDATACONTENTWRAP;
        }
    }

    /**
     * This function turns on the collapse flag
     *
     * {@source }
     *
     * @param boolean - the collapse flag
     * @param boolean - the indent flag
     *                  DEFAULT: TRUE;
     * @return none
     */
    public function set_collapse($collapse=TRUE, $indent=TRUE) {
        if ($collapse) {
            $this->_flags |= phphtmllib::_COLLAPSE;
        } else {
            $this->_flags &= ~phphtmllib::_COLLAPSE;
        }

        $this->set_newline_after_opentag(FALSE);
        $this->set_indent_flag($indent);
        if ($indent) {
            $this->set_newline_after_closetag(TRUE);
        } else {
            $this->set_newline_after_closetag(FALSE);
        }
    }

    /**
     * This function checks to see if
     * there is only 1 content data, and
     * its not an object, then it auto
     * sets some of the indentation flags
     *
     * {@source }
     * @return none
     */
    protected function _prepare_flags() {
        if ($this->_flags & phphtmllib::_CONTENTREQUIRED) {
            if ($this->count_content() == 1) {
                if (!is_object($this->_content[0])) {
                    //ok looks like this object has only
                    //1 data for content and its a string.
                    if ( !strstr($this->_content[0], "\n") ) {
                        $this->_flags &= ~phphtmllib::_NEWLINEAFTEROPENTAG;
                    }
                }
            } else if ($this->count_content() == 0) {
                $this->_flags &= ~(phphtmllib::_CONTENTREQUIRED | phphtmllib::_CLOSETAGREQUIRED);
            }
        }
    }

    /****************************************/
    /* Some helper methods for rendering    */
    /* the output xml tree.                 */
    /****************************************/

    /**
     * this function is responsible for
     * rendering the open tag.
     *
     * {@source }
     *
     * @param int - the indent level
     * @param boolean - do we add the finish / if we have no
     *                  close tag and no content?
     * @return string
     */
    protected function _render_open_tag( $indent_level, $finish_slash=TRUE ) {
        //get the indent level
        $indent = $this->_render_indent( $indent_level );

        //build the tag
        if ($this->_flags & phphtmllib::_ALWAYS_LOWERCASE) {
            $this->_tag = strtolower($this->_tag);
        } else if ($this->_flags & phphtmllib::_ALWAYS_UPPERCASE) {
            $this->_tag = strtoupper($this->_tag);
        }
        //save on mem
        $xml = $indent . ((isset($this->_tag_prefix) && $this->_tag_prefix) ? $this->_tag_prefix : phphtmllib::_TAG_PREFIX) . $this->_tag;

        if ($this->_attributes) {
            foreach( $this->_attributes as $name => $value) {
                $xml .= $this->_build_attribute_string($name, $value);
            }
        }


        if ( !($this->_flags & phphtmllib::_CLOSETAGREQUIRED) && !($this->_flags & phphtmllib::_NOFINISHSLASHXHTML)
             && $finish_slash ) {
            $xml .= ' /'.(isset($this->_tag_postfix) ? $this->_tag_postfix : phphtmllib::_TAG_SUFFIX);
        } else {
            $xml .= (isset($this->_tag_postfix) ? $this->_tag_postfix : phphtmllib::_TAG_SUFFIX);
        }

        if ($this->_flags & phphtmllib::_NEWLINEAFTEROPENTAG) {
            $xml .= "\n";
        }
        return $xml;
    }

    /**
     * this function is reponsible for
     * rendering the pcdata, or content
     * of the tag (if any)
     *
     * {@source }
     *
     * @param int - the indent level
     * @return string
     */
    protected function _render_content( $indent_level, $output_debug=0 ) {

        //walk through the content
        $xml = '';
        $count = count($this->_content);
        for ($x=0; $x<$count; $x++) {
            $item = &$this->_content[$x];
            if (is_object($item) && method_exists($item, 'render')) {
                if (($this->_flags & phphtmllib::_COLLAPSE) && method_exists($item, 'set_collapse')) {
                    $item->set_collapse(TRUE, FALSE);
                }
                if ($indent_level == phphtmllib::INDENT_LEFT_JUSTIFY) {
                    $indent = phphtmllib::INDENT_LEFT_JUSTIFY;
                } else {
                    $indent = $indent_level + 1;
                }
                $xml .= $item->render($indent, $output_debug);
            } else {
                if ($this->_flags & phphtmllib::_COLLAPSE) {
                    $xml .= $item;
                } else {
                    if ($indent_level == phphtmllib::INDENT_LEFT_JUSTIFY) {
                        $indent = phphtmllib::INDENT_LEFT_JUSTIFY;
                    } else {
                        $indent = $indent_level + 1;
                    }
                    $indent = $this->_render_indent($indent);
                    if ($this->_flags & phphtmllib::_NEWLINEAFTEROPENTAG) {
                        $item = str_replace("\n", "\n" . $indent, $item);
                        $xml .= $indent . $item . "\n";
                    } else {
                        $item = str_replace("\n", "\n" . $indent, $item);
                        $xml .= $item;
                    }
                }
            }
        }
        if ($this->_flags & phphtmllib::_CDATACONTENTWRAP) {
            if ($this->_flags & phphtmllib::_COLLAPSE) {
                $xml = '<![CDATA[' . $xml . ']]>';
            } else {
                $indent = $this->_render_indent($indent+1);
                $indent1 = $this->_render_indent($indent+2);
                $indent2 = $this->_render_indent($indent+3);
                $xml = "\n".$indent1."<![CDATA[\n".$xml."\n".$indent1."]]>\n".$indent;
            }

        }
        return $xml;
    }

    /**
     * this function is reposnsible for
     * rendering the closing tag (if any)
     *
     * {@source }
     *
     * @param int - the indent level
     * @return string
     */
    protected function _render_close_tag( $indent_level ) {
        if (!($this->_flags & phphtmllib::_CLOSETAGREQUIRED)) {
            return '';
        }

        $indent = "";
        if (($this->_flags & phphtmllib::_INDENT) && ($this->_flags & phphtmllib::_NEWLINEAFTEROPENTAG)) {
            $indent = $this->_render_indent($indent_level);
        }
        $str = $indent . '</' . $this->_tag . '>';

        if ($this->_flags & phphtmllib::_NEWLINEAFTERCLOSETAG) {
            $str .= "\n";
        }

        return $str;
    }

    /**
     * this builds an attribute for an XML tag.
     * XML attributes MUST have a name AND a
     * value.
     *
     * {@source }
     *
     * @param   string - $name attribute name
     * @param   mixed - $value attribute value
     * @return  the tag attribute name=value pair.
     *          to be added to the tag.
     */
    protected function _build_attribute_string($name, $value) {
        return ' '.$name.'="'.$value.'"';
    }

}

?>