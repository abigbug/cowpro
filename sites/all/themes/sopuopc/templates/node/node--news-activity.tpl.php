<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <div class="news-line-one clearfix">
      <div class="col-md-8 the-img"> <img src="<?php print image_style_url('sopuo_default', $node->field_image['und'][0]['uri']); ?>" class="img-responsive"/> </div>
      <div class="col-md-4 the-right hidden-xs">
        <div class="row"> 
          
          <!-- Nav tabs -->
          <ul class="nav nav-tabs nav-justified" role="tablist">
            <li role="presentation" class="active"><a href="#home" role="tab" data-toggle="tab">非JD·EDU学员</a></li>
            <li role="presentation"><a href="#profile" role="tab" data-toggle="tab">JD·EDU学员</a></li>
          </ul>
          
          <!-- Tab panes -->
          <div class="tab-content">
            <div role="tabpanel" class="tab-pane active" id="home">
              <?php
$block = block_load('webform', 'client-block-75');
$output = @drupal_render(_block_get_renderable_array(_block_render_blocks(array($block))));
print $output;
?>
            </div>
            <div role="tabpanel" class="tab-pane" id="profile">
              <p class="efStudentInfo">详情请与自己所在的校区老师联系<br>
                或致电400-920-2116</p>
            </div>
          </div>
        </div>
      </div>
  </div>
  <div class="news-line2017 clearfix">
    <div class="row">
      <div class="col-md-8 the-left">
        <div class="clearfix toggleEvent">
          <div class="col-md-6 the-adddree"><i class="fa fa-map-marker"></i> <?php print @$node->field_active_address['und'][0]['value']; ?> </div>
          <div class="col-md-6 the-one"><i class="fa fa-calendar" ></i><?php print @date('Y-m-d',strtotime($node->field_event_date['und'][0]['value'])); ?> </div>
          <div class="col-md-6 the-two"><i class="fa fa-clock-o" ></i><?php print @$node->field_activity_time['und'][0]['value']; ?> </div>
          <div class="col-md-6 the-three"><i class="fa fa-address-card-o" ></i><?php print @$node->field_active_age['und'][0]['value']; ?></div>
        </div>
        <div class="clearfix  the-body"> <?php print @$node->body['und'][0]['value']; ?> </div>
      </div>
      <div class="col-md-4 the-right">    
                
	  <?php
$block1 = block_load('views', 'activity-block_3');
$output1 = @drupal_render(_block_get_renderable_array(_block_render_blocks(array($block1))));
print $output1;
?> </div>
    </div>
  </div>
  
  
</article>


