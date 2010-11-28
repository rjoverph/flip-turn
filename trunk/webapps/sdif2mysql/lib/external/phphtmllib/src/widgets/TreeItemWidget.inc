<?php
/**
 * $Id: TreeItem.inc,v 3.2 2004/08/14 23:05:20 suren Exp $
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Widget
 */


/**
 * This is the parent table class
 * that knows how to render a tree branch
 *
 * It makes use of the javascript functions
 * defined in tree.js and assumed that this
 * file has been included in the page
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Widget
 */
class TreeItemWidget extends HTMLWidget {

    /**
     * Holds the unique id of the tree item
     *
     */
    protected $_id = NULL;

    /**
     * Holds the open/closed state of the tree
     * If true, the tree is closed by default
     *
     */
    protected $_closed = false;

    /**
     * Path for images
     *
     */
    protected $img_prefix = "/images/widgets/";

    /**
     * CSS class of the title
     *
     */
    protected $_title_class = "foo";

    /**
     * If this is set to true the title
     * will be rendered in header style
     * with border-bottom and bigger font
     */
    protected $_header = false;

    /**
     * If this is set to true and _header
     * flag is true, the + and - signs for
     * expanding and collapsing all will be added
     */
    protected $_expand_all = FALSE;

    /**
     * Constructor
     *
     * @param string title
     * @param string id - unique id of tree item
     * @param boolfunct closed - whether the tree is open or closed
     */
    public function __construct($title, $id, $closed = false) {

        $this->set_title($title);

        $this->_id = $id;
        $this->_closed = $closed;
    }

    /**
     * The function for adding "data" to the
     * table
     *
     * @param mixed
     */
    public function add() {
        $args = func_get_args();
        foreach($args as $data) {
            array_push($this->data, $data);
        }
    }

    /**
     * Builds the image to expand/collapse a branch
     *
     * @return Atag
     */
    protected function _build_tree_image() {

        if ($this->_closed == false) {
            $img = html_img($this->img_prefix . "tree_open.gif", 10, 10);

        } else {
            $img = html_img($this->img_prefix . "tree_closed.gif", 10, 10);
        }

        $img->set_tag_attribute("id", "i" . $this->_id);

        return $this->_build_tree_link($img);
    }

    /**
     * Builds the link to expand/collapse a branch
     *
     * @param content of the link
     *
     * @return Atag
     */
    protected function _build_tree_link($content) {

        $link = html_a("javascript:toggle_tree('" . $this->_id . "')", $content, "form_link");
        if ($this->get_header_flag()) $link->set_style("color:white;");
        $link->set_tag_attribute("id", "l" . $this->_id);

        return $link;
    }

    /**
     * This function builds the content div for
     * the tree level
     *
     * @return DIVtag
     */
    protected function _build_tree_child() {

        if ($this->_closed) $class = "div_tree_closed";
        else $class = "div_tree";

        $attributes =array("id"=>$this->_id,
                           "class"=>$class);

        $div = new DIVtag($attributes);

        return $div;
    }


    /**
     * This function builds a clickable title/link
     * for the child tree levels
     *
     * @return DIVtag
     */
    protected function _build_tree_title() {

        if ($this->get_header_flag() == true) {
            // this is a header style title

            if ($this->get_expand_all_flag()) {

                $expand_all = html_img_href("javascript:expand_b('" . $this->_id . "')", $this->img_prefix . "expand_all.gif", 11, 11);
                $expand_all->set_class("no_print");

                $collapse_all = html_img_href("javascript:collapse_b('" . $this->_id . "')", $this->img_prefix . "collapse_all.gif", 11, 11);
                $collapse_all->set_class("no_print");

                $buttons = container(_HTML_SPACE,
                                     $expand_all,
                                     " ",
                                     $collapse_all
                                    );
            } else $buttons = NULL;

            $table = new TABLEtag(array("width"=>"100%",
                                        "style"=>"margin-bottom:4px;",
                                        "cellspacing"=>0,
                                        "cellpadding"=>0
                                       ));

            $table->add_row(new TDtag(array("width"=>"16"), $this->_build_tree_image()),
                            new TitleBox(container($this->_build_tree_link(html_b($this->get_title())),
                                                   $buttons)));

            return $table;
        } else {
            // this is a normal title
            $div_link = DIVtag::factory($this->get_title_class(), $this->_build_tree_image(),
                                 $this->_build_tree_link($this->get_title()));

            return $div_link;
        }


    }

    /**
     * render the tree branch
     *
     */
    public function render($indent_level=0, $output_debug=0) {

        $c = html_div();
        $c->set_style("padding-bottom:4px;");

        // add the tree item title
        $c->add($this->_build_tree_title());

        // build the content of the tree branch
        $child = $this->_build_tree_child();

        foreach ($this->data as $data) {

            $child->add($data);

        }

        $c->add($child);

        return $c->render($indent_level, $output_debug);
    }

    /**
     * This function sets the CSS class
     * for the tree title
     *
     * @param string class
     */
    public function set_title_class($class) {
        $this->_title_class = $class;
    }

    /**
     * This function returns the CSS class
     * of the tree title
     *
     * @return string class
     */
    public function get_title_class() {
        return $this->_title_class;
    }

    /**
     * This function sets the header style flag
     *
     * with this flag set to true the title
     * will be rendered in header style
     * with border-bottom and bigger font
     *
     * @param bool flag
     */
    public function set_header_flag($flag) {
        $this->_header = $flag;
    }

    /**
     * This function returns the header style flag
     *
     * @return bool flag
     */
    public function get_header_flag() {
        return $this->_header;
    }

    /**
     * This function sets the header style flag
     *
     * with this flag set to true the title
     * will be rendered in header style
     * with border-bottom and bigger font
     *
     * @param bool flag
     */
    public function set_expand_all_flag($flag) {
        $this->_expand_all = $flag;
    }

    /**
     * This function returns the header style flag
     *
     * @return bool flag
     */
    public function get_expand_all_flag() {
        return $this->_expand_all;
    }


} // TreeItemWidget
?>