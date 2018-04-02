<?php

use Drupal\taxonomy\Entity\Term;

/**
 * Implemements template_preprocess_views_view()
 */
function ukd8_preprocess_views_view(&$variables) {
    $node = \Drupal::routeMatch()->getParameter('node');
    if ($node) {
        // look up some tagging context
        if ($node->field_unit_ref) {
            $unit = $node->field_unit_ref->first()->entity;
            $variables['unit_abbrev'] = $unit->field_abbreviation->value;
        }
        if ($node->field_series_ref) {
            $series = $node->field_series_ref->first()->entity;
            $variables['series_name'] = $series->name->value;
            $variables['series_tid'] = $series->id();
        }
    }

    // news archive page
    if ($variables['id'] == 'news') {
        // collect some exposed filters for the title
        $view = $variables['view'];
        $inputs = $view->getExposedInput();
        foreach (['series', 'unit', 'topic', 'news-type'] as $key) {
            if (isset($inputs[$key]) && $inputs[$key] != 'All') {
                $variables['filter_title'] = ukd8_term_name_lookup($inputs[$key]);
                break;
            }
        }
    }

    // make the unit TID filter available
    $unit_teaser_lists = ['unit_events', 'announcements'];
    if (in_array($variables['id'], $unit_teaser_lists)) {
        if (count($variables['view']->args)) {
            $variables['unit_tid'] = $variables['view']->args[0];
        }
        
        // check if this is a filterable term, remove if not
        if ($variables['id'] == 'unit_events' && isset($variables['unit_tid'])) {
            $unit = Term::load($variables['unit_tid']);
            if (!$unit || !$unit->field_include_in_events_filter && !$unit->field_include_in_events_filter->value) {
                unset($variables['unit_tid']);
            }
        }
    }
    
}

/**
 * Implemements template_form_views_exposed_form_alter()
 */
function ukd8_form_views_exposed_form_alter(&$form, &$form_state, $form_id) {
    if ($form['#id'] == 'views-exposed-form-news-page-1') {
        // filter these to select ones that have a checkbox set
        $form['unit']['#options'] = array_filter($form['unit']['#options'], function($tid) {
            $term = Term::load($tid);
            if (empty($term)) return true;
            return $term->field_include_in_news_filter->value;
        }, ARRAY_FILTER_USE_KEY);
    }
    if ($form['#id'] == 'views-exposed-form-events-page-1') {
        // filter these to select ones that have a checkbox set
        $form['unit']['#options'] = array_filter($form['unit']['#options'], function($tid) {
            $term = Term::load($tid);
            if (empty($term)) return true;
            return $term->field_include_in_events_filter->value;
        }, ARRAY_FILTER_USE_KEY);
    }
    if ($form['#id'] == 'views-exposed-form-announcements-feed-page-1') {
        // filter these to select ones that have a checkbox set
        $form['unit']['#options'] = array_filter($form['unit']['#options'], function($tid) {
            $term = Term::load($tid);
            if (empty($term)) return true;
            return $term->field_include_in_events_filter->value;
        }, ARRAY_FILTER_USE_KEY);
    }
}