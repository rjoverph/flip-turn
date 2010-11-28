<?php
/**
 * PostRequestBuilder
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Request
 */


/**
 * This file contains the PostRequestBuilder
 * which is used for building ajax post
 * requests
 *
 * This class is a special case to help build
 * urls for doing POST requests in ajax mode.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Request
 */
class PostRequestBuilder extends RequestBuilder {

    /**
     * the message used along with the
     * ajax post.
     */
    protected $post_message = '';

    /**
     * The form id
     */
    protected $formId;

    /**
     * Public constructor
     *
     * @param string $id           - id of the form element to post.
     * @param array $values        - array of key=>value pairs to add.
     * @param mixed $formId        - id of the form tag
     *
     *
     */
    public function __construct($target, $values=array(), $formId) {
        parent::__construct($target, $values);
        $this->formId = $formId;
    }

    /**
     * The message to send in the post request
     *
     * @param string $message
     *
     * @todo nuke this ?
     */
    public function set_post_message($message) {
        $this->post_message = $message;
    }

    /**
     * Returns a url for a POST for non ajax mode.
     *
     * @return string
     */
    public function get_url() {
        return 'javascript:' . $this->get_js();
    }

    /**
     * Returns js call for a POST for non ajax mode.
     *
     * @return string
     */
    public function get_js() {
        return $this->get_js_fields() . 'form.submit();';
    }

    /**
     * Builds and returns js code that
     * sets all form fields
     *
     * @return string
     */
    protected final function get_js_fields() {
        $js = "var f=$('" . $this->formId . "');";

        foreach($this->data as $name => $value ) {
            $js .= "f." . $name . ".value='" . $value . "';";
        }

        return $js;
    }

    /**
     * Returns ajax version of the url
     *
     */
    public function get_ajax_url() {
        $this->set('ajax', 1);

        $form = "\$('".$this->form_id."')";

        $prefix_js = "form=".$form.';';
        foreach( $this->data as $name => $value ) {
            if (!array_key_exists($name, $this->registered_vars)) {
                $prefix_js .= "form.".$name.".value='".$value."';";
            }
        }

        // wrap it into javascript call
        $ret = "javascript:".$prefix_js."p(form,'" . $this->get_ajax_id() . "','')";

        return $ret;

    }

    /**
     * This method is used for building an action value for
     * a form tag.  We don't always want all the vars passed
     * in the action.  This is valud for POST type forms
     *
     * @return string
     */
    public function get_form_action_url() {
        return self::$prefix;
    }

}

?>
