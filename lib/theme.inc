<?php

use Drupal\block\Entity\Block;
use Drupal\taxonomy\Entity\Term;
use Drupal\Core\Form\FormStateInterface;
use Drupal\image\Entity\ImageStyle;
use Drupal\Core\Url;

function ukd8_form_system_theme_settings_alter(&$form, FormStateInterface &$form_state, $form_id = NULL) {
  // Work-around for a core bug affecting admin themes. See issue #943212.
  if (isset($form_id)) {
    return;
  }

  $form['tagline_superhead'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Tagline Superheading'),
    '#default_value' => theme_get_setting('tagline_superhead'),
    '#description'   => t("The superheading shown with the section tagline."),
  );
}

function ukd8_unit_vars(&$variables, $unit, $title_override = FALSE) {
  $variables['unit_name'] = $unit->name->value;
  if (count($unit->field_unit_home)) {
    if ($unit->field_unit_home[0]->uri) {
      $variables['unit_url'] = Url::fromUri($unit->field_unit_home[0]->uri)->toString();
    }
  }

  $variables['unit_nav'] = $unit->field_section_nav;
  if (count($unit->field_quicklink_collection)) {
    $variables['unit_quicklinks'] = $unit->field_quicklink_collection->entity->field_links;
  }
  if (count($unit->field_tagline)) {
    $variables['tagline'] = $unit->field_tagline[0]->value;
  }

  if (count($unit->field_tagline_superhead)) {
    $variables['tagline_superhead'] = $unit->field_tagline_superhead[0]->value;
  }
  else {
    $variables['tagline_superhead'] = theme_get_setting('tagline_superhead');
  }
  
  if (count($unit->field_page_banner_background)) {
    if ($e = $unit->field_page_banner_background->entity) {
      if ($f = $e->field_image->entity) {
        $style = ImageStyle::load('page_header');
        if ($style) {
          $url = $style->buildUrl($f->getFileUri());
          $variables['unit_page_header_banner'] = $url;
        }
      }
    }
  }

  if ($title_override) {
    $variables['title_override'] = $unit->name->value;
  }

  if (count($unit->field_footer_title_override)) {
    if ($unit->field_footer_title_override->value) {
      $variables['unit_footer_override'] = $unit->field_footer_title_override->value;
    }
  }

  foreach ($unit->field_address as $f) {
    $variables['unit_address'][] = $f->value;
  }

  if (count($unit->field_social_media_override)) {
    $variables['unit_social_menu'] = $unit->field_social_media_override;
  }

  $variables['unit_phone'] = (count($unit->field_contact_phone))? $unit->field_contact_phone[0]->value : null;
  $variables['unit_email'] = (count($unit->field_contact_email))? $unit->field_contact_email[0]->value : null;

  if (count($unit->field_header_style) && $unit->field_header_style->entity) {
    switch ($unit->field_header_style->entity->name->value) {
      case 'unit landing':
        $variables['is_landing_page'] = TRUE;
        break;
      case 'center':
        $variables['is_center_page'] = TRUE;
        break;
    }
  }

  if (count($unit->field_logo)) {
    $variables['center_logo'] = check_markup($unit->field_logo[0]->value, 'svg');
  }

  // inject a map
  if (count($unit->field_building_id)) {
    $building_id = $unit->field_building_id[0]->value;
    if (is_numeric($building_id)) {
      $variables['unit_map'] = [
        '#markup' => '<iframe height="100%" width="100%" frameborder="0" scrolling="no" marginheight="0" marginwidth="0" src="https://maps.uky.edu/campusmap/embedded/?Map=Perspective&amp;Bldg=' . $building_id . '&amp;MapHighlightColor=0,51,204"> </iframe>',
        '#allowed_tags' => ['iframe'],
      ];
    }
  }

}

function ukd8_meta_lookup(&$variables, $term_name, $title_override = FALSE) {
  // lookup based on a specific term
  $query = \Drupal::entityQuery('taxonomy_term')
      ->condition('vid', 'units')
      ->condition('name', $term_name);
  $tids = $query->execute();
  if (count($tids)) {
      $tid = array_shift($tids);
      $unit = Term::load($tid);
      ukd8_unit_vars($variables, $unit, $title_override);
  }
}

function ukd8_inject_unit_meta($node, &$variables) {
  if (count($node->field_unit_ref)) {
      $unit = $node->field_unit_ref->first()->entity;
      ukd8_unit_vars($variables, $unit);
  }
}

function ukd8_inject_block(&$variables, $key, $block_id) {
  $block = Block::load($block_id);
  if ($block) {
    $variables[$key] = \Drupal::entityTypeManager()
        ->getViewBuilder('block')
        ->view($block); 
  }
}

function ukd8_inject_series_meta($node, &$variables) {
  if (count($node->field_series_ref)) {
      $series = $node->field_series_ref->first()->entity;
      $variables['series_name'] = $series->name->value;
      $variables['series_tid'] = $series->id();
  }
}

function ukd8_term_name_lookup($tid) {
  $term = Term::load($tid);
  if ($term) {
    return $term->name->value;
  }
  return null;
}