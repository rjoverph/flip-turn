<?php
/**
 * This file contains the FEText
 *
 * $Id: FEText.inc 2812 2007-05-25 22:23:19Z suren2 $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * This is the Text FormElement which builds a
 * text input field. It has no validation method.
 *
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEText extends FormElement {

    /**
     * Holds text that is displayed inside
     * the text box and goes away when
     * user clicks on it
     *
     * Most useful in the form of
     * "enter your name here"
     *
     * @var string
     */
    protected $value_description;

    /**
     * The constructor
     *
     * @param label string - text label for the element
     * @param bool required - is this a required element
     * @param int required - element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int required - maximum number of chars allowed to type in
     */
    function __construct($label, $required = FALSE, $width = NULL, $maxlength = NULL) {
        parent::__construct($label, $required);

        if ($width != NULL) {
            if (is_numeric($width))
                $this->set_attribute("size", $width);
            else
                $this->set_style_attribute("width", $width);
        }

        if ($maxlength != NULL)
            $this->set_attribute("maxlength", $maxlength);
    }

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    public function get_element() {

        $attributes = $this->build_element_attributes();
        $attributes['type'] = "text";

        $value = $this->get_value();
        if (!$value && $this->value_description) {
            $attributes['value'] = $this->value_description;
            $attributes['onFocus'] =  "if (this.value == '$this->value_description') {this.value='';}";
            $attributes['onBlur'] =  "if (this.value == '') {this.value='$this->value_description';}";
        }
        else {
            $attributes['value'] = $value;
        }

        $c = Container::factory(new INPUTtag($attributes));

        if ($this->_js_validation_enabled && $this->js_validate()) {
            // add div for js errors
            $c->add(new DIVtag(array('id' => 'error' . $this->get_element_id(),
                                     'class' => 'inlineError',
                                     'style' => 'display:none;')));
        }
        return $c;
    }

    /**
     * Sets text that is displayed inside
     * the text box and goes away when
     * user clicks on it
     *
     * Most useful in the form of
     * "enter your name here"
     *
     * @var string $text
     */
    public function set_value_description($text) {
        $this->value_description = $text;

    }

    /**
     * no validation really needed here
     */
    public function validate() {
        return;
    }

    public function get_value() {
        $value = parent::get_value();

        if ($this->value_description && $value == $this->value_description) {
            $value = '';
        }

        return $value;
    }

}

?>