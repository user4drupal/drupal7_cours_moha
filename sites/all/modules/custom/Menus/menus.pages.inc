<?php
/**
  * Sur la page d'administration de l'entité Menus, on listera les bundles de ce typed'entité.
  Lorsque l'on cliquera sur les l'un des bundles, on sera redirigé sur la page permettant d'administrer 
  les champs et leur affichege
**/
function menus_admin($type = NULL){
    if ($type) {
        return drupal_get_form('menus_addmenu', $type);
    }
    else {
       $rows = array();
       $rows[] = array(l(t('Diner'), 'admin/menus/diner'));
       $rows[] = array(l(t('Gouter'), 'admin/menus/gouter'));
       $header = array('Type');
       $content = array(
           '#theme' => 'table',
           '#header' => $header,
           '#rows' => $rows
       );
       return $content;
    }
}
/**
	Ici, via le générateur de formulaire, On ajoute une entité
	de type Menus en fonction du bundle séléctionné.
**/
function menus_addmenu($form, &$form_state, $type) {
    // On ajoute le champ Nom de notre entité Menus
    $form['name'] = array(
        '#type' => 'textfield',
        '#title' => 'name'
    );

    // On crée une classe de style Drupal
    $menus = new stdClass();
    $menus->type = $type;
    // On définit l'objet Menus    
    $form['menus'] = array(
        '#type' => 'value',
        '#value' => $menus
    );
    // On définit le type de bundle afin de passer
    // la validation du formulaire
    
    $form['type'] = array(
        '#type' => 'value',
        '#value' => $type 
    );

    // On fournit les champs attachés au formulaire
    field_attach_form('menus', $menus, $form, $form_state);

    // On ajoute les actions du formulaire
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['add'] = array(
        '#type' => 'submit',
        '#value' => 'add'
    );
    return $form;
}

function menus_addmenu_validate($form, &$form_state) {
    entity_form_field_validate('menus', $form, $form_state);
}

function menus_addmenu_submit($form, &$form_state) {
    $menus = $form_state['values']['menus'];
    $menus->name = $form_state['values']['name'];
    // On enregistre les informations dans la table menus
    drupal_write_record('menus', $menus);
    // On injecte les données à l'objet avec mes paramètres
    // du formulaire
    entity_form_submit_build_entity('menus', $menus, $form, $form_state);
    // On récupère les champs d'autres éventuels modules
    field_attach_submit('menus', $menus, $form, $form_state);
    // On ajoute les données dans la BDD
    field_attach_insert('menus', $menus);
    // On affiche un message de confirmation de l'ajout
    drupal_set_message(
            t('Nouveau @type a été ajouté',
            array('@type' => $menus->type))
            );
}
