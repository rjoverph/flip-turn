<?php

/**
 * This is the project generated home page
 *
 *
 * @package XX_PROJECT_NAME_XX
 *
 */


class HomePage extends XX_PROJECT_CLASS_NAME_XXPage {


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
        $container->add('Hello World to XX_PROJECT_NAME_XX', BRtag::factory(5));
        return $container;
    }

}
?>
