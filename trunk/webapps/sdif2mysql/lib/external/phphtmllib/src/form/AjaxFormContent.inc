<?php
/**
 * AjaxFormContent
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage FormEngine
 */


/**
 * This is a child of the FormContent class to
 * provide an ajaxable FormContent object
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage FormEngine
 *
 */
abstract class AjaxFormContent extends FormContent implements Ajaxable {

    /**
     * Are we using ajax
     */
    protected $ajax = 1;

    protected $ajax_divid = 'pageBody';
    protected $ajax_target = NULL;

    /**
     * The constructor
     *
     *
    public function __construct() {
        parent::__construct('', null, '');
    }*/

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
    public function form_success() {

       $obj = $this->get_success_object();

       $obj = Container::factory($obj);

        if ($message = $this->get_success_message()) {

            $script = SCRIPTtag::factory();
            $script->add("setTimeout('Effect.Fade(\'idMessage\');', 1000);");

            $js = SCRIPTtag::factory();
            $js->add('message_show("' . $message . '",2);');
            $obj->add($js);
        }

        return $obj;
    }

}

?>