<?php
/**
 * This file contains the FEButton class
 *
 * $Id: FEButton.inc 1821 2006-08-03 23:52:31Z hemna $
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
 * This is the button FormElement which builds a
 * input field of type="button". It has no validation method.
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEButton extends FEBoxElement {

    /**
     * Holds the width of the element
     *
     */
    protected $_width = "120px";

    /**
     * Holds the type of the button
     */
    protected $_type = 'button';

    /**
     * This function builds the element form attributes
     *
     * @return array attributes
     */
    protected function build_element_attributes() {

        $attributes = parent::build_element_attributes();

        $attributes["name"] = $this->get_element_name();
        $attributes["value"] = $this->get_value();

        return $attributes;
    }

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    public function get_element() {

        $this->set_style_attribute("width", $this->_width);

        $button = BUTTONtag::factory($this->_type, $this->get_label_text());

        $button->set_tag_attributes($this->build_element_attributes());

        return $button;

    }

    /**
     * no validation really needed here
     */
    public function validate() {
        return;
    }

}

?>