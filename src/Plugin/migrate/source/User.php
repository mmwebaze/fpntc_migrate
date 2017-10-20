<?php

namespace Drupal\fpntc_migrate\Plugin\migrate\source;

use Drupal\migrate\Plugin\migrate\source\SqlBase;
use Drupal\migrate\Row;

/**
 * fpntc user from the d7 database
 *
 * @MigrateSource(
 *   id = "fpntc_user_sql"
 * )
 *
 */
class User extends SqlBase {

  public function fields() {
    $fields = [
      'uid' => $this->t('User ID'),
      'name' => $this->t('Unique username'),
      'pass' => $this->t('User password hashed'),
      'mail' => $this->t('User email address'),
      'status' => $this->t('Whether the user is active(1) or blocked(0)'),
      'timezone' => $this->t('User timezone'),
      'init' => $this->t('E-mail address used for initial account creation.'),
    ];

    return $fields;
  }

  public function getIds() {
    return [
      'uid' => [
        'type' => 'integer'
      ]
    ];
  }

  public function query() {
    $query =  $this->select('users', 'u');
    #$query->innerJoin('field_data_field_user_first_name','ufn', 'u.uid = ufn.entity_id');
    #$query->innerJoin('field_data_field_user_last_name','uln', 'u.uid = uln.entity_id');
   # $query->innerJoin('field_data_field_user_zip','uz', 'u.uid = uz.entity_id');
    $query->fields('u', array_keys($this->fields()))
    #->fields('ufn', ['field_user_first_name_value'])
    #->fields('uln', ['field_user_last_name_value'])
    #->fields('uz', ['field_user_zip_value'])
      //->innerJoin('field_data_field_user_first_name', 'ufn')
      ->condition('uid', 1, '>');

    return $query;
  }
  public function prepareRow(Row $row) {
    $zip = $this->select('field_data_field_user_zip', 'uz')
      ->fields('uz', ['field_user_zip_value','entity_id'])
      ->condition('entity_id', $row->getSourceProperty('uid'))
      ->execute()
      ->fetchCol();
    $row->setSourceProperty('zipcode', $zip);
    $field_name = [];
    $firstname = $this->select('field_data_field_user_first_name', 'ufn')
      ->fields('ufn', ['field_user_first_name_value','entity_id'])
      ->condition('entity_id', $row->getSourceProperty('uid'))
      ->execute()
      ->fetchCol();
    $row->setSourceProperty('firstname', $firstname);
    $field_name['given'] = $firstname[0];
    var_dump($firstname);

    $lastname = $this->select('field_data_field_user_last_name', 'uln')
      ->fields('uln', ['field_user_last_name_value','entity_id'])
      ->condition('entity_id', $row->getSourceProperty('uid'))
      ->execute()
      ->fetchCol();
    $field_name['family'] = $lastname[0];
    var_dump($field_name);
    //die();
    $row->setSourceProperty('field_name', $field_name);
 /* select u.name, ufn.field_user_first_name_value, uln.field_user_last_name_value, uz.field_user_zip_value from users u
  inner join field_data_field_user_first_name ufn on (u.uid = ufn.entity_id)
  inner join field_data_field_user_last_name uln on (u.uid = uln.entity_id)
  inner join field_data_field_user_zip uz on (u.uid = uz.entity_id)
  LIMIT 10*/
    return parent::prepareRow($row);
  }
}