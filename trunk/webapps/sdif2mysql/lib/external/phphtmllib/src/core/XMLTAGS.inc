<?php

/**
 * This file contains all of the default
 * support xml tags by phpHtmlLib.
 *
 * $Id: XMLTAGS.inc 3203 2008-11-21 18:29:55Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 *
 */


/**
 * xml tag class
 * @package phpHtmlLib
 */
class XMLtag extends XMLTagClass {
    protected $_tag = "xml";
    protected $_tag_prefix = "<?";
    protected $_tag_postfix = " ?>";

    function __construct( $attributes=array() ) {
		parent::__construct( $this->_tag, $attributes);
        $this->_flags &= ~(phphtmllib::_CONTENTREQUIRED | phphtmllib::_CLOSETAGREQUIRED);
        $this->_flags |= phphtmllib::_ALWAYS_LOWERCASE | phphtmllib::_NOFINISHSLASHXHTML;

		$num_args = func_num_args();
        for ($i=1;$i<$num_args;$i++) {
            $this->add(func_get_arg($i));
        }
    }

} // XMLtag

/**
 * xml-stylesheet tag class
 * @package phpHtmlLib
 */
class XMLSTYLESHEETtag extends XMLtag {
    protected $_tag = "xml-stylesheet";
} // XMLSTYLESHEETtag


/**
 * A simple wrapper for standard XML
 * CDATA section data
 * @package phpHtmlLib
 */
class CDATAtag extends XMLTagClass {
    protected $_tag = "CDATA[";
    protected $_tag_prefix = "<![";
    protected $_tag_postfix = "]]>";

	function __construct() {
		parent::__construct($this->_tag, array());
        $this->_flags &= ~phphtmllib::_CLOSETAGREQUIRED;
        $this->_flags |= phphtmllib::_NOFINISHSLASHXHTML;

		$num_args = func_num_args();
        for ($i=0;$i<$num_args;$i++) {
            $this->add(func_get_arg($i));
		}
	}

	function _render_open_tag( $indent_level, $finish_slash=FALSE ) {
		//get the indent level
		$indent = $this->_render_indent( $indent_level );

		$xml = $indent . $this->_tag_prefix . $this->_tag;

		if ($this->_flags & phphtmllib::_NEWLINEAFTEROPENTAG) {
			$xml .= "\n";
		}
		return $xml;
	}

	function _render_close_tag($indent_level) {
		$indent = "";
		if (($this->_flags & phphtmllib::_INDENT) && ($this->_flags & phphtmllib::_NEWLINEAFTEROPENTAG)) {
			$indent = $this->_render_indent($indent_level);
		}
		$str = $indent .$this->_tag_postfix;

		if ($this->_flags & phphtmllib::_NEWLINEAFTERCLOSETAG) {
			$str .= "\n";
		}
		return $str;
	}
}

?>
