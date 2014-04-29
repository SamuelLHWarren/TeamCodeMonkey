<?php

/**
 * Returns HTML for UiKit's/Bootstrap's Thumbnail.
 *
 * Example on how to invoke:
 * 
 * $thumbnails = array(
 *   '#theme' => 'thumbnail',
 *   '#elements' => array(
 *       array(
 *       'layout' => 'default',
 *       'header' => 'Heading1', 
 *       'caption' => 'Awesome content...', 
 *       'img_src' => 'http://placehold.it/350x150',
 *       'alt'     => 'Awesome pic',
 *       'link'    => 'http://www.google.com/',
 *       'attributes' => array( 
 *           'class' => array('span4'))
 *                 ),
 *       array(
 *       'layout' => 'layout1',
 *       'header' => 'Awesome Heading',
 *       'caption' => 'Awesome content...', 
 *       'buttons' => array(
 *         array('attributes' => array('class' => array('btn', 'btn-primary'), 'href' => 'http://www.amazon.com/'), 'value' => 'Read More'),
 *         array('attributes' => array('class' => array('btn', 'btn-info'), 'href' => 'http://www.amazon.com/'), 'value' => 'Action')
 *         ),
 *       'img_src' => 'http://placehold.it/350x150',
 *       'alt'     => 'Awesome pic2',
 *       'link'    => 'http://www.google.com/',
 *       'attributes' => array( 
 *           'class' => array('span4'))
 *                 ),
 *       array(
 *       'layout' => 'layout2',
 *       'header' => 'Awesome Heading',
 *       'caption' => NULL, 
 *       'buttons' => array(
 *         array('attributes' => array('class' => array('btn', 'btn-primary'), 'href' => 'http://www.amazon.com/'), 'value' => 'Read More'),
 *         array('attributes' => array('class' => array('btn', 'btn-info'), 'href' => 'http://www.amazon.com/'), 'value' => 'Action')
 *         ),
 *       'img_src' => 'http://placehold.it/350x150',
 *       'alt'     => 'Awesome pic2',
 *       'link'    => 'http://www.google.com/',
 *      'attributes' => array( 
 *           'class' => array('span4'))
 *                 ),
 *     ),    
 *    );
 *
 *    print drupal_render($thumbnails);
 */
function wvusdrupal_thumbnail($variables) {

  $elements = $variables['elements'];
  $variables['attributes']['class'][] = 'thumbnails';

  $output = '<ul' . drupal_attributes($variables['attributes']) . '>';

  foreach ($elements as $id => $item) {
    $output .= '<li' . drupal_attributes($item['attributes']) . '>';

    switch ($item['layout']) {

      //just image
      case 'default':
              $output .= '<a href="' . $item['link'] . '" class="thumbnail">';
              $output .= '<img src="' . $item['img_src'] . '" alt="' . $item['alt']. '">';
              $output .= '</a>';
          break;
      //order: header, image, caption, button(s)
      case 'layout1':

              $output .= '<div class="thumbnail">';

                if(isset($item['header'])) {

                    $output .= '<h3>' . check_plain($item['header']) . '</h3>';
                }

                $output .= '<img src="' . $item['img_src'] . '" alt="' . $item['alt']. '">';

                if(isset($item['caption'])) {

                  $output .= '<div class="caption">';
                  $output .= '      <p>' . render($item['caption']) . '</p>';

                  if(isset($item['buttons']) && is_array($item['buttons'])) {

                     $output .= '<p>';

                     foreach($item['buttons'] as $button){

                         $output .= '<a' . drupal_attributes($button['attributes']) . '>' . $button['value'] . '</a>';
                    }
                     $output .= '</p>';
                  }

                  $output .= '</div>';
                }

              $output .= '</div>';
                    
          break;
      //order: image, caption, header, button(s)
      case 'layout2':

            $output .= '<div class="thumbnail">';

                $output .= '<img src="' . $item['img_src'] . '" alt="' . $item['alt']. '">';

                if(isset($item['caption'])) {

                  $output .= '<div class="caption">';
                  $output .= '      <p>' . render($item['caption']) . '</p>';
                  $output .= '</div>';
                }

              if(isset($item['header'])) {

                  $output .= '<h3>' . check_plain($item['header']) . '</h3>';
              }

              if(isset($item['buttons']) && is_array($item['buttons'])) {

                     $output .= '<p>';
                     foreach($item['buttons'] as $button){
                         $output .= '<a' . drupal_attributes($button['attributes']) . '>' . $button['value'] . '</a>';
                      }
                     $output .= '</p>';
              }

              $output .= '</div>';
          break;
  }

    $output .= '</li>';
  }

  $output .= '</ul>';

  return $output;
}