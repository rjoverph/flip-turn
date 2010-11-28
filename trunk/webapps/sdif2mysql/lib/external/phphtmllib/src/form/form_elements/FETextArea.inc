<?php
/**
 * This file contains the Text FormElement class.
 *
 * This is the TextArea FormElement which builds a
 * textarea field. It has no validation method.
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */

/**
 * This is the FETextArea FormElement which builds a
 * textarea input field.
 * It validates the length of the input.
 *
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */

class FETextArea extends FEBoxElement {

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
     * This lets you limit the amount of data to
     * accept in the field
     */
    protected $_limit_char_count = -1;

    /**
     * The constructor
     *
     * @param string $label - text label for the element
     * @param bool $required - is this a required element
     * @param int $rows - the rows attribute
     * @param int $cols required - the cols attribute
     * @param int $width - element width in pixels (px), percentage (%) or elements (em)
     * @param int $height - element height in pixels (px), percentage (%) or elements (em)
     * @param int $limit_char_count - the number of characters to limit the value to.
     */
    function __construct($label, $required = TRUE, $rows, $cols,
                         $width = NULL, $height = NULL,
                         $limit_char_count=-1) {

        $this->_limit_char_count = $limit_char_count;
        parent::__construct($label, $required, $width, $height);

        $this->set_rows($rows);
        $this->set_cols($cols);
    }

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    public function get_element() {

        $value = $this->get_value();
        $attributes = $this->build_element_attributes();

        if (!$value && $this->value_description) {
            $attributes['onFocus'] =  "if (this.innerHTML == '$this->value_description') {this.innerHTML='';}";
            $attributes['onBlur'] =  "if (this.innerHTML == '') {this.innerHTML='$this->value_description';}";
        }

        $tag = new TEXTAREAtag($attributes);

        if ($value) {
            $tag->add($value);
        }
        else if ($this->value_description) {
            $tag->add($this->value_description);
        }

        return $tag;
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
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_name().
     * @return void
     */
    public function validate() {

        $value = $this->get_value();

        if ($this->value_description && $value == $this->value_description) {
                $value = '';
        }

        if ($this->_limit_char_count > 0) {
            $length = strlen($value);
            if ($length > $this->_limit_char_count) {
                Validator::error(ValidatorException::STR_INVALID_LENGTH_N, null,
                                 $this->get_label(), array($this->_limit_char_count, $length));
            }
        }
    }

    /**
     * This method is used as a shortcut
     * to set the rows attribute
     *
     * @param int the rows attribute value
     */
    public function set_rows($rows) {
        $this->set_attribute("rows", $rows);
    }

    /**
     * This method is used as a shortcut
     * to set the cols attribute
     *
     * @param int the cols attribute value
     */
    public function set_cols($cols) {
        $this->set_attribute("cols", $cols);
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