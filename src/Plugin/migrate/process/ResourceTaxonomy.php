<?php
namespace Drupal\fpntc_migrate\Plugin\migrate\process;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\Row;

/**
 * Processes taxonomy id by label
 *
 * @MigrateProcessPlugin(
 *   id = "taxonomy_term_tid"
 * )
 *
 */
class ResourceTaxonomy extends ProcessPluginBase {
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property){
    /*$tids = [];
    foreach (explode('-',$value) as $name){
      $term = \Drupal::entityTypeManager()
        ->getStorage('taxonomy_term')
        ->loadByProperties(['name' => $name]);

      array_push($tids, current($term)->id());
    }

    return $tids;*/

      $term = \Drupal::entityTypeManager()
        ->getStorage('taxonomy_term')
        ->loadByProperties(['name' => $value]);
    return current($term)->id();
  }
}