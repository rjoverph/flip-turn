<?php

/**
 * This is the project generated home page
 *
 *
 * @package sdif2mysql
 *
 */


class HomePage extends sdif2mysqlPage {


    function __construct() {
        parent::__construct('Home Page');
    }

    public function request_vars() {
        return array();
    }

    /**
     * build the main content for the page
     * and return it all inside a container object
     *
     * @param Container object
     */
    function content_block() {

        $container = Container::factory();
        $container->add('Hello World to sdif2mysql', BRtag::factory(5));
        return $container;
    }

}
?>
