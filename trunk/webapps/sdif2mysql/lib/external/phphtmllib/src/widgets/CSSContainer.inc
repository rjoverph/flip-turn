<?php
/**
 * This file contains the CSSContainer widget
 *
 * $Id: CSSContainer.inc 2735 2007-05-16 06:01:18Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget 
 *
 */


/**
 * This class is a container for CSSBuilder
 * objects.  It is meant to make the 
 * theming of many CSSBuilder objects easy
 * to manage.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */ 
class CSSContainer extends HTMLWidget {

    /**
     * Only allow the adding of CSSBuilder
     * child classes
     *
     */
    function add() {
        $args = func_get_args();
        foreach( $args as $arg ) {
            if (is_subclass_of($arg, "CSSBuilder")) {
                parent::add( $arg );
            }
        }
    }


    /**
     * This walks all of the
     * CSSBuilder objects
     * and calls their respective update_all_values
     * method.
     *
     * NOTE: This must be called AFTER all the classes
     *       have been added.
     *
     * @param string - the property that the search lives in
     * @param string - the original value to find
     * @param string - the new value
     */
    function update_all_values( $property, $search, $value ) {

        $count = $this->count_content();
        for ($i=0; $i<$count; $i++) {
            $this->_content[$i]->update_all_values($property, $search, $value );
        }
    }

}
?>
