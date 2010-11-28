<?php
/**
 * This file contains the main phphtmllib Log class
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Logging
 */

/**
 * The Log container
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Logging
 */

class Log {
    
    const   EMERG =  0;
    const   ALERT =  1; 
    const   CRIT =  2;
    const   ERR =  3;
    const   WARN =  4;
    const   NOTICE =  5;
    const   INFO =  6;
    const   DEBUG =  7;    
    
    
    protected $writers = array();
    
    /**
     * The constructor
     */
    public function __construct(LogWriter $writer=null) {
        if ($writer) {
            $this->add_writer($writer);
        }        
    }
    
    /**
     * Destructor to clean up
     */
    public function __destruct() {
        
    }
    
    /**
     * This is the singleton method for the Log
     * class.  Note this will only work for the very
     * first time singleton() is called.  typically
     * in init.inc to setup an app wide logger.
     * 
     * for example
     * $log = Log::singleton();
     * $log->add_writer(FileLogWriter::factory(realpath($GLOBALS["path_base"])."/logs/application.log", new LogFormatter));
     *
     * @return unknown
     */
    public static function singleton() {
        static $log = null;
        
        if ($log == null) {
            $log = new Log;
        }
        
        return $log;
    }
    
    public function add_writer(LogWriter $writer) {
        $this->writers[] = $writer;
    }
    
    /**
     * This is the main log function to log a message
     * 
     * @param int $priority
     * @param string $message
     * @param array $extra 
     */
    public function log(LogEvent $event) {
        foreach($this->writers as $writer) {
            $writer->log($event);
        }
    }
    
    
    
    /**
     * This method logs an Emergency event
     * 
     * @param string $message
     * @param Exception $exception
     */
    public function emerg($message, Exception $exception=null) {
        $this->log(LogEvent::factory(self::EMERG, $message, $exception));
    }
    
    /**
     * This method logs an Alert event
     * 
     * @param string $message
     * @param Exception $exception
     */
    public function alert($message, Exception $exception=null) {
        $this->log(LogEvent::factory(self::ALERT, $message, $exception));
    }
    
    /**
     * This method logs an Critical event
     * 
     * @param string $message
     * @param Exception $exception
     */
    public function crit($message, Exception $exception=null) {
        $this->log(LogEvent::factory(self::CRIT, $message, $exception));
    }
    
   /**
     * This method logs an Error event
     * 
     * @param string $message
     * @param Exception $exception
     */
    public function err($message, Exception $exception=null) {
        $this->log(LogEvent::factory(self::ERR, $message, $exception));
    }
    
    
   /**
     * This method logs an Warning event
     * 
     * @param string $message
     * @param Exception $exception
     */
    public function warning($message, Exception $exception=null) {
        $this->log(LogEvent::factory(self::WARN, $message, $exception));
    }
    
    
   /**
     * This method logs an Warning event
     * 
     * @param string $message
     * @param Exception $exception
     */
    public function notice($message, Exception $exception=null) {
        $this->log(LogEvent::factory(self::NOTICE, $message, $exception));
    }
    
   /**
     * This method logs an Warning event
     * 
     * @param string $message
     * @param Exception $exception
     */
    public function info($message, Exception $exception=null) {
        $this->log(LogEvent::factory(self::INFO, $message, $exception));
    }
    
   /**
     * This method logs an Warning event
     * 
     * @param string $message
     * @param Exception $exception
     */
    public function debug($message, Exception $exception=null) {
        $this->log(LogEvent::factory(self::DEBUG, $message, $exception));
    }
    
    
   
}
?>