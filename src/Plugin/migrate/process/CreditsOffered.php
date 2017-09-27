<?php

namespace Drupal\fpntc_migrate\Plugin\migrate\process;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\Row;

/**
 * Node body field creation plugin
 *
 * @MigrateProcessPlugin(
 *   id = "ce_credits_offered_plugin"
 * )
 *
 */
class CreditsOffered extends ProcessPluginBase{
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property){
    if (strtolower($value) == 'yes'){
      return 1;
    }
    else{
      return 0;
    }
  }
}