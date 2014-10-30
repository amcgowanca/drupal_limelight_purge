<?php
/**
 * @file
 * limelight_purge.admin.inc
 */

/**
 * Form builder for the Limelight Purge configuration.
 *
 * @param array $form
 *   An array of form elements and properties.
 * @param array $form_state
 *   An array representing the current form's state.
 *
 * @return array
 *   Returns a system settings array.
 */
function limelight_purge_settings_form($form, $form_state) {
  $form['api_info'] = array(
    '#type' => 'fieldset',
    '#title' => t('API and Authentication'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['api_info']['limelight_purge_limelight_api_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#maxlength' => '128',
    '#default_value' => limelight_purge_limelight_api_username(),
  );
  $form['api_info']['limelight_purge_limelight_api_shortname'] = array(
    '#type' => 'textfield',
    '#title' => t('Shortname'),
    '#maxlength' => '60',
    '#default_value' => limelight_purge_limelight_api_shortname(),
  );
  $form['api_info']['limelight_purge_limelight_api_shared_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Shared key'),
    '#description' => t('The shared key can be retrieved within the Limelight control panel under <em>My settings</em> &rarr; <em>Edit my profile</em>.'),
    '#maxlength' => '128',
    '#default_value' => limelight_purge_limelight_api_shared_key(),
  );
  $form['purge_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Purge settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['purge_settings']['limelight_purge_limelight_purge_type'] = array(
    '#type' => 'select',
    '#title' => t('Purge type'),
    '#description' => t('The two primary purge types are <em>invalidate</em> and <em>delete</em>.') .
      theme('item_list', array('items' => array(
        t('Invalidate purge type will result in content on the edge servers being invalidated. On the next request, the edge server will revalidate content with the origin, but does not remove the asset from the server.'),
        t('Delete purge type will remove content from the edge servers. This may cause high traffic loads at the origin.'),
      ))),
    '#options' => array(
      LIMELIGHT_PURGE_LIMELIGHT_PURGE_TYPE_INVALIDATE => t('Invalidate'),
      LIMELIGHT_PURGE_LIMELIGHT_PURGE_TYPE_DELETE => t('Delete'),
    ),
    '#default_value' => limelight_purge_limelight_purge_type(),
  );
  $form['purge_settings']['limelight_purge_queue_process_on_cron'] = array(
    '#type' => 'radios',
    '#title' => t('Process purge queue on cron'),
    '#options' => array(
      1 => t('Yes'),
      0 => t('No'),
    ),
    '#default_value' => limelight_purge_queue_process_on_cron(),
  );
  return system_settings_form($form);
}
