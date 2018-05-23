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

  $scheme_opts = [
    'default' => 'Default',
    'light' => 'Light (gray)',
    'dark' => 'Dark',
    'wildcat' => 'Wildcat',
  ];

  $color_defs = [
    'full_width_hero_schema' => 'Full width hero page header',
    'split_hero_schema' => 'Split hero page header',
    'text_only_schema' => 'Text-only page header',
    'call_to_action_schema' => 'Call to Action block',
    'pullquote_schema' => 'Pullquote',
    'social_media_schema' => 'Social media links panel',
    'statistic_schema' => 'Statistic block',
  ];
  
  $theme_settings =  \Drupal::config('ukd8.settings');

  $form['ukd8_settings']['color_schemes'] = [
    '#title' => t('Theme color settings'),
    '#type' => 'fieldset',
  ];

  foreach ($color_defs as $k => $label) {
    $v = $theme_settings->get($k);
    $form['ukd8_settings']['color_schemes'][$k] = [
      '#type' => 'select',
      '#title' => t($label),
      '#default_value' => $v,
      '#options' => $scheme_opts,
    ];
  }

  $form['ukd8_settings']['layout'] = [
    '#title' => t('Layout settings'),
    '#type' => 'fieldset',
  ];

  $form['ukd8_settings']['layout']['divide_statistics'] = [
    '#type' => 'checkbox',
    '#title' => t('Divide statistic collections'),
    '#default_value' => $theme_settings->get('divide_statistics'),
  ];
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