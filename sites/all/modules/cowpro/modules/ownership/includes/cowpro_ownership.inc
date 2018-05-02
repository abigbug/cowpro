<?php
function _cowpro_ownership_action_roles(&$entities, $context = array(),$rtype) { 
  $role = user_role_load_by_name ('客户经理');
  $rid=$role->rid;
  foreach ($entities as $entity) {
    $wrapper = entity_metadata_wrapper('user', $entity);
    if (!$wrapper->roles->access("update")) {
      return;
    }
    $roles = $wrapper->roles->value();
    if($rtype==1){
      $roles = array_merge($roles,array($rid));
    }
    if($rtype==0){
      $roles = array_diff($roles,array($rid));
    }
    //var_dump($roles);die();
    $wrapper->roles->set($roles);
    $wrapper->save();
  }
}
function _cowpro_ownership_action_add(&$entities, $context = array()) {
    global $user;
    $relationship_type = user_relationships_type_load(array('name'=>'客户归属'));
    $requestee_id=reset($context['add_ownership']);
    foreach ($entities as $entity) {
      $relationships = user_relationships_load(array(
              'requester_id' => $entity->uid,
              'rtid'    => $relationship_type->rtid,
      ));
      $relationship = array_shift($relationships);
      if ($relationship) {
          user_relationships_delete_relationship($relationship, $user, "remove");
      }
      $relationship = new stdClass;
      $relationship->requester_id = $entity->uid;
      $relationship->requestee_id = $requestee_id;
      $relationship->rtid = $relationship_type->rtid;
      $relationship->approved = 1;
      user_relationships_save_relationship($relationship);
    }
}
function _cowpro_ownership_action_cancel(&$entities, $context = array()) {
    global $user;
    $relationship_type = user_relationships_type_load(array('name'=>'客户归属'));
    foreach ($entities as $entity) {
      $relationships = user_relationships_load(array(
              'requester_id' => $entity->uid,
              'rtid'    => $relationship_type->rtid,
      ));
      $relationship = array_shift($relationships);
      if ($relationship) {
          user_relationships_delete_relationship($relationship, $user, "remove");
      }
    }
}