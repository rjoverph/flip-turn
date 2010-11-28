<?php
/**
 * This file contains the FEComboListBox class
 *
 * $Id: FEComboListBox.inc 2399 2007-02-22 21:38:46Z hemna $
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
 * This builds a complex dual select box
 * with buttons to move entries from one
 * select box to another.
 *
 * From      Actions    To
 * --------  Add >>     --------
 * |------|  Add All    |------|
 * |------|             |------|
 * |------|             |------|
 * |------|  << Remove  |------|
 * |------|  Remove All |------|
 * |------|             |------|
 * --------             --------
 *
 * @author Walter A. Boring IV
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
class FEComboListBox extends FEDataList {

    /**
     * Holds the list of available
     * data elements for the 'to'
     * box.
     *
     */
    protected $_data_list_to = array();

    /**
     * The from field's label
     *
     * @var string
     */
    protected $_from_label = 'Available';

    /**
     * The to field's label
     *
     * @var string
     */
    protected $_to_label = 'Selected';

    /**
     * This Form Element needs to
     * propogate some js to the
     * Form tag's onsubmit attribute
     *
     * @var string
     */
    protected $_has_form_on_submit = true;

    /**
     * This flag turns on/off the
     * ordering mechanism
     */
    protected $_ordering = TRUE;

    /**
     * This is an array of all the required
     * elements for the select list
     */
    protected $_required_values = array();


    /**
     * The constructor
     *
     * @param string $label text label for the element
     * @param boolean $required is this a required element?
     * @param int $width element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int $height element height in px
     * @param array $from_data_list list of 'from' field data elements (name=>value)
     * @param array $to_data_list list of 'to' field data elements (name=>value)
     */
    function __construct($label, $required = TRUE, $width="200px", $height="100px",
                         $from_data_list = array(), $to_data_list = array()) {

        $this->set_to_list_data($to_data_list);
        parent::__construct($label, $required, $width, $height, $from_data_list);
    }

    /**
     * This function sets the array of data
     * to be used in the data list
     *
     * @param array data_list - list of data elements (name=>value)
     */
    public function set_to_list_data( $data_list = array() ) {
        $this->_data_list_to = $data_list;
    }

    /**
     * Use this method to set the label for the
     * 'from' field
     *
     * @param string
     * @return none
     */
    public function set_from_label($label) {
        $this->_from_label = $label;
    }

    /**
     * Use this method to set the label for the
     * 'to' field
     *
     * @param string
     * @return none
     */
    public function set_to_label($label) {
        $this->_to_label = $label;
    }

    /**
     * Use this method to set required select values
     *
     * @param array array of valid select list values
     * @return none
     */
    public function set_required_values($required) {
        $this->_required_values = $required;
    }

    /**
     * This returns the initial value of
     * the element
     *
     * @return mixed
     */
    protected function get_init_value() {
        if (array_key_exists($this->_element_name, $_REQUEST)) {
            $all_list = array_merge( $this->_data_list, $this->_data_list_to);

            if (isset($_REQUEST[$this->_element_name])) {
                $diff = array_diff( $all_list, $_REQUEST[$this->_element_name]);
                $this->set_list_data( $diff );
                $to_list = array();

                if (is_array($_REQUEST[$this->_element_name])) {
                    foreach( $_REQUEST[$this->_element_name] as $value ) {
                        $key = array_search($value, $all_list);
                        if ($key) {
                            $to_list[$key] = $value;
                        }
                    }
                } else {
                    if (!empty($_REQUEST[$this->_element_name])) {
                        $to_list[array_search($_REQUEST[$this->_element_name], $all_list)] = $_REQUEST[$this->_element_name];
                    }
                }
                $this->set_to_list_data( $to_list );
            } else {
                //the assigned list is empty
                $this->set_list_data( $all_list );
                $this->set_to_list_data(array());
            }
        }
        return $this->_data_list_to;
    }


    /**
     * This function will set the
     * initial value for the element
     *
     * @param value mixed
     */
    public function set_value($value) {
        //we need to diff what is available and what is
        //selected so that we don't show duplicated entries.
        if (!is_array($value)) {
            //$this->set_list_data( $diff );
            $this->set_to_list_data(array());
        } else {
            $diff = array_diff( $this->_data_list, $value);
            $this->set_list_data( $diff );
            $this->set_to_list_data($value);
        }
    }


    /**
     * This method turns on the right select box's
     * ability to show the ordering buttons.
     *
     * @param bool
     */
    public function enable_ordering($flag=TRUE) {
        $this->_ordering = $flag;
    }

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    public function get_element() {
        $table = html_table();
        $table->add_row($this->_from_label, phphtmllib::_HTML_SPACE,
                        $this->get_label(NULL,$this->_to_label, FALSE));

        $from_select = form_select($this->_element_name.'_available',
                                   $this->_data_list,'', TRUE);

        if ($this->onChangeJS != null) {
            $from_select->set_tag_attribute("onChange", $this->onChangeJS);
        }

        $from_select->set_tag_attribute('id', $this->get_element_id().'_from');

        $style = '';
        if ($this->_height) {
            $style .= "height: ".$this->_height.";";
        }
        if ($this->_width) {
            $style .= "width: ".$this->_width.";";
        }

        //build the buttons
        $button_style = 'width: 90px;';
        $f_name = $this->_element_name."_move_around";
        $add = form_button($this->_element_name.'_add', 'Add >>', array('style' => $button_style,
                                                                        'onclick' => $f_name."('right',false);"));
        $add_all = form_button($this->_element_name.'_add_all', 'Add All', array('style' => $button_style,
                                                                                 "onclick" => $f_name."('right', true);"));

        $remove = form_button($this->_element_name.'_remove', '<< Remove', array('style' => $button_style,
                                                                                 'onclick' => $f_name."('left', false);"));
        $remove_all = form_button($this->_element_name.'_remove_all', 'Remove All', array('style' => $button_style,
                                                                                          'onclick' => $f_name."('left', true);"));

        $to_select = form_select($this->_element_name.'[]',
                                 $this->_data_list_to, '', TRUE);

        if (strlen($style) > 0) {
            $from_select->set_style($style);
            $to_select->set_style($style);
        }

        //check to see if we are disabled
        if ($this->is_disabled()) {
            $from_select->set_tag_attribute('disabled');
            $add->set_tag_attribute('disabled');
            $add_all->set_tag_attribute('disabled');
            $remove->set_tag_attribute('disabled');
            $remove_all->set_tag_attribute('disabled');
            $to_select->set_tag_attribute('disabled');
        }

        $to_select->set_tag_attribute('id', $this->get_element_id().'_to');


        $button_td = new TDtag(array('align' => 'left'),
                                   $add, html_br(), $add_all, html_br(2),
                                   $remove, html_br(), $remove_all);

        $f_name = $this->_element_name."_order";

        $move_up = form_button('Move Up', 'Move Up', array('onclick' => "javascript: ".$f_name."(0)"));
        $move_down = form_button('Move Down', 'Move Down', array('onclick' => "javascript: ".$f_name."(1)"));

        //IE sucks.
        $button_td->set_collapse();

        $tr = html_tr();
        $tr->add( $from_select,
                  $button_td,
                  $to_select);

        if ($this->_ordering) {
            $tr->add(Container::factory($move_up, $move_down));
        }
        $table->add_row( $tr );

        return $table;
    }

    /**
     *
     * This function is responsible for performing complete
     * validation and setting the appropriate error message
     * in case of a failed validation
     *
     * NOTE: This makes sure that the data submitted for both
     *       fields is in the original list.
     *
     */
    public function validate() {
        //need to make sure we only allow
        //elements that the class has.
        $combined = array_flip(array_merge( $this->_data_list, $this->_data_list_to));

        if (isset($_REQUEST[$this->_element_name])) {
            if (is_array($_REQUEST[$this->_element_name])) {
                foreach( $_REQUEST[$this->_element_name] as $value ) {
                    if (!isset($combined[$value])) {
                        Validator::error(ValidatorException::STR_INVALID_FIELD);
                    }
                }
                return TRUE;
            } else {
                if (!isset($combined[$value])) {
                    Validator::error(ValidatorException::STR_INVALID_FIELD);
                }
            }
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
        return implode( ", ", array_keys( $this->get_value() ) );
    }

    /**
     * This is a method for getting the JS needed
     * for the form tag's onsubmit attribute.
     *
     * @return string
     */
    public function onSubmit() {
        return $this->_element_name.'_check_submit();';
    }

    /**
     * This method builds the Javascript needed for this
     * element.
     *
     * @return string The javascript.
     */
    public function javascript() {

        $from_id = $this->get_element_id().'_from';
        $to_id = $this->get_element_id().'_to';

        $js =  "function ".$this->_element_name."_move_around(direction, all) {\n".
               "  if (direction==\"right\") {\n".
               "    box1 = \"".$this->_element_name."_available\";\n".
               "    box2 = \"".$this->_element_name."[]\";\n".
               "  } else {\n".
               "    box1 = \"".$this->_element_name."[]\";\n".
               "    box2 = \"".$this->_element_name."_available\" + \"\";\n".
               "  }\n".

               "  for (var i=0;i<document.forms[0].elements[box1].length;i++) {\n";

        // Display a javascript error for any demographics that shouldn't be moved
        if (!empty($this->_required_values)) {
            foreach ($this->_required_values as $required) {
                $required_list[] = "document.forms[0].elements[box1][i].value == $required";
            }

            $required_list = join(" || ",$required_list);

            $js .= "    if (direction==\"left\" && (document.forms[0].elements[box1][i].selected || all) && ".
                   "    (".$required_list . ")) {\n".
                   "        alert(document.forms[0].elements[box1][i].innerHTML + ' is required');\n".
                   "    }\n".
                   "    else if ((document.forms[0].elements[box1][i].selected || all)) {\n";
        } else {
            $js .= "    if ((document.forms[0].elements[box1][i].selected || all)) {\n";
        }

        $js .= "      // add to the other list box\n".
               "      document.forms[0].elements[box2].options[document.forms[0].elements[box2].length] =".
               "    new Option(document.forms[0].elements[box1].options[i].text, document.forms[0].elements[box1][i].value);\n".
               "      // remove from the current listbox\n".
               "      document.forms[0].elements[box1][i] = null;\n".
               "      i--;\n".
               "    }\n".
               "   }\n".
               "}\n";


        $js .= "\nfunction ".$this->_element_name."_check_submit() {\n".
               "  // select all items in the added ip list\n".
               "  // in order to include in the post data\n".
               "  box = \"".$this->_element_name."[]\";\n".
               "  if (document.forms[0].elements[box]) {\n".
               "    for (var i=0;i<document.forms[0].elements[box].length;i++) {\n".
               "      document.forms[0].elements[box][i].selected = true;\n".
               "    }\n".
               "  }\n".

               "  // disable the buttons\n".
               "  //document.forms[0]._form_action1.disabled = true;\n".
               "  //if (document.forms[0]._form_action2)\n".
               "  //    document.forms[0]._form_action2.disabled = true;\n".
               "  //document.forms[0].cancel.disabled = true;\n".
               "  return true;\n".
               "}\n";


        //the to select box ordering
        $js .=  "\nfunction ".$this->_element_name."_order(down) {\n".
                "  to = document.getElementById('".$to_id."'); \n".
                "  sl = to.selectedIndex; \n".
                "  if ((sl != -1) && (to.options[sl].value > '')) {\n".
                "    oText = to.options[sl].text;\n".
                "    oValue = to.options[sl].value;\n".
                "    if ((to.options[sl].value > '') && (sl > 0) && (down == 0)) {\n".
                "      to.options[sl].text = to.options[sl-1].text;\n".
                "      to.options[sl].value = to.options[sl-1].value;\n".
                "      to.options[sl-1].text = oText;\n".
                "      to.options[sl-1].value = oValue;\n".
                "      to.selectedIndex--;\n".
                "    } else if ((sl < to.length-1) && (to.options[sl+1].value > '') && (down == 1)) {\n".
                "      to.options[sl].text = to.options[sl+1].text;\n".
                "      to.options[sl].value = to.options[sl+1].value;\n".
                "      to.options[sl+1].text = oText;\n".
                "      to.options[sl+1].value = oValue;\n".
                "      to.selectedIndex++;\n".
                "    }\n".
                "  } else {\n".
                "    alert('Please select an entry to move');\n".
                "  }\n".
               "}\n";

        return trim($js);
    }

    /**
     * This function will return the
     * elements value
     *
     * @return mixed
     */
    public function get_value(){
        return $this->_data_list_to;
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
    public function get_confirm_element(){
        $name = $this->get_element_name();

        $c = Container::factory();
        if (is_array( $_REQUEST[$name]) ) {
            foreach( $_REQUEST[$name] as $value ){
                $c->add(form_hidden( $name."[]", $value));
            }
        } else {
            $c->add(form_hidden($name."[]", $_REQUEST[$name] ));
        }

        return $c;
    }
}

?>
