<?php
/**
 * This file contains the ErrorBoxWidgetCSS
 * object
 * 
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */

/**
 * This class defines the css used by the
 * TextNav Object.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
class ErrorBoxWidgetCSS extends CSSBuilder {

    function user_setup() {

        $this->add_entry('.errorbox', '',
                         array('border' => '1px outset #aaaaaa;',
                               'background-color' =>  '#efefef'));

        $this->add_entry('.errorbox', '.errortitle',
                         array('color' => '#FF0000'));

        $this->add_entry('.errorbox', '.errorseparator',
                         array('border-bottom' => '1px solid #afafaf',
                               'padding' => '5px'));

        $this->add_entry('.errorbox', '.errorcell',
                         array('font-family' => 'ariel',
                               'size' => '10pt',
                               'padding' => '3px',
                               'white-space' => 'nowrap'));

        $this->add_entry('.errorbox', '.errormessage',
                         array('text-align' => 'center',
                               'padding-top' => '10px',
                               'padding-bottom' => '10px'));
    }
}


?>
