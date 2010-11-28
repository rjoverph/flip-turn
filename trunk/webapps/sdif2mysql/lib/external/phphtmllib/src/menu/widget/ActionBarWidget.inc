<?php
/**
 * This holds the action bar widget
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */

/**
 * This class is used for building a
 * bar of links, buttons, icons for
 * performing 'actions'.
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */
class ActionBarWidget extends HTMLWidget {

    /**
     * Holds the menu bar object
     *
     * @var ActionBar
     */
    protected $ab;

    /**
     * Constructor
     *
     * @param ActionBar $ab
     */
    public function __construct(ActionBar $ab) {
        $this->ab = $ab;
    }

    /**
     * Renders our action bar
     *
     * @return string
     */
    public function render($indent_level=0, $output_debug=0) {

        $div = new DIVtag(array('id' => 'idActionBar',
                                'class' => 'actionBar'));

        foreach ($this->ab as $item) {

            // add a regular action bar item link
            if ($item instanceof AjaxActionBarItem) {
                $url = AjaxRequestBuilder::get_replace_url($item->get_target(), $item->get_params(), $item->get_ajax_id());
            } else {
                $url = RequestBuilder::get_url($item->get_target(), $item->get_params());
            }

            $div->add(new Atag(array('class' => 'actionBar',
                                     'href' => $url),
                               $item->get_name()));
        }

        return $div->render($indent_level, $output_debug);
    }

}
?>