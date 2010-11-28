<?php
/**
 * This file contains the PageWidget class
 *
 * $Id: HTMLFramesetPage.inc 2733 2007-05-16 05:59:16Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */

/**
 * This class is used to build a frameset
 * only page..
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
abstract class HTMLFramesetPage extends HTMLPage {

    /**
     * have to extend this to not force the child
     * to declare it.
     *
     * @return none
     */
    protected function body_content() {
        return NULL;
    }

    /**
     * This function is used to save
     * a frameset to the page.  This will
     * automatically output a properly
     * formatted frameset.
     *
     * If you don't want/need a frameset
     * just return NULL;
     *
     */
    abstract protected function frameset();

    /**
     * This is the function that renders the HTML
     * for this widget.
     *
     * @return string - the HTML
     */
    public function render() {

        //test to see if they want debugging of
        //output enabled.
        if ( $this->_enable_debug ) {
            if ( isset($_GET["debug"]) ) {
                $this->set_text_debug( TRUE );
            }
        }

        //see if we have permissions to build the
        //content for this page.  If permissions checks
        //aren't allowed, this will pass.
        if ($this->has_permission()) {
            //check to see if they want to render a frameset
            $frameset = $this->frameset();
            //add and set the page output
            //to be a frameset.
            $this->set_frameset( $frameset );

            //Lets see if they have any javascript
            //for the head
            $js = $this->head_javascript();
            if ( $js != NULL ) {
                $this->add_head_js( $js );
            }
        } else {
            $this->add( html_br(), $this->_permission_box);
        }

        return parent::render();
    }
}

?>
