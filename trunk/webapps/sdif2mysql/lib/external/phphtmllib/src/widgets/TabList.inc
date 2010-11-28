<?php
/**
 * This file contains the TabList
 * object
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */


/**
 * This class implements a set of multiple tabs holding
 * data objects
 *
 *
 * @author Suren Markosian
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */
class TabList extends HTMLWidget {

    /**
     * The number of tabs
     */
    protected $_tab_num=0;

    /**
     * The selected tab
     * from the list
     */
    protected $_tab_selected=null;

    /**
     * array of tabs that have been added
     */
    protected $_tabs = array();

    /**
     * the TR object for the tabs
     */
    protected $_tab_row = null;

    /**
     * This holds a list of
     * name=>value vars that the
     * caller/child wants to propogate
     * automatically.
     *
     */
    protected $_save_vars = array();

    /**
     * Flag to let us know we are a subtab
     * list or not
     */
    protected $_subtab_flag = false;


    /**
     * The outer wrapper for the ui.
     * So we can build top level and
     * sublevels
     */
    protected $_ui_wrapper = null;

    /**
     * valid selected tab?
     */
    protected $_valid_tab = false;

    /**
     * array of icons that have been added
     */
    protected $_icons = array();

    /**
     * boolean to tell whether icons have been added
     */
    protected $_icon_flag = false;

    /**
     * boolean to tell whether to display line after tab
     */
    protected $_tab_line_flag = false;

    /**
     * The constructor.
     *
     * @param the title of the tablist.
     */
    public function __construct($title) {
        parent::__construct();
        $this->title = $title;
    }

    /**
     * The render method
     *
     * @param int the html indentation level
     * @param int the html debug level
     * @return string the output html
     */
    public function render( $indent_level=0, $output_debug=0 ) {
        if ($this->_subtab_flag) {
            //we need to build a subtab list
            $this->_build_subtab_ui();
        } else {
            //ok build the outer UI for the top tabs
            $this->_build_top_tab_ui();
        }

        return $this->_ui_wrapper->render($indent_level, $output_debug=0);

  }

    /**
     * Sets display line after tab
     *
     */
    public function setTabLine($display=false) {
        $this->_tab_line_flag = $display;
    }

    /**
     * This public method adds a new tab to the table
     * @param title string - tab title
     * @param data object - data container for this tab
     */
    public function add(&$tab_obj) {

        if (is_subclass_of($tab_obj, "tabwidget")) {
            //render a normal tab with its content.
            $this->_tabs[] =& $tab_obj;
        } else if (is_subclass_of($tab_obj, "tablist") ||
                   $tab_obj instanceof TabList) {
            $tab_obj->_set_subtab_flag(TRUE);
            $this->_tabs[] =& $tab_obj;
        } else {
            trigger_error(__CLASS__."::".__FUNCTION__."() - called with an invalid object (".
                          get_parent_class($tab_obj).
                          "). must be either a TabWidget or a TabList(subtab).",
                          E_USER_ERROR);
        }
    }

    /**
     * Alias for add_icon
     *
     * Note, this method name does not follow the standard method naming
     * convention and has been deprecated
     *
     * @deprecated
     * @param string $icon icon SRC to display
     * @param string $title link verbage
     * @param string $url link URL
     * @return void
     */
    public function addicon($icon, $title, $url) {
        return $this->add_icon($icon, $title, $url);
    }

    /**
     * This public method adds a new tab icon to the table
     *
     * @param string $icon icon SRC to display
     * @param string $title link verbage
     * @param string $url link URL
     * @param string $width width of icon image
     * @param string $height height of icon image
     * @param string $onclick onclick javascript event handler for a tag
     * @return void
     */
    public function add_icon($icon, $title, $url, $width = '', $height = '', $onclick = '') {
        $this->_icons[] = array('icon' => $icon,
                                'title' => $title,
                                'url' => $url,
                                'width' => $width,
                                'height' => $height,
                                'onclick' => $onclick);
        $this->_icon_flag = true;
    }

    /**
     * Return the title
     */
    public function get_title() {
        return $this->title;
    }

    /**
     * This function sets the save variables
     * that the user/child wants to automatically
     * propogate
     *
     * @param array - name=>value pairs of the data
     *                that they want to propogate
     */
    public function set_save_vars( $vars ) {
        $this->_save_vars = $vars;
    }

    /**
     * this function builds a partial
     * query string with the
     * $this->_save_vars
     *
     * @return string
     */
    protected function _build_save_vars() {
        $query_string = "";
        foreach( $this->_save_vars as $name => $value ) {
            $query_string .= $name."=".$value."&";
        }
        return $query_string;
    }


    /**
     * this private function builds the url
     * for the main tab script and adss the
     * needed query string params
     *
     * @param string - the tab name
     * @param string - the subtab name
     *
     * @return string url
     */
    protected function _build_url($tab_name, $subtab_name=null) {
        $url = $_SERVER["SCRIPT_NAME"]."?".TabWidget::TABLIST_SELECTED."=".$tab_name."&";
        if ($subtab_name !== null) {
            $url .= TabWidget::TABLIST_SUB_SELECTED."=".$subtab_name."&";
        }
        $url .= $this->_build_save_vars();
        return $url;
    }

    /**
     * This method is used to set the
     * subtab bit
     *
     * @param boolean
     */
    protected function  _set_subtab_flag($flag) {
        $this->_subtab_flag = $flag;
    }

    /**
     * This method creates the name of the tab
     *
     * @param string - the tab display string
     * @return string - the tab name
     */
    public static function name($title) {
        return TabWidget::name($title);
    }


    /**
     * This method builds the query string
     * 'tab_selected=<name>' for you
     * to place in a url
     *
     * @param string - the tab title
     * @return string - the query var assigned to tab name
     */
    public static function queryvar($title) {
        return TabWidget::queryvar($title);
    }


    /**
     * This method builds the outer wrapper UI
     * for the top level tab list.
     *
     * @return none
     */
    protected function _build_top_tab_ui() {
        // initialize selected tab number
        if (isset($_REQUEST[TabWidget::TABLIST_SELECTED]))
            $this->_tab_selected = $_REQUEST[TabWidget::TABLIST_SELECTED];

        $this->_tab_row = new TRtag();

        $this->_ui_wrapper = html_table();
        $this->_ui_wrapper->set_class('tablist');

        $this->tab_num = count( $this->_tabs );
        // create data row and add data to it
        $tr = new TRtag();
        $colspan = 2*$this->tab_num+1;
        $data_td = new TDtag(array("class"=>"tab_data","colspan"=>$colspan));

        foreach( $this->_tabs as $tab_obj ) {
            $title = $tab_obj->get_title();
            $tab_name = $this->name($title);
            $this->_build_tab($title, $tab_name);

            // separator between two tabs
            $this->_add_tab_spacer();

            if ($tab_name==$this->_tab_selected) {
                if (is_subclass_of($tab_obj, "tablist") ||
                    $tab_obj instanceof TabList) {
                    $this->_valid_tab = TRUE;
                    $data_td->add( $tab_obj );
                } else {
                    $this->_valid_tab = TRUE;
                    $data_td->add( $tab_obj->content() );
                }
            }
        }

        if (!$this->_valid_tab) {
            //someone hacked the selected tab
            $data_td->add( $this->_invalid_tab() );
        }


        // Check whether to build icon td
        if ($this->_icon_flag)
            $this->_build_icons();
        else
            $this->_add_tab_spacer(TRUE);

        $this->_ui_wrapper->add_row($this->_tab_row);

        // Add line after tabs
        $this->_add_line_spacing();

        $tr->add($data_td);
        $this->_ui_wrapper->add_row($tr);
    }


    /**
     * This method builds the outer wrapper UI
     * for the subtab
     *
     * @return none
     */
    protected function _build_subtab_ui() {

        // initialize selected tab number
        if (isset($_REQUEST[TabWidget::TABLIST_SUB_SELECTED]))
            $this->_tab_selected = $_REQUEST[TabWidget::TABLIST_SUB_SELECTED];

        $this->_ui_wrapper = html_table("100%");

        $this->_tab_row = new TRtag();

        $tr = new TRtag();

        $tab_name = $this->name($this->get_title());
        $data_td = new TDtag(array("class"=>"subtab_data"));

        foreach( $this->_tabs as $tab_obj ) {
            $title = $tab_obj->get_title();
            $subtab_name = $this->name($title);
            $this->_build_subtab($title, $tab_name, $subtab_name);

            if ($subtab_name==$this->_tab_selected) {
                if (is_subclass_of($tab_obj, "tablist") ||
                    get_class($tab_obj) == 'tablist') {
                    $this->_valid_tab = TRUE;
                    $data_td->add( $tab_obj );
                } else {
                    $this->_valid_tab = TRUE;
                    $data_td->add( $tab_obj->content() );
                }
            }
        }

        if (!$this->_valid_tab) {
            //someone hacked the selected tab
            $data_td->add( $this->_invalid_tab() );
        }

        //add last spacer to cram everything left.
        $this->_tab_row->add( new TDtag(array("width" => "95%",
                                              "class" => "subtab"), phphtmllib::_HTML_SPACE));
        $this->_ui_wrapper->add_row($this->_tab_row);
        $tr->add($data_td);
        $this->_ui_wrapper->add_row($tr);
    }


    /**
     * This method is used to build a top level
     * tab
     *
     * @param string - the tab title
     *
     */
    protected function _build_tab($title, $tab_name) {

        if ($this->_tab_selected == null ||
            empty($this->_tab_selected)) {
            $this->_tab_selected = $tab_name;
        }

        if ($tab_name==$this->_tab_selected) {
            $class = "tab_selected";
            $link_class = "tab_link_selected";
        } else {
            $class = "tab_default";
            $link_class = "tab_link_default";
        }


        // create link for this tab pointing to the same page with the tab number
        $url = $this->_build_url($tab_name);

        // the actual tab
        $onclick = "window.location='" . $url."';return false;";
        $td = new TDtag(array(
                              "class"=>$class,
                              "valign" => "top",
                              "width"=>"10%",
                              "nowrap",
                              "onclick"=> $onclick));

        $td->add(html_a($url, $title, $link_class));
        $td->set_collapse();
        $this->_tab_row->add($td);
    }

    /**
     * This method builds a single subtab
     *
     * @param string the title
     * @param string the tab name
     */
    protected function _build_subtab($title, $tab_name, $subtab_name) {

        if ($this->_tab_selected == null ||
            empty($this->_tab_selected)) {
            $this->_tab_selected = $subtab_name;
        }

        if ($subtab_name==$this->_tab_selected) {
            $class = "subtab";
            $link_class = "subtab_link_selected";
        } else {
            $class = "subtab";
            $link_class = "subtab_link_default";
        }

        $url = $this->_build_url($tab_name, $subtab_name);

        $td = html_td($class);

        $td->set_collapse();
        $td->add( html_a($url, $title, $link_class));

        $this->_tab_row->add( $td );
    }


    /**
     * This method adds a new spacer in between
     * the tabs.
     *
     * @param boolean - is this the last spacer?
     */
    protected function _add_tab_spacer($last_spacer=false) {

        $attributes = array();

        if ($last_spacer) {
            $width = 100 - ($this->tab_num*10) . "%";

            $attributes["class"] = "tab_spacer_last";
            $attributes["align"] = "center";
            $attributes["width"] = $width;

        } else {
            $attributes["class"] = "tab_spacer";
            $attributes["align"] = "left";
        }


        $td = new TDtag($attributes);
        $td->add(phphtmllib::_HTML_SPACE);
        $td->set_collapse();
        $this->_tab_row->add($td);
    }

    /**
     * This method builds a message for an invalid
     * selected tab/subtab
     *
     * @return Container
     */
    protected function _invalid_tab() {
        return "Invalid Selected Tab";
    }

    /**
     * This method builds the icons to the right of the tabs
     *
     */
    protected function _build_icons() {
        $attributes = array();

        $width = 100 - ($this->tab_num*10) . "%";

        $attributes["class"] = "tab_icon";
        $attributes["align"] = "right";
        $attributes["width"] = $width;
        $td2 = new TDtag( $attributes);

        $spacing_div = new DIVtag(array("style" => "display: inline; padding:5px;"));
        $spacing_div->add("&nbsp;");

        foreach ($this->_icons as $icontab) {
            $img = html_img(
                $icontab['icon'],
                $icontab['height'], $icontab['width'], 0,
                $icontab['title'], null, $icontab['title'],
                'top');
            $url = html_a(
                $icontab['url'],
                Container::factory($img->render(), phphtmllib::_HTML_SPACE,
                          phphtmllib::_HTML_SPACE, $icontab['title']),
                'icon_data', '', '');
            $url->set_tag_attribute('onclick', $icontab['onclick']);
            $icontablist .= $spacing_div->render() . $url->render();
        }

        $td2->add($icontablist);
        $this->_tab_row->add($td2);
    }

    /**
     * This method adds a new spacing between the tabs and the tab contents
     *
     */
    protected function _add_line_spacing() {

        if (!$this->_subtab_flag &&
            $this->_tab_line_flag) {
            $colspan = 2*$this->tab_num+1;

            $spacing_td = new TDtag(array("class"=>"tab_spacing","colspan"=>$colspan));
            $spacing_td->add("&nbsp;");
            $spacing_tr = new TRtag();

            $spacing_tr->add($spacing_td);

            $this->_ui_wrapper->add_row($spacing_tr);
        }
    }

}
?>
