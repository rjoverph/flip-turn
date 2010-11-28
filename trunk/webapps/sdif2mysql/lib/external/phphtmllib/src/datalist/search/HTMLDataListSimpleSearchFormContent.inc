<?php
/**
 * 
 * This file contains the 'simple' search 
 * FormContent used by the DefaultHTMLDataList
 * class.  This is functionally the same as the
 * old simplesearch capability of the
 * phphtmllib 2.x DefaultGUIDataList
 * 
 * $Id: HTMLDataListSimpleSearchFormContent.inc 2644 2007-05-04 01:26:36Z hemna $
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage DataList
 */


/**
 * This is the new way to do 'simple' searches for the
 * DataList
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage DataList
 */
class HTMLDataListSimpleSearchFormContent extends HTMLDataListSearchFormContent {

    
    /**
     * This method creates the FormElements used
     * by the simple search
     * 
     * @see FormContent
     * @return none
     */
    public function form_init_elements() {
        $this->add_element( new FEListBox($this->build_label(HTMLDataListSearchFormContent::LABEL_SEARCH_FIELD), FALSE,
                                          NULL, NULL,
                                          $this->_searchable_fields));

        $this->add_element( new FEText($this->build_label(HTMLDataListSearchFormContent::LABEL_SEARCH_VALUE), FALSE, 10));

        $modifier = $this->get_modifier_form_element();
        if ($modifier) {
            $this->add_element($modifier);
        }
    }

    /**
     * Where we add the buttons to the form
     * 
     */
    public function form_init_buttons() {
        $this->add_button( new FESubmitButton($this->build_label(HTMLDataListSearchFormContent::LABEL_SUBMIT)));
    }

    /**
     * initialize our form elements with any 
     * selected data?
     * 
     * @see FormContent
     */
    public function form_init_data() {
    }


    /**
     * This method builds the layout for the search form
     * 
     * @see FormContent
     * @return Container object
     */
    public function form() {
        $c = Container::factory(HTMLDataListSearchFormContent::FIND,phphtmllib::_HTML_SPACE,
                                $this->element_form($this->build_label(HTMLDataListSearchFormContent::LABEL_SEARCH_FIELD)));

        if ($this->get_search_modifier()) {
            $c->add(phphtmllib::_HTML_SPACE,
                    $this->element_form($this->build_label(HTMLDataListSearchFormContent::LABEL_SEARCH_MODIFIER)));
        }

        //now add the text box
        $c->add( phphtmllib::_HTML_SPACE,
                 $this->element_form($this->build_label(HTMLDataListSearchFormContent::LABEL_SEARCH_VALUE)),
                 phphtmllib::_HTML_SPACE,
                 $this->get_button($this->build_label(HTMLDataListSearchFormContent::LABEL_SUBMIT)));

        return $c;
    }


    /**
     * We have to extend this from the parent
     * class, but we don't need to do anything here.
     * 
     * @see FormContent
     * @return TRUE
     */
    public function form_action() {
        return TRUE;
    }



    /**
     * This method returns the field that is being searched
     * 
     * @return string
     */
    public function get_search_field_value() {
        return $this->get_element_value($this->build_label(HTMLDataListSearchFormContent::LABEL_SEARCH_FIELD));
    }


    /**
     * This method returns the search field value that the user
     * entered.  This is the actual search value
     * 
     * @return string
     */
    public function get_search_value_value() {
        return $this->get_element_value($this->build_label(HTMLDataListSearchFormContent::LABEL_SEARCH_VALUE));
    }

    /**
     * This method returns the modifier for the search field
     * 
     * @return string
     */
    public function get_search_modifier_value() {
        return $this->get_element_value($this->build_label(HTMLDataListSearchFormContent::LABEL_SEARCH_MODIFIER));

    }

    
}
?>
