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
include_once("forms.class.php") ;
include_once("results.class.php") ;

/**
 * Construct the Results Purge form
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnSwimMeetForm
 */
class ResultsPurgeForm extends FlipTurnPurgeForm
{
    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements()
    {
        $this->setPurgeLabel('Purge Results') ;
        $this->setPurgeMessage('Purging the Results will delete all
            results currently stored in the database.  This action
            cannot be reversed.  Make sure all data has been saved
            appropriately prior to performing this action.') ;

        parent::form_init_elements() ;
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

        $result = new SwimResult() ;
        $result->PurgeResults() ;

        $this->set_action_message(sprintf("%d record%s purged from Results database.",
            $result->getAffectedRows(), $result->getAffectedRows() == 1 ? "" : "s")) ;

        unset($result) ;

        return $success ;
    }
}
?>
