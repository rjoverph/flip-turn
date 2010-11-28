<?php

/**
 * This example illustrates the use of the
 * DataList object classes.  This object
 * can show a list of data from any data source
 * and have any GUI layout and provide the
 * features of:
 * searching, sorting, paging of the data.
 *
 * This page shows the Data coming a CSV
 * (comma seperated values) file on disk.
 *
 * $Id: widget7.php 2781 2007-05-18 17:52:38Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage widget-examples
 * @version 3.0.0
 *
 */

/**
 * Include the phphtmllib libraries
 *
 */
include_once("includes.inc");


/**
 * This class shows how to use the data coming
 * from a CSV Formatted file
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage widget-examples
 * @version 3.0.0
 */
class csvfilelist extends DefaultHTMLDataList {

    /**
     * the default base path to images
     * used by any child of
     * this class.
     */
    protected $_image_path = '/images/widgets/';

    function get_data_source() {
        $source = new CSVFILEDataListSource("test.csv");
        $this->set_data_source( &$source );
    }

    function user_setup() {
        $this->add_header_item("First Name", "200", "FName", HTMLDataList::SORTABLE, HTMLDataList::SEARCHABLE);
        $this->add_header_item("Last Name", "200", "LName", HTMLDataList::SORTABLE, HTMLDataList::SEARCHABLE);
        $this->add_header_item("Email", "200", "Email", HTMLDataList::SORTABLE, HTMLDataList::SEARCHABLE, "center");

        //turn on the 'collapsable' search block.
        //The word 'Search' in the output will be clickable,
        //and hide/show the search box.
        $this->_collapsable_search = TRUE;

        //lets add an action column of checkboxes,
        //and allow us to save the checked items between pages.
        $this->add_action_column(DefaultHTMLDataList::ACTION_CHECKBOX,
                                 DefaultHTMLDataList::ACTION_FIRST, 'Email');

        //we have to be in POST mode, or we could run out
        //of space in the http request with the saved
        //checkbox items
        $this->set_form_method('POST');

        //set the flag to save the checked items
        //between pages.
        $this->save_checked_items(TRUE);
    }

    function actionbar_cell() {
        //don't actually do anything.
        //just show how to add a button
        return $this->action_button('Test','');
    }
}

/**
 * The page class to show the datalist
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage widget-examples
 * @version 3.0.0
 */
class CSVDataListPage extends HTMLPage {

    protected function permission() {
        return TRUE;
    }

    protected function head_content() {
        //add the css
        //$this->add_head_css( new DefaultGUIDataListCSS );
        $this->add_css_link( "/css/widgets.php" );
    }

    protected function body_content() {

        //build the csv file data list object.
        $csvlist = new csvfilelist("CSV File list", 600, "LName");

        $this->add( SPANtag::factory("font10", "View the source ",
                              Atag::factory("test.csv", "test.csv file.")),
                    BRtag::factory(2),
                    $csvlist );
    }
}


//create the page object
$page = new CSVDataListPage("phpHtmlLib Widgets - DataList Example",
                            phphtmllib::XHTML_TRANSITIONAL);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}

print $page->render();
?>
