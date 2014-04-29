<?php
/**
 * @file
 * Implementation of UiKit/Bootstrap media object. 
 * http://wvus-ibu.github.io/wvus.uikit/ui-elements/#media
 * 
 */

/**
 * Returns HTML for a media object
 * 
 */ 
function wvusdrupal_media_object($variables)  {

  $heading = $variables['heading'];
  //string or html output of a media object - nested media object
  $body = $variables['body'];
  //pull-left or pull-right
  $img_pull = $variables['img_pull'];
  $href =  $variables['href'];
  $img_src = $variables['img_src'];
  

  $output  = '<div class="media">';
  $output .= '<a class="'. $img_pull .'" href="' . $href . '">';
  $output .= '<img class="media-object" src="'. $img_src .'">';
  $output .= '</a>';
  $output .= '<div class="media-body">';
  $output .= '<a href="' . $href . '">';
  if (!empty($heading)) {
      if (is_string($heading)) {
      
        $output .= '<h4 class="media-heading">' . $heading . '</h4>';
    }
  }
  $output .= '</a>';
  $output .= render($body);
  $output .= '</div>';
  $output .= '</div>';


  return $output;

}
