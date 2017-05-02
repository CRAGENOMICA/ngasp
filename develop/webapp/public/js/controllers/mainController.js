/*
 * ngaSP: the computational solution for next generation analysis of 
 * Sequence Polymorphisms.
 * Copyright (c) 2015-2017, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez,
 * Centre for Research in Agricultural Genomics (CRAG).
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version
 * 2.1 as published by the Free Software Foundation.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 2.1 for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License version 2.1 along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */
CRAG.controller('MainController', function($scope, $rootScope, $http, $state, $cookies, $interval, socket, logs, AlertService, Fullscreen, arrays, docs) {

	$scope.init = function() {
    $rootScope.webAddress = ''; /*http://localhost:3000/*/
		$rootScope.num_users = 1;
		$rootScope.local_manager_list = [];
		$rootScope.experiments_list = [];
    $rootScope.selected_experiment_id = -1;
    $rootScope.clients_list = [];

/*
// var str = '{"command": "value", "key2": "value2"}';
var str = '{"command":"GET_EXPERIMENT_RESULT","data":{"lm_id":"24eu3","response_id":1,"cmd":null,"experiment_id":1,"result":"ngaSP 0.3.1 ngaSP 0.3.1 ngaSP 0.3.1 ngaSP 0.3.1 ngaSP 0.3.1 ngaSP 0.3.1 ngaSP\n0.3.1 ngaSP 0.3.1 ngaSP 0.3.1  ngaSP 0.3.1"}}';


var jsonObj = JSON.parse(str);
logs.log(jsonObj.command);
*/

/*
var values = {"dm":[{"name":"$idum","type":"int64","value":"-12345"},{"name":"$output","type":"int","value":"0"},{"name":"$output_file","type":"string","value":""},{"name":"$precision","type":"int","value":"2"},{"name":"$randomize_value","type":"double","value":"0"},{"name":"$seed","type":"int64","value":"12345"},{"name":"$table_col_width","type":"int","value":"4"}]};
*/


		$rootScope.alerts = []; // { type: '', msg: '' }
        

    // =========================================================================
    // COOKIES
    // =========================================================================

    var cookie_menu_visible = $cookies.get('menu_open');
    if (cookie_menu_visible == null) {
        cookie_menu_visible = true;
    }
    $scope.menu_visible = (cookie_menu_visible=="true");


    $rootScope.theme_id_selected = $cookies.get('theme');
    if ($rootScope.theme_id_selected == null) {
        $rootScope.theme_id_selected = 0; // <-- By default select this theme
    }
    $scope.OnChangeTheme($rootScope.theme_id_selected);


    $rootScope.selected_case_id = $cookies.get('selected_case_id');
    $rootScope.selected_case_title = $cookies.get('selected_case_title');

    // =========================================================================
    // CREATE DOCUMENTATION
    // =========================================================================
    $rootScope.CreateURSDocumentation();
	};

    $scope.stylesheets = [
        { id: 0, name: 'CRAG', href: 'theme_crag' },
        { id: 1, name: 'Modern', href: 'theme_modern' },
        { id: 2, name: 'Dark', href: 'theme_dark' }
    ]; 



    $scope.OnChangeTheme = function(id) {
        $rootScope.theme_id_selected = id;
        document.body.className = arrays.FindArrayElementById($scope.stylesheets, id).href;
        $cookies.put('theme', id);
    };

  $rootScope.OpenSequenceDiagram = function(selected_case_id, selected_case_title) {
    $rootScope.selected_case_id = selected_case_id;
    $rootScope.selected_case_title = selected_case_title;
    $cookies.put('selected_case_id', selected_case_id);
    $cookies.put('selected_case_title', selected_case_title);
    $state.go('system_diagrams');
  };

  $rootScope.OpenDocumentation = function(document_id) {
    if (document_id == 'CDE-CAE-083') {
      $state.go('calculation_development');
    } else {
      if (document_id == 'BUS-WMF-070') {
        $state.go('mstatspop_ngasp');
      } else {
        alert('No documentation for this item, yet.');
      }
    }
  };

	$scope.OnShowHideMenu = function() {
		$scope.menu_visible = !$scope.menu_visible;
        $cookies.put('menu_open', $scope.menu_visible);
	};

  /* If you are looking for more icons: http://glyphicons.com/ */
	$scope.contents = [
		{ id: 1,	name: 'ngaSP',        parents: [], 	  selected: false,  has_children: false, is_open: false, icon: 'glyphicon-home',	url: 'home' },
/*		{ id: 104,name: 'Commands',     parents: [],    selected: false, has_children: true, is_open: true, icon: 'glyphicon-indent-left',	url: 'commands' },
		{ id: 105,name: 'mstatspop',    parents: [104], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 102,name: 'How to use',   parents: [], 	  selected: false, has_children: true, is_open: true, icon: 'glyphicon-question-sign',	url: 'help' },
		{ id: 103,name: 'Pipeline',     parents: [102], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'pipeline' },
		{ id: 150,name: 'Examples',     parents: [102], selected: false, has_children: false, is_open: false, icon: 'glyphicon-paperclip',	url: 'examples' },
		{ id: 160,name: 'Downloads',    parents: [], 	  selected: false, has_children: false, is_open: false, icon: 'glyphicon-download-alt',	url: 'downloads' },
*/

/*
		{ id: 110,name: 'Calculations', parents: [],    selected: false, has_children: true, is_open: true, icon: 'glyphicon-indent-left',	url: 'commands' },
		{ id: 111, name: 'optimal-tests',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 112, name: 'r2',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 113, name: 'r2p',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 114, name: 'freq-stats',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 115, name: 'file-stats',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 116, name: 'mismatch',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 117, name: 'sxsfss',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 118, name: 'joint-freq-dist',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 119, name: 'piwpiafst',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 120, name: 'hwhafsth',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 121, name: 'fs',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 122, name: 'permute',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 123, name: 'dna_matrix-to_matrix-pol',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 124, name: 'fasta-to-dna_matrix',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 125, name: 'fasta-to-tfasta',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 126, name: 'create-tfa',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 127, name: 'open-fasta-file',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 128, name: 'open-tfasta-file',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 129, name: 'gff',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 130, name: 'mstatspop-open-fasta',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 131, name: 'mstatspop-open-ms',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 132, name: 'spectrum-file',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 133, name: 'mask-file-ms',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 134, name: 'effec-nuc-tcga-freqs',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 135, name: 'calc-x',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 136, name: 'calc-y',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 137, name: 'calc-z',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 138, name: 'lengthamng',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 139, name: 'array-ope-x',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 140, name: 'mstatspop-output',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 141, name: 'array-sum-all',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 142, name: 'duplicate-populations',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 143, name: 'randomize',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 144, name: 'gc-content',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 145, name: 'open-effect-sizes-file',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 146, name: 'open-coordinates-file',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 147, name: 'open-weight-positions-file',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
		{ id: 148, name: 'execute',    parents: [110], selected: false, has_children: false, is_open: false, icon: 'glyphicons-question-sign',	url: 'mstatspop' },
*/

		{ id: 2,	name: 'Administration', 	    parents: [], 	  selected: false, has_children: true,  is_open: true, icon: 'glyphicon-cog',	url: null },
		{ id: 3,	name: 'Dashboard', 			      parents: [2], 	selected: false, has_children: false, is_open: false, icon: '',	url: 'admin_dashboard' },
		{ id: 4,	name: 'Network', 			        parents: [2], 	selected: false, has_children: false, is_open: false, icon: '',	url: 'network' },
		//{ id: 5,	name: 'Experiments', 		      parents: [2], 	selected: false, has_children: false, is_open: false, icon: '',	url: 'experiments' },

		{ id: 7,	name: 'Documents',			      parents: [2], 	selected: false, has_children: true,  is_open: true, icon: 'glyphicon-file',	url: null },
/*		{ id: 15,	name: 'URS & FRS',            parents: [2,7],	selected: false, has_children: false, is_open: false, icon: '',	url: 'URS_FRS' },
		{ id: 16,	name: 'UC & TM',	parents: [2,7],	selected: false, has_children: false, is_open: false, icon: '',	url: 'traceability_matrix' },
*/
		{ id: 9,	name: "Use Cases (Events' Flow)",      parents: [2,7],	selected: false, has_children: false, is_open: false, icon: '',	url: 'system_diagrams' },

		{ id: 17,	name: "Calculation Development",      parents: [2,7],	selected: false, has_children: false, is_open: false, icon: '',	url: 'calculation_development' },
//		{ id: 8,	name: 'Components',			      parents: [2,7],	selected: false, has_children: false, is_open: false, icon: '',	url: 'components_diagram' },
		{ id: 12,	name: 'Pipeline Development', parents: [], 	  selected: false, has_children: true,  is_open: true, icon: 'glyphicon-pencil',	url: '' },
		{ id: 13,	name: 'Pipeline Editor', 	    parents: [12], 	selected: false, has_children: false, is_open: false, icon: '',	url: 'pipeline_editor' },
		{ id: 14,	name: 'Experiment Designer',  parents: [], 	  selected: false, has_children: true,  is_open: true, icon: 'glyphicon-star',	url: '' },
		{ id: 18, name: 'Experiment Editor',    parents: [14], 	selected: true, has_children: false, is_open: false, icon: '',	url: 'experiment_editor' },

	];



	function GetMenuOption(menu_id) {
		var option = null;

		for (var i = 0; ((i < $scope.contents.length) && (option == null)); i++) {
			if ($scope.contents[i].id == menu_id) {
				option = $scope.contents[i];
			}
		}

		return option;
	};

    $scope.OnOpenHome = function() {
        $state.go('home');
    };

	$scope.OnMenuSelectedItem = function(menu_id) {
		/* Unselect all */
		for (var i = 0; i < $scope.contents.length; i++) {
			$scope.contents[i].selected = false;
		}

		var option = GetMenuOption(menu_id);

		/* Allways select the item */
		option.selected = true;
		
		if (option.has_children == true) {
			/* Open close the menú item if it has children */
			option.is_open = !option.is_open;

			if (option.is_open == false) {
				/* close all options that have the parent menu_id */
				for (var i = 0; i < $scope.contents.length; i++) {
					var close = false;
					for (var j = 0; j < $scope.contents[i].parents.length; j++) {
						if ($scope.contents[i].parents[j] == menu_id) {
							close = true;
						} else {
							if (close) {
								var parent = GetMenuOption($scope.contents[i].parents[j]);
								parent.is_open = false;
							}
						}
					}
				}
			}
		} else {
			/* Open the destination page */
			/* document.body.style.backgroundColor = "#edecec"; */

      /* Uncomment this line if you want to hide the menu automatically*/
      /*$scope.OnShowHideMenu();*/

      $rootScope.selected_case = null;
			$state.go(option.url);
		}
	};

	$scope.IsMenuOpen = function(menu_id) {
		var ret = 'NO_CHILDREN';

		var option = GetMenuOption(menu_id);
		if (option.has_children == true) {
			ret = option.is_open;
		}

		return ret;
	};

	$scope.IsMenuOptionSelected = function(menu_id) {
		return GetMenuOption(menu_id).selected;
	};


	/* It returns the state of the Menu: visible or hidden */
	$scope.ShowMenu = function() {
		return $scope.menu_visible;
	};


	// ========================================================================
	// ALERTS
	// ========================================================================

	$rootScope.AddAlert = function(message) {
		$rootScope.alerts.push({msg: message});
	};

	$rootScope.CloseAlert = function(index) {
		$rootScope.alerts.splice(index, 1);
	};


	// ========================================================================
	// LOADING
	// ========================================================================

	$rootScope.loadings = 0;  // Number of processes loading

	$rootScope.ShowLoading = function() {
		return ($rootScope.loadings > 0);
	};

	$rootScope.ActivateLoading = function() {
		$rootScope.loadings++;
	};

	$rootScope.StopLoading = function() {
		$rootScope.loadings--;
		if ($rootScope.loadings < 0 ) {
			$rootScope.loadings = 0;
		}
	};

	// ========================================================================
	// COMUNICATIONS
	// ========================================================================

    $rootScope.Http = function(send, callbackOk, callbackCancel, showLoading) {
      showLoading = ((showLoading == undefined) ||
                     (showLoading == null) ||
                     (showLoading == true));

      if (showLoading) {
  	    $rootScope.ActivateLoading();
      }

    	logs.logDataSent(send);
	    $http(send).then(function() {
        if (showLoading) {
  		    $rootScope.StopLoading();
        }
        var data = null;
        if (arguments.length > 0) {
            data = arguments[0];
        }
        logs.logDataReceivedOk(data);
		    callbackOk(data);
	    },
      function() {
        if (showLoading) {
  		    $rootScope.StopLoading();
        }
        var data = null;
        if (arguments.length > 0) {
            data = arguments[0];
        }
        logs.logDataReceivedError(data);
        callbackCancel(data);
	    });
    };



	// ========================================================================
	// COMMON MESSAGES TO THE CENTRAL MANAGER
    // ACCESSIBLE FOR EVERY CONTROLLER
	// ========================================================================

	// Naming conventions: http://www.restapitutorial.com/lessons/restfulresourcenaming.html
	// POST		/experiments		Create new experiment
	// GET  	/experiments/id		Read the experiment id
	// GET  	/experiments		Read all experiments
	// PUT  	/experiments/id		Update experiment
	// DELETE 	/experiments/id		Delete the experiment id
	// Use plurals

	$rootScope.OnRefreshLocalManagersList = function() {
		$rootScope.Http({
		        method: 'GET',
		        url: $rootScope.webAddress + 'localmanagers',
				headers: { 'Content-Type': 'application/json' },
		        data: {},
	    },
        function(message) {
			$rootScope.local_manager_list = message.data.data;
		},
		function(message) {
		});
	};

  $rootScope.timer_refresh_experiments = undefined;

	$rootScope.OnRefreshExperimentsList = function() {
		$rootScope.Http({
		        method: 'GET',
		        url: $rootScope.webAddress + 'experiments',
				headers: { 'Content-Type': 'application/json' },
		        data: {},
	    },
		function(message) {
			$rootScope.experiments_list = message.data.data;

      // If there is no experiment selected and the experiment list is not empty then the first experiment is the selected one:
      if (($rootScope.selected_experiment_id == -1) && ($rootScope.experiments_list.length > 0)) {
        $rootScope.selected_experiment_id = $rootScope.experiments_list[0].experiment_id;
      }

/*
      var activate_timer = false;

      if ($rootScope.experiments_list.length > 0) {
        for (var i = 0; ((i < $rootScope.experiments_list.length) && (activate_timer == false)); i++) {
          activate_timer = ($rootScope.experiments_list[i].status == "OPEN");
        }
      } else {
        activate_timer = false;
      }

      if (activate_timer) {
        if ($rootScope.timer_refresh_experiments == undefined) {
          // the timer is no activated and it must be activated
          $rootScope.timer_refresh_experiments = $interval(function() { $rootScope.OnRefreshExperimentsList(); }, 1000);
        } else {
          // the timer is already activated and it must remain activated
          // So, do nothing here
        }
      } else {
        if ($rootScope.timer_refresh_experiments == undefined) {
          // the timer is no activated and it must remain inactivated
          // So, do nothing here
        } else {
          // stop the timer
          $interval.cancel($rootScope.timer_refresh_experiments);
          $rootScope.timer_refresh_experiments = undefined;
        }
      }
*/
		},
		function(message) {
		},
    false); // <-- 
	};

	$rootScope.OnRefreshClientsList = function() {

        logs.log("-------------OnRefreshClientsList-----------------");

		$rootScope.Http({
		        method: 'GET',
		        url: $rootScope.webAddress + 'clients',
				headers: { 'Content-Type': 'application/json' },
		        data: {},
	    },
		function(message) {
			$rootScope.clients_list = message.data.data;
		},
		function(message) {
		});
	};

	// ========================================================================
	// MESSAGES FROM THE CENTRAL MANAGER
	// ========================================================================

	socket.on('REFRESH_REQUIRED', function (message) {
    if((message != null) && (message.data != null) && (message.data.data != "")) {
      logs.logDataReceivedOk(message);

	    if ((loc = message.data.indexOf("RUN_END=")) != -1) {
        exp_id = message.data.substr(loc + 8);  // 8 is the length of "RUN_END="
        // exp_id = message.data.substr(0, message.data.indexOf("]"));

        //$rootScope.OnSelectExperiment(exp_id, null, null);
		    //$rootScope.OnGetOutput();
	    }

      if (message.data.indexOf("LM_LIST") != -1) {
	      $rootScope.OnRefreshLocalManagersList();
      }
	
      if (message.data.indexOf("EXPERIMENTS_LIST") != -1) {
	      $rootScope.OnRefreshExperimentsList();
      }

      if (message.data.indexOf("CLIENTS_LIST") != -1) {
	      $rootScope.OnRefreshClientsList();
      }

      if (message.data.indexOf("EXPERIMENT_OUTPUT") != -1) {
              AlertService.info("Experiment output available.");
	      // $scope.OnGetOutput();
      }
    }
	});

    socket.on('connect', function() {
      console.log('Direct socket connection stablished with Central Manager');
    });


    $scope.OnFullScreen = function() {
        if (Fullscreen.isEnabled())
            Fullscreen.cancel();
        else
            Fullscreen.all();
    };


	// ========================================================================
	// CREATE DOCUMENTATION
	// ========================================================================

  $rootScope.CreateURSDocumentation = function() {
    if ($rootScope.URS_Ready == null) {
      $rootScope.definitions = [];

      docs.AddToDictionary("ngasp", "Next Generation Analysis Sequence Polimorphism.");
      docs.AddToDictionary("End User", "The system user who will analyze his / her data using already available pipelines.");
      docs.AddToDictionary("Pipeline Developer", "The system user who who will develop new analysis pipelines combining the existing available calculations and other pipelines.");
      docs.AddToDictionary("Calculation Developer", "The Calculation Developer will use the system to create new calculations.");
      docs.AddToDictionary("Software Engineer", "The Software Engineer will be the developer that will create the system.");
      docs.AddToDictionary("Data Manager", "The Data Manager is who controls all the data of an experiment.");
      docs.AddToDictionary("Local Manager", "The Local Manager is the backend instance that controlls all the experiments of one machine.");
      docs.AddToDictionary("Central Manager", "The Central Manager is the NodeJs application that controlls all the Local Managers. One Central manager has multiple local managers.");
      docs.AddToDictionary("pipeline", "It is a workflow of calculations and other pipelines.");
      docs.AddToDictionary("experiment", "It is an instancied pipeline.");
      docs.AddToDictionary("session", "It is a group of experiments.");
      docs.AddToDictionary("Master", "It is the process who distributes calculations in parallel over worker processes. One Master has multiple workers.");
      docs.AddToDictionary("Worker", "It is the process that executes calculations sequentially.");
      docs.AddToDictionary("client", "It is the web browser of a user.");
      docs.AddToDictionary("process", "It is an instance of the ngasp application. It can be a Master MPI process or a Worker MPI process.");
      docs.AddToDictionary("DM", ">Data Manager");
      docs.AddToDictionary("LM", ">Local Manager");
      docs.AddToDictionary("CM", ">Central Manager");

      $rootScope.user_requirements = [];

      /*
      // =========================================================================
      mod = docs.AddModule($scope.user_requirements, "Team Work Platform");
      // =========================================================================
      cat = docs.AddCategory(mod, "Development Requirements");
      sec = docs.AddSection(cat, "Source Code");
      docs.AddRequirement(sec, 1, "The source code must be written using verifiable coding style guides.", "M", false);
      docs.AddRequirement(sec, 2, "The source code must be commented and annotated for generating documentation.", "M", false);
      docs.AddRequirement(sec, 3, "The source code must be object-oriented.", "M", true);
      */

/*
Obsolete

      docs.AddRequirement(sec, 4, "The system must be able to accept CM request for execute commands on an specific backend.", "M", true, "Obsolete due to Master-Worker Model");
      docs.AddRequirement(sec, 5, "The system must be able to accept CM request for getting all data manager variables of an specific backend.", "M", true, "Obsolete due to Master-Worker Model");
      docs.AddRequirement(sec, 6, "The system must be able to accept CM request for getting an specific backend output.", "M", true, "Obsolete due to Master-Worker Model");
      docs.AddRequirement(sec, 7, "The system must be able to accept CM request for cleaning an specific backend output.", "M", true, "Obsolete due to Master-Worker Model");
      docs.AddRequirement(sec, 8, "The system must be able to accept CM request for getting an specific current backend state.", "M", true, "Obsolete due to Master-Worker Model");
      docs.AddRequirement(sec, 9, "The Local Manager state must be: OK", "M", true, "Obsolete due to Master-Worker Model");
      docs.AddRequirement(sec, 10, "The system must be able to open new instances of the backend for new backend.", "M", true, "Obsolete due to Master-Worker Model");
      docs.AddRequirement(sec, 11, "The system must be able to accept CM request for closing an specific backend.", "M", true, "Obsolete due to Master-Worker Model");
      docs.AddRequirement(sec, 12, "LM must communicate with its backend via \"named pipes\".", "M", true, "Obsolete due to Master-Worker Model");
      docs.AddRequirement(sec, 13, "The system must be able to accept CM request for getting the calculations list.", "M", true, "Obsolete due to Master-Worker Model");
      docs.AddRequirement(sec, 14, "The system must be able to accept CM request for getting the data types list.", "M", true, "Obsolete due to Master-Worker Model");
      docs.AddRequirement(sec, 15, "The LM must check automatically the state of all its backends.", "M", true, "Obsolete due to Master-Worker Model");

      docs.AddRequirement(sec, 1, "The system must be able to accept and execute LM remote commands while an backend is being running.", "M", true, "Obsolete due to Master-Worker Model");
      docs.AddRequirement(sec, 2, "The system must be able to answer a LM request for getting all data manager variables.", "M", true, "Obsolete due to Master-Worker Model");
      docs.AddRequirement(sec, 3, "The system must be able to answer a LM request for saving the current backend output to a file (to be able to send current results to the interface).", "M", true, "Obsolete due to Master-Worker Model");
      docs.AddRequirement(sec, 4, "The system must be able to answer a LM request for cleaning the backend output file.", "M", true, "Obsolete due to Master-Worker Model");
      docs.AddRequirement(sec, 5, "The system must be able to answer a LM request for getting the current backend state.", "M", true, "Obsolete due to Master-Worker Model");
      docs.AddRequirement(sec, 6, "The backend state must be: OPEN / WORKING.", "M", true, "Obsolete due to Master-Worker Model");
      docs.AddRequirement(sec, 7, "The system must be able to answer a LM request for running an specific command.", "M", true, "Obsolete due to Master-Worker Model");
      docs.AddRequirement(sec, 8, "The system must be able to close itself due to a LM request for it.", "M", true, "Obsolete due to Master-Worker Model");

      sec = docs.AddSection(cat, "Backend Runner");
      docs.AddRequirement(sec, 1, "The backend must be able to execute instructions from a queue.", "M", true);


      // =========================================================================
      mod = docs.AddModule($scope.user_requirements, "Central Manager");
      // =========================================================================
      cat = docs.AddCategory(mod, "General");
      sec = docs.AddSection(cat, "Requests from Clients");
      docs.AddRequirement(sec, 1, "The CM must be able answer requests for creating new experiments.", "M", true);
      docs.AddRequirement(sec, 2, "The CM must be able answer requests for executing an experiment command.", "M", true);
      docs.AddRequirement(sec, 3, "The CM must be able answer requests for getting the experiment output.", "M", true);
      docs.AddRequirement(sec, 4, "The CM must be able answer requests for cleaning the experiment output.", "M", true);
      docs.AddRequirement(sec, 5, "The CM must be able answer requests for closing the application server.", "M", true);
      docs.AddRequirement(sec, 6, "The CM must be able answer requests for getting the local managers list.", "M", true);
      docs.AddRequirement(sec, 7, "The CM must be able answer requests for getting the experiments list.", "M", true);
      docs.AddRequirement(sec, 8, "The CM must be able answer requests for getting the clients list.", "M", true);
      docs.AddRequirement(sec, 9, "The CM must be able answer requests for getting the calculations list.", "M", true);
      docs.AddRequirement(sec, 10, "The CM must be able answer requests for getting the data types list.", "M", true);
      docs.AddRequirement(sec, 11, "The CM must be able answer requests for getting all data manager variables of an experiment.", "M", true);

      sec = docs.AddSection(cat, "Connections");
      docs.AddRequirement(sec, 1, "The CM must be able to enroll Local Managers.", "M", true);
      docs.AddRequirement(sec, 2, "The CM must be able to disenroll Local Managers.", "O", false);
      docs.AddRequirement(sec, 3, "The CM must check automatically the state of all its Local Managers.", "M", true);
      docs.AddRequirement(sec, 4, "The CM must be able to answer client requests using the same established connection.", "M", true);
      docs.AddRequirement(sec, 5, "The CM must be able to send specific messages to clients.", "M", true);
      docs.AddRequirement(sec, 6, "The CM must be able to send messages to all its clients at the same time.", "M", true);

*/

/*
TBD
      docs.AddRequirement(sec, 11, "The backend must have a command for manage the list of executed instructions.", "O", true);



      docs.AddRequirement(sec, 24, "The backend must have a command for set the application in TCP mode for receiving commands via TCP protocol.", "M", true);

      docs.AddRequirement(sec, 1, "All command line executable commands must be stored in the Command Manager.", "M", true);
      docs.AddRequirement(sec, 20, "All executed commands must be logged in a log file.", "M", true);

     docs.AddRequirement(sec, 18, "The backend must have a command for showing the log file content.", "M", true);

The Command Manager will contain a list of instanced commands (one of each type).", "M", true);

      docs.AddRequirement(sec, 2, "The Instructions Controller will be able to obtain instructions from the standard input.", "M", true);
      docs.AddRequirement(sec, 3, "The Instructions Controller will be able to obtain instructions from a named pipe (in \"Local Manager\" & \"Backend Listener\" execution modes).", "M", true);


      cat = docs.AddCategory(mod, "Testing");
      sec = docs.AddSection(cat, "Test using mstatspop");
      docs.AddRequirement(sec, 1, "The backend output for the mstatspop command must be compared with the mstatspop output for different inputs.", "M", true);
      docs.AddRequirement(sec, 2, "The baskend must be tested with Javier inputs files.", "M", false);
      docs.AddRequirement(sec, 3, "The system must be tested using valgrind.", "M", false);

      cat = docs.AddCategory(mod, "Technology");
      sec = docs.AddSection(cat, "WebApp");
      docs.AddRequirement(sec, 1, "The interface must be developed using Java.", "M", false, "Web interfaces offers a quickest developing and more spectacular charts.");
      docs.AddRequirement(sec, 2, "The interface must be developed using: HMTL5, Javascript, AngularJs and NodeJs.", "M", true);

      docs.AddRequirement(sec, 1, "The administrator must be able to create new experiments.", "O", true);
      docs.AddRequirement(sec, 2, "The administrator must be able to run specific commands on experiments.", "O", true);
      docs.AddRequirement(sec, 3, "The administrator must be able to close experiments.", "O", true);
      docs.AddRequirement(sec, 4, "The administrator must be able to close the system.", "O", true);

      cat = docs.AddCategory(mod, "Git");
      cat = docs.AddCategory(mod, "Docker");
      cat = docs.AddCategory(mod, "Vagrant");

*/

      // =========================================================================
      mod = docs.AddModule($scope.user_requirements, "Backend");
      // =========================================================================

      cat = docs.AddCategory(mod, "Command Line Execution Mode");
      // ********************************************************

      sec = docs.AddSection(cat, "Command Line");
      docs.AddRequirement(sec, 1, "The backend must be able to be executed via command line.", "M", true);
      docs.AddRequirement(sec, 2, "The command line instructions syntax must be [GOS]*[CMD]?[COS]*", "M", true);
      docs.AddRequirement(sec, 3, "The backend must have a command for executing the mstatspop calculation.", "M", true);
      docs.AddRequirement(sec, 4, "The backend must have a command for running commands from an external file.", "M", true);
      docs.AddRequirement(sec, 5, "The backend must have a command for showing the application version number.", "M", true);
      docs.AddRequirement(sec, 6, "The backend must have a command for increasing / decreasing the verbose level of logs.", "M", true);
      docs.AddRequirement(sec, 7, "The backend must have a command for showing the application help.", "M", true);
      docs.AddRequirement(sec, 8, "The backend must have a command for stopping the application.", "M", true);
      docs.AddRequirement(sec, 9, "The backend must have a command for enabling / disabling the dry-run option.", "M", true);
      docs.AddRequirement(sec, 10, "The backend must have a command for showing the contents of the data manager.", "M", true);
      docs.AddRequirement(sec, 11, "The backend must have a command for creating data manager variables.", "M", true);
      docs.AddRequirement(sec, 12, "The backend must have a command for allocating memory for data manager variables.", "O", true);
      docs.AddRequirement(sec, 13, "The backend must have a command for assigning values to data manager variables.", "M", true);
      docs.AddRequirement(sec, 14, "The backend must have a command for deleting data manager variables.", "M", true);
      docs.AddRequirement(sec, 15, "The backend must have a command for printing data manager variables.", "M", true);
      docs.AddRequirement(sec, 16, "The backend must have a command for creating a new instance of a calculation.", "M", true);
      docs.AddRequirement(sec, 17, "The backend must have a command for running a calculation.", "M", true);
      docs.AddRequirement(sec, 18, "The backend must have a command for defining a constant and its value.", "O", true);
      docs.AddRequirement(sec, 19, "The backend must have a command for setting a loop.", "M", true);
      docs.AddRequirement(sec, 20, "The backend must have a command for setting a conditional statement.", "M", true);
      docs.AddRequirement(sec, 21, "The backend must have a command for turning the application into the interactive shell execution mode.", "M", true);
      docs.AddRequirement(sec, 22, "The backend must have a command for turning the application out of the interactive shell execution mode.", "M", true);
 
      sec = docs.AddSection(cat, "The Manager");
      docs.AddRequirement(sec, 1, "All main components must be managed by one manager.", "M", true);
      docs.AddRequirement(sec, 2, "The Manager must have the Command Manager.", "M", true);
      docs.AddRequirement(sec, 3, "The Manager must have the Options Container.", "M", true);
      docs.AddRequirement(sec, 4, "The Manager must have the Instructions Controller.", "M", true);
      docs.AddRequirement(sec, 5, "The Manager must have the Calculations Factory.", "M", true);
      docs.AddRequirement(sec, 6, "The Manager must have the Calculations Manager.", "M", true);
      docs.AddRequirement(sec, 7, "The Manager must have the Data Factory.", "M", true);
      docs.AddRequirement(sec, 8, "The Manager must have the Data Manager.", "M", true);
      docs.AddRequirement(sec, 9, "The Manager must have the Logger.", "M", true);
      docs.AddRequirement(sec, 10, "The Manager must have the Strings table.", "M", true);
      docs.AddRequirement(sec, 11, "The Manager will have the loop for executing stdin commands.", "M", true);
      docs.AddRequirement(sec, 12, "The Manager will set the user desired execution mode.", "M", true);

      sec = docs.AddSection(cat, "The Commands Manager");
      docs.AddRequirement(sec, 1, "The Command Manager will contain a list of instanced commands (one of each type).", "M", true);

      sec = docs.AddSection(cat, "Options Container");
      docs.AddRequirement(sec, 1, "The Options Container will contain the list of command line general options.", "M", true);

      sec = docs.AddSection(cat, "Instructions Controller");
      docs.AddRequirement(sec, 1, "The Instructions Controller will contain a queue of commands to execute.", "M", true);
      docs.AddRequirement(sec, 2, "The Instructions Controller will execute general options before any command.", "M", true);
      docs.AddRequirement(sec, 3, "The Instructions Controller will be able to obtain instructions from the standard input.", "M", true);
      docs.AddRequirement(sec, 4, "The Instructions Controller will be able to obtain instructions from a file.", "M", true);
      docs.AddRequirement(sec, 5, "The Instructions Controller will be able to obtain instructions from a pipe.", "M", false, "Workers will use Open MPI instead.");
      docs.AddRequirement(sec, 6, "The Instructions Controller will be able to obtain instructions from MPI messages.", "M", true);
      docs.AddRequirement(sec, 7, "The Instructions Controller will have a history of executed instructions.", "M", true);
      docs.AddRequirement(sec, 8, "The history must allow to remove all the list of executed commands.", "M", true);
      docs.AddRequirement(sec, 9, "The history must allow to execute one of its executed commands.", "M", true);
      docs.AddRequirement(sec, 10, "The history must show all the list of executed commands when it is required.", "M", true);


      sec = docs.AddSection(cat, "Calculations Factory");
      docs.AddRequirement(sec, 1, "The calculations factory will contain a list of calculations (one of each type).", "M", true);

      sec = docs.AddSection(cat, "Calculations Manager");
      docs.AddRequirement(sec, 1, "The calculations manager will contain a list of instanced calculations.", "M", true);
      docs.AddRequirement(sec, 2, "The calculations manager must be upgradable with unlimited new calculations.", "M", true);

      sec = docs.AddSection(cat, "Calculations");
      docs.AddRequirement(sec, 1, "Calculations must be written in C++.", "M", true);
      docs.AddRequirement(sec, 2, "Calculations must implement the function \"Prepare()\".", "M", true);
      docs.AddRequirement(sec, 3, "Calculations must implement the function \"Calculate()\".", "M", true);
      docs.AddRequirement(sec, 4, "Calculations must implement the function \"Finalize()\".", "M", true);
      docs.AddRequirement(sec, 5, "Calculations must define their inputs and outputs.", "M", true);
      docs.AddRequirement(sec, 6, "Calculations must ask for input and output variables to its Data Manager.", "M", true);
      docs.AddRequirement(sec, 7, "Calculations could have more than one implementation.", "E", true);
      docs.AddRequirement(sec, 8, "The default calculation inplementation will be serial.", "M", true);
      docs.AddRequirement(sec, 9, "All mstatspop main functions must be converted into ngasp calculations.", "M", true);

      sec = docs.AddSection(cat, "Data Factory");
      docs.AddRequirement(sec, 1, "The Data Factory will contain a list of datas (one of each type).", "M", true);

      sec = docs.AddSection(cat, "Data Manager");
      docs.AddRequirement(sec, 1, "The Data Manager will contain a list of instanced variables.", "M", true);
      docs.AddRequirement(sec, 2, "The Data Manager will be able accept requests for creating, getting and removing variables.", "M", true);
      docs.AddRequirement(sec, 3, "Data Managers will be able to synchronize their data between them.", "M", false);
      docs.AddRequirement(sec, 4, "Data Managers will be able to save their state to file.", "M", true);
      docs.AddRequirement(sec, 5, "Data Managers will be able to load their state from file.", "M", true);

      sec = docs.AddSection(cat, "Logger");
      docs.AddRequirement(sec, 1, "All user messages must be coordinated by one Logger.", "M", true);
      docs.AddRequirement(sec, 2, "Log message types must be: Info / Debug / Error / Warning.", "M", true);
      docs.AddRequirement(sec, 3, "Log modes must be: Debug Mode / Normal Mode / Silent Mode.", "M", true);
      docs.AddRequirement(sec, 4, "The \"Silent Mode\" must show only these message types to the user: Warning / Error.", "M", true);
      docs.AddRequirement(sec, 5, "The \"Normal Mode\" must show only these message types to the user: Info / Warning / Error.", "M", true);
      docs.AddRequirement(sec, 6, "The \"Debug Mode\" must show only these message types to the user: Info / Debug / Warning / Error.", "M", true);
      docs.AddRequirement(sec, 7, "The \"Silent Mode\" must store on the log file only these messages types: Warning / Error.", "M", true);
      docs.AddRequirement(sec, 8, "The \"Normal Mode\" must store on the log file only these messages types: Warning / Error.", "M", true);
      docs.AddRequirement(sec, 9, "The \"Debug Mode\" must store on the log file only these messages types: Info / Debug / Warning / Error.", "M", true);
      docs.AddRequirement(sec, 10, "The logger must log all command's activity.", "M", true);
      docs.AddRequirement(sec, 11, "The logger must log all calculations's activity.", "M", true);
      docs.AddRequirement(sec, 12, "The logger must allow to remove all its messages.", "M", true);
      docs.AddRequirement(sec, 13, "The logger must show all its messages when it is required.", "M", true);


      sec = docs.AddSection(cat, "String Table");
      docs.AddRequirement(sec, 1, "All the backend messages shown to the user will be written in the string table.", "M", true);
      docs.AddRequirement(sec, 2, "All command descriptions will be written in the string table.", "M", true);
      docs.AddRequirement(sec, 3, "All calculation descriptions will be written in the string table.", "M", true);

      cat = docs.AddCategory(mod, "Interactive Shell Execution Mode");
      // *********************************************************

      sec = docs.AddSection(cat, "Standard Input");
      docs.AddRequirement(sec, 1, "In an interactive shell execution mode, the application must accept commands from the standard input.", "M", true);


      cat = docs.AddCategory(mod, "Local Manager Execution Mode");
      // *********************************************************

      sec = docs.AddSection(cat, "General");
      docs.AddRequirement(sec, 1, "The system must have at least one local manager as a Master MPI process.", "M", false);


      docs.AddRequirement(sec, 2, "The local manager must have one data manager.", "M", false);


      docs.AddRequirement(sec, 3, "The local manager must create at least one MPI Worker process.", "M", false);
      docs.AddRequirement(sec, 4, "The local manager must listen incoming instructions from the central manager all the time.", "M", false);
      docs.AddRequirement(sec, 5, "The local manager must execute received instructions from a queue.", "M", false);
      docs.AddRequirement(sec, 6, "The local manager will select the worker that will run an step.", "M", false);
      docs.AddRequirement(sec, 7, "The local manager will send messages to the worker identifying: calc_id to be executed, its inputs and its outputs.", "M", false);
      docs.AddRequirement(sec, 8, "The local manager will own the scattering and gathering data process.", "E", false);
      docs.AddRequirement(sec, 9, "The local manager will start all its workers at its start up.", "M", false);
      docs.AddRequirement(sec, 10, "The local manager will present itsself to the central manager.", "M", false);
      docs.AddRequirement(sec, 11, "The local manager will distribute steps into its workers.", "M", false);

/*
"GONZ. The Local Manager will open workers using the 'system' command", "M", false);
"GONZ. The Local Manager will talk with its workers using a named pipe", "M", false);
"GONZ. The Local Manager will exchange Data Manager data using IPC shared memory", "M", false);
"GONZ. Local Managers of different machines will exchange information using MPI messages.", "M", false);

"GONZ. The scatter-gather model will depend on three things: the input variable, the type of calculation and the output variable", "M", false);
"GONZ. The scatter node will be placed between the DM input variable and the calculation's input."
"GONZ. The gather node will be placed between the calculation's output and the DM output variable."



Workflow = conjunt d'steps
Workbench = dades  + eines + localització del repo deda des
Tarea = conjunto de steps del workflow
maquina = estado de los recursos de computo disponibles
Precarga de 200 linias del fichero
Planificador debe conocer el estado de la máquina
El LM le envia el estado de la máquina al planificador
El LM se conecta al CM para abrir la conexion
  
  
Workflow = conjunt d'steps
Workbench = dades  + eines + localització del repo deda des
Tarea = conjunto de steps del workflow
maquina = estado de los recursos de computo disponibles
Precarga de 200 linias del fichero
Planificador debe conocer el estado de la máquina
El LM le envia el estado de la máquina al planificador
  
  
User puede levantar más LM
  
User
  RestFul
  
1 CM
  

1 Planificator
  
n LM
  
  named Pipe
  
n Worker / Exec / Proceso




The administrator must be able to add more nodes to the system.
The system must be able to reopen fallen nodes automatically.
  */




      cat = docs.AddCategory(mod, "Worker Execution Mode");
      // **************************************************

      sec = docs.AddSection(cat, "General");
      docs.AddRequirement(sec, 1, "The worker must have one data manager.", "M", false);
      docs.AddRequirement(sec, 2, "The worker must execute one step at a time.", "M", false);
      docs.AddRequirement(sec, 3, "The worker will communicate the step's finished state to its master: done / error message.", "M", false);
      docs.AddRequirement(sec, 4, "The worker will get the following machine information: Number of cores / Total Memory / Total Free Memory", "M", false);


      cat = docs.AddCategory(mod, "Central Manager Execution Mode");
      // ***********************************************************

      sec = docs.AddSection(cat, "General");
      docs.AddRequirement(sec, 1, "The system must have one central manager.", "M", false);
      docs.AddRequirement(sec, 2, "The central manager will select the local manager to execute an experiment.", "M", false);
      docs.AddRequirement(sec, 3, "The central manager will send the experiment id to the local manager.", "M", false);
     

      cat = docs.AddCategory(mod, "Calculations");
      // ***********************************************************

      sec = docs.AddSection(cat, "mstatspop");
      docs.AddRequirement(sec, 1, "mstatspop must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "optimal tests");
      docs.AddRequirement(sec, 1, "optimal-tests must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "r2");
      docs.AddRequirement(sec, 1, "r2 must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "r2p");
      docs.AddRequirement(sec, 1, "r2p must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "the freq stats");
      docs.AddRequirement(sec, 1, "freq stats must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "file stats");
      docs.AddRequirement(sec, 1, "file stats must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "mismatch");
      docs.AddRequirement(sec, 1, "mismatch must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "sxsfss");
      docs.AddRequirement(sec, 1, "sxsfss must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "joint freq dist");
      docs.AddRequirement(sec, 1, "joint freq dist must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "piwpiafst");
      docs.AddRequirement(sec, 1, "piwpiafst must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "hwhafsth");
      docs.AddRequirement(sec, 1, "hwhafsth must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "fs");
      docs.AddRequirement(sec, 1, "fs must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "permute");
      docs.AddRequirement(sec, 1, "permute must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "dna_matrix to matrix_pol");
      docs.AddRequirement(sec, 1, "dna_matrix to matrix_pol must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "fasta to dna_matrix");
      docs.AddRequirement(sec, 1, "fasta to dna_matrix must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "open fasta file");
      docs.AddRequirement(sec, 1, "open fasta file must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "gff");
      docs.AddRequirement(sec, 1, "gff must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "mstatspop open fasta");
      docs.AddRequirement(sec, 1, "mstatspop open fasta must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "mstatspop open ms");
      docs.AddRequirement(sec, 1, "mstatspop open ms must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "spectrum file");
      docs.AddRequirement(sec, 1, "spectrum file must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "mask file ms");
      docs.AddRequirement(sec, 1, "mask file ms must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "effec nuc tcga freqs");
      docs.AddRequirement(sec, 1, "effec nuc tcga freqs must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "calc x");
      docs.AddRequirement(sec, 1, "calc x must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "calc y");
      docs.AddRequirement(sec, 1, "calc y must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "calc z");
      docs.AddRequirement(sec, 1, "calc z must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "lengthamng");
      docs.AddRequirement(sec, 1, "lengthamng must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "array ope x");
      docs.AddRequirement(sec, 1, "array ope x must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "mstatspop output");
      docs.AddRequirement(sec, 1, "mstatspop output must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "array sum all");
      docs.AddRequirement(sec, 1, "array sum all must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "duplicate populations");
      docs.AddRequirement(sec, 1, "duplicate populations must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "randomize");
      docs.AddRequirement(sec, 1, "randomize must be converted into an ngasp calculation.", "M", true);
      sec = docs.AddSection(cat, "gc content");
      docs.AddRequirement(sec, 1, "gc content must be converted into an ngasp calculation.", "M", true);


      cat = docs.AddCategory(mod, "Data Manager");
      // *****************************************

      sec = docs.AddSection(cat, "Data Types");
      docs.AddRequirement(sec, 1, "The DM must have the minimum data types.", "M", false);
      docs.AddRequirement(sec, 2, "The DM must have all basic and compound data types required for executing mstatspop.", "M", true);

      sec = docs.AddSection(cat, "Basic Data");
      docs.AddRequirement(sec, 1, "GONZ. The DM must have the 'number' data type that will correspond to 'int64' in c++.", "M", false);
      docs.AddRequirement(sec, 2, "GONZ. The DM must have the 'string' data type that will correspond to 'std::string' in c++.", "M", false);
      docs.AddRequirement(sec, 3, "GONZ. The DM must have the 'boolean' data type that will correspond to 'bool' in c++.", "M", false);
      docs.AddRequirement(sec, 4, "GONZ. The DM must have the 'char' data type that will correspond to 'char' in c++.", "M", false);
      docs.AddRequirement(sec, 5, "GONZ. The DM must have the 'double' data type for maintaining the compatibility with mstatspop.", "M", false);
      docs.AddRequirement(sec, 6, "GONZ. The DM must have the 'float' data type for maintaining the compatibility with mstatspop.", "M", false);
      docs.AddRequirement(sec, 7, "GONZ. The DM must have the 'int' data type for maintaining the compatibility with mstatspop.", "M", false);

      sec = docs.AddSection(cat, "Compound Data");
      docs.AddRequirement(sec, 1, "The DM must be able to create arrays of each basic data types.", "M", true);
      docs.AddRequirement(sec, 2, "The DM must be able to create matrices of each basic data types.", "M", true);
      docs.AddRequirement(sec, 3, "The DM must be able to create arrays of matrices of each basic data types.", "M", true);

      sec = docs.AddSection(cat, "Assigning Values to Variables");
      docs.AddRequirement(sec, 1, "The DM must give the way to assign an scalar value to a variable (a=1).", "M", true);
      docs.AddRequirement(sec, 2, "The DM must give the way to assign a variable value to a variable (a=b).", "M", true);
      docs.AddRequirement(sec, 3, "The DM must give the way to assign value to compound data directly (vector[0], matrix[0,0], cube[0,0,0]).", "M", true);
      docs.AddRequirement(sec, 4, "The DM must give the way to assign value to compound data indirectly (vector[a], matrix[a,b], cube[a,b,c], vector[matrix[0,b]], ...).", "M", true);

      sec = docs.AddSection(cat, "Export Data");
      docs.AddRequirement(sec, 1, "All data types must be exportable to JSON format.", "M", true);


      cat = docs.AddCategory(mod, "File Formats");
      // *****************************************

      sec = docs.AddSection(cat, "ngasp");
      docs.AddRequirement(sec, 1, "ngasp format will be used for storing scripts.", "M", true);
      docs.AddRequirement(sec, 2, "ngasp format will be used for storing the data manager state.", "M", true);
      docs.AddRequirement(sec, 3, "Command syntax must be [GOS]*[CMD]?[COS]*.", "M", true);
      docs.AddRequirement(sec, 4, "The syntax must accept wrapping commands into different lines.", "M", true);
      docs.AddRequirement(sec, 5, "The syntax must accept line comments.", "M", true);
      docs.AddRequirement(sec, 6, "The syntax must accept loops.", "M", true);
      docs.AddRequirement(sec, 7, "The syntax must accept conditional sentences.", "M", true);
      docs.AddRequirement(sec, 8, "The syntax must be rewritable using a global string table.", "M", true);
      docs.AddRequirement(sec, 9, "All the mstatspop's main function must be rewritten to ngasp language.", "M", true, "All this function rewritten in ngasp language takes a lot of time to run.");

      sec = docs.AddSection(cat, "Common Working Language (CWL)");
      docs.AddRequirement(sec, 1, "CWL format will be used for storing pipelines.", "M", true);
      docs.AddRequirement(sec, 2, "CWL format will be used for storing experiments.", "M", true);
      docs.AddRequirement(sec, 3, "GONZ. The input binding of data manager variables should use url addresses.", "D", false);
      docs.AddRequirement(sec, 4, "GONZ. The method for running calculations and pipelines (run: {import}) should use a tag to differentiate them.", "D", false);



      sec = docs.AddSection(cat, "Pipeline Graphical Information (PGI)");
      docs.AddRequirement(sec, 1, "PGI format will be used for storing pipelines graphical information.", "M", true);



      // =========================================================================
      mod = docs.AddModule($scope.user_requirements, "Interface");
      // =========================================================================

      cat = docs.AddCategory(mod, "Website Sections");
      // *********************************************

      sec = docs.AddSection(cat, "Sections");
      docs.AddRequirement(sec, 1, "The interface must have an administration section.", "M", true);
      docs.AddRequirement(sec, 2, "The interface must have a pipeline development section.", "M", true);
      docs.AddRequirement(sec, 3, "The pipeline development section will have a pipeline editor.", "M", true);
      docs.AddRequirement(sec, 4, "The interface must have an experiment development section.", "M", true);
      docs.AddRequirement(sec, 5, "The experiment development section will have an experiment editor.", "M", true);

      sec = docs.AddSection(cat, "Website User Authentification");
      docs.AddRequirement(sec, 1, "The administration section will be only accessible by administrators.", "M", false);
      docs.AddRequirement(sec, 2, "The Pipeline Development section will be accessible by administrators and Pipeline Developers.", "M", false);
      docs.AddRequirement(sec, 3, "The Experiment Designer section will be accessible by administrators, Pipeline Developers and Final Users.", "M", false);

      cat = docs.AddCategory(mod, "Administration Section");
      // ***************************************************

      sec = docs.AddSection(cat, "Dashboard");
      docs.AddRequirement(sec, 1, "The dashboard must show a summary with the number of: Central Manager, Local Managers, Workers, Experiments and Users.", "D", false);
      docs.AddRequirement(sec, 2, "The dashboard must show the summary information graphically with their relations.", "D", false);
      docs.AddRequirement(sec, 3, "The dashboard must show the experiments's completition percentage (0%, 25%, 50%, 100%).", "D", false);

      sec = docs.AddSection(cat, "Processes Viewer");
      docs.AddRequirement(sec, 1, "The network viewer must show the following information: process type, node, socket, core, total memory, free memory", "D", true);

      sec = docs.AddSection(cat, "Experiments Viewer");
      docs.AddRequirement(sec, 1, "The experiments viewer must show the following information: experiment id, completition, list of processes", "D", true);

      sec = docs.AddSection(cat, "Documents");
      docs.AddRequirement(sec, 1, "User and functional requirements specification must be documented.", "M", true);
      docs.AddRequirement(sec, 2, "Use cases must be documented.", "M", true);
      docs.AddRequirement(sec, 3, "The traceability matrix between URS and UC must be documented.", "M", true);
      docs.AddRequirement(sec, 4, "The system design must be documented.", "M", true);


      cat = docs.AddCategory(mod, "Pipeline Development Section");
      // *********************************************************

      sec = docs.AddSection(cat, "Pipeline Editor");
      docs.AddRequirement(sec, 1, "The system must allow user to work with more than one pipeline at the same time.", "M", true);
      docs.AddRequirement(sec, 2, "The pipeline editor will have the following node types: Inputs / Outputs / Calculations / Pipelines / Local Variables.", "M", true);
      docs.AddRequirement(sec, 3, "Pipeline attributes will be (metadata): namespace / name / date / owner / general description / inputs description / outputs description / result description.", "M", false);
      docs.AddRequirement(sec, 4, "User must be able to zoom the pipeline page with the keyboard keys: '+' / '-'.", "O", true);
      docs.AddRequirement(sec, 5, "User must be able to zoom the pipeline page using an interface menu.", "O", true);
      docs.AddRequirement(sec, 6, "User must be able to move the pipeline page with the keyboard keys: Up / Right / Down / Left.", "O", true);
      docs.AddRequirement(sec, 7, "User must be able to move up and down the pipeline page with the mouse wheel.", "O", true);
      docs.AddRequirement(sec, 8, "User should be able to move the editor page using the mouse.", "O", false);
      docs.AddRequirement(sec, 9, "User should be able to copy / paste nodes using the mouse.", "O", false);
      docs.AddRequirement(sec, 10, "User should be able to select nodes using the mouse.", "O", true);
      docs.AddRequirement(sec, 11, "User should be able to multiselect nodes nodes using the mouse.", "O", false);
      docs.AddRequirement(sec, 12, "User should be able to move all selected nodes at the same time.", "O", false);
      docs.AddRequirement(sec, 13, "The system must show help for the following components: calculations / pipelines.", "O", false);
      docs.AddRequirement(sec, 14, "The system allow user to activate / disactivate a grid in the pipeline page background.", "O", true);
      docs.AddRequirement(sec, 15, "The system allow user to activate / disactivate the snap to the grid.", "O", true);
      docs.AddRequirement(sec, 16, "All node connections must be \"magnetic connections\".", "O", true);
      docs.AddRequirement(sec, 17, "The pipeline parallelism will be defined explicitly by its node dependencies.", "M", true);
      docs.AddRequirement(sec, 18, "The system will save pipelines into a remote repository.", "M", true);
      docs.AddRequirement(sec, 19, "The system must allow to debug pipelines for looking for errors.", "M", true);
      docs.AddRequirement(sec, 20, "The system will allow to remove pipelines from the remote repository.", "M", true);
      docs.AddRequirement(sec, 21, "The system will allow to load pipelines from the remote repository.", "M", true);
      docs.AddRequirement(sec, 22, "GONZ. All graphs must be directed acyclic graph (DAG).", "M", false);

      sec = docs.AddSection(cat, "Pipeline Input Nodes");
      docs.AddRequirement(sec, 1, "The pipeline input node must be connected to at least one node.", "M", true);
      docs.AddRequirement(sec, 2, "The pipeline input node can only be connected to these nodes: [calculation, pipeline].", "M", true);
      docs.AddRequirement(sec, 3, "The pipeline input node will get its name automatically from its connected node.", "M", true);
      docs.AddRequirement(sec, 4, "User will be able to change the pipeline input node's name.", "M", false);
      docs.AddRequirement(sec, 5, "The system should allow user to define the pipeline input node's default values and/or ranges.", "O", false);

      sec = docs.AddSection(cat, "Pipeline Output Nodes");
      docs.AddRequirement(sec, 1, "The pipeline output node must be connected to only one node.", "M", true);
      docs.AddRequirement(sec, 2, "The pipeline output node can only be connected to these nodes: [calculation, pipeline].", "M", true);
      docs.AddRequirement(sec, 3, "The pipeline output node will get its name automatically from its connected node.", "M", true);
      docs.AddRequirement(sec, 4, "User will be able to change the pipeline output node's name.", "M", false);

      sec = docs.AddSection(cat, "Variable Nodes");
      docs.AddRequirement(sec, 1, "User must be able to set the value to a variable node.", "M", false);

      sec = docs.AddSection(cat, "Calculation Nodes");
      docs.AddRequirement(sec, 1, "If the calculation node has outputs then at least one output must be connected.", "M", true);
      docs.AddRequirement(sec, 2, "If the calculation node has inputs then at least one input must be connected.", "M", true);
      docs.AddRequirement(sec, 3, "User must be able to connect a calculation node input or output with a new variable without knowing the correct type.", "M", true);

      
      cat = docs.AddCategory(mod, "Experiment Designer Section");
      // ********************************************************

      sec = docs.AddSection(cat, "Experiment Debug");
      docs.AddRequirement(sec, 1, "The system must allow user to work with more than one experiment at the same time.", "M", true);
      docs.AddRequirement(sec, 2, "The system must allow user to debug the experiment.", "M", false);
      docs.AddRequirement(sec, 3, "The system must allow user to run the experiment.", "M", false);
      docs.AddRequirement(sec, 4, "The system must represent the \"run experiment\" action with a \"play button\".", "M", false);


      cat = docs.AddCategory(mod, "Session Manager");
      // ********************************************

      sec = docs.AddSection(cat, "File Upload");
      docs.AddRequirement(sec, 1, "The session managger must allow user to upload files.", "M", false);

      sec = docs.AddSection(cat, "Variables");
      docs.AddRequirement(sec, 1, "The session managger must allow user to view the data manager variable's list.", "M", false);


      cat = docs.AddCategory(mod, "Design Requirements");
      // ************************************************

      sec = docs.AddSection(cat, "General Design");
      docs.AddRequirement(sec, 1, "The interface must have \"fullscreen\".", "O", true);
      docs.AddRequirement(sec, 2, "The interface must have \"multiple themes\".", "O", true);
      docs.AddRequirement(sec, 3, "The interface must show a progress bar when it is waiting for a server answer.", "O", true);

      sec = docs.AddSection(cat, "Logo");
      docs.AddRequirement(sec, 1, "The system must have a new logo that uses the word \"ngasp\" and last \"sp\" letters must be shown different.", "O", true);

      sec = docs.AddSection(cat, "Cookies");
      docs.AddRequirement(sec, 1, "The interface must save the last page opened in a cookie (the page name).", "O", true);
      docs.AddRequirement(sec, 2, "On the start up, the interface must open the last visited page according to an specific cookie value.", "O", true);
      docs.AddRequirement(sec, 3, "The interface must save the last menu state in a cookie (visible / hidden).", "O", true);
      docs.AddRequirement(sec, 4, "On the start up, the interface must show / hide the menu according to an specific cookie value.", "O", true);
      docs.AddRequirement(sec, 5, "The interface must save the last theme selected in a cookie (visible / hidden).", "O", true);
      docs.AddRequirement(sec, 6, "On the start up, the interface must select the theme according to an specific cookie value.", "O", true);


      // =========================================================================
      mod = docs.AddModule($scope.user_requirements, "Data Bases");
      // =========================================================================

      cat = docs.AddCategory(mod, "Pipeline's Repository");
      // **************************************************

      sec = docs.AddSection(cat, "General");
      docs.AddRequirement(sec, 1, "The pipeline's repository will store pipelines: WCL & PGI information.", "M", false);
      docs.AddRequirement(sec, 2, "The pipeline's repository will be accessible by: pipeline developers and administrators.", "M", false);
      docs.AddRequirement(sec, 3, "GONZ. The pipeline repository will be installed in the CM machine", "M", false);


      cat = docs.AddCategory(mod, "Experiment's Repository");
      // ****************************************************

      sec = docs.AddSection(cat, "General");
      docs.AddRequirement(sec, 1, "The experiment's repository will store experiments: WCL & PGI information.", "M", false);
      docs.AddRequirement(sec, 2, "The experiment's repository will be accessible by: experiment designers, pipeline developers and administrators.", "M", false);


      cat = docs.AddCategory(mod, "Users's Database");
      // *********************************************

      sec = docs.AddSection(cat, "General");
      docs.AddRequirement(sec, 1, "This database will contain a list of system users with their system roles.", "M", false);

      // =========================================================================
      mod = docs.AddModule($scope.user_requirements, "Installation");
      // =========================================================================

      cat = docs.AddCategory(mod, "Workstation");
      // ****************************************

      sec = docs.AddSection(cat, "General");
      docs.AddRequirement(sec, 1, "The system must run in a workstation.", "M", false);

      cat = docs.AddCategory(mod, "Cluster");
      // ************************************

      sec = docs.AddSection(cat, "General");
      docs.AddRequirement(sec, 1, "The system must run in cluster of nodes.", "M", false);



      // =========================================================================
      // List with only URS names, descriptions and boolean if it is used:
      // =========================================================================

      $rootScope.URS_list = [];
      for (var p1 = 0; p1 < $rootScope.user_requirements.length; p1++) {
        var s1 = $rootScope.user_requirements[p1];
        for (var p2 = 0; p2 < s1.list.length; p2++) {
          var s2 = s1.list[p2];
          for (var p3 = 0; p3 < s2.list.length; p3++) {
            var s3 = s2.list[p3];
            for (var p4 = 0; p4 < s3.list.length; p4++) {
              var s4 = s3.list[p4];
              if (s4.why_removed == undefined) {
                var id = s1.id + '-' + s2.id + '-' + s3.id + '-' + docs.To3Digits(s4.id);

                if (arrays.FindArrayElementById($rootScope.URS_list, id) != null) {
                  alert("duplicated URS: " + id);
                }

                /*
                var find_id = id;
                var cnt = 2;
                while (arrays.FindArrayElementById($rootScope.URS_list, find_id) != null) {
    
                  find_id = id + '-' + cnt; 
                  cnt++;
                  //alert("duplicated URS: " + id);
                }

                id = find_id;*/

                $rootScope.URS_list.push(
                {
                  id:    id,
                  desc:  s4.desc,
                  used:  false
                });
              }
            }
          }
        }
      }

      // =========================================================================
      // Traceability Matrix:
      // =========================================================================



      $rootScope.traceability_matrix = [];

      cas = docs.AddUser("Backend User");
      cas = docs.AddCase(-1, "Initialize all system components.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-TMA-001');
      docs.SetURS(cas, 'BAC-CLM-TMA-002');
      docs.SetURS(cas, 'BAC-CLM-TMA-003');
      docs.SetURS(cas, 'BAC-CLM-TMA-004');
      docs.SetURS(cas, 'BAC-CLM-TMA-005');
      docs.SetURS(cas, 'BAC-CLM-TMA-006');
      docs.SetURS(cas, 'BAC-CLM-TMA-007');
      docs.SetURS(cas, 'BAC-CLM-TMA-008');
      docs.SetURS(cas, 'BAC-CLM-TMA-009');
      docs.SetURS(cas, 'BAC-CLM-TMA-010');
      docs.SetURS(cas, 'BAC-CLM-TMA-011');
      docs.SetURS(cas, 'BAC-CLM-TMA-012');
      docs.SetURS(cas, 'BAC-CLM-TCM-001');
      docs.SetURS(cas, 'BAC-CLM-OCO-001');
      docs.SetURS(cas, 'BAC-CLM-ICO-001');
      docs.SetURS(cas, 'BAC-CLM-CFA-001');
      docs.SetURS(cas, 'BAC-CLM-CMA-001');
      docs.SetURS(cas, 'BAC-CLM-CMA-002');
      docs.SetURS(cas, 'BAC-CLM-DFA-001');
      docs.SetURS(cas, 'BAC-CLM-DMA-001');
      docs.SetURS(cas, 'BAC-CLM-ICO-007');
      docs.SetURS(cas, 'BAC-CLM-LOG-001');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Execute command.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-CLI-001');
      docs.SetURS(cas, 'BAC-CLM-CLI-002');
      docs.SetURS(cas, 'BAC-CLM-CLI-003');
      docs.SetURS(cas, 'BAC-CLM-CLI-004');
      docs.SetURS(cas, 'BAC-CLM-CLI-005');
      docs.SetURS(cas, 'BAC-CLM-CLI-006');
      docs.SetURS(cas, 'BAC-CLM-CLI-007');
      docs.SetURS(cas, 'BAC-CLM-CLI-008');
      docs.SetURS(cas, 'BAC-CLM-CLI-009');
      docs.SetURS(cas, 'BAC-CLM-CLI-010');
      docs.SetURS(cas, 'BAC-CLM-CLI-011');
      docs.SetURS(cas, 'BAC-CLM-CLI-012');
      docs.SetURS(cas, 'BAC-CLM-CLI-013');
      docs.SetURS(cas, 'BAC-CLM-CLI-014');
      docs.SetURS(cas, 'BAC-CLM-CLI-015');
      docs.SetURS(cas, 'BAC-CLM-CLI-016');
      docs.SetURS(cas, 'BAC-CLM-CLI-017');
      docs.SetURS(cas, 'BAC-CLM-CLI-018');
      docs.SetURS(cas, 'BAC-CLM-CLI-019');
      docs.SetURS(cas, 'BAC-CLM-CLI-020');
      docs.SetURS(cas, 'BAC-CLM-CLI-021');
      docs.SetURS(cas, 'BAC-CLM-CLI-022');
      docs.SetURS(cas, 'BAC-CLM-LOG-010');
      docs.SetURS(cas, 'BAC-CLM-LOG-011');
      docs.SetURS(cas, 'BAC-CLM-ICO-002');
      cas = docs.AddCase(-1, "Include all commands in the commands manager.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-ICO-001');
      cas = docs.AddCase(-1, "Include options in the options container.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-OCO-001');
      cas = docs.AddCase(-1, "Fech initial instructions from the command line.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-ICO-003');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Execute an ngaSP script.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-CLI-004');
      docs.SetURS(cas, 'BAC-CLM-LOG-010');
      docs.SetURS(cas, 'BAC-CLM-LOG-011');
      cas = docs.AddCase(-1, "Get pending work.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-TMA-011');
      docs.SetURS(cas, 'BAC-CLM-ICO-001');
      cas = docs.AddCase(-1, "Prepare next instruction.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-TMA-011');
      docs.SetURS(cas, 'BAC-CLM-ICO-001');
      cas = docs.AddCase(-1, "LaunchNextInstruction.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-TMA-011');
      docs.SetURS(cas, 'BAC-CLM-ICO-001');

      cas = docs.AddCase(-1, "Add instruction to the instructions controller.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-ICO-003');
      docs.SetURS(cas, 'BAC-CLM-ICO-004');
      docs.SetURS(cas, 'BAC-CLM-ICO-006');
      cas = docs.AddCase(-1, "Remove instruction from the instructions controller.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-ICO-003');
      docs.SetURS(cas, 'BAC-CLM-ICO-004');
      docs.SetURS(cas, 'BAC-CLM-ICO-006');
      cas = docs.AddCase(-1, "Generate instructions from general options.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-ICO-003');
      docs.SetURS(cas, 'BAC-CLM-ICO-004');
      docs.SetURS(cas, 'BAC-CLM-ICO-006');


      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Execute the mstatspop calculation.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-CLI-003');
      docs.SetURS(cas, 'BAC-CLM-LOG-010');
      docs.SetURS(cas, 'BAC-CLM-LOG-011');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Change to interactive mode.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-CLI-021');
      docs.SetURS(cas, 'BAC-CLM-LOG-010');
      cas = docs.AddCase(-1, "Get instructions from stdin.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-ICO-003');
      docs.SetURS(cas, 'BAC-ISM-SIN-001');


      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Stop the interactive mode.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-CLI-022');
      docs.SetURS(cas, 'BAC-CLM-LOG-010');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Execute calculation.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-CAL-001');  	
      docs.SetURS(cas, 'BAC-CLM-CAL-002');  	
      docs.SetURS(cas, 'BAC-CLM-CAL-003');  	
      docs.SetURS(cas, 'BAC-CLM-CAL-004');  	
      docs.SetURS(cas, 'BAC-CLM-CAL-005');  	
      docs.SetURS(cas, 'BAC-CLM-CAL-006');  	
      cas = docs.AddCase(-1, "Include all calculations in the calculations factory.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-CFA-001');
      cas = docs.AddCase(-1, "Init the calculations manager with one calculation of each type.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-CMA-001');
      docs.SetURS(cas, 'BAC-CLM-CMA-002');
      cas = docs.AddCase(-1, "Calculate mstatspop.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-MST-001');
      cas = docs.AddCase(-1, "Calculate optimal-tests.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-OTE-001');
      cas = docs.AddCase(-1, "Calculate r2.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-R2-001');
      cas = docs.AddCase(-1, "Calculate r2p.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-R2P-001');
      cas = docs.AddCase(-1, "Calculate freq-stats.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-TFS-001');
      cas = docs.AddCase(-1, "Calculate file-stats.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-FST-001');
      cas = docs.AddCase(-1, "Calculate mismatch.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-MIS-001');
      cas = docs.AddCase(-1, "Calculate sxsfss.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-SXS-001');
      cas = docs.AddCase(-1, "Calculate joint-freq-dist.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-JFD-001');
      cas = docs.AddCase(-1, "Calculate piwpiafst.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-PIW-001');
      cas = docs.AddCase(-1, "Calculate hwhafsth.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-HWH-001');
      cas = docs.AddCase(-1, "Calculate fs.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-FS-001');
      cas = docs.AddCase(-1, "Calculate permute.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-PER-001');
      cas = docs.AddCase(-1, "Calculate dna_matrix-to_matrix-pol.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-DTM-001');
      cas = docs.AddCase(-1, "Calculate fasta-to-dna_matrix.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-FTD-001');
      cas = docs.AddCase(-1, "Calculate open-fasta-file.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-OFF-001');
      cas = docs.AddCase(-1, "Calculate gff.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-GFF-001');
      cas = docs.AddCase(-1, "Calculate mstatspop-open-fasta.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-MOF-001');
      cas = docs.AddCase(-1, "Calculate mstatspop-open-ms.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-MOM-001');
      cas = docs.AddCase(-1, "Calculate spectrum-file.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-SFI-001');
      cas = docs.AddCase(-1, "Calculate mask-file-ms.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-MFM-001');
      cas = docs.AddCase(-1, "Calculate effec-nuc-tcga-freqs.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-ENF-001');
      cas = docs.AddCase(-1, "Calculate calc-x.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-CX-001');
      cas = docs.AddCase(-1, "Calculate calc-y.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-CY-001');
      cas = docs.AddCase(-1, "Calculate calc-z.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-CZ-001');
      cas = docs.AddCase(-1, "Calculate lengthamng.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-LEN-001');
      cas = docs.AddCase(-1, "Calculate array-ope-x.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-AOX-001');
      cas = docs.AddCase(-1, "Calculate mstatspop-output.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-MOU-001');
      cas = docs.AddCase(-1, "Calculate array-sum-all.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-ASA-001');
      cas = docs.AddCase(-1, "Calculate duplicate-populations.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-DPO-001');
      cas = docs.AddCase(-1, "Calculate randomize.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-RAN-001');
      cas = docs.AddCase(-1, "Calculate gc-content.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CAL-GCO-001');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Create a Data Manager variable.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-DMA-001');
      docs.SetURS(cas, 'BAC-CLM-DMA-002');
      cas = docs.AddCase(-1, "Include all data types in the data factory.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-DFA-001');
      docs.SetURS(cas, 'BAC-DMA-DTY-001');
      docs.SetURS(cas, 'BAC-DMA-DTY-002');
      docs.SetURS(cas, 'BAC-DMA-BDA-001');
      docs.SetURS(cas, 'BAC-DMA-BDA-002');
      docs.SetURS(cas, 'BAC-DMA-BDA-003');
      docs.SetURS(cas, 'BAC-DMA-BDA-004');
      docs.SetURS(cas, 'BAC-DMA-BDA-005');
      docs.SetURS(cas, 'BAC-DMA-BDA-006');
      docs.SetURS(cas, 'BAC-DMA-BDA-007');
      docs.SetURS(cas, 'BAC-DMA-CDA-001');
      docs.SetURS(cas, 'BAC-DMA-CDA-002');
      docs.SetURS(cas, 'BAC-DMA-CDA-003');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Set value to a Data Manager variable.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'BAC-DMA-AVV-001');
      docs.SetURS(cas, 'BAC-DMA-AVV-002');
      docs.SetURS(cas, 'BAC-DMA-AVV-003');
      docs.SetURS(cas, 'BAC-DMA-AVV-004');


      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Print the Data Manager variable's value.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-DMA-002');
      cas = docs.AddCase(-1, "Get DM variable.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-DMA-002');
      cas = docs.AddCase(-1, "Export DM variable to JSON format.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-DMA-EDA-001');


      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Remove a Data Manager variable.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-DMA-002');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Save DM state to file.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-DMA-004');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Restore DM state from file.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-DMA-005');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Watch logs.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-LOG-013');
      cas = docs.AddCase(-1, "Create log message.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-LOG-002');
      docs.SetURS(cas, 'BAC-CLM-LOG-003');
      docs.SetURS(cas, 'BAC-CLM-LOG-004');
      docs.SetURS(cas, 'BAC-CLM-LOG-005');
      docs.SetURS(cas, 'BAC-CLM-LOG-006');
      docs.SetURS(cas, 'BAC-CLM-LOG-007');
      docs.SetURS(cas, 'BAC-CLM-LOG-008');
      docs.SetURS(cas, 'BAC-CLM-LOG-009');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Remove logs.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-LOG-012');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Remove history.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-ICO-008');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Execute command from history.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-ICO-009');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Watch history.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-ICO-010');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Write ngasp script file.", docs.CASE_MANUAL_PROCESS);
      docs.SetURS(cas, 'BAC-FFO-NGA-001');
      docs.SetURS(cas, 'BAC-FFO-NGA-002');
      docs.SetURS(cas, 'BAC-FFO-NGA-003');
      docs.SetURS(cas, 'BAC-FFO-NGA-004');
      docs.SetURS(cas, 'BAC-FFO-NGA-005');
      docs.SetURS(cas, 'BAC-FFO-NGA-006');
      docs.SetURS(cas, 'BAC-FFO-NGA-007');
      docs.SetURS(cas, 'BAC-FFO-NGA-008');
      docs.SetURS(cas, 'BAC-FFO-NGA-009');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Write mstatspop.ngasp script file.", docs.CASE_MANUAL_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-CAL-009');



      // ***
      cas = docs.AddUser("WebApp User");
      cas = docs.AddCase(-1, "Create sections.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'INT-WSE-SEC-001');
      docs.SetURS(cas, 'INT-WSE-SEC-002');
      docs.SetURS(cas, 'INT-WSE-SEC-003');
      docs.SetURS(cas, 'INT-WSE-SEC-004');
      docs.SetURS(cas, 'INT-WSE-SEC-005');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Togle fullscreen.", docs.CASE_MANUAL_PROCESS);
      docs.SetURS(cas, 'INT-DRE-GDE-001');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Change web theme.", docs.CASE_MANUAL_PROCESS);
      docs.SetURS(cas, 'INT-DRE-GDE-002');

      cas = docs.AddCase(-1, "Show / Hide progress bar.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'INT-DRE-GDE-003');

      // ***
      cas = docs.AddUser("Software Engineer");
      cas = docs.AddCase(-1, "Create a new C++ command in the development environment.", docs.CASE_MANUAL_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-STA-001');
      docs.SetURS(cas, 'BAC-CLM-STA-002');
      cas = docs.AddCase(-1, "Create unit tests for the new command.", docs.CASE_MANUAL_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-TCM-001');
      cas = docs.AddCase(-1, "Debug the new command.", docs.CASE_MANUAL_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-TCM-001');
      cas = docs.AddCase(-1, "Ensure all unit tests are Ok.", docs.CASE_MANUAL_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-CMA-001');
      cas = docs.AddCase(-1, "Upgrade the system (Rebuild / Deploy / Reinstall).", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-CMA-001');


      // ***
      cas = docs.AddUser("Calculation Developer : WebApp User, Software Engineer");
      cas = docs.AddCase(-1, "Create a new C++ calculation in the development environment.", docs.CASE_MANUAL_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-CAL-001');
      docs.SetURS(cas, 'BAC-CLM-CAL-002');
      docs.SetURS(cas, 'BAC-CLM-CAL-003');
      docs.SetURS(cas, 'BAC-CLM-CAL-004');
      docs.SetURS(cas, 'BAC-CLM-CAL-005');
      docs.SetURS(cas, 'BAC-CLM-CAL-006');
      docs.SetURS(cas, 'BAC-CLM-CAL-007');
      docs.SetURS(cas, 'BAC-CLM-CAL-008');
      docs.SetURS(cas, 'BAC-CLM-STA-001');
      docs.SetURS(cas, 'BAC-CLM-STA-003');
      cas = docs.AddCase(-1, "Debug the new calculation.", docs.CASE_MANUAL_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-CMA-001');
      cas = docs.AddCase(-1, "Create unit tests for the new calculation.", docs.CASE_MANUAL_PROCESS);
      docs.SetURS(cas, 'BAC-CLM-CMA-001');


      // ***
      cas = docs.AddUser("Pipeline Developer : WebApp User");

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Create a new pipeline.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-PDS-PED-001');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Load existing pipeline.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-PDS-PED-021');
      docs.SetURS(cas, 'INT-PDS-PED-001');

// To Do:
      // CASE_START_PROCESS
//      cas = docs.AddCase(-1, "Set pipeline attributes.", docs.CASE_START_PROCESS);
//      docs.SetURS(cas, 'INT-PDS-PED-003');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Remove existing pipeline.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-PDS-PED-020');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Add node.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-PDS-PED-002');
      cas = docs.AddCase(-1, "Get the list of node types.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'INT-PDS-PED-002');


      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Select node.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-PDS-PED-010');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Remove node.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-PDS-PED-002');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Connect two nodes.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-PDS-PED-016');
      docs.SetURS(cas, 'INT-PDS-PIN-001');
      docs.SetURS(cas, 'INT-PDS-PIN-002');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Disconnect two nodes.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-PDS-PED-016');
      docs.SetURS(cas, 'INT-PDS-PIN-001');
      docs.SetURS(cas, 'INT-PDS-PIN-002');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Move node.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-PDS-PED-005');


      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Show node help.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-PDS-PED-013');


      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Change node value.", docs.CASE_START_PROCESS);
      // TBD: docs.SetURS(cas, 'INT-PDS-PIN-005');
      docs.SetURS(cas, 'INT-PDS-VNO-001');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Add input to node.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-PDS-PED-002');
      docs.SetURS(cas, 'INT-PDS-PIN-001');
      docs.SetURS(cas, 'INT-PDS-PIN-002');
      docs.SetURS(cas, 'INT-PDS-PIN-003');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Add output to node.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-PDS-PED-002');
      docs.SetURS(cas, 'INT-PDS-PON-001');
      docs.SetURS(cas, 'INT-PDS-PON-002');
      docs.SetURS(cas, 'INT-PDS-PON-003');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Add local variable to node.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-PDS-PED-002');
      docs.SetURS(cas, 'INT-PDS-CNO-003');


      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Zoom the canvas.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-PDS-PED-004');
      docs.SetURS(cas, 'INT-PDS-PED-005');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Move the canvas.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-PDS-PED-006');
      docs.SetURS(cas, 'INT-PDS-PED-007');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Show / Hide the grid.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-PDS-PED-014');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Save the pipeline.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-PDS-PED-018');
      cas = docs.AddCase(-1, "Generate Workflow PGI information.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-FFO-PGP-001');

      // CASE_START_PROCESS
      cas = docs.AddCase(-1, "Debug the pipeline.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-PDS-PED-019');
      docs.SetURS(cas, 'INT-PDS-CNO-001');
      docs.SetURS(cas, 'INT-PDS-CNO-002');

      cas = docs.AddCase(-1, "Generate Workflow CWL information.", docs.CASE_SYSTEM_PROCESS);
      docs.SetURS(cas, 'BAC-FFO-CWC-001');
      docs.SetURS(cas, 'BAC-FFO-CWC-002');


      // ***
      cas = docs.AddUser("Experiment Designer : WebApp User");
      cas = docs.AddCase(-1, "Create a new experiment.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-EDS-EDE-001');

      cas = docs.AddCase(1, "Load an existing experiment.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-EDS-EDE-001');

      // ***
      cas = docs.AddUser("Administrator: WebApp User");
      cas = docs.AddCase(-1, "Start the system.", docs.CASE_MANUAL_PROCESS);
      docs.SetURS(cas, 'INS-WOR-GEN-001');
      docs.SetURS(cas, 'INS-CLU-GEN-001');


      cas = docs.AddCase(-1, "Get system network information.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-ASE-DAS-001');
      docs.SetURS(cas, 'INT-ASE-DAS-002');
      docs.SetURS(cas, 'INT-ASE-DAS-003');
      docs.SetURS(cas, 'INT-ASE-PVI-001');
      cas = docs.AddCase(-1, "Get experiments information.", docs.CASE_START_PROCESS);
      docs.SetURS(cas, 'INT-ASE-EVI-001');
      cas = docs.AddCase(-1, "Create system documentation.", docs.CASE_MANUAL_PROCESS);
      docs.SetURS(cas, 'INT-ASE-DOC-001');
      docs.SetURS(cas, 'INT-ASE-DOC-002');
      docs.SetURS(cas, 'INT-ASE-DOC-003');
      docs.SetURS(cas, 'INT-ASE-DOC-004');


      // ***
      cas = docs.AddUser("Grpahical Designer");
      cas = docs.AddCase(-1, "Checklist.", docs.CASE_MANUAL_PROCESS);
      docs.SetURS(cas, 'INT-DRE-LOG-001');


//      cas = docs.AddCase(1, "The Master selects a worker to execute a calculation", docs.CASE_SYSTEM_PROCESS);


      // ********************************
      $rootScope.URS_Ready = true;
      // ********************************
    }    
  };

	$scope.init();
});






