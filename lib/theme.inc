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

  $form['is_main'] = ['#type' => 'checkbox',
    '#title' => t('Is the main uky.edu site'),
    '#default_value' => theme_get_setting('is_main'),
  ];

  $form['lockup_wordmark_1'] = [
    '#type'          => 'textfield',
    '#title'         => t('Lockup wordmark line 1'),
    '#default_value' => theme_get_setting('lockup_wordmark_1'),
    '#description'   => t("Text shown as the first line of the wordmark in the header."),
  ];
  $form['lockup_wordmark_2'] = [
    '#type'          => 'textfield',
    '#title'         => t('Lockup wordmark line 2'),
    '#default_value' => theme_get_setting('lockup_wordmark_2'),
  ];

  $form['uky_home_url'] = [
    '#type'          => 'textfield',
    '#title'         => t('UK Homepage URL'),
    '#default_value' => theme_get_setting('uky_home_url'),
    '#description'   => t("URL for UK home links."),
  ];
  $form['college_url'] = [
    '#type'          => 'textfield',
    '#title'         => t('Parent college URL'),
    '#default_value' => theme_get_setting('college_url'),
    '#description'   => t("URL for this site's parent college, if applicable."),
  ];
  $form['college_title'] = [
    '#type'          => 'textfield',
    '#title'         => t('Parent college title'),
    '#default_value' => theme_get_setting('college_title'),
    '#description'   => t("Link display name for this site's parent college."),
  ];

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
    'carousel_schema' => 'Carousel slab',
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

  $form['ukd8_settings']['layout']['center_carousel'] = [
    '#type' => 'checkbox',
    '#title' => t('Use centered carousel style'),
    '#default_value' => $theme_settings->get('center_carousel'),
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