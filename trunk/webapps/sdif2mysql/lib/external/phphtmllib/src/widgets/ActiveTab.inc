<?php
/**
 * This class is used for creating a tab panel of content
 * where the tabs can be switched on the fly w/ JS, thereby
 * eliminating a page turn to see the other tab's content.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */
class ActiveTab extends HTMLWidget {

    const PLACEMENT_LEFT = 1;
    const PLACEMENT_TOP = 2;
    const PLACEMENT_RIGHT = 3;
    const PLACEMENT_BOTTOM = 4;

    /**
     * Location of the actual table
     *
     * @var int
     */
    protected $placement = self::PLACEMENT_RIGHT;

    /**
     * Background color of the
     * active tab and tab body
     *
     * @var string
     */
    protected $active_color = '#f9f9ff';

    /**
     * Background color of the
     * inactive tab
     *
     * @var string
     */
    protected $inactive_color = '#cccccc';

    /**
     * CSS border color
     *
     * @var string
     */
    protected $border_color = '#999999';

    /**
     * Color of the tab text
     *
     * @var string
     */
    protected $text_color = '#00007f';

    /**
     * Holds the actual tabs and
     * tab content
     *
     * @var array
     */
    protected $tabs = array();

    /**
     * Selected active tab
     *
     */
    protected $tab_selected = 0;

    /**
     * Variable prefix to allow
     * multiple tabs
     */
    protected $prefix = '';

    /**
     * Holds the width
     *
     * @var string
     */
    protected $width = '500px';

    /**
     * Constructor
     *
     */
    public function __construct($width = '500px', $placement = self::PLACEMENT_TOP) {
        parent::__construct();
        $this->width = $width;
        $this->placement = $placement;

        // determine selected tab
        $this->tab_selected = (isset($_REQUEST[$this->prefix . 'tabIndex']))?$_REQUEST[$this->prefix . 'tabIndex']:0;
    }

    /* ----------- SETTERS / GETTERS -------------------- */

    /**
     * Sets tabs location
     *
     * @param int $placement
     */
    public function set_placement($placement) {
        $this->placement = $placement;
    }

    /**
     * Sets default selected tab
     * index
     *
     * @param int $index
     */
    public function set_tab_selected($index) {
        $this->tab_selected = $index;
    }

    /**
     * Sets tab prefix
     *
     * @param string $prefix
     */
    public function set_prefix($prefix) {
        $this->prefix = $prefix;
    }

    /**
     * Adds a new tab
     *
     * @param string $title
     * @param Container $content
     */
    public function add($title, Container $content) {
        $this->tabs[] = array('title' => $title,
                              'content' => $content);
    }

    /* ----------- PROTECTED / PRIVATE FUNCTIONS ------------------ */

    public function render($indent_level=1, $output_debug=0) {      

        $div = new DIVtag(array('style' => 'overflow:hidden;'));

        // tab attributes
        $attr_tab = array();
        $attr_content = array('style' => 'background-color:' . $this->active_color .
                              ';padding:10px;border:1px solid ' . $this->border_color . ';');        

        switch ($this->placement) {

        	case self::PLACEMENT_LEFT:
                $attr_tab['style'] = 'text-align:right;float:left;width:120px;';
                $attr_content['style'] .= 'margin-left:119px;width:' . $this->width . ';';

        	    $div->add(new DIVtag($attr_tab, $this->render_tabs()),
        	              new DIVtag($attr_content, $this->render_content()));
        		break;

            case self::PLACEMENT_TOP:
                $attr_tab['style'] = 'padding-top:7px;padding-bottom:6px;vertical-align:bottom;';
                $attr_content['style'] .= 'width:' . $this->width . ';';

        	    $div->add(new DIVtag($attr_tab, $this->render_tabs()),
        	              new DIVtag($attr_content, $this->render_content()));
        		break;

            case self::PLACEMENT_RIGHT:
                $attr_content['style'] .= 'float:left;width:' . $this->width . ';margin-right:-1px;';
                $attr_tab['style'] = 'float:left;width:120px;';

                $div->add(new DIVtag($attr_content, $this->render_content()),
                          new DIVtag($attr_tab, $this->render_tabs()));
        		break;

            case self::PLACEMENT_BOTTOM:

                $attr_tab['style'] = 'padding-top:6px;padding-bottom:7px;vertical-align:top;';
                $attr_content['style'] .= 'width:' . $this->width . ';';

        	    $div->add(new DIVtag($attr_content, $this->render_content()),
                          new DIVtag($attr_tab, $this->render_tabs()));
        		break;

            default:
        		break;
        }

        $c = Container::factory($div,
                                new DIVtag(array('style' => 'clear:both;')));

        // store tab selected in a hidden field
        $c->add(new INPUTtag(array('type' => 'hidden',
                                   'name' => $this->prefix . 'tabIndex',
                                   'id' => $this->prefix . 'tabIndex',
                                   'value' => $this->tab_selected)));

        $script = SCRIPTtag::factory();
        $script->add($this->get_javascript());
        $c->add($script);

        return $c->render($indent_level, $output_debug);
    }


    /**
     * Renders all tabs
     *
     * @return Container
     */
    protected function render_tabs() {

        $c = new Container();

        foreach ($this->tabs as $tab_index => $tab) {
            $c->add(new DIVtag($this->build_tab_attributes($tab_index), $tab['title']));
        }

        return $c;
    }

    /**
     * Builds tab attributes
     *
     * @return array
     */
    protected function build_tab_attributes($tab_index) {

        $attr = array('id' => $this->prefix . 'tab' . $tab_index);
        $style = array('cursor' => 'pointer',
                       'border' => '1px solid ' . $this->border_color,
                       'padding' => '6px',
                       'padding-left' => '8px',
                       'padding-right' => '8px',
                       'color' => $this->text_color,
                       'vertical-align' => 'middle');

        // set correct margins
        $margin = '4px';

        // open up one border side
            switch ($this->placement) {

                case self::PLACEMENT_LEFT:
            	    $style['margin-bottom'] = $margin;
            		break;

            	case self::PLACEMENT_TOP:
            	    $style['border-bottom'] = 'none';
            	    $style['margin-right'] = $margin;
            	    $style['display'] = 'inline';
            		break;

            	case self::PLACEMENT_RIGHT:
            	    $style['margin-bottom'] = $margin;
            		break;

            	case self::PLACEMENT_BOTTOM:
            	    $style['margin-right'] = $margin;
            	    $style['border-top'] = 'none';
            	    $style['display'] = 'inline';
            		break;

            	default:
            		break;
            }

        if ($tab_index == $this->tab_selected) {
            $style['background-color'] = $this->active_color;

            // open up one border side
            switch ($this->placement) {

                case self::PLACEMENT_LEFT:
            	    $style['border-right'] = 'none';
            		break;

            	case self::PLACEMENT_TOP:
            	    $style['padding-bottom'] = '7px';
            		break;

            	case self::PLACEMENT_RIGHT:
            	    $style['border-left'] = 'none';
            		break;

            	case self::PLACEMENT_BOTTOM:
            	    $style['padding-top'] = '8px';
            		break;

            	default:
            		break;
            }
        }
        else {
            $style['background-color'] = $this->inactive_color;
        }

        $str = '';
        foreach ($style as $key=>$value) {
            $str .= $key . ':' . $value . ';';
        }

        $attr['style'] = $str;

        $attr['onClick'] = $this->prefix . 'changeTab(' . $tab_index . ')';

        $attr['onMouseOver'] = "this.style.backgroundColor='" . $this->active_color . "';";
        $attr['onMouseOut'] = "if (" . $this->prefix . "currentTabIndex != $tab_index) this.style.backgroundColor='" . $this->inactive_color . "';";

        return $attr;
    }


    /**
     * Builds tab content
     *
     * @return Container
     */
    protected function render_content() {

        $c = new Container();

        foreach ($this->tabs as $tab_index => $tab) {
            $c->add(new DIVtag($this->build_content_attributes($tab_index), $tab['content']));
        }

        return $c;
    }

    /**
     * Builds tab content
     *
     * @param int $tab_index
     *
     * @return Container
     */
    protected function build_content_attributes($tab_index) {

        $style = '';

        if ($tab_index != $this->tab_selected) {
            $style .= 'display:none;';
        }

        return array('style' => $style,
                     'id' => $this->prefix . 'tabContent' . $tab_index);
    }

    /**
     * Builds javaScript needed for the
     * tabs to work
     *
     */
    public  function get_javascript() {

        $js = "

        window." . $this->prefix . "currentTabIndex = " . $this->tab_selected . ";
        ";

        $js .= "window." . $this->prefix . "changeTab = function(tabIndex) {


        var tab1 = $('" . $this->prefix . "tab' + " . $this->prefix . "currentTabIndex);
        var tab2 = $('" . $this->prefix . "tab' + tabIndex);";

        if ($this->active_color) {
            $js .= "tab1.style.backgroundColor = '" . $this->inactive_color . "';
                    tab2.style.backgroundColor = '" . $this->active_color . "';";
        }

        switch ($this->placement) {
        	case self::PLACEMENT_LEFT:
                $js .= "tab2.style.borderRight = 'none';
                tab1.style.borderRight = '1px solid " . $this->border_color . "';";
        		break;

        	case self::PLACEMENT_TOP:

        	    $js .= "tab1.style.paddingBottom = '6px';tab2.style.paddingBottom = '7px';";

        		break;

        	case self::PLACEMENT_RIGHT:
        	    $js .= "tab2.style.borderLeft = 'none';
                tab1.style.borderLeft = '1px solid " . $this->border_color . "';";

        		break;

        	case self::PLACEMENT_BOTTOM:
                $js .= "tab1.style.paddingTop = '6px';tab2.style.paddingTop = '8px';";
        		break;

        	default:
        		break;
        }



        $js .= "
        $('" . $this->prefix . "tabContent' + " . $this->prefix . "currentTabIndex).style.display = 'none';
        $('" . $this->prefix . "tabContent' + tabIndex).style.display = '';

        " . $this->prefix . "currentTabIndex = tabIndex;
        $('" . $this->prefix . "tabIndex').value = tabIndex;


        }
        ";

        return $js;
    }


}

?>