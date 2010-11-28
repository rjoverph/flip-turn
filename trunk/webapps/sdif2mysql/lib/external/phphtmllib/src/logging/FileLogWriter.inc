<?php
/**
 * This is the File Log Writer class that
 * logs entries to a file on disk
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Logging
 */
 

/**
 * This class logs entries to a file on disk.
 * 
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Logging
 */
class FileLogWriter extends LogWriter {

    /**
     * The file descriptor
     */
   protected $file_fd;
   
   /**
    * The filename we are working with
    * @var string
    */
   protected $filename;
   
   /**
    * The LogFormatter class
    * @var LogFormatter
    */
   protected $formatter;

    /**
     * Class Constructor
     *
     * @param string $filename
     * @param LogFormatter $formatter
     */
    public function __construct($filename, LogFormatter $formatter=null) {
        $this->open($filename);
        $this->formatter = $formatter;
        if ($formatter == null) {
            //lets set a default
            $this->formatter = new LogFormatter;
        }        
    }
    
    /**
     * The factory method
     * 
     * @param string $filename
     * @param LogFormatter $formatter
     */
    public static function factory($filename, LogFormatter $formatter=null) {
        return new FileLogWriter($filename, $formatter);         
    }
    
    /**
     *
     * The destructor to make sure we safely close the
     * file.
     */
    public function __destruct() {
        if ($this->file_fd) {
            fclose($this->file_fd);    
        }
    }
    
    /**
     * This is the abstract log function 
     * that is called from the Log class to
     * log an entry.
     * 
     * @param LogEvent $event
     * @return void
     */
    public function log(LogEvent $event) {
        fwrite($this->file_fd, $this->formatter->format($event)."\n");                        
    }
    
    
    
    /**
     * This method tries to open the file for append writing.
     * 
     * @param string $filename
     */
    protected function open($filename) {
        $this->filename = $filename;
        $this->file_fd = fopen($filename, "a");
        if (!$this->file_fd) {
            //oops something went wrong.
            throw new phphtmllibException("Failed to open logilfe for writing ".$filename, 
                                                                       phphtmllibException::LOG_FILE_WRITER_OPEN_FAILED);
        }
    }
}
?>