<?php
/**
 * The MenuUrlItem
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */

/**
 * This is a MenuItem that only
 * contains an achor tag object
 * for manual url entries.
 *
 * $Id: MenuItem.inc 2004 2006-09-19 05:41:41Z hemna $
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */
class MenuUrlItem extends MenuItem {

    /**
     * The manual url to go to.
     * 
     * @var Atag object
     */
    protected $obj;


    /**
     * Constructor
     *
     * @param string $name
     * @param string $url
     * @param array $params
     * @param int $position
     * @param string $icon
     */
    public function __construct($name, Atag $a, $params = null,
                                $position = 0, $icon = null) {
        parent::__construct($name, $a, $params, $position, $icon, FALSE);
        $this->obj = $a;
    }

    /**
     * Returns menu item
     * target
     *
     * @param string
     */
    public function get() {
        return $this->obj;
    }
}
?>