<?php

/**
 * Implements hook_preprocess_paragraph().
 */
function ukd8_preprocess_paragraph(&$variables) {
    $paragraph = $variables['paragraph'];

    // visually hide the title?
    if ($paragraph->field_hide_title && $paragraph->field_hide_title->value) {
        $variables['content']['field_title']['#attributes']['class'][] = 'visually-hidden';
    }

    // load up the theme settings
    // see theme.inc
    _ukd8_add_theme_settings($variables);
}