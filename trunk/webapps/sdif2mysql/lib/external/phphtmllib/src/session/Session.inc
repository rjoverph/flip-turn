<?php
/**
 * base Session class
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Session
 */


/**
 * This class is a container for
 * doing sessions in php5
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Session
 */
abstract class Session {

    /**
     * This method has to be declared to register the
     * callback functions with the php internals 
     * handler.  i.e.
     * 
     * session_module_name('user');
     *  session_set_save_handler(
     *       array('MemcacheSession', 'open'),
     *       array('MemcacheSession', 'close'),
     *       array('MemcacheSession', 'read'),
     *       array('MemcacheSession', 'write'),
     *       array('MemcacheSession', 'destroy'),
     *       array('MemcacheSession', 'gc')
     *  );
     * 
     */
    abstract public static function init();


    /********************************************/
    /*        PHP 5 Callback functions          */
    /********************************************/

    /**
     * Open session.
     *
     * @param string the session save path from PHP
     * @param string the session name from PHP
     * @return boolean
     */
    abstract public static function open($path, $name);

    /**
     * Close the session.
     *
     */
    abstract public static function close();

    /**
     * Read session data from disk.
     *
     * @param string the session id
     * @return mixed.
     */
    abstract public static function read($id);

    /**
     *  Write new data to disk
     *
     * @param string the sessn id
     * @param array the session data
     * @return boolean
     */
    abstract public static function write($id, $data);

    /**
     * completely destroy the user's session
     *
     * @param string the session id to nuke
     */
    abstract public static function destroy($id);

    /* Garbage collection, deletes old sessions */
    abstract public static function gc($life);

}

?>