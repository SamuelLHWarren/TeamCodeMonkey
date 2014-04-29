<?php
/**
 * Helper function that creates HTML for dropdowns
 * @param $variables[] array contains 
 * $variables['menuId'] : id of the menu (optional)
 * $variables['aria']: aria-labeledby (optional)
 * $variables['classes']: array of classes ie pull-right (optional)
 * $variables['links']: array of links with href, name and optional attribute
 */

  function _dropdown_menu($variables){
    $menuId = $variables['id'];
    $aria = $variables['ariaLabel'];
    $attributes = $variables['attributes'];
    $links = $variables['links'];

    $classes = "";
    if(isset($attributes['class'])){
      $classes .= " " . implode(' ', $attributes['class']); 
    }
    $output = '<ul class="dropdown-menu' . $classes . '" role="menu"';

    if (isset($aria)){
      $output .= ' aria-lablledby="' . $aria . '"';
    }
    if(isset($menuId)){
      $output .= ' id="' . $menuId .'"';
    }
    $output .= ">";

    foreach ($links as $key => $link) {
      if ($link['attribute'] != 'submenu' && $link != 'divider'){
        if($link['attribute'] == 'disabled'){
          $output .= '<li class="disabled">';
        } else {
          $output .= '<li>';
        }
        $output .= l($link['name'], $link['href']);
        $output .="</li>";
        //$output .= '<a href="' . $link['href'] . '" tabindex="-1" >' . $link['name'] .'</a></li>';
        
      }elseif ($link == 'divider') {
        $output .= '<li class="divider"></li>';
      }
    }
    $output .= "</ul>";
    return $output;
  }

