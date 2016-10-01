<?php
class cowpro_creditor_assignment_handler_filter_amount extends views_handler_filter {
	function can_expose() {
		return FALSE;
	}

	/**
	 * See _node_access_where_sql() for a non-views query based implementation.
	 */
	function query() {
		// generate sql with GROUP BY united_parameter, node_created, nid
		/*
		$this->ensure_my_table ();

		$field_alias = 'united_parameter';

		$join = new views_join ();
		$join->construct ( 'field_data_field_united_parameter', $this->table_alias, 'nid', 'entity_id', array (), 'INNER' );
		$this->query->ensure_table ( 'field_data_field_united_parameter', $this->relationship, $join );

		$this->query->add_field ( 'field_data_field_united_parameter', 'field_united_parameter_value', $field_alias );
		$this->query->add_field ( 'field_data_field_united_parameter', 'field_united_parameter_value', 'cnt', array (
				'count' => TRUE
		) );

		$this->query->add_groupby ( $field_alias );
		*/
		$query->add_field('node', 'nid', 'node_nid', array('function' => 'groupby'));
		$query->add_groupby('node.nid');
	}
}
