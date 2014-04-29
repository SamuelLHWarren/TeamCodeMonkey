<?php
function wvusdrupal_breadcrumb($variables){
  $breadcrumbs = $variables['breadcrumb'];
  array_push($breadcrumbs, drupal_get_title());
  $output = '';
  if (count($breadcrumbs) > 1){
    $count = count($breadcrumbs) - 1; //count starts at 1
    $output .= '<ul class="breadcrumb">';
    foreach ($breadcrumbs as $key => $link) {
      if($key == 0){
        $output .= '<li><a href="' . url('<front>') . '"><i class="icon-home icon-large"></i></a>';
        $output .= '<span class="divider">&gt;</span></li>';
      } else{
        if ($key != $count) {
          $output .= '<li>' . $link . '<span class="divider">&gt;</span></li>';
        } elseif ($key == $count) {
          $output .= '<li class="active">' . drupal_get_title() . '</li>';
        }
      }
    }
    $output .= "</ul>";
  }
  return $output;
}