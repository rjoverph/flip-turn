<?php
/**
 *  This file contains the LogEvent object.
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Logging
 */
 

/**
 * This class is the LogEvent class
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Logging
 */
class LogEvent {
    
    /**
     * The timestamp when
     * the event happened.
     * @var integer
     */
    protected $timestamp;
    
    /**
     * the event priority
     * @var integer
     */
    protected $priority;
    
    /**
     * The event message
     * @var string
     */
    protected $message;
    
    /**
     * The Exception associated
     * with the event?
     * @var Exception
     */
    protected $exception;
    
    /**
     * any extra info associated
     * with the event.
     */
    protected $extra = array();

    /**
     * Class Constructor
     *
     * @param int $priority
     * @param string $message
     * @param Exception $exception
     */
    public function __construct($priority, $message, Exception $exception=null) {
        $this->timestamp = time();
        $this->priority = $priority;
        $this->message = $message;
        $this->exception = $exception;   
    }
    
    /**
     * Static version of the constructor
     * 
     * @param int $priority
     * @param string $message
     * @param Exception $exception
     * @param array $extra
     * @return LogEvent
     */
    public static function factory($priority, $message, Exception $exception=null, $extra=array()) {
        $e = new LogEvent($priority, $message, $exception);
        $e->set_extra($extra);
        
        return $e;
    }
    
    /**
     * This method is used to set any extra logging info.
     * The extra must be an array of key => value pairs
     * and the value must be a string.
     * 
     * @param array $extra
     */
    public function set_extra($extra=array()) {
        $this->extra = array_merge($this->extra, $extra);               
    }
    
    
    /**
     * This method is used to get the timestamp
     * When the log event happened.
     * 
     * @return integer
     */
    public function get_timestamp() {
        return $this->timestamp;
    }
    
    /**
     * This method is used to get the priority
     * of the event.
     * 
     * @return integer
     */
    public function get_priority() {
        return $this->priority;
    }
    
    /**
     * This method is used to get the message associated 
     * with an event.
     * 
     * @return string
     */
    public function get_message() {
        return $this->message;
    }
    
    /**
     * This method is used to get the Exception
     * that happened associated with the event.
     * 
     * @return Exception
     */
    public function get_exception() {
        return $this->exception;
    }
    
    /**
     * This method is used to get the extra 
     * array
     * 
     * @return array
     */
    public function get_extra() {
        return $this->extra;
    }
    
}
?>