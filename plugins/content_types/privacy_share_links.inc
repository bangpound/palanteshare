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
);

/**
 * Empty form so we can have the default override title.
 */
function palanteshare_privacy_share_links_content_type_edit_form($form, &$form_state) {
  // Does nothing!
  return $form;
}

function palanteshare_privacy_share_links_content_type_render($subtype, $conf, $panel_args, $context) {

  $node = isset($context->data) ? clone($context->data) : NULL;

  $title = $node->title;

  $uri = entity_uri('node', $node);
  $url = url($uri['path'], array('absolute' => TRUE));

  $display = array(
    'label' => 'hidden',
    'type' => 'text_summary_or_trimmed',
  );
  $summary = field_view_field('node', $node, 'body', $display);

  $links = array();

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

  $links['twitter'] = array(
    'title' => t('Twitter'),
    'href' => 'https://twitter.com/home',
    'query' => array(
      'status' => $title .' '. $url,
    ),
  );

  $links['google-plus'] = array(
    'title' => t('Google Plus'),
    'href' => 'https://plus.google.com/share',
    'query' => array(
      'url' => $url,
    ),
  );

  $links['diaspora'] = array(
    'title' => t('Diaspora'),
    'href' => 'http://sharetodiaspora.github.com',
    'query' => array(
      'title' => $title,
      'url' => $url,
    ),
  );

  $links['facebook'] = array(
    'title' => t('Facebook'),
    'href' => 'https://www.facebook.com/share.php',
    'query' => array(
      't' => $title,
      'u' => $url,
    ),
  );

  $links['email'] = array(
    'title' => t('Email'),
    'href' => 'mailto:',
    'query' => array(
      'subject' => $title,
      'body' => trim(filter_xss(render($summary), array())) ."\r\n\r\n". $url ."\r\n",
    ),
  );

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
