<?php

$_SERVER['REMOTE_ADDR'] = '127.0.0.1';

define('DS', DIRECTORY_SEPARATOR);
define ('PATH', DS . '..' . DS . '..' . DS . '..' . DS . '..' . DS );
define('DRUPAL_ROOT', realpath(dirname(__FILE__) ) . PATH );
set_include_path(DRUPAL_ROOT . get_include_path());

include_once DRUPAL_ROOT . 'includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

class menu_for_all_test extends PHPUnit_Framework_TestCase
{

  public function test_function_help()
  {
    $output = '<h3>A propos du module : Menu for all</h3>';
    $output .= '<p>Exemple de module pour le livre : Drupal Avancé aux éditions Eyrolles</p>';
    $this->assertEquals(     menu_for_all_help('admin/help#menu_for_all'), $output	);
  }


  public function test_ajouter_page()
  {
    $status_noeud=$this->creation_page();
    $this->assertEquals(1, $status_noeud->status);
  }


  public function creation_page()
  {
    $node = new stdClass();
    $node->title = "Page de test";
    $node->body = "Une page de test avec PHPUnit";
    $node->type = "page";
    $node->promote = 1;
    node_save($node);

    return $node;
  }


}
?>
