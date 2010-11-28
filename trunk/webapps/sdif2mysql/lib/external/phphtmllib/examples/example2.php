<?php

/**
 * Another example of how to build a table
 * with some data
 *
 *
 * $Id: example2.php 2089 2006-09-23 00:26:13Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage examples
 * @version 2.0.0
 *
 */

/**
 * Include the phphtmllib libraries
 */
include_once("includes.inc");


//create the page object
$page = new HTMLDocument("phpHtmlLib Example 2 - Table example script",
                         phphtmllib::XHTML_TRANSITIONAL);

if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}


//build a <style> tag and a little bit
//of local css declarations to spruce up
//the look of the table.
//You can also easily add external stylesheet
//links.  I'll show that in other examples.
$style = STYLEtag::factory();
$style->add( "span.foo { font-size: 1em; font-weight: bolder;}" );
$style->add( "td { padding-left: 5px; text-align: center;}" );
$style->add( "table {border: 2px solid #999999;}" );
$style->add( "th {background-color: #eeeeee; ".
			      "border-bottom: 2px solid #999999;}" );
$style->add( "caption { font-size: 14pt; font-weight: bold;}" );
$page->add_head_content( $style );


//lets add a simple link to this script
//and turn debugging on,
//then add 2 <br> tags
$page->add( Atag::factory($_SERVER["PHP_SELF"]."?debug=1", "Show Debug Source"),
			BRtag::factory(2) );


//build the table that will hold the data
$data_table = TABLEtag::factory("500", 0, 0);

//add a caption for the table.
$data_table->add( CAPTIONtag::factory("A Caption for the table") );

//Add 1 <tr> to the table with 3 <th> tags.
$data_table->add_row( THtag::factory("Column 1"), THtag::factory("Column 2"),
					  THtag::factory("BAR") );


//now demonstrate an easy way to add
//20 rows to a table 1 row at a time.
//You could easily pull the row data from
//a DB
for($x=0; $x<20; $x++) {
	//add 1 <tr> to the table with 3 <td>'s
	//the last <td> contains a span with a
	//class attribute of "foo"
	$data_table->add_row("Row #".($x+1),
						 $x*2,
						 SPANtag::factory("foo", "something else"));
}

//add the table to the page.
$page->add( $data_table );


//this will render the entire page
print $page->render();
?>
