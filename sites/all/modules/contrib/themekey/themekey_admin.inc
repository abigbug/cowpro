<?php

/**
 * @file
 * Contains all form manipulations to required by ThemeKey.
 *
 * @author Markus Kalkbrenner | bio.logis GmbH
 *   @see http://drupal.org/user/124705
 *
 * @author profix898
 *   @see http://drupal.org/user/35192
 */

require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'themekey') . '/themekey_base.inc';
require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'themekey') . '/themekey_build.inc';


/**
 * Form builder for the rule chain.
 *
 * The form will not be validated. All changes will be saved immediately.
 * Validation will happen when the form displays the stored configuration.
 * Otherwise all the drag'n'drop stuff will not work.
 *
 * @see themekey_form_alter()
 * @see themekey_rule_chain_form_submit()
 * @see themekey_rule_chain_form_set_error()
 *
 * @ingroup forms
 */
function themekey_rule_chain_form($form, &$form_state) {
  return themekey_abstract_rule_chain_form($form, $form_state, array(
    'load_rules_callback' => 'themekey_load_rules',
    'themes' => themekey_theme_options(TRUE, TRUE),
    'rule_delete_path' => 'admin/config/user-interface/themekey/rules/delete/',
  ));
}

function themekey_abstract_rule_chain_form($form, &$form_state, $options) {
  $properties = variable_get('themekey_properties', array());

  if (empty($properties)) {
    // first call of this form ever
    themekey_rebuild();
    $properties = variable_get('themekey_properties', array());
  }

  $attributes = variable_get('themekey_attributes', array());
  $operators = array(
    '=' => '=',
    '!' => '!',
    '*' => '*',
    '!*' => '!*',
    '<' => '<',
    '<=' => '<=',
    '>' => '>',
    '>=' => '>=',
    '~' => '~',
    '!~' => '!~',
  );

  $form = array('#tree' => TRUE);

  $items = array();
  $fix_depth = FALSE;
  if (empty($form_state['input']['old_items'])) {
    $items = $options['load_rules_callback']();
  }
  else {
    $items = $form_state['input']['old_items'];
    $fix_depth = TRUE;
  }

  $parent_options = array_merge(array(0), array_keys($items));
  $parent_options = array_combine($parent_options, $parent_options);
  foreach ($items as $item) {
    if ($fix_depth) {
      if (!empty($item['parent'])) {
        $item['depth'] = $items[$item['parent']]['depth'] + 1;
      }
      else {
        $item['depth'] = 0;
      }
    }

    $form['old_items'][$item['id']]['depth'] = array(
      '#type' => 'hidden',
      '#value' => $item['depth'],
    );

    $form['old_items'][$item['id']]['id'] = array(
      '#type' => 'hidden',
      '#value' => $item['id'],
    );

    $property = $item['property'];
    $wildcard = '';
    $static = FALSE;

    if (!in_array($property, $properties)) {
      if (!empty($attributes[$property]['static'])) {
        $static = TRUE;

        $form['old_items'][$item['id']]['property'] = array(
          '#type' => 'hidden',
          '#default_value' => $property,
          '#value' => $property,
          '#prefix' => '<span class="themekey-fadeable">' . $property . '</span>',
        );

        $form['old_items'][$item['id']]['operator'] = array(
          '#type' => 'hidden',
          '#default_value' => '=',
          '#value' => '=',
        );

        $form['old_items'][$item['id']]['value'] = array(
          '#type' => 'hidden',
          '#default_value' => 'static',
          '#value' => 'static',
        );

        $form['old_items'][$item['id']]['theme'] = array(
          '#type' => 'select',
          '#default_value' => 'default',
          '#options' => array('default' => t('Triggered')),
        );
      }
      else {
        $property = 'drupal:path:wildcard';
        $wildcard = $item['property'];
      }
    }

    if (!isset($form['old_items'][$item['id']]['property'])) {
      $form['old_items'][$item['id']]['property'] = array(
        '#type' => 'select',
        '#default_value' => $property,
        '#options' => $properties,
      );
    }

    $form['old_items'][$item['id']]['wildcard'] = array(
      '#type' => 'textfield',
      '#default_value' => $wildcard,
      '#size' => 10,
      '#maxlength' => 255,
    );

    if (!isset($form['old_items'][$item['id']]['operator'])) {
      $form['old_items'][$item['id']]['operator'] = array(
        '#type' => 'select',
        '#default_value' => $item['operator'],
        '#options' => $operators,
      );
    }

    if (!isset($form['old_items'][$item['id']]['value'])) {
      $form['old_items'][$item['id']]['value'] = array(
        '#type' => 'textfield',
        '#default_value' => $item['value'],
        '#size' => 20,
        '#maxlength' => 255,
      );
    }

    $form['old_items'][$item['id']]['parent'] = array(
      '#type' => 'select',
      '#default_value' => $item['parent'],
      '#options' => $parent_options,
    );

    if (!isset($form['old_items'][$item['id']]['theme'])) {
      $form['old_items'][$item['id']]['theme'] = array(
        '#type' => 'select',
        '#default_value' => $item['theme'],
        '#options' => $options['themes'],
      );
    }

    $form['old_items'][$item['id']]['enabled'] = array(
      '#type' => 'checkbox',
      '#default_value' => isset($item['enabled']) ? $item['enabled'] : FALSE,
    );

    $form['old_items'][$item['id']]['weight'] = array(
      '#type' => 'weight',
      '#delta' => 200,
      '#default_value' => $item['weight'],
    );

    $form['old_items'][$item['id']]['delete'] = array(
      '#markup' => $static ? '' : l(t('delete'), $options['rule_delete_path'] . $item['id']),
    );

    $form['old_items'][$item['id']]['module'] = array(
      '#type' => 'hidden',
      '#default_value' => $item['module'],
    );
  }

  $form['new_item']['property'] = array(
    '#type' => 'select',
    '#default_value' => !empty($_GET['property']) ? check_plain($_GET['property']) : '',
    '#options' => $properties,
  );
  $form['new_item']['wildcard'] = array(
    '#type' => 'textfield',
    '#default_value' => '',
    '#size' => 10,
    '#maxlength' => 255,
  );
  $form['new_item']['operator'] = array(
    '#type' => 'select',
    '#default_value' => '=',
    '#options' => $operators,
  );
  $form['new_item']['value'] = array(
    '#type' => 'textfield',
    '#default_value' => !empty($_GET['value']) ? html_entity_decode(filter_xss($_GET['value'])) : '',
    '#size' => 25,
    '#maxlength' => 255,
  );
  $form['new_item']['theme'] = array(
    '#type' => 'select',
    '#default_value' => 'default',
    '#options' => $options['themes'],
  );
  $form['new_item']['enabled'] = array(
    '#type' => 'checkbox',
    '#default_value' => TRUE,
  );

  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}


/**
 * Validation of
 * @see themekey_rule_chain_form()
 */
function themekey_rule_chain_form_validate(&$form, $form_state) {
  themekey_abstract_rule_chain_form_validate($form, $form_state, array(
    'check_enabled_callback' => 'themekey_check_theme_enabled',
    'not_enabled_message' => t('Theme is not enabled.'),
  ));
}

function themekey_abstract_rule_chain_form_validate(&$form, $form_state, $options) {
  module_load_include('inc', 'themekey', 'themekey_validators');

  $attributes = variable_get('themekey_attributes', array());

  $values = $form_state['values'];

  if (!empty($values['old_items'])) {
    foreach ($values['old_items'] as $key_1 => $value_1) {
      if ($value_1['enabled']) {
        if (!empty($options['check_enabled_callback']) && !$options['check_enabled_callback']($value_1['theme'])) {
          form_set_error('old_items][' . $key_1 . '][theme', check_plain($value_1['theme'] . ': ' . $options['not_enabled_message']));
        }

        if (empty($value_1['property'])) {
          form_set_error('old_items][' . $key_1 . '][property', check_plain(t('Property missing')));
        }
        else {
          if (0 == drupal_strlen($value_1['value'])) {
            form_set_error('old_items][' . $key_1 . '][value', check_plain(t('You must enter a value')));
          }
          elseif (!empty($attributes[$value_1['property']]['validator'])) {
            //validate rule with custom validator
            $validator = $attributes[$value_1['property']]['validator'];

            if (!function_exists($validator) && isset($attributes[$value_1['property']]['file'])) {
              themekey_load_function(
                $validator,
                $attributes[$value_1['property']]['file'],
                isset($attributes[$value_1['property']]['path']) ? $attributes[$value_1['property']]['path'] : '');
            }

            if (function_exists($validator)) {
              $rule = array(
                'property' => $value_1['property'],
                'wildcard' => $value_1['wildcard'],
                'operator' => $value_1['operator'],
                'value' => $value_1['value'],
              );
              $errors = $validator($rule);
              foreach ($errors as $element => $msg) {
                form_set_error('old_items][' . $key_1 . '][' . $element, filter_xss($msg, array('em')));
              }
            }
            else {
              form_set_error('old_items][' . $key_1 . '][property', filter_xss(t('ThemeKey requested an unknown validator called %validator to validate property %property', array('%validator' => $validator, '%property' => $value_1['property'])), array('em')));
            }
          }
          elseif ('~' == $value_1['operator'] || '!~' == $value_1['operator']) {
            $rule = array(
              'property' => $value_1['property'],
              'wildcard' => $value_1['wildcard'],
              'operator' => $value_1['operator'],
              'value' => $value_1['value'],
            );
            $errors = themekey_validator_regex($rule);
            foreach ($errors as $element => $msg) {
              form_set_error('old_items][' . $key_1 . '][' . $element, filter_xss($msg, array('em')));
            }
          }
        }

        foreach ($values['old_items'] as $key_2 => $value_2) {
          if ($key_2 == $key_1) {
            continue;
          }

          if ($value_2['enabled'] &&
            !empty($value_1['value']) &&
            $value_2['property'] == $value_1['property'] &&
            $value_2['operator'] == $value_1['operator'] &&
            $value_2['value'] == $value_1['value'] &&
            ($value_2['parent'] == $value_1['parent'] ||
            $value_2['parent'] == $value_1['id'])) {

            if ('drupal:path:wildcard' != $value_2['property'] ||
                ('drupal:path:wildcard' == $value_2['property'] && $value_2['wildcard'] == $value_1['wildcard'])) {
              // We have two identical rules with same 'indention' in a chain.
              // This is allowed only if first one has childs and second one has none and one isn't the parent of the other
              if (!$value_2['parent'] == $value_1['id']) {
                $has_childs_1 = FALSE;
                $has_childs_2 = FALSE;

                foreach ($values['old_items'] as $value_3) {
                  if ($value_3['parent'] == $value_1['id']) {
                    $has_childs_1 = TRUE;
                  }

                  if ($value_3['parent'] == $value_2['id']) {
                    $has_childs_2 = TRUE;
                  }

                  if ($has_childs_1 && $has_childs_2) {
                    break;
                  }
                }

                if ((($value_1['weight'] < $value_2['weight']) && $has_childs_1 && !$has_childs_2) ||
                    (($value_1['weight'] > $value_2['weight']) && !$has_childs_1 && $has_childs_2)) {
                  // no error
                  continue;
                }
                elseif (($value_1['weight'] > $value_2['weight']) && $has_childs_1 && !$has_childs_2) {
                  form_set_error('old_items][' . $key_1 . '][property', check_plain(t('Theme switching rule could never be reached')));
                  continue;
                }
                elseif (($value_1['weight'] < $value_2['weight']) && !$has_childs_1 && $has_childs_2) {
                  form_set_error('old_items][' . $key_1 . '][property', check_plain(t('Theme switching rule hides a later one')));
                  continue;
                }
                elseif (($value_1['weight'] < $value_2['weight']) && $has_childs_1 && $has_childs_2) {
                  form_set_error('old_items][' . $key_1 . '][property', check_plain(t('Theme switching rule should be combined with an identical one below')));
                  continue;
                }
                elseif (($value_1['weight'] > $value_2['weight']) && $has_childs_1 && $has_childs_2) {
                  form_set_error('old_items][' . $key_1 . '][property', check_plain(t('Theme switching rule should be combined with an identical one above')));
                  continue;
                }
              }

              form_set_error('old_items][' . $key_1 . '][property', check_plain(t('You entered two identical theme switching rules in the chain')));
              form_set_error('old_items][' . $key_2 . '][property', check_plain(t('You entered two identical theme switching rules in the chain')));
            }
          }
        }
      }
    }
  }

  if (!empty($values['new_item']['value'])) {
    if ($values['new_item']['enabled'] && !empty($options['check_enabled_callback']) && !$options['check_enabled_callback']($values['new_item']['theme'])) {
      form_set_error('new_item][theme', check_plain($options['not_enabled_message']));
    }

    if (empty($values['new_item']['property'])) {
      form_set_error('new_item][property', check_plain(t('Property missing')));
    }
    else {
      if (!empty($attributes[$values['new_item']['property']]['validator'])) {
        //validate rule with custom validator
        $validator = $attributes[$values['new_item']['property']]['validator'];

        if (!function_exists($validator) && isset($attributes[$values['new_item']['property']]['file'])) {
          themekey_load_function(
            $validator,
            $attributes[$values['new_item']['property']]['file'],
            isset($attributes[$values['new_item']['property']]['path']) ? $attributes[$values['new_item']['property']]['path'] : '');
        }

        if (function_exists($validator)) {
          $rule = array(
            'property' => $values['new_item']['property'],
            'wildcard' => $values['new_item']['wildcard'],
            'operator' => $values['new_item']['operator'],
            'value' => $values['new_item']['value'],
          );
          $errors = $validator($rule);
          foreach ($errors as $element => $msg) {
            form_set_error('new_item][' . $element, filter_xss($msg));
          }
        }
        else {
          form_set_error('new_item][property', filter_xss(t('ThemeKey requested an unknown validator called %validator to validate the property, %property', array('%validator' => $validator, '%property' => $values['new_item']['property']))), array('em'));
        }
      }
      elseif ('~' == $values['new_item']['operator'] || '!~' == $values['new_item']['operator']) {
        $rule = array(
                  'property' => $values['new_item']['property'],
                  'wildcard' => $values['new_item']['wildcard'],
                  'operator' => $values['new_item']['operator'],
                  'value' => $values['new_item']['value'],
        );
        $errors = themekey_validator_regex($rule);
        foreach ($errors as $element => $msg) {
          form_set_error('new_item][' . $element, filter_xss($msg, array('em')));
        }
      }
    }
  }
}


/**
 * Form submission handler for themekey_rule_chain_form().
 *
 * @see themekey_rule_chain_form()
 */
function themekey_rule_chain_form_submit($form, &$form_state) {
  themekey_abstract_rule_chain_form_submit($form, $form_state, array(
    'rule_set_callback' => 'themekey_rule_set',
  ));
}

function themekey_abstract_rule_chain_form_submit($form, &$form_state, $options) {
  $max_weight = 0;
  if (!empty($form_state['values']['old_items'])) {
    foreach ($form_state['values']['old_items'] as $id => $item) {
      if ($item['weight'] > $max_weight) {
        $max_weight = $item['weight'];
      }

      $item['id'] = $id;

      if ('drupal:path:wildcard' == $item['property']) {
        $item['property'] = $item['wildcard'];
      }

      unset($item['wildcard']);

      $options['rule_set_callback']($item);
    }
  }

  if (!empty($form_state['values']['new_item']['value']) || '0' === $form_state['values']['new_item']['value']) {
    $item = $form_state['values']['new_item'];

    $item['parent'] = 0;
    $item['weight'] = $max_weight + 1;

    if ('drupal:path:wildcard' == $item['property']) {
      $item['property'] = $item['wildcard'];
    }

    unset($item['wildcard']);

    $options['rule_set_callback']($item);
  }

  drupal_set_message(check_plain(t('The configuration options have been saved. Trying to clear page cache ...')));

  // fast deletion of page cache (truncate)
  cache_clear_all('*', 'cache_page', TRUE);
}


/**
 * Form builder for the ThemeKey settings form.
 *
 * @ingroup forms
 */
function themekey_settings_form($form, &$form_state) {
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('General Settings'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['settings']['themekey_path_case_sensitive'] = array(
    '#type' => 'checkbox',
    '#title' => t('Property drupal:path is case sensitive'),
    '#default_value' => variable_get('themekey_path_case_sensitive', 0),
    '#description' => t('Drupal paths are case insensitive by default. Modules like Global Redirect might change this behavior.'),
  );

  $form['settings']['themekey_allthemes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Provide all themes for selection'),
    '#default_value' => variable_get('themekey_allthemes', 0),
    '#description' => t('Make all installed themes available for selection, not enabled ones only.'),
  );

  $form['settings']['themekey_theme_maintain'] = array(
    '#type' => 'checkbox',
    '#title' => t('Retain the theme until a new theme is set'),
    '#default_value' => variable_get('themekey_theme_maintain', 0),
    '#description' => t('Select this option to have logged-in users stay in the same theme until they browse to a new page with an explicit theme set.'),
  );

  $form['settings']['themekey_theme_maintain_anonymous'] = array(
    '#type' => 'checkbox',
    '#title' => t('Retain the theme until a new theme is set for anonymous users'),
    '#default_value' => variable_get('themekey_theme_maintain_anonymous', 0),
    '#description' => t('Select this option to have anonymous users stay in the same theme until they browse to a new page with an explicit theme set.'),
  );

  if (module_exists('forum')) {
    $form['settings']['themekey_module_forum_triggers_taxonomy_vid'] = array(
      '#type' => 'checkbox',
      '#title' => t('Forum pages trigger property taxonomy:vid'),
      '#default_value' => variable_get('themekey_module_forum_triggers_taxonomy_vid', 0),
      '#description' => t('Property taxonomy:vid is set when a single node is shown (for example, /node/17). If this option is selected, forum pages like /forum/28 will set taxonomy:vid as well.'),
    );
  }

  $form['settings']['themekey_cron_page_cache'] = array(
    '#type' => 'checkbox',
    '#title' => t('Cron cleans up page cache'),
    '#default_value' => variable_get('themekey_cron_page_cache', 1),
    '#description' => t('Select this option if ThemeKey should check rules containing time-based properties when cron runs. ThemeKey will carefully clean up the page cache if necessary to provide the right theme to anonymous users automatically, for example, a Christmas theme.'),
  );

  return system_settings_form($form);
}


/**
 * Form builder for the ThemeKey ajax settings form.
 *
 * @ingroup forms
 */
function themekey_ajax_settings_form($form, &$form_state) {
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Ajax Settings'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['settings']['themekey_ajax_base_page_theme'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use current theme for Ajax responses.'),
    '#default_value' => variable_get('themekey_ajax_base_page_theme', 1),
    '#description' => t('Many different pages can invoke an Ajax request to system/ajax or another generic Ajax path. It is almost always desired for an Ajax response to be rendered using the same theme as the base page, because most themes are built with the assumption that they control the entire page, so if the CSS for two themes are both loaded for a given page, they may conflict with each other. Drupal provides a generic functionality to handle this issue. Unfortunately some modules do not use it the right way. Therefor ThemeKey provides a generic workaround which solves the issue for some modules.'),
  );

  $form['settings']['themekey_unsafe_ajax_base_page_theme'] = array(
    '#type' => 'checkbox',
    '#title' => t('Bypass a request forgery protection in theme selection for Ajax responses.'),
    '#default_value' => variable_get('themekey_unsafe_ajax_base_page_theme', 0),
    '#description' => t('The option "%option" is only working for non-cached pages due to a request forgery protection in core that prevents that a user can force a different theme by injecting a different theme name in the Ajax request. By disabling this protection you can get more use-cases to work. To disable the protection is risky if you installed a theme that provides additional features or bypasses access rights on the theme level. Or if you configured a theme to expose non-public data, for example as a block. To reduce that risk you should provide a list of "Safe Themes" below.', array('%option' => t('Use current theme for Ajax responses.'))),
  );

  $form['settings']['themekey_consider_default_theme_safe'] = array(
    '#type' => 'checkbox',
    '#title' => t('Always consider the default theme to be safe.'),
    '#default_value' => variable_get('themekey_consider_default_theme_safe', 1),
    '#description' => t('Always consider the default theme to be safe independent from the list of "Safe Themes" below.'),
  );

  if (module_exists('themekey_ui')) {
    module_load_include('inc', 'themekey_ui', 'themekey_ui_admin');
    themekey_ui_theme_build_select_form(
      $form,
      t('Safe Themes'),
      t('Select all themes that are safe to be used by Ajax calls triggered by anonymous users.'),
      variable_get('themekey_ajax_themes', array()),
      NULL,
      TRUE,
      'themekey_ajax_themes',
      list_themes(),
      FALSE,
      TRUE
    );
  }
  else {
    drupal_set_message(t('Enable the "ThemeKey UI" module to get a graphical selector for "Safe Themes"'), 'warning', FALSE);

    $options = array();
    $themes = list_themes();
    foreach ($themes as $machine_name => $theme) {
      if ($theme->status) {
        $options[$machine_name] = $theme->info['name'];
      }
    }

    $form['settings']['themekey_ajax_themes'] = array(
      '#type' => 'checkboxes',
      '#options' => $options,
      '#title' => t('Safe Themes'),
      '#default_value' => variable_get('themekey_ajax_themes', array()),
      '#description' => t('Select all themes that are safe to be used by Ajax calls triggered by anonymous users.'),
    );
  }

  $form['#submit'][] = 'themekey_ajax_settings_form_submit';

  return system_settings_form($form);
}

function themekey_ajax_settings_form_submit($form, &$form_state) {
  $form_state['values']['themekey_ajax_themes'] = array_values(array_filter($form_state['values']['themekey_ajax_themes'], 'is_string'));
  $old_themes = variable_get('themekey_ajax_themes', array());
  if (
    array_diff($old_themes, $form_state['values']['themekey_ajax_themes']) ||
    array_diff($form_state['values']['themekey_ajax_themes'], $old_themes)
  ) {
    // fast deletion of menu cache (truncate)
    cache_clear_all('*', 'cache_menu', TRUE);
  }
}

/**
 * Themes themekey_rule_chain_form() and adds drag'n'drop features.
 *
 * @ingroup themeable
 */
function theme_themekey_rule_chain_form($variables) {
  return theme_themekey_abstract_rule_chain_form($variables, array(
    'header' => array(
      t('Theme Switching Rule Chain'),
      t('Theme'),
      t('Enabled'),
      t('Operation'),
      t('Parent'),
      t('Weight'),
      t('Page<br />Cache'),
    )
  ));
}

function theme_themekey_abstract_rule_chain_form($variables, $options) {
  $form = $variables['form'];
  themekey_admin_theme_warning();

  $output = '';

  $rows = array();
  $num_childs = array();

  if (!empty($form['old_items'])) {
    $parents_disabled = array();
    $attributes = variable_get('themekey_attributes', array());

    foreach ($form['old_items'] as $key => $item) {
      if (is_numeric($key) && !empty($item['property'])) {
        themekey_deprected_property_warning($item['property']['#value']);

        $parents_disabled[$key] = FALSE;

        if (!empty($parents_disabled[$item['parent']['#value']])) {
          $form['old_items'][$key]['enabled']['#value'] = 0;
        }

        if (!$form['old_items'][$key]['enabled']['#value']) {
          $parents_disabled[$key] = TRUE;
        }
        elseif (!empty($item['parent']['#value'])) {
          $num_childs[$item['parent']['#value']] = empty($num_childs[$item['parent']['#value']]) ? 1 : $num_childs[$item['parent']['#value']] + 1;
        }
      }
    }

    foreach ($form['old_items'] as $key => $item) {
      if (is_numeric($key) && !empty($item['property'])) {
        $row = (isset($form['old_items'][$key]['#attributes']) && is_array($form['old_items'][$key]['#attributes'])) ? $form['old_items'][$key]['#attributes'] : array();

        // Add special classes to be used for tabledrag.js.
        $form['old_items'][$key]['id']['#attributes']['class'] = array('themekey-property-id');
        $form['old_items'][$key]['parent']['#attributes']['class'] = array('themekey-property-parent');
        $form['old_items'][$key]['weight']['#attributes']['class'] = array('themekey-property-weight');
        // Add special classes to be used for themekey-properties.js.
        $form['old_items'][$key]['property']['#attributes']['class'] = array('themekey-property-property themekey-fadeable');
        $form['old_items'][$key]['wildcard']['#attributes']['class'] = array('themekey-property-wildcard themekey-fadeable');
        $form['old_items'][$key]['operator']['#attributes']['class'] = array('themekey-fadeable');
        $form['old_items'][$key]['value']['#attributes']['class'] = array('themekey-fadeable');
        $form['old_items'][$key]['enabled']['#attributes']['class'] = array('themekey-property-enabled');
        $form['old_items'][$key]['theme']['#attributes']['class'] = array('themekey-property-theme themekey-fadeable');

        if (isset($form['old_items'][$key]['append_path'])) {
          // Special element of ThemeKey Redirect. See themekey_redirect_rule_chain_form().
          $form['old_items'][$key]['append_path']['#attributes']['class'] = array('themekey-property-append-path themekey-fadeable');
        }

        // form items of type markup don't have attributes
        $form['old_items'][$key]['delete']['#markup'] = str_replace('<a', '<a class="themekey-rule-delete-link"', $form['old_items'][$key]['delete']['#markup']);

        if ('drupal:path:wildcard' != $item['property']['#value']) {
          $form['old_items'][$key]['wildcard']['#attributes']['style'] = 'display: none';
        }

        if (!empty($num_childs[$key])) {
          $form['old_items'][$key]['theme']['#attributes']['style'] = 'display: none';
          if (isset($form['old_items'][$key]['append_path'])) {
            $form['old_items'][$key]['append_path']['#attributes']['style'] = 'display: none';
          }
          // form items of type markup don't have attributes
          $form['old_items'][$key]['delete']['#markup'] = str_replace('<a', '<a style="display: none"', $form['old_items'][$key]['delete']['#markup']);
        }

        if (!empty($parents_disabled[$item['parent']['#value']])) {
          $form['old_items'][$key]['enabled']['#attributes']['style'] = 'display: none';
          $form['old_items'][$key]['enabled']['#default_value'] = 0;
        }

        $elements = array();

        $description = htmlentities(strip_tags($attributes[$form['old_items'][$key]['property']['#default_value']]['description']));
        $description = str_replace('\'', '', $description);

        $elements[] = array(
          'data' => theme('indentation', array('size' => $form['old_items'][$key]['depth']['#value'])) .
            drupal_render($form['old_items'][$key]['id']) .
            drupal_render($form['old_items'][$key]['property']) .
            drupal_render($form['old_items'][$key]['wildcard']) .
            drupal_render($form['old_items'][$key]['operator']) .
            drupal_render($form['old_items'][$key]['value']) .
            '<a name="anchor-' . $key . '" href="#anchor-' . $key . '" id="' . drupal_clean_css_identifier('edit-old-items-' . $key . '-value-help') . '" class="themekey-fadeable" title="' . $description . '" onClick="alert(\'' . $description . '\')">?</a>',
          'class' => array('themekey-properties-row'),
        );

        $elements[] = array(
          'data' => drupal_render($form['old_items'][$key]['theme']) .
            // Special element of ThemeKey Redirect. See themekey_redirect_rule_chain_form().
            (isset($form['old_items'][$key]['append_path']) ? drupal_render($form['old_items'][$key]['append_path']) : ''),
        );

        $elements[] = array(
          'data' => drupal_render($form['old_items'][$key]['enabled']),
        );

        $elements[] = array(
          'data' => drupal_render($form['old_items'][$key]['delete']),
        );

        $elements[] = array(
          'data' => drupal_render($form['old_items'][$key]['parent']),
        );

        $elements[] = array(
          'data' => drupal_render($form['old_items'][$key]['weight']),
        );

        $page_cache = $attributes[$form['old_items'][$key]['property']['#default_value']]['page cache'];
        drupal_alter('themekey_page_cache_support', $page_cache, $key, $form['#form_id']);
        if ($form['old_items'][$key]['enabled']['#value']) {
          themekey_page_cache_warning($page_cache);
        }

        $elements[] = array(
          'data' => '<div id="' . drupal_clean_css_identifier('edit-old-items-' . $key . '-page-cache-icon') . '">' .
          theme('themekey_page_cache_icon', array('page_cache_support' => $page_cache)) .
          '</div>',
        );

        $row['class'][] = 'draggable';
        if (!$form['old_items'][$key]['enabled']['#value']) {
          $row['class'][] = 'themekey-fade-out';
        }
        if (!$form['old_items'][$key]['parent']['#value']) {
          $row['class'][] = 'themekey-top-level';
        }
        $row['id'] = 'themekey-properties-row-' . $key;
        $row['data'] = $elements;
        $rows[] = $row;
      }
    }
  }

  if (!empty($rows)) {
    if (empty($form['pager']['#value'])) {
      drupal_add_tabledrag('themekey-properties', 'match', 'parent', 'themekey-property-parent', 'themekey-property-parent', 'themekey-property-id', TRUE);
      drupal_add_tabledrag('themekey-properties', 'order', 'sibling', 'themekey-property-weight');
    }

    $output .= theme('table', array('header' => $options['header'], 'rows' => $rows, 'attributes' => array('id' => 'themekey-properties')));

    foreach ($num_childs as $parent => $num) {
      $output .= '<input id="themekey-num-childs-' . $parent . '" type="hidden" value="' . $num . '"></input>';
    }
  }

  $rows = array();

  if (!empty($form['new_item'])) {
    if (isset($form['new_item']['property'])) {
      $row = (isset($form['new_item']['#attributes']) && is_array($form['new_item']['#attributes'])) ? $form['new_item']['#attributes'] : array();

      // Add special classes to be used for themekey-properties.js.
      $form['new_item']['property']['#attributes']['class'] = array('themekey-property-property');
      $form['new_item']['wildcard']['#attributes']['class'] = array('themekey-property-wildcard');
      if ('drupal:path:wildcard' != $form['new_item']['property']['#value']) {
        $form['new_item']['wildcard']['#attributes']['style'] = 'display: none';
      }

      $elements = array();
      $elements[] = t('New Rule:');
      $elements[] = array(
        'data' => drupal_render($form['new_item']['property']) .
          drupal_render($form['new_item']['wildcard']) .
          drupal_render($form['new_item']['operator']) .
          drupal_render($form['new_item']['value']),
        'class' => array('themekey-properties-row'),
      );
      $elements[] = array(
        'data' => drupal_render($form['new_item']['theme']) .
          // Special element of ThemeKey Redirect. See themekey_redirect_rule_chain_form().
          (isset($form['new_item']['append_path']) ? drupal_render($form['new_item']['append_path']) : ''),
      );
      $elements[] = array('data' => drupal_render($form['new_item']['enabled']));

      $row['data'] = $elements;
      $rows[] = $row;
    }
  }

  if (!empty($rows)) {
    $header = array(
      '',
      $options['header'][0],
      $options['header'][1],
      $options['header'][2],
    );

    $output .= '<a name="themekey_new_rule"></a>';
    $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'themekey-new-item')));
  }

  $output .= drupal_render_children($form);

  drupal_add_css(drupal_get_path('module', 'themekey') . '/themekey_rule_chain.admin.css');
  drupal_add_js(drupal_get_path('module', 'themekey') . '/themekey_rule_chain.admin.js');

  return $output;
}


/**
 * Detects if there's an active administration theme and displays a warning.
 */
function themekey_admin_theme_warning() {
  if (!in_array('system', variable_get('themekey_compat_modules_enabled', array())) && variable_get('admin_theme', '0')) {
    drupal_set_message(filter_xss(t('%admin_theme is configured as administration theme at !link. This setting is more powerful than a corresponding ThemeKey rule.',
      array('%admin_theme' => variable_get('admin_theme', '0'), '!link' => l(t('!path', array('!path' => 'admin/appearance')), 'admin/appearance')))), 'warning');
    if (variable_get('node_admin_theme', '0')) {
      drupal_set_message(filter_xss(t('As configured at !link, adding or editing a node will use the administration theme, %admin_theme.',
        array('%admin_theme' => variable_get('admin_theme', '0'), '!link' => l(t('!path', array('!path' => 'admin/appearance')), 'admin/appearance')))), 'warning');
    }
  }
}

/**
 * Detects if deprecated properties are in use.
 */
function themekey_deprected_property_warning($property) {
  static $warnings = array();

  if (!isset($warnings[$property])) {
    $attributes = variable_get('themekey_attributes', array());
    if (!empty($attributes[$property]['deprecated'])) {
      drupal_set_message(!empty($attributes[$property]['deprecated message']) ? filter_xss($attributes[$property]['deprecated message']) : t('Property %property is deprecated!', array('%property' => $property)), 'warning');
    }
    $warnings[$property] = TRUE;
  }
}

/**
 * Detects if page cache is active and incompatible properties are used
 * in theme switching rule chain.
 */
function themekey_page_cache_warning($page_cache_support) {
  static $warnings = array();

  if (variable_get('cache', 0)) {
    switch ($page_cache_support) {
      case THEMEKEY_PAGECACHE_UNSUPPORTED:
        if (!isset($warnings[THEMEKEY_PAGECACHE_UNSUPPORTED])) {
          drupal_set_message(filter_xss(t('!page_cache_icon Your site uses !page_caching, but the Theme Switching Rule Chain contains properties that do not support page caching. You have to ensure that any rule using those properties are wrapped by a different rule that excludes anonymous users like "user:uid > 0".',
            array('!page_caching' => l(t('page caching'), 'admin/config/development/performance'), '!page_cache_icon' => theme('themekey_page_cache_icon', array('page_cache_support' => $page_cache_support)))), array('a', 'img')), 'warning');
          $warnings[THEMEKEY_PAGECACHE_UNSUPPORTED] = TRUE;
        }
        break;

      case THEMEKEY_PAGECACHE_TIMEBASED:
        if (!isset($warnings[THEMEKEY_PAGECACHE_TIMEBASED])) {
          if (variable_get('themekey_cron_page_cache', 1)) {
            drupal_set_message(filter_xss(t('!page_cache_icon Your site uses !page_caching and the Theme Switching Rule Chain contains properties that require your cron to run frequently enough. During the cron run ThemeKey deletes the page cache if necessary depending on your Theme Switching Rules.',
              array('!page_caching' => l(t('page caching'), 'admin/config/development/performance'), '!page_cache_icon' => theme('themekey_page_cache_icon', array('page_cache_support' => $page_cache_support)))), array('a', 'img')), 'warning');
          }
          else {
            drupal_set_message(filter_xss(t('!page_cache_icon Your site uses !page_caching and the Theme Switching Rule Chain contains properties that require "!cron_page_cache" to be enabled, but it is disabled.',
              array('!page_caching' => l(t('page caching'), 'admin/config/development/performance'), '!cron_page_cache' => l(t('Cron cleans up page cache'), 'admin/config/user-interface/themekey/settings'), '!page_cache_icon' => theme('themekey_page_cache_icon', array('page_cache_support' => $page_cache_support)))), array('a', 'img')), 'error');
          }
          $warnings[THEMEKEY_PAGECACHE_TIMEBASED] = TRUE;
        }
        break;
    }
  }
}


/**
 * Menu callback -- ask for confirmation of ThemeKey rule deletion
 */
function themekey_admin_delete_rule_confirm($form, &$form_state, $arg, $themekey_property_id) {
  $form['themekey_property_id'] = array(
    '#type' => 'value',
    '#value' => $themekey_property_id,
  );

  $title = themekey_format_rule_as_string($themekey_property_id);

  return confirm_form($form,
    t('Are you sure you want to delete the ThemeKey rule, %title?', array('%title' => $title)),
    'admin/config/user-interface/themekey/rules',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}


/**
 * Execute ThemeKey rule deletion
 */
function themekey_admin_delete_rule_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    themekey_rule_del($form_state['values']['themekey_property_id']);
  }

  $form_state['redirect'] = 'admin/config/user-interface/themekey/rules';
}


/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function theme_themekey_page_cache_icon($variables) {
  $page_cache_support = $variables['page_cache_support'];
  static $module_path = '', $page_cache_support_desriptions = array();

  if (empty($module_path)) {
    $module_path = drupal_get_path('module', 'themekey');
    $page_cache_support_desriptions = themekey_get_page_cache_support_desriptions();
  }

  return '<img src="/' . $module_path . '/img/page_cache_' . $page_cache_support . '.png" width="16" height="16" title="' . htmlentities(strip_tags($page_cache_support_desriptions[$page_cache_support]), ENT_COMPAT, 'UTF-8') . '"></img>';
}


/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function themekey_get_page_cache_support_desriptions() {
  return array(
    THEMEKEY_PAGECACHE_UNSUPPORTED => t('Unsupported! If you enable page caching on your system, you have to ensure that any rule using this property is wrapped by another rule that excludes anonymous users, such as "user:uid > 0".'),
    THEMEKEY_PAGECACHE_SUPPORTED => t('Supported'),
    THEMEKEY_PAGECACHE_TIMEBASED => t('Supported if you enable "Cron cleans up page cache" at !link and run your cron frequently enough. During the cron run ThemeKey deletes the page cache if necessary depending on your Theme Switching Rules.', array('!link' => l(t('!path', array('!path' => 'admin/config/user-interface/themekey/settings')), 'admin/config/user-interface/themekey/settings'))),
  );
}
