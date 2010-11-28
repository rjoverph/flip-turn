<?php
/**
 * This file contains the FECheckBoxList class.
 *
 * $Id: FECheckBoxList.inc 2127 2006-10-05 05:12:34Z hemna $
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
 * This is the CheckBoxList FormElement which builds a
 * list of checkboxes inside a scrollable DIV.
 * It has no validation method.
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FECheckBoxList extends FEMultiListBox {

    /**
     * Flag to tell us to render the check all
     * checkbox
     */
    protected $_checkall_flag = FALSE;

    /**
     * This method is used to turn on/off
     * the magic 'check all' checkbox
     *
     * @param boolean
     */
    function enable_checkall($flag=TRUE) {
        $this->_checkall_flag = $flag;
    }

    /**
     * This returns the JS require to
     * do the work of the check all checkbox
     *
     * @return string
     */
    public function javascript() {
        if (!$this->_checkall_flag) {
            return '';
        } else {
           $js_name = $this->_js_checkall_name();
           $id_name = 'id'.str_replace('[]','',
                                       str_replace('_','',
                                                   $this->get_element_name()));
           $num = count($this->_data_list);

           $js_str = <<<JSEND

            function $js_name(fromlink) {
                var e_name = '$js_name';
                var checkall = document.getElementById('id_$js_name');
                var num = $num;
                var e;

                if (fromlink) {
                    if (checkall.checked) {
                        checkall.checked = false;
                    } else {
                        checkall.checked = true;
                    }
                }

                state = checkall.checked;

                for (i=0;i<num;i++) {
                    id_name = '$id_name'+i;
                    e = document.getElementById(id_name);
                    e.checked = state;
                }
            }


JSEND;
           return $js_str;
        }
    }

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    public function get_element() {

        if ($this->_height || $this->_width) {
            $this->set_style_attribute("overflow", "auto");
            $this->set_style_attribute("border", "1px inset");
            $this->set_style_attribute("background-color", "white");
        }

        $attributes = $this->build_element_attributes();
        unset( $attributes["name"] );
        $div = new DIVtag($attributes);

        $element_name = $this->get_element_name();
        $selected_values = $this->get_value();

        $x=0;
        foreach ($this->_data_list as $text=>$value) {
            $name = str_replace("[]", "[$x]", $element_name);
            $id = str_replace('_','','id'.str_replace('[]','',$element_name).$x);
            $x++;
            $attributes = array("type"=>"checkbox",
                                "name"=>$name,
                                "id"=>$id,
                                "value"=>$value);

            if (is_array($selected_values) && in_array($value, $selected_values))
                $attributes[] = "checked";

            $checkbox = new INPUTtag($attributes);

            if ($this->is_disabled() || isset($this->_disabled_items[$text])) {
                $checkbox->set_tag_attribute("disabled", 'disabled');
                $a = $text;
            } else {
                $js_action = "javascript:e=document.getElementById('" . $id . "'); e.checked=!e.checked;";
                $a_attributes = array("href" => "javascript:void(0)",
                                      "class"=>"form_element",
                                      "onClick" => $js_action);
                $a = new Atag($a_attributes, htmlspecialchars($text), FALSE);
            }

            $check = Container::factory( $checkbox, $a );
            $check->set_collapse();

            $div->add($check, html_br());
        }

        //build the checkall if needed
        if ($this->_checkall_flag) {
            $name = $this->_js_checkall_name();
            $onclick = "javascript:".$name."(false);";

            $checkbox = new INPUTtag(array('type' => 'checkbox', 'value' => 0,
                                           'onclick' => $onclick,
                                           'id' => 'id_'.$name));

            $onclick = "javascript:".$name."(true);";
            $a = new Atag(array('href' => 'javascript:void(0)',
                                'class' => 'form_element',
                                'onclick' => $onclick),
                                'Select All', FALSE);

            $check = Container::factory($checkbox, $a);

            //so we can get some nice spacing
            $check_div = new DIVtag(array('style' => 'padding-left:1px;padding-top:8px;'),$check);
            $check_div->set_collapse();
            return Container::factory($div,$check_div);
        }
        return $div;
    }

    /**
     * This private method builds the name of the js
     * checkall function
     *
     * @return string
     */
    private function _js_checkall_name() {
        return str_replace('[]', '',$this->get_element_name()."_checkall");
    }

}

?>