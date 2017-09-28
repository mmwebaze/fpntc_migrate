<?php

namespace Drupal\fpntc_migrate\Util;

class CsvHandler {
  public static function readCsv($path_to_file) {
    $file_system = \Drupal::service('file_system');
    $content = array();
    $path = $file_system->realpath($path_to_file);

    if (file_exists($path) == 1) {
      $file = fopen($path, "r");
      $line_count = 0;
      $header_row = [];
      $body = [];
      while (($line = fgetcsv($file)) !== false) {

        if ($line_count == 0){
          foreach ($line as $key => $header){
            $header_row[$header] = $key;
          }
          $content['header'] = $header_row;
        }
        else{
          $body[$line_count] = $line;
        }
        $line_count++;
      }
      $content['body'] = $body;
      fclose($file);
    }

    return $content;
  }
}