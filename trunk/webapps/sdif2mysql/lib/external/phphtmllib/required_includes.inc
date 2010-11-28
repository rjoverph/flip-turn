<?php
/**
 * the script that includes this file MUST
 * set the $phphtmllib var.  Its used to determine
 * the base path on the filesystem where the php html libs
 * live.
 *
 * $Id: autoload.inc 1832 2006-08-08 19:29:49Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 *
 * @package phpHtmlLib
 * @todo rewrite using the AutoloadGenerator class
 *
 */
//require('config.inc');

/**
 * The base interface for all
 */
require_once(PHPHTMLLIB."/phphtmllib.inc");

/**
 * this is the base class of them ALL
 */
include_once(PHPHTMLLIB."/src/core/Container.inc");

/**
 * get the XML tag class
 */
include_once(PHPHTMLLIB."/src/core/XMLTagClass.inc");

/**
 * get the parent tag class
 */
include_once(PHPHTMLLIB."/src/core/HTMLTagClass.inc");

/**
 * include the html tags
 */
include_once(PHPHTMLLIB.'/src/core/HTMLTAGS.inc');

/**
 * Include the XML tags
 */
include_once(PHPHTMLLIB.'/src/core/XMLTAGS.inc');

/**
 * include the html tags
 */
include_once(PHPHTMLLIB.'/src/misc/tag_utils/html_utils.inc');
include_once(PHPHTMLLIB.'/src/misc/tag_utils/divtag_utils.inc');
include_once(PHPHTMLLIB.'/src/xml/xml_utils.inc');
include_once(PHPHTMLLIB.'/src/misc/tag_utils/form_utils.inc');


//include_once(PHPHTMLLIB.'/debug_dump.inc');
//include_once(PHPHTMLLIB.'/timers.inc');
?>
