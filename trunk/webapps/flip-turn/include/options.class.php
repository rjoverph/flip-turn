<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * Options classes.
 *
 * $Id$
 *
 * (c) 2007 by Mike Walsh
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package FlipTurn
 * @subpackage Options
 * @version $Revision$
 * @lastmodified $Date$
 * @lastmodifiedby $Author$
 *
 */

//error_reporting(E_ALL) ;

require_once("db.class.php") ;

/**
 * Class definition of the Swim Team Option Meta
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FlipTurnDBI
 */
class FlipTurnOptionMeta extends FlipTurnDBI
{
    /**
     * option meta id
     */
    var $__ometa_id ;

    /**
     * option meta key
     */
    var $__ometa_key ;

    /**
     * option meta value
     */
    var $__ometa_value ;

    /**
     * Set Option Meta Id
     *
     * @param int - $id - Id of the meta option
     */
    function setOptionMetaId($id)
    {
        $this->__ometa_id = $id ;
    }

    /**
     * Get Option Meta Id
     *
     * @return int - Id of the meta option
     */
    function getOptionMetaId()
    {
        return $this->__ometa_id ;
    }

    /**
     * Set Option Meta Key
     *
     * @param int - $key - Key of the meta option
     */
    function setOptionMetaKey($key)
    {
        $this->__ometa_key = $key ;
    }

    /**
     * Get Option Meta Key
     *
     * @return int - Key of the meta option
     */
    function getOptionMetaKey()
    {
        return $this->__ometa_key ;
    }

    /**
     * Set Option Meta Value
     *
     * @param int - $value - Value of the meta option
     */
    function setOptionMetaValue($value)
    {
        $this->__ometa_value = $value ;
    }

    /**
     * Get Option Meta Value
     *
     * @return int - Value of the meta option
     */
    function getOptionMetaValue()
    {
        return $this->__ometa_value ;
    }

    /**
     * Load Option Meta
     *
     * @param - string - $query - SQL query string
     */
    function loadOptionMeta($query = null)
    {
        if (is_null($query))
			die(sprintf("%s(%s):  %s", basename(__FILE__), __LINE__, "Null Query")) ;
        $this->setQuery($query) ;
        $this->runSelectQuery() ;

        // Make sure only one result is returned ...

        if ($this->getQueryCount() == 1)
        {
            $this->__ometa_record = $this->getQueryResult() ;

            //  Short cut to save typing ... 

            $om = &$this->__ometa_record ;

            $this->setOptionMetaId($om['ometaid']) ;
            $this->setOptionMetaKey($om['ometakey']) ;
            $this->setOptionMetaValue($om['ometavalue']) ;
        }
        else
        {
            $this->setOptionMetaId(null) ;
            $this->setOptionMetaKey(null) ;
            $this->setOptionMetaValue(null) ;
            $this->__ometa_record = null ;
        }

        return ($this->getQueryCount() == 1) ;
    }

    /**
     * Load Option Meta by Key
     *
     * @param - string - $key - option meta key
     */
    function loadOptionMetaByKey($key)
    {
        $query = sprintf("SELECT * FROM %s WHERE ometakey='%s'",
            FT_OPTIONS_META_TABLE, $key) ;

        return $this->loadOptionMeta($query) ;
    }

    /**
     * Load Option Meta by Meta Id
     *
     * @param - int - $id - option meta id
     */
    function loadOptionMetaByOMetaId($ometaid = null)
    {
        if (is_null($ometaid)) $ometaid = $this->getOptionMetaId() ;

        if (is_null($ometaid))
			die(sprintf("%s(%s):  %s", basename(__FILE__), __LINE__, "Null Id")) ;
        $query = sprintf("SELECT * FROM %s WHERE ometaid='%s'",
            FT_OPTIONS_META_TABLE, $ometaid) ;

        return $this->loadOptionMeta($query) ;
    }

    /**
     * check if a record already exists
     * by unique id in the user profile table
     *
     * @param - string - $query - SQL query string
     * @return boolean - true if it exists, false otherwise
     */
    function existOptionMeta($query = null)
    {
        if (is_null($query))
			die(sprintf("%s(%s):  %s", basename(__FILE__), __LINE__, "Null Query")) ;
        $this->setQuery($query) ;
        $this->runSelectQuery(false) ;

        return (bool)($this->getQueryCount()) ;
    }

    /**
     * Exist Option Meta by User Id and Key
     *
     * @param - int - $userid - user id
     * @param - string - $key - option meta key
     */
    function existOptionMetaByKey($key)
    {
        $query = sprintf("SELECT ometaid FROM %s
            WHERE ometakey='%s'", FT_OPTIONS_META_TABLE, $key) ;

        return $this->existOptionMeta($query) ;
    }

    /**
     * save a option meta record
     *
     * @return - integer - insert id
     */
    function saveOptionMeta()
    {
        $success = false ;

        if (is_null($this->getOptionMetaKey()))
			wp_die(sprintf("%s(%s):  %s", basename(__FILE__), __LINE__, "Null Key")) ;
        //  Update or new save?
 
        $update = $this->existOptionMetaByKey($this->getOptionMetaKey()) ;

        if ($update)
            $query = sprintf("UPDATE %s ", FT_OPTIONS_META_TABLE) ;
        else
            $query = sprintf("INSERT INTO %s ", FT_OPTIONS_META_TABLE) ;

        $query .= sprintf("SET 
            ometakey=\"%s\",
            ometavalue=\"%s\"",
            $this->getOptionMetaKey(),
            $this->getOptionMetaValue()) ;

        //  Query is processed differently for INSERT and UPDATE

        if ($update)
        {
            $query .= sprintf(" WHERE ometakey=\"%s\"", $this->getOptionMetaKey()) ;

            $this->setQuery($query) ;
            $success = $this->runUpdateQuery() ;
        }
        else
        {
            $this->setQuery($query) ;
            $this->runInsertQuery() ;
            $success = $this->setOptionMetaId($this->getInsertId()) ;
        }

        return $success ;
    }

    /**
     * Delete Option Meta data based on a query string
     *
     * @param - string - $query - SQL query string
     * @return - int - number of affected rows
     */
    function deleteOptionMeta($query = null)
    {
        if (is_null($query))
			die(sprintf("%s(%s):  %s", basename(__FILE__), __LINE__, "Null Query")) ;
        $this->setQuery($query) ;
        $status = $this->runDeleteQuery() ;

        return ($status) ;
    }

    /**
     * Update Option Meta by Key
     *
     * @param - string - $key - option meta key
     * @param - string - $value - option meta value
     * @return - int - number of affected rows
     */
    function globalUpdateOptionMetaByKey($key = null, $value = null)
    {
        if (is_null($key)) $key = $this->getOptionMetaKey() ;

        if (is_null($key))
			die(sprintf("%s(%s):  %s", basename(__FILE__), __LINE__, "Null option key.")) ;

        if (is_null($value)) $value = $this->getOptionMetaValue() ;

        if (is_null($value))
			die(sprintf("%s(%s):  %s", basename(__FILE__), __LINE__, "Null option value.")) ;

        $query .= sprintf("UPDATE %s SET ometavalue=\"%s\"
            WHERE ometakey=\"%s\"", FT_OPTIONS_META_TABLE, $value, $key) ;

        $this->setQuery($query) ;
        return $this->runUpdateQuery() ;
    }
}
?>
