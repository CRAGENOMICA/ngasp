CRAG.controller('ViewerController', function($scope,
                                             $rootScope,
                                             $state,
                                             $timeout,
                                             drawing,
                                             viewer,
                                             vcte) {

    // =========================================================================
    // PAGE DATA
    // =========================================================================
    
    var canvas_ = null;
    var ctx_    = null;

    $scope.viewer = {};

    // -------------------------------------------------------------------------
    // TBD
    // -------------------------------------------------------------------------

    $scope.ViewerHasData = function() {
        return viewer.ViewerHasData($scope.viewer);
    };

    $scope.StatsHasData = function() {
        return viewer.StatsHasData($scope.viewer);
    };

    // =========================================================================
    // USER ACTIONS
    // =========================================================================

    // -------------------------------------------------------------------------
    // MENU - OPEN FILES DIALOG
    // -------------------------------------------------------------------------
    var previous_files_ = { // It is a temporary struct for storing file names
        file_tfa: '',       // of the OpenFilesDialog
        file_gff: '',
        file_weights: '',
        file_stats: ''
    };

    $scope.OnOpenFilesDialog = function() {
        /*
        var test = 2;

        if (test == 0) {
            $scope.viewer.files[vcte.FileType.TFA].file_name      = "./data/<filename>";
            $scope.viewer.files[vcte.FileType.GFF].file_name      = "";
            $scope.viewer.files[vcte.FileType.WEIGHTS].file_name  = "";
            $scope.viewer.files[vcte.FileType.STATS].file_name    = "";
        }

        // DEBUG ***************************************************************
        if (test == 1) {
            $scope.viewer.files[vcte.FileType.TFA].file_name      = "./data/206_tfasta_chr1_1.tfa.gz";
            $scope.viewer.files[vcte.FileType.GFF].file_name      = "";
            $scope.viewer.files[vcte.FileType.WEIGHTS].file_name  = "";
            $scope.viewer.files[vcte.FileType.STATS].file_name    = "";
        }

        if (test == 2) {
            $scope.viewer.files[vcte.FileType.TFA].file_name      = "./data/100Kchr10.tfa.gz";
            $scope.viewer.files[vcte.FileType.GFF].file_name      = "./data/100Kchr10_criteria_max.gff";
            $scope.viewer.files[vcte.FileType.WEIGHTS].file_name  = "./data/100Kchr10_tfa2tfa_02B.tfa_npops1_nsam42_nonsynonymous_max_ExcludeMissingVariantsmhits_NOoutg_ploidy1_WEIGHTS.txt.gz";
            $scope.viewer.files[vcte.FileType.STATS].file_name    = "./data/mstatspop_100chr10.tfa.15.txt";
        }

        if (test == 3) {
            $scope.viewer.files[vcte.FileType.TFA].file_name      = "./data/100Kchr10.tfa.gz";
            $scope.viewer.files[vcte.FileType.GFF].file_name      = "./data/100Kchr10_criteria_max.gff";
            $scope.viewer.files[vcte.FileType.WEIGHTS].file_name  = "";
            $scope.viewer.files[vcte.FileType.STATS].file_name    = "./data/mstatspop_100chr10.tfa.15.txt";
        }
        // *********************************************************************
        */
        previous_files_ = {
            file_tfa: $scope.viewer.files[vcte.FileType.TFA].file_name,
            file_gff: $scope.viewer.files[vcte.FileType.GFF].file_name,
            file_weights: $scope.viewer.files[vcte.FileType.WEIGHTS].file_name,
            file_stats: $scope.viewer.files[vcte.FileType.STATS].file_name
        };
    };

    $scope.OnAcceptRefreshFiles = function() {
        previous_files_ = {
            file_tfa: '',
            file_gff: '',
            file_weights: '',
            file_stats: ''
        };

        viewer.LoadFiles($scope.viewer, true);
    };

    $scope.OnCancelRefreshFiles = function() {
        $scope.viewer.files[vcte.FileType.TFA].file_name = previous_files_.file_tfa;
        $scope.viewer.files[vcte.FileType.GFF].file_name = previous_files_.file_gff;
        $scope.viewer.files[vcte.FileType.WEIGHTS].file_name = previous_files_.file_weights;
        $scope.viewer.files[vcte.FileType.STATS].file_name = previous_files_.file_stats;

        previous_files_ = {
            file_tfa: '',
            file_gff: '',
            file_weights: '',
            file_stats: ''
        };
    };

    // -------------------------------------------------------------------------
    // VIEWER
    // -------------------------------------------------------------------------

    $scope.GetViews = function() {
        return vcte.views;
    };

    $scope.OnSetView = function(id) {
        viewer.OnChangeViewType($scope.viewer, id);
    };

    $scope.OnClose = function() {
        viewer.OnClose($scope.viewer);
    };

    // -------------------------------------------------------------------------
    // SLIDER
    // -------------------------------------------------------------------------

    // var in_slide_range = false;


    // This event fires up only on mouseup over the slider
    $scope.OnChangeSliderRange = function() {
        viewer.OnChangeSliderRange($scope.viewer);
    }

    $scope.OnViewerMoveUp = function() {
        viewer.OnViewerMoveUp($scope.viewer);
    };

    $scope.OnViewerMoveDown = function() {
        viewer.OnViewerMoveDown($scope.viewer);
    };

    /*
    $scope.$watch('viewer.position', function() {
        viewer.OnChangeSliderRange($scope.viewer);
    });

    $scope.$watch('viewer.max_position', function() {
        viewer.OnChangeSliderRange($scope.viewer);
    });
    */

    // -------------------------------------------------------------------------
    // MOUSE
    // -------------------------------------------------------------------------

    function OnMouseMove(evt) {
        if (viewer.OnMouseMove($scope.viewer, evt)) { $scope.$apply(); }
    };

    function OnMouseDown(evt) {
        if (viewer.OnMouseDown($scope.viewer, evt)) { $scope.$apply(); }
    };

    function OnMouseUp(evt) {
        if (viewer.OnMouseUp($scope.viewer, evt)) { $scope.$apply(); }

        // This event fires up only on mouseup over the canvas:
        $scope.OnChangeSliderRange();
    };

    function OnMouseWheel(evt) {
        viewer.OnMouseWheel($scope.viewer, evt);
    };

    function OnKeyDown(evt) { // evt.keyCode
        if (($rootScope.CtrlKeyPressed == false) && (evt.ctrlKey == true)) {
            $rootScope.CtrlKeyPressed = true;
            $rootScope.SetMousePointer($rootScope.MouseOverType.Previous);
        }
    };

    function OnKeyUp(evt) {
        if ($rootScope.CtrlKeyPressed == true) {
            $rootScope.CtrlKeyPressed = false;
            $rootScope.SetMousePointer($rootScope.MouseOverType.Previous);
        }
    };

    // -------------------------------------------------------------------------
    // MENU - STATISTICS
    // -------------------------------------------------------------------------

    $scope.OnTogleStatsVisibility = function(property) {
        $scope.viewer.stats_options[property] =
            !$scope.viewer.stats_options[property];
        viewer.DrawStatistics($scope.viewer);
    };

    // -------------------------------------------------------------------------
    // STATISTICS DIALOG
    // -------------------------------------------------------------------------

    $scope.OnToggleStatSelection = function toggleSelection(stat_name) {
        var stats_names = $scope.viewer.files[vcte.FileType.STATS].stats_names;

        for(var i = 0; i < stats_names.length; i++) {
            if (stats_names[i].name == stat_name) {
                stats_names[i].selected = !stats_names[i].selected;
                break; //<---------------------------------- break loop
            }
        }
    };

    $scope.OnCloseStatsSelection = function() {
        viewer.NormalizeStatisticalDataForRenderingIt($scope.viewer);
        viewer.OnDrawControl($scope.viewer);
    };

    // -------------------------------------------------------------------------
    // CANVAS
    // -------------------------------------------------------------------------

    $scope.OnSaveCanvasAsImage = function() {
        var dataURL = canvas_.toDataURL('image/png');
        button = document.getElementById("btn-download");
        button.href = dataURL;
    };

    // =========================================================================
    // MAIN
    // =========================================================================

    function OnAllFilesLoaded() {
    };

    $scope.OnInit = function() {

        // ---------------------------------------------------------------------
        // T-FASTA VIEWER CONTROL INITIALIZATION
        // ---------------------------------------------------------------------

        // Create the canvas

        canvas_ = document.getElementById("myCanvas");
        ctx_ = canvas_.getContext("2d");
        viewer.OnInit($scope.viewer, canvas_, ctx_);


        $scope.viewer.OnAllFilesLoaded = OnAllFilesLoaded;


        // Disabling canvas' context menu

        canvas_.oncontextmenu = function() {
             return false;  
        } 

        // Add page and canvas listeners

        canvas_.addEventListener('DOMMouseScroll', OnMouseWheel, false);
        canvas_.addEventListener('mousemove', OnMouseMove, false);
        canvas_.addEventListener('mousedown', OnMouseDown, false);

        addEventListener('mouseup', OnMouseUp, false); // "windows": Fire this event even if the mouse is outside the canvas <----------- Problem: It fires with all mouseups (buttons,slider,...) and before the button click and slider position changes

        // Canvas has not a keydown event, so:
        addEventListener('keydown', OnKeyDown, false);
        addEventListener('keyup', OnKeyUp, false);
        addEventListener('keypress', OnKeyDown, false);
    };

	$scope.OnInit();

    if ($rootScope.tfa != undefined) {
        $scope.viewer.files[vcte.FileType.TFA].file_name      = $rootScope.tfa;
        $scope.viewer.files[vcte.FileType.GFF].file_name      = $rootScope.gff;
        $scope.viewer.files[vcte.FileType.WEIGHTS].file_name  = $rootScope.weight;
        $scope.viewer.files[vcte.FileType.STATS].file_name    = $rootScope.stats;
        viewer.LoadFiles($scope.viewer, true);
    }
});




// http://localhost:3001/#/load/slashdevelopslashexamplesslashAdaptNet_Variabilityslashoutput.tfa.gz/slashdevelopslashexamplesslashAdaptNet_Variabilityslashstatistics.txt/slashdevelopslashexamplesslashAdaptNet_Variabilityslashdata_annotation.gtf/slashdevelopslashexamplesslashAdaptNet_Variabilityslashpesos.txt



