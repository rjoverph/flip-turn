<?php
/**
 * AjaxPostRequestBuilder
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
class AjaxPostRequestBuilder extends PostRequestBuilder {

    /**
     * POST to something not associated
     * with a FormContent class.
     *
     */
    const POST_NORMAL = 0;
    /**
     * Special type of post method
     * used to post a FormContent form.
     *
     */
    const POST_FORM_CONTENT = 1;



    /**
     * This can be used to define what DOM element
     * to update. If not set, defaults to $formId
     *
     * @var string
     */
    protected $ajaxId;

    /**
     * The default mode of the generated url.
     *
     * @var unknown_type
     */
    protected $mode = AjaxRequestBuilder::MODE_UPDATE;

    /**
     * The type of POST we are doing.
     * This is used to tell us if we are
     * posting to a FormContent generated
     * form or a hand coded form.
     *
     * Default = Request::METHOD_GET
     */
    protected $request_mode = AjaxPostRequestBuilder::POST_NORMAL;


    /**
     * The constructor
     */
    public function __construct($target, $values=array(), $ajax_id, $formId) {
        parent::__construct($target,$values,$formId);
        $this->set_ajax_id($ajax_id);
    }

    /**
     * Sets ajax id
     *
     * @param string $ajaxId
     */
    public function set_ajax_id($ajaxId) {
        $this->ajaxId = $ajaxId;
    }

    /**
     * This method sets the default mode
     * for generating urls.  This forces
     * the get_url()/get_js() to a specific
     * mode.
     *
     * @param int $mode
     */
    public function set_mode($mode=self::MODE_UPDATE) {
        $this->mode = $mode;
    }

    /**
     * This method sets the default request
     * type for generating urls.  This forces
     * the get_url()/get_js() to a specific
     * mode.
     *
     * @param int $mode default AjaxPostRequestBuilder::POST_NORMAL
     */
    public function set_request_mode($mode=self::POST_NORMAL) {
        Validator::is_range($mode,null,0,1);

        $this->request_mode = $mode;
    }

    /**
     * get the type of post we are doing here.
     *
     * @return  int
     */
    public function get_request_mode() {
        return $this->request_mode;
    }


    /**
     * Get the current request method type
     *
     * @return  string
     */
    public function get_request_method() {
        return $this->request_method;
    }

    /**
     * Returns ajax id
     *
     * @return string
     */
    public function get_ajax_id() {
        if ($this->ajaxId) {
            return $this->ajaxId;
        }
        else {
            return $this->formId;
        }
    }

    /**
     * Returns js call for a POST for non ajax mode.
     *
     * @return string
     */
    public function get_js() {
        switch ($this->mode) {
            default:
            case AjaxRequestBuilder::MODE_UPDATE:
                if ($this->request_mode == self::POST_NORMAL) {
                    return $this->get_js_fields() . "ar_p_u(f,'" . $this->get_ajax_id() . "','')";
                } else {
                    return $this->get_js_fields() . "ar_fp_u(f,'" . $this->get_ajax_id() . "','')";
                }

                break;

            case AjaxRequestBuilder::MODE_APPEND:
                if ($this->request_mode == self::POST_NORMAL) {
                    return $this->get_js_fields() . "ar_p_a(f,'" . $this->get_ajax_id() . "','')";
                } else {
                    return $this->get_js_fields() . "aar_fp_a(f,'" . $this->get_ajax_id() . "','')";
                }
                break;
        }
    }

}

?>
