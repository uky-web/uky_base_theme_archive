'use strict';

/* 
 * code specific to patternlab goes here
 */

$(document).ready(function () {
    // Grid toggle behavior, dev only
    $('.gridToggle').on('click', function () {
        $('body').toggleClass('layout-grid--on');
    });
    // Include labels
    $('.includeToggle').on('click', function () {
        $('body').toggleClass('twig-includes--on');
    });
});
//# sourceMappingURL=patternlab.js.map
