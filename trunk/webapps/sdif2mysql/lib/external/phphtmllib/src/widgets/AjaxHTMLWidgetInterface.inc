<?php
/**
 * This interface defines the required
 * methods for an AjaxHTMLWidget
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Widget
 */

/**
 * The AjaxHTMLWidgetInterface extends
 * the HTMLWidgetInterface to add
 * methods required for an ajax widget
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Widget
 */
interface AjaxHTMLWidgetInterface extends HTMLWidgetInterface {
    public function get_id();
}
?>
