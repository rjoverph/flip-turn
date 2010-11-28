<?php
/**
 * This file contains the PageWidget class
 *
 * $Id: HTMLPage.inc 3113 2008-03-13 22:32:20Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */

/**
 * This class is used to build content
 * for an entire page.  It uses the
 * HTMLPageClass widget from phphtmllib
 * to render the final output.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
abstract class HTMLPage extends HTMLDocument {

    /** CLASS VARS **/

    /**
     * This enables the ability to view the
     * source of a page bu setting debug=1
     * in the query string.
     *
     */
    protected $_enable_debug = FALSE;

    /**
     * Does the user have permission
     * to build and view the content?
     */
    protected $_perm_options = array("allowed" => TRUE,
                                     "message" => "You are not allowed to view this page.",
                                     "url" => NULL);

    /**
     * the message box for displaying
     * permissions errors
     */
    protected $_permission_box = NULL;

    /**
     * This is to enable/disable the
     * permissions checking.
     * By default it is off.
     */
    protected $_allow_permissions_checks = FALSE;


    /**
     * The width of the permissions dialog
     * table.
     */
    private $_permissions_error_width = "50%";


    /**
     * Constructor:
     *
     * @param   mixed  - $title Title string or TITLEtag object for the page.
     * @param   string - one of 3 types of html to render.  Setting this will
     *                   make the object declare the gobal define which tells
     *                   all of the tag objects what type of html tags to render.
     *                   some tags support special features.  such as the <IMG>
     *                   tag.  If xhtml is selected, the the IMGtag object and all
     *                   utility functions will not render "border=0" as a default
     *                   attribute, since this is not proper xhtml.
     *                   "html" - HTML 4.0 (default)
     *                   "xhtml_transitional" - render xhtml instead of html
     *                                        - doctype is XHTML transitional.
     *                   "xhtml_strict" - render xhtml instead of html 4.0.
     *                                  - doctype is XHTML strict.
     * @param   int   - one of 2 types.  INDENT_NICE or INDENT_LEFT_JUSTIFY
     *                  This tells the page how to render the indenting of the
     *                  output.  By default it is set to INDENT_NICE, which nicely
     *                  indents each nested tag.  You can have all tags rendered
     *                  left justified (smaller size in output) by using
     *                  INDENT_LEFT_JUSTIFY
     *
     */
    function __construct( $title = NULL, $render_type = phphtmllib::HTML, $indent_style=phphtmllib::INDENT_NICE ) {

        if (defined("DEBUG") && isset($_REQUEST["debug"])) {
            $this->enable_debug( TRUE );
        }

        //call the parent's constructor
        parent::__construct( $title, $render_type, $indent_style );

        //see if we are allowed to check permissions
        //You need to have the CSS definitions for the
        //InfoTable defined in order to see the error
        //table correctly.  Or you can override the
        //_build_permission_box() method to provide
        //a different object for displaying the
        //permission errors.
        if ($this->_allow_permissions_checks) {
            //check the permissions on this page
            $this->_check_permissions();
        }
    }

    /**
     * This function is used to build
     * addition head content that isn't
     * built by the HTMLPageClass parent
     * class by default.
     * NOTE: you can add addition content
     *       to the head in 1 of 2 ways.
     *       1) inside the call return the
     *          addition content in the
     *          return $foo;
     *       2) or use the HTMLPageClass'
     *          $this->add_head_content()
     *          from within the head_content()
     *          call.
     *
     * @return mixed.
     */
    abstract protected function head_content();

    /**
     * This function is meant to be overridden
     * by the child class.
     * This provides all of the content
     * for the page.
     * NOTE: You add the content to the
     *       body in 1 of 2 ways.
     *       1) return the content from this
     *          call.
     *       2) inside the call, you can
     *          just call $this->add();
     *          and then return NULL;
     *
     * @return mixed.
     */
    abstract protected function body_content();

    /**
     * This function is called to build
     * any JavaScript that is needed in the
     * <HEAD> portion of a document.
     *
     * @return string - the raw JS code to be
     *                  put inside the <head>
     */
    protected function head_javascript() {
        return NULL;
    }

    /**
     * This sets the debug option for
     * the HTMLPageClass
     *
     * @param boolean TRUE for on, FALSE for off
     */
    public function enable_debug( $flag = TRUE ) {
        $this->_enable_debug = $flag;
    }

	/**
	 * This method is called by the controller to 
     * render any of the http headers we need to 
     * set during render time.
     *
     * You are just supposed to call header() in here
     */
    public function http_headers() {
		header("Content-type: ".$this->_content_type."; charset=".$this->_charset.";");
	}

    /**
     * This is the function that renders the HTML
     * for this widget.
     *
     * @return string - the HTML
     */
    public function render() {

        //test to see if they want debugging of
        //output enabled.
        if ( $this->_enable_debug ) {
            if ( isset($_GET["debug"]) ) {
                $this->set_text_debug( TRUE );
            }
        }

        //see if we have permissions to build the
        //content for this page.  If permissions checks
        //aren't allowed, this will pass.
        if ($this->has_permission()) {

            //Try and get some more head content
            $content = "";
            $content = $this->head_content();
            if ( $content != "" ) {
                $this->add_head_content( $content );
            }

            //try and get the body content.
            //the user could just have added
            //the data manually.
            $content = "";
            $content = $this->body_content();
            if ( $content != "" ) {
                $this->add( $content );
            }

            //Lets see if they have any javascript
            //for the head
            $js = $this->head_javascript();
            if ( $js != NULL ) {
                $this->add_head_js( $js );
            }
        } else {
            $this->add( html_br(), $this->_permission_box);
        }

        return parent::render();
    }

    /**
     * This method is used to enable or disable the
     * built in permissions checking mechanism.
     *
     * @param boolean TRUE = enable permissions checks
     */
    public function allow_permissions_checks($flag=true) {
        $this->_allow_permissions_checks = $flag;
    }

    /**
     * This method allows all PageWidget children to
     * do any kind of permissions checking before
     * any content methods are called.
     * This allows for a very secure method of building
     * and rendering the page content.
     *
     */
    protected function _check_permissions() {
        //call the child permission() method
        if ( !$this->permission() ) {
            //looks like the user doesn't have
            //permissions to view this page
            $this->_set_perms( FALSE );

            $this->_build_permission_box();
        }
    }

    /**
     * This is meant to be extended by the child class
     * to do any generic permissions checking for access
     * to the content that the child builds
     *
     * @return boolean - TRUE = has permissions to build
     *                          and view content.
     */
    abstract protected function permission();

    /**
     * set the value of the permissions
     *
     * @param boolean - TRUE = has permission
     */
    protected function _set_perms( $flag ) {
        $this->_perm_options["allowed"] = $flag;
    }

    /**
     * do we have permissions to build/view the content?
     * This method is available after the constructor.
     * The constructor calls _check_permissions to set the
     * flag to make this object available.
     *
     * @return boolean
     */
    public function has_permission() {
        if (!$this->_allow_permissions_checks) {
            //permissions checks aren't allowed
            //so just return true.
            return TRUE;
        } else {
            return $this->_perm_options["allowed"];
        }
    }

    /**
     * This is used to set the various options for displaying
     * the failed permissions box.  This should be called
     * prior to returning false in the permissions() method
     *
     * @param string - the permissions message
     *                 NOTE: NULL message means use the default.
     * @param string - the url where to go to.
     *                 NOTE: if NULL, then there will be no
     *                       button shown
     */
    public function set_permissions_message($message=NULL, $url=NULL) {
        if ( $message != NULL ) {
            $this->_perm_options["message"] = $message;
        }
        $this->_perm_options["url"] = $url;
    }

    /**
     * This is the method used to build the
     * object to display the permissions error.
     *
     * By default it uses either the MessageBoxWidget
     * or the MessageBoxOK widget which both rely on
     * having the InfoTable object's css included in the page.
     *
     * @return none
     */
    protected function _build_permission_box() {
        $message = $this->_perm_options["message"];
        if (!is_object($message)) {
            $message = htmlspecialchars($message);
        }
        if ( $this->_perm_options["url"] == NULL ) {
            $this->_permission_box = new MessageBoxWidget("Error", $this->_permissions_error_width,
                                                          $message);
        } else {
            $this->_permission_box = new MessageBoxOK("Error", $this->_permissions_error_width,
                                                      $message,
                                                      $this->_perm_options["url"]);
        }
    }
}
?>
