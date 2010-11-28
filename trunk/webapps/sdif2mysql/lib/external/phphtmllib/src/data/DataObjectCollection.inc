<?php
/**
 * This class represent a collection of multiple
 * DataObject
 *
 * @TODO more documentation is needed
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Data
 */

/**
 * This class represent a collection of multiple
 * DataObject
 *
 * @TODO more documentation is needed
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Data
 */

class DataObjectCollection implements Iterator, Countable {

    /**
     * Holds the index into the array of data
     * so we can keep track of where we are
     * when we are walking the array
     * (only usefull for non DB children)
     *
     */
    var $_data_index = 0;

    /**
     * Holds our DataObject childs
     *
     */
    protected $data = array();

    /**
     *
     * The constructor
     */
    function __construct() {

    }

    /**
     * Adds a DataObject child
     *
     * @param DataObject $obj
     */
    public function add(DataObject $obj) {
        $this->data[] = $obj;
    }

    /**
     * Saves on all data
     * objects in this collection
     *
     */
    public function save() {
        foreach ($this->data as $obj) {
            $obj->save();
        }
    }

    /* -- ITERATOR INTERFACE ----------------------------------- */

    public function rewind() {
        reset($this->data);
    }

    public function current() {
        return current($this->data);
    }

    public function key() {
        return key($this->data);
    }

    public function next() {
        return next($this->data);
    }

    public function valid() {
        return ($this->current() !== false);
    }

    /**
     * Returns number of
     * data object
     *
     * @return int
     */
    public function count() {
        return count($this->data);
    }

}
?>