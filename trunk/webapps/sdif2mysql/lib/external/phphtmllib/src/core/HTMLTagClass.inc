<?php

/**
 * Holds the HTMLTagClass
 *
 * $Id: HTMLTagClass.inc 3020 2007-10-04 03:42:02Z brianrue $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 *
 * @copyright LGPL - See LICENCE
 *
 */


/**
 * Base class for all HTML Tag classes.
 *  Tag class renders an html tag, its
 *  attributes, the content (if any),
 *  and close tag (if needed).
 *
 * @author      Walter A. Boring IV <waboring@newsblob.com>
 * @link http://phphtmllib.sourceforge.net
 * @package phpHtmlLib
 */
class HTMLTagClass extends XMLTagClass {

    /**
     * the list of tag attributes that we
     * should create a clickable link for
     * when in debug mode.
     *
     * We comment this declaration out
     * to save memory, since only a small
     * number of tags use it
     *
     * @var  array
     * @access private
     */
    //var $_debug_link_attributes = array("background");

    /**
     * The list of attributes not to render
     * if $GLOBALS["HTML_RENDER_TYPE"] is "XHTML STRICT"
     *
     * We comment this declaration out
     * to save memory, since only a small
     * number of tags use it
     *
     */
    //var $_xhtml_strict_attributes = array();


    /**
     * The list of attributes that we want to run
     * htmlentities() on if we are in XHTML_STRICT
     * mode.  Otherwise the validator complains about
     * html characters such as &.
     *
     * We comment this declaration out
     * to save memory, since only a small
     * number of tags use it
     *
     * @var array.
     * @access private
     */
    //var $_htmlentities_attributes = array();


    /**
     * Class Constructor
     *
     * {@source }
     *
     * @param   array - Associative array of
     *                  name="value" pairs of
     *                  tag atributes.
     *                  ie array("border"=>0, "class"=>"hover");
     *
     * @param   mixed   You can have any number
     *                  of parameters that will
     *                  be added to the content
     *                  of the tag automatically.
     */
    function __construct( array $attributes=NULL ) {
        if ($attributes !== NULL) {
            $this->set_tag_attributes( $attributes );
        }

        //set the default tag options
        //$this->_set_flags();

        //add the content if any.
        $num_args = func_num_args();

        //try and see if arg 3 is an array
        //to speed up things a tad.
        if ($num_args > 1) {
            $arg = func_get_arg(1);
            if (is_array($arg)) {
                $this->_content = $arg;
            } else {
                for ($i=1;$i<$num_args;$i++) {
                    $this->add(func_get_arg($i));
                }
            }
        }

        //what version of html is this tag going to
        //be rendered as?
        //this is a magic test.  It assumes that
        //someone has created the define for
        //HTML_RENDER_TYPE
        if ( isset($GLOBALS['HTML_RENDER_TYPE']) &&
             ($GLOBALS['HTML_RENDER_TYPE'] == phphtmllib::XHTML ||
             $GLOBALS['HTML_RENDER_TYPE'] == phphtmllib::XHTML_STRICT) ) {
            $this->_flags |= phphtmllib::_XHTMLCOMPLIANT;

        }

        //if the tag is depricated
        //we raise an alert.
        if ( $this->_flags & phphtmllib::_DEPRICATED ) {
            trigger_error(htmlspecialchars($this->_tag) . ' has been depricated in HTML 4.0', E_USER_NOTICE);
        }
    }

    /**
     * Renders the tag, attributes, content and close tag.
     *
     * {@source }
     *
     * @param   int    $indent_level    the indentation level for this tag.
     * @param  boolean output in html viewable mode
     * @return  string
     */
    public function render($indent_level=0, $output_debug=0) {

        //try and guess the indentation flags
        //based on the data
        $this->_prepare_flags();

        $html = $this->_render_tag($indent_level, $output_debug);

        if ( $this->_flags & phphtmllib::_CONTENTREQUIRED) {
            $html .= $this->_render_content($indent_level, $output_debug);
        }
        if ( $this->_flags & phphtmllib::_CLOSETAGREQUIRED ) {
            $html .= $this->_render_close_tag($indent_level, $output_debug);
        }

        return $html;
    }

    //****************************************************************
    // HTML specific routines
    //****************************************************************

    /**
     * This function is a shorthand helper
     * to setting the style attribute on a
     * tag.
     *
     * {@source }
     *
     * @param string - the style value.
     * @return none
     */
    public function set_style( $value ) {
        $this->set_tag_attribute('style', $value);
    }

    /**
     * This function is a shorthand helper
     * to setting the class attribute on a
     * tag.
     *
     * {@source }
     *
     * @param string - the class value.
     * @return none
     */
    public function set_class( $value ) {
        $this->set_tag_attribute('class', $value);
    }

    /**
     * This function is a shorthand helper
     * to setting the id attribute on a
     * tag.
     *
     * {@source }
     *
     * @param string - the class value.
     * @return none
     */
    public function set_id( $value ) {
        $this->set_tag_attribute('id', $value);
    }

    //****************************************************************
    // Tag rendering routines.
    //****************************************************************

    /**
     * renders the open tag. is <TABLE>
     *
     * {@source }
     * @access  private
     *
     * @param int the indentation level for this tag.
     * @return string
     */
    protected function _render_tag($indent_level, $output_debug=0) {
        if ( $output_debug ) {
            //lets call the special render tag debug function
            return $this->_render_tag_debug( $indent_level );
        } else {
            return parent::_render_open_tag($indent_level, $this->_flags & phphtmllib::_XHTMLCOMPLIANT);
        }
    }

    /**
     * Renders all of the content.
     * Content can be raw strings, or tag objects.
     *
     * {@source }
     * @access private
     *
     * @param int the indentation level for this tag.
     * @return  string
     */
    protected function _render_content($indent_level, $output_debug=0) {
        if ( $output_debug ) {
            return $this->_render_content_debug( $indent_level );
        } else {
            return parent::_render_content( $indent_level, $output_debug);
        }
    }

    /**
     * Renders the close tag (if needed)
     *
     * {@source }
     * @access private
     *
     * @param int the indentation level for this tag.
     * @return string
     */
    protected function _render_close_tag($indent_level, $output_debug=0) {
        if ( $output_debug ) {
            return $this->_render_close_tag_debug( $indent_level );
        } else {
            return parent::_render_close_tag($indent_level);
        }
    }


    /**
     * This renders that open tag in debug mode.
     * We do this as a seperate function,
     * so we can override this by the child
     * tag, so it can add a link on content or
     * one of the attributes.
     *
     * {@source }
     * @access private
     *
     * @param int the indentation level
     * @return string
     */
    protected function _render_tag_debug($indent_level) {

        $indent = $this->_render_indent($indent_level, TRUE);

        $tag_prefix = htmlspecialchars( (@$this->_tag_prefix ? $this->_tag_prefix : phphtmllib::_TAG_PREFIX));
        $tab_postfix = htmlspecialchars( (@$this->_tag_postfix ? $this->_tag_postfix : phphtmllib::_TAG_SUFFIX));
        $str = $indent . $tag_prefix. '<span class="purple" style="white-space:nowrap;">';
        $str .= $this->_tag . '</span>';

        if ( ($this->_flags & phphtmllib::_XHTMLCOMPLIANT) && !($this->_flags & phphtmllib::_ALWAYS_UPPERCASE) ) {
            //we have to have the tag name be lower case.
            $str = strtolower( $str );
        }

        if (is_array($this->_attributes)) {
            foreach( $this->_attributes as $name => $value) {
                $str .= $this->_build_attribute_string_debug($name, $value);
            }
        }

        //if we want to output xhtml compliant code, we have to
        //render a special tag closing.
        if ( $this->_flags & phphtmllib::_XHTMLCOMPLIANT ) {
            //we have to render a special close for the
            //open tag, if the tag doesn't require a close
            //tag or content.
            if ( !($this->_flags & phphtmllib::_CLOSETAGREQUIRED) && !($this->_flags & phphtmllib::_NOFINISHSLASHXHTML) ) {
                $html = $str . '&nbsp;/&gt;';
            } else {
                $html = $str . '&gt;';
            }
        } else {
            $html = $str . '&gt;';
        }

        if ( $this->_flags & phphtmllib::_NEWLINEAFTEROPENTAG ) {
            $html .= "<br>\n";
        }
        return $html;
    }

    /**
     * This renders the content in debug mode.
     * lets us wrap the content w/ a <nobr></nobr>
     * so it acts like view source.
     *
     * Content can be raw strings, or tag objects.
     *
     * {@source }
     * @access private
     *
     * @param int the indentation level for this tag.
     * @return string
     */
    protected function _render_content_debug($indent_level) {

        $html = '';
        //walk through the content
        $count = count($this->_content);
        for ($x=0; $x<=$count; $x++) {
            $item = &$this->_content[$x];
            if (is_object($item) && method_exists($item, 'render')) {
                if (($this->_flags & _COLLAPSE) && method_exists($item, 'set_collapse')) {
                    $item->set_collapse(TRUE, FALSE);
                }
                if ($indent_level == phphtmllib::INDENT_LEFT_JUSTIFY) {
                    $indent = phphtmllib::INDENT_LEFT_JUSTIFY;
                } else {
                    $indent = $indent_level + 1;
                }
                $html .= $item->render($indent, TRUE);
            } else {
                if ($this->_flags & phphtmllib::_COLLAPSE) {
                    $html .= htmlspecialchars($item);
                } else {
                    if ($indent_level == phphtmllib::INDENT_LEFT_JUSTIFY) {
                        $indent = phphtmllib::INDENT_LEFT_JUSTIFY;
                    } else {
                        $indent = $indent_level + 1;
                    }
                    $indent = $this->_render_indent($indent, TRUE);
                    if ( $this->_flags & phphtmllib::_NEWLINEAFTEROPENTAG ) {
                        $item = htmlspecialchars($item);
                        $item = str_replace("\n", "<br>\n" . $indent, $item);
                        $html .= $indent . '<span style="white-space:nowrap">' .$item . "</span><br>\n";
                    } else {
                        $item = htmlspecialchars($item);
                        $item = str_replace("\n", "<br>\n" . $indent, $item);
                        $html .= $item;
                    }
                }
            }
        }
        return $html;
    }

    /**
     * this renders the close tag in debugging mode.
     *
     * {@source }
     * @access private
     *
     * @param int the indentation level for this tag.
     * @return string
     */
    protected function _render_close_tag_debug( $indent_level ) {

        $indent ="";
        if ( ($this->_flags & phphtmllib::_INDENT) && ($this->_flags & phphtmllib::_NEWLINEAFTEROPENTAG) ) {
            $indent = $this->_render_indent($indent_level, TRUE);
        }
        $str = $indent . '&lt;/' . '<span class="purple">';
        $str .= $this->_tag . '</span>&gt;';

        if ( $this->_flags & phphtmllib::_XHTMLCOMPLIANT ) {
            $str = strtolower( $str );
        }

        if ( $this->_flags & phphtmllib::_NEWLINEAFTERCLOSETAG ) {
            $str .= "<br>\n";
        }

        return $str;

    }

    //****************************************************************
    // Utility functions for attributes.
    //****************************************************************

    /**
     * this builds an attribute for a tag.
     * It also filters out any attributes
     * that shouldn't be rendered if they
     * are in the $this->_xhtml_strict_attributes
     * array and HTML_RENDER_TYPE = XHTML STRICT
     *
     * {@source }
     *
     * @param   string - $name attribute name
     * @param   mixed - $value attribute value
     * @return  the tag attribute name=value pair.
     *          to be added to the tag.
     */
    protected function _build_attribute_string($name, $value) {
        if ( isset($GLOBALS['HTML_RENDER_TYPE']) &&
             $GLOBALS['HTML_RENDER_TYPE'] == phphtmllib::XHTML_STRICT ) {

            if ((($this instanceof IMGtag) && $name == 'border') ||
                ($this instanceof FORMtag) && ($name == 'name' || $name == 'target')) {
                return NULL;
            }

            //if (@in_array($name, $this->_xhtml_strict_attributes)) {
            //    return NULL;
            //}

            if (!is_int($name)) {
                //We do this because XHTML STRICT complains about
                //html characters such as &.  So we mask them.
                $value = htmlspecialchars($value);
            }

        }

        //hack to make non name-value pair work.
        //ie <option name=foo value=bar CHECKED>
        if ( ((int)$name - 0) === $name) {
            $returnval = ' '.$value;
        } else if ( $value === NULL ) {
            $returnval = ' '.$name;
        } else {
            $returnval= ' '.$name.'="'.$value.'"';
        }

        return $returnval;
    }

    /**
     * The debug version of _build_attribute_string
     *
     * {@source }
     *
     * @param   string - $name attribute name
     * @param   mixed - $value attribute value
     * @return  the tag attribute name=value pair.
     *          to be added to the tag.
     */
    protected function _build_attribute_string_debug($name, $value) {
        //hack to make non name-value pair work.
        //ie <option name=foo value=bar CHECKED>
        if ( is_int($name) ) {
            $returnval = ' <span class="black">' . $value . '</span>';
        } else if ( $value === NULL ) {
            $returnval = ' <span class="black">' . $name . '</span>';
        } else {
            if ( $name == 'href' ||  $name == 'src' ) {
                //lets create a clickable link for the value
                //of this attribute
                $value = '<a href="' . $value . '">' . $value . '</a>';
                $returnval = ' <span class="black">' . $name . '=</span><span class="blue">"' . $value . '"</span>';
            } else {
                $returnval = ' <span class="black">' . $name . '=</span><span class="blue">"' . $value . '"</span>';
            }
        }

        if ( $GLOBALS['HTML_RENDER_TYPE'] == phphtmllib::XHTML_STRICT &&
             @in_array($name, $this->_xhtml_strict_attributes) ) {
            $returnval = NULL;
        }

        return $returnval;
    }

    //****************************************************************
    // Misc functions
    //****************************************************************

    /**
     * This function checks to see if
     * there is only 1 content data, and
     * its not an object, then it auto
     * sets some of the indentation flags
     *
     * {@source }
     * @access private
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
                $this->_flags &= ~phphtmllib::_NEWLINEAFTEROPENTAG;
            }
        }
    }

}
?>
