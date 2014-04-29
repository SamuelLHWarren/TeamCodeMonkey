<?php

/**
 * Preprocessor for theme('button').
 */
function wvusdrupal_preprocess_button(&$vars) {

  $vars['element']['#attributes']['class'][] = 'btn';

}

/**
 * Returns HTML for a button element.
 * 
 * Example on how to invoke: 
 * 
 *  $button = array(
 *  '#theme' => 'button',
 *  '#id'    => 'id',
 *  '#value' => 'Add to cart',
 *  '#name'  => 'name',
 *  '#type'  => 'button',
 *  '#attributes' => array(
 *  //button styles - refernce http://wvus-ibu.github.io/wvus.uikit/ui-elements/#buttons
 *  'class' => array( 'btn-danger', 'btn-large', 'disabled'
 *
 *       )
 *     )
 * );
 *
 * print drupal_render($button);
 *
 * 
 */

function wvusdrupal_button($variables) {
  $element = $variables['element'];
  $label = $element['#value'];
  element_set_attributes($element, array('id', 'name', 'value', 'type'));

  $element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }

  // Prepare input whitelist - added to ensure ajax functions don't break
  $whitelist = _wvusdrupal_button_whitelist();


  if (isset($element['#id']) && in_array($element['#id'], $whitelist)) {
    return '<input' . drupal_attributes($element['#attributes']) . ">\n"; // This line break adds inherent margin between multiple buttons
  }
  else {
    return '<button' . drupal_attributes($element['#attributes']) . '>'. $label ."</button>\n"; // This line break adds inherent margin between multiple buttons
  }

}

/**
 * Returns an array containing ids of any whitelisted drupal elements
 */
function _wvusdrupal_button_whitelist() {
/**
 * Why whitelist an element?
 * The reason is to provide a list of elements we wish to exclude
 * from certain modifications made by the custom theme which
 * break core functionality - e.g. ajax.
 */
  return array(
    'edit-refresh',
    'edit-pass-pass1',
    'edit-pass-pass2',
    'panels-ipe-cancel',
    'panels-ipe-customize-page',
    'panels-ipe-save',
  );
}