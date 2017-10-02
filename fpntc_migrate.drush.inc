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
  $module_path = drupal_get_path('module', 'fpntc_migrate');
  $content_settings = file_get_contents($module_path.'/config/node.update.settings.yml');
  $loaded_settings = Yaml::parse($content_settings)['resource.settings'];

  $id = $loaded_settings['id'];
  $delimiter = $loaded_settings['delimiter'];
  $path = $loaded_settings['path'];
  $destinations = $loaded_settings['destinations'];

  $content = CsvHandler::readCsv($path);

  foreach ($destinations as $destination => $fields){
    if(count($fields) > 0){
      $columns = [];
      foreach ($fields as $field) {
        array_push($columns, $content['header'][$field]);
      }
      $row = 0;
      foreach ($content['body'] as $line){
        $tids = [];
        foreach ($columns as $column){
          if (!empty($line[$column])){
            $term_names = explode($delimiter,$line[$column]);

            foreach ($term_names as $term_name){
              $term = \Drupal::entityTypeManager()
                ->getStorage('taxonomy_term')
                ->loadByProperties(['name' => $term_name]);
              if (count($term) > 0){
                array_push($tids, current($term)->id());
              }
              else{
                //throw new Exception('Error @row content'.$row);
                var_dump('Error @row content'.$row.' => '.$line[$column]);

              }
            }
          }
          //array_push($str, $line[$column]);

        }
        foreach ($tids as $tid){
          $storage = \Drupal::service('entity_type.manager')->getStorage('node');
          $ids = $storage->getQuery()
            ->condition('title', $line[$id])
            ->execute();
          $nodes = $storage->loadMultiple($ids);

          if(count($nodes) == 1){
            var_dump('Now updating....');
            $node = current($nodes);
            $options = $node->get($destination)->getValue();
            /*foreach ($options as $option){
              var_dump(array_values($option));
            }
            var_dump($options);*/
            array_push($options, ['target_id' => $tid]);

            $node->set($destination, $options);
            $node->save();
            //var_dump($node->get($destination)->getValue());
          }
        }
        $row++;
      }
    }
  }
}