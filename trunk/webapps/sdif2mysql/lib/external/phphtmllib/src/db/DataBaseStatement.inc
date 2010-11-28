<?php
/**
 * This file contains the phphtmllib
 * framework DataBaseStatement object.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage DataBase
 */

/**
 * This class extends the built in php PDOStatement class
 * to provide a consistent API for the Data Objects
 * and to allow debugging.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage DataBase
 */
class DataBaseStatement extends PDOStatement {
    /**
     * The database handle
     * 
     */
    public $dbh;


    protected function __construct($dbh) {
       $this->dbh = $dbh;
       $this->setFetchMode(PDO::FETCH_OBJ);
    }
  
   public function fetch() {
       $ret = parent::fetch();

       //ddd('fetch called bitch!');
       return $ret;
   }
}
?>
