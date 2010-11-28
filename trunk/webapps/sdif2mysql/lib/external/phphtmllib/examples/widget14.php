<?php

/**
 * This example illustrates the use of the
 * permissions checking mechanism built into the
 * PageWidget object.
 *
 *
 * $Id: widget14.php 2781 2007-05-18 17:52:38Z hemna $
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
 *
 * The first tab object.
 *
 * @package phpHtmlLib
 * @subpackage widget-examples
 */
class FirstTab extends TabWidget {
    public function __construct($title='First Tab Title') {
        parent::__construct($title);
    }

    public function content() {
        return 'testing 123';
    }
}

/**
 *
 * The second tab object.
 *
 * @package phpHtmlLib
 * @subpackage widget-examples
 */
class FooTab extends TabWidget {
    public function __construct() {
        parent::__construct('Foo');
    }

    public function content() {
        $dialog = new MessageBoxWidget("Some title", "400",
                                       Container::factory("This is a message",
                                                 BRtag::factory(2),
                                                 "Want to see a permissions error?",
                                                 BRtag::factory(),
                                                 Atag::factory($_SERVER["PHP_SELF"]."?failed=1",
                                                        "Click Here"))
                                                 );
        return Container::factory(BRtag::factory(),$dialog, BRtag::factory());
    }
}

/**
 *
 * The test tab.
 *
 * @package phpHtmlLib
 * @subpackage widget-examples
 */
class test extends TabWidget {
    function content() {
        return "test ".$this->get_title();
    }
}

/**
 *
 * The entire page.
 *
 * @package phpHtmlLib
 * @subpackage widget-examples
 */
class WidgetListPage extends HTMLPage {


    public function __construct($title) {
        parent::__construct($title, phphtmllib::HTML);

        //we need this for the css defined for the InfoTable
        //for the DialogWidget.  The DialogWidget uses InfoTable.
        $this->add_css_link("/css/widgets.php");
    }

    protected function permission() {
        return TRUE;
    }

    protected function head_content() {

    }

    /**
     * This will only get called if we have permissions to
     * build and render the content for this page object.
     *
     * @return object
     */
    protected function body_content() {
        $tablist = new TabList("Scan");
        $tablist->add( new FirstTab );
        $tablist->add( new FooTab );
        $tablist->add( new FirstTab('Third tab!') );

        $subtab = new TabList("list");
        $subtab->add( new test("sub 1") );
        $subtab->add( new test("sub 2") );
        $subtab->add( new test("sub 3") );
        $subtab->add( new test("sub 4") );

        $tablist->add( $subtab );


        $div = DIVtag::factory('', $tablist);
        $div->set_style('width: 600px');
        $this->add($div);
    }
}

//build the Page object and try and
//render it's content.
//the permissions checking happens at
//'constructor' time.
$page = new WidgetListPage("testing");

//the render method will not call the
//content building methods if the permissions
//fail.
print $page->render();
?>
