<?php
/**
 * This file contains the Timer class.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 */

/**
 * Simple timer class, can be used alone or as a parent
 * class for a more complicated timer
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 */
class Timer {
    /**
     * Time started in seconds
     * @var float
     */
    protected $time_start = 0;

    /**
     * Time stopped in seconds
     * @var float
     */
    protected $time_stop = 0;

    /**
     * Flag true if timer is not running
     * @var bool
     */
    private $stopped = FALSE;

    /**
     * The constructor.
     *
     * @param bool $start_flag TRUE will start the timer on class construction,
     *                         FALSE forces user to call the start() method
     *
     */
    function __construct($start_flag = FALSE) {
        if ($start_flag) {
            $this->start();
        }
    }

    /**
     * Starts the timer
     *
     * @return void
     */
    public function start() {
        $this->stopped = FALSE;
        $_time = explode(" ",microtime());
        $this->time_start = $_time[1] + $_time[0];
    }

    /**
     * Stops the timer
     *
     * @return void
     */
    public function stop() {
        $_time = explode(" ", microtime());
        $this->time_stop = $_time[1] + $_time[0];
        $this->stopped = TRUE;
    }

    /**
     * Returns the time started, in seconds
     *
     * @return float
     */
    public function get_time_start() {
        return $this->time_start;
    }

    /**
     * Returns the time stopped, in seconds
     *
     * @return float
     */
    public function get_time_stop() {
        return $this->time_stop;
    }

    /**
     * This function returns the elapsed time since stop()
     *
     * @return float
     */
    public function get_elapsed( ) {
        if (!$this->stopped) {
            $this->stop();
        }
        return $this->get_time_stop() - $this->get_time_start();
    }
}
?>