<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 *
 * $Id$
 *
 * SDIF form classes.  These classes manage the
 * entry and display of the various forms used
 * by the Flip-Turn web application.
 *
 * (c) 2010 by Mike Walsh for FlipTurn.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage forms
 * @version $Revision$
 * @lastmodified $Date$
 * @lastmodifiedby $Author$
 *
 */

/**
 * Include the Form Processing objects
 *
 */
include_once("db.include.php") ;
include_once("queue.class.php") ;
include_once("forms.class.php") ;

/**
 * Construct the Swim Meet Import Results form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnSwimMeetForm
 */
class SDIFFileUploadForm extends FlipTurnFileUploadForm
{
    /**
     * This method gets called after the FormElement data has
     * passed the validation.  This enables you to validate the
     * data against some backend mechanism, say a DB.
     *
     */
    function form_backend_validation()
    {
        //   Need to make sure file contains meet results.
        //
        //   What is a results file?
        //
        //   -  1 A0 record
        //   -  1 B1 record
        //   -  1 B2 record (optional)
        //   -  1 or more C1 records
        //   -  1 or more C2 records
        //   -  0 or more D0 records
        //   -  0 or more D3 records
        //   -  0 or more G0 records
        //   -  0 or more E0 records
        //   -  0 or more F0 records
        //   -  0 or more G0 records
        //   -  1 Z0 record
        //
        //  A results file can contain results for more than
        //  one team - so what to do if that happens?

        $legal_records = array("A0" => 1, "B1" => 1, "B2" => 0,
            "C1" => 1, "C2" => 0, "D0" => 0, "D3" => 0, "G0" => 0,
            "E0" => 0, "F0" => 0, "Z0" => 1) ;
 
        $record_counts = array("A0" => 0, "B1" => 0, "B2" => 0,
            "C1" => 0, "C2" => 0, "D0" => 0, "D3" => 0, "G0" => 0,
            "E0" => 0, "F0" => 0, "Z0" => 0) ;
 
        $file = $this->get_element("SDIF Filename") ; 
        $fileInfo = $file->get_file_info() ; 

        $lines = file($fileInfo['tmp_name']) ; 

        //  Scan the records to make sure there isn't something odd in the file

        $line_number = 1 ;

        foreach ($lines as $line)
        {
            if (trim($line) == "") continue ;

            $record_type = substr($line, 0, 2) ;

            if (!array_key_exists($record_type, $legal_records))
            {
                $this->add_error("SDIF Filename", sprintf("Invalid record \"%s\" encountered in SDIF file on line %s.", $record_type, $line_number)) ;
                return false ;
            }
            else
            {
                $record_counts[$record_type]++ ;
            }

            $line_number++ ;
        }

        //  Got this far, the file has the right records in it, do
        //  the counts make sense?
        
        foreach ($record_counts as $record_type => $record_count)
        {
            if ($record_count < $legal_records[$record_type])
            {
                $this->add_error("SDIF Filename", sprintf("Missing required \"%s\" record(s) in SDIF file.", $record_type)) ;
                return false ;
            }
        }

        unset($lines) ; 

	    return true ;
    }

    /**
     * This method is called ONLY after ALL validation has
     * passed.  This is the method that allows you to 
     * do something with the data, say insert/update records
     * in the DB.
     */
    function form_action()
    {
        $success = true ;

        $file = $this->get_element($this->getUploadFileLabel()) ; 
        $fileInfo = $file->get_file_info() ; 

        $this->set_file_info($fileInfo) ; 
        $this->set_file_info_table($fileInfo) ; 

        //  Read the file contents for processing
 
        $lines = file($fileInfo['tmp_name']) ; 

        $line_number = 1 ;
        $record = array() ;

        //  Establish a database connection
 
        $sdifqueue = new SDIFQueue() ;
        $sdifqueue->openConnection() ;

        //  Need a record set to work with

        $rs = $sdifqueue->getEmptyRecordSet() ;

        //  Process each line in the file, adding it to the SDIF queue

        foreach ($lines as $line)
        {
            if (trim($line) == "") continue ;

            $record_type = substr($line, 0, 2) ;
            $record["linenumber"] = $line_number ;
            $record["recordtype"] = $record_type ;
            $record["sdifrecord"] = trim($line) ;

            $sql = $sdifqueue->getConnection()->GetInsertSQL($rs, $record) ;

            $sdifqueue->setQuery($sql) ;
            $sdifqueue->runInsertQuery() ;

            $line_number++ ;
        }

        $sdifqueue->closeConnection() ;

        unset($sdifqueue) ;

        //  Delete the file so we don't keep a lot of stuff around. 

        if (!unlink($fileInfo['tmp_name'])) 
            $this->add_error($this->getUploadFileLabel(),
                "Unable to remove uploaded file."); 

        $this->set_action_message("File \"" . 
            $this->get_element_value($this->getUploadFileLabel()) .
            "\" successfully uploaded.") ; 

        return $success ;
    }
}

/**
 * Construct the SDIF Queue Purge form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnSwimMeetForm
 */
class SDIFQueuePurgeForm extends FlipTurnForm
{
    /**
     * Label
     */
    var $_confirm_label = "Purge SDIF Queue" ;

    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        $confirm = new FECheckBox($this->_confirm_label) ;
        $this->add_element($confirm) ;
    }

    /**
     * This method is called only the first time the form
     * page is hit.  This enables u to query a DB and 
     * pre populate the FormElement objects with data.
     *
     */
    function form_init_data()
    {
    }

    /**
     * This is the method that builds the layout of where the
     * FormElements will live.  You can lay it out any way
     * you like.
     *
     */
    function form_content()
    {
        $table = html_table($this->_width,0,4) ;
        $table->set_style("border: 0px solid") ;

        $msg = html_div("ft_form_msg") ;
        $msg->add(html_p("Purging the SDIF Queue will delete all records
            currently stored in the SDIF Queue.  This action cannot be
            reversed.  Make sure all data has been saved appropriately
            prior to performing this action.", html_br())) ;

        $table->add_row($msg) ;
        $table->add_row($this->element_form($this->_confirm_label)) ;

        $this->add_form_block(null, $table) ;
    }

    /**
     * This method gets called after the FormElement data has
     * passed the validation.  This enables you to validate the
     * data against some backend mechanism, say a DB.
     *
     */
    function form_backend_validation()
    {
        $valid = true ;

        //  User must tick the checkbox to proceed!

        if (is_null($this->get_element_value($this->_confirm_label)))
        {
            $valid = false ;
            $this->add_error($this->_confirm_label, "Checkbox not selected.") ;
        }

	    return $valid ;
    }

    /**
     * This method is called ONLY after ALL validation has
     * passed.  This is the method that allows you to 
     * do something with the data, say insert/update records
     * in the DB.
     */
    function form_action()
    {
        $success = true ;

        $sdifqueue = new SDIFQueue() ;
        $sdifqueue->PurgeQueue() ;

        $this->set_action_message(sprintf("%d record%s purged from SDIF Queue.",
            $sdifqueue->getAffectedRows(), $sdifqueue->getAffectedRows() == 1 ? "" : "s")) ;

        unset($sdifqueue) ;

        return $success ;
    }

    /**
     * Overload form_content_buttons() method to have the
     * button display "Confirm" instead of the default "Save".
     *
     */
    function form_content_buttons()
    {
        return $this->form_content_buttons_Confirm_Cancel() ;
    }
}

/**
 * Construct the SDIF Queue Process form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnSwimMeetForm
 */
class SDIFQueueProcessForm extends FlipTurnForm
{
    /**
     * Label
     */
    var $_confirm_label = "Process SDIF Queue" ;

    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        //  Swimmer handling
        $swimmer = new FERadioGroup("Swimmers",
            array(
                ucfirst(FT_CREATE) => FT_CREATE
               ,ucfirst(FT_IGNORE) => FT_IGNORE)) ;
        $swimmer->set_br_flag(false) ;
        $this->add_element($swimmer) ;

        //  Swim Meets handling
        $swimmeets = new FERadioGroup("Swim Meets",
            array(
                ucfirst(FT_CREATE) => FT_CREATE
               ,ucfirst(FT_IGNORE) => FT_IGNORE)) ;
        $swimmeets->set_br_flag(false) ;
        $this->add_element($swimmeets) ;

        //  Swim Teams handling
        $swimteams = new FERadioGroup("Swim Teams",
            array(
                ucfirst(FT_CREATE) => FT_CREATE
               ,ucfirst(FT_IGNORE) => FT_IGNORE)) ;
        $swimteams->set_br_flag(false) ;
        $this->add_element($swimteams) ;
    }

    /**
     * This method is called only the first time the form
     * page is hit.  This enables u to query a DB and 
     * pre populate the FormElement objects with data.
     *
     */
    function form_init_data()
    {
        $this->set_element_value("Swimmers", FT_CREATE) ;
        $this->set_element_value("Swim Meets", FT_CREATE) ;
        $this->set_element_value("Swim Teams", FT_CREATE) ;
    }

    /**
     * This is the method that builds the layout of where the
     * FormElements will live.  You can lay it out any way
     * you like.
     *
     */
    function form_content()
    {
        $table = html_table($this->_width,0,4) ;
        $table->set_style("border: 0px solid") ;

        $msg = html_div("ft_form_msg") ;
        $msg->add(html_p(html_b("Processing the SDIF Queue requires
            processing swimmers, swim meets, and/or swim teams which are
            not currently stored in the database.  Specify how unknown
            data should be processed."), html_br())) ;

        $td = html_td(null, null, $msg) ;
        $td->set_tag_attribute("colspan", "2") ;
        $table->add_row($td) ;
        $table->add_row($this->element_label("Swimmers"), $this->element_form("Swimmers")) ;
        $table->add_row($this->element_label("Swim Meets"), $this->element_form("Swim Meets")) ;
        $table->add_row($this->element_label("Swim Teams"), $this->element_form("Swim Teams")) ;

        $this->add_form_block(null, $table) ;
    }

    /**
     * This method gets called after the FormElement data has
     * passed the validation.  This enables you to validate the
     * data against some backend mechanism, say a DB.
     *
     */
    function form_backend_validation()
    {
        $sdifqueue = new SDIFQueue() ;
        $valid = $sdifqueue->ValidateQueue() ;
        unset($sdifqueue) ;

	    return $valid ;
    }

    /**
     * This method is called ONLY after ALL validation has
     * passed.  This is the method that allows you to 
     * do something with the data, say insert/update records
     * in the DB.
     */
    function form_action()
    {
        $success = true ;

        $sdifqueue = new SDIFQueue() ;
        $sdifqueue->ProcessQueue() ;

        $this->set_action_message(sprintf("%d record%s purged from SDIF Queue.",
            $sdifqueue->getAffectedRows(), $sdifqueue->getAffectedRows() == 1 ? "" : "s")) ;

        unset($sdifqueue) ;

        return $success ;
    }

    /**
     * Overload form_content_buttons() method to have the
     * button display "Confirm" instead of the default "Save".
     *
     */
    function form_content_buttons()
    {
        return $this->form_content_buttons_Confirm_Cancel() ;
    }
}
?>