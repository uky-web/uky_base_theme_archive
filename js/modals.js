'use strict';

var modals = function modals() {
    $(".modal-control").magnificPopup();

    $('.nice-video--control').magnificPopup({
        disableOn: 700,
        type: 'iframe',
        mainClass: 'mfp-fade',
        removalDelay: 160,
        preloader: false,
        fixedContentPos: false
    });
};

$(document).ready(function () {
    modals();
});
//# sourceMappingURL=modals.js.map
