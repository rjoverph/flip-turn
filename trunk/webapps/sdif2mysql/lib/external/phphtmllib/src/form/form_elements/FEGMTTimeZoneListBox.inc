<?php
/**
 * This file contains the FEGMTTimeZoneListBox class
 *
 * $Id: FEGMTTimeZoneListBox.inc 2399 2007-02-22 21:38:46Z hemna $
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
 * This class is used to build a ListBox for
 * GMT timezone selection
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
class FEGMTTimeZoneListBox extends FEListBox {

    /**
     * The timezone selections
     */
    private $_zones=array("GMT -12 : Eniwetok, Kwajalein"=>-12,
                          "GMT -11 : Midway Islands, Samoa"=>-11,
                          "GMT -10 : Hawaii"=>-10,
                          "GMT -09 : Alaska"=>-9,
                          "GMT -08 : Pacific (USA, Canada), Tijuana"=>-8,
                          "GMT -07 : Arizona"=>-7,
                          "GMT -06 : Central (USA, Canada), Mexico"=>-6,
                          "GMT -05 : Bogota, Lima, Quito, East (USA, Canada)"=>-5,
                          "GMT -04 : Caracas, La Paz, Atlantic (Canada)"=>-4,
                          "GMT -03 : Terre Neuve, Brasilia, Georgetown"=>-3,
                          "GMT -02 : Atlantic Center"=>-2,
                          "GMT -01 : Azores"=>-1,
                          "GMT +00 : Casablanca, London, Dublin, Lisbon"=>0,
                          "GMT +01 : Paris, Amsterdam, Berlin, Rome, Vienna"=>1,
                          "GMT +02 : Athens, Bucharest, Riga, Cairo, Israel"=>2,
                          "GMT +03 : Nairobi, Moscow, Baghdad"=>3,
                          "GMT +04 : Abu Dhabi, Kabul"=>4,
                          "GMT +05 : Islamabad"=>5,
                          "GMT +06 : Colombo"=>6,
                          "GMT +07 : Bangkok, Hanoi, Jakarta"=>7,
                          "GMT +08 : Beijing, Hong Kong, Singapore, Taipei"=>8,
                          "GMT +09 : Tokyo, Seoul"=>9,
                          "GMT +10 : Sydney, Vladivostok"=>10,
                          "GMT +11 : New Caledonia"=>11,
                          "GMT +12 : Wellington"=>12);

    /**
     * The constructor
     *
     * @param string $label the label (default = 'Minutes')
     * @param boolean $required required or not
     */
    function __construct($label='TimeZone', $required=FALSE) {
        parent::__construct($label, $required, null,null, $this->_zones);
    }
}

?>