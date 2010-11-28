<?php

/**
 * This contains the VerticalCSSNavTable widget
 *
 * $Id: VerticalCSSNavTable.inc 2739 2007-05-16 06:03:55Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 *
 */

/**
 * This class builds a nice table
 * that conains clickable cells.
 *
 *  ---------------------
 *  |      TITLE        |
 *  ---------------------
 *  |     SUBTITLE      |
 *  ---------------------
 *  |    link 1         |
 *  ---------------------
 *  |    link 2         |
 *  ---------------------
 *
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */
class VerticalCSSNavTable extends HTMLWidget {

    /**
     * the subtitle if any
     *
     * @var string
     */
    protected $_subtitle = "";


    /**
     * Holds the outer table object
     *
     * @var TABLEtag object
     */
    protected $_table = NULL;


    /**
     * Constructor for this class
     * It just sets the width for the
     * widget.
     *
     * @param int $width - the width of the widget
     */
    public function __construct($title, $subtitle="", $width="100%" ) {
        parent::__construct();
        $this->set_title( $title );
        $this->set_subtitle( $subtitle );
        $this->set_width( $width );
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
    public function render($indent_level=1, $output_debug=0) {

        $this->_table = html_table( $this->get_width() );
        $this->_table->set_class("verticalcssnav");

        $this->_build_title();

        $this->_build_links();

        return $this->_table->render( $indent_level, $output_debug );
    }


    /**
     * This sets the subtitle
     *
     * @param string - the subtitle
     */
    public function set_subtitle( $subtitle ) {
        $this->_subtitle = $subtitle;
    }

    /**
     * This function returns the current
     * subtitle.
     *
     * @return string - the subtitle
     */
    public function get_subtitle() {
        return $this->_subtitle;
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
    public function add($url, $text, $title="", $target="") {
        array_push($this->data, array("type"=>"url", "url"=>$url,
                                      "text"=>$text, "title"=>$title,
                                      "target"=>$target));
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
     * This function builds the title tr
     *
     */
    protected function _build_title() {
        $caption = html_caption( $this->get_title() );
        $this->_table->add( $caption );
    }

    /**
     * This function builds the subtitle
     * if needed.
     */
    protected function _build_subtitle() {

        $subtitle = $this->get_subtitle();
        if ($subtitle != "") {
            $div = html_div();
            $div->set_class( "subtitle" );
            $div->add( $this->get_subtitle() );
            return $div;
        } else {
            return NULL;
        }
    }


    /**
     * This function is used to build the links
     * to click on
     *
     * @return Container
     */
    protected function _build_links() {
        $container = Container::factory();

        $container->add( $this->_build_subtitle() );

        foreach( $this->data as $nav ) {
            switch ($nav["type"]) {
            case 'url':
                $a = html_a($nav["url"], $nav["text"], "", $nav["target"], $nav["title"]);
                $a->set_class("navurl");
                $container->add( $a );
                break;
            case "text":
                $div = html_div("",$nav["text"]);

                $container->add($div);
                break;
            }

        }

        $this->_table->add_row( $container );

        return $container;
    }

}

?>
