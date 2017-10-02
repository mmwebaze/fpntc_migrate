<?php
use Symfony\Component\Yaml\Yaml;
use Drupal\fpntc_migrate\Util\CsvHandler;

/**
 * Implements hook_drush_command().
 */
function fpntc_migrate_drush_command(){
  $items['fpntc-migrate'] = [
    'description' => 'fpntc update nodes migrate',
    'aliases' => ['fp'],
  ];

  return $items;
}

function drush_fpntc_migrate(){
  /*$module_path = drupal_get_path('module', 'fpntc_migrate');
  $content_settings = file_get_contents($module_path.'/config/node.update.settings.yml');
  $loaded_settings = Yaml::parse($content_settings)['resource.settings'];

  $id = $loaded_settings['id'];
  $path = $loaded_settings['path'];
  $destinations = $loaded_settings['destinations'];

  $content = CsvHandler::readCsv($path);

  foreach ($destinations as $destination => $fields){
    if(count($fields) > 0){
      $columns = [];
      foreach ($fields as $field) {
        array_push($columns, $content['header'][$field]);
      }
      foreach ($content['body'] as $line){
        $tids = [];
        foreach ($columns as $column){
          var_dump(empty($line[$column]).' '.$line[$column]);
          if (!empty($line[$column])){
            $term = \Drupal::entityTypeManager()
              ->getStorage('taxonomy_term')
              ->loadByProperties(['name' => $line[$column]]);
            array_push($tids, current($term)->id());
          }
          //array_push($str, $line[$column]);

        }
        foreach ($tids as $tid){
          $storage = \Drupal::service('entity_type.manager')->getStorage('node');
          $ids = $storage->getQuery()
            ->condition('title', $line[1])
            ->execute();
          $nodes = $storage->loadMultiple($ids);

          if(count($nodes) == 1){
            $node = current($nodes);
            $options = $node->get($destination)->getValue();
            foreach ($options as $option){
              var_dump(array_values($option));
            }
            var_dump($options);
            var_dump('---------------------');
            array_push($options, ['target_id' => $tid]);
            var_dump($options);
            var_dump('@@@@---------------------');
            var_dump($options);
            var_dump('---------------------');
            $node->set($destination, $options);
            $node->save();
            var_dump($node->get($destination)->getValue());
          }
        }

      }
    }
  }*/
//Increase knowledge
  $term = \Drupal::entityTypeManager()
    ->getStorage('taxonomy_term')
    ->loadByProperties(['name' => 'Increase knowledgeD']);

  var_dump(count($term).' bbbb');
  $time = '';
  var_dump(strtotime($time));
  var_dump(time());
  /*$storage = \Drupal::service('entity_type.manager')->getStorage('node');
  $ids = $storage->getQuery()
    ->condition('type', 'resource')
    ->execute();
  $nodes = $storage->loadMultiple($ids);

  foreach ($nodes as $node) {
    var_dump($node->label());die();
  }

  var_dump(count($nodes));*/

 /* $nids = \Drupal::entityQuery('node')->condition('type','resource')->execute();
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