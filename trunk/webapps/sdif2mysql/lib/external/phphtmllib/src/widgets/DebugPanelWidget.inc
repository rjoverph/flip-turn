<?php
/**
 * This file contains the DebugPanelWidget
 * for use in an MVC
 *
 * @author Suren Markosian
 * @package phpHtmlLib
 * @subpackage framework
 */

/**
 * This is the debug panel widget
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Widget
 */
class DebugPanelWidget extends HTMLWidget {

    /**
     * Holds total execution time
     *
     */
    private $exec_time;

    /**
     * Holds rendered source
     *
     * @var unknown_type
     */
    private $html;

    /**
     * Holds object
     *
     * @var phphtmllib
     */
    private $obj;

    /**
     * Holds target info
     *
     * @var unknown_type
     */
    private $target;

    /**
     * cache information
     */
    private $info = array();

    /**
     * Constructor
     *
     * @param string $target
     * @param Container $obj
     * @param string $html
     * @param string $exec_time
     */
    public function __construct($target, $obj, $html, $exec_time) {
        $this->target = $target;
        $this->obj = $obj;
        $this->html = $html;
        $this->exec_time = $exec_time;
    }

    /**
     * Sets execution time
     *
     * @param float $exec_time
     */
    public function set_exec_time($exec_time) {
        $this->exec_time = $exec_time;
    }

    /**
     * Sets content source (html/cache/whatever)
     *
     * @param string $source
     */
    public function set_source($source) {
        $this->source = $source;
    }

    /**
     * Render the widget
     *
     */
    public function render($indent_level=0, $output_debug=0) {

        $target = $this->target;
        $id_prefix = $target . time();
        $id = 'idDebug' . $id_prefix;

        $c = new DIVtag(array('id' => $id));

        $table = new TABLEtag(array('align' => 'center',
                                    'width' => '700px',
                                    'cellpadding' => 0,
                                    'cellspacing' => 0,
                                    'style' => 'border:1px solid #dfdfa0;background-color:#ffffef;margin-top:20px;'));


        $title = new TABLEtag(array('width' => '100%',
                                    'cellpadding' => '2',
                                    'cellspacing' => 0,
                                    'style' => 'background-color:#efefbc;'));


        $title->add_row(new TDtag(array('style' => 'font-size:10px;font-weight:bold;'), $target),
                        new TDtag(array('align' => 'right', 'style' => 'font-size:10px;'), Atag::factory("javascript:Effect.toggle('" . $id . "','appear',{duration:0.2})",'[x]')));

        $table->add_row(new TDtag(array('colspan' => 2), $title));

        $tr = new TRtag();

        $tool_td = new TDtag(array('style' => 'font-size:10px;padding:10px;'));

        if (Request::singleton()->get('ajax')) {

            $tool_td->add(Atag::factory('javascript:ar_g_u(\'' . str_replace('flushcache=1', '', $_SERVER['REQUEST_URI']) . '\', \''.Request::singleton()->get('ajaxid').'\');',
                                        'Refresh', NULL, NULL, 'refresh current request'), ' | ');

            $tool_td->add(Atag::factory(str_replace("ajax=1", "", $_SERVER['REQUEST_URI']), '- AJAX', NULL, NULL, 'Remove Ajax from request'), ' | ');

            $tool_td->add(Atag::factory($_SERVER['REQUEST_URI'], 'To URI', NULL, NULL, 'Put full request in Address bar.'), ' | ');
        }

        if ($_SERVER['REQUEST_METHOD'] == 'GET') {
            $tool_td->add(Atag::factory("javascript:Effect.toggle('idDebugGET" . $id_prefix . "','appear',{duration:0.2});",
                                        '$_GET (' . count($_GET) . ')', NULL, NULL, 'view $_GET array'), ' | ');
        } else {
            //must be a post
            $tool_td->add(Atag::factory("javascript:Effect.toggle('idDebugPOST" . $id_prefix . "','appear',{duration:0.2});",
                                        '$_POST (' . count($_POST) . ')', NULL, NULL, 'view $_POST array'), ' | ');
        }

        if (isset($_SESSION)) {
            $tool_td->add(Atag::factory("javascript:Effect.toggle('idDebugSESSION" . $id_prefix . "','appear',{duration:0.2});",
                                        '$_SESSION ('. count($_SESSION).')', NULL, NULL, 'view $_SESSION array'), ' | ');
        }

        $tool_td->add(Atag::factory("javascript:Effect.toggle('idDebugSERVER" . $id_prefix . "','appear',{duration:0.2});",
                                    '$_SERVER (' . count($_SERVER) . ')', NULL, NULL, 'view $_SERVER array'), ' | ');

        if (count(ClassMap::$included) > 0) {
            $tool_td->add(Atag::factory("javascript:Effect.toggle('idDebugAutoload" . $id_prefix . "','appear',{duration:0.2});",
                                        'Autoload (' . count(ClassMap::$included) . ')', NULL, NULL, 'view included files for this request'), ' | ');
        }

        if (Cache::cache_enabled() &&
            $this->obj instanceof Cacheable &&
            $this->obj->is_cacheable()) {
            $vars = array('flushcache' => 1);
            if (Request::singleton()->get('ajax')) {
                //last request was ajax
                $r = new AjaxRequestBuilder($this->target, $vars);
                $r->set_ajax_id(Request::singleton()->get('ajaxid'));
                $url = $r->get_replace_url();
            } else {
                //last request wasn't ajax
                $r = new RequestBuilder($this->target, $vars);
                $url = $r->get_url();
            }

            $r->import_request();
            //$tool_td->add(Atag::factory('javascript:g(\'' . $_SERVER['REQUEST_URI'] . '&flushcache=1\', \'pageBody\');', 'Flush Cache'), ' | ');
            $tool_td->add(Atag::factory($url, 'Flush Cache', NULL, NULL, 'flush this reques\'t cache data and refresh.'));
        }

        $tr->add($tool_td);

        // render exec info

        $str = '';
        if ($this->exec_time) {
            $str .= round($this->exec_time, 3) . ' sec | ';
        }

        $str .= strlen($this->html) . ' bytes | ';

        if (Cache::cache_enabled() &&
            $this->obj instanceof Cacheable &&
            $this->obj->is_cacheable()) {

                $a = new ACRONYMtag(array('style' => 'cursor:help;font-size:10px;',
                                      'title' => 'Lifetime: ' . $this->obj->get_cache_lifetime() . ' sec'), 'cached');
                $a->set_collapse();
                $str .= trim($a->render());
        }
        else {
            $str .= 'render';
        }

        if ($str) {
            $tr->add(new TDtag(array('align' => 'right', 'style'=>'font-size:10px;padding:10px;'), $str));
        }

        $table->add($tr);
        $c->add($table);

        // add info blocks

        $c->add($this->build_info_block('_GET', $_GET, 'idDebugGET' . $id_prefix));
        if ($_SERVER['REQUEST_METHOD'] == 'POST') {
            $c->add($this->build_info_block('_POST', $_POST, 'idDebugPOST' . $id_prefix));
        }

        if (isset($_SESSION)) {
            $c->add($this->build_info_block('_SESSION', $_SESSION, 'idDebugSESSION' . $id_prefix));
        }

        $c->add($this->build_info_block('_SERVER', $_SERVER, 'idDebugSERVER' . $id_prefix));

        if (count(ClassMap::$included) > 0) {
            $c->add($this->build_info_block('Autoload', ClassMap::$included, 'idDebugAutoload' . $id_prefix));
        }

        return $c->render($indent_level, $output_debug);
    }

    /**
     * Builds array info block
     *
     */
    private function build_info_block($title, $data, $id = null) {

        $table_attr = array('cellpadding' => 2,
                            'cellspacing' => 2,
                            'align' => 'center',
                            'id' => $id,
                            'style' => 'border:1px solid #aaaaaa;margin-top:10px;display:none;');
        $row_attr = array('style' => 'border-bottom:1px solid #efefef;');

        // GET REQUEST VARIABLES
        $table_get = new TABLEtag($table_attr);
        $table_get->add_row(new TDtag(array('colspan' => 2, 'style' => 'border-bottom:1px solid #aaaaaa;'), Btag::factory($title)));

        foreach ($data as $key => $value) {
            if (is_array($value)) {
                $value = 'Array(' . implode(",", $value) . ')';
            }
            $table_get->add_row(new TDtag(array('style' => 'font-size:10px;'), $key),
                                new TDtag(array('style' => 'font-size:10px;'), $value));
        }

        return $table_get;
    }

}

?>