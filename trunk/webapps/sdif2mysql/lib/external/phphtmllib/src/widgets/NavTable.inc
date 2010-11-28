<?php
/**
 * This contains the InfoTable widget
 *
 * $Id: NavTable.inc 2738 2007-05-16 06:03:02Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 *
 */

/**
 * This builds a navigational table
 * widget that has a title, any #
 * of subtitles and then navigational
 * links.
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage HTMLWidget
 */
class NavTable extends HTMLWidget {


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

  //functions for adding/updating data

  /**
   * this function adds an entry to the navtable.
   * It automatically adds the link based on $url,
   * with $text as the viewable text.
   *
   * @param string - the url for the link
   * @param string - the link text
   * @param string - the link title text
   * @param string - the link target
   */
  public function add($url, $text, $title=NULL, $target=NULL) {
      array_push($this->data, array("type"=>"url",
                                    "url"=>$url,
                                    "text"=>$text,
                                    "target"=>$target,
                                    "title"=>$title));
  }

  /**
   * This lets you add a blank line
   * between 2 links
   *
   * @param int - the # of blank lines to insert
   */
  public function add_blank( $num = 1 ) {
    for ($x=1; $x<=$num; $x++)
       array_push($this->data, array( "type"=>"blank" ));
  }

  /**
   * this adds a text item in the nav
   *
   * @param string - the text to display
   */
  public function add_text( $text ) {
      array_push($this->data, array( "type"=>"text", "text"=>$text ));
  }

  /**
   * This adds a new heading in the nav.
   * It will look just like the sub title area
   *
   * @param string - the text in the heading
   */
  public function add_heading( $title ) {
      array_push($this->data, array( "type" => "heading", "title" => $title ));
  }

  //******************************************
  //*   rendering area
  //******************************************


  /**
   * renders a title table for the widget.
   * @access private
   */
  protected function render_title_table() {
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
   * render a blank tr
   * @access private
   */
  private function _render_blank_tr() {
      $tr = new TRtag;
      $space = "&nbsp;&nbsp;";

      $td = new TDtag( array( "style" => "width:1%;", "class" => "navtablediv"), $space );
      $td2 = new TDtag( array( "style" => "width:99%;", "class" => "navtablediv"), $space );

      $tr->add( $td, $td2 );
      $tr->set_collapse();

      return $tr;
  }

  /**
   * render a url row.
   * @param array() - the item to render.
   */
  private function _render_url( $val ) {
      $tr = new TRtag;
      $bullet = "&bull;&nbsp;&nbsp;";

      $tr->add( html_td("bullet", "", $bullet) );

      $url_td = new TDtag( array("class" => "link") );

      $attributes = array("href" => $val["url"]);
      if ($val["target"] != NULL) {
          $target = $val["target"];
      } else {
          $target = "";
      }
      $url = html_a( $val["url"], $val["text"], NULL, $target, $val["title"]);

      $url_td->add( $url );
      $tr->add( $url_td );
      $tr->set_collapse();

      return $tr;
  }

  /**
   * render a text row.
   * @param array() - the item to render.
   */
  private function _render_text( $val ) {
      $tr = new TRtag;
      $bullet = "&bull;&nbsp;&nbsp;";

      $td = html_td("bullet", "", $bullet);
      $text_td = html_td("link", "", $val["text"] );

      $tr->add( $td, $text_td );
      $tr->set_collapse();

      return $tr;
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
      $span->set_class("navtable");

      $html = "";

      //render the title area first.
      $title = $this->render_title_table();
      $span->add( $title );

      $table = html_table($this->width, 0, 0, 2);
      $table->set_class("content");

      if ($this->subtitle) {
          $table->add_row( $this->_build_subtitle() );
      }

      foreach ($this->data as $key=>$val) {
          switch ($val["type"]) {
              case "blank":
                  $table->add_row( $this->_render_blank_tr() );
                  break;

              case "url":
                  $table->add_row( $this->_render_url( $val ) );
                  break;

              case "text":
                  $table->add_row( $this->_render_text( $val ) );
                  break;

              case "heading":
                  //dunno if we can do this.
                  break;
          }
      }

      $span->add( $table );

      return $span->render( $indent_level, $output_debug);
  }
}

?>
