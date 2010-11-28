<?php
/**
 * This file contains the Password FormElement class.
 *
 * 
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
 * This is the ConfirmPassword FormElement which builds a
 * input field of type="password".  It requires the caller
 * to add a FEPassword object to this class to have something
 * to compare during validation time.
 * It first validates that the value is_password(), and then
 * makes sure it matches exactly what the value is in
 * the FEPassword.
 *
 * USE: after u create the FEConfirmPassword, you MUST call
 * password() method which adds a reference to the FEPassword
 * object, so it can validate against.
 * 
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosian <suren@emicron.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
class FEConfirmPassword extends FEPassword {

    /**
     * This holds the FEPassword we are
     * trying to confirm
     */
    protected $fepassword = NULL;

    /**
     * use this function to add the
     * FEPassword object that we want
     * to confirm.
     *
     * @param FEPassword $fepassword
     */
    public function password(FEPassword &$fepassword) {
        $this->fepassword = &$fepassword;
    }

    /**
     * This function performs the actual validation
     * It is called only if the validation is required by
     * this element
     *
     * This function is responsible for performing complete
     * validation and setting the appropriate error message
     * in case of a failed validation
     *
     * @return void
     */
    public function validate() {
        Validator::is_password($this->get_value());

        if ($this->fepassword == NULL) {
            Validator::is_confirm_password($this->get_value(),
                                           NULL);
        }

        //looks like we have an FEPassword to confirm against
        Validator::is_confirm_password($this->get_value(),
                                       $this->fepassword->get_value());
    }
}

?>
