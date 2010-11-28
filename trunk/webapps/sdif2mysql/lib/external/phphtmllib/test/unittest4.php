<?php
/**
 * This is a Unit Test script for the
 * HTMLTagClass class.  It is used to make sure
 * everything works from build to build.
 * 
 * 
 * $Id: unittest4.php 1551 2005-09-07 19:26:21Z hemna $
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
class HTMLTagClassTest extends PHPUnit_TestCase {

    function HTMLTagClassTest($name) {
        $this->PHPUnit_TestCase($name);
    }

    function test_Atag() {
        $url = 'www.cnn.com';
        $content = 'click me!';
        $class = 'foo';
        $target = 'bar';
        $title = 'testing';

        $rendered = '<a href="www.cnn.com" class="foo" target="bar" title="testing">click me!</a>';

        $obj = new Atag(array('href' => $url,
                              'class' => $class,
                              'target' => $target,
                              'title' => $title),
                        $content);
        $obj->set_collapse();

        $tag = Atag::factory($url, $content, $class, $target, $title);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_a($url, $content, $class, $target, $title);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }


    function test_ABBRtag() {
        $title = 'testing';
        $content = 'foobar';

        $rendered = '<abbr title="testing">foobar</abbr>';

        $obj = new ABBRtag(array('title'=>$title),
                           $content);

        $tag = ABBRtag::factory($title, $content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_abbr($title, $content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }


    function test_ACRONYMtag() {
        $title = 'testing';
        $content = 'foobar';

        $rendered = '<acronym title="testing">foobar</acronym>';

        $obj = new ACRONYMtag(array('title'=>$title),
                              $content);

        $tag = ACRONYMtag::factory($title, $content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_acronym($title, $content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }


    function test_ADDRESStag() {

        $rendered = '<address></address>';

        $obj = new ADDRESStag;
        $tag = ADDRESStag::factory();
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_address();
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_APPLETtag() {

        $rendered = '<applet></applet>';

        $obj = new APPLETtag;
        $tag = APPLETtag::factory();
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_applet();
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_AREAtag() {
        $href = 'www.cnn.com';
        $coords = 'coords';
        $shape = 'shape';
        $alt = 'alt';
        $target = 'target';
        $title = 'title';

        $rendered = '<area href="www.cnn.com" coords="coords" shape="shape" alt="alt" target="target" title="title">';

        $obj = new AREAtag(array('href' => $href,
                                 'coords' => $coords,
                                 'shape' => $shape,
                                 'alt' => $alt,
                                 'target' => $target,
                                 'title' => $title));

        $tag = AREAtag::factory($href, $coords, $shape, $alt, $target, $title);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_area($href, $coords, $shape, $alt, $target, $title);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_Btag() {

        $content = 'foo bar';
        $rendered = '<b>foo bar</b>';

        $obj = new Btag(NULL, $content);
        $tag = Btag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_b($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_BASEtag() {

        $href = 'http://phphtmllib.newsblob.com/';
        $rendered = '<base href="http://phphtmllib.newsblob.com/">';

        $obj = new BASEtag(array('href'=>$href));
        $tag = BASEtag::factory($href);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_base($href);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_BDOtag() {

        $dir = 'ltr';
        $content = "testing";
        $rendered = '<bdo dir="ltr">testing</bdo>';

        $obj = new BDOtag(array('dir'=>$dir), $content);
        $tag = BDOtag::factory($dir, $content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_bdo($dir, $content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_BIGtag() {

        $content = 'foo bar';
        $rendered = '<big>foo bar</big>';

        $obj = new BIGtag(NULL, $content);
        $tag = BIGtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_big($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_BLOCKQUOTEtag() {

        $content = 'foo bar';
        $rendered = '<blockquote>foo bar</blockquote>';

        $obj = new BLOCKQUOTEtag(NULL, $content);
        $tag = BLOCKQUOTEtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_blockquote($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }


    function test_BODYtag() {

        $content = 'foo bar';
        $rendered = '<body>foo bar</body>';

        $obj = new BODYtag(NULL, $content);
        $tag = BODYtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_body($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }


    function test_BRtag() {

        $num=3;
        $class='foo';
        $rendered = '<br class="foo">';
        $rendered_double = '<br class="foo"><br class="foo"><br class="foo">';

        $obj = new BRtag(array('class'=>$class));
        $tag = BRtag::factory(1, $class);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_br(1, $class);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        $brs = BRtag::factory($num, $class);
        $this->assertEquals('Container', get_class($brs),
                            "Didn't return a container!");

        $this->assertEquals($num, $brs->count_content(),
                            "Container doesn't have ".$num." brs!");

        $this->assertEquals($rendered_double,
                            trim($brs->render()),
                            $num." BRs didn't render properly");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }


    function test_BUTTONtag() {

        $content = 'foo bar';
        $type = 'reset';
        $rendered = '<button type="reset">foo bar</button>';

        $obj = new BUTTONtag(array('type' => $type), $content);
        $tag = BUTTONtag::factory($type, $content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_button($type, $content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_CAPTIONtag() {

        $content = 'foo bar';
        $rendered = '<caption>foo bar</caption>';

        $obj = new CAPTIONtag(NULL, $content);
        $tag = CAPTIONtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_caption($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_CENTERtag() {

        $content = 'foo bar';
        $rendered = '<center>foo bar</center>';

        $obj = new CENTERtag(NULL, $content);
        $tag = CENTERtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_center($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_CITEtag() {

        $content = 'foo bar';
        $rendered = '<cite>foo bar</cite>';

        $obj = new CITEtag(NULL, $content);
        $tag = CITEtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_cite($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_CODEtag() {

        $content = 'foo bar';
        $rendered = '<code>foo bar</code>';

        $obj = new CODEtag(NULL, $content);
        $tag = CODEtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_code($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_COLtag() {

        $width = 2;
        $span = 'foo';
        $align = '';
        $rendered = '<col width="2" span="foo"></col>';

        $obj = new COLtag(array('width' => $width, 'span' => $span));
        $tag = COLtag::factory($width, $align, $span);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_col($width, $align, $span);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_COLGROUPtag() {

        $attributes = array('foo' => 'bar', 'span' => 2);
        $rendered = '<colgroup foo="bar" span="2"></colgroup>';

        $obj = new COLGROUPtag($attributes);
        $tag = COLGROUPtag::factory($attributes);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_colgroup($attributes);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_DDtag() {

        $content = 'foo bar';
        $rendered = '<dd>foo bar</dd>';

        $obj = new DDtag(NULL, $content);
        $tag = DDtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_dd($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_DELtag() {

        $content = 'foo bar';
        $rendered = '<del>foo bar</del>';

        $obj = new DELtag(NULL, $content);
        $tag = DELtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_del($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_DFNtag() {

        $content = 'foo bar';
        $rendered = '<dfn>foo bar</dfn>';

        $obj = new DFNtag(NULL, $content);
        $tag = DFNtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_dfn($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_DIRtag() {

        $content = 'foo bar';
        $rendered = '<dir>foo bar</dir>';

        $obj = new DIRtag(NULL, $content);
        $tag = DIRtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_dir($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_DIVtag() {

        $content = 'foo bar';
        $rendered = '<div>foo bar</div>';

        $obj = new DIVtag(NULL, $content);
        $tag = DIVtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_div('',$content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_DLtag() {

        $content = 'foo bar';
        $rendered = '<dl>foo bar</dl>';

        $obj = new DLtag(NULL, $content);
        $tag = DLtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_dl($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_DOCTYPEtag() {

        $doc_element = 'HTML';
        $source = 'PUBLIC';
        $link1 = 'http://phphtmllib.newsblob.com';
        $link2 = NULL;
        $rendered = '<!DOCTYPE HTML PUBLIC "http://phphtmllib.newsblob.com">';

        $obj = new DOCTYPEtag(array($doc_element, $source, '"'.$link1.'"'));
        $tag = DOCTYPEtag::factory($doc_element, $source, $link1, $link2);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = xml_doctype($doc_element, $source, $link1, $link2);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_DTtag() {

        $content = 'foo bar';
        $rendered = '<dt>foo bar</dt>';

        $obj = new DTtag(NULL, $content);
        $tag = DTtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_dt($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_EMtag() {

        $content = 'foo bar';
        $rendered = '<em>foo bar</em>';

        $obj = new EMtag(NULL, $content);
        $tag = EMtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_em($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_FIELDSETtag() {

        $content = 'foo bar';
        $legend = 'monkey';
        $rendered = "<fieldset>\n  <legend>monkey</legend>\n  foo bar\n</fieldset>";

        $obj = new FIELDSETtag(NULL, new LEGENDtag(NULL, $legend), $content);
        $tag = FIELDSETtag::factory($legend, $content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_fieldset($legend, $content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_FONTtag() {

        $content = 'foo bar';
        $rendered = '<font>foo bar</font>';

        $obj = new FONTtag(NULL, $content);
        $tag = FONTtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_FORMtag() {

        $content = 'foo bar';
        $name = 'foo';
        $action = 'phphtmllib.newsblob.com';
        $method = 'POST';
        $onsubmit = "javascript: alert('eek!')";
        $rendered = '<form name="foo" action="phphtmllib.newsblob.com" method="POST" onsubmit="javascript: alert(\'eek!\')">foo bar</form>';

        $obj = new FORMtag(array('name' => $name,
                                 'action' => $action,
                                 'method' => $method,
                                 'onsubmit' => "javascript: alert('eek!')"), 
                           $content);
        $tag = FORMtag::factory($name, $action, $method, array('onsubmit' => $onsubmit));
        $tag->add($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_form($name, $action, $method, array('onsubmit' => $onsubmit));
        $helper->add($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }


    function test_FRAMEtag() {

        $name = 'foo';
        $src = "phphtmllib.newsblob.com";
        $scrolling="yes";

        $attributes = array('name' => $name,
                            'src' => $src,
                            'scrolling' => $scrolling,
                            'marginwidth' => 0,
                            'marginheight' => 0,
                            'noresize',
                            'frameborder' => 'no');

        $rendered = '<frame name="foo" src="phphtmllib.newsblob.com" scrolling="yes" marginwidth="0" marginheight="0" noresize frameborder="no">';

        $obj = new FRAMEtag($attributes);
        $tag = FRAMEtag::factory($name, $src, $scrolling);
        //$this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_frame($name, $src, $scrolling);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_FRAMESETtag() {

        $border = 0;
        $rows = 1;
        $cols = 2;
        $scrolling="yes";

        $attributes = array("border" => $border,
                            "framespacing" => "0",
                            "frameborder" => "no",
                            "rows" => $rows,
                            "cols" => $cols);

        $rendered = '<frameset border="0" framespacing="0" frameborder="no" rows="1" cols="2"></frameset>';

        $obj = new FRAMESETtag($attributes);
        $tag = FRAMESETtag::factory($rows, $cols, $border);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_frameset($rows, $cols, $border);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }


    function test_H1tag() {

        $content = 'foo bar';
        $rendered = '<h1>foo bar</h1>';

        $obj = new H1tag(NULL, $content);
        $obj->set_collapse();
        $tag = H1tag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_h1($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_H2tag() {

        $content = 'foo bar';
        $rendered = '<h2>foo bar</h2>';

        $obj = new H2tag(NULL, $content);
        $obj->set_collapse();
        $tag = H2tag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_h2($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_H3tag() {

        $content = 'foo bar';
        $rendered = '<h3>foo bar</h3>';

        $obj = new H3tag(NULL, $content);
        $obj->set_collapse();
        $tag = H3tag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_h3($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_H4tag() {

        $content = 'foo bar';
        $rendered = '<h4>foo bar</h4>';

        $obj = new H4tag(NULL, $content);
        $obj->set_collapse();
        $tag = H4tag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_h4($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_H5tag() {

        $content = 'foo bar';
        $rendered = '<h5>foo bar</h5>';

        $obj = new H5tag(NULL, $content);
        $obj->set_collapse();
        $tag = H5tag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_h5($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_H6tag() {

        $content = 'foo bar';
        $rendered = '<h6>foo bar</h6>';

        $obj = new H6tag(NULL, $content);
        $obj->set_collapse();
        $tag = H6tag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_h6($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_HEADtag() {

        $content = 'foo bar';
        $rendered = '<head>foo bar</head>';

        $obj = new HEADtag(NULL, $content);
        $tag = HEADtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_head($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_HRtag() {

        $rendered = '<hr>';

        $obj = new HRtag;
        $tag = HRtag::factory();
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_hr();
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_HTMLtag() {

        $content = 'foo bar';
        $rendered = '<html>foo bar</html>';

        $obj = new HTMLtag(NULL, $content);
        $tag = HTMLtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_html($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_Itag() {

        $content = 'foo bar';
        $rendered = '<i>foo bar</i>';

        $obj = new Itag(NULL, $content);
        $tag = Itag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_i($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_IFRAMEtag() {

        $src = "http://phptmllib.newsblob.com";
        $width = 10;
        $height = 100;
        $scrolling="no";
        $rendered = '<iframe src="http://phptmllib.newsblob.com" width="10" height="100" scrolling="no"></iframe>';

        $obj = new IFRAMEtag(array('src' => $src,
                                   'width' => $width,
                                   'height' => $height,
                                   'scrolling' => $scrolling));
        $tag = IFRAMEtag::factory($src, $width, $height, $scrolling);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_iframe($src, $width, $height, $scrolling);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_IMGtag() {

        $src = "http://phptmllib.newsblob.com/foo.jpg";
        $width = 10;
        $height = 100;
        $border = 1;
        $rendered = '<img src="http://phptmllib.newsblob.com/foo.jpg" border="1" alt="" height="100" width="10">';

        $obj = new IMGtag(array('src' => $src,
                                'border' => $border,
                                'alt' => '',
                                'height' => $height,
                                'width' => $width));
        $tag = IMGtag::factory($src, $width, $height, $border);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_img($src, $width, $height, $border);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

     function test_INPUTtag() {

         $type = 'text';
         $name = 'foo';
         $value = 'bar';

         $rendered = '<input type="text" name="foo" value="bar">';

         $obj = new INPUTtag(array('type' => $type,
                                   'name' => $name,
                                   'value' => $value));
        $tag = INPUTtag::factory($type, $name, $value);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_input($type, $name, $value);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

     function test_INStag() {

        $content = 'foo bar';
        $rendered = '<ins>foo bar</ins>';

        $obj = new INStag(NULL, $content);
        $tag = INStag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_ins($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_KBDtag() {

        $content = 'foo bar';
        $rendered = '<kbd>foo bar</kbd>';

        $obj = new KBDtag(NULL, $content);
        $tag = KBDtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_kbd($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_LABELtag() {

        $content = 'foo bar';
        $for = 'foo';
        $rendered = '<label for="foo">foo bar</label>';

        $obj = new LABELtag(array('for' => $for), $content);
        $tag = LABELtag::factory($for,$content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_label($for,$content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_LEGENDtag() {

        $content = 'foo bar';
        $rendered = '<legend>foo bar</legend>';

        $obj = new LEGENDtag(NULL, $content);
        $tag = LEGENDtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_legend($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_LItag() {

        $content = 'foo bar';
        $rendered = '<li>foo bar</li>';

        $obj = new LItag(NULL, $content);
        $tag = LItag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_li($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");

    }

    function test_LINKtag() {

        $href = "http://phphtmllib.newsblob.com";
        $rel = "stylesheet";
        $type = "text/css";
        $rendered = '<link href="http://phphtmllib.newsblob.com" rel="stylesheet" type="text/css">';

        $obj = new LINKtag(array('href' => $href,
                                 'rel' => $rel,
                                 'type' => $type));
        $tag = LINKtag::factory($href, $rel, $type);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_link($href, $rel, $type);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_MAPtag() {

        $name = "foo";
        $content = "bar blah";
        $rendered = '<map name="foo">bar blah</map>';

        $obj = new MAPtag(array('name' => $name), $content);
        $tag = MAPtag::factory($name, $content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_map($name, $content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_METAtag() {

        $name = "foo";
        $content = "bar blah";
        $equiv = 'floop';
        $rendered = '<meta content="bar blah" http-equiv="floop" name="foo">';

        $obj = new METAtag(array('content' => $content,
                                 'http-equiv' => $equiv,
                                 'name' => $name));
        $tag = METAtag::factory($content, $equiv, $name);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_meta($content, $equiv, $name);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_NOFRAMEStag() {

        $content = 'foo bar';
        $rendered = '<noframes>foo bar</noframes>';

        $obj = new NOFRAMEStag(NULL, $content);
        $tag = NOFRAMEStag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_noframes($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_NOSCRIPTtag() {

        $content = 'foo bar';
        $rendered = '<noscript>foo bar</noscript>';

        $obj = new NOSCRIPTtag(NULL, $content);
        $tag = NOSCRIPTtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_noscript($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_OBJECTtag() {

        $content = 'foo bar';
        $rendered = '<object>foo bar</object>';

        $obj = new OBJECTtag(NULL, $content);
        $tag = OBJECTtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_object($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_OLtag() {

        $content = 'foo bar';
        $rendered = "<ol><li>foo bar</li></ol>";

        $obj = new OLtag(NULL, $content);
        $obj->set_collapse();
        $tag = OLtag::factory($content);
        $tag->set_collapse();
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_ol($content);
        $helper->set_collapse();
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_OPTGROUPtag() {

        $content = 'foo bar';
        $label = 'mep';
        $rendered = '<optgroup label="mep">foo bar</optgroup>';

        $obj = new OPTGROUPtag(array('label' => $label), $content);
        $tag = OPTGROUPtag::factory($label, $content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_optgroup($label, $content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_OPTIONtag() {

        $content = 'foo bar';
        $value = 'mep';
        $rendered = '<option value="mep">foo bar</option>';

        $obj = new OPTIONtag(array('value' => $value), $content);
        $tag = OPTIONtag::factory($value, $content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_option($value, $content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_Ptag() {

        $content = 'foo bar';
        $rendered = '<p>foo bar</p>';

        $obj = new Ptag(NULL, $content);
        $tag = Ptag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_p($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_PARAMtag() {

        $name = 'foo';
        $value = 'bar';
        $rendered = '<param name="foo" value="bar"></param>';

        $obj = new PARAMtag(array('name' => $name,
                                  'value' => $value));
        $tag = PARAMtag::factory($name, $value);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_param($name, $value);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_PREtag() {

        $content = 'foo bar';
        $rendered = '<pre>foo bar</pre>';

        $obj = new PREtag(NULL, $content);
        $tag = PREtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_pre($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_Qtag() {

        $content = 'foo bar';
        $rendered = '<q>foo bar</q>';

        $obj = new Qtag(NULL, $content);
        $tag = Qtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_q($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_Stag() {

        $content = 'foo bar';
        $rendered = '<s>foo bar</s>';

        $obj = new Stag(NULL, $content);
        $tag = Stag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_SAMPtag() {

        $content = 'foo bar';
        $rendered = '<samp>foo bar</samp>';

        $obj = new SAMPtag(NULL, $content);
        $tag = SAMPtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_samp($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_SCRIPTtag() {

        $src = 'foo';        
        $rendered = '<script type="text/javascript" src="foo"></script>';

        $obj = new SCRIPTtag(array('type' => 'text/javascript',
                                   'src' => $src));
        $tag = SCRIPTtag::factory($src);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_script($src);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_SELECTtag() {

        $name = 'foo';        
        $value = 'bar';
        $rendered = '<select name="foo"><option value="bar">foo</option></select>';

        $obj = new SELECTtag(array('name' => $name),
                             OPTIONtag::factory($value, $name, TRUE));
        $obj->set_collapse();
        $tag = SELECTtag::factory($name, array($name => $value), $value);
        $tag->set_collapse();
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = form_select($name, array($name => $value), $value);
        $helper->set_collapse();
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_SMALLtag() {

        $content = 'foo bar';
        $rendered = '<small>foo bar</small>';

        $obj = new SMALLtag(NULL, $content);
        $tag = SMALLtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_small($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_SPANtag() {

        $content = 'foo bar';
        $class = 'foo';
        $rendered = '<span class="foo">foo bar</span>';

        $obj = new SPANtag(array('class' => $class), $content);
        $tag = SPANtag::factory($class, $content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_span($class,$content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_STRONGtag() {

        $content = 'foo bar';
        $rendered = '<strong>foo bar</strong>';

        $obj = new STRONGtag(NULL, $content);
        $tag = STRONGtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_strong($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_STYLEtag() {

        $content = 'foo bar';
        $type = 'foo';
        $rendered = '<style type="foo">foo bar</style>';

        $obj = new STYLEtag(array('type' => $type), $content);
        $tag = STYLEtag::factory($type, $content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_style($type, $content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_SUBtag() {

        $content = 'foo bar';
        $rendered = '<sub>foo bar</sub>';

        $obj = new SUBtag(NULL, $content);
        $tag = SUBtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_sub($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_SUPtag() {

        $content = 'foo bar';
        $rendered = '<sup>foo bar</sup>';

        $obj = new SUPtag(NULL, $content);
        $tag = SUPtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_sup($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_TABLEtag() {

        $width = "50%";
        $border = 1;
        $cellspacing = 2;
        $cellpadding = 25;

        $rendered = '<table width="50%" border="1" cellspacing="2" cellpadding="25"></table>';

        $obj = new TABLEtag(array('width' => $width,
                                  'border' => $border,
                                  'cellspacing' => $cellspacing,
                                  'cellpadding' => $cellpadding));
        $tag = TABLEtag::factory($width, $border, $cellspacing, $cellpadding);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_table($width, $border, $cellspacing, $cellpadding);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");


        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_TBODYtag() {

        $content = 'foo bar';
        $rendered = '<tbody>foo bar</tbody>';

        $obj = new TBODYtag(NULL, $content);
        $tag = TBODYtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_tbody($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }
    

    function test_TDtag() {

        $content = 'foo bar';
        $class = 'foo';
        $align = '';
        $rendered = '<td class="foo">foo bar</td>';

        $obj = new TDtag(array('class' => $class), $content);
        $tag = TDtag::factory($class, $align, $content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_td($class, $align, $content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_TEXTAREAtag() {

        $content = 'foo bar';
        $rows = 2;
        $cols = 22;
        $rendered = '<textarea rows="2" cols="22">foo bar</textarea>';

        $obj = new TEXTAREAtag(array('rows' => $rows,
                                     'cols' => $cols), $content);
        $tag = TEXTAREAtag::factory($rows, $cols, $content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_TFOOTtag() {

        $content = 'foo bar';
        $rendered = '<tfoot>foo bar</tfoot>';

        $obj = new TFOOTtag(NULL, $content);
        $tag = TFOOTtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_tfoot($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_THtag() {

        $content = 'foo bar';
        $rendered = '<th>foo bar</th>';

        $obj = new THtag(NULL, $content);
        $tag = THtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_th($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_THEADtag() {

        $content = 'foo bar';
        $rendered = '<thead>foo bar</thead>';

        $obj = new THEADtag(NULL, $content);
        $tag = THEADtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_thead($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_TITLEtag() {

        $content = 'foo bar';
        $rendered = '<title>foo bar</title>';

        $obj = new TITLEtag(NULL, $content);
        $tag = TITLEtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_title($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_TRtag() {

        $content = 'foo bar';
        $class = 'foo';
        $rendered = '<tr class="foo"><td>foo bar</td></tr>';

        $obj = new TRtag(array('class' => $class), $content);
        $obj->set_collapse();
        $tag = TRtag::factory($class, $content);
        $tag->set_collapse();
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_tr($class, $content);
        $helper->set_collapse();
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_TTtag() {

        $content = 'foo bar';
        $rendered = '<tt>foo bar</tt>';

        $obj = new TTtag(NULL, $content);
        $tag = TTtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_tt($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_Utag() {

        $content = 'foo bar';
        $rendered = '<u>foo bar</u>';

        $obj = new Utag(NULL, $content);
        $tag = Utag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_u($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_ULtag() {

        $content = 'foo bar';
        $rendered = '<ul><li>foo bar</li></ul>';

        $obj = new ULtag(NULL, $content);
        $obj->set_collapse();
        $tag = ULtag::factory($content);
        $tag->set_collapse();
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_ul($content);
        $helper->set_collapse();
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

    function test_VARtag() {

        $content = 'foo bar';
        $rendered = '<var>foo bar</var>';

        $obj = new VARtag(NULL, $content);
        $tag = VARtag::factory($content);
        $this->assertEquals($obj, $tag, "factory and constructor");

        $helper = html_var($content);
        $this->assertEquals($tag, $helper, "factory and helper weren't equal!");

        //string generation or render();
        $this->assertEquals($rendered, trim($obj->render()),
                            "Obj->render and rendered don't match");
    }

}

$suite = new PHPUnit_TestSuite('HTMLTagClassTest');
$result = PHPUnit::run($suite);
if (isset($_SERVER["PHP_SELF"]) && strlen($_SERVER["PHP_SELF"]) > 0) {
    echo $result->toHTML();
} else {
    echo $result->toString();
}
?>
