<?php
/**
 * The AjaxableHTMLWidget base class
 *
 * @author Suren Markosian
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Widget
 */

/**
 * Main framework Ajaxable page class
 *
 * Provides functionality for registering
 * variables, checking permissions, etc
 *
 * @author Suren Markosian
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Widget
 *
 */
abstract class AjaxableHTMLWidget extends HTMLWidget implements Ajaxable {
    
	/**
     * CSS style for the outer div
     *
     * @var string
     */
    protected $style;

    /**
     * Holds CSS class for this
     * widget
     *
     * @var string
     */
    protected $class;

    /**
     * Use span instead of a div
     *
     * @var bool
     */
    protected $use_span = false;


    /**
     * The unique 
     * HTML Dom id
     *
     * @var string
     */
    protected $id;
    
    /**
     * The class target used
     * by the controller.
     * 
     * @var string
     */
    protected $target;
    
    
    /**
     * The constructor that allows us to set the id
     * automatically
     * 
     * You should always call the constructor
     */
    public function __construct() {
        $this->set_ajax_replacement_divid('id'.get_class($this));
    }
    

    
    /**
     * Helper methods for the
     * wrapping DIV or SPAN
     */
    
	/**
     * Sets CSS style for the top
     * wrapper div
     *
     * @param string $style
     */
    public function set_style($style) {
        $this->style = $style;
    }

    /**
     * Sets css class for this widget
     *
     * @param string $class
     */
    public function set_class($class) {
        $this->class = $class;
    }

    /**
     * Tells us to use span instead
     * of a div
     *
     * @param boolean $flag
     */
    public function use_span($flag) {
        $this->use_span = $flag;
    }
    
    
    /**
     * This method is used to build the contents
     * of the actual widget.  It must return the
     * contents as a renderable object.
     * 
     * @return Container
     */
    abstract public function get_content();

    /**
     * The render method which automatically
     * wraps the contents into a div if the request
     * wasn't an ajax request.
     *
     * @param unknown_type $indent_level
     * @param unknown_type $output_debug
     * @return unknown
     */
    public final function render($indent_level=0, $output_debug=false) {

        //If this was an ajax request we don't
        //want to automatically wrap the contents
        //in a unique div...as it's already there in the DOM.
        if (Request::singleton()->get('allajax') == 1 || (Request::singleton()->is_ajax() &&
            Request::singleton()->get_target() == get_class($this) &&
            Request::singleton()->get('ajaxid') == $this->get_id())) {
                
            $c = $this->get_content();
            
            if ($c instanceof Container) {
                return $c->render();
            } else {
                return $c;
            }
        }  else {

            $c = $this->build_container();
            $c->add($this->get_content());

            return $c->render($indent_level, $output_debug);
        }
    }

    /**
     * This method builds the wrapper container
     * that is only done when the request
     * was NOT an ajax request.  This is so we can
     * have a dom element to replace the contents
     * later when it is an ajax request.
     *
     * @return DIVtag or SPANtag
     */
    protected function build_container() {
        $attr = $this->build_container_attributes();

        $class_name = ($this->use_span)?'SPANtag':'DIVtag';

        $c = new $class_name($attr);
        return $c;
    }

    /**
     * Build the container class and id attributes
     *
     * @return array
     */
    protected function build_container_attributes() {
        $attr = array('id' => $this->get_ajax_replacement_divid());

        if ($this->style) {
            $attr['style'] = $this->style;
        }

        if ($this->class) {
            $attr['class'] = $this->class;
        }

        return $attr;
    }
    
    
    
    
    /**
     * Ajaxable Interface methods.
     */

    /**
     * This method is required for Ajax objects
     * to have the request variables registered
     * so the Controller can get them and pass
     * them to the Request object
     *
     * @return array
     */
    public function request_vars() {
        return array();
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
    public function set_ajax_replacement_divid($id) {
        $this->id = $id;
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
        return $this->id;
    }

    /**
     * This method is used to set the target
     * object that will be called by the Controller
     * for a request.
     *
     * @param string $target
     * @return void
     */
    public function set_ajax_target($target) {
        $this->target = $target;
    }

    /**
     * This method is used to get the target
     * object that will be called by the Controller
     * for a request.
     *
     * @return string $target
     */
    public function get_ajax_target() {
        if (is_null($this->ajax_target)) {
            $this->ajax_target = get_class($this);
        }
        return $this->ajax_target;
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
        return new AjaxRequestBuilder($this->get_ajax_target(),$vars);
    }
}
?>
