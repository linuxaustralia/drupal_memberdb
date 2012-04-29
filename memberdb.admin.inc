<?php
/**
 * MemberDB settings form.
 */
function memberdb_admin_settings() {

  // This whole thing will fail if there is no 'memberdb' $db_url in settings.php.
  // So check for that first.
  global $db_url;
  if (!is_array($db_url) || empty($db_url['memberdb'])) {
    drupal_set_message(t('This module requires additional configuration. No $db_url named memberdb was found in your settings.php file. Please add one.'), 'error');
    $config = FALSE;
  }
  else {
    drupal_set_message(t('Your settings.php file contains a $db_url named memberdb.'));
    $config = TRUE;
  }

  // If the memberdb db_url wasn't found, expand this help section.
  $form = array();
  $form['help'] = array(
    '#type' => 'fieldset',
    '#title' => 'Help',
    '#collapsible' => TRUE,
    '#collapsed' => $config,
  );
  $form['help']['memberdb_help'] = array(
    '#type'  => 'markup',
    '#value' => memberdb_admin_settings_help(),
  );

  if ($config == FALSE) {
    return system_settings_form($form);
  }

  $form['memberdb'] = array(
    '#type' => 'fieldset',
    '#title' => 'Drupal Integration',
    '#description' => t('Please configure the MemberDB integration options below. These will ensure the correct member data is displayed on the user profile.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['memberdb']['memberdb_organisation'] = array(
    '#type' => 'select',
    '#title' => 'Organisation',
    '#description' => t('Select the MemberDB organisation for which you want to display data on this site.'),
    '#options' => memberdb_get_organisations(TRUE),
    '#default_value' => variable_get('memberdb_organisation', 0),
  );

  return system_settings_form($form);
}

/**
 * Creates the help text for the MemberDB settings page
 *
 * @return
 *   HTML with the help text
 */
function memberdb_admin_settings_help() {
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
