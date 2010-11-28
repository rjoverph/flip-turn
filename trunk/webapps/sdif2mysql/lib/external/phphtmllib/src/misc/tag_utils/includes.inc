<?php

/**
 * this file includes all of the utility function files.
 * these files define utility functions that help
 * the creation of the tag objects.
 *
 * $Id: includes.inc 1551 2005-09-07 19:26:21Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 *
 */

/**
 * do the includes
 */
include_once( PHPHTMLLIB.'/tag_utils/divtag_utils.inc');
include_once( PHPHTMLLIB.'/tag_utils/font_utils.inc');
include_once( PHPHTMLLIB.'/tag_utils/form_utils.inc');
include_once( PHPHTMLLIB.'/tag_utils/frame_utils.inc');
include_once( PHPHTMLLIB.'/tag_utils/html_utils.inc');
include_once( PHPHTMLLIB.'/tag_utils/misc_utils.inc');

//include the xml stuff
include_once( PHPHTMLLIB.'/tag_utils/xml_utils.inc');
include_once( PHPHTMLLIB.'/tag_utils/wml_utils.inc');
include_once( PHPHTMLLIB.'/tag_utils/svg_utils.inc');

?>
