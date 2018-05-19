'use strict';

var carousel_single = {
    cssEase: 'ease-in-out',
    dots: true,
    lazyLoad: 'progressive'
};

var carousel_center = {
    cssEase: 'ease-in-out',
    dots: true,
    lazyLoad: 'progressive',
    centerMode: true,
    centerPadding: '60px',
    sidesToShow: 3,
    responsive: [{
        breakpoint: 768,
        settings: {
            arrows: true,
            centerMode: true,
            centerPadding: '40px',
            slidesToShow: 3
        }
    }, {
        breakpoint: 480,
        settings: {
            arrows: true,
            centerMode: false,
            slidesToShow: 3
        }
    }]
};

var carousel = function carousel() {
    var $carousels = $('.carousel');
    var config = carousel_single; // default configuration
    if ($carousels.length < 1) return;

    var positionArrows = function positionArrows(slick, slide) {
        //arrows should be positioned at 40% of the width of the slide track
    };

    $carousels.on('init', function (e, slick) {
        slick.$slides.find('img').wrap('<div class="carousel__image-wrapper"></div>');
        console.log(slick);
        var buttonTop = slick.$slider.width();
        console.log(buttonTop);
    });
    $carousels.on('lazyLoaded', function (e, slick, image, imageSource) {
        //console.log(image,imageSource);
    });
    $carousels.on('afterChange', function (e, slick, currentSlide) {
        console.log('after change', slick, currentSlide);
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
