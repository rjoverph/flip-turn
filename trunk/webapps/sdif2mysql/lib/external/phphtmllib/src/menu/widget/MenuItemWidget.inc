<?php
/**
 * This shows 1 way to render a MenuItem data Object.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */

/**
 * This shows 1 way to render a MenuItem data Object.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */
class MenuItemWidget extends HTMLWidget {

    /**
     * The MenuItem to render
     *
     * @var MenuItem
     */
    protected $item;

    public function __construct(MenuItem $item) {
        $this->item = $item;
    }

    public function render($ident_level=0, $output_debug=0) {

        // add a regular menu item link

        //Are we a submenu item ?
        if ($this->item->has_menus()) {
            //we are
            $url = '#';
            $onclick = "return false;";
            $name = $this->item->get_name();
            $over = "menuItemMouseover(event, '".'mid' . strtolower(str_replace('_', '', $name))."');";
            $content = Container::factory(SPANtag::factory('menuItemText',$this->item->get_name()),
                                          SPANtag::factory('menuItemArrow', '&#9654;'));
        } else {
            $over = null;
            if ($this->item instanceof AjaxMenuItem) {
                $request = new AjaxRequestBuilder($this->item->get_target(), array());
                $request->set_ajax_id($this->item->get_ajax_id());
                $request->set_data($this->item->get_params());
                $url = '#';
                $onclick = $request->get_replace_url() . ';buttonOrMenuMouseout(event)';
            } else {
                $request = new RequestBuilder($this->item->get_target(), array());
                $request->set_data($this->item->get_params());
                $url = $request->get_url();
                $onclick = '';
            }
            $content = $this->item->get_name();
        }


        $a = new Atag(array('class' => 'menuItem',
                            'href' => $url,
                            'onClick' => $onclick),
                      $content);
        if (!is_null($over)) {
            $a->set_tag_attribute('onmouseover', $over);
        }
        $a->set_collapse();
        return $a->render($ident_level, $output_debug);
    }
}


?>
