<?php
/**
 * This file contains the main LogFormatter class.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Logging
 */


/**
 * This is the default LogFormatter
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Logging
 */
class LogFormatter {

    /**
     * The date string format
     * @var string
     */
    protected $date_format = DATE_RFC822;

    /**
     * The exception backtrace level.
     * This is how many backtrace entries you
     * want dumped
     * -1 = none
     * 0 = ALL
     * 1 = 1
     *
     * Default is 5
     * @var integer
     */
    protected $exception_backtrace_level = 5;

    /**
     * Class Constructor
     *
     * @param LogEvent $event
     */
    public function __construct() {
    }


    /**
     * This function is used to format the LogEvent
     * into a string.
     *
     * @param LogEvent $event
     * @return string
     */
    public function format(LogEvent $event) {
        $event_string = "";

        //first format the date and priority
        $event_string = '['.date($this->date_format, $event->get_timestamp()).'] '.
        $this->format_priority($event->get_priority()).' : ';

        //add the message
        $message = $event->get_message();
        if (is_string($message)) {
            $event_string .= $event->get_message();            
        } else {
            $event_string .= var_export($message, true);
        }
        

        //now try and deal with an exception
        $exception = $event->get_exception();
        if ($exception) {
            //we have an exception to dump.
            $event_string .= "\n    ".get_class($exception)."(".$exception->getCode().') : '.$exception->getMessage();
            if ($exception instanceOf phphtmllibException) {
                $event_string .= "\n    Extra : ".$exception->get_extra_as_string();
            }
             
            //backtrace
            if ($this->exception_backtrace_level > -1) {
                //we need to show the backtrace.
                $trace = $exception->getTraceAsString();
                $depth = $GLOBALS['config']->get('uncaught_exception_trace_depth',5);
                if ($depth) {
                    $depth = "#".$depth;
                    $end = strpos($trace, "\n", strpos($trace, $depth));
                    $trace = substr($trace, 0, $end);
                }
                
                $event_string .= "\n    Exception Backtrace : \n".$trace;
            }
        }
         
        //do we have any extra to dump?
        $extra_string = "";
        $extra = $event->get_extra();
        foreach($extra as $key => $value) {
            $extra_string .= $key ."=".$value."\n";
        }
        $event_string .= $extra_string;

        return $event_string;
    }


    /**
     * This method is used to set the date
     * format.
     *
     * @param mixed $format (either DATE_RFC822 or "H:i:s YMd")
     */
    public function set_date_format($format) {
        $this->date_format = $format;
    }


    /**
     * This method is used to transform the priority
     * into a human readable string.
     *
     * @param integer
     * @return string
     */
    public function format_priority($priority) {
        switch ($priority) {
            case Log::EMERG:
                $priority_string = "Emergency";
                break;
            case Log::ALERT:
                $priority_string = "Alert";
                break;
            case Log::CRIT:
                $priority_string = "Critical";
                break;
            case Log::ERR:
                $priority_string = "Error";
                break;
            case Log::WARN:
                $priority_string = "Warning";
                break;
            case Log::NOTICE:
                $priority_string = "Notice";
                break;
            case Log::INFO:
                $priority_string = "Info";
                break;
            case Log::DEBUG:
                $priority_string = "Debug";
                break;
        }

        return $priority_string;
    }


    /**
     * This method is used to set the
     * level of backtrace to dump in an
     * exception.
     *
     * @param integer $level
     *     NOTE: -1 = no backtrace, 0 = entire backtrace.
     */
    public function set_exception_backtrace_level($level) {
        $this->exception_backtrace_level = $level;
    }

}
?>