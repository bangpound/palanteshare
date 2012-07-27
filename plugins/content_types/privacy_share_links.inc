<?php
function eff_library_eff_share_blog_content_type_render($subtype, $conf, $panel_args, $context) {
  $node = $context->data;
  $title = $node->title;
  $url = "https://www.eff.org".$_SERVER['REQUEST_URI'];
  $body_trimmed = substr(strip_tags($node->body['und'][0]['safe_value']), 0, 260);
  $identica_link = "https://identi.ca/notice/new?status_textarea=".urlencode("$title $url");
  $twitter_link = "https://twitter.com/home?status=".urlencode("$title $url");
  $google_plus_link = "https://plus.google.com/share?url=".urlencode($url);
  $diaspora_link = "http://sharetodiaspora.github.com/?title=".str_replace("+", " ", urlencode($title))."&url=".urlencode($url);
  $facebook_link = "https://www.facebook.com/share.php?u=".urlencode($url)."&t=".urlencode($title);
  $email_link = "mailto:?subject=".$title."&body=".substr(htmlspecialchars(strip_tags($node->body['und'][0]['safe_value'])), 0, 260)."...%0D%0A%0D%0A".$url."%0D%0A";

  // build the block
  $block = new stdClass();
  $block->title   = NULL;
  $block->content =
    '<div class="share-links">'.
    '<a href="'.$twitter_link.'" target="_blank"><img src="/sites/all/themes/frontier/images/share/twitter.gif" alt="Share on Twitter" /></a>'.
    '<a href="'.$facebook_link.'" target="_blank"><img src="/sites/all/themes/frontier/images/share/facebook.gif" alt="Share on Facebook" /></a>'.
    '<a href="'.$google_plus_link.'" onclick="javascript:window.open(this.href, \'\', \'menubar=no,toolbar=no,resizable=yes,scrollbars=yes,height=600,width=600\');return false;"><img src="/sites/all/themes/frontier/images/share/gplus-16.png" alt="Share on Google+"/></a>'.
    '<a href="'.$identica_link.'" target="_blank"><img src="/sites/all/themes/frontier/images/share/identica.gif" alt="Share on Identi.ca" /></a>'.
    '<a href="'.$diaspora_link.'" target="_blank"><img src="/sites/all/themes/frontier/images/share/diaspora-16.png" alt="Share on Diaspora" /></a>'.
    '<a href="'.$email_link.'" target="_blank"><img src="/sites/all/themes/frontier/images/share/email.gif" alt="Email This" /></a>'.
    '</div>';
  return $block;
}
