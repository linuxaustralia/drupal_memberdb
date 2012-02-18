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
    $display_help = TRUE;
  }

  // If the memberdb db_url wasn't found, expand this help section.
  $form = array();
  $form['help'] = array(
    '#type' => 'fieldset',
    '#title' => 'Help',
    '#collapsible' => TRUE,
    '#collapsed' => ($display_help) ? FALSE : TRUE,
  );
  $form['help']['memberdbtoboggan_help'] = array(
    '#type'  => 'markup',
    '#value' => memberdbtoboggan_settings_help(),
  );

  // If the MemberDB db_url wasn't found, display only the help section.
  if ($display_help) {
    return system_settings_form($form);
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
  }

  return system_settings_form($form);
}

/**
 * Helpfile for memberdbtoboggan.
 */

/**
 * Creates the help text for the MemberDB Toboggan settings page
 *
 * @return
 *   HTML with the help text
 */
function memberdbtoboggan_settings_help() {
  return t('
<p>To make use of the <em>memberdbtoboggan</em> module, Drupal needs to be able to access the MemberDB backend database.</p>
<p>You can configure this database by editing your settings.php file.</p>
<p>Modify the $db_url variable, so that instead of a string it is an array. The array should have at least a \'default\' key that contains the existing url for the Drupal database.
First, change:
<pre>
  $db_url = \'mysqli://username:password@localhost/database\';
</pre>
<p>To:</p>
<pre>
  $db_url = array();
  $db_url[\'default\'] = \'mysqli://username:password@localhost/database\';
</pre>
<p>You can now append the database url for the MemberDB database below the default url. You should give it the key \'memberdb\'.
<pre>
  $db_url = array();
  $db_url[\'default\'] = \'mysqli://username:password@localhost/database\';
  $db_url[\'radius\'] = \'mysqli://memberdb:secret@localhost/memberdb\';
</pre>
<p>The <em>memberdb</em> account needs to be able to read from and write to the table with account credentials and attributes.</p>
  ');
}
