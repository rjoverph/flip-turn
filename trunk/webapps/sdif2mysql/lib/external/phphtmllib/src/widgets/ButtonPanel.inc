<?php
/**
 * $Id: ButtonPanel.inc 2735 2007-05-16 06:01:18Z hemna $
 *
 * a button panel for a dialog box window
 *
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */

/**
 * This class defines a bottom button panel for a dialog box window
 * It is a HTMLWidget child with a specific css style class and border
 * This row is separated by vertical top line
 *
 * @author Suren Markosian
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */
class ButtonPanel extends HTMLWidget {

    /**
     *  Holds all the buttons
     *
     **/
    var $data;

    /**
     *
     * @param string the width of the button panel
     * @param string the alignment.
     * @return none.
     */
    function __construct($width = "100%", $align="center") {
        parent::__construct();
        $this->set_align($align);
        $this->set_width($width);
    }

    /**
     * Push content onto the data object
     *
     * adds a button to the data
     * @param mixed $content - either string, or tag object.
     */
    function add() {
        $args = func_get_args();

        foreach($args as $content) {
            $this->_data[] = $content;
        }
    }


    /**
     * render the entire table.
     *
     */
    function render($indent_level=0, $output_debug=0) {

        $div =& $this->_build_wrapper();

        foreach ($this->_data as $button) {
            $div->add($button, phphtmllib::_HTML_SPACE);
        }

        return $div->render($indent_level, $output_debug);
    }


    /**
     * Builds the outer wrapper for the panel
     *
     * @return DIVtag object
     */
    function &_build_wrapper() {
        $div = new DIVtag(array("align"=>"center",
                                "width"=>$this->get_width(),
                                "class"=>"button_panel"
                               ));
        return $div;
    }
}
?>
