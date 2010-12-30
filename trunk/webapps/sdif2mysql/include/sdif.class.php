<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 *
 * $Id$
 *
 * SDIF Classes
 *
 * This information is based on the United States Swimming Interchange
 * format version 3 document revision F.  This document can be found on
 * the US Swimming web site at:  http://www.usaswimming.org/
 *
 * (c) 2010 by Mike Walsh
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage SDIF
 * @version $Revision$
 * @lastmodified $Date$
 * @lastmodifiedby $Author$
 *
 */

include_once('db.class.php') ;
include_once('sdif.include.php') ;

/**
 * SDIF record base class
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnDBI
 */
class SDIFRecord extends FlipTurnDBI
{
    /**
     * SDIF record storage
     */
    var $_sdif_record ;

    /**
     * SDIF record type
     */
    var $_sdif_record_type ;

    /**
     * Set SDIF record
     *
     * @param string SDIF record
     */
    function setSDIFRecord($rec)
    {
        $this->_sdif_record = $rec ;
    }
}

/**
 * SDIF record base class
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 */
class SDIFB1Record extends SDIFRecord
{
    /**
     * Org Code
     */
    var $_org_code ;

    /**
     * Future Use #1
     */
    var $_future_use_1 ;

    /**
     * Meet Name
     */
    var $_meet_name ;

    /**
     * Meet Address Line 1
     */
    var $_meet_address_1 ;

    /**
     * Meet Address Line 2
     */
    var $_meet_address_2 ;

    /**
     * Meet City
     */
    var $_meet_city ;

    /**
     * Meet State
     */
    var $_meet_state ;

    /**
     * Meet Postal Code
     */
    var $_meet_postal_code ;

    /**
     * Meet Country Code
     */
    var $_meet_country_code ;

    /**
     * Meet Code
     */
    var $_meet_code ;

    /**
     * Meet Start
     */
    var $_meet_start ;

    /**
     * Meet Start for database
     */
    var $_meet_start_db ;

    /**
     * Meet End
     */
    var $_meet_end ;

    /**
     * Meet End for database
     */
    var $_meet_end_db ;

    /**
     * Pool Altitude
     */
    var $_pool_altitude ;

    /**
     * Future Use #2
     */
    var $_future_use_2 ;

    /**
     * Course Code
     */
    var $_course_code ;

    /**
     * Future Use #3
     */
    var $_future_use_3 ;

    /**
     * Set Org Code
     *
     * @param int org code
     */
    function setOrgCode($code)
    {
        $this->_org_code = $code ;
    }

    /**
     * Get Org Code
     *
     * @return int org code
     */
    function getOrgCode()
    {
        return $this->_org_code ;
    }

    /**
     * Set Future Use 1
     *
     * @param string future use 1
     */
    function setFutureUse1($txt)
    {
        $this->_future_use_1 = $txt ;
    }

    /**
     * Get Future Use 1
     *
     * @return string future use 1
     */
    function getFutureUse1()
    {
        return $this->_future_use_1 ;
    }

    /**
     * Set Meet Name
     *
     * @param string meet name
     */
    function setMeetName($txt)
    {
        $this->_meet_name = $txt ;
    }

    /**
     * Get Meet Name
     *
     * @return string meet name
     */
    function getMeetName()
    {
        return $this->_meet_name ;
    }

    /**
     * Set Meet Address 1
     *
     * @param string meet address 1
     */
    function setMeetAddress1($txt)
    {
        $this->_meet_address_1 = $txt ;
    }

    /**
     * Get Meet Address 1
     *
     * @return string meet address 1
     */
    function getMeetAddress1()
    {
        return $this->_meet_address_1 ;
    }

    /**
     * Set Meet Address 2
     *
     * @param string meet address 2
     */
    function setMeetAddress2($txt)
    {
        $this->_meet_address_2 = $txt ;
    }

    /**
     * Get Meet Address 2
     *
     * @return string meet address 2
     */
    function getMeetAddress2()
    {
        return $this->_meet_address_2 ;
    }

    /**
     * Set Meet City
     *
     * @param string meet city
     */
    function setMeetCity($txt)
    {
        $this->_meet_city = $txt ;
    }

    /**
     * Get Meet City
     *
     * @return string meet city
     */
    function getMeetCity()
    {
        return $this->_meet_city ;
    }

    /**
     * Set Meet State
     *
     * @param string meet state
     */
    function setMeetState($txt)
    {
        $this->_meet_state = $txt ;
    }

    /**
     * Get Meet State
     *
     * @return string meet state
     */
    function getMeetState()
    {
        return $this->_meet_state ;
    }

    /**
     * Set Meet Postal Code
     *
     * @param string meet postal code
     */
    function setMeetPostalCode($txt)
    {
        $this->_meet_postal_code = $txt ;
    }

    /**
     * Get Meet Postal Code
     *
     * @return string meet postal code
     */
    function getMeetPostalCode()
    {
        return $this->_meet_postal_code ;
    }

    /**
     * Set Meet Country Code
     *
     * @param string meet country code
     */
    function setMeetCountryCode($txt)
    {
        $this->_meet_country_code = $txt ;
    }

    /**
     * Get Meet Country Code
     *
     * @return string meet country code
     */
    function getMeetCountryCode()
    {
        return $this->_meet_country_code ;
    }

    /**
     * Set Meet Code
     *
     * @param string meet code
     */
    function setMeetCode($txt)
    {
        $this->_meet_code = $txt ;
    }

    /**
     * Get Meet Code
     *
     * @return string meet code
     */
    function getMeetCode()
    {
        return $this->_meet_code ;
    }

    /**
     * Set Meet Start
     *
     * @param string meet start
     * @param boolean date provided in database format
     */
    function setMeetStart($txt, $db = false)
    {
        if ($db)
        {
            $this->_meet_start_db = $txt ;
 
            //  The meet start date is stored in YYYY-MM-DD in the database but
            //  SDIF B1 record expects it in MMDDYYYY format so the dates are
            //  reformatted appropriately.

            $date = &$this->_meet_start_db ;

            $this->_meet_start_db = sprintf("%02s%02s%04s",
                substr($date, 5, 2), substr($date, 8, 2), substr($date, 0, 4)) ;
        }
        else
        {
            $this->_meet_start = $txt ;
 
            //  The meet start date is stored in MMDDYYYY format in the SDIF B1
            //  record.  The database needs dates in YYYY-MM-DD format so the
            //  dates are reformatted appropriately.

            $date = &$this->_meet_start ;

            $this->_meet_start_db = sprintf("%04s-%02s-%02s",
                substr($date, 4, 4), substr($date, 0, 2), substr($date, 2, 2)) ;
        }
    }

    /**
     * Get Meet Start
     *
     * @param boolean date returned in database format
     * @return string meet start
     */
    function getMeetStart($db = true)
    {
        if ($db)
            return $this->_meet_start_db ;
        else
            return $this->_meet_start ;
    }

    /**
     * Set Meet End
     *
     * @param string meet end
     * @param boolean date provided in database format
     */
    function setMeetEnd($txt, $db = true)
    {
        if ($db)
        {
            $this->_meet_end_db = $txt ;
 
            //  The meet end date is stored in YYYY-MM-DD in the database but
            //  SDIF B1 record expects it in MMDDYYYY format so the dates are
            //  reformatted appropriately.

            $date = &$this->_meet_end_db ;

            $this->_meet_end_db = sprintf("%02s%02s%04s",
                substr($date, 5, 2), substr($date, 8, 2), substr($date, 0, 4)) ;
        }
        else
        {
            $this->_meet_end = $txt ;
 
            //  The meet end date is stored in MMDDYYYY format in the SDIF B1
            //  record.  The database needs dates in YYYY-MM-DD format so the
            //  dates are reformatted appropriately.

            $date = &$this->_meet_end ;

            $this->_meet_end_db = sprintf("%04s-%02s-%02s",
                substr($date, 4, 4), substr($date, 0, 2), substr($date, 2, 2)) ;
        }
    }

    /**
     * Get Meet End
     *
     * @param boolean date returned in database format
     * @return string meet end
     */
    function getMeetEnd($db = true)
    {
        if ($db)
            return $this->_meet_end_db ;
        else
            return $this->_meet_end ;
    }

    /**
     * Set Pool Altitude
     *
     * @param string pool altitude
     */
    function setPoolAltitude($txt)
    {
        $this->_pool_altitude = $txt ;
    }

    /**
     * Get Pool Altitude
     *
     * @return string pool altitude
     */
    function getPoolAltitude()
    {
        return $this->_pool_altitude ;
    }

    /**
     * Set Future Use 2
     *
     * @param string future use 2
     */
    function setFutureUse2($txt)
    {
        $this->_future_use_2 = $txt ;
    }

    /**
     * Get Future Use 2
     *
     * @return string future use 2
     */
    function getFutureUse2()
    {
        return $this->_future_use_2 ;
    }

    /**
     * Set Course Code
     *
     * @param string course code
     */
    function setCourseCode($txt)
    {
        $this->_course_code = $txt ;
    }

    /**
     * Get Course Code
     *
     * @return string course code
     */
    function getCourseCode()
    {
        return $this->_course_code ;
    }

    /**
     * Set Future Use 3
     *
     * @param string future use 3
     */
    function setFutureUse3($txt)
    {
        $this->_future_use_3 = $txt ;
    }

    /**
     * Get Future Use 3
     *
     * @return string future use 3
     */
    function getFutureUse3()
    {
        return $this->_future_use_3 ;
    }

    /**
     * Parse Record
     */
    function ParseRecord()
    {
        $c = container() ;
        $c->add(html_pre(FT_SDIF_COLUMN_DEBUG1,
            FT_SDIF_COLUMN_DEBUG2, $this->_sdif_record)) ;
        print $c->render() ;

        //  This doesn't work right and I am not sure why ...
        //  it ends reading data from the wrong character position.

        //$success = sscanf($this->_sdif_record, FT_SDIF_B1_RECORD,
        //    $this->_org_code,
        //    $this->_future_use_1,
        //    $this->_meet_name,
        //    $this->_meet_address_1,
        //    $this->_meet_address_2,
        //    $this->_meet_city,
        //    $this->_meet_state,
        //    $this->_meet_postal_code,
        //    $this->_meet_country_code,
        //    $this->_meet_code,
        //    $this->_meet_start,
        //    $this->_meet_end,
        //    $this->_pool_altitude,
        //    $this->_future_use_2,
        //    $this->_course_code,
        //    $this->_future_use_3) ;

        //  Extract the data from the SDIF record by substring position

        $this->setOrgCode(trim(substr($this->_sdif_record, 2, 1))) ;
        $this->setFutureUse1(trim(substr($this->_sdif_record, 3, 8))) ;
        $this->setMeetName(trim(substr($this->_sdif_record, 11, 30))) ;
        $this->setMeetAddress1(trim(substr($this->_sdif_record, 41, 22))) ;
        $this->setMeetAddress2(trim(substr($this->_sdif_record, 63, 22))) ;
        $this->setMeetCity(trim(substr($this->_sdif_record, 85, 20))) ;
        $this->setMeetState(trim(substr($this->_sdif_record, 105, 2))) ;
        $this->setMeetPostalCode(trim(substr($this->_sdif_record, 107, 10))) ;
        $this->setMeetCountryCode(trim(substr($this->_sdif_record, 117, 3))) ;
        $this->setMeetCode(trim(substr($this->_sdif_record, 120, 1))) ;
        $this->setMeetStart(trim(substr($this->_sdif_record, 121, 8))) ;
        $this->setMeetEnd(trim(substr($this->_sdif_record, 129, 8))) ;
        $this->setPoolAltitude(trim(substr($this->_sdif_record, 137, 4))) ;
        $this->setFutureUse2(trim(substr($this->_sdif_record, 141, 8))) ;
        $this->setCourseCode(trim(substr($this->_sdif_record, 149, 1))) ;
        $this->setFutureUse3(trim(substr($this->_sdif_record, 150, 10))) ;

        var_dump($this) ;
    }
}
?>
