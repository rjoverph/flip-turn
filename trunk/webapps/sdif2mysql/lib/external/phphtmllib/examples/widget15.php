<?php
/**
 * This example illustrates the use of the
 * TabControl Widget.  This widget gives you
 * the ability to build content for n # of tabs
 * and have the browser switch between the tabs
 * without a request to the server.
 *
 *
 * @author Culley Harrelson <culley@fastmail.fm>
 * @package phpHtmlLib
 * @subpackage widget-examples
 * @version $Id: widget15.php 2781 2007-05-18 17:52:38Z hemna $
 *
 */

/**
 * Include the phphtmllib libraries
 *
 */
include("includes.inc");

//create the page object
$page = new HTMLDocument("phpHtmlLib Widgets - Tab Control Example",
                         phphtmllib::XHTML_TRANSITIONAL);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}
//use the default theme
$page->add_css_link( "/css/widgets.php" );

$tab = new TabControlWidget(BIGtag::factory('My Big Dumb Tab Control'), 'right');
$tab->add_tab(Atag::factory("javascript:e=document.getElementById('secretitem'); e.style.display='block';void(0)", 'Click Me Tab'), false);
$tab->add_tab(Atag::factory('#', 'Dumb Tab #2'), true);
$tab->add_tab(Atag::factory('javascript:alert(\'he haw\');void(0)', 'Super really long tab for the verbose'), false);
$page->add($tab);
$div = DIVtag::factory('', 'Surprise!');
$div->set_id('secretitem');
$div->set_style('display:none;');
$page->add(BRtag::factory(2), $div);


$title = html_div('', 'Click every tab before you leave');
//$title->set_tag_attribute('align', 'right');
//$title->set_style('padding: 5px;');
$tab2 = new TabControlWidget();
for ($i = 1; $i<6; $i++) {
    if ((!array_key_exists('tab', $_GET) and $i == 1) or $_GET['tab'] == $i) {
        $tab2->add_tab(Atag::factory("{$_SERVER['PHP_SELF']}?tab=$i", "Tab $i"), true);
    } else {
        $tab2->add_tab(Atag::factory("{$_SERVER['PHP_SELF']}?tab=$i", "Tab $i"), false);
    }
}
$page->add($tab2);

print $page->render();
?>
