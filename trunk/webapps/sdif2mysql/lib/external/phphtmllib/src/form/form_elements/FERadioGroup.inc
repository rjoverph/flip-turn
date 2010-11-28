<?php
/**
 * This file contains the FERadioGroup class
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */

/**
 *
 * This is the Radio Button Group FormElement which builds a
 * List of Radio buttons that can be used in any
 * style of layout.
 *
 * It has no validation method.
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
class FERadioGroup extends FormElement {

    /**
     * Holds the list of available
     * data elements
     *
     */
    protected $_data_list = array();

    /**
     * the br flag
     */
    protected $_br_flag = FALSE;


    /**
     * The constructor
     *
     * @param label string - text label for the element
     * @param array - the name => value pairs of the radio
     *                buttons text => value
     * @param boolean - required flag
     */
    function __construct($label, $data_list=array(), $required=true) {
        parent::__construct($label, $required);
        foreach ($data_list as $name=>$value) {
            $this->_data_list[] = array($name=>$value);
        }
    }

    /**
     * This provides a method
     * for the FormContent
     * to get access to the
     * text associated with a
     * field.  This is only available
     * on FormElements that have text
     * associated with a field.
     * It is used during Confirmation
     *
     * @param mixed - the value to look up
     * @return string - the text associated
     */
    public function get_value_text() {
        $value = $this->get_value();
        foreach( $this->_data_list as $arr) {
            $flip = array_flip($arr);
            if (isset($flip[$value])) {
                return $flip[$value];
            }
        }
        return NULL;
    }

    /**
     * This function is used to set the br flag
     * that will automatically add a BR tag after
     * each radio button
     *
     * @param boolean
     */
    public function set_br_flag($flag=TRUE) {
        $this->_br_flag = $flag;
    }

    /**
     * This function builds and returns the
     * form element object
     *
     * @param int the index to get
     * @param boolean the br flag.
     *        NOTE: the class's br flag takes precedence.
     * @return object
     */
    public function get_element($index=NULL, $br_flag=FALSE) {
        $container = Container::factory();

        if ($br_flag != $this->_br_flag) {
            $br_flag = $this->_br_flag;
        }

        if ($index === NULL) {
            $count = count( $this->_data_list );
            for ($x=0;$x<=$count-1;$x++) {
                if ($br_flag) {
                    $container->add( $this->_get_index_element($x),
                                     html_br());
                } else {
                    $container->add( $this->_get_index_element($x));
                }

            }
        } else {
            $container->add( $this->_get_index_element($index));
        }

        return $container;
    }

    /**
     * This method builds an individual Radio button
     * with its associated text
     *
     * @param int - the index
     * @return INPUTtag of type radio
     */
    protected function _get_index_element($index) {
        $attributes = $this->build_element_attributes();
        $attributes["type"] = "radio";

        list($name, $value) = each($this->_data_list[$index]);
        $attributes["value"] = $value;

        $id_name = $this->get_element_id().'_'.$index;
        $attributes['id'] = $id_name;

        if (($value == $this->get_value())) {
            $attributes[] = "checked";
        }

        $tag = new INPUTtag($attributes);

        $label = new LABELtag(array('for' => $id_name), $name);

        $c = Container::factory($tag, $label);
        $c->set_collapse();
        return $c;
    }

    /**
     * no validation really needed here
     */
    public function validate() {
        return;
    }
}

?>