<?php
/**
 * This file contains the Ajaxable Interface
 * which defines required methods that an
 * Ajaxable widget must provide.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 */

/**
 * This interface defines the set of methods
 * that must exist for each phphtmllib framework
 * widget/object to be 'ajaxable'.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 */
interface Ajaxable {

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
    public function set_ajax_replacement_divid($divid);

    /**
     * This method is used to get the
     * replacement div id that
     * will get replaced as a result
     * of the ajax request.
     *
     * <div id="idreplace">
     * @return string $divid
     */
    public function get_ajax_replacement_divid();

    /**
     * This method is used to set the target
     * object that will be called by the Controller
     * for a request.
     *
     * @param string $target
     * @return void
     */
    public function set_ajax_target($target);

    /**
     * This method is used to get the target
     * object that will be called by the Controller
     * for a request.
     *
     * @return string $target
     */
    public function get_ajax_target();

    /**
     * This method is used to construct a
     * RequestBuilder object that uses
     * the replacement divid and ajax target.
     *
     * @param array $vars
     * @return RequestBuilder
     */
    public function get_request_builder($vars=array());

    /**
     * This method is required for Ajax objects
     * to have the request variables registered
     * so the Controller can get them and pass
     * them to the Request object.
     *
     * @return array
     */
//    public function request_vars();

}

?>