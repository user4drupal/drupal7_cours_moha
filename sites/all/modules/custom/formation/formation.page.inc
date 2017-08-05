<?php

function formation_page(){

  $name = user_is_logged_in() ? $GLOBALS['user']->name : t('guest');
  $output = '<p>' . t('You are on the Formation page. Your name is %name',
                    array('%name' => $name)) . '</p>';

  return $output;
}

function formation_rss($arg1 = '1', $arg2 = NULL, $arg3 = NULL){
	$xml = genere_flux(array($arg1, $arg2, $arg3));
	drupal_add_http_header('Content-Type', 'application/rss+xml; charset=utf-8');
	print $mxl;
}

function formation_liste_noeuds_page($nodetype = '') {

  // Une amélioration possible (non demandée dans l’exercice)
  // serait d’afficher la liste de tous les types de noeud
  // au cas où aucun $nodetype n’est précisé.
  // La fonction node_type_get_names() permet de récupérer
  // dans la base de données la liste des types de noeud existants.
  $all_types = node_type_get_names();
  //dpm($all_types);
  if (!$nodetype) {
    foreach ($all_types as $name => $title) {
      $items[] = l(t($title), current_path() . '/' . $name);
    }
    $output = theme('item_list', array('items' => $items));
  }
  else {
    // Récupère le NID et le titre de tous les noeuds de type $nodetype.
    // Requête "classique".
    /*$result = db_query("SELECT nid, title
              		FROM {node}
              		WHERE type = :nodetype
              		ORDER BY title ASC",
    		            array(':nodetype' => $nodetype)
    		      );*/
    // Variante : on ne liste que 10 noeuds en utilisant une pagination.
    $query = db_select('node', 'n')
              ->fields('n', array('nid', 'title'))
              ->condition('type', $nodetype, '=')
              ->orderBy('title', 'ASC')
  						->extend('PagerDefault')     //Pager Extender
              ->limit(10);
    $result = $query->execute();

    $type_name = $all_types[$nodetype];
    // Crée un lien vers chaque noeud, et stocke le lien dans un tableau $items.
    $items = array();
    foreach ($result as $record) {
      // La fonction l() renvoie un lien <a href="">...</a>.
      // Elle prend 2 arguments :
      //   - le texte du lien (ici : le titre du noeud)
      //   - le chemin du lien (ici : node/NID)
      // Si les alias d'URL sont activés, la fonction l() les utilisera
      // automatiquement pour construire le lien.
      $items[] = l($record->title, 'node/' . $record->nid);
    }
    // Prépare les variables pour theme_item_list().
    $variables = array(
  	  'items' => $items,
  	  'title' => 'List of ' . $type_name,
    );
    // Renvoie la liste des noeuds formatés avec la fonction theme_item_list().
    $output = theme('item_list', $variables);
    // On ajoute ici la pagination avec la fonction theme_pager().
    $output .= theme('pager');
  }

  return $output;
}

function formation_statistics_page($node) {
  $compteur = formation_get_compteur($node->nid);
  //dpm($compteur);

  // Version 1 - Le HTML est généré directement par la fonction de callback.
 return t("The node %title has been viewed %compteur time(s).",
               array('%title' => $node->title, '%compteur' => $compteur,));

  // Version 2 - Le HTML est généré par une fonction de thème (c'est mieux !!).
//  return theme('formation_compteur', array('compteur' => $compteur, 'node' => $node));

  // Version 3 - On utilise un Render Array (c'est encore mieux !).
   
}

