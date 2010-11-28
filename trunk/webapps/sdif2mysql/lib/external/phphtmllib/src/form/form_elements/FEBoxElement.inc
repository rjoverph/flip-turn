<?php
/**
 * This file contains the base FEBoxElement class
 *
 * $Id: FEBoxElement.inc 1821 2006-08-03 23:52:31Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * This is the Box FormElement which builds a
 * DIV with a width and a height.  It is a base
 * class for more complicated FormElements.
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
abstract class FEBoxElement extends FormElement {

    /**
     * Holds the width of the element
     *
     */
    protected $_width = NULL;

    /**
     * Holds the height of the element
     *
     */
    protected $_height = NULL;

    /**
     * The constructor
     *
     * @param label string - text label for the element
     * @param bool required - is this a required element
     * @param int required - element width in pixels (px), percentage (%) or elements (em)
     * @param int required - element height in pixels (px), percentage (%) or elements (em)
     */
    function __construct($label, $required = TRUE, $width = NULL, $height = NULL) {
        parent::__construct($label, $required);

        if ($width != NULL) {
            if (is_numeric($width)) {
                $this->set_attribute("size", $width);
            }
            else {
                $this->set_style_attribute("width", $width);
            }

            $this->_width = $width;
        }

        if ($height != NULL) {
            $this->set_style_attribute("height", $height);
            $this->_height = $height;
        }
    }
}

?>