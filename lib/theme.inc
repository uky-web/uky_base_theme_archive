<?php

use Drupal\block\Entity\Block;
use Drupal\taxonomy\Entity\Term;
use Drupal\Core\Form\FormStateInterface;
use Drupal\image\Entity\ImageStyle;
use Drupal\Core\Url;
use Drupal\Core\Cache\CacheableMetadata;

function ukd8_form_system_theme_settings_alter(&$form, FormStateInterface &$form_state, $form_id = NULL) {
  // Work-around for a core bug affecting admin themes. See issue #943212.
  if (isset($form_id)) {
    return;
  }

  $form['tagline_superhead'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Tagline Superheading'),
    '#default_value' => theme_get_setting('tagline_superhead'),
    '#description'   => t("The superheading shown with the section tagline."),
  );

  $theme_opts = [
    'default' => 'Default',
    'light' => 'Light (gray)',
    'dark' => 'Dark',
    'wildcat' => 'Wildcat',
  ];

  $defs = [
    'full_width_hero' => 'Full width hero page header',
    'split_hero' => 'Split hero page header',
    'text_only' => 'Text-only page header',
    'call_to_action' => 'Call to Action block',
    'pullquote' => 'Pullquote',
    'social_media' => 'Social media links panel',
    'statistic' => 'Statistic block',
  ];
  
  $theme_settings =  \Drupal::config('ukd8.settings');

  $form['ukd8_settings']['color_theme'] = [
    '#title' => t('Theme color settings'),
    '#type' => 'fieldset',
  ];

  foreach ($defs as $k => $label) {
    $v = $theme_settings->get($k);
    $form['ukd8_settings']['color_theme'][$k] = [
      '#type' => 'select',
      '#title' => t($label),
      '#default_value' => $v,
      '#options' => $theme_opts,
    ];
  }
}

function _ukd8_add_theme_settings(array &$variables) {
  $theme_settings = \Drupal::config('ukd8.settings');
  // Add cachability metadata.
  CacheableMetadata::createFromRenderArray($variables)
    ->addCacheableDependency($theme_settings)
    ->applyTo($variables);
  // Add theme setting variables to the twig template variables.
  $variables['theme_settings'] = $theme_settings->getOriginal();
}