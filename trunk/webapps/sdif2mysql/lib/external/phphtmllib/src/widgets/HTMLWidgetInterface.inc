<?php
/**
 *
 * This file defines the HTMLWidgetInterface class.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */
interface HTMLWidgetInterface {

    public function set_title( $title );
    public function get_title();

    public function set_width( $width );
    public function get_width();

    public function set_align( $align );
    public function get_align();

    public function get_javascript();    
}
