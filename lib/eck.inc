<?php

function ukd8_preprocess_eck_entity(&$variables) {

// Commenting out.  This breaks the theme loading
  // Helpful $content variable for templates.
//  $variables += ['content' => []];
//  foreach (\Drupal\Core\Render\Element::children($variables['entity']) as $key) {
//    $variables['content'][$key] = $variables['entity'][$key];
//  }

  // inspired by Paragraphs, injecting:
  //  eck: raw content
  //  content: child elements (i.e., fields)
  //  plain_title: just the title string
  $type = $variables['entity']['#entity_type'];
  if (isset($variables['entity']['#' . $type])) {
    $variables['eck'] = $variables['entity']['#' . $type];

    $variables['plain_title'] = (isset($variables['eck']->title))?
       strip_tags($variables['eck']->title[0]->value) :
       '';
  }

  // load up the theme settings
  // see theme.inc
  _ukd8_add_theme_settings($variables);
}