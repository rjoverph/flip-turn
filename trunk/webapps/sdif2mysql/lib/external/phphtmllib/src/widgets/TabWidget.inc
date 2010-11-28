<?php
/**
 * Holds the TabWidget and Tablist
 *
 * $Id: TabWidget.inc 2740 2007-05-16 06:04:11Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * This class implements the Qualys Tab object.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */
class TabWidget extends HTMLWidget {

    const TABLIST_SELECTED = 'tab_selected';
    const TABLIST_SUB_SELECTED = 'subtab_selected';

    /**
     * Is this tab selected or not?
     */
    protected $_selected = false;

    /**
     * The tab number in the list of tabs.
     */
    protected $_number = 0;

    /**
     * The constructor
     *
     * {@source }
     *
     * @param string the title for the Tab
     */
    public function __construct($title) {
        parent::__construct();
        $this->set_title($title);
    }


    /**
     * This is the function where you
     * can build the content for the Tab itself.
     *
     * The alternative is to use the add() method.
     *
     * {@source }
     * @return Container object
     */
    public function content() {
        return null;
    }

    /**
     * This method creates the name of the tab
     *
     * @param string - the tab display string
     * @return string - the tab name
     */
    public function name($title) {
        $name = strtolower($title);
        $len = strlen($name);

        for ($i=0; $i<$len;$i++) {
            if ((ord($name[$i])<97 || ord($name[$i])>122) &&
                (ord($name[$i])<48 || ord($name[$i])>57))
                $name[$i] = "_";
        }
        return $name;
    }


    /**
     * This method builds the query string
     * 'tab_selected=<name>' for you
     * to place in a url
     *
     * @param string - the tab title
     * @param boolean - is this a subtab?
     * @return string - the query var assigned to tab name
     */
    public function queryvar($title, $subtab_flag=false) {
        if ($subtab_flag) {
            $prefix = TabWidget::TABLIST_SUB_SELECTED."=";
        } else {
            $prefix = TabWidget::TABLIST_SELECTED."=";
        }
        return $prefix.TabWidget::name($title);
    }
}

?>
