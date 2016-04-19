<?php
/**
 * @file
 * This file provides administration form for the module.
 */

/**
 * Provides form for cookie control popup.
 */
function popup_message_admin_form($form_state) {

  global $language;
  $ln = $language->language;
  $popup_settings = popup_message_get_settings();

  $form['summary'] = array(
    '#type' => 'fieldset',
    '#title' => t('Summary'),
    '#weight' => 1,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['summary']['popup_message_' . $ln] = array (
    '#type'  => 'item',
    '#tree'   => TRUE,
  );

  if (module_exists('locale')) {
    $form['popup_message_' . $ln]['#title'] = t('You are editing settings for the %language language.', array('%language' => $language->name));
  }

  $form['summary']['popup_message_' . $ln]['popup_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable popup'),
    '#default_value' => isset($popup_settings['popup_enabled']) ? $popup_settings['popup_enabled'] : 0,
    '#description' => t('Check this, and enter the Date and time below to enable.'),
  );

  $form['summary']['popup_message_' . $ln]['popup_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Link'),
    '#default_value' => isset($popup_settings['popup_link']) ? $popup_settings['popup_link'] : '',
    '#size' => 60,
    '#maxlength' => 220,
    '#required' => TRUE,
    '#description' => t('Enter the link.  For external links prepend http://'),
  );

  $form['summary']['popup_message_' . $ln]['scheduled_date'] = array(
    '#type' => 'date_popup',
    '#date_format' => 'd/m/y - g:i a',
    '#title' => t('Schedule'),
    '#default_value' => isset($popup_settings['scheduled_date']) ? $popup_settings['scheduled_date'] : '',
    '#required' => TRUE,
  );

  $form['summary']['popup_message_' . $ln]['unscheduled_date'] = array(
    '#type' => 'date_popup',
    '#date_format' => 'd/m/y - g:i a',
    '#title' => t('Unschedule'),
    '#default_value' => isset($popup_settings['unscheduled_date']) ? $popup_settings['unscheduled_date'] : '',
    '#required' => TRUE,
  );

  $form['message'] = array(
    '#type' => 'fieldset',
    '#title' => t('Message'),
    '#weight' => 2,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['message']['popup_message_' . $ln] = array (
    '#type'  => 'item',
    '#tree'   => TRUE,
  );

  $form['message']['popup_message_' . $ln]['popup_agree_button_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Hide Popup Button Text'),
    '#default_value' => isset($popup_settings['popup_agree_button_message']) ? $popup_settings['popup_agree_button_message'] : t('Thanks for Letting Me Know'),
    '#size' => 30,
    '#required' => TRUE,
  );

  $form['message']['popup_message_' . $ln]['popup_disagree_button_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Find Out More Button Text'),
    '#default_value' => isset($popup_settings['popup_disagree_button_message']) ? $popup_settings['popup_disagree_button_message'] : t('Please Tell Me More'),
    '#size' => 30,
    '#required' => TRUE,
  );

  $form['message']['popup_message_' . $ln]['popup_info'] = array(
    '#type' => 'text_format',
    '#title' => t('Popup message'),
    '#default_value' => isset($popup_settings['popup_info']['value']) ? $popup_settings['popup_info']['value'] : '',
    '#required' => TRUE,
    '#format' => isset($popup_settings['popup_info']['#format']) ? $popup_settings['popup_info']['#format'] : 'full_html',
  );

  $form['attributes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Attributes'),
    '#weight' => 3,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['attributes']['popup_message_' . $ln] = array (
    '#type'  => 'item',
    '#tree'   => TRUE,
  );

  $form['attributes']['popup_message_' . $ln]['popup_clicking_confirmation'] = array(
    '#type' => 'checkbox',
    '#title' => t('Close Popup by clicking'),
    '#default_value' => isset($popup_settings['popup_clicking_confirmation']) ? $popup_settings['popup_clicking_confirmation'] : 1,
    '#description' => t('By default by clicking any link on the website the visitor accepts the cookie policy. Uncheck this box if you do not require this functionality. You may want to edit the pop-up message below accordingly.'),
  );

  $form['attributes']['popup_message_' . $ln]['popup_link_new_window'] = array(
    '#type' => 'checkbox',
    '#title' => t('Open link in a new window'),
    '#default_value' => isset($popup_settings['popup_link_new_window']) ? $popup_settings['popup_link_new_window'] : 0,
  );

  $form['attributes']['popup_message_' . $ln]['popup_position'] = array(
    '#type' => 'checkbox',
    '#title' => t('Place the pop-up at the top of the page'),
    '#default_value' => isset($popup_settings['popup_position']) ? $popup_settings['popup_position'] : 0,
    '#description' => t('By default the pop-up appears at the bottom of the page. Click this box if you want it to appear at the top'),
  );

  $form['attributes']['popup_message_' . $ln]['popup_delay'] = array(
    '#type' => 'textfield',
    '#title' => t('Popup time delay in seconds'),
    '#default_value' => isset($popup_settings['popup_delay']) ? $popup_settings['popup_delay'] : 1,
    '#size' => 5,
    '#maxlength' => 5,
    '#required' => TRUE,
  );

  if (module_exists('geoip') || module_exists('smart_ip')){
    $form['attributes']['popup_message_' . $ln]['eu_only'] = array(
      '#type' => 'checkbox',
      '#title' => t('Only display popup in EU countries (using the <a href="http://drupal.org/project/geoip">geoip</a> module or the <a href="http://drupal.org/project/smart_ip">smart_ip</a> module)'),
      '#default_value' => isset($popup_settings['eu_only']) ? $popup_settings['eu_only'] : 0,
    );
  }

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced'),
    '#weight' => 4,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['advanced']['popup_message_' . $ln] = array (
    '#type'  => 'item',
    '#tree'   => TRUE,
  );

  // Adding option to add/remove popup on specified domains
  $exclude_domains_option_active = array(
    0 => t('Add'),
    1 => t('Remove'),
  );
  $form['advanced']['popup_message_' . $ln]['domains_option'] = array(
    '#type' => 'radios',
    '#title' => t('Add/Remove popup on specified domains'),
    '#default_value' => isset($popup_settings['domains_option']) ? $popup_settings['domains_option'] : 1,
    '#options' => $exclude_domains_option_active,
    '#description' => t("Specify if you want to add or remove popup on the listed below domains."),
  );
  $form['advanced']['popup_message_' . $ln]['domains_list'] = array(
    '#type' => 'textarea',
    '#title' => t('Domains list'),
    '#default_value' => isset($popup_settings['domains_list']) ? $popup_settings['domains_list'] : '',
    '#description' => t("Specify domains with protocol (e.g. http or https). Enter one domain per line."),
  );

  $form['advanced']['popup_message_' . $ln]['exclude_paths'] = array(
    '#type' => 'textarea',
    '#title' => t('Exclude paths'),
    '#default_value' => isset($popup_settings['exclude_paths']) ? $popup_settings['exclude_paths'] : '',
    '#description' => t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>')),
  );

  $form['advanced']['popup_message_domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Domain (Optional)'),
    '#default_value' => variable_get('popup_message_domain', ''),
    '#description' => t('Sets the domain of the cookie to a specific url.  Used when you need consistency across domains.  This is language independent.'),
  );

  return system_settings_form($form);

}

/**
 * Validates form for cookie control popup.
 */
function popup_message_admin_form_validate($form, &$form_state) {
  global $language;
  $ln = $language-> language;

  if (!preg_match('/^[1-9][0-9]{0,4}$/', $form_state['values']['popup_message_' . $ln]['popup_delay'])) {
    form_set_error('popup_message_' . $ln . '][popup_delay', t('Delay must be an integer value.'));
  }

  $popup_link = $form_state['values']['popup_message_' . $ln]['popup_link'];
  //if the link contains a fragment then check if it validates then rewrite link with full url
  if ((strpos($popup_link, '#') !== FALSE) && (strpos($popup_link, 'http') === FALSE)) {
    $fragment = explode('#', $popup_link);
    $popup_link = url($fragment[0], array('fragment' => $fragment[1], 'absolute' => TRUE));
    form_set_error('popup_message_' . $ln . '][popup_link', t('Looks like your privacy policy link contains fragment #, you should make this an absolute url eg @link', array('@link' => $popup_link)));
  }

  cache_clear_all('popup_message_client_settings_' . $language->language, 'cache');
}
