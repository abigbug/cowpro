<?php

class cowpro_userpoints_handler_field_operation extends views_handler_field {
  function render($values) {
    $uid = $this->get_value($values);

    $link = $GLOBALS['base_url'] .  "/user/$uid/points";
    return "<a href='$link'>详情</a>";
  }
}
