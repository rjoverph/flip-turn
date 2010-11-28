<?php
/**
 * This file contains the TabControlCSS
 * object
 * 
 * @author Culley Harrelson <culley@fastmail.fm>
 * @package phpHtmlLib
 */


/**
 * CSS for the tab control
 *
 * @author Culley Harrelson <culley@fastmail.fm>
 * @package phpHtmlLib
 */
class TabControlCSS extends CSSBuilder {
    function user_setup() {

        $this->add_entry('.tabs', '',
                         array(
                             'float' => 'left',
                             'width' => '100%',
                             'background' => '#fff url("/phphtmllib/images/widgets/tabs_bg.gif") repeat-x bottom',
                             'font-size' => '1.0em',
                             'line-height' => 'normal',
                             'font-family' => 'Veranda, Arial, Helvetica, sans-serif',
                             'font-weight' => 'normal',
                             'font-size' => '12px',
                             'margin-top' => '10px',
                             'margin-bottom' => '10px'
                             )
                         );
        $this->add_entry('.tabs', 'ul',
                         array(
                             'margin' => '0',
                             'padding' => '3px 5px 0',
                             'list-style' => 'none'
                             )
                         );
        $this->add_entry('.tabs', 'li',
                         array(
                             'float' => 'left',
                             'background' => 'url("/phphtmllib/images/widgets/tab_left.gif") no-repeat left top',
                             'margin' => '0',
                             'padding' => '0 0 0 6px',
                             'border-bottom' => '1px solid #666'
                             )
                         );
        $this->add_entry('.tabs', 'a',
                         array(
                             'float' => 'left',
                             'display' => 'block',
                             'width' => '.1em',
                             'background' => 'url("/phphtmllib/images/widgets/tab_right.gif") no-repeat right top',
                             'padding' => '5px 6px 4px 2px',
                             'text-decoration' => 'none',
                             'font-weight' => 'bold',
                             'color' => '#666'
                             )
                         );
        $this->add_entry('.tabs', 'ul a', array('width' => 'auto'));
        $this->add_entry('.tabs', 'a:hover', array('color' => '#333'));
        $this->add_entry('.tabs', '.current', array('background-position' => '0 -150px', 'border-width' => '0'));
        $this->add_entry('.tabs', '.current a', array('background-position' => '100% -150px', 'padding-bottom' => '5px', 'color' => '#333'));
        $this->add_entry('.tabs', 'li:hover, .header li:hover a', array('background-position' => '0 -150px', 'color' => '#333'));
        $this->add_entry('.tabs', 'li:hover a', array('background-position' => '100% -150px'));
    }
}
?>
