<?php
/**
 * Another example of how to build an
 * SVG Image with phpHtmlLib.
 * SVG = Scalable Vector Graphics.
 * that phpHtmlLib provides.
 *
 *
 * $Id: example8.php 2985 2007-09-27 23:39:18Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage examples
 * @version 2.0.0
 *
 */

/**
 * Include the phphtmllib libraries
 */
include_once("includes.inc");

/**
 * SVG helpers aren't included in the
 * autoload.inc by default
 */
include_once(PHPHTMLLIB.'/src/svg/SVGTAGS.inc');

/**
 * load the svg util functions
 */
include_once(PHPHTMLLIB.'/src/svg/svg_utils.inc');

//allow the user to change the width
//and the height of the graph itself
$width = 320;
if (!empty($_REQUEST["width"])) {
    $width = $_REQUEST["width"];
}

$height = 240;
if (!empty($_REQUEST["height"])) {
    $height = $_REQUEST["height"];
}

$svgdoc = new SVGDocument("100%","100%");
$graph = new SVGXYLineGraph("The Title of the Graph", $width,$height);
$graph->set_x_title("X-Axis dude");
$graph->set_y_title("Some Y Axis Data points");

//ok add a line and make it red
$graph->add_line("0,1,2.3,4.2,6,8", "1,2,2.7,0.3,6,1", "red");

//add 2 more lines
$graph->add_line("0,1,4.1,6", "0,4,2,3", "blue");
$graph->add_line("1,2,3,4,5", "0,4,3,1,7", "black");

//add the line graph widget to the document.
$svgdoc->add( $graph );

print $svgdoc->render();
?>
