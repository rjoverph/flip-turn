<?php
/**
 * This file contains the HTMLDataList base class
 * that can be used for all HTML render based DataList
 * classes.
 *
 * $Id: HTMLDataList.inc 3029 2007-10-07 21:19:12Z brianrue $
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage DataList
 */


/**
 *
 * This is an abstract class that provides the common
 * methods for building and rendering an HTML based
 * DataList class.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage DataList
 */
abstract class HTMLDataList extends DataList implements HTMLWidgetInterface {


    //is a column sortable or not?
    const NOT_SORTABLE = 0;
    const SORTABLE = 1;

    //case insensitive sorting.
    const SORTABLE_ICASE = 2;

    //numeric type sorting.
    const SORTABLE_NUMERIC = 3;

    const SEARCHABLE = TRUE;
    const NOT_SEARCHABLE = FALSE;

    //pagination defines
    const PAGE_STYLE_JUMP = 0;
    const PAGE_STYLE_NAVIGATE = 1;

    /**
     * The title of the table.
     *
     * @var string
     */
    protected $title='';

    /**
     * the width of the widget
     *
     * @var string
     */
    protected $width="100%";

    /**
     * The widget wide alignment
     * value.
     *
     * @var string
     */
    protected $_align = NULL;

    /**
     * This holds a list of
     * name=>value vars that the
     * caller/child wants to propogate
     * automatically.
     *
     */
    protected $_save_vars = array();


    /**
     * Flag to let us know that search
     * is enabled.
     *
     */
    protected $_search_flag = FALSE;

    /**
     * Holds the FormContent used for the
     * search area
     */
    protected $_formcontent = NULL;


    /**
     * Flag to enable simple search modifyer.
     * IF enabled it will add a select that adds
     * the "beings with", "contains" options for
     * a simple search.
     */
    protected $_search_modifier = HTMLDataListSearchFormContent::SEARCH_ALL;

    /**
     * this array holds some strings for the
     * search functionality.  This enables
     * some level of localization for other
     * languages.
     *
     */
    var $_search_text = array("title" => "Search",
                              "find" => "Find",
                              "button" => "Search");


    /**
     * the default base path to images
     * used by any child of
     * this class.
     */
    protected $_image_path;


    /**
     * Some attributes for the
     * form tag.
     */

    /**
     * The default form method attribute
     */
    protected $_form_method = 'GET';

    /**
     * The default form name attribute
     */
    protected $_default_form_name = 'myform';


    /**
     * flag indicating if we should scrub the data
     */
    protected $_clean_string = TRUE;

    /**
     * holds the pagination navigation style
     * to be used.
     * NOTE: Default is HTMLDataList::PAGE_STYLE_NAVIGATE
     * */
    protected $pagination_style = HTMLDataList::PAGE_STYLE_NAVIGATE;


    /**
     * The wrapper div id name
     */
    protected $divid = 'idDataList';


    /**
     * The form tag's id
     */
    protected $formid = 'idmyform';

    /**
     * The Constructor.
     *
     *
     * @param string - the title of the data list
     * @param string - the overall width
     * @param string - the column to use as the default sorting order
     * @param boolean - sort the default column in reverse order?
     */
    function __construct($title='', $width = "100%",
                         $default_orderby='', $default_reverseorder=FALSE) {
        $this->set_title( $title );
        $this->set_width( $width );

        //build the FORMtag container object
        //that wraps everything.
        $this->build_form();

        if ($title != NULL && $title != "") {
            $this->set_form_name(strtolower(preg_replace('/(\W|^\d)/', '_', $title)));
        }

        $this->_image_path = $GLOBALS['config']->get('widget_image_path', '/images/widgets');
        parent::__construct($default_orderby,$default_reverseorder);
    }


    /**
     * This is the init method
     *
     */
    protected function init() {

        //now call user_setup
        $this->user_setup();

        //if they have searching enabled
        //then we should build the search
        //form now and set the searchable
        //fields that the form might want to use.
        if ($this->_search_flag) {
            $this->init_search();
        }
    }


    /**
     * The child class must extend user_setup
     * to add the columns and setup the data
     * search criteria.
     *
     * @return none
     */
    abstract protected function user_setup();


    /**
     * This method is used to return the
     * HTMLDataListSearchFormContent child
     * class that will be used as the
     * search form for this datalist.
     *
     * @return HTMLDataListSearchFormContent child
     */
    abstract protected function build_search_formcontent();


    /**
     * This function adds a header item to the column headers
     * from a list of parameters.
     *
     * @param string - $label - the label to use for
     *                          the column header.
     * @param int    - $size - the size for the table column.
     * @param string - $dbfield - the db field associated
     *                            with this label from the query.
     * @param boolean - $sortable - flag to make this column sortable.
     * @param boolean - $searchable - flag to make this column searchable.
     * @param string - header align value.
     * @param string - the sort order
     * @param string - the maximum # of characters to allow in the cell.
     *
     * @return array a single header array
     */
    public function add_header_item( $label, $size=100, $data_name=NULL,
                                     $sortable=FALSE, $searchable=FALSE,
                                     $align="left", $sortorder="",
                                     $max_text_length=NULL) {

        $this->_columns[$label] = array("size" => $size,
                                        "data_name" => $data_name,
                                        "sortable" => $sortable,
                                        "searchable" => $searchable,
                                        "align" => $align,
                                        "sortorder" => $sortorder,
                                        "maxtextlength" => $max_text_length,
                                        "reverseorder"=>false);

        $this->_check_datasource("add_header_item");
        $this->_datalistsource->add_column($label, $data_name, $sortable,
                                           $searchable, $sortorder);
    }


    /**
     * This method sets the value of the id for the
     * wrapping div tag that encapsulates the output.
     *
     * @param string $idname
     */
    public function set_div_id($idname) {
        $this->divid = $idname;
    }

    /**
     * This method gets the value of the id for the
     * wrapping div tag that encapsulates the output.
     *
     * @param string $idname
     */
    public function get_div_id() {
        return $this->divid;
    }

    /**
     * This function sets a prefix for all
     * variables that are used in the item list
     * table on a page.  This allows you to have
     * multiple itemlists on a single html page.
     *
     * @param string $prefix - the prefix for all vars.
     */
    protected function set_global_prefix($prefix) {
        parent::set_global_prefix($prefix);

        $this->set_div_id($prefix. $this->get_div_id());
        $this->set_form_id($prefix. $this->get_form_id());
    }


    /*******************************************/
    /*         FORM VARIABLES SECTION          */
    /*******************************************/

    /**
     * This method builds the FORMtag object
     */
    protected function build_form() {
        $this->_form = FORMtag::factory($this->_default_form_name,
                                        '',
                                        $this->_form_method,
                                        array('style' => "margin-top: 0px;margin-bottom:0px;",
                                              'id' => $this->get_form_id()));
    }

    /**
     * This function is used to set the
     * form name
     *
     * @param string
     */
    public function set_form_name($name) {
        $this->_form->set_name($name);
    }

    /**
     * This function is used to get
     * the form name
     *
     * @return string
     */
    public function get_form_name() {
        return $this->_form->get_name();
    }

    /**
     * This function is used to set the
     * form target
     *
     * @param string
     */
    public function set_form_target($target) {
        $this->_form->set_tag_attribute('target', $name);
    }

    /**
     * This function is used to get
     * the form target
     *
     * @return string
     */
    public function get_form_target() {
        return $this->_form->get_tag_attribute('target');
    }

    /**
     * This function is used to set the
     * form method
     *
     * @param string (POST or GET)
     */
    public function set_form_method($method) {
        if (isset($this->_form)) {
            $this->_form->set_method($method);
        }

        $this->_form_method = $method;
    }

    /**
     * This function is used to get
     * the form method
     *
     * @return string (POST or GET)
     */
    public function get_form_method() {
        return $this->_form->get_method();
    }

    /**
     * Sets the form action
     *
     * @param string
     */
    public function set_form_action($action) {
        $this->_form->set_action($action);
    }

    /**
     * This function is used to get
     * the form action
     *
     * @return string (POST or GET)
     */
    public function get_form_action() {
        return $this->_form->get_action();
    }


    /**
     * This sets the form id
     *
     * @param string $id
     */
    public function set_form_id($id) {
        $this->formid = $id;
        if (isset($this->_form)) {
            $this->_form->set_tag_attribute('id', $id);
        }
    }

    /**
     * gets the form tag's id value
     *
     * @return string
     */
    public function get_form_id() {
        return $this->formid;
    }

    /**
     * this method builds some hidden
     * form fields to automatically
     * be placed inside the form.
     *
     * This method returns a list of
     * hidden form fields if we are a POST.
     * It returns a portion of a query string
     * If we are a GET.
     *
     * @return mixed depending on form method
     */
    protected function _build_save_vars() {
        $container = Container::factory();
        foreach($this->_save_vars as $name => $value) {
            $container->add(form_hidden($name, $value));
        }
        return $container;
    }

    /**
     * This function sets the save variables
     * that the user/child wants to automatically
     * propogate
     *
     * @param array - name=>value pairs of the data
     *                that they want to propogate
     */
    public function set_save_vars($vars) {
        $this->_save_vars = array_merge($this->_save_vars, $vars);
    }


    /**
     * This function builds the list of
     * default hidden form vars for when
     * the datalist is being rendered
     * as a POST
     *
     * @return Container
     */
    protected function _build_default_vars() {
        // the navigation links will set the offset anyway
        $c =  Container::factory(new FEHidden($this->_vars["offsetVar"][DataList::VAR_NAME], $this->offset()),
                                 new FEHidden($this->_vars["orderbyVar"][DataList::VAR_NAME], $this->orderby()),
                                 new FEHidden($this->_vars["reverseorderVar"][DataList::VAR_NAME], $this->reverseorder()),
                                 new FEHidden($this->_vars["expandrowsVar"][DataList::VAR_NAME], $this->expandrows()));

        //we have to add the _form_content's hidden form vars as well
        if (isset($this->_formcontent)) {
            foreach ($this->_formcontent->get_hidden_elements() as $element) {
                if ($element instanceof FEHidden) {
                    $c->add($element->get_element());
                }
            }
        }

        return $c;
    }

    /**
     * This builds the base url used
     * by the column headers as well
     * as the page tool links.
     *
     * it basically builds:
     * $_SELF?$_GET
     *
     * @return string
     */
    protected function build_base_url() {

        $url = $_SERVER["PHP_SELF"]."?";

        if ( $this->get_form_method() == "POST" ) {
            return $url;
        }

        $vars = array_merge($_POST, $_GET);
        //request method independant access to
        //browser variables
        if ( count($vars) ) {
            //walk through all of the get vars
            //and add them to the url to save them.
            foreach($vars as $name => $value) {

                if ( $name != $this->_vars["offsetVar"][DataList::VAR_NAME] &&
                     $name != $this->_vars["orderbyVar"][DataList::VAR_NAME] &&
                     $name != $this->_vars["reverseorderVar"][DataList::VAR_NAME]
                   ) {
                    if ( is_array($value) ) {
                        $url .= $name."[]=".implode("&".$name."[]=",$value)."&";
                    } else {
                        $url .= $name."=".urlencode(stripslashes($value))."&";
                    }
                }
            }
        }

        return $url;
    }



    /**
     * This method is used to set the style of
     * pagination navigation to use.
     *
     * @param int
     */
    protected function set_pagination_style($style = HTMLDataList::PAGE_STYLE_NAVIGATE ) {
        $this->pagination_style = $style;
    }


    /**
     * This function builds the 'tool' images that
     * allow  you to walk through the data list itself.
     * It provides image links for
     * first - go to the first page in the data list
     * prev - go to the previous page in the data list
     * next - go to the next page in the data list
     * last - go to the last page in the data list
     * all - show the rest of the list from the current offset
     *
     * @param string - which tool image to build
     * @return Object
     */
    protected function build_tool_img( $which ) {
        $num_pages = $this->get_num_pages();
        $cur_page = $this->get_current_page();
        $last_page = $this->get_last_page();

        $image_path = $this->get_image_path();
        switch ( $which ) {

        case "first":
            $rows_string = "First ".$this->get_default_num_rows()." Rows";
            if ( $this->offset() <= 0 ) {
                $obj = IMGtag::factory($image_path."/first_group_button_inactive.gif",
                                       16,16,0,$rows_string, NULL, $rows_string . ": Disabled Link");
            } else {
                $url = $this->_build_tool_url(0);
                $img = IMGtag::factory($image_path."/first_group_button.gif",16,16,0,$rows_string,NULL,$rows_string);
                $img->set_tag_attribute('style', 'width:16px;height:16px;');
                $obj = Atag::factory($url,$img);
                //$obj = html_img_href($url, ,
                //                     '','',0, $rows_string, NULL, NULL, $rows_string);
            }
            break;

        case "prev":
            $rows_string = "Previous ".$this->get_default_num_rows()." Rows";
            if ( $this->offset() <= 0 ) {
                $obj = IMGtag::factory($image_path."/prev_group_button_inactive.gif",
                                       16,16,0,$rows_string, NULL, $rows_string . ": Disabled Link");
            } else {
                $offset = $this->offset() - $this->numrows();
                if ( $offset < 0 ) {
                    $offset = 0;
                }
                $url = $this->_build_tool_url($offset);
                $img = IMGtag::factory($image_path."/prev_group_button.gif",16,16,0,$rows_string,NULL,$rows_string);
                $img->set_tag_attribute('style', 'width:16px;height:16px;');
                $obj = Atag::factory($url,$img);
                //$obj = html_img_href($url, $image_path."/prev_group_button.gif",
                //                     '','',0, $rows_string, NULL, NULL, $rows_string);
            }
            break;

        case "next":
            $rows_string = "Next ".$this->get_default_num_rows()." Rows";
            if ( ($num_pages == 1) || ($cur_page == $last_page) ) {
                $obj = IMGtag::factory($image_path."/next_group_button_inactive.gif",
                                       16,16,0, $rows_string, NULL, $rows_string . ": Disabled Link");
            } else {
                $offset = $this->offset() + $this->numrows();
                $url = $this->_build_tool_url($offset);

                $img = IMGtag::factory($image_path."/next_group_button.gif",16,16,0,$rows_string,NULL,$rows_string);
                $img->set_tag_attribute('style', 'width:16px;height:16px;');
                $obj = Atag::factory($url,$img);
            }
            break;

        case "last":
            $rows_string = "Last ".$this->get_default_num_rows()." Rows";
            if ( ($num_pages == 1) || ($cur_page == $last_page) ) {
                $obj = IMGtag::factory($image_path."/last_group_button_inactive.gif",
                                       16,16,0, $rows_string, NULL, $rows_string . ": Disabled Link");
            } else {
                $offset = (int)(($num_pages - 1) * $this->numrows());
                $url = $this->_build_tool_url($offset);

                $img = IMGtag::factory($image_path."/last_group_button.gif",16,16,0,$rows_string,NULL,$rows_string);
                $img->set_tag_attribute('style', 'width:16px;height:16px;');
                $obj = Atag::factory($url,$img);
            }
            break;

        case "expand":
            $offset = $this->offset();
            if ( $this->expandrows() ) {
                $url = $this->_build_tool_url($offset, TRUE, 0);
                $img = IMGtag::factory($image_path."/close_group_button.gif",16,16,0,"Collapse Rows",NULL,"Collapse Rows");
                $img->set_tag_attribute('style', 'width:16px;height:16px;');
                $obj = Atag::factory($url,$img);
            } else {
                if ( ($num_pages == 1) ) {
                    $obj = IMGtag::factory($image_path."/expand_group_button_inactive.gif",
                                           16,16,0, "Expand Rows", NULL, "Expand Rows" . ": Disabled Link");
                } else {
                    $url = $this->_build_tool_url($offset, TRUE, 1);
                    $img = IMGtag::factory($image_path."/expand_group_button.gif",16,16,0,"Expand Rows",NULL,"Expand Rows");
                    $img->set_tag_attribute('style', 'width:16px;height:16px;');
                    $obj = Atag::factory($url,$img);
                }
            }
            //so we don't save it into the mozilla navigation bar links
            unset($url);
            break;
        }

        return $obj;
    }

    /**
     * This function is used to build the url
     * for a tool link.
     * (first, prev, next, last, all)
     *
     * @param int - the offset for the link
     * @param boolean - add the expandrows value to the url
     * @param int - the expandrows value to use if the flag is on
     *
     * @return string
     */
    protected function _build_tool_url($offset, $expandrows_flag=FALSE, $expandrows_value=0) {
        if ( $this->get_form_method() == "POST" ) {
            $form_name = $this->get_form_name();
            $url = "javascript: document.".$form_name;
            $url .= ".".$this->_vars["offsetVar"][DataList::VAR_NAME].".value='".$offset."';";

            //add the expandrows variable to the post
            if ( $expandrows_flag ) {
                $form_field = $this->_vars["expandrowsVar"][DataList::VAR_NAME];
                $url .= "document.".$form_name.".";
                $url .= $form_field.".value='".$expandrows_value."';";
            }

            $url .= "document.".$form_name.".submit();";
        } else {
            $url = $this->build_base_url();
            $url .= $this->build_state_vars_query_string($offset, $expandrows_flag,
                                                         $expandrows_value);
        }
        return $url;
    }

    /**
     * This method builds the offset value
     * based on the page number.
     *
     * @param int $page the page number
     * @return int the offset for that page.
     */
    function page_offset($page) {
        $offset = $this->numrows()*$page;
        return $offset;
    }


    /**
     * This method builds a Page Jump style
     * set of navigation links.
     *
     * @return DIVtag object
     */
    function build_jump_links() {
        $current_page = $this->get_current_page();
        $num_pages = $this->get_num_pages();
        if (empty($current_page)) {
            $current_page = 1;
        }

        //determine the pages to show.
        $windowSize = 3;
        $jumpRange = array();
        $lowerPage = max($current_page - (int)($windowSize / 2), 1);
        $upperPage = min($current_page + (int)($windowSize / 2), $num_pages);
        if ($upperPage == 0) {
            $upperPage = 1;
        }
        if ($upperPage == $num_pages) {
            $lowerPage = max($upperPage - $windowSize, 1);
        } else if ($lowerPage == 1) {
            $upperPage = min($lowerPage + ($windowSize-1), $num_pages);
        }

        for ($i = $lowerPage; $i <= $upperPage; $i++) {
            $jumpRange[] = $i;
        }
        if ($lowerPage > 1) {
            array_unshift($jumpRange, 1);
        }
        if ($upperPage < $num_pages) {
            $jumpRange[] = $num_pages;
        }

        //XXX need way to build unique id
        $d = new DIVtag(array('id' => 'datalistjumplinks'));
        $d->set_collapse();
        $lastpage = 0;
        foreach( $jumpRange as $pageoffset ) {

            if ($pageoffset - $lastpage >= 2) {
                if ($pageoffset - $lastpage == 2) {
                    $d->add(Atag::factory($this->_build_tool_url($this->page_offset($pageoffset-1)), $pageoffset-1),
                            phphtmllib::_HTML_SPACE);
                } else {
                    $d->add( '...'.phphtmllib::_HTML_SPACE );
                }
            }

            if ($pageoffset == $current_page) {
                $d->add( $current_page.phphtmllib::_HTML_SPACE );
            } else {
                $d->add(Atag::factory($this->_build_tool_url($this->page_offset($pageoffset-1)), $pageoffset),
                        phphtmllib::_HTML_SPACE);
            }
            $lastpage = $pageoffset;
        }

        return $d;
    }

    /**
     * this function is used to build a sub query string
     * of all of the query string vars to save the
     * state of the DBItemList.  This is used for pages
     * that want to come back to the list at the same state
     *
     * @param int - the offset for the link
     * @param boolean - add the expandrows value to the url
     * @param int - the expandrows value to use if the flag is on
     * @return string - name=value& pairs
     */
    protected function build_state_vars_query_string($offset, $expandrows_flag=FALSE,
                                           $expandrows_value=0) {
        $str = "";

        $str .= $this->_vars["offsetVar"][DataList::VAR_NAME]."=".urlencode($offset);
        $str .= "&".$this->_vars["orderbyVar"][DataList::VAR_NAME]."=".urlencode($this->orderby());
        $str .= "&".$this->_vars["reverseorderVar"][DataList::VAR_NAME]."=".urlencode($this->reverseorder());
        //$str .= "&".$this->_vars["search_fieldVar"][DataList::VAR_NAME]."=".urlencode($this->search_field());
        //$str .= "&".$this->_vars["search_valueVar"][DataList::VAR_NAME]."=".urlencode($this->search_value());
        //$str .= "&".$this->_vars["simple_search_modifierVar"][DataList::VAR_NAME]."=".urlencode($this->simple_search_modifier_value());
        //$str .= "&".$this->_vars["search_typeVar"]."=".urlencode($this->search_type());
        if ( $expandrows_flag ) {
            $str .= "&".$this->_vars["expandrowsVar"][DataList::VAR_NAME]."=".urlencode($expandrows_value);
        }

        return htmlentities($str);
    }


    /**
     * This function returns the path to the
     * images used in this class
     *
     * @return string
     */
    public function get_image_path() {
        return $this->_image_path;
    }

    /**
     * This function returns the path to the
     * images used in this class
     *
     * @return string
     */
    public function set_image_path($path) {
        return $this->_image_path = $path;
    }


    /**
     * This builds a url for a particular
     * column header.
     *
     * @param string - $col_name
     * @return Atag object;
     */
    protected function build_column_url($col_name) {
        $orderby = $this->orderby();
        $reverseorder = $this->reverseorder();
        $search_value = $this->search_value();

        $order_value = $this->_columns[$col_name]["data_name"];
        $reverse_value = "false";
        if ( !$reverseorder ) {
            $reverseorder = 'false';
        }

        if ( $orderby == $order_value && $reverseorder === 'false' ) {
            $reverse_value = "true";
        } else if ($orderby != $order_value && $this->_default_reverseorder === 'true') {
            //This is the case where the user wants the default ordering for
            //columns to be reversed...DESCENDING instead of ASCENDING
            $reverse_value = 'true';
        }

        if ( $this->get_form_method() == "POST" ) {
            //we have to construct this url
            //specially.
            $form_name = $this->get_form_name();

            $url = "javascript: ";
            //set the offset correctly
            $url .= "document.".$form_name.".".$this->_vars["offsetVar"][DataList::VAR_NAME].".value='".$this->offset()."';";
            //set the orderby correctly.
            $url .= "document.".$form_name.".".$this->_vars["orderbyVar"][DataList::VAR_NAME].".value='".$order_value."';";
            //set the reverseorder
            $url .= "document.".$form_name.".".$this->_vars["reverseorderVar"][DataList::VAR_NAME].".value='".$reverse_value."';";

            $url .= "document.".$form_name.".submit();";
        } else {
            //handle the normal get.
            $url = "javascript:document.location='".$this->build_base_url();
            //Now add the orderby, reverseorder and offset vars
            $url .= $this->_vars["offsetVar"][DataList::VAR_NAME] ."=0&";
            //set the orderbyvar
            $url .= $this->_vars["orderbyVar"][DataList::VAR_NAME] ."=".$order_value."&";
            //set the reverseorder
            $url .= $this->_vars["reverseorderVar"][DataList::VAR_NAME] ."=".$reverse_value."&";

            $url .= "';";
        }

        return htmlentities($url);
    }


    /**
     * This does some magic filtering on the data
     * that we display in a column.  This helps
     * to prevent nast data that may have html
     * tags in it.
     *
     * @param string - the column data u want to filter
     * @return string the cleaned/filtered data
     */
    protected function filter_column_string($data) {
        return htmlspecialchars(trim($data));
    }

    /**
     * This method sets the flag to tell us if we want to clean the data
     *
     *
     * @param boolean TRUE = clean it
     */
    protected function set_cleanstring($flag=TRUE) {
        $this->_clean_string = $flag;
    }

    /**
     * return the value of the clean string flag
     *
     *
     * @return boolean
     */
    protected function get_cleanstring() {
        return $this->_clean_string;
    }

    /**
     * This function is used to make sure that the string we are
     * placing in a cell has been "cleaned"
     *
     * @param mixed - the cell object.  It can be a string.
     * @param string - the name of the column this object/string
     *                 will live
     *
     * @return mixed - the cleaned string or object
     */
    protected function _clean_string($obj, $col_name) {
        if ( is_string($obj) ) {
            if ( $this->_columns[$col_name]["maxtextlength"] ) {
                //looks like we need to make sure we
                //truncate the string to a max length
                if ( strlen($obj) > $this->_columns[$col_name]["maxtextlength"] ) {
                    //we need to truncate it and
                    //add a hover title attribute for the full
                    //object
                    $obj = new SPANtag(array("title"=>$this->filter_column_string($obj)),
                                       $this->filter_column_string(substr($obj, 0, $this->_columns[$col_name]["maxtextlength"]) . "..."));
                } else {
                    $obj = $this->filter_column_string($obj);
                }
            } else {
                $obj = $this->filter_column_string($obj);
            }
        }
        return $obj;
    }


    /********************************/
    /*      SEARCH RELATED          */
    /********************************/

        /**
     * Enable the search ability.
     *
     * @param boolean
     */
    public function search_enable( ) {
        $this->_search_flag = TRUE;
    }

    /**
     * Disable the search ability.
     *
     * @param boolean
     */
    public function search_disable( ) {
        $this->_search_flag = FALSE;
    }

    /**
     * get the status of the search
     * ability.
     *
     * @return boolean
     */
    public function is_search_enabled() {
        return $this->_search_flag;
    }



    /**
     * returns the current value of
     * the search field name
     *
     * @return string
     */
    public function search_field() {
        if ($this->is_search_enabled()) {
            return $this->_formcontent->get_search_field_value();
        } else {
            return '';
        }
    }

    /**
     * returns the current value of
     * te search field value.
     *
     * @return string
     */
    public function search_value() {
        if ($this->is_search_enabled()) {
            return $this->_formcontent->get_search_value_value();
        } else {
            return '';
        }
    }

    /**
     * returns the current value of the
     * simple search modifier
     *
     * @return string
     */
    public function search_modifier_value() {
        if ($this->is_search_enabled()) {
            return $this->_formcontent->get_search_modifier_value();
        } else {
            return '';
        }
    }


    /**
     * This method gets the array of
     * searchable header fields (columns)
     *
     * @return array
     */
    protected function get_searchable_fields() {
        $fields = array();
        foreach($this->_columns as $name => $header) {
            if ( $header["searchable"] == self::SORTABLE ||
                 $header["searchable"] == self::SORTABLE_ICASE ||
                 $header["searchable"] == self::SORTABLE_NUMERIC) {
                $fields[$name] = $header["data_name"];
            }
        }
        return $fields;
    }


    /**
     * Set the simple search modifyer
     * flag.
     * NOTE: by default all the modifiers
     *       are enabled.  You can limit the
     *       modifiers by passing in the
     *       string of defines of which ones
     *       you want enabled.
     *
     * MODIFIERS:
     *          SEARCH_BEGINS_WITH
     *          SEARCH_CONTAINS
     *      SEARCH_EXACT
     *      SEARCH_ENDS_WITH
     *
     *       ie. SEARCH_BEGINS_WITH.SEARCH_EXACT
     *           will enable ONLY the
     *           "begins with" and "exact" modifiers.
     *
     * @param string
     */
    function set_search_modifier( $modifier = HTMLDataListSearchFormContent::SEARCH_ALL ) {
        $this->_search_modifier = $modifier;
    }


    /**
     * This function is used to make safe
     * any query string value that is used
     *
     * @param string
     * @return string
     */
    protected function search_value_filter( $value ) {
        return stripslashes( trim($value) );
    }




    /**
     * This method is used to initialize the Search form.
     * It gets the FormContent from the child class and
     * initializes it.
     *
     */
    protected function init_search() {
        if (!isset($this->_formcontent)) {
            $this->set_search_formcontent($this->build_search_formcontent());
        }

        $this->_formcontent->set_global_prefix($this->get_global_prefix());

        //ok now initialize the form.
        //first get the searchable fields
        $fields = $this->get_searchable_fields();
        $this->_formcontent->set_searchable_fields( $fields );

        //pass the search modifier to the FormContent.
        //it gets set in user_setup which is called prior
        //to the formcontent existing.
        $this->_formcontent->set_search_modifier($this->_search_modifier);


        //initialize the form elements.
        $this->_formcontent->init();
    }

    /**
     * This method should be extended by the child
     * to pass any extra params to the datalistsource
     * prior to calling datalistsource->execute()
     *
     * @return array
     */
    protected function extra_query_params() {
        //we need to walk all of the form elements
        //in the form content and return their values.
        if (!isset($this->_formcontent)) {
            return array();
        } else {
            $params = array();
            foreach( $this->_formcontent as $element) {
                $params[$element->get_label_text()] = $element->get_value();
            }

            return $params;
        }
    }


    /**
     * This method is used to set the formcontent
     * that will be used for the search area.
     *
     * @param HTMLDataListSearchFormContent
     * @return boolean
     */
    public function set_search_formcontent( HTMLDataListSearchFormContent $formcontent) {
        if (!($formcontent instanceof HTMLDataListSearchFormContent)) {
            throw new phphtmllibException('FormContent not a child of HTMLDataListSearchFormContent');
        }
        $this->_formcontent = $formcontent;
    }


    /**
     * This method returns the layout of the
     * FormContent::form()
     *
     * @return mixed
     */
    protected function get_search_formcontent_layout() {
        return $this->_formcontent->form();
    }


    /**
     * This method is used to return the current
     * FormContent child for search.
     *
     * @return HTMLDataListSearchFormContent
     */
    public function get_search_formcontent() {
        return $this->_formcontent;
    }



    /*******************************/
    /* Errors related stuff here   */
    /*******************************/

    /**
     * This method builds and returns the
     * errors to display
     *
     * @return Container object
     */
    public function build_errors() {
        $errors = new ErrorBoxWidget();

        return $errors;
    }




    /**
     * Interface implementation methods
     */

    /**
     * Function for returning the raw javascript
     * that is required for this widget.
     *
     * @return string - the raw javascript
     */
    public function get_javascript() {
        return NULL;
    }

    /**
     * Set the title for the widget.
     * this is just a generic title string
     * that can be used however the child class
     * wants to use it.
     *
     * @param string - $title
     */
    public function set_title( $title ) {
        $this->title = $title;
    }

    /**
     * Function for accessing the
     * title of this widget
     *
     * @return string - the title
     */
    public function get_title() {
        return $this->title;
    }


    /**
     * Set the width for the widget.
     * this is meant to be the overall
     * width expected to be used to
     * control the generated html.
     *
     * @param string - $width (ie. 80, 100%)
     */
    public function set_width( $width ) {
        $this->width = $width;
    }

    /**
     * Function for getting the current
     * widget width setting.
     *
     * @return string - the width
     */
    public function get_width() {
        return $this->width;
    }

    /**
     * This function sets the align attribute
     * for the outer table.
     *
     * @param string - $align - the align value
     */
    public function set_align( $align ) {
        $this->_align = $align;
    }

    /**
     * This gets the alignment value
     * for the outer table
     *
     * @return string - the alignment
     */
    public function get_align() {
        return $this->_align;
    }
}

?>
