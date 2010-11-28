<?php
/**
 * base DataObject
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Data
 */

/**
 * Abstract DataObject class defines
 * API for all data access methods
 * of an application.
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 * @subpackage Data
 */
abstract class DataObject {

    /**
     * Holds the data in an
     * array
     *
     * @var array
     */
    protected $data = NULL;

    /**
     * Holds a list of fields
     * that were changed by the
     * setters
     *
     * @var array
     */
    protected $changed_fields = array();

    /**
     * Is true if the object or
     * any related objects were changed
     *
     * @var bool
     */
    protected $changed = false;

    /**
     * How long do we allow
     * our objects to live in the
     * cache before they expire
     *
     * This value is given in seconds
     *
     * @var int
     */
    protected $cache_lifetime = 0;

    /**
     * This is the cache object
     * that is created based on
     * cache_type
     *
     * @var Cache
     */
    protected $cache;

    /**
     * Was this a newly created record?
     *
     * @var boolean
     */
    protected $new_record = FALSE;

    /*** PUBLIC METHODS ************************************************************/

    /**
     * Constructor
     * This will set the cache object
     * and attempt to load the data.
     *
     */
    public function __construct() {

        // setup the cache object
        // to use
        $this->cache = $this->get_cache_object();

        //set a default.
        $this->data = new stdClass;

        //try and load the data.
        $this->load();
    }

    /**
     * Sets a field to a given value
     *
     * @param string $name
     * @param string $value
     */
    protected function set($name, $value) {
        $this->__set($name, $value);
    }

    /**
     * override for set to get
     *
     * $f->foo = bar to work
     *
     * @param string $name
     * @param mixed $value
     */
    public function __set($name, $value) {
        // assign the value

        //only save changed if there is a diff.
        if (!isset($this->data->$name) || $this->data->$name != $value) {
            $this->data->$name = $value;

            // we keep track of all the fields
            // that were changed
            $this->changed_fields[$name] = $this->changed = true;
        }
    }

    /**
     * Returns a value by name
     *
     * @param string $name
     */
    protected function get($name) {
        return $this->__get($name);
    }

    /**
     * override for get to work
     *
     * echo $f->foo;
     *
     * @return mixed
     */
    public function __get($name) {
        if (isset($this->data->$name)) {
            return $this->data->$name;
        } else {
            return false;
        }
    }

    /**
     * This function replaces the data
     * with a new data set
     *
     * Dangerous and should only be used by other classes
     * and object collections
     *
     * @param StdClass $data
     */
    public function set_data(StdClass $data) {
        $this->data = $data;
    }

    /**
     * This function checks the
     * cache and calls load_data
     * if there is no cached
     * data for this object
     *
     */
    public final function load() {
        // perform any pre-load
        // actions like init i/o
        // stream
        $this->before_load();

        // try cache first
        if (!$this->load_cache()) {

            // cache not found
            // lets load it
            $this->load_data();

            // whatever we loaded
            // let's save it to cache
            $this->save_cache();
        } else {
            $this->new_record = false;
        }

        //Do any post load processing
        //i.e. decrypting data?
        $this->after_load();
    }

    /**
     * Saves our data to the
     * data source and to the
     * cache
     *
     * It calls abstract save_* methods
     * that need to be implemented in
     * the child classes
     *
     */
    public final function save() {

        if ($this->changed) {
            // perform any pre-save
            // actions like init i/o
            // stream
            $this->before_save();

            // actually save the data
            $this->save_data();

            // save was successfull
            // we can now write it to
            // cache as well
            $this->save_cache();
            $this->after_save();

            //reset the changed fields
            $this->changed_fields = array();
            $this->changed = false;
            $this->new_record = false;
        }
    }

    /**
     * This method marks this particular
     * DataObject for deletion during
     * the next call to save();
     *
     */
    public final function delete() {
        //we have been marked for deletion
        //make sure we delete
        $this->before_delete();

        //nuke the row in the db.
        $this->delete_data();

        //drop the cache entry.
        $this->delete_cache();

        //any after_delete
        $this->after_delete();

        //reset the changed fields
        $this->changed_fields = array();
        $this->changed = false;
    }

    /**
     * Has this field changed?
     *
     * @param string $name
     * @return boolean
     */
    public final function has_changed($name) {
         return isset($this->changed_fields[$name]);
    }

    /**
     * Have there been any changes since the last
     * time this was loaded
     *
     * @return boolean
     */
     public final function any_changes() {
         return $this->changed;
     }

    /* -- PROTECTED METHODS -------------------------------------------------------- */

    /**
     * This method is used to build the cache object.
     *
     * @return Cache
     */
    protected function get_cache_object() {
        return NoCache::singleton();
    }

    /**
     * Used to set the cache expiry time
     *
     * @param int (in seconds)
     */
    public function set_cache_lifetime($time) {
        $this->cache_lifetime = $time;
    }

    /**
     * This function loads our
     * data from cache and returns
     * true on success or false
     * if no cached data was found
     *
     * @return bool
     */
    protected final function load_cache() {

        // try to get it from cache
        if ($data = $this->cache->get($this->get_cache_key())) {
            $this->data = $data;
            return true;
        }
        else {
            return false;
        }
    }

    /**
     * This function saves our
     * data to cache
     *
     */
    protected final function save_cache() {
        // save it to cache
        $this->cache->set($this->get_cache_key(), $this->data, $this->cache_lifetime);
    }

    /**
     * This function nukes the entry in the
     * cache
     *
     */
    protected final function delete_cache() {
        $this->cache->delete($this->get_cache_key());
    }

    /**
     * Called before loading data
     *
     * Useful for initializing any
     * I/O streams or any other
     * parameters needed
     *
     */
    protected function before_load() {
    }

    /**
     * This method is called after loading
     * is complete.
     *
     */
    protected function after_load() {
    }

    /**
     * Called before saving data
     *
     * Useful for initializing any
     * I/O streams or any other
     * parameters needed
     *
     */
    protected function before_save() {
    }

    /**
     * This method is called after save is
     * completed (including cache save)
     *
     */
    protected function after_save() {
    }

    /**
     * This method is called before any data
     * is deleted
     */
    protected function before_delete() {
    }

    /**
     * This method is called after all delete
     * functionality is done (including cache)
     */
    protected function after_delete() {
    }

    /* -- ABSTRACT METHODS -------------------------------------------------------- */

    /**
     * This function implements
     * data loading from a data
     * source
     *
     */
    abstract protected function load_data();

    /**
     * This function implements
     * data saving back to data
     * source
     *
     * It should look at list of changed
     * fields to determine
     * what needs to be saved
     *
     */
    abstract protected function save_data();

    /**
     * This function implements the deleting
     * of data in the store.
     *
     */
    abstract protected function delete_data();

    /**
     * Generates unique key for
     * caching
     *
     * @return string
     */
    abstract protected function get_cache_key();

}

?>
