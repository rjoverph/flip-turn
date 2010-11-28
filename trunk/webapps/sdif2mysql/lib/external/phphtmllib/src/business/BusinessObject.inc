<?php
/**
 *
 * This class contains the base business layer object
 * for doing work.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Business
 */

/**
 *
 * This class contains the base business layer object
 * for doing the core work of your application.  This enables
 * you to contain the logic of your application outside the user
 * interface layer.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Business
 */
abstract class BusinessObject {

    /**
     * Business logic identifier
     *
     * @var int
     */
    protected $id;

    /**
     * The constructor
     *
     * @param int $id business logic identifier
     */
    public function __construct($id = null) {

        $this->id = $id;

        //ok lets initialize our data or data objects
        $this->init();
    }

    /**
     * This method must be created in the child class.
     * This is where you instantiate your DataObject
     * classes that this class uses.
     *
     */
    abstract protected function init();

    /**
     * This function saves each
     * of the data objects
     *
     */
    abstract public function save();

    /**
     * This function is used to delete
     * a particular BusinessObject's data.
     */
    abstract public function delete();

}

?>