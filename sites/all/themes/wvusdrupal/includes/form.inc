<?php

/**
 * Implements hook_form_alter().
 */
function wvusdrupal_form_alter(&$form, &$form_state, $form_id) {
  // Id's of forms that should be ignored
  // Make this configurable - @TODO: Move to theme_settings
  $form_ids = array(
    'node_form',
    'system_site_information_settings',
    'user_profile_form',
    'node_delete_confirm',
  );

  // Only wrap in container for certain form
  if (isset($form['#form_id']) && !in_array($form['#form_id'], $form_ids) && !isset($form['#node_edit_form']) && isset($form['actions']) && ($form['actions']['#type'] == 'actions')) {
    $form['actions']['#theme_wrappers'] = array();
  }
}

/**
 * Returns HTML for a form element.
 */
function wvusdrupal_form_element(&$variables) {
  $element = &$variables['element'];
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }

  $exclude_control = FALSE;
  $control_wrapper = '<div class="controls">';
  // Add Custom class
  if (isset($element['#type']) && ($element['#type'] == "radio" || $element['#type'] == "checkbox")){
    $exclude_control = TRUE;
  }
  else {
    $attributes['class'] = array('control-group');
  }

  // Check for errors and set correct error class
  if (isset($element['#parents']) && form_get_error($element)) {
    $attributes['class'][] = 'error';
  }

  if (!empty($element['#type'])) {
    $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#name'])) {
    $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }
  $attributes['class'][] = 'form-item';
  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';

  // Prepare input whitelist - added to ensure ajax functions don't break
  $whitelist = _wvusdrupal_element_whitelist();

  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      // Check if item exists in element whitelist
      if (isset($element['#id']) && in_array($element['#id'], $whitelist)) {
        $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
        $exclude_control = TRUE;
      }
      else {
        $output = $exclude_control ? $output : $output.$control_wrapper;
        $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      }
      break;

    case 'after':
      $output = $exclude_control ? $output : $output.$control_wrapper;
      $variables['#children'] = ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output = $exclude_control ? $output : $output.$control_wrapper;
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if ( !empty($element['#description']) ) {
    $output .= '<p class="help-block">' . $element['#description'] . "</p>\n";
  }

  // Check if control wrapper was added to ensure we close div correctly
  if ($exclude_control) {
    $output .= "</div>\n";
  }
  else {
    $output .= "</div></div>\n";
  }
  return $output;
}

/**
 * Returns HTML for a form element label and required marker.
 */
function wvusdrupal_form_element_label(&$variables) {
  $element = $variables['element'];
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  // If title and required marker are both empty, output no label.
  if ((!isset($element['#title']) || $element['#title'] === '' && $element['#type'] !== 'radio' && $element['#type'] !== 'checkbox') && empty($element['#required'])) {
    return '';
  }

  // If the element is required, a required marker is appended to the label.
  $required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

  $title = filter_xss_admin($element['#title']);

  $attributes = array();
  // Style the label as class option to display inline with the element.
  if ($element['#title_display'] == 'after') {
    $attributes['class'][] = 'option';
    $attributes['class'][] = $element['#type'];
  }
  // Show label only to screen readers to avoid disruption in visual flows.
  elseif ($element['#title_display'] == 'invisible') {
    $attributes['class'][] = 'element-invisible';
  }

  if (!empty($element['#id'])) {
    $attributes['for'] = $element['#id'];
  }

  // @Bootstrap: Add Bootstrap control-label class except for radio.
  if ($element['#type'] != 'radio') {
    $attributes['class'][] = 'control-label';
  }
  // @Bootstrap: Insert radio and checkboxes inside label elements.
  $output = '';
  if ( isset($variables['#children']) ) {
    $output .= $variables['#children'];
  }

  // @Bootstrap: Append label
  $output .= $t('!required !title', array('!title' => $title, '!required' => $required));

  // The leading whitespace helps visually separate fields from inline labels.
  return ' <label' . drupal_attributes($attributes) . '>' . $output . "</label>\n";
} 

/**
 * Returns an array containing ids of any whitelisted drupal elements
 */
function _wvusdrupal_element_whitelist() {
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
