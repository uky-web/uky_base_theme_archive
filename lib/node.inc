<?php

use Drupal\Component\Utility\Html;

/**
 * Implements hook_preprocess_node().
 */
function ukd8_preprocess_node(array &$variables) {
    $node = $variables['node'];
    $type = $node->getType();

    $variables['plain_title'] = strip_tags($node->title[0]->value);
    $variables['is_front'] = \Drupal::service('path.matcher')->isFrontPage();
    $variables['base_path'] = base_path();
}
