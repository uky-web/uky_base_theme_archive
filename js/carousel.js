'use strict';

var carousel_single = {
    cssEase: 'ease-in-out',
    dots: true,
    lazyLoad: 'progressive'
};

var carousel_center = {
    cssEase: 'ease-in-out',
    lazyLoad: 'progressive',
    centerMode: true,
    dots: true,
    centerPadding: '110px',
    sidesToShow: 3,
    arrows: true,
    responsive: [{
        breakpoint: 768,
        settings: {
            centerMode: false,
            slidesToShow: 1
        }
    }, {
        breakpoint: 480,
        settings: {
            centerMode: false,
            slidesToShow: 1
        }
    }]
};

var carousel = function carousel() {
    var $carousels = $('.carousel');
    var config = carousel_single; // default configuration
    if ($carousels.length < 1) return;

    var positionArrowsSingle = function positionArrowsSingle(slick) {
        var buttonTop = slick.slideWidth * .4;
        var buttons = slick.$nextArrow.add(slick.$prevArrow);
        buttons.css({ top: buttonTop });
    };

    var positionArrowsCentered = function positionArrowsCentered(slick) {
        var $currentSlide = $(slick.$slides[slick.currentSlide]);
        var $currentImage = $currentSlide.find('img');
        var $currentTrack = slick.$slideTrack;
        var imgHeight = $currentImage.height();
        var imgNatHeight = $currentImage.prop('naturalHeight');
        if (imgHeight > 0) {
            var padding = (imgHeight - imgNatHeight) / 2;
            var buttonTop = imgHeight * .5 + padding;
            var buttons = slick.$nextArrow.add(slick.$prevArrow);
            buttons.css({ top: buttonTop });
            $currentTrack.css({ paddingTop: padding });
        }
    };

    $carousels.on('lazyLoaded', function (e, slick, image, imageSource) {});
    $carousels.on('init setPosition afterChange', function (e, slick) {
        if ($(e.currentTarget).has('.carousel--single')) {
            positionArrowsSingle(slick);
        }
        if ($(e.currentTarget).has('.carousel--center')) {
            positionArrowsCentered(slick);
        }
    });
    $carousels.map(function (index, elem) {
        // override configuration based on class name
        if (elem.classList.contains('carousel--center')) {
            config = carousel_center;
        }
        $(elem).slick(config);
    });
};
//# sourceMappingURL=carousel.js.map
