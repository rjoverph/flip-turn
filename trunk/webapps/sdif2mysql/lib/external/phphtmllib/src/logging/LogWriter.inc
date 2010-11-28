<?php
/**
 * This is the abstract class for the LogWriter
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Logging
 */


/**
 * This abstract class describes the interface
 * for the LogWriter
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Logging
 */
abstract class LogWriter {

    /**
     * This is the abstract log function
     * that is called from the Log class to
     * log an entry.
     *
     * @param LogEvent $event
     * @return void
     */
    abstract public function log(LogEvent $event);
}
?>