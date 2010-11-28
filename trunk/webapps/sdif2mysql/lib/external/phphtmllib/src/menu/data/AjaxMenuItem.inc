<?php
/**
 * This is the AjaxMenuItem
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */

/**
 * This is the AjaxMenuItem
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */
class AjaxMenuItem extends MenuItem {

    /**
     * The ajax id that we
     * want the request results
     * to go to.
     *
     * @var string
     */
    protected $ajaxid = AjaxablePage::AJAX_ID;

    /**
     * Constructor
     *
     * @param string $name
     * @param string $target
     * @param array $params
     * @param int $position
     * @param string $icon
     * @param string $ajaxid
     */
    public function __construct($name, $target = null, $params = null,
                                $position = 0, $icon = null, $ajaxid = AjaxablePage::AJAX_ID) {
        parent::__construct($name, $target, $params,
                            $position, $icon);
        $this->ajaxid = $ajaxid;
    }

    /**
     * Get the id of the replacement
     * html element where the
     * results of the request 
     * should go to.
     *
     * @return string
     */
    public function get_ajax_id() {
        return $this->ajaxid;
    }
}


?>
