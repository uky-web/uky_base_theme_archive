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

    // $variables['is_landing_page'] = FALSE;
    if ($type == 'page') {
        $variables['has_content_prefix'] = count($node->field_wide_paragraphs) > 0;

         // look up some context
        ukd8_inject_unit_meta($node, $variables);
    }
    elseif ($type == 'person') {
        ukd8_inject_unit_meta($node, $variables);
    }
    elseif ($type == 'news') {
        ukd8_meta_lookup($variables, 'News', TRUE);
        ukd8_inject_series_meta($node, $variables);
    }
    elseif ($type == 'event') {
        ukd8_meta_lookup($variables, 'Events', TRUE);
    }
    elseif ($type == 'announcement') {
        ukd8_meta_lookup($variables, 'Resources', TRUE);
        //ukd8_inject_unit_meta($node, $variables);

        ukd8_inject_block($variables, 'announcements_block', 'views_block__announcements_block_1');
    }

    // section jumplinks
    if (count($node->field_paragraphs) && count($node->field_section_jumplinks) && $node->field_section_jumplinks->value) {
        // loop through paragraphs, collect titles
        $titles = [];
        foreach ($node->field_paragraphs as $p) {
            $paragraph = $p->entity;
            $type = $paragraph->bundle();
            if (count($paragraph->field_title) && $paragraph_title = $paragraph->field_title->value) {
                $id = '#' . Html::getId($paragraph_title);
                $titles[$id] = $paragraph_title;
            }
            else {
                // some special cases
                if ($type == 'series_spotlight') {
                    $titles['#' . Html::getId('Series Spotlight')] = 'Series Spotlight';
                }
            }
        }
        $variables['section_titles'] = $titles;
        $variables['#attached']['library'][] = 'ukd8/sticky';
    }
}
