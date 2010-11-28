<?php
/**
 * This class is used for doing period 
 * scheduled tasks
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Controller
 */


/**
 * This class helps for doing repetetive
 * tasks that might be on a schedule.
 * 
 * Instead of running do_task() as fast
 * as possible, this puts a wait state
 * between each runs of do_task(). It has
 * a check to see if there are any local 
 * limits in place to prevent another pass
 * through the main loop, then calls
 * the child function schedule(), which 
 * does all the real work.
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Controller
 */
abstract class ScheduleDaemon extends Daemon {
    /**
     * The time in seconds between 
     * runs in the main loop.
     */
    protected $wait_period=1;

    /**
     * The default wait period in seconds.
     * This is used to reset the wait_period
     * back to the original value.
     */
    protected $wait_period_default=1;

    /**
     * The maximum value in seconds
     * we should ever wait between
     * loops.
     */
    protected $wait_period_max=60;

    /**
     * constructor
     */
    public function __construct() {
        parent::__construct();

        $this->generated_suppression_filename();
    }

    /**
     * This is the main function that
     * gets called every loop.
     *
     */
    abstract protected function schedule();

    /**
     * Are there any local limits we need to worry
     * about before running the schedule() method
     * for this time through the loop?
     *
     * @return boolean TRUE = can run another.
     */
    abstract protected function can_run();


    /**
     * This method is the main loop.
     *
     */
    protected function do_task() {
        //now do a wait state
        //so we aren't constantly running.
        $this->wait_state();

        //first check local limits
        if ($this->can_run()) {
            //we can run
            $this->log->info("::schedule()");

            //try and find a new item to work on.
            //and process it.
            $this->schedule();
        }
    }


    /**
     * the main start method.
     * We don't want to allow startup if the
     * suppression file exists on disk
     */
    public function start() {
        //make sure the suppression file doesn't exist
        if (file_exists($this->suppression_filename)) {
            $this->log->info('::start() not starting because of suppression file '.
                               $this->suppression_filename);
        } else {
            //it's ok to start.
            parent::start();
        }
    }

    /**
     * This method makes sure the the daemon
     * process is still running
     *
     * @param string the full path to the script
     *        ie. /usr/local/emaillabs/scripts/message_schedule.php
     */
    public function test_daemon($script) {
        $pid_filename = $this->generate_pid_filename();
        $this->log->info("::test_daemon() ".$pid_filename);

        if (file_exists($this->suppression_filename)) {
            $this->log->debug('::test_daemon() not starting because of suppression file '.
                               $this->suppression_filename);
            return;
        }

        //lets make sure it exists
        if (!file_exists($pid_filename)) {
            //it doesn't exist.  doh!
            try {
                $this->restart_daemon($script);
            } catch (Exception $e) {
                $this->log->warning("::test_daemon() ".$pid_filename." doesn't exist..restarted ".$script);
            }
            return;
        }

        $pid = trim(file_get_contents($pid_filename));

        //ok file exists...make sure it's still alive.
        $cmd = "ps --no-heading -p ".$pid." -o cmd | grep ".$script;
        $this->log->debug("::test_daemon() running  ".$cmd);
        $res = exec($cmd);
        if (strlen($res) <= 0) {
            try {
                $this->restart_daemon($script);
            } catch (Exception $e) {
                $this->log->warning(get_class($this)."::test_daemon() ".
                                    $pid_filename." wasn't running..restarted ".$script . " ".$e->getMessage());                                   
            }
        }
    }


    /**
     * This method is used to restart a Daemon process.
     *
     * @param string $script the script to restart
     */
    public function restart_daemon($script) {
        $cmd = "/usr/local/bin/php -f ".$script." </dev/null >/dev/null 2>&1";
        $this->log->info("::restart_daemon(".$script.") - ".$cmd);
        $output = '';
        $return = 0;
        exec($cmd, $output, $return);

        if ($return) {
            throw new DaemonException(get_class($this)."::restart_daemon() couldn't start the daemon ".
                                      print_r($output, true));
        }
    }

    /**
     * This method is used to suppress the starting of the daemon.
     * It writes a file to disk that start() looks for.
     *
     * Make sure you call enable_start() to clean up the file.
     */
    public function disable_start() {
        $this->log->info('::disable_start()');
        if (!touch($this->suppression_filename)) {
            throw new DaemonException(get_class($this).'::disable_start() failed to create suppression file - '.
                                               $this->suppression_filename);
        }
    }

    /**
     * This method is used to enable the starting of the
     * daemon.
     *
     */
    public function enable_start() {
        $this->log->info('::enable_start()');
        if (file_exists($this->suppression_filename)) {
            if (!unlink($this->suppression_filename)) {
                throw new DaemonException(get_class($this).'::disable_start() failed to create suppression file - '.
                                                   $this->suppression_filename);
            }
        }
    }


    /**
     * This method is used to pause the scheduler so
     * we aren't constantly running as fast as we can.
     *
     */
    protected function wait_state() {
        $this->log->debug("::wait_state() for ".$this->wait_period." seconds"); 
                           
        sleep($this->wait_period);
    }

    /**
     * Method for setting the next wait period
     *
     * @param int $seconds
     */
    public function set_wait_period($seconds) {
        //make sure this isn't larger then 
        //the maximum wait period allowed.
        if ($seconds > $this->wait_period_max) {
            $seconds = $this->wait_period_max;
        }
        $this->wait_period = $seconds;
    }

    /**
     * This method is used to reset the
     * wait period between main loop calls to
     * the default setting.
     *
     */
    protected function reset_wait_period() {
        $this->set_wait_period($this->wait_period_default);
    }

    /**
     * This method builds the suppression filename
     * based off of the pid filename.
     *
     * It assumes the pid filename ends with .pid
     *
     */
    protected final function generated_suppression_filename() {
        $this->suppression_filename = str_replace('.pid', '.suppress', $this->pid_file);
    }
}
?>
