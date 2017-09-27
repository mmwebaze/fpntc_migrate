<?php
namespace Drupal\fpntc_migrate\Plugin\migrate\process;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\Row;

/**
 * Node body field creation plugin
 *
 * @MigrateProcessPlugin(
 *   id = "taxonomy_term_tid"
 * )
 *
 */
class ResourceTaxonomy extends ProcessPluginBase {
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property){
      $term = \Drupal::entityTypeManager()
        ->getStorage('taxonomy_term')
        ->loadByProperties(['name' => $value]);
    return current($term)->id();
  }
}