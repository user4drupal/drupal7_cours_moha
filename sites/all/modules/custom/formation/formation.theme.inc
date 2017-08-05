<?php
function theme_formation_compteur($variables) {
  $compteur = $variables['compteur'];
  $node     = $variables['node'];

  return t("The node %title has been viewed %compteur time(s). (theme function)",
              array('%title' => $node->title, '%compteur' => $compteur,));
}

function formation_preprocess_block(&$variables) {
  // On récupère le bloc qui va être affiché.
	$block = $variables['block'];
	// On récupère la région sélectionnée dqns le formulaire "formation_block_color_form".
	$region = variable_get('formation_block_color_region');
  // Si le bloc est positionné dans la région choisie, alors on lui ajoute une classe.
  if ($block->region == $region) {
    // On ajoute la classe stockée en base grâce au formulaire "formation_block_color_admin_form".
    $variables['classes_array'][] = variable_get('formation_block_color');
  }
}