<?php

/**
 * This contains the TextNav widget
 *
 * $Id: TextCSSNav.inc 2739 2007-05-16 06:03:55Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 *
 */


/**
 * This class builds a simple text navigational
 * widget.
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */
class TextCSSNav extends HTMLWidget {

    /**
     * Flag to tell us that we can
     * highlight (css) the selected
     * link.
     *
     * This is off by default
     */
    private $_highlight_selected = FALSE;

    /**
     * Holds which one is auto selected
     *
     */
    private $_selected = 0;

    /**
     * the prefix for the query string var
     * so we can have multiple widgets
     * on the same page and have them
     * operate independantly
     */
    private $_query_prefix = "";

    /**
     * flag to tell us if we should add
     * the selected query var or not
     * to the urls
     */
    private $_show_selected = TRUE;


    /**
     * Constructor for this class
     * It just sets the width for the
     * widget.
     *
     * @param int $width - the width of the widget
     */
    public function __construct($highlight_selected=FALSE) {
        parent::__construct();
        $this->_highlight_selected = $highlight_selected;
    }

    /**
     * This function is used to enable/disable the
     * addition of the selected link
     *
     * @param boolean $show_selected
     */
    public function show_selected($show_selected=TRUE) {
        $this->_show_selected = $show_selected;
    }

    /**
     * function that will render the widget.
     *
     * @param int - the indentation level for
     *              the container.
     * @param int - the output debug flag to
     *              maintain compatibility w/ the API.
     *
     * @return string the raw html output.
     */
    public function render( $indent_level=1, $output_debug=0) {
        $this->_selected = @$_REQUEST[$this->_query_prefix."textcssnavselected"];
        $div = html_div("textnav", $this->_build_links());
        return $div->render( $indent_level, $output_debug );
    }


    /**
     * This method is used to set the prefix for
     * the widget so someone can have multiple
     * widgets on the same page and have them
     * operate independantly
     *
     * @param string - the prefix for the query var
     */
    public function set_prefix( $prefix ) {
        $this->_query_prefix = $prefix;
    }


    //functions for adding/updating data

    /**
     * this function adds a clickable link.
     * It automatically adds the link based on $url,
     * with $text as the viewable text.
     *
     * @param string - the url for the link
     * @param string - the link text
     * @param string - the title text
     * @param string - the link target
     */
    public function add($url, $text, $title="", $target="", $selected=FALSE) {
        array_push($this->data, array("type"=>"url", "url"=>$url,
                                      "text"=>$text, "title"=>$title,
                                      "target"=>$target,
                                      "selected"=> $selected));
    }


    /**
     * This lets you add a blank entry
     * between 2 links
     *
     * @param int - the # of blank lines to insert
     */
    public function add_blank( $num = 1 ) {
        for ( $x=1; $x<=$num; $x++ )
            array_push($this->data, array( "type"=>"blank" ));
    }

    /**
     * this adds a text item in the nav
     *
     * @param string - the text to display
     */
    public function add_text( $text ) {
        array_push($this->data, array( "type"=>"text", "text"=>$text ));
    }

    /**
     * This function is used to build the links
     * to click on
     *
     * @return Container
     */
    protected function _build_links() {
        $container = Container::factory();
        $container->set_collapse();

        $is_first = TRUE;
        $cnt = 1;
        foreach( $this->data as $nav ) {
            switch ( $nav["type"] ) {
            case 'url':

                $is_selected = $this->_highlight_selected && ($this->_selected == $cnt || $nav["selected"]);
                $class = $is_selected ? "selected" : "";
                if ( $is_first ) {
                    $class .= "first";
                }
                if ( !$is_selected && !$is_first ) {
                    $class = NULL;
                }

                $obj = $this->_build_link( $nav, $class, $cnt );
                $is_first = FALSE;
                $cnt++;
                break;
            case "blank":
                $obj = "&nbsp;";
                break;

            case 'text':
                $obj = $nav['text'];
                break;
            }
            $container->add( $obj );
        }

        return $container;
    }


    /**
     * This method actually builds an individual link
     *
     * @param array the link information
     * @param the css class to use
     * @return Atag object
     */
    protected function _build_link( $nav, $class, $cnt ) {
        $url = $nav["url"];
        if ( $this->_highlight_selected ) {


            if ($this->_show_selected) {
                if ( !strstr($url, "?") ) {
                    $url .= "?";
                }
                $url .= "&".$this->_query_prefix."textcssnavselected=".$cnt;
            }

        }
        $link = html_a(htmlentities($url), $nav["text"], "normal", $nav["target"], $nav["title"]);
        if ( !is_null($class) ) {
            $link->set_class( $class );
        }

        return $link;
    }
}
?>
