<?php
/**
 * AjaxDataListSimpleSearchFormContent
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage DataList
 * 
 */

/**
 * This file is the simple search FormContent
 * for the Ajax DataList
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage DataList
 */

class AjaxDataListSimpleSearchFormContent extends HTMLDataListSimpleSearchFormContent implements Ajaxable {

    /**
     * Are we using ajax
     */
    protected $ajax = 1;

    protected $ajax_divid = 'pageBody';
    protected $ajax_target = NULL;

    const LABEL_SEARCHED = 'searched';

    /**
     * This member says we need to
     * render as part of an ajax
     * request
     */
    protected $ajax_mode = FALSE;

    /**
     * register some vars with the
     * Request object
     *
     * @return array
     */
    public function request_vars() {
        return array();
    }

    /**
     * This method creates the FormElements used
     * by the simple search
     *
     * @see FormContent
     * @return none
     */
    public function form_init_elements() {
        parent::form_init_elements();

        //we do this as a hook to avoid caching initial
        //search results.
        //we only want to cache if we haven't
        //pressed the search button.
        //$this->add_hidden_element(self::LABEL_SEARCHED);
        //$this->set_hidden_element_value(self::LABEL_SEARCHED, 0);
    }

    /**
     * We do this so a child can add their own buttons
     * as they see fit.
     *
     * @return void
     */
    public function form_init_buttons() {
        $button = new FEAjaxSubmitButton($this->build_label(HTMLDataListSearchFormContent::LABEL_SUBMIT));
        /*$element = $this->get_hidden_element(self::LABEL_SEARCHED);
        $id = $element->get_element_id();
        $click = "alert(document.getElementById('".$id."').value);".$button->onClick();
        $button->set_onClick($click);

        $button->set_ajax_replacement_divid('pageBody');
        */
        $this->add_button($button);
    }

    /**
     * This method is used to get the button with
     * a specific label
     *
     * @param string $label
     * @return FormElement object
     */
    protected function get_button($label) {
        $button = parent::get_button($label);
        if ($button instanceof FEAjaxSubmitButton) {
            //set the replacement divid
            //set the success message
            $button->set_ajax_replacement_divid($this->get_ajax_replacement_divid());
            $button->set_success_message($this->get_success_message());
        }
        return $button;
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
        $this->set_cancel_action($this->get_request_builder()->get_url());
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
        $this->set_cancel_action($this->get_request_builder()->get_url());
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
    public function get_request_builder($vars=array()) {
        return new RequestBuilder($this->get_ajax_target(),
                                  $vars,
                                  $this->get_ajax_replacement_divid());
    }

    /**
     * Returns a string message that will
     * be dislayed in a special message
     * area upon form success
     *
     * @return string
     */
    public function get_success_message() {
        return null;
    }

    /**
     * Returns RequestBuilder object
     * to redirect to a new target
     *
     * @return RequestBuilder
     */
    public function get_success_target() {
        return null;
    }

    /**
     * Returns an object to be rendered
     * upon success
     *
     * @return Container
     */
    public function get_success_object() {
        return null;
    }

     /**
     * Executed upon form success
     *
     */
    final public function form_success() {

        $obj = Container::factory($this->get_success_object());

        if ($message = $this->get_success_message()) {

            $js = SCRIPTtag::factory();
            $js->add('message_show("' . $message . '",2);');
            $obj->add($js);
        }

        return $obj->render();
    }

    /**
     * Sets ajax flag
     *
     * @param bool $flag
     */
    public function set_ajax($flag) {
        $this->ajax = $flag;
    }

}
?>
