(function() {
  var prepNiceVideo;

  prepNiceVideo = function() {
    return $('.nice-video--control').magnificPopup({
      disableOn: 700,
      type: 'iframe',
      mainClass: 'mfp-fade',
      removalDelay: 160,
      preloader: false,
      fixedContentPos: false
    });
  };

  $(document).ready(function() {
    // Grid toggle behavior, dev only
    $('.gridToggle').on('click', function() {
      return $('body').toggleClass('layout-grid--on');
    });
    // Include labels
    $('.includeToggle').on('click', function() {
      return $('body').toggleClass('twig-includes--on');
    });
    $('img').baseline(function() {
      var size;
      size = parseFloat(getComputedStyle(document.documentElement, null).getPropertyValue('font-size'));
      return size / 2;
    });
    return prepNiceVideo();
  });

}).call(this);
