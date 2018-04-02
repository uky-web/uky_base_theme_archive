<?php

/**
 * Implements hook_preprocess_paragraph().
 */
function ukd8_preprocess_paragraph(&$variables) {
    $paragraph = $variables['paragraph'];

    // inject unit info under some conditions
    if (count($paragraph->field_tagline_heading) && $paragraph->field_tagline_heading[0]->value) {
        $node = \Drupal::routeMatch()->getParameter('node');
        if ($node) {
            // look up some context for the section (unit)
            ukd8_inject_unit_meta($node, $variables);
        }
    }

    // visually hide the title?
    if ($paragraph->field_hide_title && $paragraph->field_hide_title->value) {
        $variables['content']['field_title']['#attributes']['class'][] = 'visually-hidden';
    }
}