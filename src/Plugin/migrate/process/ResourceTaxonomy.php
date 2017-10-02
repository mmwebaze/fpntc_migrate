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
    var_dump($value);

      $term = \Drupal::entityTypeManager()
        ->getStorage('taxonomy_term')
        ->loadByProperties(['name' => $value]);

    if (count($term) == 1){
      return current($term)->id();
    }
    return current($term)->id();
  }
}