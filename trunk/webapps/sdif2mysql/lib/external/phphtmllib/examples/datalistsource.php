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
 * $Id: datalistsource.php 2777 2007-05-18 17:14:14Z hemna $
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


define("ADODB_FORCE_NULLS", TRUE);

ini_set("include_path",
		ini_get("include_path").":".$_SERVER["DOCUMENT_ROOT"]."/adodb");
require_once( "adodb.inc.php" );

$GLOBALS['ADODB_FETCH_MODE'] = ADODB_FETCH_ASSOC;

//$source = new CSVFILEDataListSource("test.csv");
//$source->set_orderby('FName');
//$source->set_reverseorder(TRUE);

try {
    $db = &ADONewConnection('mysql');  # create a connection
    $db->Connect(DB_HOSTNAME,DB_USERNAME,DB_PASSWORD,DB_NAME);
} catch(Exception $e) {
      var_dump('oops exception '.$e->getMessage());
}
$source = new ADODBSQLDataListSource($db);
$source->set_debug(2);

$source->add_column('ID', 'SCHEMA_ID', TRUE);
$source->add_column('SERIAL', 'SERIAL_NUMBER', TRUE);
$source->add_column('DATE', 'INSERT_DATE', TRUE);
$source->add_column('VERSION', 'APP_VERSION', TRUE);

$source->set_query_params(0,110, 'SCHEMA_ID', FALSE, 'SCHEMA_ID', 2, HTMLDataList::SEARCH_EXACT);
$source->setup_db_options('*', 'Schema_Version');

$res = $source->execute();
if (!$res) {
    var_dump('Oops!!');
    exit;
}
//ddd($source);
//ddd($source);

foreach( $source as $value ) {
    var_dump($value);
}


//create the page object
$page = new HTMLDocument("phpHtmlLib Widgets - DataList Example",
                         XHTML_TRANSITIONAL);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}

//add the css
//$page->add_head_css( new DefaultGUIDataListCSS );

$page->add( html_span("font10", "View the source ",
					  html_a("test.csv", "test.csv file.")),
			html_br(2),
            'ass' );

print $page->render();
?>
