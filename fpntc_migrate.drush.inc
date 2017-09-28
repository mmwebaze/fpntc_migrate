<?php
use Symfony\Component\Yaml\Yaml;
use Drupal\fpntc_migrate\Util\CsvHandler;

function fpntc_migrate_drush_command(){
  $items['fpntc-migrate'] = [
    'description' => 'fpntc migrate',
    'aliases' => ['fp'],
  ];

  return $items;
}

function drush_fpntc_migrate(){
  $module_path = drupal_get_path('module', 'fpntc_migrate');
  $content_settings = file_get_contents($module_path.'/config/node.update.settings.yml');
  $loaded_settings = Yaml::parse($content_settings)['resource.settings'];

  $id = $loaded_settings['id'];
  $path = $loaded_settings['path'];
  $destinations = $loaded_settings['destinations'];

  $content = CsvHandler::readCsv($path);

  foreach ($destinations as $nodeField => $destination){
    if(count($destination) > 0){
      $columns = [];
      foreach ($destination as $item) {
        array_push($columns, $content['header'][$item]);
      }
      foreach ($content['body'] as $line){
        $tids = [];
        foreach ($columns as $column){
          //array_push($str, $line[$column]);
          $term = \Drupal::entityTypeManager()
            ->getStorage('taxonomy_term')
            ->loadByProperties(['name' => $line[$column]]);
          array_push($tids, current($term)->id());
        }
        foreach ($tids as $tid){
          var_dump($line[1].'&&');die();
          $storage = \Drupal::service('entity_type.manager')->getStorage('node');
          $ids = $storage->getQuery()
            ->condition('title', $line[1])
            ->execute();
          $nodes = $storage->loadMultiple($ids);
          var_dump(count($nodes)); die();
        }

      }
    }
  }

  $storage = \Drupal::service('entity_type.manager')->getStorage('node');
  $ids = $storage->getQuery()
    ->condition('type', 'resource')
    ->execute();
  $nodes = $storage->loadMultiple($ids);

  foreach ($nodes as $node) {
    var_dump($node->label());die();
  }

  var_dump(count($nodes));

  /*$nids = \Drupal::entityQuery('node')->condition('type','resource')->execute();
  $nodes =  \Drupal\node\Entity\Node::loadMultiple($nids);

  foreach ($nodes as $node) {
    $settings = $node->getFieldDefinitions();
    //var_dump($settings['field_resource_link']);
    var_dump($node->get('field_intended_audience')->getValue());
    //var_dump($node->get('field_resource_file')->getValue());
    //var_dump($node->label());
    die();
  }*/

}