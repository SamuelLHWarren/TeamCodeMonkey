<?php
/**
 * bootstrap_carousel
 * Creates markup for the carousel
 *
 * @param $id: id of carousel
 * @param $slides: array of slides and info ie. $slides[][alt, src, caption]
 * The caption of a slide can be a string of markup or array with heading and body
 *      $slides[]['caption']['heading']
 *      $slides[]['caption']['body']
 */

function wvusdrupal_carousel(&$variables){
  $slides = $variables['slides'];
  $id = $variables['id'];


  $output = '<div id="' . $id . '" class="carousel slide">';
  $output .= '<ol class="carousel-indicators">';

  // Carousel Indicators
  $i = 0;
  
  foreach($slides as $slide){
    $active = '';
    if ($i == 0){
      $active = 'active';
    }
    $output .= '<li data-target="' . $id .'" data-slide-to="' . $i . '" class="' . $active . '"></li>';
    $i++;
  }
  $output .= '</ol> <!-- /carousel-indicators -->';

  // Carousel Items
  $output .= '<div class="carousel-inner">';
  foreach ($slides as $key => $slide) {
    $active = '';
    if ($key == 0){
      $active = 'active';
    }
    $output .= '<div class="item '. $active .'">';
    $output .= '<img src="' . $slide['src'] . '" alt="' . $slide['alt'] . '">';

    if (!empty($slide['caption'])){
      $output .= '<div class="carousel-caption">';

      if (is_array($slide['caption'])){
        $heading = $slide['caption']['heading'];
        $body = $slide['caption']['body'];

        if (!empty($heading)){
          $output .= '<h4>' . $heading . '</h4>';
        }
        if(!empty($body)){
          $output .= '<p>' . $body . '</p>';
        }

      } else {
        $output .= $slide['caption'];
      }
      $output .= '</div> <!-- /carousel-caption -->';
    }
  $output .= '</div> <!-- /carousel-item -->';
}
  $output .= '</div> <!-- /Carousel-Inner -->';
  $output .= '<a class="carousel-control left" href="#' . $id . '" data-slide="prev">';
  $output .= '<i class="icon-chevron-left"></i></a>';
  $output .= '<a class="carousel-control right" href="#'. $id . '" data-slide="next">';
  $output .= '<i class="icon-chevron-right"></i></a> <!-- /carousel-nav -->';
  $output .= '</div> <!-- /Carousel -->';

  return $output;
}