<?php
/**
 * StandardTheme
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage css
 */

/**
 * This file builds a class that is used
 * to render the default/standard theme
 * css for the phphtmllib widgets
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage css
 */


class StandardTheme extends CSSContainer {

    public function __construct() {
        parent::__construct();

        //now add all of the CSS objects
        $this->add_css_objects();

        //now add the theme
        $this->add_theme();
    }

    public function request_vars() {
        return array();
    }


    /**
     * This method is used to add all of the desired 
     * phphtmllib CSS objects for theming
     * 
     * @return none
     */
    protected function add_css_objects() {
        $this->add( new InfoTableCSS(TRUE) );
        $this->add( new NavTableCSS );

        $this->add( new TextCSSNavCSS );
        $this->add( new TextNavCSS );
        $this->add( new VerticalCSSNavTableCSS );
        $this->add( new ImageThumbnailWidgetCSS );
        $this->add( new ActiveTabCSS );
        $this->add( new RoundTitleTableCSS );
        $this->add( new ButtonPanelCSS );
        $this->add( new TabListCSS );
        $this->add( new TabControlCSS );
        $this->add( new FooterNavCSS );
    }


    /**
     * This method is used to set/update the theme
     * colors which are diffs from the standard theme
     * settings that are defined in the CSS objects
     * 
     * @return none
     */
    protected function add_theme() {

    }
}

?>
