<?php

/**
 * This example illustrates how to use the
 * HTMLPageClass to build a complete html
 * page.
 *
 *
 * $Id: example1.php 2089 2006-09-23 00:26:13Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage examples
 * @version 2.0.0
 *
 */

/**
 * Include the phphtmllib libraries
 * All subsequent examples will use the
 * inlude_once("includes.inc");
 */
include_once("includes.inc");

//create the page object

//the first parameter is the title of the page.
//this will automatically get placed inside the <title>
//inside the head.

//we want XHTML output instead of HTML
//IF you want HTML output, then just leave off the
//2nd parameter to the constructor.

//Be default, phpHtmlLib will nicely indent all of the output
//of the html source, to make it easy to read.  If you want
//all of the html source output to be left justified, then
//pass INDENT_LEFT_JUSTIFY as the 3rd parameter.
$page = new HTMLDocument("phpHtmlLib Example 1 - Hello World",
                         phphtmllib::XHTML_TRANSITIONAL);

//if you want phphtmllib to render the
//output as viewable source code
//then add ?debug=1 to the query string to this script
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}



//add the obligitory hello world
//calling the add method will add the object
//into the page.  It will get rendered when
//you call the HTMLPageClass' render() method.
$page->add( SPANtag::factory(NULL, "hello world"), BRtag::factory(2) );

//note the calls to the 2 factory methods
//SPANtag::factory() and BRtag::factory()  These are wrapper
//functions for constructing tags and adding common
//attributes, along with content.
// Every HTMLTagClass object has a factory method.

//BRtag::factory() builds a <br> tag.  The parameter is
//how many <br>'s to build.


//lets add a simple link to this script
//and turn debugging on
$page->add( Atag::factory($_SERVER["PHP_SELF"]."?debug=1", "Show Debug source") );


//this will render the entire page
//with the content you have added
//wrapped inside all the required
//elements for a complete HTML/XHTML page.
//NOTE: all the objects in phphtmllib have
//      the render() method.  So you can call
//      render on any phphtmlib object.
print $page->render();
?>
