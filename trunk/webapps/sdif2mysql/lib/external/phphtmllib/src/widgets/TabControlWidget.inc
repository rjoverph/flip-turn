<?php
/**
 * This file contains the TabControlWidget class
 *
 * $Id: TabControlWidget.inc 2739 2007-05-16 06:03:55Z hemna $
 *
 * @author Culley Harrelson <culley@fastmail.fm>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 *
 */

/**
 * This class is used for creating a tab control panel.
 *
 * the tab buttons are generated with overlapping background images that grow
 * and shrink depending on the length of text.
 *
 * @author Culley Harrelson <culley@fastmail.fm>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 *
 * @link http://alistapart.com/articles/slidingdoors/
 * @link http://alistapart.com/articles/slidingdoors2/
 * @todo figure out a way to hook in a css tab that joins the tab control.  I was having trouble making it work and gave up after a few hours.
 */

class TabControlWidget extends HTMLWidget {

    protected $_tabs = array();
    protected $_align;
    protected $_title;

    /**
     * This is the constructor for the TabControlWidget object.
     *
     * @param string - a title string displayed on the opposite side
     * @param string - right or left-- how to align the tab control
     * @todo figure out center alignment
     */
    public function __construct($title=NULL, $align='left') {
        parent::__construct();
        $this->_title = $title;
        $this->_align = $align;
        if (!$this->_align == 'right') {
        }
    }

    /**
     * add a tab.
     *
     * @param ATag - an anchor tag object used for the tab link
     * @param boolean whether or not the tab is the selected tab
     */
    public function add_tab($href, $selected=FALSE) {
        $this->_tabs[] = array("href" => $href,
                               "selected" => $selected
                               );
    }

    /**
     * render the widget
     *
     */
    public function render($indent_level=1, $output_debug=0) {
        $ul = html_ul();
        if ($this->_align == 'right') {
            $ul->set_style('float: right;');
            $tabs = array_reverse($this->_tabs);
            $tabs = $this->_tabs;
        }

        foreach ($this->_tabs as $tab) {
            $li = html_li($tab['href']);
            if ($tab['selected']) {
                $li->set_class('current');
            }
            $id = strtolower(preg_replace('/\W/', '_', $tab['href']->get_element(0))) . '_tab';
            $li->set_id($id);
            $ul->add($li);

        }

        $div = html_div('tabs', $ul);

        if (!is_null($this->_title)) {
            $div->add(phphtmllib::_HTML_SPACE);
            $div->add($this->_title);
        }
        return $div->render($indent_level, $output_debug);

    }
}




?>
