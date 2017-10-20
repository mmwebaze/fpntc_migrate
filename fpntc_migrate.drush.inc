<?php
use Symfony\Component\Yaml\Yaml;
use Drupal\fpntc_migrate\Util\CsvHandler;

/**
 * Implements hook_drush_command().
 */
function fpntc_migrate_drush_command(){
  $items['fpntc-migrate'] = [
    'description' => 'fpntc update nodes migrate',
    'arguments' => ['entity' => 'The type of entity reference field being updated.'],
    'aliases' => ['fp'],
  ];

  return $items;
}

function drush_fpntc_migrate($entity){
  $storage = \Drupal::service('entity_type.manager')->getStorage('user');
  $users = $storage->loadMultiple();
 // $nodes = $storage->loadMultiple($ids);
  foreach ($users as $user){
    if ($user->id() == 0 || $user->id() == 1){

    }
    else{
      var_dump('deleting user with id '+$user->id());
      $user->delete();
    }
  }

  die();
  $correct_args = array('term', 'file');
  if (!in_array($entity, $correct_args)) {
    return drush_set_error(dt('"@type" is not a valid statement type. Please choose between "term" and "file".',
      array('@entity' => $entity)));
  }

  $module_path = drupal_get_path('module', 'fpntc_migrate');
  $content_settings = file_get_contents($module_path.'/config/node.update.settings.yml');
  $loaded_settings = Yaml::parse($content_settings)['resource.settings'];

  $id = $loaded_settings['id'];
  $delimiter = $loaded_settings['delimiter'];
  $path = $loaded_settings['path'];
  $destinations = $loaded_settings['entity'][$entity]['destinations'];
  $file_source_uri = $loaded_settings['file_source_uri'];
  $file_dest_uri = $loaded_settings['file_dest_uri'];

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
            if ($entity == 'term'){
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
            else{
              $files = explode(',',$line[$column]);
              //$uri  = file_unmanaged_copy('public://source.jpg', 'public://destination.jpg', FILE_EXISTS_REPLACE);
              foreach ($files as $file){
                $bestanden = explode('|',$file);
                $uri  = file_unmanaged_copy($file_source_uri.'/'.$bestanden[0], $file_dest_uri.'/'.$bestanden[0], FILE_EXISTS_REPLACE);
                //die();
                if ($uri){
                  $file = \Drupal\file\Entity\File::Create([
                    'uri' => $uri,
                  ]);
                  $file->save();
                  $nodes = get_nodes($line[$id]);

                  if(count($nodes) == 1){
                    $node = current($nodes);
                    update_nodes($node, $destination, $file->id(), $bestanden[1]);
                  }
                }
              }
            }
          }
          //array_push($str, $line[$column]);

        }
        foreach ($tids as $tid){
          /*$storage = \Drupal::service('entity_type.manager')->getStorage('node');
          $ids = $storage->getQuery()
            ->condition('title', $line[$id])
            ->execute();
          $nodes = $storage->loadMultiple($ids);*/
          $nodes = get_nodes($line[$id]);

          if(count($nodes) == 1){
            $node = current($nodes);
            update_nodes($node, $destination, $tid);
            /*$options = $node->get($destination)->getValue();

            array_push($options, ['target_id' => $tid]);

            $node->set($destination, $options);
            $node->save();*/
            //var_dump($node->get($destination)->getValue());
          }
        }
        $row++;
      }
    }
  }
}

function get_nodes($node_title){
  $storage = \Drupal::service('entity_type.manager')->getStorage('node');
  $ids = $storage->getQuery()
    ->condition('title', $node_title)
    ->execute();
  $nodes = $storage->loadMultiple($ids);

  return $nodes;
}

function update_nodes($node, $destination, $id, $description = NULL){
  print('Updating field '.$destination);
  try{
    $options = $node->get($destination)->getValue();
    /*foreach ($options as $option){
      var_dump(array_values($option));
    }
    var_dump($options);*/
    $opties = [];

    if($description){
      $opties['description'] = $description;
    }
    $opties['target_id'] = $id;
    //array_push($options, ['target_id' => $id]);
    array_push($options, $opties);
    $node->set($destination, $options);
    $node->save();
  }
  catch (Exception $e){
    print('Exception caught: '.$e->getMessage());
  }
}