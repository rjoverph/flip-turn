<?php
/**
 * The ActionBarItem
 * 
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */


/**
 * This is the action item
 * for the action bar
 *
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */
class ActionBarItem extends MenuItem {

    /**
     * Menu item displayed name
     *
     * @var string
     */
    protected $name;

    /**
     * Menu item target name
     *
     * @var string
     */
    protected $target;

    /**
     * Target parameters
     *
     * @var array
     */
    protected $params;

    /**
     * Holds the icon name
     * for the menu
     *
     * @var string
     */
    protected $icon;

    /**
     * Constructor
     *
     * @param string $name
     * @param string $target
     * @param array $params
     * @param int $position
     * @param string $icon
     */
    public function __construct($name, $target = null, $params = null, $icon = null) {
        parent::__construct($name, $target, $params, 0, $icon);
    }

}
?>