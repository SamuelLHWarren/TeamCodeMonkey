<?php

/**
 * Returns HTML for a query pager.
 *
 * Menu callbacks that display paged query results should call theme('pager') to
 * retrieve a pager control so that users can view other results. Format a list
 * of nearby pages with additional query results.
 *
 * @param $vars
 *   An associative array containing:
 *   - tags: An array of labels for the controls in the pager.
 *   - element: An optional integer to distinguish between multiple pagers on
 *     one page.
 *   - parameters: An associative array of query string parameters to append to
 *     the pager links.
 *   - quantity: The number of pages in the list.
 *   - type:
 *       0: numbered pagination with next and prevous ie. search results
 *       1: basic next and previous. Used for single content results. ie next post/previous post
 *
 * @ingroup themeable
 */
function wvusdrupal_pager($variables) {
  $output = "";
  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];
  //$type = $variable['type'];

  // sets $is_quick_pager if the type is 1 
  //$type == 1 ? $is_quick_pager = TRUE : $is_quick_pager = FALSE;
  $is_quick_pager = FALSE;
  global $pager_page_array, $pager_total;
  
  if(!$is_quick_pager){

    // Calculate various markers within this pager piece:
    // Middle is used to "center" pages around the current page.
    $pager_middle = ceil($quantity / 2);
    //print '$pager_middle '. $pager_middle . "<br>";
    // current is the page we are currently paged to
    $pager_current = $pager_page_array[$element] + 1;
    //print '$pager_current '. $pager_current . "<br>";
    // first is the first page listed by this pager piece (re quantity)
    $pager_first = $pager_current - $pager_middle + 1;
    //print '$pager_first ' . $pager_first . "<br>";
    // last is the last page listed by this pager piece (re quantity)
    $pager_last = $pager_current + $quantity - $pager_middle;
    //print '$print_last ' . $pager_last . "<br>";
    // max is the maximum page number
    $pager_max = $pager_total[$element];
    //print '$pager_max ' . $pager_max . "<br>";
    // End of marker calculations.

    // Prepare for generation loop.
    $i = $pager_first;
    if ($pager_last > $pager_max) {
      // Adjust "center" if at end of query.
      $i = $i + ($pager_max - $pager_last);
      $pager_last = $pager_max;
    }
    if ($i <= 0) {
      // Adjust "center" if at start of query.
      $pager_last = $pager_last + (1 - $i);
      $i = 1;
    }

    // End of generation loop preparation.
    $li_first = theme('pager_first', array('text' => (isset($tags[0]) ? $tags[0] : t('first')), 'element' => $element, 'parameters' => $parameters));
    $li_previous = theme('pager_previous', array('text' => (isset($tags[1]) ? $tags[1] : t('previous')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
    $li_next = theme('pager_next', array('text' => (isset($tags[3]) ? $tags[3] : 'next'), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
    $li_last = theme('pager_last', array('text' => (isset($tags[4]) ? $tags[4] : t('last')), 'element' => $element, 'parameters' => $parameters));

    if ($pager_total[$element] > 1) {
      /*
      if ($li_first) {
        $items[] = array(
          'class' => array('pager-first'),
          'data' => $li_first,
        );
      }
      */
      if ($li_previous) {
        $items[] = array(
          'class' => array('prev'),
          'data' => $li_previous,
        );
      }

      // When there is more than one page, create the pager list.
      if ($i != $pager_max) {
        if ($i > 1) {
          $items[] = array(
            'class' => array('pager-ellipsis', 'disabled'),
            'data' => '<span>…</span>',
          );
        }
        // Now generate the actual pager piece.
        for (; $i <= $pager_last && $i <= $pager_max; $i++) {
          if ($i < $pager_current) {
            $items[] = array(
             // 'class' => array('pager-item'),
              'data' => theme('pager_previous', array('text' => $i, 'element' => $element, 'interval' => ($pager_current - $i), 'parameters' => $parameters)),
            );
          }
          if ($i == $pager_current) {
            $items[] = array(
              'class' => array('active'), // Add the active class
              'data' => l($i, '#', array('fragment' => '','external' => TRUE)),
            );
          }
          if ($i > $pager_current) {
            $items[] = array(
              //'class' => array('pager-item'),
              'data' => theme('pager_next', array('text' => $i, 'element' => $element, 'interval' => ($i - $pager_current), 'parameters' => $parameters)),
            );
          }
        }
        if ($i < $pager_max) {
          $items[] = array(
            'class' => array('pager-ellipsis', 'disabled'),
            'data' => '<span>…</span>',
          );
        }
      }
      // End generation.
      if ($li_next) {
        $items[] = array(
          'class' => array('next'),
          'data' => $li_next,
        );
      }
      /*
      if ($li_last) {
        $items[] = array(
          'class' => array('pager-last'),
          'data' => $li_last,
        );
      }
      */
     
      return '<div class="pagination pagination-centered">'. theme('item_list', array(
        'items' => $items,
        //'attributes' => array('class' => array('pager')),
      )) . '</div>';
    }
    
    return $output;
  }

  // checks if the pager is a 2 link pager
  if($is_quick_pager){
    $li_next = theme('pager_next', array('text' => t('Newer'), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
    $li_previous = theme('pager_previous', array('text' => t('Older'), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));

    if($li_previous){
      $items[] = array(
        'data' => $li_previous
      );
    }
    if ($li_next) {
      $items[] = array(
        'data' => $li_next
      );
    }


  }
}

/**
 * Overrides the theme_pager_link
 *
 * Only changes are to the return values; when the value of $text is
 * next add the icon with right direction. When the value of $text is 
 * previous, add the icon with left direction. Otherwise, return a 
 * link with $text as the title of the link
 */


function wvusdrupal_pager_link($variables) {
  $text = $variables['text'];
  $page_new = $variables['page_new'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $attributes = $variables['attributes'];

  $page = isset($_GET['page']) ? $_GET['page'] : '';
  if ($new_page = implode(',', pager_load_array($page_new[$element], $element, explode(',', $page)))) {
    $parameters['page'] = $new_page;
  }

  $query = array();
  if (count($parameters)) {
    $query = drupal_get_query_parameters($parameters, array());
  }
  if ($query_pager = pager_get_query_parameters()) {
    $query = array_merge($query, $query_pager);
  }

  // Set each pager link title
  if (!isset($attributes['title'])) {
    static $titles = NULL;
    if (!isset($titles)) {
      $titles = array(
        t('« first') => t('Go to first page'),
        t('‹ previous') => t('Go to previous page'),
        t('next ›') => t('Go to next page'),
        t('last »') => t('Go to last page'),
      );
    }
    if (isset($titles[$text])) {
      $attributes['title'] = $titles[$text];
    }
    elseif (is_numeric($text)) {
      $attributes['title'] = t('Go to page @number', array('@number' => $text));
    }
  }

  // @todo l() cannot be used here, since it adds an 'active' class based on the
  //   path only (which is always the current path for pager links). Apparently,
  //   none of the pager links is active at any time - but it should still be
  //   possible to use l() here.
  // @see http://drupal.org/node/1410574
  $attributes['href'] = url($_GET['q'], array('query' => $query));
  if($text == 'next'){
    return '<a' . drupal_attributes($attributes) . '><i class="icon-chevron-sign-right icon-large"></i></a>';
  }elseif ($text == 'previous') {
    return '<a' . drupal_attributes($attributes) . '><i class="icon-chevron-sign-left icon-large"></i></a>';
  }else{
    return '<a' . drupal_attributes($attributes) . '>' . check_plain($text)  . '</a>';
  }
}


/**
 * Theme Function for View Navigation Links with "Previous", "Back" and 
 * "Next" links. 
 * @see node--blog-post.tpl.php file for use
 */
function wvusdrupal_view_navigation_links($variables) {
  $links = $variables['links'];
  $attributes = $variables['attributes'];
  $heading = $variables['heading'];
  $output = '<ul class="pager pull-left">';
  foreach ($links as $key => $link) {
    switch ($key) {
      case 'previous':
        $output .= "<li><a href='/" . $link['href'] . "'><i class='icon-long-arrow-left'></i> " . $link['title'] . "</a></li>";
        break;
      case 'back':
        $output .= "<li><a href='/" . $link['href'] . "'>" . $link['title'] . "</a></li>";
        break;
      case 'next':
        $output .= "<li><a href='/" . $link['href'] . "'>" . $link['title'] . " <i class='icon-long-arrow-right'></i></a></li>";
        break;
      default:
        $output .= "<li><a href='/" . $link['href'] . "'>" . $link['title'] . "</a></li>";
        break;
    }
  }
  $output .= '</ul>';

  return $output;
}