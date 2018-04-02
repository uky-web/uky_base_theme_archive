<?php

use Drupal\node\Entity\Node;

/**
 * Implements hook_preprocess_page().
 */
function ukd8_preprocess_page(array &$variables) {
    if (!empty($variables['node'])) {
        $node = $variables['node'];

        if ($node instanceof Node) {
            $type = $node->getType();

            // look up some context for the section (unit)
            if ($type == 'page') {
                ukd8_inject_unit_meta($node, $variables);

                if ($node->field_suppress_sidebar->value) {
                    unset($variables['page']['sidebar']);
                }
            }
            elseif ($type == 'person') {
                ukd8_inject_unit_meta($node, $variables);
                // hide the quicklinks for people
                unset($variables['unit_quicklinks']);
            }
            elseif ($type == 'news') {
                ukd8_meta_lookup($variables, 'News');
                $variables['narrow_sidebar'] = true;
            }
            elseif ($type == 'event') {
                ukd8_meta_lookup($variables, 'Events');
            }
            elseif ($type == 'announcement') {
                ukd8_meta_lookup($variables, 'Resources');
            }

            // selectively hide some sidebar features
            if ($node->field_suppress_quicklinks->value) {
                unset($variables['unit_quicklinks']);
            }
            if ($node->field_suppress_announcements->value) {
                $variables['hide_announcements'] = TRUE;
            }
        }
    }
    else {
        // is there a better way to get the View ID?
        $current_path = \Drupal::service('path.current')->getPath();
        $alias = \Drupal::service('path.alias_manager')->getAliasByPath($current_path);

        // inject news meta stuff for the archive page
        if ($alias == '/news-archive') {
            ukd8_meta_lookup($variables, 'News');
        }

        if ($alias == '/events') {
            ukd8_meta_lookup($variables, 'Events');
        }

        if ($alias == '/announcements') {
            ukd8_meta_lookup($variables, 'Resources');
        }
    }

    if ($variables['is_front']) {
        ukd8_inject_block($variables, 'event_block', 'views_block__unit_events_block_2');
    }
}