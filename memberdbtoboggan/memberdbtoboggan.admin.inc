<?php
/**
 * UberCoova settings form.
 */
function memberdbtoboggan_settings() {

  // This whole thing will fail if there is no 'memberdb' $db_url in settings.php.
  // So check for that first.
  global $db_url;
  if (!is_array($db_url) || empty($db_url['memberdb'])) {
    drupal_set_message(t('This module requires additional configuration. No $db_url named memberdb was found in your settings.php file. Please add one.'), 'error');
  }

  $form['memberdbtoboggan_prefix'] = array(
    '#type' => 'textfield',
    '#title' => 'Username Prefix',
    '#description' => t('Prepend this string to the MemberDB ID to generate a Drupal username.'),
    '#default_value' => variable_get('memberdbtoboggan_prefix', 'la'),
  );

  $roles = array(0 => '<none>');
  $roles += user_roles(TRUE);
  $form['memberdbtoboggan_rid'] = array(
    '#type' => 'select',
    '#title' => 'Assign Role',
    '#description' => t('Assign this role to a Drupal user when it is newly created from the MemberDB database.'),
    '#options' => $roles,
    '#default_value' => variable_get('memberdbtoboggan_rid', 0),
  );

  if (module_exists('profile')) {
    $fields = array(0 => '<none>');
    $fields += memberdbtoboggan_profile_fields();

    $form['memberdbtoboggan_profile_firstname'] = array(
      '#type' => 'select',
      '#title' => 'Profile first name',
      '#description' => t('Transpose the MemberDB firstname to this profile field.'),
      '#options' => $fields,
      '#default_value' => variable_get('memberdbtoboggan_profile_firstname', 0),
    );

    $form['memberdbtoboggan_profile_surname'] = array(
      '#type' => 'select',
      '#title' => 'Profile last name',
      '#description' => t('Transpose the MemberDB lastname to this profile field.'),
      '#options' => $fields,
      '#default_value' => variable_get('memberdbtoboggan_profile_surname', 0),
    );

    $form['memberdbtoboggan_member_id'] = array(
      '#type' => 'select',
      '#title' => 'MemberDB ID',
      '#description' => t('Transpose the MemberDB ID to this profile field.'),
      '#options' => $fields,
      '#default_value' => variable_get('memberdbtoboggan_member_id', 0),
    );
  }

  return system_settings_form($form);
}
