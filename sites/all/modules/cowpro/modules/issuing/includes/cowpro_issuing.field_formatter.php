<?php
/**
 * 参考 user_reference_field_formatter_prepare_view()
 * Implements hook_field_formatter_prepare_view().
 *
 * Preload all user referenced by items using 'full entity' formatters.
 */
function _user_reference_field_formatter_prepare_view($entity_type, $entities, $field, $instances, $langcode, &$items, $displays) {
	// Load the referenced users, except for the 'user_reference_uid' which does
	// not need full objects.

	// Collect ids to load.
	$ids = array();
	foreach ($items as $delta => $item) {
		if ($item['access']) {
			$ids[$item['uid']] = $item['uid'];
		}
	}
	$entities = user_load_multiple($ids);

	// Add the loaded user objects to the items.
	foreach ($items as $delta => $item) {
		if ($item['access']) {
			$items[$delta]['user'] = $entities[$item['uid']];
		}
	}
}

function cowpro_issuing_field_formatter_view_user_reference($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
	_user_reference_field_formatter_prepare_view($entity_type, $entity, $field, $instance, $langcode, $items, $display);
	$result = array();
	// Collect the list of user ids.
	$uids = array();
	foreach ($items as $delta => $item) {
		$uids[$item['uid']] = $item['uid'];
	}

	foreach ($items as $delta => $item) {
		if ($item['access']) {
			$user = $item['user'];
			$label = entity_label('user', $user);
			$uri = entity_uri('user', $user);
			$result[$delta] = array(
					'#type' => 'link',
					'#title' => $label,
					'#href' => $uri['path'],
					'#options' => $uri['options'],
			);
		}
	}

	return $result;
}

/**
 * 参考 node_reference_field_formatter_prepare_view()
 * Implements hook_field_formatter_prepare_view().
 *
 * Preload all nodes referenced by items using 'full entity' formatters.
 */
function _node_reference_field_formatter_prepare_view($entity_type, $entities, $field, $instances, $langcode, &$items, $displays) {
	// Load the referenced nodes, except for the 'node_reference_nid' which does
	// not need full objects.

	// Collect ids to load.
	$ids = array();
	foreach ($items as $delta => $item) {
		if ($item['access']) {
			$ids[$item['nid']] = $item['nid'];
		}
	}
	$entities = node_load_multiple($ids);

	// Add the loaded nodes to the items.
	foreach ($items as $delta => $item) {
		if ($item['access']) {
			$items[$delta]['node'] = $entities[$item['nid']];
		}
	}
}

function cowpro_issuing_field_formatter_view_node_reference($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
	_node_reference_field_formatter_prepare_view($entity_type, $entity, $field, $instance, $langcode, $items, $display);
	$settings = $display['settings'];
  $result = array();
	foreach ($items as $delta => $item) {
		if ($item['access']) {
			$node = $item['node'];
			$label = entity_label('node', $node);
			if ($display['type'] == 'node_reference_default') {
				$uri = entity_uri('node', $node);
				$result[$delta] = array(
						'#type' => 'link',
						'#title' => $label,
						'#href' => $uri['path'],
						'#options' => $uri['options'],
				);
			}
			else {
				$result[$delta] = array(
						'#markup' => check_plain($label),
				);
			}
			if (!$node->status) {
				$result[$delta]['#prefix'] = '<span class="node-unpublished">';
				$result[$delta]['#suffix'] = '</span>';
			}
		}
	}
	return $result;
}

function cowpro_issuing_field_formatter_view_list_text($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
      $allowed_values = list_allowed_values($field, $instance, $entity_type, $entity);
      foreach ($items as $delta => $item) {
        if (isset($allowed_values[$item['value']])) {
          $output = field_filter_xss($allowed_values[$item['value']]);
        }
        else {
          // If no match was found in allowed values, fall back to the key.
          $output = field_filter_xss($item['value']);
        }
        $element[$delta] = array('#markup' => $output);
      }
	return $element;
}

function cowpro_issuing_field_formatter_view_image($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
	$settings = $display['settings'];
	$settings += array(
			'image_link' => 'file',
			'image_style' => 'thumbnail',
	);

  $element = array();

  // Check if the formatter involves a link.
  if ($settings['image_link'] == 'content') {
    $uri = entity_uri($entity_type, $entity);
  }
  elseif ($settings['image_link'] == 'file') {
    $link_file = TRUE;
  }

  foreach ($items as $delta => $item) {
    if (isset($link_file)) {
      $uri = array(
        'path' => file_create_url($item['uri']),
        'options' => array(),
      );
    }
    $element[$delta] = array(
      '#theme' => 'image_formatter',
      '#item' => $item,
      '#image_style' => $settings['image_style'],
      '#path' => isset($uri) ? $uri : '',
    );
  }

  return $element;
}

function cowpro_issuing_field_formatter_view_taxonomy_term_reference($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  foreach ($items as $delta => $item) {
  	$name = ($item['tid'] != 'autocreate' ? $item['taxonomy_term']->name : $item['name']);
  	$element[$delta] = array(
  			'#markup' => check_plain($name),
  	);
  }

	return $element;
}
