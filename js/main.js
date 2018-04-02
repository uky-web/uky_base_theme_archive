(function() {
  var prepNiceVideo;

  prepNiceVideo = function() {
    $('iframe[src*="youtube"]').parent().fitVids();
    $('.nice-video button').on('click', function() {
      var $iframe, $wrapper, closure;
      $wrapper = $(this).parents('.nice-video');
      $wrapper.toggleClass('nice-video--playing');
      $iframe = $wrapper.find('iframe');
      closure = function() {
        return $iframe.attr({
          'src': $iframe.attr('src').replace("autoplay=0", "autoplay=1")
        });
      };
      setTimeout(closure, 300);
    });
    return $('.nice-video').addClass('nice-video--ready');
  };

  $(document).ready(function() {
    // Grid toggle behavior, dev only
    $('.gridToggle').on('click', function() {
      return $('body').toggleClass('layout-grid--on');
    });
    return prepNiceVideo();
  });

}).call(this);
