CRAG.controller('MainController', function($scope, $rootScope, $http, $state, ngProgressFactory) {

    $scope.OnInit = function() {
        // Create the Application Progress Bar
        $rootScope.progressbar = ngProgressFactory.createInstance();
    };

    $scope.MenuClick = function(option) {
        $state.go(option);
    };

    // =========================================================================
    // MOUSE CURSOR / POINTER FUNCTIONS
    // =========================================================================

    $rootScope.waiting = false;        // If true, the system is waiting something
    $rootScope.col_resizing = false;   // If true, the user is resizing a column
    $rootScope.CtrlKeyPressed = false; // If true, the Ctrl key is pressed

    $rootScope.MouseOverType = {
        Nothing     : 0,             // The mouse is over the blank page
        Viewer      : 1,             // The mouse is over the viewer control
        Gene        : 2,             // The mouse is over the gene column
        StatsMargin : 3,
        Previous    : 9              // The mouse is over the previous control
    };
    $rootScope.previous_mouse_over = $rootScope.MouseOverType.Nothing;

    $rootScope.SetMousePointer = function(mouse_over) {
        if (mouse_over == $rootScope.MouseOverType.Previous) {
            mouse_over = $rootScope.previous_mouse_over;
        }

        switch(mouse_over) {
            case $rootScope.MouseOverType.Nothing:
                if ($rootScope.waiting) { cursor = 'wait'; }
                else { 
                if ($rootScope.col_resizing) { cursor = 'col-resize'; }
                else { cursor = 'default'; }}
                $rootScope.previous_mouse_over = mouse_over;
                break;
            case $rootScope.MouseOverType.Viewer:
                if ($rootScope.waiting) { cursor = 'wait'; }
                else {
                if ($rootScope.col_resizing) { cursor = 'col-resize'; }
                else {cursor = 'crosshair'; }}
                $rootScope.previous_mouse_over = mouse_over;
                break;
            case $rootScope.MouseOverType.Gene:
                if ($rootScope.waiting) { cursor = 'wait'; }
                else {
                if ($rootScope.col_resizing) { cursor = 'col-resize'; }
                else {
                    if ($rootScope.CtrlKeyPressed) { cursor = 'zoom-out'; }
                    else { cursor = 'zoom-in'; }
                }}
                $rootScope.previous_mouse_over = mouse_over;
                break;
            case $rootScope.MouseOverType.FixedHeader:
                if ($rootScope.waiting) { cursor = 'wait'; }
                else {
                if ($rootScope.col_resizing) { cursor = 'col-resize'; }
                else {cursor = 'zoom-out'; }}
                $rootScope.previous_mouse_over = mouse_over;
                break;
            case $rootScope.MouseOverType.StatsMargin:
                if ($rootScope.waiting) { cursor = 'wait'; }
                else { cursor = 'col-resize'; }
                $rootScope.previous_mouse_over = mouse_over;
                break;
        }

        if (cursor != '') {
            document.body.style.cursor = cursor; // Page cursor
            // canvas_.style.cursor = cursor; // Canvas cursor
        }
    };

    $rootScope.SetWait = function(wait) {
        // console.log("homeController::SetWait");
        $rootScope.waiting = wait;
        $rootScope.SetMousePointer($rootScope.MouseOverType.Previous);
    };

    // =========================================================================
    // MAIN
    // =========================================================================

    $scope.OnInit();
});






