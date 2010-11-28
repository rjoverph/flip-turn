<?php
/**
 * This file contains the sdif2mysqlAjaxDefaultHTMLDataList
 * class.
 *
 * @package sdif2mysql
 */

/**
 * This class is a wrapper to automatically set the db
 * object to point to the sdif2mysql db.
 *
 * @package sdif2mysql
 */
abstract class sdif2mysqlAjaxDefaultHTMLDataList extends AjaxDefaultHTMLDataList  {
    /**
     * Get data list source
     *
     */
    protected function get_data_source() {
        $source = new DataBaseSQLDataListSource(sdif2mysqlDB::singleton());
        $this->set_data_source($source);
    }
}


?>
