<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Privacy share links'),
  'description' => t('Social share links that respect privacy.'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Node'),
  'defaults' => array(
    'identica' => TRUE,
    'twitter' => TRUE,
    'google_plus' => TRUE,
    'tumblr' => TRUE,
    'diaspora' => TRUE,
    'facebook' => TRUE,
    'email' => TRUE,
    'print' => TRUE,
  ),
);

/**
 * Empty form so we can have the default override title.
 */
function palanteshare_privacy_share_links_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  foreach ($form_state['plugin']['defaults'] as $key => $value) {
    $form[$key] = array(
      '#title' => $key,
      '#type' => 'checkbox',
      '#default_value' => $conf[$key],
    );
  }

  // Does nothing!
  return $form;
}

function palanteshare_privacy_share_links_content_type_edit_form_submit($form, &$form_state) {
  $conf = $form_state['conf'];

  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}


function palanteshare_privacy_share_links_content_type_render($subtype, $conf, $panel_args, $context) {

  $node = isset($context->data) ? clone($context->data) : NULL;

  $title = $node->title;

  $uri = entity_uri('node', $node);
  $url = url($uri['path'], array('absolute' => TRUE));

  $summary = array();
  if (field_get_items('node', $node, 'body')) {
    $display = array(
      'label' => 'hidden',
      'type' => 'text_summary_or_trimmed',
    );
    $summary = field_view_field('node', $node, 'body', $display);
  }

  $links = array();

  if (!empty($conf['identica'])) {
    $links['identica'] = array(
      'title' => t('Identi.ca'),
      'href' => 'https://identi.ca/notice/new',
      'attributes' => array(
        'class' => 'identica',
      ),
      'query' => array(
        'status_textarea' => $title .' '. $url,
      ),
    );
  }

  if (!empty($conf['twitter'])) {
    $links['twitter'] = array(
      'title' => t('Twitter'),
      'href' => 'https://twitter.com/home',
      'query' => array(
        'status' => $title .' '. $url,
      ),
    );
  }

  if (!empty($conf['google_plus'])) {
    $links['google-plus'] = array(
      'title' => t('Google Plus'),
      'href' => 'https://plus.google.com/share',
      'query' => array(
        'url' => $url,
      ),
    );
  }

  if (!empty($conf['tumblr'])) {
    $links['tumblr'] = array(
      'title' => t('Tumblr'),
      'href' => 'http://www.tumblr.com/share',
    );
  }

  if (!empty($conf['diaspora'])) {
    $links['diaspora'] = array(
      'title' => t('Diaspora'),
      'href' => 'http://sharetodiaspora.github.com',
      'query' => array(
        'title' => $title,
        'url' => $url,
      ),
    );
  }

  if (!empty($conf['facebook'])) {
    $links['facebook'] = array(
      'title' => t('Facebook'),
      'href' => 'https://www.facebook.com/share.php',
      'query' => array(
        't' => $title,
        'u' => $url,
      ),
    );
  }

  if (!empty($conf['email'])) {
    $links['email'] = array(
      'title' => t('Email'),
      'href' => 'mailto:',
      'query' => array(
        'subject' => $title,
        'body' => trim(filter_xss(render($summary), array())) ."\r\n\r\n". $url ."\r\n",
      ),
    );
  }

  if (!empty($conf['print'])) {
    $links['print'] = array(
      'title' => t('Print'),
      'href' => '#',
      'absolute' => TRUE,
      'external' => TRUE,
      'attributes' => array(
        'onclick' => 'window.print();',
      ),
    );
  }

  $block = new stdClass();
  $block->title = t('Share');
  $block->content = array(
    '#theme' => 'links__node__sharing',
    '#links' => $links,
    '#attributes' => array('class' => array('links')),
  );

  ctools_add_css('palanteshare', 'palanteshare');

  return $block;
}
