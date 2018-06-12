<?php

/**
 * @file
 * The functions in this file are the back end of ThemeKey.
 *
 * @author Markus Kalkbrenner | bio.logis GmbH
 *   @see http://drupal.org/user/124705
 *
 * @author profix898
 *   @see http://drupal.org/user/35192
 */


/**
 * Invokes a hook on all modules stored in the global
 * variable 'themekey_modules'
 *
 * @param $hook
 *   name of the hook as string
 *
 * @return
 *   mixed output of all hooks
 */
function themekey_invoke_modules($hook) {
  $modules = & drupal_static('themekey_modules', array());

  $return = array();

  if (empty($modules)) {
    foreach (variable_get('themekey_modules', array('node')) as $module) {
      if (module_exists($module) && is_readable(drupal_get_path('module', 'themekey') . '/modules/themekey.' . $module . '.inc')) {
        require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'themekey') . '/modules/themekey.' . $module . '.inc';
        $modules[] = $module;
      }
      else {
        // seems like a module has been deactivated => update variable 'themekey_modules'
        module_load_include('inc', 'themekey', 'themekey_build');
        themekey_scan_modules();
      }
    }
  }

  $args = func_get_args();
  // Remove $hook from the arguments.
  unset($args[0]);

  foreach ($modules as $module) {
    $function = 'themekey_' . $module . '_' . $hook;
    if (function_exists($function)) {
      $result = call_user_func_array($function, $args);
      if (isset($result) && is_array($result)) {
        $return = array_merge_recursive($return, $result);
      }
      elseif (isset($result)) {
        $return[] = $result;
      }
    }
  }

  return $return;
}

/**
 * Detects if a ThemeKey rule for property drupal:path
 * matches to the current page request.
 *
 * @param $condition
 *   ThemeKey rule as object:
 *   - property (must be "drupal:path")
 *   - operator
 *   - value
 *
 * @param $parameters
 *   reference to an array containing all
 *   ThemeKey properties and their values
 *
 * @return
 *   boolean
 */
function themekey_match_path($condition, &$parameters) {
  global $language;

  // don't repeat alias detection for all rules during one page request
  static $alias_uri = '';
  static $language_prefix = NULL;

  if ('drupal:path' != $condition->property) {
    return FALSE;
  }

  $get_q = themekey_get_q();

  $condition_parts = explode('/', $condition->value);
  $get_q_parts = explode('/', $get_q);

  $wildcards = themekey_match_path_parts($get_q_parts, $condition_parts);
  if (FALSE === $wildcards && module_exists('path')) {
    if (empty($alias_uri)) {
      // Derive path from request_uri.
      // drupal_parse_url() is not suitable because it lacks language prefix support.
      $offset = (variable_get('clean_url', 0) ? 0 : 3) + drupal_strlen(base_path());
      $alias_uri = drupal_substr(request_uri(), $offset);
      if (strpos($alias_uri, '?') !== FALSE) {
        // Remove query string from request uri
        $alias_uri_parts = explode('?', $alias_uri);
        $alias_uri = $alias_uri_parts[0];
      }

      if (NULL === $language_prefix) {
        if (drupal_multilingual() && LOCALE_LANGUAGE_NEGOTIATION_URL_PREFIX ==
          variable_get('locale_language_negotiation_url_part', LOCALE_LANGUAGE_NEGOTIATION_URL_PREFIX)
          && (array_key_exists('locale-url', variable_get('language_negotiation_language', array())) ||
              array_key_exists('locale-url', variable_get('language_negotiation_language_content', array())))
        ) {
          $languages = language_list('enabled');
          list($language_object, $alias_uri) = language_url_split_prefix($alias_uri, $languages[1]);
          if ($language_object) {
            $language_prefix = $language_object->prefix;
          }
          else {
            $language_prefix = FALSE;
          }
        }
        else {
          // prevent multiple checks for prefixes
          $language_prefix = FALSE;
        }
      }

      // For $alias_uri != $_GET['q'] the page was requested using an
      // aliased path, otherwise get the path alias internally
      if ($alias_uri == $get_q) {
        $lang_code = NULL;
        if (!empty($language->language) && LANGUAGE_NONE != $language->language) {
          $lang_code = $language->language;
        }

        $alias_uri = drupal_get_path_alias($get_q, $lang_code);
      }
    }

    if ($alias_uri != $get_q) {
      $wildcards = themekey_match_path_parts(explode('/', $alias_uri), $condition_parts);
      if (FALSE === $wildcards && $language_prefix) {
        // retry, because the rule might contain the path alias including the language prefix
        $wildcards = themekey_match_path_parts(explode('/', $language_prefix . '/' . $alias_uri), $condition_parts);
      }
    }
  }

  if (is_array($wildcards)) {
    $parameters['internal:temp_wildcards'] = $wildcards;
    return TRUE;
  }

  $parameters['internal:temp_wildcards'] = array();
  return FALSE;
}


/**
 * Compares if two paths are identical accepting
 * wildcards "%" and "#".
 *
 * @param $path_parts
 *   array containing single parts of a path
 *
 * @param $condition_parts
 *   array containing single parts of a path
 *   whereas a part could be a wildcard
 *
 * @return
 *   FALSE if paths doesn't match or array containing
 *   the wildcards if paths matched
 */
function themekey_match_path_parts($path_parts, $condition_parts) {
  if (count($path_parts) < count($condition_parts)) {
    return FALSE;
  }

  $wildcards = array();

  foreach ($condition_parts as $key => $part) {
    if ('#' == $part) {
      if (ctype_digit($path_parts[$key])) {
        $wildcards[$key] = $path_parts[$key];
        continue;
      }
      return FALSE;
    }

    if ('%' == $part) {
      if (isset($path_parts[$key])) {
        $wildcards[$key] = $path_parts[$key];
        continue;
      }
      return FALSE;
    }

    if (!variable_get('themekey_path_case_sensitive', 0)) {
      $part = drupal_strtolower($part);
      $path_parts[$key] = drupal_strtolower($path_parts[$key]);
    }

    if ($part == $path_parts[$key] || $part == urldecode($path_parts[$key]) || $part == rawurldecode($path_parts[$key])) {
      continue;
    }

    return FALSE;
  }

  return $wildcards;
}



/**
 * Assigns global parameters' values to ThemeKey properties.
 * Therefore it calls hook_themekey_global()
 *
 * @return
 *   associative array containing some
 *   ThemeKey properties and their values
 */
function themekey_get_global_parameters() {
  static $global_parameters = NULL;

  if (is_null($global_parameters)) {
    $global_parameters = array_merge_recursive(themekey_invoke_modules('themekey_global'), module_invoke_all('themekey_global'));

    $path_condition = new stdClass();
    $path_condition->property = 'drupal:path';
    $paths = variable_get('themekey_paths', array());
    foreach ($paths as $item) {
      $path_condition->value = $item['path'];
      $parameters = array();

      if (themekey_match_path($path_condition, $parameters)) {
        foreach ($parameters['internal:temp_wildcards'] as $index => $item_wildcard) {
          $global_parameters[$item['wildcards'][$index]] = $item_wildcard;
        }

        if (count($item['callbacks'])) {
          foreach ($item['callbacks'] as $callback) {
            $callback($item, $global_parameters);
          }
        }
      }
    }
  }

  return $global_parameters;
}

/**
 * This function steps through
 * the rule chain and returns a theme.
 *
 * @return
 *   array containing the name of the selected theme and the cascade of rules matched
 *   or NULL
 */
function themekey_match_rules() {
  $parameters = themekey_get_global_parameters();

  $result = themekey_match_rule_childs($parameters, array(
    'table' => 'themekey_properties',
    'format_rule_as_string_callback' => 'themekey_format_rule_as_string',
    'check_enabled_callback' => 'themekey_check_theme_enabled',
  ));
  if (!is_array($result)) {
    $result = NULL;
  }
  elseif ('ThemeKeyAdminTheme' === $result['theme']) {
    $result['theme'] = variable_get('admin_theme', '0');
  }
  return $result;
}

/**
 * Helper function of
 * @see themekey_match_rules()
 *
 * @param $parameters
 *   reference to an array containing all
 *   ThemeKey properties and their values
 *
 * @param $parent
 *   id of parent rule
 *
 * @param $rules
 *   array of matched rules
 *
 * @return
 *   NULL in case of an error
 *   array containing the name of the theme if child rule matched and the cascade of parent rules matched
 *   FALSE if no child rule matches
 *   TRUE if no child properties in the chain
 */
function themekey_match_rule_childs(&$parameters, $options, $parent = 0) {
  static $child_lookups = array();

  if (!$parent) {
    // reset
    $child_lookups = array();
  }

  if (isset($child_lookups[$parent])) {
    // prevent endless recursion in case of mal-formatted data in database
    return $child_lookups[$parent];
  }

  if ($result = db_select($options['table'], 'tp')
    ->fields('tp')
    ->condition('enabled', 1)
    ->condition('parent', $parent)
    ->condition('value', '', '<>')
    ->orderBy('weight', 'asc')
    ->execute()
  ) {

    $num_childs = 0;

    foreach ($result as $item) {
      $num_childs++;
      if (themekey_match_condition($item, $parameters)) {
        if ('drupal:path' == $item->property && !empty($parameters['internal:temp_wildcards'])) {
          $wildcards = unserialize($item->wildcards);
          if (!empty($wildcards)) {
            foreach ($wildcards as $index => $wildcard) {
              $parameters[$wildcard] = $parameters['internal:temp_wildcards'][$index];
            }
          }
        }

        if (variable_get('themekey_debug_trace_rule_switching', FALSE)) {
          themekey_set_debug_message('Match: %rule', array('%rule' => $options['format_rule_as_string_callback']($item->id)));
        }

        $child_lookups[$parent] = themekey_match_rule_childs($parameters, $options, $item->id);

        if (FALSE === $child_lookups[$parent]) {
          continue;
        }
        elseif (TRUE === $child_lookups[$parent]) {
          if (isset($options['check_enabled_callback']) && !$options['check_enabled_callback']($item->theme)) {
            if (!empty($options['stop_on_check_enabled_false'])) {
              if (variable_get('themekey_debug_trace_rule_switching', FALSE)) {
                themekey_set_debug_message('Stop on same target: %theme', array('%theme' => $item->theme));
              }
              return FALSE;
            }

            if (variable_get('themekey_debug_trace_rule_switching', FALSE)) {
              themekey_set_debug_message('Target disabled or not found: %theme', array('%theme' => $item->theme));
            }
            continue;
          }

          $rules[] = $item;
          $child_lookups[$parent] = array(
            'theme' => $item->theme,
            'rules_matched' => $rules,
          );
        }

        // return own theme or theme from child property or NULL in case of a database error
        return $child_lookups[$parent];
      }
      elseif (variable_get('themekey_debug_trace_rule_switching', FALSE)) {
        themekey_set_debug_message('No match: %rule', array('%rule' => $options['format_rule_as_string_callback']($item->id)));
      }
    }

    $child_lookups[$parent] = (!$num_childs);
    return $child_lookups[$parent];
  }

  $child_lookups[$parent] = NULL;
  return $child_lookups[$parent];
}


/**
 * Detects if a ThemeKey rule matches to the current
 * page request.
 *
 * @param $condition
 *   ThemeKey rule as object:
 *   - property
 *   - operator
 *   - value
 *
 * @param $parameters
 *   reference to an array containing all
 *   ThemeKey properties an their values
 *
 * @return
 *   boolean
 */
function themekey_match_condition($condition, &$parameters) {
  $custom_theme = &drupal_static('themekey_custom_theme', '');

  if (is_object($condition)) {
    // Default operator is 'equal'
    if (empty($condition->operator)) {
      $condition->operator = '=';
    }

    if ('drupal:path' == $condition->property) {
      $match_path = themekey_match_path($condition, $parameters);
      if ($condition->operator == '=') {
        return $match_path;
      }
      // only '=' and '!' are allowed
      // @see themekey_validator_drupal_path()
      return !$match_path;
    }

    $value = themekey_property_value($parameters, $condition->property);

    if ('static' === $value && $custom_theme) {
      if (variable_get('themekey_debug_trace_rule_switching', FALSE)) {
        themekey_set_debug_message('A static rule set custom theme %custom_theme', array('%custom_theme' => $custom_theme));
      }
      return TRUE;
    }

    if (!is_array($value)) {
      $value = array($value);
    }

    if (!empty($value)) {
      foreach ($value as $single_value) {
        if (!is_null($single_value)) {
          // Supported operators for condition check:
          // smaller ('<'), greater ('>'), equal ('='), not equal ('!'), regex match ('~')
          if ($condition->operator == '<' && $single_value >= $condition->value) {
            return FALSE; // all values need to not match
          }
          elseif ($condition->operator == '>' && $single_value <= $condition->value) {
            return FALSE; // all values need to not match
          }
          elseif ($condition->operator == '<=' && $single_value > $condition->value) {
            return FALSE; // all values need to not match
          }
          elseif ($condition->operator == '>=' && $single_value < $condition->value) {
            return FALSE; // all values need to not match
          }
          elseif ($condition->operator == '=' && $single_value == $condition->value) {
            return TRUE;
          }
          elseif ($condition->operator == '!' && $single_value == $condition->value) {
            return FALSE; // all values need to not match
          }
          elseif ($condition->operator == '*' && strpos($single_value, $condition->value) !== FALSE) {
            return TRUE;
          }
          elseif ($condition->operator == '!*' && strpos($single_value, $condition->value) !== FALSE) {
            return FALSE; // all values need to not match
          }
          elseif ($condition->operator == '~' && preg_match($condition->value, $single_value)) {
            return TRUE;
          }
          elseif ($condition->operator == '!~' && preg_match($condition->value, $single_value)) {
            return FALSE; // all values need to not match
          }
        }
        else {
          // value is NULL
          return FALSE;
        }
      }

      if ($condition->operator == '=' || $condition->operator == '~' || $condition->operator == '*' ) {
        // no value matched
        return FALSE;
      }
      else {
        // condition matched for all values
        return TRUE;
      }
    }
    else {
      // value array is empty => value is NULL
      return FALSE;
    }
  }
  else {
    trigger_error(t('Function themekey_match_condition() called with illegal parameters'), E_USER_ERROR);
  }

  return FALSE;
}


/**
 * Detects if a ThemeKey property's value for the current
 * page request.
 *
 * @param $parameters
 *   reference to an array containing all
 *   ThemeKey properties and their values
 *
 * @param $property
 *   the name of the property as string
 *
 * @return
 *   The value of the property:
 *   - string if it's a single value
 *   - array of strings if there're multiple values
 *   - NULL if no value
 */
function themekey_property_value(&$parameters, $property) {

  // TODO Warning if property is not part of variable_get('themekey_attributes')

  // Property value is available directly
  if (isset($parameters[$property])) {
    return $parameters[$property];
  }

  $parameters[$property] = NULL;

  $src_candidates = array();
  $maps = variable_get('themekey_maps', array());

  foreach ($maps as $pos => $map) {
    if ($map['dst'] == $property) {
      if (!empty($parameters[$map['src']])) {
        $map_func = $map['callback'];

        if (!function_exists($map_func) && isset($map['file'])) {
          themekey_load_function(
            $map_func,
            $map['file'],
            isset($map['path']) ? $map['path'] : '');
        }

        $arguments = isset($map['args']) ? $map['args'] : array();

        if (function_exists($map_func)) {
          $parameters[$property] = $map_func($parameters[$map['src']], $arguments);
        }
        else {
          themekey_set_debug_message('Map function %map_function does not exists', array('%map_function' => $map_func));
          watchdog('php', 'ThemeKey map function %map_function does not exists', array('%map_function' => $map_func), WATCHDOG_ERROR);
        }
        break;
      }
      $src_candidates[$pos] = $map['src'];
    }
  }

  if (is_null($parameters[$property]) && !empty($src_candidates)) {
    foreach ($src_candidates as $pos => $src) {
      $return = themekey_property_value($parameters, $src);
      if ($return) {
        $map_func = $maps[$pos]['callback'];
        $parameters[$property] = $map_func($return, $parameters);
        break;
      }
    }
  }

  return $parameters[$property];
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function themekey_format_rule_as_string($themekey_property_id) {
  module_load_include('inc', 'themekey', 'themekey_build');
  return themekey_abstract_format_rule_as_string($themekey_property_id, array(
    'rule' => themekey_rule_get($themekey_property_id),
  ));
}

function themekey_abstract_format_rule_as_string($themekey_property_id, $options) {
  // fallback title
  $title = $themekey_property_id;

  $item = $options['rule'];
  if (!empty($item)) {
    $properties = variable_get('themekey_properties', array());
    if (!in_array($item->property, $properties)) {
      $attributes = variable_get('themekey_attributes', array());
      if (!array_key_exists($item->property, $attributes)) {
        $item->wildcard = $item->property;
        $item->property = 'drupal:path:wildcard';
      }
      elseif (!empty($attributes[$item->property]['static'])) {
        $item->theme = 'triggered';
      }
    }

    $title = '"' . $item->property . ' ';
    if (!empty($item->wildcard)) {
      $title .= $item->wildcard . ' ';
    }
    $title .= $item->operator . ' ' . $item->value . ' >>> ' . $item->theme . '"';
  }

  return $title;
}

/**
 * Magic loading of validation and callback functions.
 * @see _theme_process_registry()
 *
 * @return
 *   TRUE if the function has been loaded, otherwise FALSE
 */
function themekey_load_function($function, $file, $path = '') {
  if (!empty($file)) {
    if (empty($path)) {
      $filename = './' . $file;
      if (file_exists($filename)) {
        require_once $filename;
        if (function_exists($function)) {
          return TRUE;
        }
      }
      foreach (module_implements('themekey_properties') as $module) {
        if (themekey_load_function($function, $file, drupal_get_path('module', $module))) {
          if (function_exists($function)) {
            return TRUE;
          }
        }
      }
    }
    else {
      $filename = './' . $path . '/' . $file;
      if (file_exists($filename)) {
        require_once $filename;
        if (function_exists($function)) {
          return TRUE;
        }
      }
    }
  }

  return FALSE;
}
