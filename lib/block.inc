<?php

use Drupal\Core\Entity\EntityInterface;

/**
 * Implements hook_preprocess_block()
 */
function ukd8_preprocess_block(&$variables) {
  // Convenience variable for block headers.
  $title_class = &$variables['title_attributes']['class'];

  // Generic block header class.
  $title_class[] = 'block-title';

  $region = isset($variables['configuration']['region']) ? $variables['configuration']['region'] : '';

  if ($region == 'header') {
    $title_class[] = 'visually-hidden';
  }

  // Add a unique class for each block for styling.
  if (isset($variables['attributes']['id'])) {
    $variables['attributes']['class'][] = $variables['attributes']['id'];
  }

  // helper variable
  foreach ($variables['content'] as $k => $v) {
    if (strpos($k, 'field_')===0) {
      if (isset($v['#items'])) {
        $variables['block'][$k] = $v['#items'];
      }
    }
  }
}

/**
 * Implements hook_theme_suggestions_block_alter()
 */
function ukd8_theme_suggestions_block_alter(array &$suggestions, array $variables) {
  // Block suggestions for custom block bundles.
  if (isset($variables['elements']['content']['#block_content'])) {
    array_splice($suggestions, 1, 0, 'block__bundle__' . $variables['elements']['content']['#block_content']->bundle());
  }
}