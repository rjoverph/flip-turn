<?php

/**
 * This file contains the SOAPable interface
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage SOAP
 */

/**
 * This interface describes which
 * BusinessObjects want to automatically
 * generate a child class to export a 
 * SOAPAPI.  All of set_* methods in the
 * parent class will be rewritten in the
 * SOAPAPI generated object to include the
 * obj id.
 * 
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage SOAP
 */
interface SOAPable {

    /**
     * This function is used to register
     * which functions can be 
     * exported as a SOAP request
     *
     * @return array
     */
    public static function soap_api();
}
