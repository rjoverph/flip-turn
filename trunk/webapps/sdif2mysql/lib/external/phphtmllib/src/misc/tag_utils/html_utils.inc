<?php

/**
 * This file contains some utility functions
 * to help build some Tag objects that are
 * commonly used in html.
 *
 * $Id: html_utils.inc 2440 2007-02-22 23:58:51Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 *
 */


/**
 * build an href with content and attributes.
 *
 * @tutorial HTMLTagClass.cls#helper
 *
 * @author Walt A. Boring
 *
 * @see Atag::factory()
 * @param   string the url to go to.
 * @param   string the visible link text.
 * @param   string class - the css class to use.
 * @param   string the target browser
 *                 window/frame for the url.
 * @param   string the title attribute
 * @return  Atag object.
 */
function html_a($url, $content, $class=NULL, $target=NULL, $title=NULL) {
    return Atag::factory($url, $content, $class, $target, $title);
}

/**
 * build an abbr tag with content.
 *
 *  This is to build an abbreviation.
 *  normally its just
 *  <abbr title="foo bar">foo</abbr>
 *
 * @see ABBRtag::factory()
 *
 * @param string - the title attribute
 * @param mixed - the content for the tag
 * @return  ABBRtag object.
 */
function html_abbr($title, $content) {
    return ABBRtag::factory($title, $content);
}

/**
 * build an acronym tag with content.
 *
 *  This is to build an acronym.
 *  normally its just
 *  <acronym title="foo bar">foo</abbr>
 *
 * @see ACRONYMtag::factory()
 *
 * @param string - the title attribute
 * @param mixed - the content for the tag
 * @return  ACRONYMtag object.
 */
function html_acronym($title, $content) {
    return ACRONYMtag::factory($title, $content);
}

/**
 * build an address tag with content.
 *
 * @return  ADDRESStag object.
 */
function html_address() {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new ADDRESStag;
    } else {
        $arg_list = func_get_args();
        return new ADDRESStag(NULL, $arg_list);
    }
}

/**
 * build an applet tag with content.
 *
 * @return  APPLETtag object.
 */
function html_applet() {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new APPLETtag;
    } else {
        $arg_list = func_get_args();
        return new APPLETtag(NULL, $arg_list);
    }
}

/**
 * build an area tag with content.
 *
 * @see AREAtag::factory()
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
function html_area($href, $coords, $shape="rect",
                   $alt="", $target="", $title="") {

    return AREAtag::factory($href, $coords, $shape,
                            $alt, $target, $title);
}

/**
 * build a bold b tag with content.
 *
 * @author Walt A. Boring
 * @return  BRtag object.
 */
function html_b() {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new Btag;
    } else {
        $arg_list = func_get_args();
        return new Btag(NULL, $arg_list);
    }
}

/**
 * build a base tag.
 * This tag MUST go in the head
 *
 * @param string - the href
 * @param string - the target
 *                 _blank, _parent, _self, _top
 * @return  BASEtag object.
 */
function html_base($href, $target="") {
    return BASEtag::factory($href, $target);
}

/**
 * build a bdo tag.
 * dir attribute is required.
 *
 * @param string - the dir attribute
 *                ltr, rtl
 * @param mixed - any number of text
 *                content params.
 * @return BDOtag object.
 */
function html_bdo($dir) {
    $attributes = array('dir' => $dir);
    $num_args = func_num_args();
    if ( $num_args==1 ) {
        $obj = new BDOtag($attributes);
    } else {
        $arg_list = func_get_args();
        array_shift($arg_list);
        $obj = new BDOtag($attributes, $arg_list);
    }
    return $obj;
}


/**
 * build a big tag with content.
 *
 * @author Walt A. Boring
 * @return BIGtag object.
 */
function html_big() {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new BIGtag;
    } else {
        $arg_list = func_get_args();
        return new BIGtag(NULL, $arg_list);
    }
}

/**
 * build a blockquote tag with content.
 *
 * @author Walt A. Boring
 * @return BLOCKQUOTEtag object.
 */
function html_blockquote() {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new BLOCKQUOTEtag;
    } else {
        $arg_list = func_get_args();
        return new BLOCKQUOTEtag(NULL, $arg_list);
    }
}

/**
 * build a body tag with content.
 *
 * @author Walt A. Boring
 * @return BODYtag object.
 */
function html_body() {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new BODYtag;
    } else {
        $arg_list = func_get_args();
        return new BODYtag(NULL, $arg_list);
    }
}

/**
 * builds n # of  br tags.
 *
 * @param int - the number of
 *              br tags you want
 * @param string the class attribute
 *
 * @return  mixed - BRtag object.
 *                  or Container
 */
function html_br($num=1, $class=null) {
    return BRtag::factory($num, $class);
}

/**
 * build a button tag with content.
 *
 * @param string - the button type
 *                 button, reset, submit
 *                 DEFAULT : button
 * @param mixed - any number of items as
 *                content.
 * @return BUTTONtag object.
 */
function html_button($type="button") {
    $attributes = array('type' => $type);
    $num_args = func_num_args();
    if ( $num_args==1 ) {
        $obj = new BUTTONtag($attributes);
    } else {
        $arg_list = func_get_args();
        array_shift($arg_list);
        $obj = new BUTTONtag($attributes, $arg_list);
    }
    return $obj;
}

/**
 * build a caption tag with content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return CAPTIONtag object.
 */
function html_caption() {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new CAPTIONtag;
    } else {
        $arg_list = func_get_args();
        return new CAPTIONtag(NULL, $arg_list);
    }
}

/**
 * build a center tag with some content.
 * DEPRICATED
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return CENTERtag object.
 */
function html_center( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new CENTERtag;
    } else {
        $arg_list = func_get_args();
        return new CENTERtag(NULL, $arg_list);
    }
}

/**
 * build a cite tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return CITEtag object.
 */
function html_cite( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new CITEtag;
    } else {
        $arg_list = func_get_args();
        return new CITEtag(NULL, $arg_list);
    }
}

/**
 * build a code tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return CODEtag object.
 */
function html_code( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new CODEtag;
    } else {
        $arg_list = func_get_args();
        return new CODEtag(NULL, $arg_list);
    }
}

/**
 * build a col tag
 *
 * @param int the width attribute
 * @param string the align attribute
 * @param string the span attribute
 * @return COLtag object.
 */
function html_col($width='', $align='', $span='') {
    return COLtag::factory($width, $aligh, $span);
}

/**
 * build a colgroup tag.
 *
 * NOTE: The colgroup element is an empty
 *       element that contains attributes
 *       only. To create columns, you must
 *       specify td elements within a tr
 *       element.
 *
 * @param array - tag attributes.
 * @return COLGROUPEtag object.
 */
function html_colgroup( $attributes ) {
    return COLGROUPtag::factory( $attributes );
}

/**
 * render an html comment string
 *
 * @param   string - the string to comment.
 * @return  string - the string wrapped in
 *                   the html comment block
 */
function html_comment( $string ) {
    return '<!-- ' . $string . ' //-->';
}

/**
 * build a dd tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return DDtag object.
 */
function html_dd( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new DDtag;
    } else {
        $arg_list = func_get_args();
        return new DDtag(NULL, $arg_list);
    }
}

/**
 * build a del tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return DELtag object.
 */
function html_del( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new DELtag;
    } else {
        $arg_list = func_get_args();
        return new DELtag(NULL, $arg_list);
    }
}


/**
 * build a dfn tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return DFNtag object.
 */
function html_dfn( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new DFNtag;
    } else {
        $arg_list = func_get_args();
        return new DFNtag(NULL, $arg_list);
    }
}

/**
 * build a dir tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return DIRtag object.
 */
function html_dir( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new DIRtag;
    } else {
        $arg_list = func_get_args();
        return new DIRtag(NULL, $arg_list);
    }
}

/**
 * html_div() is defined in
 * divtag_utils.inc
 */

/**
 * build a dl tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return DLtag object.
 */
function html_dl( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new DLtag;
    } else {
        $arg_list = func_get_args();
        return new DLtag(NULL, $arg_list);
    }
}

/**
 * build a dt tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return DTtag object.
 */
function html_dt( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new DTtag;
    } else {
        $arg_list = func_get_args();
        return new DTtag(NULL, $arg_list);
    }
}

/**
 * build a em tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return EMtag object.
 */
function html_em( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new EMtag;
    } else {
        $arg_list = func_get_args();
        return new EMtag(NULL, $arg_list);
    }
}

/**
 * build a fieldset tag with some content.
 *
 * @param   mixed - The legend text, or the
 *                  LEGENDtag for the fieldset.
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return FIELDSETtag object.
 */
function html_fieldset($legend="") {
    $arg_list = func_get_args();

    if ( $legend != "" ) {
        if ( !is_object($legend) ) {
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

/**
 * html_form() is defined
 * in form_utils.inc
 */


/**
 * build an H1 tag object with content.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return  H1tag object.
 */
function html_h1( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        $obj = new H1tag;
    } else {
        $arg_list = func_get_args();
        $obj = new H1tag(NULL, $arg_list);
    }
    $obj->set_collapse();
    return $obj;
}

/**
 * build an H2 tag object with content.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return  H2tag object.
 */
function html_h2( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        $obj = new H2tag;
    } else {
        $arg_list = func_get_args();
        $obj = new H2tag(NULL, $arg_list);
    }
    $obj->set_collapse();
    return $obj;
}


/**
 * build an H3 tag object with content.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return  H3tag object.
 */
function html_h3( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        $obj = new H3tag;
    } else {
        $arg_list = func_get_args();
        $obj = new H3tag(NULL, $arg_list);
    }
    $obj->set_collapse();
    return $obj;
}

/**
 * build an H4 tag object with content.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return  H4tag object.
 */
function html_h4( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        $obj = new H4tag;
    } else {
        $arg_list = func_get_args();
        $obj = new H4tag(NULL, $arg_list);
    }
    $obj->set_collapse();
    return $obj;
}

/**
 * build an H5 tag object with content.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return  H5tag object.
 */
function html_h5( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        $obj = new H5tag;
    } else {
        $arg_list = func_get_args();
        $obj = new H5tag(NULL, $arg_list);
    }
    $obj->set_collapse();
    return $obj;
}


/**
 * build an H6 tag object with content.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return  H6tag object.
 */
function html_h6( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        $obj = new H6tag;
    } else {
        $arg_list = func_get_args();
        $obj = new H6tag(NULL, $arg_list);
    }
    $obj->set_collapse();
    return $obj;
}

/**
 * build an head tag object with content.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return  HEADtag object.
 */
function html_head( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new HEADtag;
    } else {
        $arg_list = func_get_args();
        return new HEADtag(NULL, $arg_list);
    }
}

/**
 * build an hr tag object.
 *
 * @see HRtag::factory()
 * @return  HRtag object.
 */
function html_hr( ) {
    return HRtag::factory();;
}

/**
 * build an html tag object.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return  HTMLtag object.
 */
function html_html( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new HTMLtag;
    } else {
        $arg_list = func_get_args();
        return new HTMLtag(NULL, $arg_list);
    }
}


/**
 * build a i tag with some content.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return Itag object.
 */
function html_i( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new Itag;
    } else {
        $arg_list = func_get_args();
        return new Itag(NULL, $arg_list);
    }
}

/**
 * build a irame tag with some content.
 *
 * @see IFRAMEtag::factory()
 *
 * @author Walt A. Boring
 * @param string the src attribute
 * @param string the width attribute
 * @param string the height attribute
 * @param string the scrolling attribute
 * @return Itag object.
 */
function html_iframe($src, $width="", $height="", $scrolling="") {
    return IFRAMEtag::factory($src, $width, $height, $scrolling);
}


/**
 * Build an img tag.
 *  If width and or height are not provided
 *  we do not set them in the tag.
 *
 * @see IMGtag::factory()
 *
 * @author Walter A. Boring IV
 * @param   string - $image - image src
 * @param   int    - $width - width of the image.
 * @param   int    - $heigth - height of the image
 * @param   int    - $border - border flag.
 * @param   string - $alt - alt tag for the image
 * @param   string - $usemap - the image map name
 * @param   string - $align - the align attribute
 * @param   string - $localfilename - the full path
 *                   to the filename.  If this is set
 *                   and $width == '' and $height == ''
 *                   then we will try and determine the
 *                   size attributes of the image.
 * @return  IMGtag object.
 */
function html_img( $image, $width='', $height='', $border=0,
                   $alt="", $usemap=NULL, $title=NULL,
                   $align=NULL, $filename=NULL ) {

    return IMGtag::factory($image, $width, $height, $border,
                           $alt, $usemap, $title, $align,
                           $filename);
}


/**
 * This method is a wrapper for html_img() that
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
 * @param   string - $image - image src
 * @param   int    - $border - border flag.
 * @param   string - $alt - alt tag for the image
 * @param   string - $usemap - the image map name
 * @param   string - $align - the align attribute
 * @return IMGtag object
 */
function html_img_local($image, $border=0, $alt='', $usemap=NULL,
                        $title=NULL, $align=NULL) {
    return IMGtag::factory_local($image, '', '', $border, $alt, $usemap,
                                 $title, $align, $_SERVER['DOCUMENT_ROOT'].$image);
}


/**
 * This method is similar to html_img_local, but it assumes the
 * image is on a remote server, so it won't prepent $_SERVER['DOCUMENT_ROOT']
 * to the getimagesize() call.  This is purely a wrapper for html_img()
 * eliminating the width, and height attributes.
 *
 * @param   string - $image - image src
 * @param   int    - $border - border flag.
 * @param   string - $alt - alt tag for the image
 * @param   string - $usemap - the image map name
 * @param   string - $align - the align attribute
 * @return IMGtag object
 */
function html_img_remote($image, $border=0, $alt='', $usemap=NULL,
                         $title=NULL, $align=NULL) {
    return html_img($image, '', '', $border, $alt, $usemap,
                    $title, $align, $image);
}


/**
 * build an hlink for an image.
 * this automatically turns off indenting
 * and newlines, so it formats well
 *
 * @param   string - $url - href for the a
 * @param   string - $image - src for the img
 * @param   int    - $width - width of the image
 * @param   int    - $height - height of the image
 * @param   int    - $border - for the img
 * @param   string - $alt - for the img ALT=""
 * @param   string - $usemap - the image map name
 * @param   string - $target - the a target="blah"
 * @param   string - $title - the title attribute
 * @param   string - $align - the align attribute
 * @return  Atag object with img as content
 *
 */
function html_img_href( $url, $image, $width='', $height='', $border=0,
                        $alt="", $usemap=NULL, $target=NULL, $title=NULL, $align=NULL) {
    $img = html_img($image, $width, $height, $border, $alt, $usemap, $title, $align);
    $a = html_a($url, $img, NULL, $target);
    return $a;
}


/**
 * This builds an input object
 * NOTE: This wrapper automatically
 *       calls htmlspecialchars() on
 *       the value attribute's data.
 *
 * @param string - the type attribute
 * @param string - the name attribute
 * @param string - the value attribute
 * @param array  - any other name=>value attributes
 *                 for the tag
 *
 * @return INPUTtag object.
 */
function html_input( $type, $name, $value='', $attributes=array() ) {
    return INPUTtag::factory($type, $name, $value, $attributes);
}

/**
 * build a ins tag with some content.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return INStag object.
 */
function html_ins( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new INStag;
    } else {
        $arg_list = func_get_args();
        return new INStag(NULL, $arg_list);
    }
}

/**
 * build a kbd tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return KBDtag object.
 */
function html_kbd( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new KBDtag;
    } else {
        $arg_list = func_get_args();
        return new KBDtag(NULL, $arg_list);
    }
}

/**
 * build a label tag with some content.
 *
 * @param   string - the id of the form
 *                   element to tie this
 *                   label to.
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return LABELtag object.
 */
function html_label($for="") {

    $attributes = array();
    if ( $for != "" ) {
        $attributes["for"] = $for;
    }
    $tag = new LABELtag( $attributes );
    $num_args = func_num_args();
    for ( $i=1;$i<$num_args;$i++ ) {
        $tag->add(func_get_arg($i));
    }
    return $tag;
}

/**
 * build a legend tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return LEGENDtag object.
 */
function html_legend( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new LEGENDtag;
    } else {
        $arg_list = func_get_args();
        return new LEGENDtag(NULL, $arg_list);
    }
}


/**
 * build a LI tag with some content..
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return LItag object.
 */
function html_li( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new LItag;
    } else {
        $arg_list = func_get_args();
        return new LItag(NULL, $arg_list);
    }
}

/**
 * build a LINK tag with some content..
 *
 * @see LINKtag::factory()
 *
 * @param   string the href link
 * @param   string the rel attribute
 * @param   string the type of content.
 * @return LINKtag object.
 */
function html_link($href, $rel, $type) {
    return LINKtag::factory($href, $rel, $type);
}

/**
 * build a map tag with some content.
 *
 * @param   string - the name of the map.
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return MAPtag object.
 */
function html_map( $name ) {
    $attributes = array('name' => $name);
    $num_args = func_num_args();
    if ( $num_args==1 ) {
        $obj = new MAPtag($attributes);
    } else {
        $arg_list = func_get_args();
        array_shift($arg_list);
        $obj = new MAPtag($attributes, $arg_list);
    }
    return $obj;
}

/**
 * build a meta tag..
 *
 * @param   string - the content value.
 * @param   string - the http-equiv value
 * @param   string - the name
 *
 * @return METAtag object.
 */
function html_meta( $content, $http_equiv="", $name="" ) {
    return METAtag::factory($content, $http_equiv, $name);
}


/**
 * build a noframes tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return NOFRAMEStag object.
 */
function html_noframes( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new NOFRAMEStag;
    } else {
        $arg_list = func_get_args();
        return new NOFRAMEStag(NULL, $arg_list);
    }
}

/**
 * build a noscript tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return NOSCRIPTtag object.
 */
function html_noscript( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new NOSCRIPTtag;
    } else {
        $arg_list = func_get_args();
        return new NOSCRIPTtag(NULL, $arg_list);
    }
}

/**
 * build a object tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return OBJECTtag object.
 */
function html_object( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new OBJECTtag;
    } else {
        $arg_list = func_get_args();
        return new OBJECTtag(NULL, $arg_list);
    }
}

/**
 * build a OL tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return OLtag object.
 */
function html_ol( ) {
    //we need to make sure all arguments
    //pass through the add method
    //because add automagically converts
    //strings to LItag objects.
    $tag = new OLtag;
    $num_args = func_num_args();
    if ( $num_args >= 1 ) {
        $arg_list = func_get_args();
        foreach( $arg_list as $arg) {
            $tag->add($arg);
        }
    }
    return $tag;
}

/**
 * build a OPTGROUP tag with some content..
 *
 * @param string label attribute
 * @param  mixed - n number of arguments
 *                  as content for the tag.
 * @return OPTGROUPtag object.
 */
function html_optgroup($label) {
    $tag = new OPTGROUPtag( array("label" => $label));
    $num_args = func_num_args();
    for ( $i=1;$i<$num_args;$i++ ) {
        $tag->add(func_get_arg($i));
    }
    return $tag;
}

/**
 * build a OPTION tag with some content..
 *
 * @param string - the value attribute
 * @param string - the content for the tag.
 *
 * @return OPTIONtag object.
 */
function html_option($value, $content, $selected=FALSE) {
    return OPTIONtag::factory($value, $content, $selected);
}


/**
 * build a p tag.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return Ptag object.
 */
function html_p( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new Ptag;
    } else {
        $arg_list = func_get_args();
        return new Ptag(NULL, $arg_list);
    }
}

/**
 * build a param tag.
 *
 * @see PARAMtag::factory()
 *
 * @param string name attribute
 * @param string value attribute
 * @return PARAMtag object.
 */
function html_param($name, $value="") {
    return PARAMtag::factory($name, $value);
}

/**
 * build a pre tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return PREtag object.
 */
function html_pre( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new PREtag;
    } else {
        $arg_list = func_get_args();
        return new PREtag(NULL, $arg_list);
    }
}

/**
 * build a q tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return Qtag object.
 */
function html_q( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new Qtag;
    } else {
        $arg_list = func_get_args();
        return new Qtag(NULL, $arg_list);
    }
}

/**
 * build a samp tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return SAMPtag object.
 */
function html_samp( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new SAMPtag;
    } else {
        $arg_list = func_get_args();
        return new SAMPtag(NULL, $arg_list);
    }
}

/**
 * build a script tag with some content..
 *
 * @see SCRIPTtag::factory()
 *
 * @param   src    - the src
 * @param   string - type of script
 * @return SCRIPTtag object.
 */
function html_script($src="", $type="text/javascript") {
    return SCRIPTtag::factory($src, $type);
}

/**
 * select tag is defined in
 * form_utils.inc as
 * form_select()
 *
 */

/**
 * build a small small tag with content.
 *
 * @author Suren Markosian
 * @return SMALLtag object.
 */
function html_small() {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new SMALLtag;
    } else {
        $arg_list = func_get_args();
        return new SMALLtag(NULL, $arg_list);
    }
}


/**
 * build a bold span tag with content.
 *
 * @param   string - the class for the
 *                   span.
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return SPANtag object.
 */
function html_span($class="") {
    if ( $class == "" ) {
        $attributes = NULL;
    } else {
        $attributes = array('class' => $class);
    }

    $arg_list = func_get_args();
    array_shift($arg_list);
    $obj = new SPANtag($attributes, $arg_list);
    return $obj;
}


/**
 * build a strong tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return STRONGtag object.
 */
function html_strong( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new STRONGtag;
    } else {
        $arg_list = func_get_args();
        return new STRONGtag(NULL, $arg_list);
    }
}

/**
 * build a style tag with some content.
 *
 * @param   string - the type
 *                   text/css (DEFAULT),
 *                   text/javasript
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return STYLEtag object.
 */
function html_style($type="text/css") {
    $attributes = array('type' => $type);
    $num_args = func_num_args();
    if ( $num_args==1 ) {
        $obj = new STYLEtag($attributes);
    } else {
        $arg_list = func_get_args();
        array_shift($arg_list);
        $obj = new STYLEtag($attributes, $arg_list);
    }
    return $obj;
}

/**
 * build a sub tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return SUBtag object.
 */
function html_sub( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new SUBtag;
    } else {
        $arg_list = func_get_args();
        return new SUBtag(NULL, $arg_list);
    }
}

/**
 * build a sup tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return SUPtag object.
 */
function html_sup( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new SUPtag;
    } else {
        $arg_list = func_get_args();
        return new SUPtag(NULL, $arg_list);
    }
}

/**
 * Build a TABLEtag object
 * with some of the attributes set
 *
 * @param mixed - width attribute
 *                default: 100%
 * @param mixed - border
 *                default: 0
 * @param mixed - cellspacing
 *                default: 0
 * @param mixed - cellpadding
 *                default: 0
 * @param string - align the align
 *                 attribute
 *                default: not set.
 * @return TABLEtag object.
 */
function html_table( $width="100%", $border="0",
                     $cellspacing="0",
                     $cellpadding="0",
                     $align=NULL) {
    return TABLEtag::factory($width, $border,
                             $cellspacing, $cellpadding,
                             $align);
}

/**
 * build a tbody tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return TBODYtag object.
 */
function html_tbody( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new TBODYtag;
    } else {
        $arg_list = func_get_args();
        return new TBODYtag(NULL, $arg_list);
    }
}



/**
 * build an td tag object with content.
 *
 * @param   string - the class to use
 * @param   string - the alignment
 *                   left, right
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return  TDtag object.
 */
function html_td($class="", $align="") {
    if ( $class == "" && $align == "" ) {
        $attributes = NULL;
    } else {
        $attributes = array();
        if ( $class != "" ) {
            $attributes["class"] = $class;
        }

        if ( $align != "" ) {
            $attributes["align"] = $align;
        }
    }

    $arg_list = func_get_args();
    array_shift($arg_list);
    array_shift($arg_list);
    $obj = new TDtag($attributes, $arg_list);
    return $obj;
}

/**
 * build a tfoot tag with content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return TFOOTtag object.
 */
function html_tfoot( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new TFOOTtag;
    } else {
        $arg_list = func_get_args();
        return new TFOOTtag(NULL, $arg_list);
    }
}


/**
 * build a <th>$header</th> tag.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return THtag object.
 */
function html_th( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new THtag;
    } else {
        $arg_list = func_get_args();
        return new THtag(NULL, $arg_list);
    }
}

/**
 * build a thhead tag.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return THEADtag object.
 */
function html_thead( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new THEADtag;
    } else {
        $arg_list = func_get_args();
        return new THEADtag(NULL, $arg_list);
    }
}


/**
 * build a title tag with some content.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return TITLEtag object.
 */
function html_title( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new TITLEtag;
    } else {
        $arg_list = func_get_args();
        return new TITLEtag(NULL, $arg_list);
    }
}

/**
 * build a tr tag and contents
 *
 * @param   string - class
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return TRtag object.
 */
function html_tr( $class="" ) {
    $tag = new TRtag;

    if ( $class != "" ) {
        $tag->set_class( $class );
    }

    $num_args = func_num_args();
    for ( $i=1;$i<$num_args;$i++ ) {
        $tag->add(func_get_arg($i));
    }
    return $tag;
}

/**
 * build a tt tag and contents
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return TTtag object.
 */
function html_tt() {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new TTtag;
    } else {
        $arg_list = func_get_args();
        return new TTtag(NULL, $arg_list);
    }
}

/**
 * build a u tag and contents
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return Utag object.
 */
function html_u( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new Utag;
    } else {
        $arg_list = func_get_args();
        return new Utag(NULL, $arg_list);
    }
}


/**
 * build a UL tag with content
 * wrapped in an LI tag.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return ULtag object.
 */
function html_ul( ) {
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

/**
 * build a var tag and contents
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return VARtag object.
 */
function html_var( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new VARtag;
    } else {
        $arg_list = func_get_args();
        return new VARtag(NULL, $arg_list);
    }
}


/**
 * build a xmp tag with some content..
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return XMPtag object.
 */
function html_xmp( ) {
    $num_args = func_num_args();
    if ( !$num_args ) {
        return new XMPtag;
    } else {
        $arg_list = func_get_args();
        return new XMPtag(NULL, $arg_list);
    }
}

/**
 * build a mailto url link .
 *
 * @author Walt A. Boring
 * @param   string $email - the email address
 *                          for the mailto
 * @param   string $subject - the subject for
 *                            the email
 * @param   string $body - the body conent
 *                         for the email
 * @param   string $cc = the cc email address.
 * @return CENTERtag object.
 */
function mailto($email, $subject=NULL, $body=NULL, $cc=NULL){

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

    return html_a($mailto, $email);
}

?>
