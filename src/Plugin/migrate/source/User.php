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
    //get user zipcode
    $zip = $this->select('field_data_field_user_zip', 'uz')
      ->fields('uz', ['field_user_zip_value','entity_id'])
      ->condition('entity_id', $row->getSourceProperty('uid'))
      ->execute()
      ->fetchCol();
    $row->setSourceProperty('zipcode', $zip);

    //Get user agency name
    /*$agency_name = $this->select('field_data_field_user_agency_name', 'uan')
      ->fields('uan', ['field_user_agency_name_value','entity_id'])
      ->condition('entity_id', $row->getSourceProperty('uid'))
      ->execute()
      ->fetchCol();
    $row->setSourceProperty('agency_name', $agency_name);*/

    $field_name = [];
    //get user first name
    $firstname = $this->select('field_data_field_user_first_name', 'ufn')
      ->fields('ufn', ['field_user_first_name_value','entity_id'])
      ->condition('entity_id', $row->getSourceProperty('uid'))
      ->execute()
      ->fetchCol();
    $row->setSourceProperty('firstname', $firstname);
    $field_name['given'] = $firstname[0];

    //get user last name
    $lastname = $this->select('field_data_field_user_last_name', 'uln')
      ->fields('uln', ['field_user_last_name_value','entity_id'])
      ->condition('entity_id', $row->getSourceProperty('uid'))
      ->execute()
      ->fetchCol();
    $field_name['family'] = $lastname[0];

    $row->setSourceProperty('field_name', $field_name);
    return parent::prepareRow($row);
  }
}