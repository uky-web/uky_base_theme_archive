<?php

use Drupal\block\Entity\Block;

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function ukd8_theme_suggestions_menu_alter(array &$suggestions, array $variables) {
  // Remove the block and replace dashes with underscores in the block ID to
  // use for the suggestion name.
  if (isset($variables['attributes']['block_id'])) {
    $hook = str_replace(array('block-', '-'), array('', '_'), $variables['attributes']['block_id']);
    $block = Block::load($hook);
    if ($block) {
      $region = $block->getRegion();
      $suggestions[] = $variables['theme_hook_original'] . '__' . $region;
      $suggestions[] = $variables['theme_hook_original'] . '__' . $region . '__' . $hook;
    }
  }
}