<?php
/*
 * Custom theme functions
 *
 */

/**
 * Implements hook_css_alter().
 */
function wvusdrupal_css_alter(&$css) {
  $theme_path = drupal_get_path('theme', 'wvusdrupal');
  // Load excluded CSS files from theme.
  $excludes = _wvusdrupal_alter(wvusdrupal_theme_get_info('exclude'), 'css');
  //Add UiKit
  $uikit = $theme_path . '/wvus.uikit/css/wvus.uikit.css';
  //commented out due to loading order; reference drupal bootstrap theme.inc file
  //overrides.css is included in the base theme info file for easier access, might need to revisit this implementation 
  // $css[$uikit] = array(
  //     'data' => $uikit,
  //     'type' => 'file',
  //     'every_page' => TRUE,
  //     'media' => 'all',
  //     'preprocess' => FALSE,
  //     'group' => CSS_THEME,
  //     'browsers' => array('IE' => TRUE, '!IE' => TRUE),
  //     'weight' => -2,
  //   );
  // // Add overrides.
  //   $override = $theme_path . '/css/overrides.css';
  //   $css[$override] = array(
  //     'data' => $override,
  //     'type' => 'file',
  //     'every_page' => TRUE,
  //     'media' => 'all',
  //     'preprocess' => TRUE,
  //     'group' => CSS_THEME,
  //     'browsers' => array('IE' => TRUE, '!IE' => TRUE),
  //     'weight' => -1,
  //   );
  $css = array_diff_key($css, $excludes);
}

/**
 * Implements hook_js_alter().
 */
function wvusdrupal_js_alter(&$js) {
  // Load excluded JS files from theme.
  $excludes = _wvusdrupal_alter(wvusdrupal_theme_get_info('exclude'), 'js');

  $theme_path = drupal_get_path('theme', 'wvusdrupal');

  // Replace core progress bar JS with the Bootstrap equivilent.
  if (isset($js['misc/progress.js']) && !empty($js['misc/progress.js'])) {
    unset($js['misc/progress.js']);
    $progress = $theme_path . '/js/progress.js';
    $js[$progress] = drupal_js_defaults($progress);
  }

  // Fix broken Views AJAX pagers.
  if (module_exists('views') && !empty($js[drupal_get_path('module', 'views') . '/js/ajax_view.js'])) {
    // Override core ajax prototype function to append throbber inside links,
    // instead of after it (floating issues).
    $ajax = $theme_path . '/js/bootstrap_ajax.js';
    $js[$ajax] = drupal_js_defaults($ajax);
    $js[$ajax]['group'] = JS_THEME;
    // Override views prototype function to bind to Bootstrap pagination.
    $ajax_view = $theme_path . '/js/bootstrap_ajax_view.js';
    $js[$ajax_view] = drupal_js_defaults($ajax_view);
    $js[$ajax_view]['group'] = JS_THEME;
  }

  $js = array_diff_key($js, $excludes);
}

function _wvusdrupal_alter($files, $type) {
  $output = array();

  foreach($files as $key => $value) {
    if (isset($files[$key][$type])) {
      foreach ($files[$key][$type] as $file => $name) {
        $output[$name] = FALSE;
      }
    }
  }
  return $output;
}

/**
 * Implements theme_status_messages
 */

function wvusdrupal_status_messages($variables) {
  $display = $variables['display'];
  $output = '';
  $message_class = '';

  $status_heading = array(
    'status' => array('heading' => t('Status message'), 'class' => 'alert-success'),
    'error' => array('heading' => t('Error message'), 'class' => 'alert-error'),
    'warning' => array('heading' => t('Warning message'), 'class' => 'alert-warning'),
    'success' => array('heading' => t('Success message'), 'class' => 'alert-success'),
    'info' => array('heading' => t('Information message'), 'class' => 'alert-info'),
  );


  foreach (drupal_get_messages($display) as $type => $messages) {

    if (count($messages) > 1) {
      $output .= "<div class=\"messages alert alert-block " . $status_heading[$type]['class'] . "\">\n";
    }else{
      $output .= "<div class=\"messages alert " . $status_heading[$type]['class'] . "\">\n";
    }
    $output .= "<button type=\"button\" class=\"close\" data-dismiss=\"alert\">&times</button>";
    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="element-invisible">' . $status_heading[$type]['heading'] . "</h2>\n";
    }
    if (count($messages) > 1) {
      $output .= " <ul>\n";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= $messages[0];
    }
    $output .= "</div>\n";
  }
  return $output;
}