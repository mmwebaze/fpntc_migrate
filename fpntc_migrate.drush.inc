<?php

function fpntc_migrate_drush_command(){
  $items['fpntc-migrate'] = [
    'description' => 'fpntc migrate',
    'aliases' => ['fp'],
  ];

  return $items;
}

function drush_fpntc_migrate(){
  $nids = \Drupal::entityQuery('node')->condition('type','resource')->execute();
  $nodes =  \Drupal\node\Entity\Node::loadMultiple($nids);

  foreach ($nodes as $node) {
    var_dump($node->get('field_intended_audience')->getValue());
    var_dump($node->get('field_resource_file')->getValue());
    //var_dump($node->label());
    die();
  }

}