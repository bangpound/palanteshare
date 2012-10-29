(function ($) {

/**
 * Attach the machine-readable name form element behavior.
 */
Drupal.behaviors.privacyShareGoogleAnalytics = {
  attach: function (context, settings) {
    $('.pane-privacy-share-links .pane-content ul.links a', context).once(function () {
      var network = $(this).parent('li').attr('class');
      $(this).click(function () {
        _gaq.push(['_trackSocial', network, 'share']);
      });
    });
  }
};

})(jQuery);
