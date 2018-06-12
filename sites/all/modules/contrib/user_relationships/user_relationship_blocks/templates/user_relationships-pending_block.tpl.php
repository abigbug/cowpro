<?php
/**
 * @file
 * Template for relationships requests block
 * List all pending requests and provide links to the actions that can be taken on those requests
 */
if ($relationships) {
  $list = array();
  foreach ($relationships as $rtid => $relationship) {
    if ($user->uid == $relationship->requester_id) {
      $relation_to =& $relationship->requestee;
      $controls = theme('user_relationships_pending_request_cancel_link', array('uid' => $account->uid, 'rid' => $relationship->rid));
      $line = t('@rel_name to !username (!controls)', array('!username' => theme('username', array('account' => $relation_to)), '!controls' => $controls) + user_relationships_type_translations($relationship));
      $key = t('Sent requests');
    }
    else {
      $relation_to =& $relationship->requester;
      $controls =
        theme('user_relationships_pending_request_approve_link', array('uid' => $account->uid, 'rid' => $relationship->rid)).'|'.
        theme('user_relationships_pending_request_disapprove_link', array('uid' => $account->uid, 'rid' => $relationship->rid));
      $line = t('@rel_name from !username (!controls)', array('!username' => theme('username', array('account' => $relation_to)), '!controls' => $controls) + user_relationships_type_translations($relationship));
      $key = t('Received requests');
    }
    $list[$key][] = $line;
  }

  $output = array();
  foreach ($list as $title => $users) {
    $output[] = theme('item_list', array('items' => $users, 'title' => $title));
  }
}

print isset($output) ? implode('', $output) : t('No Pending Requests');

?>
