<?php
// Provide < PHP 5.3 support for the __DIR__ constant.
if (!defined('__DIR__')) {
  define('__DIR__', dirname(__FILE__));
}

// Load module specific files in the includes directory.
$includes = file_scan_directory(__DIR__ . '/includes', '/\.inc$/');
foreach ($includes as $include) {
  require_once $include->uri;  
}

// Load module specific files in the widgets directory.
$includes = file_scan_directory(__DIR__ . '/includes/components/widgets', '/\.inc$/');
foreach ($includes as $include) {
  require_once $include->uri;  
}

// Load module specific files in the widgets directory.
$includes = file_scan_directory(__DIR__ . '/includes/components/styles', '/\.inc$/');
foreach ($includes as $include) {
  require_once $include->uri;  
}

// Load module specific files in the uielements directory.
$includes = file_scan_directory(__DIR__ . '/includes/components/uielements', '/\.inc$/');
foreach ($includes as $include) {
  require_once $include->uri;  
}


/**
 * Implements hook_theme().
 */
function wvusdrupal_theme(&$existing, $type, $theme, $path){
  // If we are auto-rebuilding the theme registry, warn about the feature.
  if (
    // Only display for site config admins.
    isset($GLOBALS['user']) && function_exists('user_access') && user_access('administer site configuration')
    && theme_get_setting('bootstrap_rebuild_registry')
    // Always display in the admin section, otherwise limit to three per hour.
    && (arg(0) == 'admin' || flood_is_allowed($GLOBALS['theme'] . '_rebuild_registry_warning', 3))
  ) {
    flood_register_event($GLOBALS['theme'] . '_rebuild_registry_warning');
    drupal_set_message(t('For easier theme development, the theme registry is being rebuilt on every page request. It is <em>extremely</em> important to <a href="!link">turn off this feature</a> on production websites.', array('!link' => url('admin/appearance/settings/' . $GLOBALS['theme']))), 'warning', FALSE);
  }

  return array(
    'carousel' => array(
        'variables' => array(
            'id' => '',
            'slides' => array()
          )
      ),
    'media_object' => array(
        'variables' => array(
            'heading' => '',
            'body' => '',
            'href' => '',
            'img_src' => '',
            'img_pull' => '',
         ),
      ),
    'accordion' => array(
      'variables' => array(
          'id' => '',
          'elements' => array(),
      ),
    ),
    'thumbnail' => array(
      'variables' => array(
        'attributes' => array(),
        'elements' => array(),
      ),
    ),
    'modal' => array(
      'variables' => array(
        'heading' => '',
        'body' => '',
        'footer' => '',
        'attributes' => array(),
        'html_heading' => FALSE,
      ),
    ),
    'view_navigation_links' => array(
      'variables' => array(
        'links' => array(),
        'attributes' => array(),
        'heading' => NULL
      ),
    ),
  );
}

/**
 * Returns the correct span class for a region
 */
function _wvusdrupal_content_span($columns = 1) {
  $class = FALSE;
  
  switch($columns) {
    case 1:
      $class = 'span12';
      break;
    case 2:
      $class = 'span9';
      break;
    case 3:
      $class = 'span6';
      break;
  }
  
  return $class;
}
