<?php
/**
 * Holds the main phphtmllib Interface Class
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * The base interface object definition
 * for the entire library
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
interface phphtmllib {

    const VERSION = "#!#VERSION#!#";

    const XHTML_TRANSITIONAL = "xhtml_transitional";
    const XHTML = "xhtml_transitional";
    const XHTML_STRICT = "xhtml_strict";
    const XHTML_FRAMESET = "xhtml_frameset";
    const HTML= "html";

    const INDENT_NICE= 0;
    const INDENT_LEFT_JUSTIFY = -1;

    const _HTML_SPACE = "&nbsp;";
    const _HTML_MDASH = "&mdash;";

    const _INDENT_STR= "  ";

    const _NEWLINEAFTERCONTENT = 1;
    const _NEWLINEAFTEROPENTAG = 2;
    const _NEWLINEAFTERCLOSETAG= 4;
    const _CONTENTREQUIRED = 8;
    const _CLOSETAGREQUIRED = 16;
    const _DEPRICATED = 32;
    const _INDENT = 64;
    const _COLLAPSE = 128;
    const _ALWAYS_UPPERCASE = 256;
    const _ALWAYS_LOWERCASE = 512;
    const _NOFINISHSLASHXHTML = 1024;
    const _CDATACONTENTWRAP = 2048;
    const _XHTMLCOMPLIANT = 4096;

    //We do this to slightly speed things up by
    //removing _set_flags() for all

    //Container phphtmllib::_NEWLINEAFTERCONTENT | phphtmllib::_INDENT;
    const _FLAGS_DEFAULT = 65;

    //XMLTagClass
    //_FLAGS_DEFAULT | phphtmllib::_NEWLINEAFTEROPENTAG |
    //phphtmllib::_NEWLINEAFTERCLOSETAG | phphtmllib::_CONTENTREQUIRED |
    //phphtmllib::_CLOSETAGREQUIRED
    const _FLAGS_DEFAULT_XMLTAG = 95;

    //XML tag w/o content or close tag
    //_FLAGS_DEFAULT_XMLTAG &= ~(phphtmllib::_CONTENTREQUIRED | phphtmllib::_CLOSETAGREQUIRED);
    const _FLAGS_XML_OPEN_ONLY = 71;

    //XML tag w/o content or close tag
    //_FLAGS_DEFAULT_XMLTAG &= ~phphtmllib::_NEWLINEAFTEROPENTAG;
    const _FLAGS_XML_NO_NEWLINE_AFTER_OPEN = 93;

    //special case for the DOCTYPE tag
    //$this->_flags &= ~(phphtmllib::_CONTENTREQUIRED | phphtmllib::_CLOSETAGREQUIRED);
    //$this->_flags |= phphtmllib::_ALWAYS_UPPERCASE | phphtmllib::_NOFINISHSLASHXHTML;
    const _FLAGS_XML_DOCTYPE = 1410;

    //HTML Depricated
    //_FLAGS_DEFAULT_XMLTAG |= phphtmllib::_DEPRICATED;
    const _FLAGS_HTML_DEPRICATED = 127;

    const _TAG_PREFIX = "<";
    const _TAG_SUFFIX = ">";

    public function render($indent_level=0, $output_debug=0);
}


function phphtmllib_get_version() {
    return phphtmllib::VERSION;
}

?>
