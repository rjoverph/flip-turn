<?php

/**
 * This file contains miscellaneous functions
 * used by the phpHtmllibs that don't seem to
 * fit in the other files.
 *
 * $Id: misc_utils.inc 2162 2006-10-07 00:13:17Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 *
 */

/**
 * This builds an IMG tag object that is used
 * to show a spacer image.
 * <img src="spacer.gif" width="$width" height="$height">
 *
 * @param   int $width - the width of the img
 *                       ( DEFAULT : 1)
 * @param   int $height - the height of the img
 *                       ( DEFAULT : 1)
 * @param   string  $img_path - The dir that holds the spacer.gif file.
 *                              ( DEFAULT = "/images" )
 * @return  IMGtag object.
 */
function build_spacergif_imgtag( $width=1, $height=1, $img_path='/images' ) {
    $attributes = array( "src" => $img_path.'/spacer.gif',
                         "width" => $width,
                         "height" => $height);
    return html_img( $img_path.'/spacer.gif', $width, $height );
}

/**
 * This function creates a new container widget
 * and stuffs all the args into it.
 *
 * @param mixed - variable # of args
 * @return Container object
 */
function container() {
    $container = new Container;

    $num_args = func_num_args();
    for ($i=0;$i<$num_args;$i++) {
        $container->add(func_get_arg($i));
    }
    return $container;
}


/**
 * This function is used to wrap
 * a string in the standard
 * CDATA section wrapper for a
 * tag content
 *
 * <![CDATA[ CONTENT ]]>
 *
 * @param string the content to wrap
 */
function cdata_wrapper( ) {
	$tag = new CDATAtag;

	$num_args = func_num_args();
    for ($i=0;$i<$num_args;$i++) {
        $tag->add(func_get_arg($i));
    }
	return $tag;
}
?>
