<?php
/**
 * This file contains the FEActiveDIVRadioButtonGroup class
 *
 * $Id: FEActiveDIVRadioButtonGroup.inc 1625 2005-10-05 18:17:32Z hemna $
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
 * This is a special FERadioButtonGroup form element
 * that allows each of the radio buttons to show/hide
 * a div on the fly.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEActiveDIVRadioButtonGroup extends FERadioGroup {

    public function javascript() {
        $name = $this->get_element_name();

        $js  = 'function '.$this->_form_name.'_'.$name."_activate(id) {\n";
        $js .= "   var e,o;\n";
        $js .= "    e = document.getElementById(id);\n";

        foreach ($this->_data_list as $button) {
            list($name, $value) = each( $button );
            $js .= "    o = document.getElementById('".$this->_id_name($name)."');\n";
            $js .= "    o.style.display = 'none';\n";
        }

        $js .= "    e.style.display = 'block';\n}\n\n";

        return $js;
    }

    /**
     * This method builds an individual Radio button
     * with its associated text
     *
     * @param int - the index
     * @return INPUTtag of type radio
     */
    protected function _get_index_element($index) {
        $element_name = $this->get_element_name();

        $attributes = $this->build_element_attributes();
        $attributes["type"] = "radio";

        list($name, $value) = each($this->_data_list[$index]);
        $attributes["value"] = $value;

        $id_name = $this->get_element_name().'_'.$index;
        $attributes['id'] = $id_name;

        $attributes['onclick'] = 'javascript:'.$this->_form_name.'_'.$element_name.
                                 "_activate('".$this->_id_name($name)."');";

        if (($value == $this->get_value()))
            $attributes['checked'] = "checked";

        $tag = new INPUTtag($attributes);

        //now build the href so we can click on it.
        $attr["class"] ="form_link";
        $attr["href"] = "javascript:void(0)";
        $js = "javascript: function check(item){item.click();} ".
              "check(".$element_name.".item($index));";

        $js = "e=document.getElementById('".$id_name."'); e.click();";
        $attr["onclick"] = $js;

        $href = new Atag($attr, $name);

        $c = Container::factory($tag, $href);
        $c->set_collapse();
        return $c;
    }


    /**
     * This builds the magic div
     *
     * @param int the index
     * @return DIVtag object
     */
    private function build_div($index) {
        //which one is selected?

        reset($this->_data_list[$index]);
        list($name, $value) = each($this->_data_list[$index]);

        $style = 'position:absolute;left:0px;top:0px;';

        if ($value == $this->get_value()) {
            //ok this item is selected!
            //it needs to be visible first.
            $style .= 'visibility:visible;';
        } else {
            $style .= 'visibility:hidden;';
        }

        return new DIVtag(array('id' => $this->_id_name($name),
                                'style' => $style));
    }

    private function _id_name($name) {
        return $this->_form_name.'_'.$this->get_element_name().
               '_'.$this->_sanitize_string($name);
    }

}
?>
