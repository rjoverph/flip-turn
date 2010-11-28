<?php
/**
 * This is the simple AjaxHTMLDataList class
 * which is a base class for building
 * generic Ajaxable DataLists that can
 * look like anything you want.
 *
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage DataList
 */


/**
 * This builds the base Ajaxable HTMLDataList parent class.
 * You must extend this class to use it.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage DataList
 */
abstract class AjaxHTMLDataList extends HTMLDataList implements Ajaxable,Cacheable {

    /**
     * The cache lifetime in seconds.
     *
     */
    const CACHE_LIFETIME = 60;



    /**
     * Flag to let us know that search
     * is enabled.
     *
     */
    protected $_search_flag = TRUE;


    protected $ajax_divid = 'idmyahdl';
    protected $ajax_target = NULL;


    protected $_cur_col_cntr;

    protected $alternating_row_colors = FALSE;



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

        //so we only replace outself automatically.
        $this->set_ajax_replacement_divid($this->get_div_id());

        parent::__construct($title, $width, $default_orderby, $default_reverseorder);
    }

    /**
     * Render the output
     *
     * @param int $indent_level
     * @param int $output_debug
     */
    public function render($indent_level=0, $output_debug=0) {

        $div_wrapper = $this->get_wrapper();

        //lets see if we have errors.
        if ($this->has_errors()) {
            $div_wrapper->add( $this->get_errors() );
        }

        //add the javascript
        $div_wrapper->add( $this->_javascript() );

        //do they want a search box?
        if ($this->is_search_enabled()) {
            //ok now add the SearchFormContent
            $this->_form->add( $this->get_search_formcontent_layout() );
        }


        //add the form tag
        $div_wrapper->add($this->_form);


        //the outer table container
        $this->_data_table = TABLEtag::factory($this->get_width(), 0, 0, 2, $this->get_align());
        $this->_form->add( $this->_data_table );
        $this->_data_table->set_class("datalist_border");

        $title_table = html_table("100%");

        $title = new TDtag(array("align" => "left",
                                 "class" => "myhikkup_datalist_title",
                                 "style" => "padding-left: 5px;"),
                           $this->get_title() );

        //pagination controls
        $table = TABLEtag::factory('', 0, 0, 0);
        $table->set_collapse();

        //the page info
        $td = new TDtag(array("style"=>"color: black;background-color: #eeeeee;".
                              "padding-left: 2px; padding-right: 2px; border:1px inset #cccccc;"));
        $td->add($this->get_page_info());

        //only show the jump links if we have more then 1 page worth
        if ($this->get_num_pages() == 1) {
            $table->add_row( phphtmllib::_HTML_SPACE );
        } else {
             //build the pagination piece
        switch ($this->pagination_style) {
        case HTMLDataList::PAGE_STYLE_JUMP:
            $table->add_row( $this->build_jump_links() );
            break;

        case HTMLDataList::PAGE_STYLE_NAVIGATE:
            $table->add_row( $this->build_tool_img("prev"), phphtmllib::_HTML_SPACE,

                             $td,
                             phphtmllib::_HTML_SPACE,

                             $this->build_tool_img("next"),phphtmllib::_HTML_SPACE,
                             new TDtag(array("style"=>"font-size: 1px; line-height: 1px; width:10px;"), phphtmllib::_HTML_SPACE)

                            );
            break;
        }
        }



        $spacer_div = new DIVtag(array('style' => 'padding-top: 3px; padding-bottom:3px;'),
                                 $table);
        $this->_tool_td = TDtag::factory('datalist_title', "right", $spacer_div);

        $title_table->add( new TRtag( array(), $title, $this->_tool_td) );

        //add the header tr reference
        //it will get populated later
        $cols = count($this->_columns);
        $this->_data_table->add_row( new TDtag(array("colspan" => $cols,
                                                     "style" => "border-bottom:2px solid black;"),
                                               $title_table) );


        //COLUMN HEADERS
        //now build the column headers
        $header_tr = new TRtag;
        $column_count = count($this->_columns);

        foreach( $this->_columns as $name => $col ) {
            $header_tr->add($this->build_header( $name, $col, $column_count) );
        }

         $this->_data_table->add($header_tr);

        //initialize the first date row
        $this->_data_row = new TRtag;

        if ($this->_query_worked) {
            //now walk the list of rows and build and add the
            //cells of data
            $even = TRUE;

            //ok iterate over each row from the datalistsource (Iterator)
            foreach( $this->_datalistsource as $row_data)  {
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
     * This method builds the FORMtag object
     */
    protected function build_form() {
        //force a non ajax request builder
        //as we want a non ajax url for the action attribute.
        $builder = $this->get_request_builder(array(), FALSE, TRUE);
        $request = $builder->get_url();

        $this->_form = FORMtag::factory($this->_default_form_name,
                                        $request,
                                        $this->_form_method,
                                        array('style' => "margin-top: 0px;margin-bottom:0px;",
                                              'id' => $this->get_form_id()));
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
        
        $button = new FEAjaxSubmitButton($name);
        $button->set_ajax_replacement_divid($this->get_ajax_replacement_divid());
        return $button;        
    }
    
    


    /*************************/
    /* Internals to DataList */
    /*************************/

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
        static $col_count=1;

        if ($col_count == 1) {
            $col_head_class = 'datalist_col_headf';
            $col_head_hover = 'datalist_col_head_hoverf';
            $col_head_clicked = 'datalist_col_head_clickedf';
        } else {
            $col_head_class = 'datalist_col_head';
            $col_head_hover = 'datalist_col_head_hover';
            $col_head_clicked = 'datalist_col_head_clicked';
        }
        $col_count++;

        $td = new TDtag(array("class"=>$col_head_class,
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
                    $img = IMGtag::factory($this->get_image_path()."/picto_down.gif",11,11,'',$alt_title);
                    $img->set_tag_attribute("style", "padding-left: 5px;margin-left:5px;vertical-align:middle;width:11px;height:11px;");
                    $td->add($img);
                } else {
                    $alt_title = "Sorted in Descending Order";
                    $img = IMGtag::factory($this->get_image_path()."/picto_up.gif",11,11,'',$alt_title);
                    $img->set_tag_attribute("style", "padding-left: 5px;margin-left:5px;vertical-align:middle;width:11px;height:11px");
                    $td->add($img);
                }
            }

            // we want to highlight the td on mouse over
            $td->set_tag_attribute("onmouseover",
                                   "javascript:style.cursor='pointer';this.className='".$col_head_hover."';");
            $td->set_tag_attribute("onmouseout",
                                   "javascript:this.className='".$col_head_class."'");
            $td->set_tag_attribute("onmousedown",
                                   "javascript:this.className='".$col_head_clicked."'");

            $td->set_tag_attribute("onclick", $col_url);

        } else {
            $td->add($col_name);
            $td->set_tag_attribute("style", "padding-left:5px;padding-right:5px;white-space:nowrap;");
        }

        return $td;
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
    protected function add_row_cell($obj, $col_name, $last_in_row_flag, $row_data, $even_row) {
        if (!$this->_cur_col_cntr) {
            $this->_cur_col_cntr = 1;

            $td = $this->wrap_column_item($obj, $col_name, $even_row);
            $this->_data_row->add( $td );
        } else {
            //show the normal data
            $td = $this->wrap_column_item($obj, $col_name, $even_row);
            $this->_data_row->add( $td );
        }


        if ($last_in_row_flag) {

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
            $r = $this->get_request_builder();
            $r->set($this->_vars["offsetVar"][DataList::VAR_NAME], $this->offset());
            $r->set($this->_vars["orderbyVar"][DataList::VAR_NAME], $order_value);
            $r->set($this->_vars["reverseorderVar"][DataList::VAR_NAME], $reverse_value);
            return $r->get_url();
        } else {
            //handle the normal get.
            $r = $this->build_base_url();

            $r->set($this->_vars["offsetVar"][DataList::VAR_NAME], 0);
            $r->set($this->_vars["orderbyVar"][DataList::VAR_NAME], $order_value);
            $r->set($this->_vars["reverseorderVar"][DataList::VAR_NAME], $reverse_value);

            return $r->get_url();
        }
    }

    /**
     * this function is used to build a sub query string
     * of all of the query string vars to save the
     * state of the DataList.  This is used for pages
     * that want to come back to the list at the same state
     *
     * @param int - the offset for the link
     * @param boolean - add the expandrows value to the url
     * @param int - the expandrows value to use if the flag is on
     * @param RequestBuilder
     */
    protected function build_state_vars_query_string($offset, $expandrows_flag=FALSE,
                                                     $expandrows_value=0, $r) {
        $r->set($this->_vars["offsetVar"][DataList::VAR_NAME], $offset);
        $r->set($this->_vars["orderbyVar"][DataList::VAR_NAME], $this->orderby());
        $r->set($this->_vars["reverseorderVar"][DataList::VAR_NAME], $this->reverseorder());

        if ( $expandrows_flag ) {
            $r->set($this->_vars["expandrowsVar"][DataList::VAR_NAME], $expandrows_value);
        }
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
        $r = $this->build_base_url();
        $this->build_state_vars_query_string($offset,$expandrows_flag, $expandrows_value, $r);
        return $r->get_url();
    }


    /**
     * This builds the base url used
     * by the column headers as well
     * as the page tool links.
     *
     * it basically builds:
     * $_SELF?$_GET
     *
     * @return RequestBuilder
     */
    protected function build_base_url() {

        $r = $this->get_request_builder();
        //$r->import_request();
        $r->set('ajaxid', $this->get_ajax_replacement_divid());

        //now clean out stuff we don't want in there
        $r->delete($this->_vars["offsetVar"][DataList::VAR_NAME]);
        $r->delete($this->_vars["orderbyVar"][DataList::VAR_NAME]);
        $r->delete($this->_vars["reverseorderVar"][DataList::VAR_NAME]);
        $r->delete('_');
        //$r->delete(FormProcessor::FORM_ACTION);
        //have to suck this out or stuff breaks
        $r->delete('fajax');

        return $r;
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
        $c = parent::_build_default_vars();

        //We have to propogate the base vars
        //that the controller needs here.
        if ($this->_form_method == "POST") {
            //$request = $this->get_request_builder();
            $c->add(new FEHidden('target', $this->get_ajax_target()));
            $c->add(new FEHidden('ajax', 1));
            $c->add(new FEHidden('ajaxid', $this->get_div_id()));
        }


        return $c;
    }



    /**
     * This method builds the container/div
     * that holds the entire output
     *
     * @return Container
     */
    protected function get_wrapper() {
        //only return the wrapper if
        //we aren't called from an ajax
        //request.
        //otherwise we'll get multiple
        //wrappers...doh.
        if (Request::singleton()->is_ajax($this->get_div_id())) {
            $c = Container::Factory();
        } else {
            $c = DIVtag::factory();
            $c->set_tag_attribute('id', $this->get_div_id());
        }
        return $c;
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
        $this->set_ajax_replacement_divid($this->get_div_id());
    }


    /**********************/
    /* AJAXABLE INTERFACE */
    /**********************/

    /**
     * This protected method allows us to return
     * the string that is the Target for any
     * ajax requests for urls.
     *
     * @return string
     */
    public function get_ajax_target() {
        if (is_null($this->ajax_target)) {
            $this->ajax_target = get_class($this);
        }
        return $this->ajax_target;
    }

    /**
     * This protected method allows us to return
     * the string that is the Target for any
     * ajax requests for urls.
     *
     * @return string
     */
    public function set_ajax_target($target) {
        $this->ajax_target = $target;
    }

    /**
     * This method is used to set the
     * replacement div id that
     * will get replaced as a result
     * of the ajax request.
     *
     * <div id="idreplace">
     *
     * @param string $divid
     * @return void
     */
    public function set_ajax_replacement_divid($divid) {
        $this->ajax_divid = $divid;
        if (isset($this->_formcontent)) {
            $this->_formcontent->set_ajax_replacement_divid($divid);
        }
    }

    /**
     * This method is used to get the
     * replacement div id that
     * will get replaced as a result
     * of the ajax request.
     *
     * <div id="idreplace">
     * @return string $divid
     */
    public function get_ajax_replacement_divid() {
        return $this->ajax_divid;
    }


    /**
     * This method is used to construct a
     * RequestBuilder object that uses
     * the replacement divid and ajax target.
     *
     * @param array $vars
     * @return RequestBuilder
     */
    public function get_request_builder($vars=array(), $ignore_post=FALSE, $no_ajax=FALSE) {
            $vars = array_merge($vars, $this->_save_vars);

            //special case to enforce no ajax
            if ($no_ajax) {
                $builder = new RequestBuilder($this->get_ajax_target(), $vars);
            } else if ($this->_form_method == "POST") {
                //we need to use the Post version
                $builder = new AjaxPostRequestBuilder($this->get_ajax_target(), $vars,
                                                      $this->get_ajax_replacement_divid(),
                                                      $this->get_form_id());
                //force the mode to update
                $builder->set_mode(AjaxRequestBuilder::MODE_UPDATE);
                $builder->set_request_mode(AjaxPostRequestBuilder::POST_FORM_CONTENT);
            } else {
                $builder = new AjaxRequestBuilder($this->get_ajax_target(),
                                                  $vars, $this->get_ajax_replacement_divid());
                //force the mode to update
                $builder->set_mode(AjaxRequestBuilder::MODE_UPDATE);
            }


        return $builder;
    }

    /*******************************/
    /* Cacheable Interface Methods */
    /*******************************/

    /**
     * Are we a cacheable object or not?
     * We should only return yes if we
     * aren't in search mode.
     */
    public function is_cacheable() {
        if (Request::singleton()->get(FormProcessor::FORM_ACTION)) {
            return FALSE;
        } else {
            return TRUE;
        }
    }

    public function get_cache_lifetime() {
        return self::CACHE_LIFETIME;
    }

    public function get_cache_key() {
        //ok the key should be built dynamically.
        //based on the params used in the
        $key = get_class($this);

        foreach($this->_vars as $var) {
            $key .= $var[DataList::VAR_NAME].$var[DataList::VAR_VALUE].'_';
        }

        $key = substr($key, 0, -1);

        return $key;
    }
}

?>