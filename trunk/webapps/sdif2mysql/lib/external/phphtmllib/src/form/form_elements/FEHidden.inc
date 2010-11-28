<?php
/**
 * This file contains the FEHidden class
 *
 * $Id: FEHidden.inc 2748 2007-05-16 18:03:57Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * This is the Hidden FormElement which builds a
 * input field of type="hidden". It has no validation method.
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEHidden extends FormElement {

    function __construct($label, $value=NULL) {
        parent::__construct($label, false);
        if ($value != NULL) {
            $this->set_value( $value );
        }
    }

    /**
     * This function creates element name
     * used in the form based on the text label
     * or any other parameters
     *
     */
    protected function create_element_name() {
        $this->set_element_name($this->get_label_text());
    }

    public function get_element() {
        $attributes = $this->build_element_attributes();
        $attributes["type"] = "hidden";

        if (($value = $this->get_value()) !== NULL)
            $attributes["value"] = $value;

        return new INPUTtag($attributes);

        //return form_hidden($this->get_element_name(),
        //                   $this->get_value() );
    }

    /**
     * This method returns the hidden version of this
     * element for a confirmation page.
     *
     * NOTE: This is called by the FormProcessor only.
     * It shouldn't be called manually.
     *
     * @return INPUTtag of type hidden
     */
    public function get_confirm_element() {
        return $this->get_element();
    }

     /**
     * no validation really needed here
     */
    public function validate() {
        return true;
    }
}

?>