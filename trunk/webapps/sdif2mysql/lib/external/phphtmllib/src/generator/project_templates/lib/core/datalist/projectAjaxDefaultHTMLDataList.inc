<?php
/**
 * This file contains the XX_PROJECT_DL_NAME_XX
 * class.
 *
 * @package XX_PROJECT_NAME_XX
 */

/**
 * This class is a wrapper to automatically set the db
 * object to point to the XX_PROJECT_NAME_XX db.
 *
 * @package XX_PROJECT_NAME_XX
 */
abstract class XX_PROJECT_DL_NAME_XX extends AjaxDefaultHTMLDataList  {
    /**
     * Get data list source
     *
     */
    protected function get_data_source() {
        $source = new DataBaseSQLDataListSource(XX_PROJECT_DB_NAME_XX::singleton());
        $this->set_data_source($source);
    }
}


?>
