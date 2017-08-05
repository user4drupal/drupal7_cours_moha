<?php
function formation_calculatrice($form, &$form_state){
	$form = array();

	$form['presentation'] = array(
	  '#type' => 'select',
	  '#title' => t('Choose a display type.'),
	  '#options' => array(
	    'radios' => t('Radios'),
	    'select' => t('Select'),
	  ),
	  '#ajax' => array(
	    'wrapper' => 'operation',
	    'callback' => 'presentation_ajax_callback',
	  )
	);
	
	$form['value1'] = array(
     '#type' => 'textfield',
     '#title' => t('First value'),
     '#description' => t('Enter first numeric value.'),
     '#size' => '20',
     '#required' => TRUE,
     '#prefix' => '<div class="formation-bg">',
     '#suffix' => '</div>',
     '#default_value' => '1',
   );

	$operation_type = isset($form_state['values']['presentation']) ?
    $form_state['values']['presentation'] : 'radios';

	$form['operator'] = array(
     '#type' => $operation_type,
     '#title' => t('Operator'),
     '#description' => t('Choose an operator.'),
     '#options' => array(
     'addition'       => t('Plus'),
     'soustraction'   => t('Minus'),
     'multiplication' => t('Multiply'),
     'division'       => t('Divide'),
     ),
     '#default_value' => 'addition',
     '#prefix' => '<div id="operation">',
     '#suffix' => '</div>',
   );

	$form['value2'] = array(
     '#type' => 'textfield',
     '#title' => t('Second value'),
     '#description' => t('Enter second numeric value.'),
     '#size' => '20',
     '#required' => TRUE,
     '#prefix' => '<div class="formation-bg">',
     '#suffix' => '</div>',
     '#default_value' => '1',
   );

	$form['calculate'] = array(
     '#type' => 'submit',
     '#value' => t('Calculate'),
   );

	 if (isset($form_state['resultat'])) {
     $form['resultat'] = array(
       '#type' => 'markup',     // Type par défaut.
       '#markup' => '<h2>' . $form_state['resultat'] . '</h2>',
       '#prefix' => '<div style="background:yellow">',
       '#suffix' => '</div>',
     );
   }

	$form['#validate'] = array('formation_calculatrice_validation');

	$form['#submit'] = array('formation_calculatrice_traitement');

	return $form;
}

function formation_calculatrice_validation($form, &$form_state){
	if(!is_numeric($form_state['values']['value1'])){
		form_set_error('value1', t('Field 1 must be numeric'));
	}

	if(!is_numeric($form_state['values']['value2'])){
		form_set_error('value2', t('Field 2 must be numeric'));
	}

	if($form_state['values']['operator'] == 'division' && $form_state['values']['value2'] == 0)  {
		form_set_error('value2', t('Field 2 must be positif number'));
	}
}

function formation_calculatrice_traitement($form, &$form_state){
	$operation = $form_state['values']['operator'];
   	$valeur1   = $form_state['values']['value1'];
   	$valeur2   = $form_state['values']['value2'];

	
	switch ($operation) {
		case 'addition':
			$resultat = $valeur1 + $valeur2;
			$form_state['resultat'] = $resultat;
       		$form_state['rebuild'] = TRUE;
			break;
		case 'soustraction':
			$resultat = $valeur1 - $valeur2;
			$form_state['resultat'] = $resultat;
       		$form_state['rebuild'] = TRUE;
			break;
		case 'multiplication':
			$resultat = $valeur1 * $valeur2;
			$form_state['resultat'] = $resultat;
       		$form_state['rebuild'] = TRUE;
			break;
		case 'division':
			$resultat = $valeur1 / $valeur2;
			$form_state['resultat'] = $resultat;
       		$form_state['rebuild'] = TRUE;
			break;

	}


function presentation_ajax_callback($form, &$form_state) {
   // On renvoie la portion du formulaire php
   // que l'on veut modifier (ici le champ opération).
   return $form['operator'];
 }
}

function formation_block_color_admin_form($form, &$form_state) {
   $form = array();

   $form['formation_block_color_region'] = array(
     '#title' => t('Choose a region.'),
     '#type' => 'select',
     '#options' => system_region_list(variable_get('theme_default')),
     '#default_value' => variable_get('formation_block_color_region', ''),
   );

   $form['formation_block_color'] = array(
     '#title' => t('Choose a color for the blocks.'),
     '#type' => 'select',
     '#options' => array(
       '' => t('none'),
       'blue-class' => t('blue'),
       'orange-class' => t('orange'),
       'green-class' => t('green'),
     ),
     '#default_value' => variable_get('formation_block_color', ''),
   );

   return system_settings_form($form);
 }