<?php
/**
 * This file contains the base FECheckBox class.
 *
 * $Id: FECheckBox.inc 2848 2007-07-11 21:54:58Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * This is the CheckBox FormElement which builds a
 * input field of type="checkbox". It has no validation method.
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FECheckBox extends FormElement {

    /**
     * Holds the checkbox text
     *
     */
    protected $text;

    /**
     * Element value set to 1
     *
     * @var string
     */
    protected $_value = 0;

    /**
     * The constructor
     *
     * @param label string - text label for the element
     */
    function __construct($label) {
        parent::__construct($label, false);
    }

    /**
     * This function builds the element form attributes
     *
     * @return array attributes
     */
    protected function build_element_attributes() {

        $attributes = parent::build_element_attributes();

        if ($this->get_value()) {
            $attributes[] = "checked";
        }

        $attributes["type"] = "checkbox";
        $attributes["value"] = '1';

        return $attributes;
    }

    /**
     * Returns the actual checkbox
     * without the text
     *
     * @return INPUTtag
     */
    public function get_checkbox() {
        return new INPUTtag($this->build_element_attributes());
    }

    /**
     * Returns checkbox label
     *
     * @return LABELtag
     */
    public function get_label() {
        return new LABELtag(array("for" => $this->get_element_id(),
                                  'id' => $this->get_element_id().'label'), $this->get_label_text());
    }

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    public function get_element() {
        return Container::factory($this->get_checkbox(), $this->get_label());
    }

    /**
     * no validation really needed here
     */
    public function validate() {
        return;
    }
}

?>
