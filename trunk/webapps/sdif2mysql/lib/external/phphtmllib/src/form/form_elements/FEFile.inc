<?php
/**
 * This file contains the FileUpload FormElement class.
 *
 * $Id: FEFile.inc 2925 2007-09-13 03:08:29Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Dave Brondsema <dave@brondsema.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * This is the FileUpload FormElement which builds a
 * input field of type="file".  This automagically
 * handles the case of a confirmation page.
 *
 * @author Dave Brondsema <dave@brondsema.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEFile extends FEText {


    /**
     * The $_FILES information about
     * the submitted file.
     */
    protected $_files_info = array('name' => '',
                                   'type' => '',
                                   'size' => '',
                                   'tmp_name' => '');

    /**
     * The place where we temporarily save
     * the file during confirmation
     */
    protected $_temp_dir = "/tmp";

    /**
     * Array listing mime types to check for
     * during validation
     */
    protected $_valid_types = array();

    /**
     * max size in bytes determined by user
     *
     */
    protected $_max_size;

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    public function get_element() {
        $attributes = $this->build_element_attributes();
        $attributes["type"] = "file";

        if (($value = $this->get_value()) != NULL) {
            $attributes["value"] = $value;
        }

        $tag = new INPUTtag($attributes);

        return $tag;
    }

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates file size and partial uploads..
     * @return void
     */
    public function validate() {

        if ((isset($_REQUEST[FormProcessor::FORM_CONFIRM]) &&
            $_REQUEST[FormProcessor::FORM_CONFIRM] == 1) &&
            $this->is_required()) {
            //looks like we are in confirmation
            //we should have a populated array already.
            if ($this->_files_info['name']) {
                //we are ok
                return TRUE;
            } else {
                //something bogus happened here.
                Validator::error(ValidatorException::STR_EMPTY_UPLOAD_FILE);
            }
        }

        switch ($_FILES[$this->get_element_name()]['error']) {
        case 0:
            if ($_FILES[$this->get_element_name()]['size'] == 0 &&
                $this->is_required()) {
                Validator::error(ValidatorException::STR_EMPTY_UPLOAD_FILE);
            }
            break;
        case 1:
            Validator::error(ValidatorException::STR_FILE_MAX_SIZE, NULL,
                             array(ini_get("upload_max_filesize")));
            break;
        case 2:
            Validator::error(ValidatorException::STR_FILE_MAX_SIZE, NULL,
                             array($_REQUEST['MAX_FILE_SIZE']));
            break;
        case 3:
            Validator::error(ValidatorException::STR_FILE_PARTIAL_UPLOAD);
            break;
        case 4:
            //make sure that we are required to have a result
            if ($this->is_required()) {
                Validator::error(ValidatorException::STR_FILE_MISSING);
            } else {
                //we aren't required,
                //and we don't have a value.
                //this is a special case of
                //parent::do_validation
                return TRUE;
            }
            break;

        case 5:
            Validator::error(ValidatorException::STR_EMPTY_UPLOAD_FILE);
            break;
        }

        if (!empty($this->_valid_types)) {
            if (!in_array($_FILES[$this->get_element_name()]['type'], $this->_valid_types)) {
                Validator::error(ValidatorException::STR_FILE_TYPE_INVALID);
            }
        }

        if (!empty($this->_max_size)) {
            if ($_FILES[$this->get_element_name()]['size'] > $this->_max_size) {
                Validator::error(ValidatorException::STR_FILE_MAX_SIZE, NULL,
                                 array($this->_max_size));
            }
        }
    }

    /**
     * This function will return the
     * elements value
     *
     * @return mixed
     */
    public function get_value() {
        //do we need to repopulate
        //the file_info?
        if (isset($_REQUEST[FormProcessor::FORM_CONFIRM])) {
            if (empty($this->_files_info['name'])) {
                $this->_populate_file_info();
            }

            //let the FormContent do what they want.
            return $this->_files_info;
        } else {
            if (isset($_FILES[$this->get_element_name()]['name'])) {
                return $_FILES[$this->get_element_name()]['name'];
            } else {
                return '';
            }
        }
    }

    /**
     * returns the confirmation page's value
     *
     * @param mixed - the value to look up
     * @return string - the text associated
     */
    public function get_value_text() {
        if (empty($this->_files_info['name'])) {
            return '';
        } else {
            return $this->_files_info['name']." (".
                $this->_files_info['type'].") ".
                $this->_files_info['size']." bytes";
        }
    }

    /**
     * This is so we can save the file information
     * in a hidden form field during confirmation
     * page.
     *
     * @return string
     */
    protected function get_pre_confirm_value() {
        return urlencode(serialize($this->_files_info));
    }

    /**
     * This function will return this file's portion of the $_FILES array
     *
     * @return array
     */
    public function get_file_info() {
        return @$_FILES[$this->get_element_name()];
    }

    /**
     * This is so the user can set the temp directory
     * where the file will be saved during confirmation
     * (if any)
     *
     * @param string the new temp dir.
     */
    public function set_temp_dir($dir) {
        $this->_temp_dir = $dir;
    }

    /**
     * This is so the user can get the temp directory
     * where the file was saved during confirmation
     * (if any)
     *
     * @return string the new temp dir.
     */
    public function get_temp_dir() {
        return $this->_temp_dir;
    }


    /**
     * The function that allows us to save the
     * temp file someplace we can use it after
     * a confirmation has been accepted.
     *
     * NOTE: if the user doesn't confirm, then
     *       this could leave files in /tmp
     *
     */
    protected function _pre_confirm() {
        $name = $this->get_element_name();
        if (!empty($_FILES[$name]['name'])) {
            //ok we need to move the file so that the web
            //server doesn't nuke it once the request is done.
            $this->_files_info['name'] = $_FILES[$name]["name"];
            $this->_files_info['type'] = $_FILES[$name]['type'];
            $this->_files_info['size'] = $_FILES[$name]['size'];

            $tempname = tempnam($this->_temp_dir, get_class($this));
            $this->_files_info['tmp_name'] = str_replace($this->_temp_dir, '', $tempname);
            rename($_FILES[$name]['tmp_name'], $tempname);
        }

        return TRUE;
    }

    /**
     * This method re-populates the $this->_files_info
     * because the form had a confirmation page,
     * and the user accepted the confirmation.
     *
     * This is so we can re populate the local private var
     * so we can get access at the file data on disk.
     *
     */
    protected function _populate_file_info() {
        $this->_files_info = unserialize(urldecode($this->_value));
        $this->_value = $this->_files_info['name'];
        $this->_files_info['tmp_name'] = $this->_temp_dir.$this->_files_info['tmp_name'];
    }


    /**
     * This method returns the hidden version of this
     * element for a confirmation page.
     *
     * NOTE: This is called by the FormProcessor only.
     * It shouldn't be called manually.
     *
     * @return INPUTtag of type hidden
     */
    public function get_confirm_element() {
        return form_hidden($this->get_element_name(),
                           $this->get_pre_confirm_value() );
    }

    /**
     * This is so the user can create a list of mime types
     * to allow
     *
     * @param string a mime type to check for
     */
    public function add_valid_type($mime_type) {
        $this->_valid_types[] = $mime_type;
    }

    /**
     * This allows the user to set the max size of the file
     *
     * @param integer max size in bytes
     */
    public function set_max_size($max_size) {
        $this->_max_size = $max_size;
    }

    /**
     * This allows the user to get the max size of the file
     * (if any has been set)
     *
     * @return integer value of $_max_size if any
     */
    public function get_max_size($max_size) {
        return $this->_max_size;
    }
}

?>