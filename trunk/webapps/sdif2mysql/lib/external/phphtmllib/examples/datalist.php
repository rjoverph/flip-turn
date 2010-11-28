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
 * $Id: datalist.php 2777 2007-05-18 17:14:14Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage widget-examples
 * @version 2.0
 *
 */

/**
 * Include the phphtmllib libraries
 *
 */

include_once("includes.inc");
include_once("db_defines.inc");


/**
 * This class shows how to use the data coming
 * from a CSV Formatted file
 *
 * @package phpHtmlLib
 * @subpackage widget-examples
 *
 */
class csvfilelist extends DefaultHTMLDataList {

    protected function get_data_source() {
        $source = new CSVFILEDataListSource("test.csv");
        $this->set_data_source( &$source );
    }

    protected function user_setup() {
        $this->add_header_item("First Name", "200", "FName", HTMLDataList::SORTABLE, HTMLDataList::SEARCHABLE);
        $this->add_header_item("Last Name", "200", "LName", HTMLDataList::SORTABLE, HTMLDataList::SEARCHABLE);
        $this->add_header_item("Email", "200", "Email", HTMLDataList::SORTABLE, HTMLDataList::SEARCHABLE, "center");

        //lets add an action column of checkboxes,
        //and allow us to save the checked items between pages.
        $this->add_action_column(DefaultHTMLDataList::ACTION_CHECKBOX, DefaultHTMLDataList::ACTION_FIRST, 'Email');
        $this->add_action_column(DefaultHTMLDataList::ACTION_RADIO, DefaultHTMLDataList::ACTION_LAST, 'LName');

        $this->set_debug(2);
        //$this->set_default_num_rows(12);
        $this->set_form_method('POST');
        $this->save_checked_items(TRUE);
        $this->search_enable();
    }

}


//create the page object
$page = new HTMLDocument("phpHtmlLib Widgets - DataList Example",
                         XHTML_TRANSITIONAL);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}

//add the css
$page->add_head_css( new DefaultHTMLDataListCSS );

//build the csv file data list object.
$csvlist = new csvfilelist("CSV File list", 600, "LName");
//ddd($csvlist);

$page->add( SPANtag::factory("font10", "View the source ",
                      Atag::factory("test.csv", "test.csv file.")),
            BRtag::factory(2),
            $csvlist );

print $page->render();
?>
