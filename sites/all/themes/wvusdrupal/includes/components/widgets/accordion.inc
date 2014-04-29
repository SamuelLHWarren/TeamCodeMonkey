<?php

/**
 * Returns HTML for Uikit's/Bootstrap's Collapse/Accordion.
 *
 * Example on how to invoke:
 * $accordion = array(
 *   '#theme' => 'accordion',
 *   '#id'    => 'accordion101',
 *   '#elements' => array(
 *     'collapseOne' => array('header' => 'Group Heading 1', 'content' => 'Awesome content...'),
 *     'collapseTwo' => array('header' => 'Group Heading 2', 'content' => 'Awesome content...'),
 *     )
 * );
 *
 * print drupal_render($accordion);
 */
function wvusdrupal_accordion($variables) {

  $elements = $variables['elements'];

  if (empty($variables['id'])) {
    $accordion_id = 'accordion-'. md5($elements);
  }
  else {
    $accordion_id = check_plain($variables['id']);
  }

  $output = '<div class="accordion" id="'.$accordion_id.'">';

  foreach ($elements as $id => $item) {
    $output .= '<div class="accordion-group"><div class="accordion-heading">';
    $output .= '<a class="accordion-toggle" data-toggle="collapse" data-parent="#'. $accordion_id .'" href="#'. $id .'">'. check_plain($item['header']) .'</a></div>';
    $output .= '<div id="'. $id .'" class="accordion-body collapse in"><div class="accordion-inner">';
    $output .= render($item['content']);
    $output .= '</div></div></div>';
  }

  $output .= '</div>';

  return $output;
}
