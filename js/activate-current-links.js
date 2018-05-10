(function() {
  var $;

  $ = jQuery;

  Drupal.behaviors.activate_current_links = {
    attach: function(context, settings) {
      $('a').each(function() {
        var $a, url;
        $a = $(this);
        url = $a.attr('href');
        if (url === window.location.href || url === window.location.pathname) {
          $a.addClass('is-active');
        }
      });
    }
  };

}).call(this);
