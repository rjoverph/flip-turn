<?php
/**
 * This file contains the FormContent
 * used by the HTMLDataList for managing
 * a search form.
 *
 * $Id: HTMLDataListSearchFormContent.inc 2644 2007-05-04 01:26:36Z hemna $
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage DataList
 */

/**
 * This class is an example of how to build
 * a SearchForm for the DataList.
 * This class provides the 'simple' search
 * that used to exist in the DefaultGUIDataList.
 *
 * Now you have the flexibility of using all of the
 * FormElements from the form engine to build a
 * Search area for the DataList.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage DataList
 */
abstract class HTMLDataListSearchFormContent extends FormContent {

    //Some defines for setting up the search
    //modifier fields.
    const SEARCH_BEGINS_WITH = 1;
    const SEARCH_CONTAINS = 2;
    const SEARCH_EXACT = 4;
    const SEARCH_ENDS_WITH = 8;
    const SEARCH_ALL = 15;



    //Some FormElement labels
    const FIND = 'Find';

    const LABEL_SEARCH_FIELD = 'searchfield';
    const LABEL_SEARCH_MODIFIER = 'searchmodifier';
    const LABEL_SEARCH_VALUE = 'searchvalue';

    const LABEL_SUBMIT = 'Search';



    /**
     * Some member vars
     */
    protected $_searchable_fields = array();

    /**
     * Flag to enable simple search modifyer.
     * IF enabled it will add a select that adds
     * the "beings with", "contains" options for
     * a simple search.
     */
    protected $_search_modifier = HTMLDataListSearchFormContent::SEARCH_ALL;



    /************************/
    /* DataList API methods */
    /************************/


    /**
     * This method is called from the DataList to
     * tell us what fields in the DataList are
     * searchable.
     *
     * @param array
     *        NOTE in format ( LABEL => VALUE )
     */
    public function set_searchable_fields($fields) {
        $this->_searchable_fields = $fields;
    }


    /**
     * This is used to set the global offset
     * which prefixes all the FormElement labels
     *
     * @param string
     */
    public function set_global_prefix($string) {
        $this->_global_prefix = $string;
    }


    /**
     * This method is used to build a FormElement
     * label using the global prefix.
     * If you don't use this in creating the label,
     * then there could be conflicts with multiple
     * DataLists.
     *
     * @param string
     * @return string
     */
    protected function build_label($name) {
        return $this->_global_prefix.$name;
    }




    /************************/
    /*   Internal methods   */
    /************************/



    /**
     * This builds the simple search modifier
     * select box.
     *
     * @return FEListBox object.
     */
    protected function get_modifier_form_element() {
        $options = array();

        if (!$this->_search_modifier) {
            return FALSE;
        }

        if ( $this->_search_modifier & self::SEARCH_BEGINS_WITH ) {
            $options["beginning with"] = "BEGINS";
        }
        if ( $this->_search_modifier & self::SEARCH_CONTAINS ) {
            $options["containing"] = "CONTAINS";
        }
        if ( $this->_search_modifier & self::SEARCH_EXACT ) {
            $options["matching"] = "EXACT";
        }
        if ( $this->_search_modifier & self::SEARCH_ENDS_WITH ) {
            $options["ending with"] = "ENDS";
        }

        //$selected = $this->search_modifier_value();
        //make the default Begins with
        //if ( !$selected ) {
        //    $selected = "BEGINS";
        //}

        return new FEListBox($this->build_label(self::LABEL_SEARCH_MODIFIER), FALSE, NULL, NULL, $options);
    }

    /**
     * Set the simple search modifyer
     * flag.
     * NOTE: by default all the modifiers
     *       are enabled.  You can limit the
     *       modifiers by passing in the
     *       string of defines of which ones
     *       you want enabled.
     *
     * MODIFIERS:
     *          SEARCH_BEGINS_WITH
     *          SEARCH_CONTAINS
     *      SEARCH_EXACT
     *      SEARCH_ENDS_WITH
     *
     *       ie. SEARCH_BEGINS_WITH.SEARCH_EXACT
     *           will enable ONLY the
     *           "begins with" and "exact" modifiers.
     *
     * @param string
     */
    public function set_search_modifier( $modifier = self::SEARCH_ALL ) {
        if ( $modifier == 0 ) {
            $this->_search_modifier = self::SEARCH_BEGINS_WITH |
                                      self::SEARCH_CONTAINS |
                                      self::SEARCH_EXACT |
                                      self::SEARCH_ENDS_WITH;
        } else {
            $this->_search_modifier = $modifier;
        }
    }

    /**
     * Return the current value of the
     * search modifier bitmask.
     *
     * @see set_search_modifier();
     * @return int
     */
    public function get_search_modifier() {
        return $this->_search_modifier;
    }




    /**
     * This method returns the field that is being searched
     *
     * @return string
     */
    abstract public function get_search_field_value();


    /**
     * This method returns the search field value that the user
     * entered.  This is the actual search value
     *
     * @return string
     */
    abstract public function get_search_value_value();

    /**
     * This method returns the modifier for the search field
     *
     * @return string
     */
    abstract public function get_search_modifier_value();
}
?>
