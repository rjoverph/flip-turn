<?php
/**
 * The ActionBar
 * 
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */

/**
 * This is the menu item
 * that handles single menu item data
 *
 * $Id: ActionBar.inc 2420 2007-02-22 22:14:28Z hemna $
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Menu
 */
class ActionBar implements IteratorAggregate {

    /**
     * Holds the data
     *
     * @var unknown_type
     */
    protected $data;

    /**
     * Adds a new menu item to
     * a menu under the menu bar
     *
     * @param string $name
     * @param MenuItem $item
     */
    public function add(ActionBarItem $item) {

        $this->data[] = $item;
    }

    /**
     * Returns true if there are
     * any action items
     *
     * @return bool
     */
    public function has_items() {
        return count($this->data);
    }

    /**
     * Implements iterator interface
     *
     * @return Iterator
     */
    function getIterator() {
        return new ArrayIterator($this->data);
   }

}
?>