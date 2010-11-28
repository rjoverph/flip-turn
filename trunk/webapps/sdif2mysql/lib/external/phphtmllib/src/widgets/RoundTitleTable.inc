<?php
/**
 * This contains the RoundTitleTable widget
 *
 * $Id: RoundTitleTable.inc 2738 2007-05-16 06:03:02Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 *
 */


/**
 * This builds a table
 * widget that has a nice rounded title,
 * a subtitle area and any amount of data.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */
class RoundTitleTable extends HTMLWidget {


  /**
   * the constructor for this class.
   * @param string  $title - the title for the widget.
   * @param string  $subtitle - the subtitle if any.
   * @param mixed   $width - the width of the widget.
   *                         can be a % or an int.
   */
  public function __construct( $title, $subtitle=NULL, $width="100%") {
      parent::__construct();
      $this->set_title( $title );
      $this->set_subtitle( $subtitle );
      $this->set_width( $width );
  }


  public function set_subtitle( $subtitle ) {
      $this->subtitle = $subtitle;
  }


  //******************************************
  //*   rendering area
  //******************************************


  /**
   * renders a title table for the widget.
   * @access private
   */
  private function render_title_table() {
      $table = html_table($this->width,0 ,0 ,0);

      //ok lets render the title table.
      $img = html_img("/phphtmllib/widgets/images/spacer.gif", 10, 15);

      $td = html_td("barleft", "left", $img );
      $td->set_collapse();
      $td2 = html_td("title", "", $this->title);
      $td2->set_collapse();
      $td3 = html_td("barright", "right", $img);
      $td3->set_collapse();

      $table->add_row( $td, $td2, $td3 );
      return $table;
  }

  /**
   * this function builds the subtitle td
   * to hold the...subtitle!
   *
   * @return TDtag object
   */
  private function _build_subtitle() {
      $td = html_td("subtitle", "", $this->subtitle);
      $td->set_tag_attribute("colspan", 2);
      $td->set_collapse();
      return $td;
  }


  /**
   * Render the Navtable and its content.
   *
   * @param int - the indentation level for
   *              the container.
   * @param int - the output debug flag to
   *              maintain compatibility w/ the API.
   *
   * @return string the raw html output.
   */
  public function render( $indent_level=1, $output_debug=0 ) {

      $span = html_div();
      $span->set_class("roundtitletable");

      $html = "";

      //render the title area first.
      $title = $this->render_title_table();
      $span->add( $title );

      $table = html_table($this->width, 0, 0, 2);
      $table->set_class("content");

      if ($this->subtitle) {
          $table->add_row( $this->_build_subtitle() );
      }

      //build the containing TD
      $container_td = html_td();

      foreach ($this->_content as $val) {
          $container_td->add( $val );
      }
      $table->add_row( $container_td );

      $span->add( $table );

      return $span->render( $indent_level, $output_debug);
  }
}

?>
