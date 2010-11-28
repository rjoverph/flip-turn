<?php
/**
 *
 * This file contains the sample HTML based
 * DataList class that renders like the old
 * DefaultGUIDataList
 *
 * $Id: DefaultHTMLDataList.inc 2956 2007-09-27 17:29:27Z hemna $
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage DataList
 */



/**
 *
 * This class builds an HTML output DataList
 * that looks like the old DefaultGUIDataList.
 * The layout is as follows
 *
 *
 * |----------------------------------------|
 * |  * Errors here from validation/actions |
 * |----------------------------------------|
 * |----------------------------------------|
 * |          SearchFormContent             |
 * |----------------------------------------|
 * |----------------------------------------|
 * |       Title and Page navigation        |
 * |----------------------------------------|
 * |----------------------------------------|
 * |            Column Headers              |
 * |----------------------------------------|
 * |          Cell based Data Rows          |
 * |----------------------------------------|
 * |----------------------------------------|
 * |         Generic 'Action bar'           |
 * |----------------------------------------|
 *
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage DataList
 *
 * @todo get the action column stuff working again.
 */
abstract class DefaultHTMLDataList extends HTMLDataList {

    /**
     * Some constants
     */

    /**
     * Action column constant to tell us
     * it is the FIRST column.
     */
    const ACTION_FIRST = 'FIRST';
    const ACTION_LAST = 'LAST';

    /**
     * The action column types
     */
    const ACTION_CHECKBOX = 1;
    const ACTION_RADIO = 2;

    /**
     * This holds the action column
     * settings if any.
     */
    private $_action_column = array();

    /**
     * holds the cntr for the action
     * checkbox name
     */
    private $_action_count = 0;

    /**
     * This array holds the list of
     * hidden checkbox[] items.
     *
     */
    private $_hidden_checkbox_items = array();

    /**
     * this array keeps track of the list
     * of rendered visible checkbox[]
     * items.  So we can not render the
     * hidden version of it.
     */
    private $_visible_checkbox_items = array();

    /**
     * this flag tells us to save the
     * checked items between pages
     * By default this is off.
     */
    private $_save_checked_items_flag = FALSE;

    /**
     * This variable holds the array of default
     * selected items.  This is populated
     * inside the user_setup() function
     * to pre-populate the list of selected
     * items for a the checkbox action column.
     *
     */
    private $_default_checked_items = array();


    /**
     * Do we show action bar row?
     */
    private $_show_actionbar = TRUE;

    /**
     * This variable tells us whether to display
     * select all checkbox
     */
    private $_allow_select_all = TRUE;

    /**
     * provide collapseable search block?
     */
    private $_collapsable_search = FALSE;


    /**
     * current working column counter
     */
    private $_cur_col_cntr = 0;


    /**
     * flag to support alternating row
     * colors
     */
    private $alternating_row_colors = FALSE;


    /**
     * This method builds the container/div
     * that holds the entire output
     *
     * @return Container
     */
    protected function get_wrapper() {
        $div_wrapper = DIVtag::factory();
        $div_wrapper->set_tag_attribute('id', $this->get_div_id());
        return $div_wrapper;
    }

    /**
     * This function builds the resulting html output and renders it
     *
     * @param int $indent_level
     * @param int $output_debug
     * @return string
     */
    public function render($indent_level=0, $output_debug=0) {

        $div_wrapper = $this->get_wrapper();

        //lets see if we have errors.
        if ($this->has_errors()) {
            $div_wrapper->add( $this->get_errors() );
        }

        //add the javascript
        $div_wrapper->add( $this->_javascript() );


        //add the form tag
        $div_wrapper->add($this->_form);


        //do they want a search box?
        if ($this->is_search_enabled()) {
            //ok now add the SearchFormContent
            $this->_form->add( $this->get_search_formcontent_layout() );
        }


        //the outer table container
        $this->_data_table = TABLEtag::factory($this->get_width(), 0, 0, 0, $this->get_align());
        $this->_form->add( $this->_data_table );
        $this->_data_table->set_class("datalist_border");

        //now build the title area and navigation pieces

        $table = TABLEtag::factory('', 0, 0, 0);
        $table->set_collapse();

        //the page info
        $td = new TDtag(array("style"=>"color: black;background-color: #eeeeee;".
                              "padding-left: 2px; padding-right: 2px; border:1px inset #cccccc;"));
        $td->add($this->get_page_info());


        //build the pagination piece
        switch ($this->pagination_style) {
        case HTMLDataList::PAGE_STYLE_JUMP:
            $table->add_row( $this->build_jump_links() );
            break;

        case HTMLDataList::PAGE_STYLE_NAVIGATE:
            $table->add_row( $this->build_tool_img("first"), phphtmllib::_HTML_SPACE,
                             $this->build_tool_img("prev"), phphtmllib::_HTML_SPACE,

                             $td,
                             phphtmllib::_HTML_SPACE,

                             $this->build_tool_img("next"),phphtmllib::_HTML_SPACE,
                             $this->build_tool_img("last"), phphtmllib::_HTML_SPACE,
                             $this->build_tool_img("expand"),
                             new TDtag(array("style"=>"font-size: 1px; line-height: 1px; width:10px;"), phphtmllib::_HTML_SPACE)

                            );
            break;
        }

        $spacer_div = new DIVtag(array('style' => 'padding-top: 3px; padding-bottom:3px;'),
                                 $table);
        $this->_tool_td = html_td('datalist_title', "right", $spacer_div);


        //calculate the # of columns depending on if they
        //have added action columns.
        $cols = count($this->_columns);
        if ($this->_has_action_column("FIRST")) $cols++;
        if ($this->_has_action_column("LAST")) $cols++;

        $title_table = html_table("100%");

        $title = new TDtag(array("align" => "left",
                                 "class" => "datalist_title",
                                 "style" => "padding-left: 5px;"),
                           $this->get_title() );

        $title_table->add( new TRtag( array(), $title,
                                      $this->_tool_td) );


        //add the header tr reference
        //it will get populated later
        $this->_data_table->add_row( new TDtag(array("colspan" => $cols),
                                               $title_table) );

        //COLUMN HEADERS
        //now build the column headers
        $header_tr = new TRtag;
        $column_count = count($this->_columns);

        //lets see if we need to add an action column
        //as the first column.
        if ($this->_has_action_column("FIRST")) {
            //looks like we have a FIRST column actionbar
            //lets add it
            $header_tr->add($this->_build_action_column("FIRST", TRUE));
        }

        foreach( $this->_columns as $name => $col ) {
            $header_tr->add($this->build_header( $name, $col, $column_count) );
        }

        if ($this->_has_action_column("LAST")) {
            //looks like we have a FIRST column actionbar
            //lets add it
            $header_tr->add($this->_build_action_column("LAST", TRUE));
        }

        $this->_data_table->add($header_tr);




        //initialize the first date row
        $this->_data_row = new TRtag;

        if ($this->_query_worked) {
                //now walk the list of rows and build and add the
                //cells of data
                $even = TRUE;

                //ok iterate over each row from the datalistsource (Iterator)
                if ($this->_datalistsource->get_total_rows()) {
                    foreach( $this->_datalistsource as $row_data)  {
                        //while ( $row = $this->_datalistsource->get_next_data_row() ) {
                        //try and filter the row.
                        //if (!$this->_datalistsource->row_filter($row_data)) {
                        //    $this->_datalistsource->set_total_rows( $this->_datalistsource->get_total_rows() -1);
                        //    continue;
                        //}
                        $cnt = 1;
                        foreach( $this->_columns as $col_name => $data ) {
                            if ($this->_clean_string) {
                                $obj = $this->_clean_string($this->build_column_item($row_data, $col_name),
                                                            $col_name);
                            } else {
                                $obj = $this->build_column_item($row_data, $col_name);
                            }

                            $this->add_row_cell($obj, $col_name,
                                                (($cnt == $column_count) ? TRUE : FALSE),
                                                $row_data, $even);
                            $cnt++;
                        }
                        $even = !$even;
                    }
                } else {
                    //no results were found.
                    $td = new TDtag(array('colspan'=>count($this->_columns)),
                                    $this->get_not_found_message());
                    $this->_data_table->add_row( $td );
                    $this->_data_row = new TRtag;
                }

                //ok add the actionbar?

                $this->_form->add( $this->_build_actionbar() );
        }

        //add the hidden vars if we are a POST
        if ($this->get_form_method() == "POST") {
            $this->_form->add( $this->_build_default_vars() );
        }

        //add the save vars the user wants.
        $this->_form->add( $this->_build_save_vars() );

        $this->_form->add( new FEHidden(FormProcessor::FORM_ACTION));


        return $div_wrapper->render($indent_level, $output_debug);
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
        //lets add the other vars
        $this->_vars["radioVar"][DataList::VAR_NAME] = "radio";
        $this->_vars["radioVar"][DataList::VAR_VALUE] = NULL;
        $this->_vars["checkboxVar"][DataList::VAR_NAME] = "checkbox";
        $this->_vars["checkboxVar"][DataList::VAR_VALUE] = NULL;

        parent::set_global_prefix($prefix);
    }


    /**
     * This method is used to build the default list
     * of variables that need to go along
     * with each request.
     *
     * We override it here to possibly add the list
     * of saved checkbox items.
     *
     * @return Container
     */
    protected function _build_default_vars() {
        $c = parent::_build_default_vars();

        if ($this->_save_checked_items_enabled()) {
            foreach( $this->_hidden_checkbox_items as $key => $value ) {
                if (!isset($this->_visible_checkbox_items[$key])) {
                    $c->add( new FEHidden($this->_vars["checkboxVar"][DataList::VAR_NAME].'[]', $key ) );
                }
            }
        }

        return $c;
    }


    /**
     * This function returns any Javascript required
     * for this widget
     *
     * @return mixed
     */
    protected function _javascript() {
        $js = '';

        if ($this->_collapsable_search) {
            $js .= $this->_search_javascript();
        }


        if ($this->_has_action_column("FIRST") || $this->_has_action_column("LAST")) {
            $last = isset($this->_action_column["LAST"]["type"]) ? $this->_action_column["LAST"]["type"] : '';
            $first = isset($this->_action_column["FIRST"]["type"]) ? $this->_action_column["FIRST"]["type"] : '';
            if ($last == self::ACTION_CHECKBOX || $first == self::ACTION_CHECKBOX) {
                $js .= $this->_checkbox_javascript();
            }
        }

        if (strlen($js) > 0) {
            $script = new SCRIPTtag(array('language' => 'Javascript', 'type' =>'text/javascript'));
            $script->add($js);
            return $script;
        } else {
            return NULL;
        }
    }

    /**
     * This is the basic function for letting us
     * do a mapping between the column name in
     * the header, to the value found in the DB.
     *
     * NOTE: this function is meant to be overridden
     *       so that you can push whatever you want.
     *
     * @param array - $row_data - the entire data for the row
     * @param string - $col_name - the name of the column header
     *                             for this row to render.
     * @return  mixed - either a HTMLTag object, or raw text.
     */
    protected function build_column_item($row_data, $col_name) {
        $key = $this->_columns[$col_name]["data_name"];

        if (!isset($row_data[$key]) || ($row_data[$key] == '' && $row_data[$key] !== 0)) {
            return " ";
        } else {
            return $row_data[$key];
        }
    }


    /**
     * This method is responsible for building a single cell in
     * a row.
     *
     */
    private function add_row_cell($obj, $col_name, $last_in_row_flag, $row_data, $even_row) {
        if (!$this->_cur_col_cntr) {
            $this->_cur_col_cntr = 1;
            //lets see if we need to add an action column
            //as the first column.
            if ($this->_has_action_column("FIRST")) {
                //looks like we have a FIRST column actionbar
                //lets add it
                $this->_data_row->add($this->_build_action_column("FIRST", FALSE, $row_data));
            }
            $td = $this->wrap_column_item($obj, $col_name, $even_row);
            $this->_data_row->add( $td );
        } else {
            //show the normal data
            $td = $this->wrap_column_item($obj, $col_name, $even_row);
            $this->_data_row->add( $td );
        }


        if ($last_in_row_flag) {
            //lets see if we need to add an action column
            //as the first column.
            if ($this->_has_action_column("LAST")) {
                //looks like we have a LAST column actionbar
                //lets add it
                $this->_data_row->add($this->_build_action_column("LAST", FALSE, $row_data));
            }


            //manually render here to drastically cut down
            //on the memory useage for HUGE...HUGE lists
            $this->_data_table->add( $this->_data_row->render(0,0) );
            $this->_data_row = new TRtag;
            $this->_cur_col_cntr = 0;
        } else {
            $this->_cur_col_cntr++;
        }
    }

    /**
     * This function ensures that the data we place
     * in a column is aligned according to what the
     * user wants.
     *
     * @param mixed - $obj - the data for the td.
     * @param string - $col_name - the name of the column header
     *                             for this row to render.
     * @param int - $odd_row - tells us if this cell lives in
     *                         an odd # row (for alternating row colors)
     * @param int - the column # we are working on.
     * @return TDtag object
     */
    protected function wrap_column_item($obj, $col_name, $even_flag) {
        //make sure its set to something.
        if (!is_object($obj) && $obj == '') {
            $obj = "&nbsp;";
        }

        if ($this->alternating_row_colors && !$even_flag) {
            if ($this->_columns[$col_name]["data_name"] == $this->orderby()) {
                $class = "datalist_data_cell_odd_selected";
            } else {
                $class = "datalist_data_cell_odd";
            }
        } else {
            if ($this->_columns[$col_name]["data_name"] == $this->orderby()) {
                $class = "datalist_data_cell_selected";
            } else {
                $class = "datalist_data_cell";
            }
        }
        $align = $this->_columns[$col_name]["align"];
        $td = new TDtag(array("align" => $align,
                              "class" => $class));

        if (is_object($obj) && $obj->get_tag_name() == "td") {
            return $obj;
        } else {
            $td->add( $obj );
        }
        return $td;
    }



    /**
     * This function builds the object/text
     * to be used for a column header. It can
     * either be an href because its sortable,
     * or it can just be text, because its not
     * sortable.
     *
     * @param string $col_name - the column name
     *                           to build from
     *                           the headers.
     * @param array $col_data - the column's data.
     * @param int the column # we are working on.
     * @return mixed - either an Atag object or
     *                 raw text.
     */
    protected function build_header($col_name, $col_data, $col_num) {

        $td = new TDtag(array("class"=>"datalist_col_head",
                              "width" => $col_data["size"]));

        if ($this->_columns[$col_name]["sortable"]) {
            $col_url = $this->build_column_url($col_name);
            $td->set_tag_attribute("onclick", $col_url);

            $td->set_tag_attribute("title","Sort By ".$col_name);

            $td->add( $col_name );

            //$td->add(html_a($col_url, $col_name,"head_link"));

            if ($this->_columns[$col_name]["data_name"] == $this->orderby()) {

                if ($this->reverseorder() == "false") {
                    $alt_title = "Sorted in Ascending Order";
                    $img = html_img($this->get_image_path()."/picto_down.gif",11,11,'',$alt_title);
                    $img->set_tag_attribute("style", "padding-left: 5px;margin-left:5px;vertical-align:middle;");
                    $td->add($img);
                } else {
                    $alt_title = "Sorted in Descending Order";
                    $img = html_img($this->get_image_path()."/picto_up.gif",11,11,'',$alt_title);
                    $img->set_tag_attribute("style", "padding-left: 5px;margin-left:5px;vertical-align:middle;");
                    $td->add($img);
                }
            }

            // we want to highlight the td on mouse over
            $td->set_tag_attribute("onmouseover",
                                   "javascript:style.cursor='pointer';this.className='datalist_col_head_hover';");
            $td->set_tag_attribute("onmouseout",
                                   "javascript:this.className='datalist_col_head'");
            $td->set_tag_attribute("onmousedown",
                                   "javascript:this.className='datalist_col_head_clicked'");

            $td->set_tag_attribute("onclick", $col_url);

        } else {
            $td->add($col_name);
            $td->set_tag_attribute("style", "padding-left:5px;padding-right:5px;white-space:nowrap;");
        }

        return $td;
    }


    /**
     * This function adds an action column.  This
     * adds a column of either checkboxes or radio
     * buttons.
     *
     * @param string - type of column
     *                 'checkbox' or 'radio'
     * @param string - which column it lives in
     *                 'FIRST' or 'LAST'
     * @param string - which db field is associated
     *                 with this.
     * @param string - the title to use for the column.
     *                 NOTE: if this is set, then there
     *                       will NOT be a global checkbox
     *                       that can be used to select/deslect
     *                       all at once.
     *
     */
    protected function add_action_column($type, $col, $db_field, $title=NULL) {
        $action = array("type" => $type,
                        "dbfield" => $db_field,
                        "title" => $title);
        $this->_action_column[$col] = $action;
    }

    /**
     * This function is used to set the default list
     * of selected checkbox items.  This is used so
     * the user can pre-populate the list of
     * checked items in the checkbox action column
     *
     * @param array - the array of checked items
     */
    protected function set_default_checked_items($items) {
        $this->_default_checked_items = $items;
    }

    /**
     * This function returns the array of default
     * checked items to be marked as checked in
     * the checkbox action column
     *
     * @return array
     */
    protected function get_default_checked_items() {
        return $this->_default_checked_items;
    }

    /**
     * set the flag to tell the object to
     * save the checked items
     *
     * NOTE: this only works if we are in POST mode.
     *       GET can easily fail because of too many
     *       items saved on the query string.
     *
     * @param boolean TRUE = enable
     */
    protected function save_checked_items($flag=TRUE) {
        if ($this->get_form_method() == 'POST') {
            $this->_save_checked_items_flag = $flag;
        } else {
            user_error(__CLASS__."::".__FUNCTION__."() - Cannot be used while form method is GET.  ".
                       "You should call DataList::set_form_method('POST') first.<br>", E_USER_ERROR);
        }
    }

    /**
     * This tests the object flag to
     * see if the child class wants to
     * automatically save the checked
     * items
     *
     * @return boolean
     */
    private function _save_checked_items_enabled() {
        return $this->_save_checked_items_flag;
    }


    /************************************/
    /** Action column/bar related stuff */
    /************************************/



    /**
     * This builds an action column cell
     *
     * @param string - the column to test for
     *                 FIRST or LAST
     * @param boolean - lets us know this is for
     *                  the header or a cell.
     * @param array   - the row's data.
     * @return HTMLTag object
     */
    protected function _build_action_column($col, $header_flag=FALSE, $row_data=NULL) {

        $attributes = array("width" => "1%",
                            "align" => "center");

        if ($header_flag) $attributes["class"] = "datalist_col_head";
        else $attributes["class"] = "datalist_actionbar_data_cell";

        $td = new TDtag($attributes);
        $form_value = '';
        if ($header_flag) {
            //this is for a header item.
            $form_value = "";
        } else {
            $form_value = $row_data[$this->_action_column[$col]["dbfield"]];
        }
        switch ($this->_action_column[$col]["type"]) {
        case DefaultHTMLDataList::ACTION_RADIO:
            if ($header_flag) {
                //we don't put a header button for radio
                if ($this->_action_column[$col]["title"]) {
                    $obj = $this->_action_column[$col]["title"];
                } else {
                    $obj = phphtmllib::_HTML_SPACE;
                }
            } else {
                $name = $this->_vars["radioVar"][DataList::VAR_NAME];
                $obj = form_radio($name, $form_value);

                //see if the checkbox should be disabled
                if (!$this->is_action_enabled($form_value, $row_data)) {
                    $obj->set_tag_attribute("DISABLED");
                    $obj->set_tag_attribute("value","");
                }
            }

            break;

        case DefaultHTMLDataList::ACTION_CHECKBOX:
            if ($header_flag) {
                //see if the child wants a title instead
                //of the global check/uncheck checkbox
                if ($this->_action_column[$col]["title"]) {
                    $obj = $this->_action_column[$col]["title"];
                    break;
                } else {
                    $name = $this->_vars["checkboxVar"][DataList::VAR_NAME];
                }
            } else {
                $name = $this->_vars["checkboxVar"][DataList::VAR_NAME]."[".$this->_action_count."]";
            }

            $this->_action_count++;
            $obj = form_checkbox($name, $form_value);
            if ($header_flag) {
                if ($this->_allow_select_all) {
                    $obj->set_tag_attribute("onclick", "javascript:mass(this.form)");
                } else {
                    $obj = phphtmllib::_HTML_SPACE;
                }
            }

            //see if the checkbox should be checked
            if ($this->_is_col_checked($form_value, $row_data)) {
                $obj->set_tag_attribute("CHECKED");
            }

            //see if the checkbox should be disabled
            if (!$header_flag && !$this->is_action_enabled($form_value, $row_data)) {
                $obj->set_tag_attribute("DISABLED");
                $obj->set_tag_attribute("value","");
            }

            //save which items we have rendered visibly.
            //so we can filter those out in the hidden
            //items
            $this->_visible_checkbox_items[$form_value] = TRUE;
            break;
        }
        $td->add($obj);
        $td->set_collapse();
        return $td;
    }

    /**
     * This method checks to see if a
     * particular row has been checked
     * in the action column
     *
     * @param string - the item to look for
     * @param array   - the row's data.
     * @return boolean.
     */
    protected function _is_col_checked($value, $row_data) {
        if (count($this->_hidden_checkbox_items) == 0) {
            if (isset($_REQUEST[$this->_vars["checkboxVar"][DataList::VAR_NAME]]) && is_array($_REQUEST[$this->_vars["checkboxVar"][DataList::VAR_NAME]])) {
                $this->_hidden_checkbox_items = array_flip($_REQUEST[$this->_vars["checkboxVar"][DataList::VAR_NAME]]);
            }
        }

        //call the child function to see if item should
        //be checked
        $user_flag = $this->is_action_checked($value, $row_data);
        $hidden_flag = isset($this->_hidden_checkbox_items[$value]);

        return($user_flag || $hidden_flag);

        if (isset($this->_hidden_checkbox_items[$value])) {
            return TRUE;
        } else {
            return FALSE;
        }
    }

    /**
     * This function is provided to give the child class
     * the ability to precheck/select a particular
     * column.
     *
     * @param string - the item to look for.
     * @param array   - the row's data.
     * @return boolean
     */
    protected function is_action_checked($value, $row_data) {
        return FALSE;
    }

    /**
     * This function is provided to give the child
     * class the ability to enable/disable a particular
     * checkbox.
     *
     * @param string - the item to look for.
     * @param array   - the row's data.
     * @return boolean
     */
    protected function is_action_enabled($value, $row_data) {
        return TRUE;
    }

    /**
     * This function renders the action bar at the bottom
     * of the data list.
     *
     * @return TABLEtag object
     */
    protected function _build_actionbar() {

        if ($this->show_actionbar()) {

            $table = TABLEtag::factory($this->get_width(), 0, 0, 0, $this->get_align());
            $table->set_class("datalist_actionbar");
            /*if ($this->show_outer_border()) {
                $table->set_tag_attribute("style", _CSS_BORDER_LEFT.
                                          _CSS_BORDER_RIGHT.
                                          _CSS_BORDER_BOTTOM);
            }
            else {
                $table->set_tag_attribute("style", _CSS_BORDER_TOP);
            }*/

            $td = new TDtag(array("class"=>"datalist_bottom_seperator",
                                  "colspan" => 3),
                            phphtmllib::_HTML_SPACE);
            $table->add_row( $td );

            $table->add_row($this->_build_actionbar_arrow_cell("FIRST"),
                            $this->_build_actionbar_data_cell(),
                            $this->_build_actionbar_arrow_cell("LAST") );

            return $table;
        } else return NULL;
    }

    /**
     * This function builds a TD with the
     * appropriate action arrow.
     *
     * @param string - FIRST or LAST
     * @return TDtag
     */
    protected function _build_actionbar_arrow_cell($col) {
        $td = new TDtag(array("class" => "datalist_title",
                              "style" => "padding-left:14px;padding-right:14px;".
                              "padding-top:5px;",
                              "width" => "5%")
                       );

        if ($col == "FIRST") {
            $td->set_tag_attribute("align", "left");
            if ($this->_has_action_column("FIRST") &&
                $this->_datalistsource->get_total_rows()) {
                $td->add(html_img($this->get_image_path()."/arrow_right.gif"));
            } else {
                $td->add("&nbsp;");
            }
        } else {
            $td->set_tag_attribute("align", "right");
            if ($this->_has_action_column("LAST") &&
                $this->_datalistsource->get_total_rows()) {
                $td->add(html_img($this->get_image_path()."/arrow_left.gif"));
            } else {
                $td->add("&nbsp;");
            }
        }
        return $td;
    }

    /**
     * This function builds the user's data cell
     *
     * @return TDtag;
     */
    protected function _build_actionbar_data_cell() {
        $td = new TDtag(array("class" => "datalist_title",
                              "style" => "padding-left:5px;padding-right:5px;".
                              "padding-top:5px;padding-bottom:5px")
                       );

        $flag = FALSE;
        if ($this->_has_action_column("FIRST")) {
            $flag = TRUE;
            $td->set_tag_attribute("align", "left");
        } else if ($this->_has_action_column("LAST")) {
            $flag = TRUE;
            $td->set_tag_attribute("align", "right");
        }

        if ($flag && $this->_datalistsource->get_total_rows()) {
            $td->add($this->actionbar_cell());
        } else {
            $td->add("&nbsp;");
        }

        return $td;
    }

    /**
     * this is the method that builds
     * the contents for the middle actionbar
     * td cell.
     * NOTE this function is meant to be overriden
     *      by the child class.
     *
     * @return Container object
     */
    protected function actionbar_cell() {
        return phphtmllib::_HTML_SPACE;
    }


    /**
     * This function tests to see if the child
     * wants to render an action column
     *
     * @param string - the column to test for
     *                 FIRST or LAST
     * @return boolean
     */
    protected function _has_action_column($col) {
        if (isset($this->_action_column[$col])) {
            return TRUE;
        } else {
            return FALSE;
        }
    }

    /**
     * This allows the caller to
     * turn on/off the rendering of
     * the bottom action bar row
     *
     * @param boolean - TRUE = on FALSE = off
     */
    protected function set_actionbar($flag = TRUE) {
        $this->_show_actionbar = $flag;
    }

    /**
     * This function gets the current value
     * of the show actionbar flag setting.
     *
     * @return boolean
     */
    protected function show_actionbar() {
        return $this->_show_actionbar;
    }


    /**
     * This function sets the ability to show
     * a collapseable search box or not.
     *
     * @param boolean
     */
    protected function set_collapseable_search($flag = TRUE ) {
        $this->_collapsable_search = $flag;
    }


    /**
     * This function builds an action button that will
     * modify the form action, to post to a different
     * script to handle the data
     *
     * @param string - the button name
     * @param string - the script that gets called.
     * @param string - extra js to put prior to the submit();
     * @return INPUTtag object
     */
    function action_button($name, $action = "", $javascript = "") {

        $submit = form_submit("_action", $name);

        // here we make sure that all standard buttons look the same
        if (strlen($name)<10) $submit->set_tag_attribute("style","width: 80px;");

        $form_name = $this->get_form_name();

        $onclick = "javascript: ";
        if ($action != "") {
            $onclick  .= "document.".$form_name.".action='".$action."';";
        }

        if ($javascript != "") {
            $onclick .= $javascript . ";";
        }

        $onclick .= "document.".$form_name.".submit();";


        if ($action != '' || $javascript != '') {
            $submit->set_tag_attribute("onclick", $onclick);
        }

        return $submit;
    }

    /**
     * This function returns any Javascript required
     * for this widget
     *
     * @return mixed
     */
    function get_javascript() {
        $js = '';

        if ($this->_collapsable_search) {
            $js .= $this->_search_javascript();
        }


        if ($this->_has_action_column(DefaultHTMLDataList::ACTION_FIRST) || $this->_has_action_column(DefaultHTMLDataList::ACTION_LAST)) {
            $last = isset($this->_action_column["LAST"]["type"]) ? $this->_action_column["LAST"]["type"] : '';
            $first = isset($this->_action_column["FIRST"]["type"]) ? $this->_action_column["FIRST"]["type"] : '';
            if ($last == "checkbox" || $first == "checkbox") {
                $js .= $this->_checkbox_javascript();
            }
        }

        if (strlen($js) > 0) {
            $script = new SCRIPTtag(array('language' => 'Javascript', 'type' =>'text/javascript'));
            $script->add($js);
            return $script;
        } else {
            return NULL;
        }
    }

    /**
     * This function builds the JS needed for the checkbox
     * action column
     *
     * @return SCRIPTtag
     */
    protected function _checkbox_javascript() {
        $var_name = $this->_vars["checkboxVar"][DataList::VAR_NAME];

        $js  = "function mass(form) {\n";
        $js .= "  var i=0;\n";
        $js .= "  var value=0;\n\n";
        $js .= "  if (form.".$var_name.".checked) {\n";
        $js .= "    value=1;\n";
        $js .= "  } else {\n";
        $js .= "    value=0;\n";
        $js .= "  }\n\n";
        $js .= "  for (i = 0; i < form.length; i++) {\n";
        $js .= "    if (form.elements[i].name.substring(0, ".strlen($var_name).") == '".$var_name."' && !form.elements[i].disabled) {\n";
        $js .= "      form.elements[i].checked = value;\n";
        $js .= "    }\n";
        $js .= "  }\n";
        $js .= "}\n";

        return $js;
    }

    /**
     * This function builds the JS needed for
     * collapsable search
     *
     * @return string - js code
     */
    protected function _search_javascript() {
        $js = "var tree_open = new Image();\n".
              "tree_open.src = '/images/widgets/tree_open.gif';\n".
              "var tree_closed = new Image();\n".
              "tree_closed.src = '/images/widgets/tree_closed.gif';\n".

              "function toggle_tree(id) {\n".
              "element = document.getElementById(id);\n".
              "img = document.getElementById('i'+id);\n".
              "if (!element) return;\n".

              "if (element.style.visibility=='visible' || element.style.visibility=='') {\n".
              "    element.style.visibility = 'hidden';\n".
              "    element.style.overflow = 'hidden';\n".
              "    element.style.height='1px';\n".
              "    img.src = tree_closed.src;\n".

              "document.forms['" . $this->get_form_name() . "']._search_tree_open.value=0;\n".
              "}\n".
              "else {\n".
              "    element.style.visibility = 'visible';\n".
              "    element.style.overflow = 'visible';\n".
              "    element.style.height='';\n".
              "    img.src = tree_open.src;\n".
              "document.forms['" . $this->get_form_name() . "']._search_tree_open.value=1;\n".
              "}\n".
              "document.getElementById('l'+id).blur();\n".
              "}";

        return $js;
    }


    /********************************/
    /*      SEARCH RELATED          */
    /********************************/


    /**
     * This method is used to return the
     * HTMLDataListSearchFormContent child
     * class that will be used as the
     * search form for this datalist.
     *
     * @return HTMLDataListSearchFormContent child
     */
    protected function build_search_formcontent() {
        return new HTMLDataListSimpleSearchFormContent;
    }

    /**
     * This builds the table that holds the search
     * capability.
     *
     * @return TABLEtag object.
     */
    protected function get_search_formcontent_layout() {
        //the search capability is enabled.
        //lets try and build the table.
        $td_attributes = array("style" => "padding-left: 5px;padding-bottom:4px;".
                               "padding-right:40px;padding-top:4px;".
                               "background-color: #eeeeee;",
                               "align" => "left",
                               "class" => "font10");

        $table = TABLEtag::factory($this->get_width(), 0, 0, 0, $this->get_align());

        if (isset($_REQUEST["_search_tree_open"])) {
            // set the search tree state
            $this->_search_tree_open = $_REQUEST["_search_tree_open"];
        }

        //test to see if they want to render the outer borders
        $table->set_tag_attribute("style", "border-left: 1px solid #a1a1a1;".
                                  "border-right: 1px solid #a1a1a1;");

        $td = new TDtag($td_attributes,
                        $this->_formcontent->form());
        $table->add_row($td);

        if ($this->_collapsable_search) {
            $div = new DIVtag(array("id"=>"search"), $table);
            if (!$this->_search_tree_open) {
                // hide search if tree is closed
                $div->set_tag_attribute("style", "visibility:hidden;height:1px;");
            }

            $this->set_save_vars(array("_search_tree_open" =>
                                       (int)$this->_search_tree_open));


            return Container::factory($this->_build_search_title(), $div);
        } else {
            return Container::factory($this->_build_search_title(), $table);
        }
    }



    /**
     * This function builds the search title table
     *
     * @return TABLEtag object
     */
    protected function _build_search_title() {
        //build the title stacked table
        $title = TABLEtag::factory($this->get_width(), 0, 0, 0, $this->get_align());

        if ($this->_collapsable_search) {
            // build link for collapsable search

            if ($this->_search_tree_open) $img_source = "tree_open.gif";
            else $img_source = "tree_closed.gif";

            $img = html_img("/images/widgets/" . $img_source, 10, 10);
            $img->set_tag_attribute("id", "isearch");

            $img = html_a("javascript:toggle_tree('search')", $img);

            $link = html_a("javascript:toggle_tree('search')", $this->_search_text["title"], "head_link");
            $link->set_tag_attribute("id", "lsearch");

            $c = Container::factory(phphtmllib::_HTML_SPACE, $img, $link);
        } else {
            $c = Container::factory(phphtmllib::_HTML_SPACE . $this->_search_text["title"]);
        }


        //test to see if they want to render the outer borders
        $title->set_tag_attribute("style","border: 1px solid #a1a1a1;");
        $title->add_row(new TDtag(array("class" => "datalist_title",
                                        "align" => "left"), $c));

        return $title;
    }

}

?>