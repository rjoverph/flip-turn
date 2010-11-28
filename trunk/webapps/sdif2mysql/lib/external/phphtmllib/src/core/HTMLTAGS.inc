<?php

/**
 * This file contains all of the default
 * support html tags by phpHtmlLib.
 *
 * $Id: HTMLTAGS.inc 2843 2007-06-22 00:38:56Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 *
 */


/**
 * a tag class
 * @tutorial HTMLTagClass.cls#constructor
 * @package phpHtmlLib
 */
class Atag extends HTMLTagClass {
    protected $_tag = "a";
    protected $_flags = phphtmllib::_FLAGS_XML_NO_NEWLINE_AFTER_OPEN;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags &= ~phphtmllib::_NEWLINEAFTEROPENTAG;
    //}

    /**
     * build an href with content and attributes.
     *
     * @tutorial HTMLTagClass.cls#helper
     *
     * @author Walt A. Boring
     * @param   string the url to go to.
     * @param   string the visible link text.
     * @param   string the css class to use.
     * @param   string the target browser
     *                 window/frame for the url.
     * @param   string the title attribute
     * @return  Atag object.
     */
    public static function factory($url, $content, $class=NULL,
                                   $target=NULL, $title=NULL) {
        $attributes = array("href" => $url);
        if ($class) {
            $attributes["class"] = $class;
        }

        if ($target) {
            $attributes["target"] = $target;
        }

        if ($title) {
            $attributes["title"] = $title;
        }

        $a = new Atag($attributes, $content);
        $a->set_collapse();
        return $a;
    }

    /**
     * Create a mailto link
     *
     * @param   string $email - the email address
     *                            for the mailto
     *    @param   string $subject - the subject for
     *    the email
     *    @param   string $body - the body conent
     *    for the email
     *    @param   string $cc = the cc email address.
     */
    public static function mailto($email, $subject=NULL, $body=NULL, $cc=NULL) {
        $mailto = "mailto:".$email."?";
        if ( $subject ) {
            $mailto .= "subject=".rawurlencode($subject);
        }
        if ( $body ) {
            $mailto .= "&body=".rawurlencode($body);
        }
        if ( $cc ) {
            $mailto .= "&cc=".rawurlencode($cc);
        }

        return Atag::factory($mailto, $email);
    }

} // Atag


/**
 * abbr tag class
 * @package phpHtmlLib
 */
class ABBRtag extends HTMLTagClass {
    protected $_tag = "abbr";

    /**
     * build an <ABBR> tag with content.
     *
     *  This is to build an abbreviation.
     *  normally its just
     *  <abbr title="foo bar">foo</abbr>
     *
     * @param string - the title attribute
     * @param mixed - the content for the tag
     * @return  ABBRtag object.
     */
    public static function factory($title, $content) {
        return new ABBRtag(array("title"=>$title), $content);
    }
} // ABBRtag


/**
 * acronym tag class
 * @package phpHtmlLib
 */
class ACRONYMtag extends HTMLTagClass {
    protected $_tag = "acronym";

    /**
     * build an <ACRONYM> tag with content.
     *
     *  This is to build an abbreviation.
     *  normally its just
     *  <abbr title="foo bar">foo</abbr>
     *
     * @param string - the title attribute
     * @param mixed - the content for the tag
     * @return  ABBRtag object.
     */
    public static function factory($title, $content) {
        return new ACRONYMtag(array("title"=>$title), $content);
    }

} // ACRONYMtag


/**
 * address tag class
 * @package phpHtmlLib
 */
class ADDRESStag extends HTMLTagClass {
    protected $_tag = "address";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return ADDRESStag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new ADDRESStag;
        } else {
            $arg_list = func_get_args();
            return new ADDRESStag(NULL, $arg_list);
        }
    }

} // ADDRESStag

/**
 * applet tag class
 * @package phpHtmlLib
 *
 * @deprecated
 */
class APPLETtag extends HTMLTagClass {
    protected $_tag = "applet";
    protected $_flags = phphtmllib::_FLAGS_HTML_DEPRICATED;

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return APPLETtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new APPLETtag;
        } else {
            $arg_list = func_get_args();
            return new APPLETtag(NULL, $arg_list);
        }
    }

} // APPLETtag

/**
 * area tag class
 * @package phpHtmlLib
 */
class AREAtag extends HTMLTagClass {
    protected $_tag = "area";
    protected $_flags = phphtmllib::_FLAGS_XML_OPEN_ONLY;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags &= ~(phphtmllib::_CONTENTREQUIRED | phphtmllib::_CLOSETAGREQUIRED);
    //}

    /**
     * build an <AREA> tag with content.
     *
     * @param string - the href for the area
     * @param string - the coords value
     *                 circle x,y,radius
     *                 poly x1,y1,...xn,yn
     *                 left,top,right,bottom
     * @param string - the shape
     *                 DEFAULT: rect
     *                 circle, rect, poly, default
     * @param string - the alt text
     * @param string - the target
     *                 _blank, _parent, _self, _top
     * @param string - the title text
     *
     * @return  AREAtag object.
     */
    public static function factory($href, $coords, $shape="rect",
                                   $alt="", $target="", $title="") {
        $attributes = array("href" => $href,
                            "coords" => $coords,
                            "shape" => $shape);
        if ($alt != "") {
            $attributes["alt"] = $alt;
        }

        if ($target != "") {
            $attributes["target"] = $target;
        }

        if ($title != "") {
            $attributes["title"] = $title;
        }

        $tag = new AREAtag( $attributes );
        return $tag;
    }

} // AREAtag


/**
 * b tag class
 * @package phpHtmlLib
 */
class Btag extends HTMLTagClass {
    protected $_tag = "b";
    protected $_flags = phphtmllib::_FLAGS_XML_NO_NEWLINE_AFTER_OPEN;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags &= ~phphtmllib::_NEWLINEAFTEROPENTAG;
    //}

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return Btag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new Btag;
        } else {
            $arg_list = func_get_args();
            return new Btag(NULL, $arg_list);
        }
    }

} // Btag


/**
 * base tag class
 *
 * The base element specifies a base URL
 * for all the links in a page.
 *
 * @package phpHtmlLib
 */
class BASEtag extends HTMLTagClass {
    protected $_tag = "base";
    protected $_flags = phphtmllib::_FLAGS_XML_OPEN_ONLY;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags &= ~(phphtmllib::_CONTENTREQUIRED | phphtmllib::_CLOSETAGREQUIRED);
    //}


    /**
     * The factory method for this tag.
     *
     * @param string the href attribute
     * @return BASEtag object
     */
    public static function factory($href, $target='') {
        $attributes = array('href' => $href);
        if ($target != '') {
            $attributes['target'] = $target;
        }
        return new BASEtag($attributes);
    }

} // BASEtag


/**
 * bdo tag class
 *
 * The bdo element overrides the default
 * text direction.
 *
 * REQUIRED ATTRIBUTE
 *  dir : url
 * @package phpHtmlLib
 *
 */
class BDOtag extends HTMLTagClass {
    protected $_tag = "bdo";

    /**
     * The factory method for this tag.
     *
     * @param string the dir attribute
     * @return BDOtag object
     */
    public static function factory($dir) {
        $attributes = array('dir' => $dir);
        $num_args = func_num_args();
        if ($num_args<=1) {
            $obj = new BDOtag($attributes);
        } else {
            $arg_list = func_get_args();
            array_shift($arg_list);
            $obj = new BDOtag($attributes, $arg_list);
        }
        return $obj;
    }

} // BDOtag


/**
 * big tag class
 *
 * renders as 'bigger' text.
 * @package phpHtmlLib
 */
class BIGtag extends HTMLTagClass {
    protected $_tag = "big";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return BIGtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new BIGtag;
        } else {
            $arg_list = func_get_args();
            return new BIGtag(NULL, $arg_list);
        }
    }

} // BIGtag

/**
 * blockquote tag class
 *
 * This tag defines a long
 * quotation block
 *
 * @package phpHtmlLib
 */
class BLOCKQUOTEtag extends HTMLTagClass {
    protected $_tag = "blockquote";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return BLOCKQUOTEtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new BLOCKQUOTEtag;
        } else {
            $arg_list = func_get_args();
            return new BLOCKQUOTEtag(NULL, $arg_list);
        }
    }

} // BLOCKQUOTEtag

/**
 * body tag class
 *
 * Defines the documents' body.
 *
 * OPTIONAL ATTRIBUTES (all depricated)
 *   alink => color : DEPRICATED
 *   background => filename : DEPRICATED
 *   bgcolor => color : DEPRICATED
 *   link => color : DEPRICATED
 *   text => color : DEPRICATED
 *   vlink => color : DEPRICATED
 *
 * @package phpHtmlLib
 */
class BODYtag extends HTMLTagClass {
    protected $_tag = "body";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return BODYtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new BODYtag;
        } else {
            $arg_list = func_get_args();
            return new BODYtag(NULL, $arg_list);
        }
    }

} // BODYtag


/**
 * br tag class
 *
 * This tag inserts a single line break;
 *
 * @package phpHtmlLib
 */
class BRtag extends HTMLTagClass {
    protected $_tag = "br";
    protected $_flags = phphtmllib::_FLAGS_XML_OPEN_ONLY;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags &= ~(phphtmllib::_CONTENTREQUIRED | phphtmllib::_CLOSETAGREQUIRED);
    //}

    /**
     * The factory method.
     *
     * @param int - the number of
     *              br tags you want
     * @param string the class attribute
     * @return BRtag object or Container
     */
    public static function factory($num=1, $class=NULL) {
        if ($class !== null) {
            $attributes = array('class' => $class);
        } else {
            $attributes = NULL;
        }

        if ($num == 1){
            return new BRtag($attributes);
        } else if ($num > 1) {
            $obj = new Container;
            $obj->set_collapse();
            for ($i=0; $i<$num;$i++) {
                $obj->add( new BRtag($attributes) );
            }
            return $obj;
        } else if ($num <= 0) {
            return NULL;
        }
    }

} // BRtag


/**
 * button tag class
 *
 *  Defines a push button.
 *
 * @package phpHtmlLib
 */
class BUTTONtag extends HTMLTagClass {
    protected $_tag = "button";

    /**
     * The factory method for this tag.
     *
     * @param string the type attribute
     * @return BUTTONtag object
     */
    public static function factory($type='button') {
        $attributes = array('type' => $type);
        $num_args = func_num_args();
        if ($num_args<=1) {
            $obj = new BUTTONtag($attributes);
        } else {
            $arg_list = func_get_args();
            array_shift($arg_list);
            $obj = new BUTTONtag($attributes, $arg_list);
        }
        return $obj;
    }

} // BUTTONtag


/**
 * caption tag class
 *  This element defines a table caption.
 *  The <caption> tag must be inserted immediately
 *  after the <table> tag. You can specify only one
 *  caption per table.
 *
 * OPTIONAL ATTRIBUTES
 *  align  - top, bottom   DEPRICATED
 *
 * @package phpHtmlLib
 */
class CAPTIONtag extends HTMLTagClass {
    protected $_tag = "caption";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return CAPTIONtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new CAPTIONtag;
        } else {
            $arg_list = func_get_args();
            return new CAPTIONtag(NULL, $arg_list);
        }
    }

} // CAPTIONtag


/**
 * center tag class.
 * this is a depricated html tag, but
 * browsers still support it
 *
 * @deprecated
 * @package phpHtmlLib
 */
class CENTERtag extends HTMLTagClass {
    protected $_tag = "center";
    protected $_flags = phphtmllib::_FLAGS_HTML_DEPRICATED;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags |= phphtmllib::_DEPRICATED;
    //}

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return CENTERtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new CENTERtag;
        } else {
            $arg_list = func_get_args();
            return new CENTERtag(NULL, $arg_list);
        }
    }

} // CENTERtag


/**
 * cite tag class
 *
 * Defines a citation
 *
 * @package phpHtmlLib
 */
class CITEtag extends HTMLTagClass {
    protected $_tag = "cite";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return CITEtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new CITEtag;
        } else {
            $arg_list = func_get_args();
            return new CITEtag(NULL, $arg_list);
        }
    }

} // CITEtag


/**
 * code tag class
 *
 * Defines computer code text.
 *
 * @package phpHtmlLib
 */
class CODEtag extends HTMLTagClass {
    protected $_tag = "code";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return CODEtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new CODEtag;
        } else {
            $arg_list = func_get_args();
            return new CODEtag(NULL, $arg_list);
        }
    }

} // CODEtag


/**
 * col tag class
 *
 *  Defines the attribute values for
 *  one or more columns in a table. You
 *  can only use this element inside a
 *  colgroup.
 *
 * @package phpHtmlLib
 */
class COLtag extends HTMLTagClass {
    protected $_tag = "col";

    /**
     * The factory method.
     *
     * @param int the width attribute
     * @param string the align attribute
     * @param string the span attribute
     * @return COLtag object
     */
    public static function factory($width='', $align='', $span='') {
        $attributes = array();
        if ($width != '') {
            $attributes["width"] = $width;
        }
        if ($align != '') {
            $attributes["align"] = $align;
        }
        if ($span != '') {
            $attributes["span"] = $span;
        }
        $tag = new COLtag( $attributes );
        return $tag;
    }

} // COLtag


/**
 * colgroup tag class
 *
 * Defines groups of table columns.
 *  This element is only valid
 * inside the <table> tag.
 *
 * NOTE: The colgroup element is an empty
 *       element that contains attributes
 *       only. To create columns, you must
 *       specify td elements within a tr
 *       element.
 *
 * @package phpHtmlLib
 */
class COLGROUPtag extends HTMLTagClass {
    protected $_tag = "colgroup";

    /**
     * The factory method.
     *
     * @param array attributes
     * @return COLGROUPtag object
     */
    public static function factory($attributes=NULL) {
        $tag = new COLGROUPtag( $attributes );
        return $tag;
    }

} // COLGROUPtag



/**
 * dd tag class
 *
 *  The dd tag defines the description
 *  of the term in a definition list.
 *
 * @package phpHtmlLib
 */
class DDtag extends HTMLTagClass {
    protected $_tag = "dd";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return DDtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new DDtag;
        } else {
            $arg_list = func_get_args();
            return new DDtag(NULL, $arg_list);
        }
    }

} // DDtag


/**
 * del tag class
 *
 * Defines text that has been deleted in
 * a document.
 *
 * @package phpHtmlLib
 */
class DELtag extends HTMLTagClass {
    protected $_tag = "del";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return DELtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new DELtag;
        } else {
            $arg_list = func_get_args();
            return new DELtag(NULL, $arg_list);
        }
    }

} // DELtag

/**
 * dfn tag class
 *
 *  Defines a definition term
 *
 * @package phpHtmlLib
 */
class DFNtag extends HTMLTagClass {
    protected $_tag = "dfn";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return DFNtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new DFNtag;
        } else {
            $arg_list = func_get_args();
            return new DFNtag(NULL, $arg_list);
        }
    }

} // DFNtag


/**
 * dir tag class
 *
 * The <dir> tag defines the start of a
 *
 * DEPRECATED
 *
 * @package phpHtmlLib
 */
class DIRtag extends HTMLTagClass {
    protected $_tag = "dir";
    protected $_flags = phphtmllib::_FLAGS_HTML_DEPRICATED;


    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return DIRtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new DIRtag;
        } else {
            $arg_list = func_get_args();
            return new DIRtag(NULL, $arg_list);
        }
    }

} // DIRtag

/**
 * div tag class
 *
 * The div tag defines the start of a
 * division/section in a document.
 *
 * NOTE: Browsers usually place a line break
 *       before the <div> tag.
 *
 * @package phpHtmlLib
 */
class DIVtag extends HTMLTagClass {
    protected $_tag = "div";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return DIVtag object
     */
    public static function factory($class = "") {
        if ($class == "") {
            $attributes = NULL;
        } else {
            $attributes = array('class' => $class);
        }

        $arg_list = func_get_args();
        array_shift($arg_list);
        $obj = new DIVtag($attributes, $arg_list);
        return $obj;
    }

} // DIVtag


/**
 * dl tag class
 *
 * The dl tag defines the start of a
 * definition list.
 *
 * @package phpHtmlLib
 */
class DLtag extends HTMLTagClass {
    protected $_tag = "dl";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return DLtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new DLtag;
        } else {
            $arg_list = func_get_args();
            return new DLtag(NULL, $arg_list);
        }
    }

} // DLtag

/**
 * !doctype tag class
 * @package phpHtmlLib
 */
class DOCTYPEtag extends HTMLTagClass {
    protected $_tag = "!DOCTYPE";
    protected $_flags = phphtmllib::_FLAGS_XML_DOCTYPE;

    /*function _set_flags() {
    //    parent::_set_flags();
        $this->_flags &= ~(phphtmllib::_CONTENTREQUIRED | phphtmllib::_CLOSETAGREQUIRED);
        $this->_flags |= phphtmllib::_ALWAYS_UPPERCASE | phphtmllib::_NOFINISHSLASHXHTML;
    }*/

    /**
     * The factory method.
     *
     * @param string - the document element name (ie. 'HTML')
     * @param string - the source (ie. 'PUBLIC')
     * @param string - link 1 (ie. '-//W3C//DTD XHTML 1.0 Transitional//EN' )
     * @param string - link 2 (ie. 'DTD/xhtml1-transitional.dtd' )
     * @return DOCTYPEtag object
     */
    public static function factory($doc_element, $source="PUBLIC", $link1=NULL, $link2=NULL) {
        $attributes = array($doc_element, $source);

        if ($link1 != NULL) {
            array_push($attributes,  "\"". $link1."\"");
        }
        if ($link2 != NULL) {
            array_push($attributes,  "\"". $link2."\"");
        }

        return new DOCTYPEtag( $attributes );
    }

} //!DOCTYPEtag

/**
 * dt tag class
 *
 * The dt tag defines the start of a
 * definition list.
 *
 * @package phpHtmlLib
 */
class DTtag extends HTMLTagClass {
    protected $_tag = "dt";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return DTtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new DTtag;
        } else {
            $arg_list = func_get_args();
            return new DTtag(NULL, $arg_list);
        }
    }

} // DLtag


/**
 * em tag class
 *
 *  Renders as emphasized text
 *
 * @package phpHtmlLib
 */
class EMtag extends HTMLTagClass {
    protected $_tag = "em";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return DTtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new EMtag;
        } else {
            $arg_list = func_get_args();
            return new EMtag(NULL, $arg_list);
        }
    }

} // EMtag

/**
 * embed tag class
 *
 *  Renders as emphasized text
 *
 * @package phpHtmlLib
 */
class EMBEDtag extends HTMLTagClass {
    protected $_tag = "embed";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return EMBEDtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new EMBEDtag;
        } else {
            $arg_list = func_get_args();
            return new EMBEDtag(NULL, $arg_list);
        }
    }

} // EMtag


/**
 * fieldset tag class
 *
 *  The fieldset element draws a box
 *  around the text and other elements
 *  it contains.
 *
 * @package phpHtmlLib
 */
class FIELDSETtag extends HTMLTagClass {
    protected $_tag = "fieldset";

    /**
     * The factory method for this tag.
     *
     * @param string the type attribute
     * @return BUTTONtag object
     */
    public static function factory($legend="") {
        $arg_list = func_get_args();

        if (!empty($legend)) {
            if (!is_object($legend)) {
                $legend = LEGENDtag::factory($legend);
            }

            array_shift($arg_list);
            array_unshift($arg_list, $legend);
            $obj = new FIELDSETtag(NULL, $arg_list);
        } else {
            array_shift($arg_list);
            $obj = new FIELDSETtag(NULL, $arg_list);
        }
        return $obj;
    }

} // FIELDSETtag



/**
 * font tag class
 *
 * @deprecated use styles instead
 *
 * @package phpHtmlLib
 */
class FONTtag extends HTMLTagClass {
    protected $_tag = "font";
    protected $_flags = phphtmllib::_FLAGS_HTML_DEPRICATED;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags |= phphtmllib::_DEPRICATED;
    //}

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return FONTtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new FONTtag;
        } else {
            $arg_list = func_get_args();
            return new FONTtag(NULL, $arg_list);
        }
    }

} // FONTtag



/**
 * form tag
 *
 * The form element creates a form
 * for user input.
 *
 * REQUIRED ATTRIBUTES
 *   action : url
 *            Specifies where to send the
 *            data when the user pushes the
 *            submit button in a form.
 *
 * @package phpHtmlLib
 */
class FORMtag extends HTMLTagClass {
    protected $_tag = "form";
    //protected $_xhtml_strict_attributes = array("name", "target");

    /**
     * The factory method.
     *
     * @param string  name attribute of the form tag.
     * @param string  the form action.
     * @param string  form method
     * @param string  any extra name='value' attributes for
     *                                the form tag.
     * @return FORMtag object
     */
    public static function factory($name, $action, $method="GET", $attributes=array()) {
        $attribs = array("name" => $name, "action" => $action,
                         "method" => $method);
        $attributes = array_merge( $attribs, $attributes);
        return new FORMtag( $attributes );
    }

    /**
     * This method is used to set the name attribute
     *
     * @param string the name attribute
     */
    public function set_name($name) {
        $this->set_tag_attribute('name', $name);
    }

    /**
     * This method is used to get the name attribute
     *
     * @return string the name attribute
     */
    public function get_name() {
        return $this->get_tag_attribute('name');
    }


    /**
     * This method is used to set the action attribute
     *
     * @param string the action attribute
     */
    public function set_action($action) {
        $this->set_tag_attribute('action', $action);
    }

    /**
     * This method is used to set the action attribute
     *
     * @return string the action attribute
     */
    public function get_action() {
        return $this->get_tag_attribute('action');
    }

    /**
     * This method is used to set the method attribute
     *
     * @param string the method attribute
     */
    public function set_method($method) {
        if ( strcasecmp($method,"GET") !=0 && strcasecmp($method,"POST") !=0 ) {
            user_error("FORMtag::set_method() - INVALID Form method ".$method);
        } else {
            $this->set_tag_attribute('method', $method);
        }
    }

    /**
     * This method is used to set the method attribute
     *
     * @return string the method attribute
     */
    public function get_method() {
        return $this->get_tag_attribute('method');
    }

    /**
     * This method is used to set the onsubmit attribute
     *
     * @param string the onsubmit attribute
     */
    public function set_onsubmit($onsubmit) {
        $this->set_tag_attribute('onsubmit', $onsubmit);
    }

    /**
     * This method is used to set the onsubmit attribute
     *
     * @return string the onsubmit attribute
     */
    public function get_onsubmit() {
        return $this->get_tag_attribute('onsubmit');
    }
} // FORMtag



/**
 * frame tag class
 *
 * Defines a sub window (a frame).
 *
 * @package phpHtmlLib
 */
class FRAMEtag extends HTMLTagClass {
    protected $_tag = "frame";
    protected $_flags = phphtmllib::_FLAGS_XML_OPEN_ONLY;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags &= ~(phphtmllib::_CONTENTREQUIRED | phphtmllib::_CLOSETAGREQUIRED);
    //}

    /**
     * The factory method.
     * NOTE: this comes with the following attribtes
     *      defaulted to:
     *      marginwidth = "0"
     *      marginheight = "0"
     *      noresize
     *      frameborder = "0"
     *
     * @param string the "name" attribute
     * @param string the "src" atribute
     * @param string the "scrolling" attribute
     * @return FRAMEtag object
     */
    public static function factory($name, $src, $scrolling="no") {
        $attributes = array("name" => $name,
                            "src" => $src,
                            "scrolling" => $scrolling,
                            "marginwidth" => "0",
                            "marginheight" => "0",
                            "noresize",
                            "frameborder" => "no");
        return new FRAMEtag( $attributes );
    }

} // FRAMEtag

/**
 * frameset tag class
 *
 * The frameset element defines a
 * frameset.
 *
 * @package phpHtmlLib
 */
class FRAMESETtag extends HTMLTagClass {
    protected $_tag = "frameset";

    /**
     * The factory method.
     *
     * NOTE: It comes with the following attributes
     *       defaulted to:
     *       framespacing = "0"
     *       frameborder = "no"
     *
     * @param string the rows attribute
     * @param string the cols attribute
     * @param int the border attribute
     * @return FRAMESETtag object
     */
    public static function factory($rows, $cols, $border="0" ) {
        $attributes = array("border" => $border,
                            "framespacing" => "0",
                            "frameborder" => "no",
                            "rows" => $rows,
                            "cols" => $cols);
        return new FRAMESETtag( $attributes );
    }

} // FRAMESETtag


/**
 * h1 tag class
 *
 * Defines a header
 *
 * @package phpHtmlLib
 */
class H1tag extends HTMLTagClass {
    protected $_tag = "h1";
    protected $_flags = phphtmllib::_FLAGS_XML_NO_NEWLINE_AFTER_OPEN;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags &= ~phphtmllib::_NEWLINEAFTEROPENTAG;
    //}

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return H1tag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            $obj = new H1tag;
        } else {
            $arg_list = func_get_args();
            $obj = new H1tag(NULL, $arg_list);
        }
        $obj->set_collapse();
        return $obj;
    }
} // H1tag


/**
 * h2 tag class
 *
 * Defines a header
 *
 * @package phpHtmlLib
 */
class H2tag extends HTMLTagClass {
    protected $_tag = "h2";
    protected $_flags = phphtmllib::_FLAGS_XML_NO_NEWLINE_AFTER_OPEN;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags &= ~phphtmllib::_NEWLINEAFTEROPENTAG;
    //}

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return H2tag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            $obj = new H2tag;
        } else {
            $arg_list = func_get_args();
            $obj = new H2tag(NULL, $arg_list);
        }
        $obj->set_collapse();
        return $obj;
    }
} // H2tag


/**
 * h3 tag class
 *
 * Defines a header
 *
 * @package phpHtmlLib
 */
class H3tag extends HTMLTagClass {
    protected $_tag = "h3";
    protected $_flags = phphtmllib::_FLAGS_XML_NO_NEWLINE_AFTER_OPEN;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags &= ~phphtmllib::_NEWLINEAFTEROPENTAG;
    //}

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return H3tag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            $obj = new H3tag;
        } else {
            $arg_list = func_get_args();
            $obj = new H3tag(NULL, $arg_list);
        }
        $obj->set_collapse();
        return $obj;
    }
} // H3tag


/**
 * h4 tag class
 *
 * Defines a header
 *
 * @package phpHtmlLib
 */
class H4tag extends HTMLTagClass {
    protected $_tag = "h4";
    protected $_flags = phphtmllib::_FLAGS_XML_NO_NEWLINE_AFTER_OPEN;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags &= ~phphtmllib::_NEWLINEAFTEROPENTAG;
    //}
    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return H4tag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            $obj = new H4tag;
        } else {
            $arg_list = func_get_args();
            $obj = new H4tag(NULL, $arg_list);
        }
        $obj->set_collapse();
        return $obj;
    }
} // H4tag


/**
 * h5 tag class
 *
 * Defines a header
 *
 * @package phpHtmlLib
 */
class H5tag extends HTMLTagClass {
    protected $_tag = "h5";
    protected $_flags = phphtmllib::_FLAGS_XML_NO_NEWLINE_AFTER_OPEN;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags &= ~phphtmllib::_NEWLINEAFTEROPENTAG;
    //}

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return H5tag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            $obj = new H5tag;
        } else {
            $arg_list = func_get_args();
            $obj = new H5tag(NULL, $arg_list);
        }
        $obj->set_collapse();
        return $obj;
    }
} // H5tag


/**
 * h6 tag class
 *
 * Defines a header
 *
 * @package phpHtmlLib
 */
class H6tag extends HTMLTagClass {
    protected $_tag = "h6";
    protected $_flags = phphtmllib::_FLAGS_XML_NO_NEWLINE_AFTER_OPEN;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags &= ~phphtmllib::_NEWLINEAFTEROPENTAG;
    //}

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return H6tag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            $obj = new H6tag;
        } else {
            $arg_list = func_get_args();
            $obj = new H6tag(NULL, $arg_list);
        }
        $obj->set_collapse();
        return $obj;
    }
} //H6tag


/**
 *  head tag class
 *
 * The head element can contain information
 * about the document.
 *
 * @package phpHtmlLib
 */
class HEADtag extends HTMLTagClass {
    protected $_tag = "head";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return HEADtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new HEADtag;
        } else {
            $arg_list = func_get_args();
            return new HEADtag(NULL, $arg_list);
        }
    }
} // HEADtag



/**
 * hr tag class
 *
 * inserts a horizontal rule.
 *
 * NOTE: All the "presentation attributes"
 *       of the hr element have been
 *       deprecated, in favor of style sheets.
 *
 * @package phpHtmlLib
 */
class HRtag extends HTMLTagClass {
    protected $_tag = "hr";
    protected $_flags = phphtmllib::_FLAGS_XML_OPEN_ONLY;

    /*function _set_flags() {
    //    parent::_set_flags();
        $this->_flags &= ~(phphtmllib::_NEWLINEAFTEROPENTAG | phphtmllib::_CONTENTREQUIRED | phphtmllib::_CLOSETAGREQUIRED);
    }*/

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return HRtag object
     */
    public static function factory() {
        return new HRtag;
    }
} // HRtag



/**
 * html tag class.
 *
 * @package phpHtmlLib
 */
class HTMLtag extends HTMLTagClass {
    protected $_tag = "html";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return HTMLtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new HTMLtag;
        } else {
            $arg_list = func_get_args();
            return new HTMLtag(NULL, $arg_list);
        }
    }
} // HTMLtag


/**
 * i tag class
 *
 * Renders as italic text
 *
 * @package phpHtmlLib
 */
class Itag extends HTMLTagClass {
    protected $_tag = "i";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return Itag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new Itag;
        } else {
            $arg_list = func_get_args();
            return new Itag(NULL, $arg_list);
        }
    }
} // Itag


/**
 * iframe tag class
 *
 * The iframe element creates an inline
 * frame that contains another document.
 *
 * @package phpHtmlLib
 */
class IFRAMEtag extends HTMLTagClass {
    protected $_tag = "iframe";

    /**
     * The factory method.
     *
     * @param string the src attribute
     * @param string the width attribute
     * @param string the height attribute
     * @param string the scrolling attribute
     * @return Itag object
     */
    public static function factory($src, $width="", $height="", $scrolling="") {
        $attributes = array("src" => $src);
        if ($width != "") {
            $attributes["width"] = $width;
        }
        if ($height != "") {
            $attributes["height"] = $height;
        }
        if ($width != "") {
            $attributes["scrolling"] = $scrolling;
        }
        return new IFRAMEtag( $attributes );
    }
} // IFRAMEtag


/**
 * img tag class
 *
 * This element inserts an image.
 *
 * REQUIRED ATTRIBUTES
 *  src : url
 *        The address of the image you want
 *        to insert
 *  alt : text
 *        A short description of the image.
 *        Use it for text-only browsers
 *
 * @package phpHtmlLib
 */
class IMGtag extends HTMLTagClass {
    protected $_tag = "img";
    //protected $_xhtml_strict_attributes = array("border");
    protected $_flags = phphtmllib::_FLAGS_XML_OPEN_ONLY;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags &= ~(phphtmllib::_CONTENTREQUIRED | phphtmllib::_CLOSETAGREQUIRED);
    //}


    /**
     * The factory method.
     *
     * @param   string image src
     * @param   int    width of the image.
     * @param   int    height of the image
     * @param   int    border flag.
     * @param   string alt tag for the image
     * @param   string the image map name
     * @param   string the align attribute
     * @param   string the full path
     *                 to the filename.  If this is set
     *                 and $width == '' and $height == ''
     *                 then we will try and determine the
     *                 size attributes of the image.
     * @return IMGtag object
     */
    public static function factory($image, $width='', $height='', $border=0,
                                   $alt="", $usemap=NULL, $title=NULL,
                                   $align=NULL, $filename=NULL) {

        $attributes = array( "src" => $image,
                             "border" => $border,
                             "alt" => $alt);

        if ($height != '') {
            $attributes["height"] = $height;
        }
        if ($width != '') {
            $attributes["width"] = $width;
        }

        if ($height === '' && $width === ''
            && $filename !== NULL) {

            $img = getimagesize($filename);
            if ($img) {
                $attributes['width'] = $img[0];
                $attributes['height'] = $img[1];
            }
        }

        //only add usemap entry if its not NULL
        if ($usemap) {
            $attributes["usemap"] = $usemap;
        }

        if ($title) {
            $attributes["title"] = $title;
        }

        if ($align != NULL) {
            $attributes["align"] = $align;
        }
        return new IMGtag( $attributes );
    }

    /**
     * This method is a wrapper for IMGtag::factory() that
     * allows us to automatically set the width, and
     * height based upon the discovered image attributes.
     *
     * NOTE: This assumes the $image includes a path which
     *       is on the local filesystem based off of the
     *       DOCUMENT_ROOT
     *
     *       So if DOCUMENT_ROOT = /www/mysite.com/html
     *       and $image = '/images/foo.jpg'
     *
     *       getimagesize will look in
     *       $_SERVER['DOCUMENT_ROOT'].$image
     *
     * @param   string image src
     * @param   int    border flag.
     * @param   string alt tag for the image
     * @param   string the image map name
     * @param   string the align attribute
     * @return IMGtag object
     */
    public static function factory_local($image, $border=0, $alt='', $usemap=NULL,
                                         $title=NULL, $align=NULL) {
        return IMGtag::factory($image, '', '', $border, $alt, $usemap,
                               $title, $align, $_SERVER['DOCUMENT_ROOT'].$image);
    }

} // IMGtag

/**
 * input tag
 *
 * The <input> tag defines the start of an input
 * field where the user can enter data.
 *
 * @package phpHtmlLib
 */
class INPUTtag extends HTMLTagClass {
    protected $_tag = "input";
    protected $_flags = phphtmllib::_FLAGS_XML_OPEN_ONLY;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags &= ~(phphtmllib::_CONTENTREQUIRED | phphtmllib::_CLOSETAGREQUIRED);
    //}


    /**
     * The factory method.
     *
     * NOTE: This wrapper automatically
     *       calls htmlspecialchars() on
     *       the value attribute's data.
     *
     * @param string - the type attribute
     * @param string - the name attribute
     * @param string - the value attribute
     * @param array  - any other name=>value attributes
     *                 for the tag
     * @return INPUTtag object
     */
    public static function factory($type, $name, $value='', $attributes=array()) {
        $attrib = array( "type" => $type,"name" => $name,"value" => $value);
        $attributes = array_merge( $attrib, $attributes );
        return new INPUTtag( $attributes );
    }


    /**
     * add a single attribute (name="value")
     *
     * We override this to prevent the value from
     * being injected javascript.
     *
     * {@source }
     *
     * @param   string  $name   attribute name
     * @param   mixed   $value  the value.
     * @return none
     */
    function set_tag_attribute( $name, $value=NULL ) {
        if (stristr('value', $name)) {
            $value = htmlspecialchars($value, ENT_QUOTES);
        }
        $this->_attributes[$name] = $value;
    }

    /**
     * add multiple attributes (name="value")
     *
     * We override this to prevent the value from
     * being injected javascript.
     *
     * {@source }
     *
     * @param   array   $attributes Associative array of name="value" pairs of
     *                              tag atributes.
     *                              ie array("border"=>"0", "class"=>"hover");
     * @return none
     */
    function set_tag_attributes( $attributes=array() ) {
        if (!isset($this->_attributes)) {
            $this->_attributes = array();
        }

        if (isset($attributes['value'])) {
            $attributes['value'] = htmlspecialchars($attributes['value'], ENT_QUOTES);
        }

        $this->_attributes = array_merge($this->_attributes, $attributes);
    }

} // INPUTtag

/**
 * ins tag class
 *
 * Defines inserted text.
 *
 * @package phpHtmlLib
 */
class INStag extends HTMLTagClass {
    protected $_tag = "ins";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return INStag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new INStag;
        } else {
            $arg_list = func_get_args();
            return new INStag(NULL, $arg_list);
        }
    }
} // INStag

/**
 * kbd tag class
 *
 * Defines keyboard text
 *
 * @package phpHtmlLib
 */
class KBDtag extends HTMLTagClass {
    protected $_tag = "kbd";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return KBDtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new KBDtag;
        } else {
            $arg_list = func_get_args();
            return new KBDtag(NULL, $arg_list);
        }
    }
} // KBDtag


/**
 * label tag class
 *
 * Defines a label to a control. If you
 * click the text within the label element,
 * it is supposed to toggle the control.
 *
 * NOTE: The "for" attribute binds a label
 *       to another element. Set the value
 *       of the "for" attribute equal to the
 *       value of the "id" attribute of the
 *       related element.
 *
 * @package phpHtmlLib
 */
class LABELtag extends HTMLTagClass {
    protected $_tag = "label";

    /**
     * The factory method.
     *
     * @param   string - the id of the form
     *                   element to tie this
     *                   label to.
     * @return LABELtag object
     */
    public static function factory($for="") {
        $attributes = array('for' => $for);
        $num_args = func_num_args();
        if ($num_args<=1) {
            $obj = new LABELtag($attributes);
        } else {
            $arg_list = func_get_args();
            array_shift($arg_list);
            $obj = new LABELtag($attributes, $arg_list);
        }
        return $obj;
    }
} // LABELtag


/**
 * legend tag class
 *
 * The legend element defines a caption
 * for a fieldset.
 *
 * @package phpHtmlLib
 */
class LEGENDtag extends HTMLTagClass {
    protected $_tag = "legend";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return LEGENDtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new LEGENDtag;
        } else {
            $arg_list = func_get_args();
            return new LEGENDtag(NULL, $arg_list);
        }
    }

} // LEGENDtag


/**
 * li tag class
 *
 * The li tag defines the start of a list
 * item. The li tag is used in both ordered
 * ol and unordered lists ul.
 *
 * OPTIONAL ATTRIBUTES
 *   type : 1, A, a, I, i  DEPRICATED
 *
 * @package phpHtmlLib
 */
class LItag extends HTMLTagClass {
    protected $_tag = "li";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return LItag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new LItag;
        } else {
            $arg_list = func_get_args();
            return new LItag(NULL, $arg_list);
        }
    }
} // LItag



/**
 * link tag class
 *
 * This element defines the relationship between
 * two linked documents.
 *
 * NOTE:  This element goes only in the head section,
 *        but it can appear any number of times.
 *
 * @package phpHtmlLib
 */
class LINKtag extends HTMLTagClass {
    protected $_tag = "link";
    protected $_flags = phphtmllib::_FLAGS_XML_OPEN_ONLY;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags &= ~(phphtmllib::_CONTENTREQUIRED | phphtmllib::_CLOSETAGREQUIRED);
    //}

    /**
     * The factory method.
     *
     * @param   string - the href link
     * @param   string - the rel attribute
     * @param   string - the type of content.
     * @return LINKtag object
     */
    public static function factory($href, $rel, $type) {
        return new LINKtag( array("href" => $href,
                                  "rel" => $rel,
                                  "type" => $type));
    }
} // LINKtag



/**
 * map tag class
 *
 *  Defines an image map. An image map is an
 *  image with clickable regions.
 *
 * @package phpHtmlLib
 */
class MAPtag extends HTMLTagClass {
    protected $_tag = "map";

    /**
     * The factory method.
     *
     * @param string the name attribute
     * @param   mixed n number of arguments
     *                as content for the tag.
     * @return MAPtag object
     */
    public static function factory($name) {
        $attributes = array('name' => $name);
        $num_args = func_num_args();
        if ($num_args<=1) {
            $obj = new MAPtag($attributes);
        } else {
            $arg_list = func_get_args();
            array_shift($arg_list);
            $obj = new MAPtag($attributes, $arg_list);
        }
        return $obj;
    }
} // MAPtag

/**
 * meta tag class
 *
 * The meta element provides meta-information
 * about your page, such as descriptions and
 * keywords for search engines.
 *
 * NOTE: The meta tag always goes inside the head element.
 *
 * REQUIRED ATTRIBUTES
 *  content : text
 *            Sets meta information to be associated
 *            with http-equiv or name.
 *
 * @package phpHtmlLib
 */
class METAtag extends HTMLTagClass {
    protected $_tag = "meta";
    protected $_flags = phphtmllib::_FLAGS_XML_OPEN_ONLY;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags &= ~(phphtmllib::_CONTENTREQUIRED | phphtmllib::_CLOSETAGREQUIRED);
    //}

     /**
     * The factory method.
     *
     * @param string the name attribute
     * @param   mixed n number of arguments
     *                as content for the tag.
     * @return METAtag object
     */
    public static function factory($content, $http_equiv="", $name="") {
        $attributes = array("content" => $content);

        if ($http_equiv != "") {
            $attributes["http-equiv"] = $http_equiv;
        }

        if ($name != "") {
            $attributes["name"] = $name;
        }

        return new METAtag( $attributes );
    }


    /**
     * This is a helper method to build a proper META
     * tag that includes refreshing to a url
     *
     * @param string $url full http url to go to
     * @param int $time how many seconds until refresh
     */
    public static function factory_refresh($url, $time) {
        return self::factory($time.';url='.$url, 'refresh');
    }
} // METAtag


/**
 * nobr tag class
 *
 * NOTE: This tag doesn't really
 *       exist in the HTML spec
 *       NOT WISE TO USE IT.
 * @deprecated
 * @package phpHtmlLib
 */
class NOBRtag extends HTMLTagClass {
    protected $_tag = "nobr";
    protected $_flags = phphtmllib::_FLAGS_HTML_DEPRICATED;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags |= phphtmllib::_DEPRICATED;
    //}
} // NOBRtag


/**
 * noframes tag class
 *
 *  The noframes element displays text for
 *  browsers that do not handle frames. The
 *  noframes element goes inside the frameset
 *  element.
 *
 * @package phpHtmlLib
 */
class NOFRAMEStag extends HTMLTagClass {
    protected $_tag = "noframes";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return NOFRAMEStag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new NOFRAMEStag;
        } else {
            $arg_list = func_get_args();
            return new NOFRAMEStag(NULL, $arg_list);
        }
    }
} // NOFRAMEtag



/**
 * noscript tag class
 *
 *  The noscript element is used to define
 *  an alternate content (text) if a script
 *  is NOT executed.
 *
 *  NO ATTRIBUTES
 *
 * @package phpHtmlLib
 */
class NOSCRIPTtag extends HTMLTagClass {
    protected $_tag = "noscript";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return NOSCRIPTtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new NOSCRIPTtag;
        } else {
            $arg_list = func_get_args();
            return new NOSCRIPTtag(NULL, $arg_list);
        }
    }
} // NOSCRIPTtag

/**
 * object tag class
 *
 * Defines an embedded object. Use this element
 * to insert  multimedia into your page.
 *
 * @package phpHtmlLib
 */
class OBJECTtag extends HTMLTagClass {
    protected $_tag = "object";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return OBJECTtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new OBJECTtag;
        } else {
            $arg_list = func_get_args();
            return new OBJECTtag(NULL, $arg_list);
        }
    }
} // OBJECTtag

/**
 * ol tag class
 *
 * The ol tag defines the start of an ordered list.
 *
 * OPTIONAL ATTRIBUTES
 *   type : 1,A,a,I,i  DEPRICATED DO NOT USE
 *
 * @package phpHtmlLib
 */
class OLtag extends HTMLTagClass {
    protected $_tag = "ol";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return OLtag object
     */
    public static function factory() {
        //we need to make sure all arguments
        //pass through the add method
        //because add automagically converts
        //strings to LItag objects.
        $tag = new OLtag;
        $num_args = func_num_args();
        if ($num_args >= 1) {
            $arg_list = func_get_args();
            foreach( $arg_list as $arg) {
                $tag->add($arg);
            }
        }

        return $tag;
    }


    /**
     * add content onto content stack
     * adds content to tag as a FIFO.
     * You can have n number of parameters.
     * each one will get added in succession to the content.
     *
     * we override this from the parent so we can auto detect if
     * the user is adding raw strings instead of objects.
     * If they are trying to add raw strings, then we wrap that in
     * an LItag object, since you can't add anything other then an <LI>
     * @param   mixed   $content - either string, or tag object.
     * @access  public
     */
    function add() {
        $args = func_get_args();

        foreach( $args as $content) {

            if (!is_object($content) || (@$content->get_tag_name() != "li") ) {
                //$content is raw (string)
                //lets wrap it in a <LI> object
                $li = new LItag;
                $li->add( $content );
                parent::add( $li );
            } else {
                //looks like this is some object
                //let the user do it.
                //should we only let them push a
                //<LI> object?
                parent::add( $content );
            }
        }
    }

} // OLtag


/**
 * optgroup tag class
 *
 *  Defines an option group. This element allows
 *  you to group choices. When you have a long list
 *  of options, groups of related choices are easier
 *  to handle.
 *
 * @package phpHtmlLib
 */
class OPTGROUPtag extends HTMLTagClass {
    protected $_tag = "optgroup";

    /**
     * The factory method.
     *
     * @param string label attribute
     * @param mixed n number of arguments
     *                as content for the tag.
     * @return OPTGROUPtag object
     */
    public static function factory($label) {
        $attributes = array('label' => $label);
        $num_args = func_num_args();
        if ($num_args<=1) {
            $obj = new OPTGROUPtag($attributes);
        } else {
            $arg_list = func_get_args();
            array_shift($arg_list);
            $obj = new OPTGROUPtag($attributes, $arg_list);
        }
        return $obj;
    }
} // OPTGROUPtag


/**
 * option tag class
 *
 *  The option element defines an option in the
 *  drop-down box.
 *
 * @package phpHtmlLib
 */
class OPTIONtag extends HTMLTagClass {
    protected $_tag = "option";
    protected $_flags = phphtmllib::_FLAGS_XML_NO_NEWLINE_AFTER_OPEN;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags &= ~phphtmllib::_NEWLINEAFTEROPENTAG;
    //}

    /**
     * The factory method.
     *
     * @param string value attribute
     * @param string the content
     * @param boolean SELECTED? or not
     * @return OPTIONtag object
     */
    public static function factory($value, $content, $selected=FALSE) {
        $attributes = array('value' => $value);

        if ($selected) {
            if ($GLOBALS["HTML_RENDER_TYPE"] == phphtmllib::HTML) {
                $attributes[] = 'SELECTED';
            } else {
                $attributes['selected'] = 'selected';
            }
        }
        return $tag = new OPTIONtag( $attributes, $content );
    }

} // OPTIONtag



/**
 * p tag class
 *
 * The p tag defines a paragraph.
 *
 * OPTIONAL ATTRIBUTES
 *  align : left, center, right DEPRICATED DO NOT USE
 *
 * @package phpHtmlLib
 */
class Ptag extends HTMLTagClass {
    protected $_tag = "p";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return Ptag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new Ptag;
        } else {
            $arg_list = func_get_args();
            return new Ptag(NULL, $arg_list);
        }
    }
} // Ptag


/**
 * param tag class
 *
 *  The param element allows you to specify
 *  the run-time settings for an object inserted
 *  into HTML documents.
 *
 *  REQUIRED ATTRIBUTES
 *   name : the name of the param
 *
 * @package phpHtmlLib
 */
class PARAMtag extends HTMLTagClass {
    protected $_tag = "param";

    /**
     * The factory method.
     *
     * @param string name attribute
     * @param string value attribute
     * @return PARAMtag object
     */
    public static function factory($name, $value="") {
        $attributes = array("name" => $name);
        if ($value != "") {
            $attributes["value"] = $value;
        }
        return new PARAMtag( $attributes );
    }
} // PARAMtag

/**
 * pre tag class
 *
 * The pre element defines preformatted text.
 * The text enclosed in the pre element usually
 * preserves spaces and line breaks. The text
 * renders in a fixed-pitch font.
 *
 * @package phpHtmlLib
 */
class PREtag extends HTMLTagClass {
    protected $_tag = "pre";

    function _set_flags() {
    //    parent::_set_flags();
        $this->_flags &= ~phphtmllib::_INDENT;
    }

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return PREtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new PREtag;
        } else {
            $arg_list = func_get_args();
            return new PREtag(NULL, $arg_list);
        }
    }
} // PREtag



/**
 * q tag class
 *
 *  The q tag defines the start of a short quotation.
 *
 *  NOTE: The q element does not render as anything
 *        special, you have to use styles to format
 *        the text.
 *
 * @package phpHtmlLib
 */
class Qtag extends HTMLTagClass {
    protected $_tag = "q";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return Qtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new Qtag;
        } else {
            $arg_list = func_get_args();
            return new Qtag(NULL, $arg_list);
        }
    }
} // Qtag


/**
 * S tag class
 *
 * @deprecated USE del instead
 *
 * @package phpHtmlLib
 */
class Stag extends HTMLTagClass {
    protected $_tag = "s";
    protected $_flags = phphtmllib::_FLAGS_HTML_DEPRICATED;

    //function _set_flags() {
    //    parent::_set_flags();
    //    $this->_flags |= phphtmllib::_DEPRICATED;
    //}

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return Stag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new Stag;
        } else {
            $arg_list = func_get_args();
            return new Stag(NULL, $arg_list);
        }
    }
} // Stag


/**
 * samp tag class
 *
 * Defines sample computer code.
 *
 * @package phpHtmlLib
 */
class SAMPtag extends HTMLTagClass {
    protected $_tag = "samp";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return SAMPtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new SAMPtag;
        } else {
            $arg_list = func_get_args();
            return new SAMPtag(NULL, $arg_list);
        }
    }
} // SAMPtag


/**
 * script tag class
 *
 * Defines a script, such as JavaScript.
 *
 * REQUIRED ATTRIBUTES
 *  type : text/ecmascript, text/javascript,
 *         text/jscript, text/vbscript,
 *         text/vbs, text/xml
 *         The MIME type of the script.
 *
 * OPTIONAL ATTRIBUTES
 *  language : javascript, livescript, vbscript
 *             other   DEPRICATED DO NOT USE
 *
 * @package phpHtmlLib
 */
class SCRIPTtag extends HTMLTagClass {
    protected $_tag = "script";

    /**
     * The factory method.
     *
     * @param string the src attribute
     * @param string the type attribute
     * @return SCRIPTtag object
     */
    public static function factory($src="", $type="text/javascript") {
        $attributes = array("type" => $type);
        if ($src != "") {
            $attributes["src"] = $src;
        }
        return new SCRIPTtag( $attributes );
    }
} // SCRIPTtag


/**
 * select tag class
 *
 * @todo create factory method
 *
 *  The select element creates a drop-down box.
 *
 * @package phpHtmlLib
 */
class SELECTtag extends HTMLTagClass {
    protected $_tag = "select";


    /**
     * The factory to build a SELECTtag object
     * with OPTIONtags
     *
     * @param string name of the select.
     * @param array an array of name value pairs for
     *              the options.  the format is
     *              array( "LABEL" => VALUE );
     *              each <option value="VALUE"> LABEL </option>
     *              ie
     *              array( "test" => "foo")  would give an option
     *              of <option value="foo"> test </option>
     *
     *              NOTE: this also supports automatic building of
     *                    the optgroup. Just pass in an array of
     *                    array("foogroup" => array("name" => "value1",
     *                                              "name2" => "value2"),
     *                          "bargroup" => array("blah" => "foo"));
     *
     *
     * @param mixed This can be either a string or an array.
     *              If its a string then, it will be the selected
     *              option value
     *              <option value="foo" SELECTED>foo</option>
     *              If it is an array, then all of the option
     *              values will be marked as SELECTED.  This only
     *              makes sense to do if the multiple_flag  is true.
     * @param boolean is this a multiple selection select box?
     * @param array additionnal attributes to the select tag
     *
     * @return SELECTtag object
     */
    public static function factory($name, $options, $selected=NULL,
                                   $multiple_flag=FALSE, $attribs=FALSE) {
        if ( !$attribs ) {
            $attribs = array();
        }

        $attribs["name"] = $name;
        $select = new SELECTtag( $attribs );
        if ( $multiple_flag ) {
            $select->set_tag_attribute('multiple', 'multiple');
        }

        if ( is_array($options) ) {
            while ( list($label, $value) = each($options) ) {
                //see if they wanted an option group
                if ( is_array($value) ) {
                    $option = OPTGROUPtag::factory($label);
                    foreach( $value as $optname => $optvalue ) {
                        $selected_value = SELECTtag::form_select_is_selected($optvalue, $selected);
                        $option->add(OPTIONtag::factory($optvalue, $optname, $selected_value));
                    }
                } else {
                    $selected_value = SELECTtag::form_select_is_selected($value, $selected);
                    $option = OPTIONtag::factory($value, htmlspecialchars($label), $selected_value);
                }

                $select->add( $option );
            }
        }

        return $select;
    }

    /**
     * This function is used by form_select
     * to determin if a value is selected or not.
     *
     * @param string value
     * @param string selected value
     * @return boolean
     */
    public static function form_select_is_selected($value, $selected) {
        $selected_value = false;

        if ( is_array($selected) ) {
            //looks like this is a multiple select box
            //lets see if the value is in the array
            if ( in_array($value, $selected) ) {
                $selected_value = TRUE;
            }
        } else {
            //must be a string
            if ( $value == $selected ) {
                $selected_value = TRUE;
            }
        }
        return $selected_value;
    }
} // SELECTtag



/**
 * small tag class
 *
 * Renders as smaller text
 *
 * @package phpHtmlLib
 */
class SMALLtag extends HTMLTagClass {
    protected $_tag = "small";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return SMALLtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new SMALLtag;
        } else {
            $arg_list = func_get_args();
            return new SMALLtag(NULL, $arg_list);
        }
    }

} // SMALLtag


/**
 * span tag class
 *
 * The span tag defines a section in a document.
 *
 * NOTE: Browsers do not place a line break before
 *       or after the span tag.
 *
 * @package phpHtmlLib
 */
class SPANtag extends HTMLTagClass {
    protected $_tag = "span";

    /**
     * The factory method.
     *
     * @param string label attribute
     * @param mixed n number of arguments
     *                as content for the tag.
     * @return SPANtag object
     */
    public static function factory($class="") {
        if ($class == "") {
            $attributes = NULL;
        } else {
            $attributes = array('class' => $class);
        }

        $arg_list = func_get_args();
        array_shift($arg_list);
        $obj = new SPANtag($attributes, $arg_list);
        return $obj;
    }
} // SPANtag


/**
 * strong tag class
 *
 * Renders as strong emphasized text
 * @package phpHtmlLib
 *
 */
class STRONGtag extends HTMLTagClass {
    protected $_tag = "strong";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return STRONGtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new STRONGtag;
        } else {
            $arg_list = func_get_args();
            return new STRONGtag(NULL, $arg_list);
        }
    }
} // STRONGtag


/**
 * style tag class
 *
 * Defines a style in a document. The style
 * element goes in the head section. If you
 * want to include a style sheet in your page,
 * you should define the style sheet externally,
 * and link to it using link.
 *
 * REQUIRED ATTRIBUTES
 *  type : text/css, text/javascript
 * @package phpHtmlLib
 */
class STYLEtag extends HTMLTagClass {
    protected $_tag = "style";

    /**
     * The factory method.
     *
     * @param string type attribute
     * @param mixed n number of arguments
     *                as content for the tag.
     * @return STYLEtag object
     */
    public static function factory($type="text/css") {
        $attributes = array('type' => $type);
        $num_args = func_num_args();
        if ($num_args<=1) {
            $obj = new STYLEtag($attributes);
        } else {
            $arg_list = func_get_args();
            array_shift($arg_list);
            $obj = new STYLEtag($attributes, $arg_list);
        }
        return $obj;
    }
} // STYLEtag


/**
 * sub tag class
 *
 * defines a subscript text
 *
 * @package phpHtmlLib
 */
class SUBtag extends HTMLTagClass {
    protected $_tag = "sub";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return SUBtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new SUBtag;
        } else {
            $arg_list = func_get_args();
            return new SUBtag(NULL, $arg_list);
        }
    }
} // SUBtag


/**
 * sup tag class
 *
 * defines a superscript text
 *
 * @package phpHtmlLib
 */
class SUPtag extends HTMLTagClass {
    protected $_tag = "sup";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return SUPtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new SUPtag;
        } else {
            $arg_list = func_get_args();
            return new SUPtag(NULL, $arg_list);
        }
    }
} // SUPtag


/**
 * table tag class
 *
 * The table tag defines the start of a table.
 * Inside a table row you can put table headers,
 * table rows, and table cells.
 * @package phpHtmlLib
 *
 */
class TABLEtag extends HTMLTagClass {
    protected $_tag = "table";


    /**
     * Holds the default attributes for all <tr>'s
     * @var array
     * @private
     */
    protected $_default_row_attributes = NULL;

    /**
     * Holds the default attributes for all <td>'s
     * @var array
     * @private
     */
    protected $_default_col_attributes = NULL;


    /**
     * The factory method.
     *
     * @param string the width attribute
     * @param string the border attribute
     * @param string the cellspacing attribute
     * @param string the cellpadding attribute
     * @param string the align attribute
     * @return TABLEtag object
     */
    public static function factory($width="100%", $border="0",
                                   $cellspacing="0",
                                   $cellpadding="0",$align=NULL) {
        $attributes = array( "width" => $width,
                             "border" => $border,
                             "cellspacing" => $cellspacing,
                             "cellpadding" => $cellpadding);

        if ($align != NULL) {
            $attributes["align"] = $align;
        }
        return new TABLEtag( $attributes );
    }



    //****************************************************************
    // Table specific routines.
    //****************************************************************



    /**
     * push 1 row (tr) of content.
     * Content can be raw strings, or tag objects.
     * Can push 1 item, or multiple items in call.  Each item
     * will be its own td.  should call push() to push a
     * <TR> object, but we detect it here anyway.
     * This function does not save the content by reference.
     * It copies the content and pushes it into the table.
     * If you want to save a reference use push() instead.
     * @param   mixed    $args    The <td>'s to push for next row
     * @return  string
     * @public
     */

    public function add_row() {
        $args = func_get_args();
        $tr = new TRtag( $this->_default_row_attributes );
        $tr->set_default_td_attributes( $this->_default_col_attributes );

        for ($x=0; $x <= func_num_args()-1; $x++) {
            if (is_object($args[$x])) {
                if ($args[$x] instanceOf TDtag) {
                    $tr->add( $args[$x] );
                } else if ($args[$x] instanceOf TRtag) {
                    //the user is trying to use this
                    //to add a TR object.
                    if ($tr->count_content() >= 1) {
                        //there is already content in
                        //the current tr.  This is an
                        //error, since it doesn't make
                        //sense to add data and a row
                        //inside a row.
                        return -1;
                    } else {
                        //user is using this to add
                        //a row. We'll only add it then
                        //bail.
                        $tr = $args[$x];
                        break;
                    }
                } else {
                    //we need to wrap this in its own td.
                    $tr->add( $args[$x] );
                }
            } else {
                //user is adding raw string.
                //lets wrap it in a <tr><td>content</td></tr>
                $tr->add( $args[$x] );
            }

        }
        $this->add( $tr );
    }

    /**
     * Sets the default attributes for <tr>'s
     * that are added to the table.  If there are
     * any attributes set for the <tr> it won't use
     * the defaults.
     *
     * {@source }
     * @param array $attributes - the default attributes
     * @return none
     */
    public function set_default_row_attributes( $attributes=array() ) {
        //should be an array
        $this->_default_row_attributes = $attributes;
    }

    /**
     * Sets the default attributes for <td>'s
     * that are added to the table.  If there are
     * any attributes set for the <td> it won't use
     * the defaults.
     *
     * {@source }
     * @param array $attributes - the default attributes
     * @return none
     */
    public function set_default_col_attributes( $attributes=array() ) {
        //should be an array
        $this->_default_col_attributes = $attributes;
    }



    /**
     * update the attributes of a particular element or td.
     *
     * {@source }
     * @param int $row    row # of the table to edit
     * @param int $col    column # of the table to edit
     * @param array   $attributes array of name=>value pairs
     * @return none
     */
    public function set_cell_attributes( $row, $col, $attributes=array() ) {

        if (is_object($this->_content[$row])) {
            if (is_object($this->_content[$row]->_content[$col])) {
                $this->_content[$row]->_content[$col]->set_tag_attributes( $attributes);
            }
        }
    }

    /**
     * update the attributes of a particular row or tr.
     *
     * {@source }
     * @param int $row    row # of the table to edit
     * @param int $col    column # of the table to edit
     * @param array   $attributes array of name=>value pairs
     * @return mixed -1 if the row doesn't exist already
     */
    public function set_row_attributes( $row, $attributes ) {
        if ($this->_content[$row]) {
            $this->_content[$row]->set_tag_attributes( $attributes );
        } else {
            return -1;
        }
    }

    /**
     * This method sets/resets the content for a specific
     * cell in the table
     *
     * {@source }
     * @param int the row number
     * @param int the column number
     * @param mixed the cell content
     * @return mixed -1 if the cell doesn't exist already
     */
    public function set_cell_content( $row, $col, $content) {

        $item = &$this->_get_element($row);
        if ( is_object($item) ) {
            $item = &$item->_get_element($col);
            if (is_object($item)) {
                $item->reset_content( $content );
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    }

    /**
     * This method is used to set a summary
     * attribute on the table for speech-synthesizing
     * non-visual browsers
     *
     * {@source }
     * @param string the summary
     * @return none
     */
    public function set_summary($summary) {
        $this->set_tag_attribute("summary", $summary);
    }

} // TABLEtag

/**
 * tbody class.
 *
 * Defines a table body.
 *
 * @package phpHtmlLib
 */
class TBODYtag extends TABLEtag {

    /**
     * Tag definition for class.
     * @var  string
     * @private
     */
    protected $_tag = "tbody";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return TBODYtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new TBODYtag;
        } else {
            $arg_list = func_get_args();
            return new TBODYtag(NULL, $arg_list);
        }
    }

}// TBODYtag




/**
 * textarea tag class
 *
 * Defines a text-area (a multi-line text
 *  input control).
 *  The default font in the text-area is fixed pitch.
 *
 * REQUIRED ATTRIBUTES
 *  cols : number
 *         The width of the textarea, in characters.
 *
 *  rows : number
 *         The height of  the textarea, in rows
 *
 * OPTIONAL ATTRIBUTES
 *  wrap : soft, hard, off  DEPRICATED DO NOT USE
 *
 * @package phpHtmlLib
 */
class TEXTAREAtag extends HTMLTagClass {
    protected $_tag = "textarea";

    function _set_flags() {
    //    parent::_set_flags();
        $this->_flags &= ~(phphtmllib::_INDENT | phphtmllib::_NEWLINEAFTEROPENTAG);
    }

    /**
     * The factory method.
     *
     * @param string rows attribute
     * @param string cols attribute
     * @param mixed n number of arguments
     *                as content for the tag.
     * @return TEXTAREAtag object
     */
    public static function factory($rows, $cols) {
        $arg_list = func_get_args();
        array_shift($arg_list);
        array_shift($arg_list);
        $obj = new TEXTAREAtag(array('rows' => $rows,
                                     'cols' => $cols), $arg_list);
        return $obj;
    }

} // TEXTAREAtag



/**
 * tfoot tag class
 *
 * @package phpHtmlLib
 */
class TFOOTtag extends TABLEtag {
    protected $_tag = "tfoot";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return TFOOTtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new TFOOTtag;
        } else {
            $arg_list = func_get_args();
            return new TFOOTtag(NULL, $arg_list);
        }
    }
} // TFOOTtag



/**
 * Table Header th class.
 *
 * Defines a header cell in a table.
 * Very much the same as a data cell,
 * but rendered in bold and with a default
 * center alignment.
 *
 * OPTIONAL ATTRIBUTES
 * same as TDtag
 *
 * STANDARD ATTRIBUTES
 *  same as TDtag
 *
 * EVENT ATTRIBUTES
 *   same as TDtag
 *
 * @package phpHtmlLib
 */
class THtag extends HTMLTagClass {
    protected $_tag = "th";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return THtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new THtag;
        } else {
            $arg_list = func_get_args();
            return new THtag(NULL, $arg_list);
        }
    }

    /**
     * This is a helper for setting the colspan
     * attribute
     *
     * @param int - the colspan value
     */
    public function set_colspan($colspan) {
        $this->set_tag_attribute('colspan', (int)$colspan);
    }

    /**
     * This is a helper for setting the rowspan
     * attribute
     *
     * @param int - the rowspan value
     */
    public function set_rowspan($rowspan) {
        $this->set_tag_attribute('rowspan', (int)$rowspan);
    }
} // <TH>

/**
 * Table data td class.
 *
 * Defines a cell in a table.
 *
 * OPTIONAL ATTRIBUTES
 *  bgcolor : color DEPRICATED DO NOT USE
 *  height : pixels, %  DEPRICATED DO NOT USE
 *  width : pixels, %  DEPRICATED
 *          use styles instead like this <td style="width:100px;">
 *
 * @package phpHtmlLib
 */
class TDtag extends THtag {
    protected $_tag = "td";

    /**
     * The factory method.
     *
     * @param string class attribute
     * @param string align attribute
     * @param mixed n number of arguments
     *                as content for the tag.
     * @return TDtag object
     */
    public static function factory($class="", $align="") {
        if ($class == "" && $align == "") {
            $attributes = NULL;
        } else {
            $attributes = array();
            if ($class != "") {
                $attributes["class"] = $class;
            }

            if ($align != "") {
                $attributes["align"] = $align;
            }
        }

        $arg_list = func_get_args();
        array_shift($arg_list);
        array_shift($arg_list);
        $obj = new TDtag($attributes, $arg_list);
        return $obj;
    }
}// TDtag

/**
 * Table Header thead class.
 *
 * defines a table header
 *
 * @package phpHtmlLib
 */
class THEADtag extends TABLEtag {
    protected $_tag = "thead";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return THEADtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new THEADtag;
        } else {
            $arg_list = func_get_args();
            return new THEADtag(NULL, $arg_list);
        }
    }
} // <TH>


/**
 * title tag class
 *
 * @package phpHtmlLib
 */
class TITLEtag extends HTMLTagClass {
    protected $_tag = "title";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return TITLEtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new TITLEtag;
        } else {
            $arg_list = func_get_args();
            return new TITLEtag(NULL, $arg_list);
        }
    }
} // TITLEtag


/**
 * Table Row tr class.
 * @package phpHtmlLib
 */
class TRtag extends HTMLTagClass {
    protected $_tag = "tr";

    /**
     * Holds the default attributes for all <td>'s
     * @var array
     * @private
     */
    protected $_default_td_attributes = NULL;

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return TRtag object
     */
    public static function factory($class="") {
        //we need to make sure all arguments
        //pass through the add method
        //because add automagically converts
        //strings to LItag objects.
        if ($class == "") {
            $attributes = NULL;
        } else {
            $attributes = array('class' => $class);
        }

        $tag = new TRtag($attributes);
        $num_args = func_num_args();
        if ($num_args > 1) {
            $arg_list = func_get_args();
            array_shift($arg_list);
            foreach( $arg_list as $arg) {
                $tag->add($arg);
            }
        }

        return $tag;
    }

    //****************************************************************
    // TR specific routines.
    //****************************************************************

    /**
     * Sets the default attributes for <td>'s
     * that are added to the table.  If there are
     * any attributes set for the <td> it won't use
     * the defaults.
     *
     * @param array $attributes - the default attributes
     */
    public function set_default_td_attributes( $attributes=array() ) {
        $this->_default_td_attributes = $attributes;
    }

    /**
     * add content onto content stack
     * adds content to tag as a FIFO.
     * You can have n number of parameters.
     * each one will get added in succession to the content.
     *
     * we override this from the parent so we can auto detect if
     * the user is adding raw strings instead of objects.
     * If they are trying to add raw strings, then we wrap that in
     * a TDtag object, since you can't add anything other then a <TD> or
     * <TH> to a <TR>.
     * @param   mixed   $content - either string, or tag object.
     * @access  public
     */
    public function add() {
        $args = func_get_args();

        foreach( $args as $content) {
            if (!is_object($content) || (!($content instanceOf TDtag) &&
                                         !($content instanceOf THtag)) ) {
                //$content is raw (string)
                //lets wrap it in a <td> object
                $td = new TDtag( $this->_default_td_attributes );
                $td->add( $content );
                parent::add( $td );
            } else {
                //looks like this is some object
                //let the user do it.
                //should we only let them add a
                //<TD> object?
                parent::add( $content );
            }
        }
    }

} // TRtag

/**
 * tt tag class
 * @package phpHtmlLib
 */
class TTtag extends HTMLTagClass {
    protected $_tag = "tt";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return TTtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new TTtag;
        } else {
            $arg_list = func_get_args();
            return new TTtag(NULL, $arg_list);
        }
    }
} // TTtag

/**
 * u tag class
 * @package phpHtmlLib
 */
class Utag extends HTMLTagClass {
    protected $_tag = "u";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return Utag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new Utag;
        } else {
            $arg_list = func_get_args();
            return new Utag(NULL, $arg_list);
        }
    }
} // Utag


/**
 * ul tag class
 * @package phpHtmlLib
 */
class ULtag extends OLtag {
    protected $_tag = "ul";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return ULtag object
     */
    public static function factory() {
        //we need to make sure all arguments
        //pass through the add method
        //because add automagically converts
        //strings to LItag objects.
        $tag = new ULtag;
        $num_args = func_num_args();
        if ($num_args >= 1) {
            $arg_list = func_get_args();
            foreach( $arg_list as $arg) {
                $tag->add($arg);
            }
        }

        return $tag;
    }
} // ULtag

/**
 * var tag class
 * @package phpHtmlLib
 */
class VARtag extends HTMLTagClass {
    protected $_tag = "var";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return VARtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new VARtag;
        } else {
            $arg_list = func_get_args();
            return new VARtag(NULL, $arg_list);
        }
    }
} // VARtag


/**
 * xmp tag class
 * @package phpHtmlLib
 */
class XMPtag extends HTMLTagClass {
    protected $_tag = "xmp";

    /**
     * The factory method.
     *
     * @param mixed - the content for the tag
     * @return XMPtag object
     */
    public static function factory() {
        $num_args = func_num_args();
        if (!$num_args) {
            return new XMPtag;
        } else {
            $arg_list = func_get_args();
            return new XMPtag(NULL, $arg_list);
        }
    }
} // XMPtag

?>
