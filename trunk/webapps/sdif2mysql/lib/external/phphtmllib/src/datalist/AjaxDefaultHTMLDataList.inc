<?php
/**
 * AjaxDefaultHTMLDataList
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage DataList
 */

/**
 * This file contains the Ajax DataList
 * for use in the framework.
 *
 * @package phpHtmlLib-framework
 * @subpackage DataList
 */

abstract class AjaxDefaultHTMLDataList extends DefaultHTMLDataList implements Cacheable, Ajaxable {

    protected $ajax_divid = 'idDataList';
    protected $ajax_target = NULL;

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


    public function getRequestVars() {

        $vars = array();

        foreach($this->_vars as $key => $value) {
            $vars[DataList::VAR_NAME] = '';
        }

        return $vars;
    }

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
        return 10;
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

    /**
     * This method is used to return the
     * HTMLDataListSearchFormContent child
     * class that will be used as the
     * search form for this datalist.
     *
     * @return HTMLDataListSearchFormContent child
     */
    protected function build_search_formcontent() {
        $form = new AjaxDataListSimpleSearchFormContent;
        $form->set_ajax_replacement_divid($this->get_ajax_replacement_divid());
        $form->set_ajax_target($this->get_ajax_target());
        return $form;
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
            $r = $this->build_base_url();
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
     * state of the DBItemList.  This is used for pages
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
}
?>
