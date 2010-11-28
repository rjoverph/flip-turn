<?php
/**
 * This file contains the FEEuropeanUnionListBox class
 *
 * $Id: FEEuropeanUnionListBox.inc 2399 2007-02-22 21:38:46Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * This class builds a FEDataList that shows
 * a select box for states of the European Union.
 * 
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
class FEEuropeanUnionListBox extends FEListBox {
    /**
     * The states array
     * @var array
     */
    private $_states = array("Select State" => "",
                             "Belgium" => "be",
                             "Denmark" => "dk",
                             "Germany" => "de",
                             "Greece" => "gr",
                             "Spain" => "es",
                             "France" => "fr",
                             "Ireland" => "ie",
                             "Italy" => "it",
                             "Luxembourg" => "lu",
                             "The Netherlands" => "nl",
                             "Austria" => "at",
                             "Portugal" => "pt",
                             "Finland" => "fi",
                             "Sweden" => "se",
                             "United Kingdom" => "uk",
                             "Czech Republic" => "cz",
                             "Estonia" => "ee",
                             "Cyprus" => "cy",
                             "Latvia" => "lv",
                             "Lithuania" => "lt",
                             "Hungary" => "hu",
                             "Malta" => "mt",
                             "Poland" => "pl",
                             "Slovenia" => "si",
                             "Slovakia" => "sk",
                            );

    /**
     * The constructor
     *
     * @param string $label text label for the element
     * @param boolean $required is this a required element?
     * @param int $width element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int $height element height in px
     *
     */
    function __construct($label, $required = TRUE, $width = NULL, $height = NULL) {
        parent::__construct($label, $required, $width, $height, $this->_states);
    }
}

?>