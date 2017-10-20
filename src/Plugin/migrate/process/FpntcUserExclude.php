<?php

namespace Drupal\fpntc_migrate\Plugin\migrate\process;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\MigrateSkipRowException;
use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\Row;

/**
 * FPnct exclude already migrated users based on user email address.
 *
 * @MigrateProcessPlugin(
 *   id = "fpntc_user_exclude"
 * )
 *
 */
class FpntcUserExclude extends ProcessPluginBase {
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property){
    $exclude_users = [
      'katie_saul@jsi.com', 'daniel_cothran@jsi.com', 'cbateman@jsi.com','costelloef@gmail.com',
      'theresa_russo@jsi.com', 'anna_laurence@jsi.com','elizabeth_costello@jsi.com'
    ];
    if (in_array($value, $exclude_users)) {
      $message = !empty($this->configuration['message']) ? $this->configuration['message'] : '';
      throw new MigrateSkipRowException($message);
    }
    return $value;
  }
}