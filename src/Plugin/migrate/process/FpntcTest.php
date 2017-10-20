<?php

namespace Drupal\fpntc_migrate\Plugin\migrate\process;


use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\Row;

/**
 * Node body field creation plugin
 *
 * @MigrateProcessPlugin(
 *   id = "fpntc_test"
 * )
 *
 */
class FpntcTest extends ProcessPluginBase {
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property){
    var_dump('******************************');
    //die();
    return $value;
  }
}