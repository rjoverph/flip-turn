<?php
/**
 * This file contains helper functions related
 * to framesets and frames
 *
 * $Id: frame_utils.inc 1505 2005-09-01 00:17:51Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * 
 */


/**
 * This function is used to build a 
 * FRAMESETtag object with the most
 * common attributes.
 * NOTE: It comes with the following attributes
 *       defaulted to:
 *       framespacing = "0"
 *       frameborder = "no"
 * 
 * @see FRAMESETtag::factory()
 *
 * @param string - $rows - the rows attribute
 * @param string - $cols - the cols attribute
 * @param int    - $border - the border attribute
 * @return FRAMESETtag object
 */
function html_frameset( $rows, $cols, $border="0" ) {
    return FRAMESETtag::factory($rows, $cols, $border);
}

/**
 * This function is used to build a
 * FRAMEtag object with some common attributes
 * already set.
 * NOT: this comes with the following attribtes 
 *      defaulted to:
 *      marginwidth = "0"
 *      marginheight = "0"
 *      noresize
 *      frameborder = "0"
 * 
 * @see FRAMEtag::factory()
 * 
 * @param string - $name - the "name" attribute
 * @param string - $src  - the "src" atribute
 * @param string - $scrolling - the "scrolling" attribute
 * @return FRAMEtag object.
 */
function html_frame( $name, $src, $scrolling="no") {
    return FRAMEtag::factory($name, $src, $scrolling);
}
 

?>
