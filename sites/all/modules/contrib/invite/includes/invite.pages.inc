<?php

/**
 * @file
 */

/**
 * Invte view callback.
 *
 * @param Invite $invite
 *
 * @return bool
 */
function invite_view($invite) {
  drupal_set_title(entity_label('invite', $invite));
  return entity_view('invite', array(entity_id('invite', $invite) => $invite), 'full');
}

/**
 * Invitation accept callback.
 *
 * @param Invite $invite
 */
function invite_accept($invite) {
  global $user;

  $redirect = '<front>';
  $message = '';
  $type = 'status';

  if ($user->uid == $invite->uid) {
    $message = t('You could not use own invite.');
    $type = 'error';
    $redirect = '<front>';
  }
  elseif (!$user->uid && (empty($invite->invitee)) && $invite->status() == INVITE_VALID) {
    // Process new user invitation.
    $_SESSION[INVITE_SESSION_CODE] = $invite->reg_code;
    $redirect = variable_get('invite_registration_path', 'user/register');
  }
  elseif (!empty($user->uid) && ($invite->status() == INVITE_VALID)) {
    $invite->invitee = $user->uid;
    $invite->joined = REQUEST_TIME;
    $invite->status = INVITE_USED;
    entity_save('invite', $invite);

    unset($_SESSION[INVITE_SESSION_CODE]);
    $inviter = $invite->inviter();
    $message = t('You have accepted the invitation from !user.', array('!user' => theme('username', array('account' => $inviter))));
    $redirect = 'user';
  }
  elseif (empty($user->uid) && !empty($invite->invitee) && ($invite->status() == INVITE_VALID)) {
    $_SESSION[INVITE_SESSION_CODE] = $invite->reg_code;
    $message = t('You should login first to accept this invitation.');
    $type = 'warning';
    $redirect = 'user/login';
  }
  else {
    // Cover the rest of the error which redirect to /user instead of 403.
    $type = 'error';
    $redirect = 'user';

    switch ($invite->status()) {
      case INVITE_WITHDRAWN:
        $message = t('This invitation has been withdrawn.');
        break;

      case INVITE_USED:
        $message = t('This invitation has already been used.');
        break;

      case INVITE_EXPIRED:
        $message = t('This invitation has expired.');
        break;
    }
  }

  // Give a chance for customization.
  $data = array(
    'redirect' => &$redirect,
    'message' => &$message,
    'type' => &$type,
    'invite' => $invite,
  );
  drupal_alter('invite_accept', $data);

  if (!empty($message)) {
    drupal_set_message($message, $type);
  }
  drupal_goto($redirect);
}

/**
 * Menu callback; resend an expired invite.
 *
 * @param Invite $invite
 *   An invite object.
 *
 * @return array
 *   renderable array, representing a page.
 */
function invite_resend($invite) {
  if ($invite->sendInvite()) {
    drupal_set_message(t('Invitation has been successfully resent.'));

    return array(
      'invite' => entity_view('invite', array(entity_id('invite', $invite) => $invite), 'full'),
    );
  }
  else {
    return MENU_NOT_FOUND;
  }
}

/**
 * Menu callback; display confirm form to withdraw an invitation.
 *
 * @param $form
 * @param $form_state
 * @param Invite $invite
 *   Invite object.
 *
 * @return array
 */
function invite_withdraw_form($form, &$form_state, $invite) {
  global $user;

  $form['invite'] = array(
    '#type' => 'value',
    '#value' => $invite,
  );
  $invite_render_tree = entity_view('invite', array(entity_id('invite', $invite) => $invite), 'full');
  $description = (!$invite->joined && $invite->expiry > REQUEST_TIME) ? t('The invitee will no longer be able to register using this invitation !invite<br/>', array('!invite' => drupal_render($invite_render_tree))) : '';
  $redirect = !empty($_REQUEST['destination']) ? $_REQUEST['destination'] : '<front>';

  return confirm_form(
    $form,
    t('Are you sure you want to withdraw the invitation?'),
    $redirect,
    $description . t('This action cannot be undone.'),
    t('Withdraw'),
    t('Cancel')
  );
}

/**
 * Submit handler to withdraw an invitation.
 *
 * @param $form
 * @param $form_state
 */
function invite_withdraw_form_submit($form, &$form_state) {
  $invite = $form_state['values']['invite'];

  db_update('invite')
    ->fields(array(
      'canceled' => 1,
      'status' => INVITE_WITHDRAWN,
    ))
    ->condition('reg_code', $invite->reg_code)
    ->execute();

  drupal_set_message(t('!invite has been withdrawn.', array('!invite' => l('Invitation', 'invite/' . $invite->iid))));

  // Notify other modules.
  module_invoke_all('invite_withdraw', $invite);
  if (module_exists('rules')) {
    rules_invoke_event('invite_withdraw', $invite);
  }

  $form_state['redirect'] = '<front>';
}
