<?php
/**
 * This file contains the class that is the Image
 * Submit button for a form
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */


/**
 * This class builds a submit button that is
 * an image.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEImageSubmitButton extends FEButton {

    protected $source;
    protected $width;
    protected $height;


    public function __construct($label, $src, $width, $height, $action=null) {
        parent::__construct($label, $action, null, 'image');

        $this->source = $source;

        if ($width) {
            $this->width = $width;
        } else {
            $this->width = '';
        }

        if ($height) {
            $this->height = $height;
        } else {
            $this->height = '';
        }
    }

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    public function get_element() {

        $button = new INPUTtag(array('type' => 'image',
                                     'width' => $this->width,
                                     'height' => $this->height,
                                     'src' => $this->source
                                      ));
        $button->set_collapse();

        if ($this->is_disabled()) {
            $button->set_style('-moz-opacity: 0.4;opacity:.40;filter: alpha(opacity=40)');
        }

        $button->set_tag_attributes($this->build_element_attributes());

        return $button;
    }

    /**
     * This function return the javaScript code for
     * an onSubmit event
     *
     * @return string - javascript code
     */
    public function onSubmit() {
        return "$('" . $this->get_element_id() . "').disabled=true;";
    }

    /**
     * This function return the javaScript code for
     * an onClick event
     *
     * @return string - javascript code
     */
    public function onClick() {
        return $this->pre_onclick .
            "this.form._form_action.value='".$this->get_value()."';" .
            "$('".$this->get_element_id()."text').update('wait...');$('" . $this->get_element_id() . "').readonly=true;";
    }
}

?>
