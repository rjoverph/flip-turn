<?php
/**
 * This contains the TextNav widget
 *
 * $Id: StandardDialogWidget.inc 2739 2007-05-16 06:03:55Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 *
 */

/**
 * This class is used to build a DialogWidget that
 * can have 'blocks' for messages.
 *
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */
class StandardDialogWidget extends DialogWidget {


    /**
     * Pushes a block content onto the data object
     * Each pushed block is separated by some white space
     * defined in $_block_spacing
     *
     * @param string - block title
     * @param mixed - either string, or tag object.
     * @access public
     */
    public function add_block($title, $content) {
        $this->_data[] = array("title"=>$title,
                               "content"=>$content);
    }


    /**
     * This method is used to add the message blocks
     * to the appropriate container
     *
     * @return object - the container object with the messages.
     */
    protected function _build_message_container() {
        $box = new InfoTable($this->get_title());

        //don't show the cell borders
        $box->set_show_cellborders(false);

        // add each block
        foreach ($this->_data as $block) {
            // we have a block with the title
            $box->add_row($this->_build_block($block));
        }
        return $box;
    }


    /**
     * Create a DIV that holds the title
     * and data of a block
     *
     * @return a DIVtag
     * @access private
     */
    protected function _build_block($data) {
        $div = new DIVtag();
        $div->set_style("text-align: center;");

        if (is_array($data)) {
            if (is_null($data["title"])) {
                $div->add($data["content"]);
                $block =& $div;
            } else {
                $block = FIELDSETtag::factory($data["title"], $data["content"]);
            }
        } else {
            $div->add($data);
            $block =& $div;
        }
        return $block;
    }
}
?>
