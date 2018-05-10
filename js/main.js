(function() {
  var prepAmbientVideo, prepImageGallery, prepNiceVideo;

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

  // Start the ambient video loading and prep the play/pause button behavior
  prepAmbientVideo = function() {
    var av, control, sources;
    av = $('.ambient-video video');
    if (av.length < 1) {
      return;
    }
    sources = av.find('source');
    if (window.matchMedia("(min-width: 64rem)").matches) {
      av.attr('autoplay', true);
      av[0].play();
      // Since the video is working, enable the play/pause control
      control = $('.ambient-video button');
      control.show();
      control.click(function(e) {
        var button, video;
        button = $(e.currentTarget);
        video = button.siblings('video')[0];
        button.toggleClass('video-button--paused');
        if (video.paused) {
          video.play();
          return button.attr('aria-label', button.data('pressed-label'));
        } else {
          video.pause();
          return button.attr('aria-label', button.data('unpressed-label'));
        }
      });
    } else {
      av[0].stop();
    }
  };

  prepImageGallery = function() {
    var fitCaption, gallery, grid, modals;
    gallery = $('.image-gallery');
    grid = gallery.masonry({
      columnWidth: '.image-gallery__block-sizer',
      itemSelector: '.image-gallery__block'
    });
    fitCaption = function($c) {
      var $caption, $image, captionWidth, h, r, w;
      $image = $c.find('img');
      $caption = $c.find('figcaption');
      w = $image.width();
      h = $image.height();
      r = w / h;
      captionWidth = w < 300 ? "50vw" : w;
      $caption.css({
        maxWidth: captionWidth
      });
      if (r < 1) {
        $c.addClass('mfp-portrait');
        return $c.removeClass('mfp-landscape');
      } else {
        $c.addClass('mfp-landscape');
        return $c.removeClass('mfp-portrait');
      }
    };
    modals = gallery.magnificPopup({
      delegate: 'a',
      type: 'image',
      mainClass: 'mfp-fade',
      tLoading: 'Loading image #%curr%...',
      gallery: {
        enabled: true,
        navigateByImgClick: true,
        preload: [0, 1]
      },
      image: {
        tError: '<a href="%url%">The image #%curr%</a> could not be loaded.',
        verticalFit: false,
        titleSrc: function(item) {
          return $(item.el).find('figcaption').html();
        }
      },
      callbacks: {
        resize: function() {
          return fitCaption($(this.content));
        },
        imageLoadComplete: function() {
          return fitCaption($(this.content));
        }
      }
    });
    grid.imagesLoaded().progress(function() {
      return grid.masonry('layout');
    });
    return grid.imagesLoaded().done(function() {
      return gallery.magnificPopup('open');
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
    /*
    $('img').baseline () ->
    	size = parseFloat(getComputedStyle(document.documentElement, null).getPropertyValue('font-size'));
    	return size / 2
    */
    prepNiceVideo();
    return prepAmbientVideo();
  });

}).call(this);
