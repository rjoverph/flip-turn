<?php
/**
 * AjaxablePage
 * 
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 */


/**
 * Main framework Ajaxable page class
 *
 * Provides functionality for registering
 * variables, checking permissions, etc
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 *
 */
abstract class AjaxablePage extends HTMLPage implements Ajaxable {

    /**
     * The default dom id value
     * that ajax request responeses
     * get sent.
     */
    const AJAX_ID = 'pageBody';

    /**
     * The ajax div id where
     * responses go for this page.
     */
    protected $ajax_divid = self::AJAX_ID;

    /**
     * The ajax target object.
     */
    protected $ajax_target = NULL;


    /*** PAGE BLOCKS ***********************************************************************/


    /**
     * Builds our body content
     * featuring ajax supported body
     * and message notification areas
     *
     */
    public function body_content() {
        $this->add($this->header_block());

        // we wrap all the body content
        // into a div with an ID
        $this->add(new DIVtag(array('id' => self::AJAX_ID),
                              $this->body_block()));

        $this->add($this->footer_block());
    }



    /*** LAYOUT FUNCTIONS *******************************************************************/


    /**
     * Render the page.
     *
     *
     * @return string the raw html output.
     */
    public function render() {

        if (Request::singleton()->is_ajax()) {
            // if we are going through ajax
            // request, let's process page
            // body only

            if ($this->has_permission()) {
                return $this->render_ajax_content(Request::singleton()->get('ajaxdivid'));
            }

        } else {
            return parent::render();
        }
    }

    /**
     * This method is called when we only want to
     * build the content for an ajax request.
     * Instead of building the entire page layout,
     * just build the 'main content' block that will
     * be replaced on the current page.
     *
     * @todo What is the point of this switch statement? - cwright
     *       To show an example of how to code this in the child
     *       class for different ids.
     *
     * @param string the div id that the request
     *               is meant to replace.
     * @return string
     */
    protected function render_ajax_content($div_id) {
        switch ($div_id) {

        case AjaxablePage::AJAX_ID:
            /**
             * The AJAX wants to replace the body_block()
             * content.
             */
            return $this->body_block()->render();
            break;

        default:
            /**
             * The AJAX request wants some other div id
             * replaced.  Lets look for it.
             */
            return $this->body_block()->render();
            break;
        }
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
            return get_class($this);
        } else {
            return $this->ajax_target;
        }
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
        return new AjaxRequestBuilder($this->get_ajax_target(),
                                      $vars,
                                      $this->get_ajax_replacement_divid());
    }

    /**
     * This function should return an array
     * of request variable names and their
     * properties in the following format:
     * array('key_name' => type)
     *
     * This function is called by the Controller
     * in order to pass it to the Request object
     *
     * @return array
     */
    public function request_vars() {
        return array();
    }

}
?>
