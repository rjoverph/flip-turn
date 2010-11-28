<?php
/**
 * AjaxRequestBuilder
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Request
 */


/**
 * This class handles building of
 * a URL for AJAX requests
 *
 * @author Suren Markosian
 *
 * @package phpHtmlLib-framework
 * @subpackage Request
 *
 */
class AjaxRequestBuilder extends RequestBuilder {

    /**
     * For forcing the render mode
     * to a specific type of ajax
     * request.
     * This is typically NEVER needed
     * but for the DataList that just
     * builds an AjaxRequestBuilder
     * but the parent class just calls
     * build_url().  So we force the
     * mode to update by calling
     * set_mode();
     */
    const MODE_SIMPLE = 0;
    const MODE_UPDATE = 1;
    const MODE_APPEND = 2;
    const MODE_SIMPLE_SUCCESS = 3;

    /**
     * The default mode of the generated url.
     *
     * @var unknown_type
     */
    protected $mode = self::MODE_UPDATE;

    /**
     * Id of the DOM element to
     * be updated by the AJAX
     * request
     *
     * @var string
     */
    protected $ajaxId = AjaxablePage::AJAX_ID;

    /**
     * Public constructor
     *
     * @param string $target       - request target which is
     *                               the name of the page/widget
     *                               to be executed
     * @param array $values        - array of key=>value pairs to add.
     * @param mixed $ajaxId        - id where ajax results go if replace/append
     *
     *
     */
    public function __construct($target, $values=array(), $ajax_id=null) {
        parent::__construct($target, $values);
        $this->set_ajax_id($ajax_id);
    }

    /**
     * Sets id of the DOM element to
     * be updated via AJAX request
     *
     * @param string $ajaxId
     */
    public function set_ajax_id($ajaxId = AjaxablePage::AJAX_ID) {
        $this->ajaxId = $ajaxId;
    }

    /**
     * get the ajax replacement div id.
     *
     * @return string
     */
    public function get_ajax_id() {
        return $this->ajaxId;
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
     * Ajax specific methods.
     */

    /**
     * This method sets up a few
     * ajax required parameters
     */
    protected function setup_ajax_params() {
        $this->set('ajax', 1);
        $this->set('ajaxid', $this->get_ajax_id());
    }

    /**
     * Returns ajax request url.
     *
     * @param string $success_js the js function name to call upon success
     * @param string $failure_js the js function name to call if the
     *               ajax request fails.
     * @return string
     */
    public function get_url($success_js='', $failure_js='') {
        // wrap it into javascript call
        return 'javascript:' . $this->get_js($success_js, $failure_js);
    }

    /**
     * Returns the javascript calls to
     * perform an ajax call that replaces the contents
     * of an existing div on a page.
     *
     * If set_mode() was called, it will override
     * the function call.
     *
     * @return string
     */
    public function get_js($success_js='', $failure_js='') {
        $this->setup_ajax_params();
        // wrap it into javascript call
        if ($success_js) {
            return "ar_g_s_f('".parent::get_url() . "'," .$success_js. ",'".$failure_js."');";
        } else {
            //hack to force the mode to a
            //update or append
            if ($this->mode) {
                switch ($this->mode) {
                    case self::MODE_APPEND:
                        $func = 'ar_g_a';
                        break;
                    case self::MODE_UPDATE:
                        $func = 'ar_g_u';
                        break;

                    case self::MODE_SIMPLE:
                    default:
                        $func = 'ar_g';
                        break;
                }
            } else {
                $func = 'ar_g';
            }
            return $func."('" . parent::get_url() . "','" . $this->ajaxId . "')";
        }
    }

    /**
     * Returns ajax version of the url
     * that does a div replacement.
     *
     * @return string
     */
    public function get_replace_url() {
        // wrap it into javascript call
        return 'javascript:' . $this->get_replace_js();
    }

    /**
     * Returns the javascript calls to
     * perform an ajax call that replaces the contents
     * of an existing div on a page.
     *
     * @return string
     */
    public function get_replace_js() {
        $this->setup_ajax_params();
        // wrap it into javascript call
        return "ar_g_u('" . parent::get_url() . "','" . $this->ajaxId . "')";
    }

    /**
     * Returns ajax version of the url
     * that does appends to an existing div.
     *
     * @return string
     */
    public function get_append_url() {
        // wrap it into javascript call
        return 'javascript:' . $this->get_append_js();
    }

    /**
     * Returns the javascript calls to
     * perform an ajax call that appends the
     * results to an existing div on a page.
     *
     * @return string
     */
    public function get_append_js() {
        $this->setup_ajax_params();
        // wrap it into javascript call
        return "ar_g_a('" . parent::get_url() . "','" . $this->ajaxId . "')";
    }

    /**
     * This method is used to get the raw url
     * used to make the request
     *
     * @return string
     */
    public function get_raw_url() {
        return parent::get_url();
    }

    /**
     * Build a simple ajax request.  Optionally call a
     * javascript function upon success or failure of the
     * ajax request.
     *
     * @param string $target       - request target which is
     *                               the name of the page/widget
     *                               to be executed
     * @param array $values        - array of key=>value pairs to add
     * @param string $success_js   Optional javascript function that will
     *                             be called if the request works.
     * @param string $failure_js   Optional javascript function that will
     *                             be called if the request fails.
     *
     * @return string the url with query params
     */
    public static function build_url($target, $values=array(),
                                     $success_js='', $failure_js='') {
        $r = new AjaxRequestBuilder($target, $values);
        return $r->get_url();
    }

    /**
     * Build an ajax request that replaces the contents of an existing
     * div in the dom with the results of the ajax request.  This also
     * passes in parameters from the existing request to the Controller.
     *
     * @param string $target       - request target which is
     *                               the name of the page/widget
     *                               to be executed
     * @param array $values        - array of key=>value pairs to add
     * @param mixed $ajaxId        - id where ajax results go
     *
     * @return string the url with query params.
     */
    public static function build_url_with_request($target, $values=array(),
                                                  $success_js='', $failure_js='') {
        $r = new AjaxRequestBuilder($target, $values);
        $r->import_request();
        return $r->get_url();
    }

    /**
     * Build an ajax request that replaces the contents of an existing
     * div in the dom with the results of the ajax request.
     *
     * @param string $target       - request target which is
     *                               the name of the page/widget
     *                               to be executed
     * @param array $values        - array of key=>value pairs to add
     * @param mixed $ajaxId        - id where ajax results go
     *
     * @return string the url with query params
     */
    public static function build_replace_url($target, $values=array(),
                                     $ajaxId = AjaxablePage::AJAX_ID) {
        $r = new AjaxRequestBuilder($target, $values);
        $r->set_ajax_id($ajaxId);
        return $r->get_replace_url();
    }

    /**
     * Build an ajax request that replaces the contents of an existing
     * div in the dom with the results of the ajax request.  This also
     * passes in parameters from the existing request to the Controller.
     *
     * @param string $target       - request target which is
     *                               the name of the page/widget
     *                               to be executed
     * @param array $values        - array of key=>value pairs to add
     * @param mixed $ajaxId        - id where ajax results go
     *
     * @return string the url with query params.
     */
    public static function build_replace_url_with_request($target, $values=array(),
                                                  $ajaxId = AjaxablePage::AJAX_ID) {
        $r = new AjaxRequestBuilder($target, $values);
        $r->set_ajax_id($ajaxId);
        $r->import_request();
        return $r->get_replace_url();
    }

    /**
     * Build an ajax request that appends the contents of an existing
     * div in the dom with the results of the ajax request.
     *
     * @param string $target       - request target which is
     *                               the name of the page/widget
     *                               to be executed
     * @param array $values        - array of key=>value pairs to add
     * @param mixed $ajaxId        - id where ajax results go
     *
     * @return string the url with query params
     */
    public static function build_append_url($target, $values=array(),
                                     $ajaxId = AjaxablePage::AJAX_ID) {
        $r = new AjaxRequestBuilder($target, $values);
        $r->set_ajax_id($ajaxId);
        return $r->get_append_url();
    }

    /**
     * Build an ajax request that appends the contents of an existing
     * div in the dom with the results of the ajax request.  This also
     * passes in parameters from the existing request to the Controller.
     *
     * @param string $target       - request target which is
     *                               the name of the page/widget
     *                               to be executed
     * @param array $values        - array of key=>value pairs to add
     * @param mixed $ajaxId        - id where ajax results go
     *
     * @return string the url with query params.
     */
    public static function build_append_url_with_request($target, $values=array(),
                                                  $ajaxId = AjaxablePage::AJAX_ID) {
        $r = new AjaxRequestBuilder($target, $values);
        $r->set_ajax_id($ajaxId);
        $r->import_request();
        return $r->get_append_url();
    }

}

?>