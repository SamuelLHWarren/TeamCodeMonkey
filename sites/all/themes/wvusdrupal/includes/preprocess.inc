<?php

/**
 * Preprocess variables for block.tpl.php
 *
 * @see block.tpl.php
 */
function wvusdrupal_preprocess_block(&$variables, $hook) {
  //$variables['classes_array'][] = 'row';
  // Use a bare template for the page's main content.
  if ($variables['block_html_id'] == 'block-system-main') {
    $variables['theme_hook_suggestions'][] = 'block__no_wrapper';
  }
  $variables['title_attributes_array']['class'][] = 'block-title';
}



/**
 * Preprocess variables for page.tpl.php
 *
 * @see page.tpl.php
 */
function wvusdrupal_preprocess_page(&$variables) {
  drupal_add_css('css/overrides.css');
  // Add information about the number of sidebars.
  if (!empty($variables['page']['sidebar_first']) && !empty($variables['page']['sidebar_second'])) {
    $variables['columns'] = 3;
  }
  elseif (!empty($variables['page']['sidebar_first'])) {
    $variables['columns'] = 2;
  }
  elseif (!empty($variables['page']['sidebar_second'])) {
    $variables['columns'] = 2;
  }
  else {
    $variables['columns'] = 1;
  }

  // Primary nav
  $variables['primary_nav'] = FALSE;
  if ($variables['main_menu']) {
    // Build links
    $variables['primary_nav'] = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
    // Provide default theme wrapper function
    $variables['primary_nav']['#theme_wrappers'] = array('menu_tree__primary');
  }

  // Secondary nav
  $variables['secondary_nav'] = FALSE;
  if ($variables['secondary_menu']) {
    // Build links
    $variables['secondary_nav'] = menu_tree(variable_get('menu_secondary_links_source', 'user-menu'));
    // Provide default theme wrapper function
    $variables['secondary_nav']['#theme_wrappers'] = array('menu_tree__secondary');
  }
}



/**
 * Preprocess variables for region.tpl.php
 *
 * @see region.tpl.php
 */
function wvusdrupal_preprocess_region(&$variables, $hook) {
  if ($variables['region'] == 'content' || $variables['region'] == "sidebar_second") {
    $variables['theme_hook_suggestions'][] = 'region__no_wrapper';
  }
  
  if ($variables['region'] == "sidebar_first") {
    $variables['classes_array'][] = 'well';
  }
}