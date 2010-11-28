<?php

/**
 * This file contains various helper functions
 * for building forms and form elements.
 *
 * $Id: form_utils.inc 2162 2006-10-07 00:13:17Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 *
 *
 */


/**
 * render an form open tag only.
 * This is usefull for forms that are inside a table.
 * you would render the form tag first, then the table
 * with the form fields.
 * @param   string  $name - name attribute of the form tag.
 * @param   string  $action - the form action.
 * @param   string  $method - form method
 * @param   string  $attributes - any extra name='value' attributes for
 *                                the form tag.
 * @return  string  returns the raw form tag.
 */
function html_form( $name, $action, $method="GET", $attributes=array()) {

    $attribs = array("name" => $name, "action" => $action,
                     "method" => $method);
    $attributes = array_merge( $attribs, $attributes);

    return new FORMtag( $attributes );
}

/**
 * render an form open tag only.
 * This is usefull for forms that are inside a table.
 * you would render the form tag first, then the table
 * with the form fields.
 * @param   string  $name - name attribute of the form tag.
 * @param   string  $action - the form action.
 * @param   string  $method - form method
 * @param   string  $attributes - any extra name='value' attributes for
 *                                the form tag.
 * @return  string  returns the raw form tag.
 */
function form_open( $name, $action, $method="GET", $attributes=array(), $indent_level=0 ) {
    $form = html_form( $name, $action, $method, $attributes);
    return $form->_render_tag( $indent_level );
}


/**
 * render a form close tag
 *
 * @return  string - the </form> tag.
 */
function form_close( $indent_level=0 ) {
    $form = new FORMtag;

    //just render the close tag.
    return $form->_render_close_tag( $indent_level );
}



/**
 * build/render an input tag of type text
 *
 * @param   string  $name - the name of the input tag.
 * @param   string  $value - the value of the tag
 * @param   int     $size - the size in characters of the text tag
 * @param   int     $maxlength - the maximum @ of characters for the field
 * @param   array   $attributes - any extra name='value' pair attributes
 * @param   boolean $render_flag - render an object (FALSE) or raw html (TRUE);
 * @return  mixed   either returns an input object (default) or raw html.
 */
function form_text($name, $value=NULL, $size=NULL, $maxlength=NULL,
                   $attributes = array(), $render_flag=FALSE) {

    if ( $size != NULL ) {
        $attributes["size"] = $size;
    }
    if ( $maxlength != NULL ) {
        $attributes["maxlength"] = $maxlength;
    }

    $input = html_input("text", $name, $value, $attributes);

    if ( $render_flag ) {
        return $input->render();
    } else {
        //user wants the object
        return $input;
    }
}


/**
 * build/render an input tag of type password
 *
 * @param   string  $name - the name of the input tag.
 * @param   string  $value - the value of the tag
 * @param   int     $size - the size in characters of the text tag
 * @param   int     $maxlength - the maximum @ of characters for the field
 * @param   array   $attributes - any extra name='value' pair attributes
 * @param   boolean $render_flag - render an object (FALSE) or raw html (TRUE);
 * @return  mixed   either returns an input object (default) or raw html.
 */
function form_password($name, $value=NULL, $size=NULL, $maxlength=NULL,
                       $attributes = array(), $render_flag=FALSE) {

    if ( $size != NULL ) {
        $attributes["size"] = $size;
    }
    if ( $maxlength != NULL ) {
        $attributes["maxlength"] = $maxlength;
    }

    $input = html_input( "password", $name, $value, $attributes );

    if ( $render_flag ) {
        return $input->render();
    } else {
        //user wants the object
        return $input;
    }
}

/**
 * build/render an input tag of type button
 *
 * @param   string  $name - the name of the input tag.
 * @param   string  $value - the value of the tag
 * @param   array   $attributes - any extra name='value' pair attributes
 * @param   boolean $render_flag - render an object (FALSE) or raw html (TRUE);
 * @return  mixed   either returns an input object (default) or raw html.
 */
function form_button($name, $value=NULL, $attributes=array(), $render_flag=FALSE ) {

    $input = html_input( "button", $name, $value, $attributes );

    if ( $render_flag ) {
        return $input->render();
    } else {
        return $input;
    }

}

/**
 * build/render an input tag of type submit
 *
 * @param   string  $name - the name of the input tag.
 * @param   string  $value - the value of the tag
 * @param   array   $attributes - any extra name='value' pair attributes
 * @param   boolean $render_flag - render an object (FALSE) or raw html (TRUE);
 * @return  mixed   either returns an input object (default) or raw html.
 */
function form_submit($name, $value=NULL, $attributes=array(), $render_flag=FALSE ) {

    $input = html_input( "submit", $name, $value, $attributes );

    if ( $render_flag ) {
        return $input->render();
    } else {
        return $input;
    }
}

/**
 * build/render an input tag of type image
 *
 * @param   string  $name - the name of the input tag.
 * @param   string  $value - the value of the tag
 * @param   string  $src - the image src
 * @param   array   $attributes - any extra name='value' pair attributes
 * @param   boolean $render_flag - render an object (FALSE) or raw html (TRUE);
 * @return  mixed   either returns an input object (default) or raw html.
 */
function form_image($name, $value=NULL, $src, $attributes=array(), $render_flag=FALSE ) {

    $attributes["src"] = $src;
    $input = html_input( "image", $name, $value, $attributes );

    if ( $render_flag ) {
        return $input->render();
    } else {
        return $input;
    }
}


/**
 * build/render an input tag of type radio
 *
 * @param   string  $name - the name of the input tag.
 * @param   string  $value - the value of the tag
 * @param   array   $attributes - any extra name='value' pair attributes
 * @param   boolean $render_flag - render an object (FALSE) or raw html (TRUE);
 * @return  mixed   either returns an input object (default) or raw html.
 */
function form_radio($name, $value=NULL, $attributes=array(), $render_flag=FALSE ) {

    $input = html_input( "radio", $name, $value, $attributes );

    if ( $render_flag ) {
        return $input->render();
    } else {
        return $input;
    }
}

/**
 * build/render an set of radio buttons
 * with onClick javaScript selection
 *
 * @param   string  $name - the name of the input tag.
 * @param   array   $list - an array of text label = value pairs
 * @param   string  $value - the default value (the one that will be checked)
 * @param   bool $line_break - specify whether to put a line break after each radio button
 * @param   array   $attribs - specify addionnal attribs for each value
 * @return  object returns a container object
 * @author Suren Markosian
 */
function form_active_radio( $name, $list, $value, $line_break = TRUE, $attribs = FALSE) {

    $container = new Container();
    $i=0;
    while ( list($text,$val) = each($list) ) {
        if ( $attribs[$val] ) {
            $attr = $attribs[$val];
        } else {
            $attr = array();
        }

        if ( $val == $value ) $attr[] = "checked";
        $container->add(form_radio($name, $val, $attr));

        $link = new LABELtag(array("for" => $name), $text);

        $container->add($link);
        if ( $line_break ) $container->add(html_br());
        $i++;
    }
    return $container;
}


/**
 * build/render an input tag of type hidden
 *
 * @param   string  $name - the name of the input tag.
 * @param   string  $value - the value of the tag
 * @param   array   $attributes - any extra name='value' pair attributes
 * @param   boolean $render_flag - render an object (FALSE) or raw html (TRUE);
 * @return  mixed   either returns an input object (default) or raw html.
 */
function form_hidden($name, $value=NULL, $attributes=array(), $render_flag=FALSE ) {

    $input = html_input( "hidden", $name, $value, $attributes );

    if ( $render_flag ) {
        return $input->render();
    } else {
        return $input;
    }
}

/**
 * build/render an input tag of type CHECKBOX
 *
 * @param   string  $name - the name of the input tag.
 * @param   string  $value - the value of the tag
 * @param   array   $attributes - any extra name='value' pair attributes
 * @param   boolean $render_flag - render an object (FALSE) or raw html (TRUE);
 * @return  mixed   either returns an input object (default) or raw html.
 */
function form_checkbox($name, $value=NULL, $attributes=array(), $render_flag=FALSE ) {

    $input = html_input( "checkbox", $name, $value, $attributes );

    if ( $render_flag ) {
        return $input->render();
    } else {
        return $input;
    }
}

/**
 * build/render an input tag of type CHECKBOX
 * with onClick javaScript selection
 *
 * @param   string  $name - the name of the input tag.
 * @param   string  $value - the value of the tag
 * @param   string $text - text label for the checkbox
 * @param   string class - CSS class of the text
 * @return  object returns a container object
 * @author Suren Markosian
 */
function form_active_checkbox($name, $text=NULL, $value=1, $class = NULL, $onClick = NULL, $disabled=FALSE) {

    $e = new FECheckBox($name, $text);
    $e->set_value(1);
    $e->set_attribute('class', $class);
    $e->set_onClick($onClick);
    $e->set_disabled($disabled);

    return $e->get_element();

}


/**
 * build/render an html tag of file
 *
 * @param   string  $name - the name of the input tag.
 * @param   string  $value - the value of the tag
 * @param   array   $attributes - any extra name='value' pair attributes
 * @param   boolean $render_flag - render an object (FALSE) or raw html (TRUE);
 * @return  mixed   either returns an input object (default) or raw html.
 */
function form_file($name, $value=NULL, $attributes=array(), $render_flag=FALSE ) {

    $input = html_input( "file", $name, $value, $attributes );

    if ( $render_flag ) {
        return $input->render();
    } else {
        return $input;
    }
}


//odd html tags here.
//tags that are normally only used inside a form,
//so they live in the form_utils.php

/**
 * build a textarea tag with name and attributes.
 *
 * @author Walt A. Boring
 * @param   string  $name - the name of the textarea tag.
 * @param   string  $value - data to display in the textarea.
 * @param   array   $attributes - any extra name='value' pair attributes
 * @param   boolean $render_flag - render an object (FALSE) or raw html (TRUE);
 * @return TEXTAREAtag object.
 */
function form_textarea($name, $value=NULL, $attributes=array(), $render_flag=FALSE) {

    $attrib = array("name" => $name );
    $attributes = array_merge( $attrib, $attributes );

    $textarea = new TEXTAREAtag( $attributes );

    $textarea->newline_after_opentag = FALSE;
    $textarea->add( $value );

    return $textarea;
}

/**
 * Build a select tag with all of its option tags
 *
 * @author Walt A. Boring IV
 * @param   string  $name - name of the select.
 * @param   array   $options - an array of name value pairs for
 *                             the options.  the format is
 *                             array( "LABEL" => VALUE );
 *                             each <option value="VALUE"> LABEL </option>
 *                             ie
 *                             array( "test" => "foo")  would give an option
 *                             of <option value="foo"> test </option>
 *
 *                  NOTE: this also supports automatic building of
 *                        the optgroup. Just pass in an array of
 *                        array("foogroup" => array("name" => "value1",
 *                                                  "name2" => "value2"),
 *                              "bargroup" => array("blah" => "foo"));
 *
 *
 * @param   mixed  $selected - This can be either a string or an array.
 *                             If its a string then, it will be the selected
 *                             option value
 *                              <option value="foo" SELECTED>foo</option>
 *                             If it is an array, then all of the option
 *                             values will be marked as SELECTED.  This only
 *                             makes sense to do if the multiple_flag  is true.
 * @param   boolean $multiple_flag - is this a multiple selection select box?
 * @param   array   $attribs - additionnal attributes to the select tag
 * @return a SELECTtag object.
 */
function form_select($name, $options=array(), $selected="", $multiple_flag=FALSE, $attribs=false) {
    return SELECTtag::factory($name, $options, $selected, $multiple_flag, $attribs);
}

?>
