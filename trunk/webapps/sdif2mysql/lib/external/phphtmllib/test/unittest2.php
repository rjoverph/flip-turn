<?php
/**
 * This is a Unit Test script for the
 * XmlTagClass class.  It is used to make sure
 * everything works from build to build.
 * 
 * 
 * $Id: unittest2.php 1551 2005-09-07 19:26:21Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 */

define('PHPHTMLLIB', '..');
require_once(PHPHTMLLIB."/includes.inc");
require_once(PHPHTMLLIB."/tag_utils/debug_dump.inc");
/**
 * You have to have PEAR's PHPUnit installed
 * 
 * pear install PHPUnit
 */
require_once("PHPUnit.php");


/**
 * Test the Container class
 */
class XMLTagClassTest extends PHPUnit_TestCase {

    function XMLTagClassTest($name) {
        $this->PHPUnit_TestCase($name);
    }

    function test_Constructor() {
        $tag = new XMLTagClass("foo",array("bar" => 1, "blah" => ""));
        $this->assertEquals("foo", $tag->get_tag_name(), "Test tag name");
        $this->assertEquals(0, $tag->count_content(), "Test content count");
        $this->assertEquals(1, $tag->_attributes["bar"], "Test tag attribute");
    }

    function test_add() {
        $tag = new XMLTagClass("foo");
        $tag->add("foo","bar", "blah");
        $this->assertEquals(3, $tag->count_content(), "Test content count");
        $foo = $tag->get_element(2);
        $this->assertEquals("blah", $foo, "Test content value");
    }

    function test_set_cdata_flag() {
        $tag = new XMLTagClass("foo");
        $tag->add("foo","bar", "blah");
        $tag->set_cdata_flag(TRUE);
        $this->assertEquals(phphtmllib::_CDATACONTENTWRAP, $tag->get_flags() & phphtmllib::_CDATACONTENTWRAP,
                            "Test the flag bitfield");
        $this->assertEquals("<foo><![CDATA[", 
                            substr($tag->render(), 0, 14),
                            "Test CDATA tag");
    }

    function test_render() {
        $tag = new XMLTagClass("foo");
        $tag->add("foo", "bar");
        $this->assertEquals("<foo>\n".phphtmllib::_INDENT_STR."foo\n".phphtmllib::_INDENT_STR."bar\n</foo>\n",
                            $tag->render(0), 
                            "Test render with indent level 0");
        $this->assertEquals(phphtmllib::_INDENT_STR."<foo>\n".phphtmllib::_INDENT_STR.phphtmllib::_INDENT_STR."foo\n".
                            phphtmllib::_INDENT_STR.phphtmllib::_INDENT_STR."bar\n".
                            phphtmllib::_INDENT_STR."</foo>\n",
                            $tag->render(1), 
                            "Test render with indent level 1");

        $tag->set_collapse(TRUE, FALSE);
        $this->assertEquals("<foo>foobar</foo>",
                            $tag->render(1),  "Test render with collapse");
    }


    function test_factory() {
        $tag = XMLTagClass::factory('foo', array(), 'this', 'is', 'a', 'test');
        qqq('fist');
        qqq($tag);
    }
}

$suite = new PHPUnit_TestSuite('XMLTagClassTest');
$result = PHPUnit::run($suite);
if (isset($_SERVER["PHP_SELF"]) && strlen($_SERVER["PHP_SELF"]) > 0) {
    echo $result->toHTML();
} else {
    echo $result->toString();
}
?>
