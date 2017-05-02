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

CRAG.controller('ExperimentsController', function($scope, $rootScope, $window, AlertService, MessagesFactory, logs, socket) {

  $scope.stdout = "";
  $scope.charts = []; // filters defined for this list (chart.js & boxplot.js)
/*
  var script = "";
  script += "verbose --level debug" + "<br />"
  script += "set-value --to $encoding --eq \"english_bn\"" + "<br />"
  script += "dim -n test_chart/10_32_13/string_vector_2_0 --as string_vector" + "<br />"
  script += "set-value --to test_chart/10_32_13/string_vector_2_0 --eq \"a,b,c,d,e\"" + "<br />"
  script += "dim -n test_chart/10_32_13/string_vector_3_0 --as string_vector" + "<br />"
  script += "set-value --to test_chart/10_32_13/string_vector_3_0 --eq \"s1,s2,s3,s4,s5\"" + "<br />"
  script += "dim -n test_chart/10_32_13/int_4_0 --as int" + "<br />"
  script += "set-value --to test_chart/10_32_13/int_4_0 --eq \"9999\"" + "<br />"
  script += "dim -n test_chart/10_32_13/calc-mstatspop_0_1 --as double_vector" + "<br />"
  script += "calc -n test_chart/10_32_13/calc-mstatspop_0 --as calc-mstatspop" + "<br />"
  script += "set-value --to test_chart/10_32_13/calc-mstatspop_0.inputs --eq \"null,test_chart/10_32_13/int_4_0,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null\"" + "<br />"
  script += "set-value --to test_chart/10_32_13/calc-mstatspop_0.outputs --eq \"null,test_chart/10_32_13/calc-mstatspop_0_1\"" + "<br />"
  script += "run-calculation -n test_chart/10_32_13/calc-mstatspop_0" + "<br />"
  script += "if --ref $result --eq 0" + "<br />"
  script += "dim -n test_chart/10_32_13/float_vector_in_1_0 --as float_vector" + "<br />"
  script += "set-value --to test_chart/10_32_13/float_vector_in_1_0 --eq test_chart/10_32_13/calc-mstatspop_0_1" + "<br />"
  script += "print -n test_chart/10_32_13/float_vector_in_1_0 --mode value --text \"'node':1,'type':'chart','input':0,'data':\" --eol" + "<br />"
  script += "'node':1,'type':'chart','input':0,'data':'68571.5','1.77923','2.9036537','1.69397','2.2178405','1.78624','7.1501922','1.66505','2.0832706','1.85152','1.2046429','1.81652','9.6647909','1.75721','523.727','1.77383','4.7940312','1.7123','265209','1.75961','4.0654511','1.78423','2.823406','1.62772','4.0127133','1.8687','5.7240909','1.79447','7.2529222','1.79232','3.012606','1.6563','3.4792515','1.67433','4.9182517','1.82905','2.4265721','1.81485','8.8280833','1.85253','1.1021816','1.40845','1.6923224','1.71594','1.97808','1.85149','4.0494824','1.77204','1.6624633','1.85873'" + "<br />"
  script += "print -n test_chart/10_32_13/string_vector_2_0 --mode value --text \"'node':1,'type':'chart','input':1,'data':\" --eol" + "<br />"
  script += "'node':1,'type':'chart','input':1,'data':'a','b','c','d','e'" + "<br />"
  script += "print -n test_chart/10_32_13/string_vector_3_0 --mode value --text \"'node':1,'type':'chart','input':2,'data':\" --eol" + "<br />"
  script += "'node':1,'type':'chart','input':2,'data':'s1','s2','s3','s4','s5'" + "<br />"
  script += "endif" + "<br />"
  script += "delete -n test_chart/10_32_13/calc-mstatspop_0_1" + "<br />"
  $scope.stdout = script;
*/
  ReplaceAll = function(text, search, replace) {
    // http://stackoverflow.com/questions/1144783/replacing-all-occurrences-of-a-string-in-javascript

    // Regular Expression Based Implementation
    // =======================================
    return text.replace(new RegExp(search, 'g'), replace);

    // Split and Join (Functional) Implementation
    // ==========================================
    // return text.split(search).join(replace);
  };

  GetAxeSpan = function(data_length, groups) {
    var x_span = data_length / groups;
    // Example: x_span = 357.565
    var x_span_str = "a" + x_span;
    // Example: x_span = "a357.565"
    x_span_str = x_span_str.substr(0, x_span_str.indexOf(".", 0));
    // Example: x_span = "a357"
    var zeros = "";
    for (var k = 0; k < x_span_str.length - 2; k++) {  // -2: do not count 'a' neither count '3'
      zeros += "0";
    }
    // Example: x_span = "a357". zeros = "00";
    x_span_str = x_span_str[1] + zeros;
    // Example: x_span = "300".
    x_span = x_span_str * 1;
    // Example: x_span = 300.
    return x_span;
  };

  CreateGraphs = function() {
    graph_list = [];

    // Example:
    // <br />node|4|boxplot|0|{"id":"s","type":"string","value":"Example 1"}<br />

    var node_pos = 0;
    do {
      node_pos = $scope.stdout.indexOf("<br />node|", node_pos + 1);

      if (node_pos != -1) {

        var graph_node = {
          "node":0,
          "type":"",
          "inputs":[]
        };

        var eol_pos = $scope.stdout.indexOf("<br />",  node_pos + 1);
        if (eol_pos != -1) {
          try {
            var line = $scope.stdout.substr(node_pos, eol_pos - node_pos);
            // line = "<br />node|4|boxplot|0|{"id":"s","type":"string","value":"Example 1"}"

            line = ReplaceAll(line, "<br />node", "");
            line = line.substr(line.indexOf("|") + 1);
            // line = "4|boxplot|0|{"id":"s","type":"string","value":"Example 1"}"

            graph_node.node = line.substr(0, line.indexOf("|"));
            line = line.substr(line.indexOf("|") + 1);
            // line = "boxplot|0|{"id":"s","type":"string","value":"Example 1"}"
            //  var graph_node = {
            //   "node":4,<-----
            //   "type":"",
            //   "inputs":[]
            // };

            graph_node.type = line.substr(0, line.indexOf("|"));
            line = line.substr(line.indexOf("|") + 1);
            // line = "0|{"id":"s","type":"string","value":"Example 1"}"
            //  var graph_node = {
            //   "node":4,
            //   "type":"boxplot",<-----
            //   "inputs":[]
            // };

            var num_input = line.substr(0, line.indexOf("|"));
            line = line.substr(line.indexOf("|") + 1);
            // line = "{"id":"s","type":"string","value":"Example 1"}"
            // num_input = 0;<-----
            //  var graph_node = {
            //   "node":4,
            //   "type":"boxplot",
            //   "inputs":[]
            // };

            var new_input = JSON.parse(line);
            graph_node.inputs.push(new_input);

            line = "";
            // line = ""
            // num_input = 0;
            //  var graph_node = {
            //   "node":4,
            //   "type":"boxplot",
            //   "inputs":[{"id":"s","type":"string","value":"Example 1"}]<----
            // };
         
            graph_node.inputs[0].id = num_input;
            // num_input = 0;
            //  var graph_node = {
            //   "node":4,
            //   "type":"boxplot",
            //   "inputs":[{"id":0,<----
            //              "type":"string","value":"Example 1"}]
            // };

            var found = false;
            for (var i = 0; ((i < graph_list.length) && (found == false)); i++) {
              if (graph_list[i].node == graph_node.node) {
                found = true;
                graph_list[i].inputs.push(graph_node.inputs[0]);
              }
            }

            if (!found) {
              graph_list.push(graph_node);
            }
          }
          catch(e) {
            AlertService.error(e + "\n" + line);
          }

        }
      }
    } while(node_pos != -1);


    $scope.charts = [];

    for (var i = 0; i < graph_list.length; i++) {
      switch(graph_list[i].type) {
        // =====================================================================
        case "chart":
        // =====================================================================
          var new_chart = {
            "id":$scope.charts.length,
            "type":"chart", //<--- This is the id used by the view for filtering the list of charts.
            "data":[], 
            "labels":[],
            "series":[]
          };

          for (var j = 0; j < graph_list[i].inputs.length; j++) {
            switch (graph_list[i].inputs[j].id) {
              case "0": // data
                new_chart.data = [graph_list[i].inputs[j].value];
                break;
              case "1": // labels
                new_chart.labels = [graph_list[i].inputs[j].value];
                break;
              case "2": // series
                new_chart.series = [graph_list[i].inputs[j].value];
                break;
            }
          }

          if (new_chart.data.length != 0) {
            if (new_chart.labels.length == 0) {
              var x_span = GetAxeSpan(graph_list[i].inputs[0].value.length, 7);  // For example in 7 groups. 7 is a random number that I think it could be ok.

              var x_count = 0;
              for (var j = 0; j < graph_list[i].inputs[0].value.length; j++) {
                if (x_count > 0) {
                  x_count--;
                  new_chart.labels.push('');
                } else {
                  x_count = x_span - 1;
                  new_chart.labels.push(j);
                }
              }
            }

            $scope.charts.push(new_chart);
          }
          break;

        // =====================================================================
        case "boxplot":
        // =====================================================================


          // Every boxplot chart could draw more than one boxplot.
          // Meanwhile, we will only use it with one boxplot.
          var new_boxplot_list = [
              {
                  label: "Sample A",
                  values: {
                      Q1: 180,
                      Q2: 200,
                      Q3: 250,
                      whisker_low: 115,
                      whisker_high: 400,
                      outliers: [50, 100, 425]
                  }
              }
          ];


          for (var j = 0; j < graph_list[i].inputs.length; j++) {
            switch (graph_list[i].inputs[j].id) {
              case "0":
                new_boxplot_list[0].label = graph_list[i].inputs[j].value;
                break;
              case "1":
                new_boxplot_list[0].values.Q1 = graph_list[i].inputs[j].value * 1;
                break;
              case "2":
                new_boxplot_list[0].values.Q2 = graph_list[i].inputs[j].value * 1;
                break;
              case "3":
                new_boxplot_list[0].values.Q3 = graph_list[i].inputs[j].value * 1;
                break;
              case "4":
                new_boxplot_list[0].values.whisker_low = graph_list[i].inputs[j].value * 1;
                break;
              case "5":
                new_boxplot_list[0].values.whisker_high = graph_list[i].inputs[j].value * 1;
                break;
              case "6":
                new_boxplot_list[0].values.outliers = graph_list[i].inputs[j].value;
                break;
            }
          }


          var new_boxplot_chart = {
            "id":$scope.charts.length,
            "type":"boxplot", //<--- This is the id used by the view for filtering the list of charts.
            "options":{
              chart: {
                type: 'boxPlotChart'
                ,height: 450
                ,margin : {
                  top: 20,
                  right: 20,
                  bottom: 30,
                  left: 50
                },
                color:['green', 'darkorange', 'darkblue', 'darkred', 'darkviolet']
                ,x: function(d){return d.label;}
                //y: function(d){return d.values.Q3;},
                ,maxBoxWidth: 55
                // ,yDomain: [0, 500]
              }
            },
            "data":new_boxplot_list,
            "config":"config",
            "events":"events"
          };

          $scope.charts.push(new_boxplot_chart);


          break;

        // =====================================================================
        case 'donutchart':
        // =====================================================================
          var new_donutchart = {
            "id":$scope.charts.length,
            "type":"donutchart", //<--- This is the id used by the view for filtering the list of charts.
            "options": {
              chart: {
                type: 'pieChart',
                height: 450,
                donut: true,
                x: function(d){return d.key;},
                y: function(d){return d.y;},
                showLabels: true,

                pie: {
                  startAngle: function(d) { return d.startAngle/2 -Math.PI/2 },
                  endAngle: function(d) { return d.endAngle/2 -Math.PI/2 }
                },
                duration: 500,
                legend: {
                  margin: {
                    top: 5,
                    right: 140,
                    bottom: 5,
                    left: 0
                  }
                }
              }
            }
          };

          $scope.charts.push(new_donutchart);
          break;
      }
    }
  };


  function OnResize() {
/*    console.log("resize()");

    for (var i = 0; i < $scope.charts.length; i++) {
      var graph_canvas = document.getElementById($scope.charts[i].type + "_" + $scope.charts[i].id);
      if (graph_canvas != null) {
      }
    }
*/
  };

	$scope.init = function () {
        // Default values.
        // When the user selectes an experiment from the table, this
        // variable will be a pointer to the row:
        $scope.selected_experiment = {
    		experiment_id: '',
            name: '',
            status: ''
        };
		$scope.cmd = "version";
		$scope.show_new_experiment = false;
		$scope.new_experiment_message = "";

		$scope.show_query_experiment = false;
		$rootScope.OnRefreshExperimentsList();

    CreateGraphs();

    var the_browser_window = angular.element($window);
    the_browser_window.bind('resize', OnResize);
	};

  // ========================================================================
	// PAGE EVENTS
	// ========================================================================

	$scope.OnRequestNewExperimentName = function() {
		MessagesFactory.input("Input experiment name:", 
		function(input) {  // Ok
			$scope.new_experiment_name = input;
			if (input != "") {
				var found = false;
				for (var i = 0; ((i < $rootScope.experiments_list.length) && (!found)); i++) {
					found = ($rootScope.experiments_list[i].name == $scope.new_experiment_name);
				}
				if (found) {
					MessagesFactory.error("The experiment name already exists", 
                    function() {},
                    function() {});
				} else {
					$scope.OnCreateExperiment();
				}
			}
		},
		function() {  // Cancel
			$scope.OnCancelExperimentCreation();
		})
	};

	$rootScope.OnSelectExperiment = function(experiment_id, name, status) {
        var found = false;
		for (var i = 0; ((i < $rootScope.experiments_list.length) && (!found)); i++) {
			if ($rootScope.experiments_list[i].experiment_id == experiment_id) {
                found = true;
                $scope.selected_experiment = $rootScope.experiments_list[i]; 
            }
		}

		$rootScope.OnGetOutput();
		$scope.OnQueryExperiment();
	};

	$scope.OnCreateExperiment = function() {
		$scope.ClearOutputWindow();

		$rootScope.Http({
				method: 'POST',
				url: $rootScope.webAddress + 'results',
				headers: { 'Content-Type': 'application/json' },
				data: {
					experiment_name: $scope.new_experiment_name
				},
		},
		function(message) {
			$scope.show_new_experiment = false;
			$scope.new_experiment_name = "";
			$scope.new_experiment_message = "";
			$rootScope.OnRefreshExperimentsList();
		},
		function(message) {
			$scope.new_experiment_message = message.data.data;
		});
	};

	$scope.OnCancelExperimentCreation = function() {
		$scope.show_new_experiment = false;
		$scope.new_experiment_message = "";
		$scope.new_experiment_name = "";
	};

	$scope.OnQueryExperiment = function() {
        if (($scope.selected_experiment.status == 'NOT_STARTED') ||
            ($scope.selected_experiment.status == 'OPEN')) {
    		$scope.show_query_experiment = true;
        }
	};

	$scope.OnExecuteCommand = function() {
    // The first command executed changes the status to open:
    if ($scope.selected_experiment.status == 'NOT_STARTED') {
      $scope.selected_experiment.status = 'OPEN';
    }

    if ($scope.selected_experiment.status == 'OPEN') {

      if ($scope.cmd == "dm") {
          var send = {
            method: 'GET',
            url: $rootScope.webAddress + 'datavariables/' + $scope.selected_experiment.experiment_id,
            headers: { 'Content-Type': 'application/json' },
            params: { "experiment_id": $scope.selected_experiment.experiment_id },
            data: {},
          };
          $rootScope.Http(send, function(message) {
                                  $scope.stdout = message; 
                                },
                                function(message) {
                                  AlertService.error("Couldn't get Data Manager variables.");
                                });

      } else {
        if ($scope.cmd == "clear") {
          $scope.OnCleanOutput();
        } else {
          $scope.ClearOutputWindow();
          var send = {
            method: 'PUT',
            url: $rootScope.webAddress + 'results/' + $scope.selected_experiment.experiment_id + '/' + encodeURIComponent($scope.cmd),
            headers: { 'Content-Type': 'application/json' },
            params: { "experiment_id": $scope.selected_experiment.experiment_id, "cmd": $scope.cmd },
            data: {},
          };

          if ($scope.cmd == "exit") {
            $rootScope.Http(send, function(message) {
                                    $scope.OnCloseQueryExperiment();
                                  },
                                  function(message) {
                                    AlertService.error("Command NOT executed.");
                                  });

            $scope.selected_experiment.status = 'CLOSING...';
          } else {
            $rootScope.Http(send, function(message) {
                                    $rootScope.OnGetOutput();
                                  },
                                  function(message) {
                                    AlertService.error("Command NOT executed.");
                                  });
          }
        }
      }
      $scope.cmd = "";
    } else {
      AlertService.error("This experiment is not available.");
    }
	};

	$rootScope.OnGetOutput = function() {
        $scope.ClearOutputWindow();

        if ($scope.selected_experiment.status == 'OPEN') {
		    $rootScope.Http({
		            method: 'GET',
		            url: $rootScope.webAddress + 'results/' + $scope.selected_experiment.experiment_id,
				    headers: { 'Content-Type': 'application/json' },
				    params: { "experiment_id": $scope.selected_experiment.experiment_id },
		            data: {},
	        },
		    function(message) {
                var output = message.data.data.result;

                if (output != null) {
                    // <hr> has own end of line, so let's remove the <br />:
                    output = output.split('<hr><br />').join('<hr>');

                    // Change all spaces by &nbsp; (otherwise only one space is shown)
                    // (But not spaces inside tags like <br />)
                    var output_fixed = "";
                    var inside_tag = false;
                    for (var i = 0; i < output.length; i++) {
                        var ch = output[i];
                        if (ch == '<') {
                            inside_tag = true;
                        }
                        if (ch == '>') {
                            inside_tag = false;
                        }
                        if (inside_tag == false) {
                            if (ch == ' ') {
                                output_fixed += "&nbsp;";
                            } else {
                                output_fixed += ch;
                            }
                        } else {
                            output_fixed += ch;
                        }
                    }
                    output = output_fixed;
                }

			    $scope.stdout = output;

          CreateGraphs();
		    },
		    function(message) {
       			AlertService.error("Command NOT executed.");
		    });
        }
	};

	$scope.OnCleanOutput = function() {
        if ($scope.selected_experiment.status == 'OPEN') {
		    $rootScope.Http({
		            method: 'DELETE',
		            url: $rootScope.webAddress + 'results/' + $scope.selected_experiment.experiment_id,
				    headers: { 'Content-Type': 'application/json' },
				    params: { "experiment_id": $scope.selected_experiment.experiment_id },
		            data: {},
	        },
		    function(message) {
			    $rootScope.OnGetOutput();
		    },
		    function(message) {
       			AlertService.error("Command NOT executed.");
		    });
        } else {
            AlertService.error("This experiment is not available.");
        }
	};

	// ========================================================================
	// VISIBILITY
	// ========================================================================

	$scope.ShowCleanOutputButton = function() {
		return ($scope.stdout != "");
	};

	$scope.ClearOutputWindow = function()  {
		$scope.stdout = "";
	};

	$scope.SetExperimentKey = function(lm_key, bin_key)  {
		$scope.key = lm_key + "-" + bin_key;
	};

	$scope.IsExperimentSelected = function() {
		return ($scope.selected_experiment.experiment_id != "");
	};

	$scope.ShowQueryExperiment = function() {
		return $scope.show_query_experiment;
	};

	$scope.OnCloseQueryExperiment = function() {
		$scope.show_query_experiment = false;
	};


	$scope.init();
});


