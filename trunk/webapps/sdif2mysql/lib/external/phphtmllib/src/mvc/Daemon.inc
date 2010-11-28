<?php
/**
 * The Daemon class for
 * background jobs.
 *
 * @package phpHtmlLib-framework
 * @subpackage Controller
 */

/**
 * This class is used to daemonize a
 * process you don't want to run from Cron.
 *
 * NOTE: PHP must be compiled with
 * --enable-sigchild
 * --enable-pcntl
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Controller
 */
abstract class Daemon {
   /**
    * User ID
    */
   protected $user_id = 99;

   /**
    * Group ID
    */
   protected $group_id = 99;

   /**
    * Terminate when set identity fails?
    */
   protected $require_set_identity = false;

   /**
    * Path to PID file
    *
    * example:
    *  /tmp/mydaemon.pid
    */
   protected $pid_file;

   /**
    * Home path
    */
   protected $home_path = '/';

   /**
    * Current process ID
    */
   protected $pid = 0;

   /**
    * Is this process a child
    */
   protected $is_child = false;

   /**
    * Is daemon running
    */
   protected $is_running = false;

   /**
    * The number of times we have run
    * through schedule()
    */
    protected $run_count=0;

   /**
    * The maximum allowable runs through
    * the schedule() function.
    *  0 = infinite
    */
    protected $max_runs=0;


    /**
     * Because this isn't defined from
     * apache builds.
     */
    const SIGTERM = 15;
    const SIGCHLD = 17;
    const SIGSTOP = 19;
    
    
    /**
     * Holds the Log object for 
     * logging messages.
     */
    protected $log = null;

   /**
    * The constructor.
    *
    * @return void
    */
   public function __construct() {
       //allow the script to run forever.
       set_time_limit(0);
       //flush out output.
       @ob_implicit_flush();

       //generate the PID filename
       //bassed off of the child class.
       $this->pid_file = $this->generate_pid_filename();
       
       //initialize the logger
       $this->set_logger($this->get_logger());

       //something to clean stuff up.
       register_shutdown_function(array(&$this, 'release_daemon'));
   }

   /**
    * The task you want to
    * repeatedly execute.
    * If you need waits between
    * passes, then you have to
    * add them.
    *
    */
   abstract protected function do_task();


   /**
    * This method is used to generate
    * the PID filename based off of the
    * name of the child class.
    *
    * @return string
    */
   abstract public function generate_pid_filename();

   /**
    * Allow any initialization after we've been
    * daemonized.
    */
   abstract protected function init();

   /**
    * This method is required to allow the
    * daemon to cleanup any temp data/locks
    * it has in place.
    *
    * This is only called when start() is about
    * to return/exit.
    *
    */
   abstract protected function cleanup();
   
   
   /**
    * This method is used to initialize the
    * log class used.  
    */
   abstract protected function get_logger();
   
   
   /**
    * set the logger used by this class
    * 
    */
   protected final function set_logger(Log $log) {
   		$this->log = $log;
   }


   /**
    * Starts daemon
    *
    * @return boolean
    */
   public function start() {
      $this->log->debug('::start()');

      //if it fails, we'll have an exception thrown.
      //caller needs to deal w/ it.
      $this->daemonize();

      //init
      $this->init();

      $this->is_running = true;

      while ($this->is_running) {
          if ($this->max_runs == 0 || ($this->run_count < $this->max_runs)) {
              $this->do_task();
              $this->run_count++;
          } else {
              $this->log->info("::reached max run count ".$this->run_count. ' '.$this->max_runs);
              $this->disable();
          }
          //lets touch the pid file to prove we
          //are still running.
          $this->touch_pid_file();
      }

      //make sure we cleanly exit
      $this->cleanup();

      $this->log->debug('::start() exiting.');
      return true;
   }

   /**
    * This function tells the currently
    * instantiated daemon to stop
    * the next time through the main loop.
    *
    * @return void
    */
   protected final function disable() {
      $this->log->debug('::disable()');
      $this->is_running = false;
   }


   /**
    * This method tells an already running
    * daemon process to gracefully exit.
    * This method uses the process id file
    * created by the running instance to get
    * the process id.  Then it sends the TERM
    * signal to tell it to gracefully exit.
    *
    * @return boolean
    */
   public final function stop() {
       $this->log->debug('::stop() called');
       $running_pid = @file_get_contents($this->pid_file);

       if (!$running_pid) {
           throw new DaemonException(get_class($this)." Daemon isn't running",
                                     DaemonException::ERR_NOT_RUNNING);
       } else {
           //it's running, so lets stop it.
           if (!posix_kill(trim($running_pid), self::SIGTERM)) {
               throw new DaemonException(get_class($this)." Daemon process ".$running_pid." can't be killed! ",
                                         DaemonException::ERR_CANT_KILL);
           }
       }
   }

   /**
    * This method is used for setting the maximum
    * number of runs through the do_task()
    * to prevent memory leaks forever.
    *
    * @param int $max_runs
    *        0 = infinite.
    */
   public function set_max_runs($runs) {
       $this->max_runs = $runs;
   }

   /**
    * Daemonize
    *
    * Several rules or characteristics that most daemons possess:
    * 1) Check is daemon already running
    * 2) Fork child process
    * 3) Sets identity
    * 4) Make current process a session laeder
    * 5) Write process ID to file
    * 6) Change home path
    * 7) umask(0)
    *
    * @return boolean
    */
   protected final function daemonize() {
      @ob_end_flush();

      if ($this->is_daemon_running()) {
          // Deamon is already running. Exiting
          throw new DaemonException("Daemon already running.",
                                    DaemonException::ERR_ALREADY_RUNNING);
      }

      if (!$this->fork()) {
          // Coudn't fork. Exiting.
          throw new DaemonException("Can't fork into daemon.",
                                    DaemonException::ERR_CANT_FORK);
      }

      if (!$this->set_identity() && $this->require_set_identity) {
          // Required identity set failed. Exiting
          throw new DaemonException("Required Identity set failed.",
                                    DaemonException::ERR_SET_IDENTITY);
      }

      if (!posix_setsid()) {
          throw new DaemonException("Could not make the current process a session leader",
                                    DaemonException::ERR_SETSID_FAILED);
      }

      if (!$fp = @fopen($this->pid_file, 'w')) {
          throw new DaemonException("Could not write to PID file ".$this->pid_file,
                                    DaemonException::ERR_PID_FILE_ERROR);
      } else {
          //write the process id out to the PID file.
          fputs($fp, $this->pid);
          fclose($fp);
      }

      //go to the hom directory.
      @chdir($this->home_path);
      umask(0);

      declare(ticks = 1);

      //add a couple signal handlers
      //so we know when someone tries to kill us.
      pcntl_signal(self::SIGCHLD, array(&$this, 'sig_handler'));
      pcntl_signal(self::SIGTERM, array(&$this, 'sig_handler'));
      //pcntl_signal(SIGSTOP, array(&$this, 'sig_handler'));

      return true;
   }

   /**
    * Are we already running?
    */
   public function is_daemon_running() {
      $this->log->debug('::is_daemon_running()');
      $oldPid = @file_get_contents($this->pid_file);

      if ($oldPid !== false && posix_kill(trim($oldPid),0)) {
         return true;
      } else {
         return false;
      }
   }

   /**
    * This method actually
    * forks and creates the daemon
    * process.
    *
    * @return boolean.
    */
   protected final function fork() {
      $this->log->debug('::fork()');

      $pid = pcntl_fork();

      if ($pid == -1) {
          //oopsie.
          $this->log->err('::fork() - Could not fork');
          return false;
      } else if ($pid) {
          $this->log->err('::fork() - calling exit()');
          exit();
      } else {
          //children?
          $this->is_child = true;
          $this->pid = posix_getpid();
          return true;
      }
   }

   /**
    * Tries to set the identity of a daemon.
    *
    * @return bool
    */
   protected function set_identity() {
      if (!posix_setgid($this->group_id) || !posix_setuid($this->user_id)) {
         $this->log->err('::Could not set identity');

         return false;
      } else {
         return true;
      }
   }

   /**
    * This method is
    * the o.s. signal hander.
    *
    * @param int $signal
    */
   public function sig_handler($signal) {
      switch ($signal) {
      case self::SIGTERM:
            // Shutdown
            $this->log->info(__CLASS__.'::SIGTERM signal');
            //let the loop know we must quit
            $this->disable();
            break;

      case self::SIGSTOP:
            // Shutdown
            $this->log->info(__CLASS__.'::SIGSTOP signal');
            //let the loop know we must quit
            $this->disable();
          break;

      case self::SIGCHLD:
            // Halt
            $this->log->info(__CLASS__.' Child Halt signal');
            while (pcntl_waitpid(-1, $status, WNOHANG) > 0);
            break;
      }
   }

   /**
    * Releases daemon pid file
    * This method is called on exit to
    * clean up.
    *
    * @return void
    */
   public final function release_daemon() {
      if ($this->is_child && file_exists($this->pid_file)) {
         $this->log->debug('::Releasing daemon');

         //nuke the PID file.
         unlink($this->pid_file);
      }
   }


   /**
    * This function is a safe way to call
    * cleanup() from outside of the object.
    * This should make sure there aren't any
    * running versions of the daemon to be safe,
    * then calls cleanup
    *
    */
   public function clean() {
       if (!$this->is_daemon_running()) {
           $this->cleanup();
       }
   }


   /**
    * This updates the timestamp of the
    * process id file on disk
    * to let others we are running properly.
    *
    */
   protected function touch_pid_file() {
       if (!file_exists($this->pid_file)) {
           $this->log->info("::touch_pid_file() ".$this->pid_file." doesn't exist");
       }

       touch($this->pid_file, time());
   }         

}
?>
