<?php
/**
* This file contains the FEComboListButtonsBox class
 *
 * $Id: FEComboListButtonsBox.inc 2399 2007-02-22 21:38:46Z hemna $
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
 * This class builds the FEComboList with buttons below each element
 *
 * @author Sumedh Thakar
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
class FEComboListButtonsBox extends FEComboListBox {

    /**
     * This variable holds the button array
     */
    protected $_button_info = array();

    /**
     * this function sets the array of buttons and related info
     * array is of format
     * array('left' => array(
     *                       array(
     *                        'name'=> 'expand',
     *                        'value' => 'Expand it",
     *                        'onclick'=> 'some_function()',
     *                        'js' => 'function some_function(){ alert('hi'); }'     *                        ),
     *                  )
     *       )
     *
     * @param array $button_array buttons and related info
     */
    function set_button_array($button_array){
        $this->_button_info = $button_array;
    }

    public function javascript(){
        $js = parent::javascript();
        if(count($this->_button_info)){
            foreach ($this->_button_info as $side){
                foreach ($side as $button){
                    if(isset($button['js'])) $js .= " ".$button['js']." ";
                }
            }
        }
        return $js;
    }

    public function get_element(){
        $table = parent::get_element();
        if(empty($this->_button_info)) return $table;
        if (isset($this->_button_info['left'])){
            $lbuttons = new TDtag();
            foreach($this->_button_info['left'] as $butt) {

                $attributes = array();
                if (strlen($butt['value'])>12) $attributes["style"] = "padding-left:6px;padding-right:6px;";
                else $attributes["style"] = "width:100px;";
                $attributes["onClick"] = $butt['onclick'];

                $lbuttons->add(form_button(
                                    $butt['name'],
                                    $butt['value'],
                                    $attributes),
                                    phphtmllib::_HTML_SPACE);
            }
        }else{
            $lbuttons = phphtmllib::_HTML_SPACE;
        }
        if (isset($this->_button_info['right'])){
            $rbuttons = new TDtag();
            foreach($this->_button_info['right'] as $butt) {

                $attributes = array();
                if (strlen($butt['value'])>12) $attributes["style"] = "padding-left:6px;padding-right:6px;";
                else $attributes["style"] = "width:100px;";
                $attributes["onClick"] = $butt['onclick'];

                $rbuttons->add(form_button(
                                    $butt['name'],
                                    $butt['value'],
                                    $attributes),
                                    phphtmllib::_HTML_SPACE);
            }
        }else{
            $rbuttons = phphtmllib::_HTML_SPACE;
        }
        $table->add_row($lbuttons,
                            phphtmllib::_HTML_SPACE,
                        $rbuttons
                        );
        return $table;

    }


}

?>