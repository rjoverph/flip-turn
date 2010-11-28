<?php

/**
 * This contains the FooterNav widget and
 * the FooterNavCSS widget.
 *
 * $Id: FooterNav.inc 2736 2007-05-16 06:02:12Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 *
 */

/**
 * Use this class to render footer navigation that
 * is displayed at the bottom of a page.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */
class FooterNav extends HTMLWidget {

    /**
     * the company name for the copyright
     * statement.
     *
     * @access private
     * @var string
     */
    var $_company_name = "";

    /**
     * The date string for the copyright
     * statement. In form of
     * "2001-1997", or "2001"
     *
     * @access private
     * @var string
     */
    var $_date_string = "";

    /**
     * flag to tell us to render the
     * copyright string or not.
     * defaults to TRUE (or on)
     *
     * @access private
     * @var boolean
     */
    var $_render_copyright = TRUE;

    /**
     * url for the Legal statement.
     * if this is non-null, we will
     * render the "Legal Notice" link
     * in the copyright header.
     *
     * @access private
     * @var string
     */
    var $_legalnotice_url = NULL;

    /**
     * url for the privacy policy.
     * If this is non-null, we will
     * render the "Privacy Policy" link
     * in the copyright header.
     *
     * @access private
     * @var string
     */
    var $_privacypolicy_url = NULL;

    /**
     * email address to contact web site
     * maintainer.
     *
     * @access private
     * @var string
     */
    var $_webmaster_email = NULL;

    /**
     * Constructore for this class.
     *
     * @param   string $company_name - used in the
     *                               - copyright
     * @param   string $date_str - a date string to be used
     *                             for the copyright.
     */
    function __construct( $company_name="", $date_str=NULL ) {
        parent::__construct();
        $this->set_company_name( $company_name );
        if ($date_str==NULL) {
            $year = date("Y");
            $this->set_date_string($year);
        }
    }



    /**
     * set the company name for the copyright
     * statement.
     *
     * @param   string - $name
     */
    function set_company_name( $name ) {
        $this->_company_name = $name;
    }

    /**
     * set the date string for the copyright.
     * in the form of "2001-1997", or
     * "2001".
     *
     * @param string - $date_str
     */
    function set_date_string( $date_str ) {
        $this->_date_string = $date_str;
    }

    /**
     * set/unset the flag to tell us to
     * render the copyright string
     *
     * @param boolean - $flag
     */
    function set_copyright_flag( $flag ) {
        $this->_render_copyright = $flag;
    }

    /**
     * set the legal notice url.
     * if this is set we show the
     * legal notice link that points to $url.
     *
     * @param   string - $url
     */
    function set_legalnotice_url( $url ) {
        $this->_legalnotice_url = $url;
    }

    /**
     * sets the Privacy policy url.
     * if this is set we show the
     * privacy policy link that points to $url
     *
     * @param   string - $url
     */
    function set_privacypolicy_url( $url ) {
        $this->_privacypolicy_url = $url;
    }

    /**
     * sets the Webmaster email address
     * if this is set we show the
     * mailto for this email
     *
     * @param   string - $email
     */
    function set_webmaster_email( $email ) {
        $this->_webmaster_email = $email;
    }


    /**
     * add an entry to the footer nav
     *
     * @param   string - $url - url to go to
     * @param   text   - $text - url text to click on.
     */
    function add( $url, $text ) {
        $this->data[] = array( "type" => "url", "url" => $url,
                               "text" => $text );
    }



    //******************************************
    //*   rendering area
    //******************************************


    /**
     * render the code for this widget.
     *
     * @param int - the indentation level for
     *              the container.
     * @param int - the output debug flag to
     *              maintain compatibility w/ the API.
     *
     * @return string the raw html output.
     */
    function render( $indent_level=1, $output_debug=0) {

        //build the wrapper table first.
        $table = $this->build_wrapper_table();
        $div = html_div("links");
        $count = count($this->data);
        if ($count) {
            $x=0;
            //now walk thru each item and render it.
            foreach( $this->data as $item ) {
                $a = html_a($item['url'], $item['text'], 'foot');
                $x++;
                if ($x == $count) {
                    $div->add($a, "&nbsp;&nbsp;&nbsp;");
                } else {
                    $div->add( $a, "&nbsp;|&nbsp;");
                }
            }
            $table->add_row( $div );
        }

        if ($this->_render_copyright) {
            $table->add_row( $this->build_copyright_header() );

        }

        //add the Webmaster email link if Any
        if ($this->_webmaster_email) {
            $mailto = mailto($this->_webmaster_email);
            $mailto->set_class("notice");
            $table->add_row( html_span("trademark", $mailto));
        }

        return $table->render( $indent_level, $output_debug );
    }

    /**
     * render the copyright string
     *
     * @return SPANtag object that
     *                 contains the copyright
     *                 header.
     */
    function build_copyright_header() {

        $span = html_span("trademark");
        $string  = "Copyright &copy;";
        $string .= $this->_date_string . ", ";
        $string .= $this->_company_name. ".  All Rights Reserved.&nbsp;&nbsp;";
        $span->add( $string );

        //add the Legal notice if any
        if ($this->_legalnotice_url) {
            $span->add( html_a($this->_legalnotice_url, "Legal Notice", "notice"),
                         "&nbsp;&nbsp;" );
        }

        //add the Privacy notice if any
        if ($this->_privacypolicy_url) {
            $span->push( html_a($this->_privacypolicy_url, "Privacy Policy", "notice"),
                         "&nbsp;&nbsp;" );
        }

        return $span;
    }


    /**
     * builds the wrapper table
     *
     * @return  TABLEtag object.
     */
    function build_wrapper_table() {
        $table = html_table($this->width, 0, 2, 0);
        $table->set_id("footernav");
        $table->set_default_col_attributes( array("align" => "center") );
        return $table;
    }
}
?>
