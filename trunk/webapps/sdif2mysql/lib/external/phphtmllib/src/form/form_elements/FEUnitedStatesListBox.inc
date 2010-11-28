<?php
/**
 * This file contains the FEUnitedStatesListBox
 *
 * $Id: FEUnitedStatesListBox.inc 2399 2007-02-22 21:38:46Z hemna $
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
 * a select box for States of the U.S.A.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
class FEUnitedStatesListBox extends FEListBox {

    /**
     * The states array
     * @var array
     */
    private $_states = array("Select State" => "",
                             "Alabama" => "AL",
                             "Alaska" => "AK",
                             "Arizona" => "AZ",
                             "Arkansas" => "AR",
                             "California" => "CA",
                             "Colorado" => "CO",
                             "Connecticut" => "CT",
                             "Deleware" => "DE",
                             "District of Columbia" => "DC",
                             "Florida" => "FL",
                             "Georgia" => "GA",
                             "Hawaii" => "HI",
                             "Idaho" => "ID",
                             "Illinois" => "IL",
                             "Indiana" => "IN",
                             "Iowa" => "IA",
                             "Kansas" => "KS",
                             "Kentucky" => "KY",
                             "Louisiana" => "LA",
                             "Maine" => "ME",
                             "Maryland" => "MD",
                             "Massachusetts" => "MA",
                             "Michigan" => "MI",
                             "Minnesota" => "MN",
                             "Mississippi" => "MS",
                             "Missouri" => "MO",
                             "Montana" => "MT",
                             "Nebraska" => "NE",
                             "Nevada" => "NV",
                             "New Hampshire" => "NH",
                             "New Jersey" => "NJ",
                             "New Mexico" => "NM",
                             "New York" => "NY",
                             "North Carolina" => "NC",
                             "North Dakota" => "ND",
                             "Ohio" => "OH",
                             "Oklahoma" => "OK",
                             "Oregon" => "OR",
                             "Pennsylvania" => "PA",
                             "Rhode Island" => "RI",
                             "South Carolina" => "SC",
                             "South Dakota" => "SD",
                             "Tennessee" => "TN",
                             "Texas" => "TX",
                             "Utah" => "UT",
                             "Vermont" => "VT",
                             "Virginia" => "VA",
                             "Washington" => "WA",
                             "West Virginia" => "WV",
                             "Wisconsin" => "WI",
                             "Wyoming" => "WY",
                             "Puerto Rico" => "PR",
                             "Virgin Island" => "VI",
                             "Northern Mariana Islands" => "MP",
                             "Guam" => "GU",
                             "American Samoa" => "AS",
                             "Palau" => "PW",
                            );

    /**
     * The constructor
     *
     * @param string text label for the element
     * @param boolean is this a required element?
     * @param int element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int element height in px
     * @param array data_list - list of data elements (name=>value)
     */
    function __construct($label, $required = TRUE, $width = NULL, $height = NULL) {
        parent::__construct($label, $required, $width, $height, $this->_states);
    }
}

?>