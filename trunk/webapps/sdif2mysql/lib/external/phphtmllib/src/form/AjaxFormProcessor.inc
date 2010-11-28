<?php
/**
 * AjaxFormProcessor
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage FormEngine
 */

/**
 * This is a child of the FormProcessor class to
 * provide an Ajax version of the FormProcessor
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage FormEngine
 *
 */
class AjaxFormProcessor extends FormProcessor {

    /**
     * Flag to let us know if we should
     * render the form after it was
     * successfully processed
     */
    protected $_form_success_render = FALSE;

    /**
     * The ajax target
     */
    const AJAX_TARGET = 'target';

    const AJAX_DIVID = 'ajaxdivid';
    const AJAX = 'ajax';

    /**
     * Constructor
     *
     * @param FormContent $form_content
     * @param bool $ajax
     */
    public function __construct($form_content) {

        $r = new RequestBuilder(get_class($form_content));
        $r->import_var('id');

        if (!($the_form_name = Request::singleton()->get(FormProcessor::FORM_NAME))) {
           $the_form_name = 'aform';
        }

        parent::__construct($form_content,
                            $the_form_name,
                            $r->get_url());
    }

    /**
     * This renders the form
     *
     * @param int - $indent_level
     * @param int - $output_debug
     *
     * @return string
     */
    protected function render_form($indent_level, $output_debug, $obj=NULL) {

        if (Request::singleton()->get('fajax')) {
            return parent::render_form($indent_level, $output_debug, $obj);
        } else {
            // we wrap each form into a div with an id
            $div = new DIVtag(array('id' => 'id' . $this->get_form_name()));
            $div->add(parent::render_form($indent_level, $output_debug, $obj));

            return $div->render($indent_level, $output_debug);
        }

    }

    /**
     * We override this to place our ajax specifid params
     * that we need to pass along in the request.
     *
     * @todo remove the hard coded hidden names and get them
     * from the magic Request object function so they can be obfuscated ?
     *
     * @todo get the 'ajax' name from the Request object.
     */
    protected function __hidden_fields() {
        parent::__hidden_fields();

        $this->_form->add(INPUTtag::factory('hidden', self::FORM_ACTION, ''));
        $this->_form->add(INPUTtag::factory('hidden', 'ajax', 1));
        $this->_form->add(INPUTtag::factory('hidden', self::AJAX_DIVID, $this->_form_content->get_ajax_replacement_divid()));
        $target = Request::singleton()->get_target();
        $this->_form->add(INPUTtag::factory('hidden', self::AJAX_TARGET, $target));
    }
}

?>