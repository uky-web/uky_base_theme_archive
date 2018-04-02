<?php

function ukd8_preprocess_breadcrumb(&$variables) {
    $current_path = \Drupal::service('path.current')->getPath();
    $aliased = \Drupal::service('path.alias_manager')->getAliasByPath($current_path);
    $trimmed = trim($aliased, '/');
    $slugs = explode('/', $trimmed);

    // make sure pages have at least 2 path slugs to show breadcrumbs
    if (count($slugs) < 2) {
        unset($variables['breadcrumb']);
    }
}