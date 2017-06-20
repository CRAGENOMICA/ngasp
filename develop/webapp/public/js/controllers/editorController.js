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
function IsObject(obj) {
    return ((typeof obj === "object") && (obj !== null));
}

CRAG.controller('EditorController', function($scope,
                                             $rootScope,
                                             $templateCache,
                                             $cookies,
                                             $window,
                                             $modal,
                                             $state,
                                             $sce,
                                             arrays,
                                             AlertService,
                                             MessagesFactory) {


    ////////////////////////////////////////////////////////////////////////////
    // CONSTANTS
    ////////////////////////////////////////////////////////////////////////////

    // Two states (two different menu options):
    //   - $state.includes("pipeline_editor") --> returns true
    //   - $state.includes("experiment_editor") --> returns true
    // Two types of file:
    //   - $scope.GetEditorType() --> returns $scope.FileType.PIPELINE
    //   - $scope.GetEditorType() --> returns $scope.FileType.EXPERIMENT
    $scope.FileType = {
      UNDEFINED: -1,
      PIPELINE:   0,
      EXPERIMENT: 1
    };

    var NOT_DEFINED = "2.14748e+09";
    var SERVER_DATA_PATH = '/develop/data/';

    ////////////////////////////////////////////////////////////////////////////
    // DATA
    ////////////////////////////////////////////////////////////////////////////

    $scope.canvas = null;
    $scope.ctx = null;
    var drawing = false;
    var dragging_id = null;
    var node_dragged = false;
    var prev_mouse_x = null;
    var prev_mouse_y = null;
    $scope.joining_connectors = null;
    $scope.node_selected = null;
    $scope.connector_selected = {node: null, connector: null, direction: null};
    var current_theme = null;
    var images = [];
    var num_images_loaded = 0;
    var num_data_resources_loaded = 0;
    var scaleFactor = 1.1;
    var MOVE_STEP = 50;
    $scope.ShowGrid = true;
    $scope.debug_mode = false;
    var panel_general = null;
    var HEADER_HEIGHT = 105;
    $scope.console = "";
    var EnableCanvasInputKey = true;
    var moving_canvas = false;
    var mouse_over_editor_canvas = false;
    var commands_list = [];
    var key_pressed = "";
    $scope.consoles = [];
    $scope.paint_page_borders = true;  // paints the page borders
    var OngoingExperimentsList = [];   // Enlist here your experiment id to be notified when the experiment is finished

    $scope.DoApply = function() {
        if ($scope.$root.$$phase != '$apply' && $scope.$root.$$phase != '$digest') {
            $scope.$apply();
        }
    };
    // =========================================================================
    // CONTEXT MENU
    // =========================================================================

//        ['Favorite Color', function ($itemScope, $event, color) {
  //      		alert(color);
    //    }]

$scope.MenuType = "eo";

    $scope.canvasMenuOptions = function () {
      var menu = [];
      var menu_items = [];

      if ($scope.ConnectorSelected()) {
        menu.push(["Add Variable", function ($itemScope, $event, value) { $scope.OnAddVariable() }, function ($itemScope, $event) { return $scope.ConnectorSelected(); }]);

        if ($scope.GetEditorType() == $scope.FileType.PIPELINE) {
          if ($scope.InputConnectorSelected()) {
            menu.push(["Add Input", function ($itemScope, $event, value) { $scope.OnAddInput() }, function ($itemScope, $event) { return $scope.InputConnectorSelected(); }]);
          }

          if ($scope.OutputConnectorSelected()) {
            menu.push(["Add Output", function ($itemScope, $event, value) { $scope.OnAddOutput() }, function ($itemScope, $event) { return $scope.OutputConnectorSelected(); }]);
          }
        }

          // SAME ++++++
          data_files = [];
          $scope.data_files.forEach(function(data_file) {
            var file_name = data_file.location + data_file.filename;

            short_file_name = ReplaceAll(file_name, SERVER_DATA_PATH, "");

            data_files.push([short_file_name, function ($itemScope) { $scope.OnAddVariable(file_name) }, function ($itemScope, $event) { return $scope.ConnectorSelected(); }]);
          });
          data_files.sort();
          menu.push(["Add Data File >", function ($itemScope) {}, data_files ]);
          // SAME ++++++


        if ($scope.OutputConnectorSelected()) {
          menu_items = [];
          $scope.node_types.forEach(function(node_type) {
            if ((node_type.style == $scope.NodeStyle.GRAPH_NODE) || (node_type.style == $scope.NodeStyle.EXTERNAL_VIEWER_NODE)) {
              menu_items.push([node_type.id, function ($itemScope) { $scope.AddPlotToTheNode(node_type.id); }]);
            }
          });
          menu.push(["Add Plot >", function ($itemScope) {}, menu_items ]);
        }

      }
      else {
        if ($scope.SelectedNodes()) {
          var items_above = false;
          if ($scope.node_selected.temp.type_obj.style == $scope.NodeStyle.CALCULATION_NODE) {
            menu.push(["Enable / Disable", function ($itemScope, $event, value) { $scope.OnSetDryRun() }, function ($itemScope, $event) { return $scope.SelectedNodes(); }]);
            items_above = true;
          }
          if ($scope.node_selected.temp.type_obj.style == $scope.NodeStyle.GRAPH_NODE) {
            menu.push(["Show in Right Panel", function ($itemScope, $event, value) { $scope.OnNodeGraphSelected($scope.node_selected.id); }, function ($itemScope, $event) { return $scope.SelectedNodes(); }]);
            items_above = true;
          }
          if ($scope.node_selected.temp.type_obj.style == $scope.NodeStyle.EXTERNAL_VIEWER_NODE) {
            menu.push(["Show in New Tab", function ($itemScope, $event, value) { $scope.OpenTFAViewer($scope.node_selected.id); }, function ($itemScope, $event) { return $scope.SelectedNodes(); }]);
            items_above = true;
          }
          if ($scope.node_selected.temp.type_obj.style == $scope.NodeStyle.PIPELINE_NODE) {
            menu.push(["Show Pipeline", function ($itemScope, $event, value) { ShowPipeline($scope.node_selected.temp.type_obj.id); }, function ($itemScope, $event) { return $scope.SelectedNodes(); }]);
            items_above = true;
          }
          if (items_above) {
            menu.push(null);
          }

          if (($scope.node_selected.temp.type_obj.style == $scope.NodeStyle.DATA_NODE) && ($scope.node_selected.temp.type_obj.id.indexOf('_file') != -1)) {
              menu.push(["Unregister Data File", function ($itemScope, $event, value) { $scope.OnUnregisterDataFile() }, function ($itemScope, $event) { return $scope.SelectedNodes(); }]);
          }
          menu.push(["Remove Node", function ($itemScope, $event, value) { $scope.OnRemoveNode() }, function ($itemScope, $event) { return $scope.SelectedNodes(); }]);
        } else {

          menu_items = [];
          $scope.node_types.forEach(function(node_type) {
            if (node_type.style == $scope.NodeStyle.CALCULATION_NODE) {
              var calc_name = node_type.id;
              if (calc_name.substr(0,5) == 'calc_') {
                calc_name = calc_name.substr(5, 1000);
              }
              menu_items.push([calc_name, function ($itemScope) { $scope.AddNodeToThePage(node_type.id); }]);
            }
          });
          menu.push(["Add Calculation >", function ($itemScope) {}, menu_items ]);


          menu_items = [];
          $scope.node_types.forEach(function(node_type) {
            if (node_type.style == $scope.NodeStyle.COMMENT_NODE) {
              var calc_name = node_type.id;
              menu_items.push([calc_name, function ($itemScope) { $scope.AddNodeToThePage(node_type.id); }]);
            }
          });
          menu.push(["Add Comment >", function ($itemScope) {}, menu_items ]);


          menu_items = [];
          $scope.node_types.forEach(function(node_type) {
            if (node_type.style == $scope.NodeStyle.PIPELINE_NODE) {
              menu_items.push([node_type.id, function ($itemScope) { $scope.AddNodeToThePage(node_type.id); }]);
            }
          });
          menu.push(["Add Stored Pipeline >", function ($itemScope) {}, menu_items ]);
/*
          // SAME ++++++
          data_files = [];
          $scope.data_files.forEach(function(data_file) {
            var file_name = data_file.location + data_file.filename;

            short_file_name = ReplaceAll(file_name, SERVER_DATA_PATH, "");

            /// Different
            data_files.push([short_file_name, function ($itemScope) { $scope.OnAddVariable(file_name); }]);
          });
          menu.push(["Add Data File >", function ($itemScope) {}, data_files ]);
          // SAME ++++++
*/

          /*
          menu_items = [];
          $scope.node_types.forEach(function(node_type) {
            if (node_type.style == $scope.NodeStyle.GRAPH_NODE) {
              menu_items.push([node_type.id, function ($itemScope) { $scope.AddNodeToThePage(node_type.id); }]);
            }
          });
          menu.push(["Add Plot >", function ($itemScope) {}, menu_items ]);
          */        

          menu.push(null);

          if ($scope.ShowGrid == true) {
            menu.push(["Hide Grid", function ($itemScope, $event, value) { $scope.OnShowHideGrid(); }, function ($itemScope, $event) { return !$scope.SelectedNodes(); }]);
          }
          else {
            menu.push(["Show Grid", function ($itemScope, $event, value) { $scope.OnShowHideGrid(); }, function ($itemScope, $event) { return !$scope.SelectedNodes(); }]);
          }

          if ($scope.debug_mode == true) {
            menu.push(["Hide Debug Information", function ($itemScope, $event, value) { $scope.OnShowHideDebugInformation(); }, function ($itemScope, $event) { return !$scope.SelectedNodes(); }]);
          }
          else {
            menu.push(["Show Debug Information", function ($itemScope, $event, value) { $scope.OnShowHideDebugInformation(); }, function ($itemScope, $event) { return !$scope.SelectedNodes(); }]);
          }

          menu.push(["Save as Image...", function ($itemScope, $event, value) { $scope.OnSaveCanvasAsAnImage() }, function ($itemScope, $event) { return !$scope.SelectedNodes(); }]);

          menu.push(null);
          menu.push(["Zoom >", function ($itemScope) {}, [
            ['Increase', function ($itemScope) { $scope.ZoomUp(); }],
            ['Reduce', function ($itemScope) { $scope.ZoomDown(); }]
          ]]);

          menu.push(null);
          menu.push(["View Source Code...", function ($itemScope, $event, value) { $scope.OnGetCode() }, function ($itemScope, $event) { return !$scope.SelectedNodes(); }]);

        }
      }

      return menu;
    };

    $scope.RefreshNVD3ChartByTabId = function(tab_id) {
      var interval_id = setInterval(function() {
        clearInterval(interval_id);

        // get the tab by its id
        var tab = arrays.FindArrayElementById($scope.GetOutputsNavTabs().list, tab_id);

        if ((tab != null) && (tab.node != null)) {
          // loop charts searching for the chart related with the tab node
          for (i = 0; i < $scope.charts.length; i++) {
            if (tab.node.id == $scope.charts[i].id) { // $scope.charts[i].id is the node id
              // found the chart related with the tab_id

              if ($scope.charts[i].type == "boxplot") {
                if (($scope.charts[i].api_content != null) &&
                    ($scope.charts[i].api_content.api != undefined)) {
                  $scope.charts[i].api_content.api.refresh();
                }
              }
            }
          }
        }
      }, 100);
    };

    $scope.OnNodeGraphSelected = function(node_id) {
      var tab = FindTabByNodeId($scope.GetOutputsNavTabs(), node_id);
      if (tab != null) {
          $scope.OnOutputTabPress($scope.GetOutputsNavTabs(), tab.id);
          $scope.RefreshNVD3ChartByTabId(tab.id);
/*
*/

/*
if(!$scope.$$phase) {
  $scope.DoApply();
}
*/
          //$scope.DoApply();
//          var graph = document.getElementById("graph_" + node_id);
//          if (graph != null) {
//            $scope.DoApply();
//          }
      }
    };

    // =========================================================================
    // EXPERIMENTS DATA CHARTS
    // =========================================================================
    $scope.charts = [];           // filters defined for this list (chart.js & boxplot.js)
    $scope.consoles = [];
    $scope.stdout_original = "";  // The original one
    $scope.stdout = "";           // The colorized one

    ////////////////////////////////////////////////////////////////////////////
    // DOCUMENT TABS / OUTPUT TABS
    ////////////////////////////////////////////////////////////////////////////

    var MAX_TABS = 5;    

    $scope.GetOutputsNavTabs = function() {
        // Select the output navtab using the document id:
        var nav_tab = null;

        if ($scope.DocsNavTabs.selected_tab != null) {
            nav_tab = arrays.FindArrayElementById($scope.NavTabs,
                                                  $scope.DocsNavTabs.selected_tab.id);
        }
        return nav_tab;
    };

    function GetCurrentDocument() {
        return $scope.DocsNavTabs.selected_tab; // $scope.DocsNavTabs.list[$scope.DocsNavTabs.selected_id];
    };

    function GetCurrentDocumentZoom() {
      var ret = 1;
      if ($scope.DocsNavTabs.selected_tab != null) {
          if (($scope.DocsNavTabs.selected_tab.page.zoom.current == undefined) || ($scope.DocsNavTabs.selected_tab.page.zoom.current == null)) {
            $scope.DocsNavTabs.selected_tab.page.zoom.previous = 100;
            $scope.DocsNavTabs.selected_tab.page.zoom.current = 60;
          }
          ret = $scope.DocsNavTabs.selected_tab.page.zoom.current * 1;
      }
      return ret;
    };

    function GetPreviousDocumentZoom() {
      var ret = 1;
      if ($scope.DocsNavTabs.selected_tab != null) {
          if (($scope.DocsNavTabs.selected_tab.page.zoom.previous == undefined) || ($scope.DocsNavTabs.selected_tab.page.zoom.previous == null)) {
            $scope.DocsNavTabs.selected_tab.page.zoom.previous = 100;
          }
          ret = $scope.DocsNavTabs.selected_tab.page.zoom.previous * 1;
      }
      return ret;
    };

    function SetCurrentDocumentZoom(value) {
      if ($scope.DocsNavTabs.selected_tab != null) {
          $scope.DocsNavTabs.selected_tab.page.zoom.previous = GetCurrentDocumentZoom();
          $scope.DocsNavTabs.selected_tab.page.zoom.current = Math.round(value,1) * 1;
      }
    };



    function GetCurrentDocumentNodes() {
        if (GetCurrentDocument() != null)
          return GetCurrentDocument().nodes;
      return null;
    };

    $scope.DocsNavTabs = {
        id: 0,
        index: 0,
        selected_tab: null,
        next_id: 1,
        list: [
          {
            id: 0,
            properties: {
              type:    $scope.FileType.EXPERIMENT,
              name:    "Unsaved Experiment 1",
              email:   "",
              date:    "",
              description: ""
            },
            visible: true,
            nodes: [],
            next_id: 0,
            saved: false,
            page: {
              width: 2000, //current_theme.DRAWING_WIDTH,
              height: 1400, //current_theme.DRAWING_HEIGHT
              zoom: {
                current: 60,
                previous: 100
              },
              CanvasPosition: {
                x:-20,
                y:-40
              }
            }
          }
        ]
    };

    $scope.DocsNavTabs.selected_tab = $scope.DocsNavTabs.list[0];

    $scope.NavTabs = [
      {
          id: 0,
          index: 0,
          selected_tab: null,
          list: [],
          next_id: 0
      }
    ];

    function AddNavTabs(id) {
        var new_experiment_outputs_nav_tabs = {
            id: id,
            index: 0,
            selected_tab: null,
            list: [],
            next_id: 0
        };

        $scope.NavTabs.push(new_experiment_outputs_nav_tabs);
    };

    function RemoveNavTabs(id) {
        arrays.RemoveElementById($scope.NavTabs, id);    
    };

    // data must be a json object with the field "id:null, name:xxxx"
    function AddTab(nav_tabs, data) {
      var new_tab = {
        "id": nav_tabs.next_id
      };

      for(var key in data) {
        if(data.hasOwnProperty(key)){
          new_tab[key] = data[key];
        }
      }

      nav_tabs.next_id++;
 
      nav_tabs.list.push(new_tab);

      nav_tabs.selected_tab = new_tab; // Select just created tab
    };

    function RemoveTab(nav_tabs, id) {
        // Decide which tab has to be selected after tab removal:
        if (nav_tabs.list.length > 1) {
            if (nav_tabs.selected_tab.id == id) { // Remove the selected tab
                var index_to_remove = arrays.FindArrayElementIndexById(nav_tabs.list, id);
                if (index_to_remove > 0) { // [A][SX][][][]    S=selected X=delete A=To Be Selected
                    // Select the tab of the left:
                    nav_tabs.selected_tab = nav_tabs.list[index_to_remove-1];
                } else {
                    // [SX][A][][][]    S=selected X=delete A=To Be Selected
                    nav_tabs.selected_tab = nav_tabs.list[index_to_remove+1];
                }
                // Tab selection has been changed, so:
                // DecideEditorType("CURRENT_TAB");

            } else {  // Remove another tab
                // Do not change the selected tab
            }
        } else {
            // Empty nav_tabs
            nav_tabs.selected_tab = null;
        }

        arrays.RemoveElementById(nav_tabs.list, id);
        SetVisibleTabs(nav_tabs);
    };

    function CreateOutputTab(node) {
        // Output tabs have a pointer to the related node and a pointer to the output.
        // For example, a boxplot node has a node related with and the output graph.
        var output_tab_name = node.type; //.toUpperCase()); // + ": " + node.id); //;
        AddTab($scope.GetOutputsNavTabs(),
               {
                 "name": output_tab_name,
                 "node": node,
                 "output": null
               });
    };


    function FindTabByNodeId(nav_tabs, id) {
        var tab = null;
        for (var i = 0; ((i < nav_tabs.list.length) &&
                         (tab == null)); i++) {
            if ((nav_tabs.list[i].node != null) && (nav_tabs.list[i].node.id == id)) {
                tab = nav_tabs.list[i]; 
            }
        }
        return tab;
    };

    function RemoveOutputTab(node) {
        // Find the output tap with data.node.id == node.id and remove that tab
        var tab = FindTabByNodeId($scope.GetOutputsNavTabs(), node.id);
        if (tab != null) {
            RemoveTab($scope.GetOutputsNavTabs(), tab.id);
        }
    };

    function SelectTab(nav_tabs, id) {
        nav_tabs.selected_tab = arrays.FindArrayElementById(nav_tabs.list, id);
    };

    function FindTabByName(name) {
      var found = -1;
      for (var i = 0; ((i < $scope.DocsNavTabs.list.length) && (found == -1)); i++) {
        if ($scope.DocsNavTabs.list[i].properties.name == name) {
          found = i;
        }
      }

      return found;
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    function CreateEmptyDocument() {
      var tab_name;
      var properties;

      switch($scope.GetEditorType()) {
        case $scope.FileType.EXPERIMENT:
          tab_name = "Unsaved Experiment ";
          tab_name += ($scope.DocsNavTabs.next_id + 1);

          properties = {
            type:    $scope.GetEditorType(),
            name:    tab_name,
            email:   "",
            date:    "",
            description: ""
          };


          break;
        case $scope.FileType.PIPELINE:
          tab_name = "Unsaved Pipeline ";
          tab_name += ($scope.DocsNavTabs.next_id + 1);

          properties = {
            type:    $scope.GetEditorType(),
            name:    tab_name,
            email:   "",
            date:    "",
            description: "",
            inputs:  "",
            outputs: "",
            loop_name: ""
          };

          break;
      }

      AddTab($scope.DocsNavTabs, 
      { 
        properties: properties,
        visible: true,
        nodes: [],
        next_id: 0,
        saved: false,
        page: { 
          width: current_theme.DRAWING_WIDTH,
          height: current_theme.DRAWING_HEIGHT,
          zoom: {
            current: 60,
            previous: 100
          },
          CanvasPosition: {
            x:-20,
            y:-40
          }
        }
      });
      AddNavTabs($scope.DocsNavTabs.next_id-1);

      //if ($scope.GetEditorType() == $scope.FileType.EXPERIMENT) {
        // Create the console tab        
        AddTab($scope.GetOutputsNavTabs(),
        {
          name:   "Console",
          node:   null,
          output: null
        });
      //}

      DrawScene();
    };

    $scope.OnNew = function() {
      CreateEmptyDocument();

      if ($scope.GetEditorType() == $scope.FileType.PIPELINE) {
        CreatePipelineDefaultNodes();
      }
    };

    function CreatePipelineDefaultNodes() { 
      if ($scope.GetEditorType() == $scope.FileType.PIPELINE) {
        CreateNode(null, true, 'input', 200, 100, 'Foreach', null);
        CreateNode(null, true, 'foreach_value', 200, 200, '', null);
        CreateNode(null, true, 'foreach_iteration', 200, 300, '', null);

        SetNodesTheme();
      }
      DrawScene();
    };

    function UnselectPreviousDocumentObjects() {
      // Unselect objects from previous document:
      $scope.node_selected = null;
      $scope.connector_selected = null;
    };

    function LoadPipeline(id) {
        console.log("** LoadPipeline() **");

          var send = {
            method: 'GET',
            url: $rootScope.webAddress + 'repository_pipelines/' + id,
            headers: { 'Content-Type': 'application/json' },
            data: {}
          };

          $rootScope.Http(send,
          function(message) {

            if (GetCurrentDocumentNodes().length != 0) {
              CreateEmptyDocument();
            }

            message.data.data.nodes.forEach(function (node) {
              CreateNode(node.id, node.enabled, node.type, node.x, node.y, node.value, node.outputs);
            });

            GetCurrentDocument().properties = message.data.data.properties;
            GetCurrentDocument().saved = true; // The pipeline is just loaded, so, it is saved.

            SetNodesTheme();
            DrawScene(); // The first time calculates page dimensions
            DrawScene(); // Do it again with correct page dimensions

            OnResize();

          },
          function(message) {
            console.log("****** LoadPipeline() ERROR");
          });
    };

    $scope.OnRemoveExperiment = function(experiment_id) {
      console.log("** OnRemoveExperiment() **");

      MessagesFactory.confirm("Remove the experiment?", 
      function() {  // Yes
        var send = {
          method: 'DELETE',
          url: $rootScope.webAddress + 'experiments/' + experiment_id,
          headers: { 'Content-Type': 'application/json' },
          data: {}
        };

        $rootScope.Http(send,
        function(message) {
          // $rootScope.OnRefreshExperimentsList(); <-- this event is already fired by the LocalManager

          $scope.ClearExperimentOutputs();
        },
        function(message) {
          console.log("****** OnRemoveExperiment() ERROR");
        });
      },
      function() {  // No
      });
    };

    function LoadExperiment(id) {
      console.log("** LoadExperiment() **");

      var pipeline_tab_id = FindTabByName(id);
      if (pipeline_tab_id == -1) {
        var send = {
          method: 'GET',
          url: $rootScope.webAddress + 'repository_experiments/' + id,
          headers: { 'Content-Type': 'application/json' },
          data: {}
        };

        $rootScope.Http(send,
        function(message) {
          if (GetCurrentDocumentNodes().length != 0) {
            CreateEmptyDocument();
          }

          message.data.data.nodes.forEach(function (node) {
            CreateNode(node.id, node.enabled, node.type, node.x, node.y, node.value, node.outputs);
          });

          GetCurrentDocument().properties = message.data.data.properties;
          GetCurrentDocument().saved = true; // The experiment is just loaded, so, it is saved.
          
          SetNodesTheme();

          DrawScene(); // The first time calculates page dimensions
          DrawScene(); // Do it again with correct page dimensions

          OnResize();
          DrawScene(); // Do it again with correct page dimensions

        },
        function(message) {
          console.log("****** LoadExperiment() ERROR");
        });
      } else {
        $scope.OnTabPress($scope.DocsNavTabs, pipeline_tab_id); // Select the tab
      }
    };


    $scope.OnLoad = function() {
      switch($scope.GetEditorType()) {
        case $scope.FileType.EXPERIMENT:
          GetStoredExperimentsList();
          break;
        case $scope.FileType.PIPELINE:
          GetStoredPipelinesList();
          break;
      }
    };


    // User selects an Experiment Tab
    $scope.OnTabPress = function(nav_tabs, id) {
        SetNodeValueFromTextInput(true);

        SelectTab(nav_tabs, id);
        DrawScene();

        $scope.DoZoom(); // This function does the zoom but it also ensures that the canvas position is in its place.
    };

    function CloseDocument(id) {
      RemoveTab($scope.DocsNavTabs, id);
      RemoveNavTabs(id);

      if($scope.DocsNavTabs.list.length == 0) {
          // Ensure at least one document:
          $scope.OnNew();
          // CreatePipelineDefaultNodes();
      }

      DrawScene();
    };

    // User presses the little tab button
    $scope.OnCloseDocument = function(id) {
      if (($scope.DocsNavTabs != null) &&
          ($scope.DocsNavTabs.selected_tab != null) &&
          ($scope.DocsNavTabs.selected_tab.saved == false)) {
        MessagesFactory.confirm("Close without saving the document?", 
        function() {  // Yes
          CloseDocument(id);
        },
        function() {  // No
        });
      } else {
        CloseDocument(id);
      }
    };

    $scope.OnSaveCanvasAsAnImage = function() {
      // Remove the grid temporaly
      $scope.aux_prev_show_grid = $scope.ShowGrid;
      $scope.aux_prev_paint_page_borders = $scope.paint_page_borders;

      $scope.aux_canvas_width  = $scope.canvas.width;
      $scope.aux_canvas_height = $scope.canvas.height;

      $scope.canvas.width  = GetCurrentDocument().page.width;
      $scope.canvas.height = GetCurrentDocument().page.height;

      $scope.ShowGrid = false;
      $scope.paint_page_borders = false;

      DrawScene();

      $scope.canvas.toBlob(function(blob) {
          var doc = GetCurrentDocument();

          saveAs(blob, doc.properties.name + ".png");

          // Restore the grid to its previous state:
          $scope.canvas.width = $scope.aux_canvas_width;
          $scope.canvas.height = $scope.aux_canvas_height;
          $scope.ShowGrid = $scope.aux_prev_show_grid;
          $scope.paint_page_borders = $scope.aux_prev_paint_page_borders;

          $scope.DoZoom(); // DrawScene is called. And canvas is restored with previous size.

          //DrawScene();
          $scope.aux_prev_show_grid = undefined;
          $scope.aux_prev_paint_page_borders = undefined;
          $scope.aux_canvas_width  = undefined;
          $scope.aux_canvas_height = undefined;
      });
    };

    $scope.OnSaveOutput = function(type, node_id) {
      var doc = GetCurrentDocument();
      var file_name = "";
      var text = "";
      
      if (type == 'LOG') {
        // save the Console output
        text = $scope.stdout_original;
        file_name = doc.properties.name + ".log";
      } else {
        if (type == 'CSV') {
            // save the R Export output
            text = arrays.FindArrayElementById($scope.consoles, node_id).data;
            file_name = doc.properties.name + " - R Export.csv";
        }
        if (type == 'TXT') {
            // save the Print Data output
            text = arrays.FindArrayElementById($scope.consoles, node_id).data;
            file_name = doc.properties.name + " - Data.txt";
        }
        if (type == 'NGASP_SCRIPT') {
            // save ngasp script
            text = '';

            text_aux = $scope.stdout_original;  // The original because it is the source code without color tags
            file_name = doc.properties.name + ".ngasp";

            while(text_aux != '') {
                var line = text_aux.substr(0, text_aux.indexOf("<br />"));
                text_aux = text_aux.substr(text_aux.indexOf("<br />") + 6); // 6 is br length

                if ((line != '') && (line.indexOf("$") == 0)) {  // dollard at the begining of the line
                  text += line.substr("$".length);
                  text += "<br />";
                }               
            }
        }
      }

      text = ReplaceAll(text, "&nbsp;", " ");
      text = ReplaceAll(text, "<br />", "\n");

      var blob = new Blob([text], {type: "text/plain;charset=utf-8"});
      saveAs(blob, file_name);
    }


    // Tabs LEFT Button Pressed
    $scope.OnNavTabsLeftArrowPressed = function(nav_tabs) {
        if (nav_tabs.index > 0) {
            nav_tabs.index--;
        }
        SetVisibleTabs(nav_tabs);
        
    };

    // Tabs RIGHT Button Pressed
    $scope.OnNavTabsRightArrowPressed = function(nav_tabs) {
        if (nav_tabs.index + MAX_TABS < nav_tabs.list.length) {
            nav_tabs.index++;
        }
        SetVisibleTabs(nav_tabs);
    };

    // Decide visible tabs from nav_tabs.list
    function SetVisibleTabs(nav_tabs) {
        for (var i = 0; i < nav_tabs.list.length; i++) {
            nav_tabs.list[i].visible = ((i >= nav_tabs.index) &&
                                        (i <= nav_tabs.index + MAX_TABS));
        }
    };

    // Decide if LEFT Button must be shown
    $scope.ShowNavTabsLeftArrow = function(nav_tabs) {
        return ((nav_tabs != null) && (nav_tabs.index != 0));
    };

    // Decide if RIGHT Button must be shown
    $scope.ShowNavTabsRightArrow = function(nav_tabs) {
        return ((nav_tabs != null) && (nav_tabs.index + MAX_TABS < nav_tabs.list.length));
    };


    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    var fonts = {
        NodeTitle: "10pt robotobold",
        ConnectorName: "11pt robotoregular", /* pt otherwise GetWiderText does not work properly */
        NodeValue: "11pt robotoregular",
        Comment: "italic 12pt arial",
        Default: "20pt robotobold",
        PageHeaderLabel: "14pt robotoregular",
        PageHeaderName:   "17pt robotobold",
        PageHeaderAuthor: "15pt robotoregular", // robotoitalic
        PageHeaderText:   "14pt robotoregular",
        HelpText: "12pt robotoregular",
        HelpTextBold: "12pt robotobold"
    };


    // DinA4
    $scope.paper = {
        width: 3508,
        height: 2480
    };
    var num_papers = {
        x: 3,
        y: 3
    }
    $scope.paper = {
        width: 3508,
        height: 2480
    };

    $scope.NodeStyle = { // Must be consecutive numbers (for accessing an array). They are defined in the CM, too. They must match!
        CALCULATION_NODE:     0,
        INPUT_NODE:           1,
        OUTPUT_NODE:          2,
        GRAPH_NODE:           3,
        DATA_NODE:            4,
        PIPELINE_NODE:        5,
        NULL_CONNECTION:      6,
        COMMENT_NODE:         7,
        EXTERNAL_VIEWER_NODE: 8
    };
    $scope.mouse_x = 0;
    $scope.mouse_y = 0;
    $scope.input_visible = false;
    var node_selected_for_write = null;

    $scope.data_files = [];

    $scope.node_types = [];

    function InitializeNodeTypes() {
      // These id are unique
      $scope.node_types = [
        {
            id: 'input',
            style: $scope.NodeStyle.INPUT_NODE,
            inputs: [
            ],
            outputs: [
                { id: 0, name: "", type: "input" },
            ],
        },
        {
            id: 'output',
            style: $scope.NodeStyle.OUTPUT_NODE,
            inputs: [
                { id: 0, name: "", type: "output" },
            ],
            outputs: [
            ],
        },
        {
            id: 'foreach_value',
            style: $scope.NodeStyle.DATA_NODE,
            inputs: [
            ],
            outputs: [
                { id: 0, name: "", type: "string" },
            ],
        },
        {
            id: 'foreach_iteration',
            style: $scope.NodeStyle.DATA_NODE,
            inputs: [
            ],
            outputs: [
                { id: 0, name: "", type: "int" },
            ],
        },
        {
            id: 'output',
            style: $scope.NodeStyle.OUTPUT_NODE,
            inputs: [
                { id: 0, name: "", type: "output" },
            ],
            outputs: [
            ],
        },
        /*{
            id: 'console',
            style: $scope.NodeStyle.GRAPH_NODE,
            inputs: [
            ],
            outputs: [
            ],
        },*/
        {
            id: 'comment',
            style: $scope.NodeStyle.COMMENT_NODE,
            inputs: [
            ],
            outputs: [
            ],
        },
        {
            id: 'R Export',
            style: $scope.NodeStyle.GRAPH_NODE,
            inputs: [
                { id: 0, name: "data", type: "double_vector", accumulative: true },
            ],
            outputs: [
            ],
        },
        {
            id: 'TFA Viewer',
            style: $scope.NodeStyle.EXTERNAL_VIEWER_NODE,
            inputs: [
                { id: 0, name: "TFA (gz)", type: "tfa_file", accumulative: false },
                { id: 1, name: "GFF", type: "gff_file", accumulative: false },
                { id: 2, name: "Weights", type: "weights_file", accumulative: false },
                { id: 3, name: "Statistics", type: "text_file", accumulative: false },
            ],
            outputs: [
            ],
        },
        {
            id: 'chart',
            style: $scope.NodeStyle.GRAPH_NODE,
            inputs: [
                // If the graph node needs floating point values then use 
                // double_vector instead of float. Because data could come
                // from 1, 2, 4 and 8 bits and it is better to get data using 
                // a big data type. Double is 8 bit.
                { id: 0, name: "data", type: "double_vector", accumulative: true },
                // { id: 1, name: "labels", type: "string_vector", accumulative: true },
                // { id: 2, name: "series", type: "string_vector", accumulative: true },
            ],
            outputs: [
            ],
        },
        {
            id: 'Print Data',
            style: $scope.NodeStyle.GRAPH_NODE,
            inputs: [
                { id: 0, name: "data", type: "string_vector", accumulative: true },
            ],
            outputs: [
            ],
        },
        {
            id: 'boxplot',
            style: $scope.NodeStyle.GRAPH_NODE,
            inputs: [
                { id: 0, name: "data", type: "double_vector", accumulative: true },
                /*{ id: 0, name: "Label", type: "string", accumulative: true },
                { id: 1, name: "Q1", type: "double", accumulative: true },
                { id: 2, name: "Median", type: "double", accumulative: true },
                { id: 3, name: "Q3", type: "double", accumulative: true },
                { id: 4, name: "Min", type: "double", accumulative: true },
                { id: 5, name: "Max", type: "double", accumulative: true },
                { id: 6, name: "Outliers", type: "double_vector", accumulative: true }*/
            ],
            outputs: [
            ],
        },
        /*{
            id: 'donutchart',
            style: $scope.NodeStyle.GRAPH_NODE,
            inputs: [
                { id: 0, name: "data", type: "string", accumulative: true }
            ],
            outputs: [
            ],
        },*/
      ];
    };
    InitializeNodeTypes();



    ////////////////////////////////////////////////////////////////////////////
    // INIT
    ////////////////////////////////////////////////////////////////////////////

    $scope.IconImage = {
        ICON_INPUT:           $scope.NodeStyle.INPUT_NODE,
        ICON_CALCULATION:     $scope.NodeStyle.CALCULATION_NODE,
        ICON_COMMENT:         $scope.NodeStyle.COMMENT_NODE,
        ICON_OUTPUT:          $scope.NodeStyle.OUTPUT_NODE,
        ICON_GRAPH:           $scope.NodeStyle.GRAPH_NODE,
        ICON_GRAPH:           $scope.NodeStyle.EXTERNAL_VIEWER_NODE, //-------------------------------------------------------------------------------------------------------------------------------
        ICON_DATA:            $scope.NodeStyle.DATA_NODE,
        ICON_DM:              $scope.NodeStyle.DATA_NODE,
        ICON_NULL_CONNECTION: $scope.NodeStyle.NULL_CONNECTION,
        ICON_PIPELINE:        $scope.NodeStyle.PIPELINE_NODE,
        ICON_BACKGROUND:      100,
        IMAGE_NODE_CONSOLE:   110,
        IMAGE_NODE_CHART:     111,
        IMAGE_NODE_BOXPLOT:   112,
        IMAGE_NODE_DONUTCHART:113,
        IMAGE_NODE_EXPORT:    114,
        IMAGE_TFA_VIEWER:     118,
        IMAGE_NODE_PRINT_DATA:117,
        IMAGE_PIPELINE_LOOP:  115,
        IMAGE_PIPELINE_LOOP_BLACK:  116,
        IMAGE_NODE_BOOL_ON:   200,
        IMAGE_NODE_BOOL_OFF:  201
    };
    
    $scope.GetEditorType = function() {
      var type = $scope.FileType.UNDEFINED;

      if ((GetCurrentDocument() != null) &&
          (GetCurrentDocument().properties != null)
          ) {
        type = GetCurrentDocument().properties.type;
      } else {
        if ($state.includes("experiment_editor") == true) {
          type = $scope.FileType.EXPERIMENT;
        } else {
          if ($state.includes("pipeline_editor") == true) {
            type = $scope.FileType.PIPELINE;
          }
        }
      }

      return type;
    };

    $scope.init = function () {
console.log("** Init 1 Start **");
        //panel_general = document.getElementById("panel_general");
        //$scope.canvas = panel_general.children[0].getElementById("myCanvas");
        $scope.canvas = document.getElementById("myCanvas");
        $scope.ctx = $scope.canvas.getContext("2d");

        // Load Images:
        num_images_loaded = 18;
    
        images.push({id: $scope.IconImage.ICON_INPUT,
                     image: document.getElementById("input_icon") });
        images.push({id: $scope.IconImage.ICON_CALCULATION,
                     image: document.getElementById("fx_icon") });
        images.push({id: $scope.IconImage.ICON_OUTPUT,
                     image: document.getElementById("output_icon") });
        images.push({id: $scope.IconImage.ICON_BACKGROUND,
                     image: document.getElementById("background_icon") });
        images.push({id: $scope.IconImage.ICON_GRAPH,
                     image: document.getElementById("graph_icon") });
        images.push({id: $scope.IconImage.ICON_DATA,
                     image: document.getElementById("data_icon") });
        images.push({id: $scope.IconImage.ICON_NULL_CONNECTION,
                     image: document.getElementById("null_connection") });
        images.push({id: $scope.IconImage.ICON_DM,
                     image: document.getElementById("dm_icon") });
        images.push({id: $scope.IconImage.ICON_PIPELINE,
                     image: document.getElementById("pipeline_icon") });
        images.push({id: $scope.IconImage.IMAGE_NODE_BOOL_ON,
                     image: document.getElementById("bool_on") });
        images.push({id: $scope.IconImage.IMAGE_NODE_BOOL_OFF,
                     image: document.getElementById("bool_off") });
        images.push({id: $scope.IconImage.IMAGE_NODE_CONSOLE,
                     image: document.getElementById("node_console") });
        images.push({id: $scope.IconImage.IMAGE_NODE_CHART,
                     image: document.getElementById("node_chart") });
        images.push({id: $scope.IconImage.IMAGE_NODE_PRINT_DATA,
                     image: document.getElementById("node_print_data") });
        images.push({id: $scope.IconImage.IMAGE_NODE_BOXPLOT,
                     image: document.getElementById("node_boxplot") });
        images.push({id: $scope.IconImage.IMAGE_NODE_DONUTCHART,
                     image: document.getElementById("node_donutchart") });
        images.push({id: $scope.IconImage.IMAGE_NODE_EXPORT,
                     image: document.getElementById("node_export") });
        images.push({id: $scope.IconImage.IMAGE_TFA_VIEWER,
                     image: document.getElementById("tfa_viewer") });
        images.push({id: $scope.IconImage.IMAGE_PIPELINE_LOOP,
                     image: document.getElementById("loop") });
        images.push({id: $scope.IconImage.IMAGE_PIPELINE_LOOP_BLACK,
                     image: document.getElementById("loop_black") });
        images.push({id: $scope.IconImage.ICON_COMMENT,
                     image: document.getElementById("comment_icon") });


        // -------------------------------------------------------------------------
        // DRAG & DROP FILE NAMES
        // -------------------------------------------------------------------------
        $scope.canvas.addEventListener('dragover', function(e) {
            e.stopPropagation();
            e.preventDefault();
            e.dataTransfer.dropEffect = 'copy';
        });
        $scope.canvas.addEventListener('drop', function(e) {
            e.stopPropagation();
            e.preventDefault();
            var files = e.dataTransfer.files;

            GetCurrentDocumentNodes().forEach(function(node) {
                if ((node.selected == true) && 
                    (node.temp.type_obj.style == $scope.NodeStyle.DATA_NODE) &&
                    (node.type != 'bool') &&
                    (node.type != 'foreach_iteration') &&
                    (node.type != 'foreach_value')) {

                    node.value = files[0].name;
                    DrawScene();
                }
            });
        });


try {
    var isFileSaverSupported = !!new Blob;
} catch (e) {}

console.log("** Init 1 End **");
	};

    // This init is started when all images are loaded:
	$scope.init2 = function () {
console.log("** Init 2 Start **");
        num_data_resources_loaded = 5;

        GetCalculationsList($scope.DataResourceLoad());
        GetCommandsList($scope.DataResourceLoad());
        GetDataFilesList($scope.DataResourceLoad());
        GetDataTypesList($scope.DataResourceLoad());
        AddPipelinesToNodeTypes($scope.DataResourceLoad());
console.log("** Init 2 End **");
	};


    function OnResize() {
      console.log("resize()");

      // It Adapts the canvas to the size of the window.
      // A big canvas is slower than an small one. 
      $scope.canvas.width  = window.innerWidth;
      $scope.canvas.height = window.innerHeight - 80;

      // Previous lines restores the original size of the painting. So, the previous zoom must be set to 100%.
      if ($scope.DocsNavTabs.selected_tab != null) {
          $scope.DocsNavTabs.selected_tab.page.zoom.previous = 100;
      }

      // Page width per zoom cannot be larger that the window width. It means that, zoom * page_width = window_width. 
      // So, zoom = window_width / page_width
      var sidebar_pos = document.getElementById('sidebar-resizer').style.left;
      if (sidebar_pos != undefined) {
        if (sidebar_pos != "") {
            $scope.ResetCanvasMovement();
            console.log("sidebar_pos = " + sidebar_pos);
            sidebar_pos = sidebar_pos.replace("px", "");
            console.log("sidebar_pos = " + sidebar_pos);
            sidebar_pos *= 1;
            var windows_width = sidebar_pos;
            console.log("windows_width = " + windows_width);
            $scope.DocsNavTabs.selected_tab.page.zoom.current =  (windows_width  / $scope.DocsNavTabs.selected_tab.page.width) * 100;
            $scope.DoApply();
        }
      }



      $scope.DoZoom(); // DrawScene is called.
    };

/*
$scope.ResizeGraph = function() {
  console.log("pipelineEditorController - $scope.ResizeGraph()");
OnResize();
    var graph_canvas = angular.element("_");


};
*/

    // This init is started when all data resources are loaded:
	$scope.init3 = function () {
console.log("** Init 3 Start **");
        current_theme = themes[$rootScope.theme_id_selected];
        SetNodesTheme();

        DrawScene();
        SetCanvasEvents();

        var the_browser_window = angular.element($window);
        the_browser_window.bind('resize', OnResize);

        OnResize();

console.log("** Init 3 End **");


        // ============================================
        // EXPERIMENTS INIT
        // ============================================

        // Default values.
        // When the user selectes an experiment from the table, this
        // variable will be a pointer to the row:
/*        $scope.selected_experiment = {
    		  experiment_id: '',
          name: '',
          status: '',
          lm_id: null,
          exec_data: {
            num_instructions: 0,
            executed_instructions: 0,
            job_done: 0
          }
        };
*/
		    $scope.cmd = "";
		    $scope.show_new_experiment = false;
		    $scope.new_experiment_message = "";

		    $scope.show_query_experiment = false;
		    $rootScope.OnRefreshExperimentsList();

        // Create the console tab        
        AddTab($scope.GetOutputsNavTabs(),
               {
                 name:   "Console",
                 node:   null,
                 output: null
               });

        CreateGraphs();
	};

    $scope.ImageLoad = function() {
        num_images_loaded--;
        if (num_images_loaded == 0) {
            $scope.init2();
        }
    };

    $scope.DataResourceLoad = function() {
        num_data_resources_loaded--;
        if (num_data_resources_loaded == 0) {

// var mstatspop = arrays.FindArrayElementById($scope.node_types, 'mstatspop');
// console.log(JSON.stringify(mstatspop));

            $scope.init3();
        }
    };


    function GetDataFilesList(OnReceived) {
console.log("** GetDataFilesList() **");
        $rootScope.Http({
		        method: 'GET',
		        url: $rootScope.webAddress + 'datafiles',
		        headers: { 'Content-Type': 'application/json' },
		        data: {
		        },
        },
        function(message) {
            var result = message.data.data;

            $scope.data_files = [];

            result.forEach(function (datafile_def) {
                var new_data_file = {
                    location: datafile_def.location,
                    filename: datafile_def.filename
                };

                $scope.data_files.push(new_data_file);
            });

            if ((OnReceived != undefined) && (OnReceived != null)) {
                OnReceived();
            }
        },
        function(message) {
	        $scope.new_experiment_message = JSON.stringify(message);
console.log("** GetDataFilesList() Error **" + $scope.new_experiment_message);
        });
    };




    function GetDataTypesList(OnReceived) {
console.log("** GetDataTypesList() **");
        $rootScope.Http({
		        method: 'GET',
		        url: $rootScope.webAddress + 'datatypes',
		        headers: { 'Content-Type': 'application/json' },
		        data: {
		        },
        },
        function(message) {
            var result = JSON.parse(message.data.data.result);

            result.datatypes.forEach(function (datatype_def) {
                var new_data_node = {
                    id: datatype_def.id,
                    style: $scope.NodeStyle.DATA_NODE,
                    inputs: [{ id: 0, name: "", type: datatype_def.id }],
                    outputs: [{ id: 0, name: "", type: datatype_def.id }]
                };

                $scope.node_types.push(new_data_node);
            });

            // Adding the "null" type:
            var new_data_node = {
                id: "null_connection",
                style: $scope.NodeStyle.NULL_CONNECTION,
                inputs: [{ id: 0, name: "", type: "null_connection" }],
                outputs: [{ id: 0, name: "", type: "null_connection" }]
            };


            $scope.node_types.push(new_data_node);

            if ((OnReceived != undefined) && (OnReceived != null)) {
                OnReceived();
            }
        },
        function(message) {
	        $scope.new_experiment_message = JSON.stringify(message);
console.log("** GetDataTypesList() Error **" + $scope.new_experiment_message);
        });
    };

    function GetCalculationsList(OnReceived) {
console.log("** GetCalculationsList() **");
        $rootScope.Http({
		        method: 'GET',
		        url: $rootScope.webAddress + 'calculations',
		        headers: { 'Content-Type': 'application/json' },
		        data: {
		        },
        },
        function(message) {
            var result = JSON.parse(message.data.data.result);

            result.calculations.forEach(function (calc_def) {
                calc_def.style = $scope.NodeStyle.CALCULATION_NODE;
                $scope.node_types.push(calc_def);
            });

            if ((OnReceived != undefined) && (OnReceived != null)) {
                OnReceived();
            }
        },
        function(message) {
console.log("** GetCalculationsList() Error **");
        });
    };

    function GetCommandsList(OnReceived) {
console.log("** GetCommandsList() **");
        $rootScope.Http({
		        method: 'GET',
		        url: $rootScope.webAddress + 'commands',
		        headers: { 'Content-Type': 'application/json' },
		        data: {
		        },
        },
        function(message) {
            var result = JSON.parse(message.data.data.result);

            result.commands.forEach(function (calc_def) {
                commands_list.push(calc_def);
            });

            if ((OnReceived != undefined) && (OnReceived != null)) {
                OnReceived();
            }
        },
        function(message) {
console.log("** GetCommandsList() Error **");
        });
    };

    function AddPipelinesToNodeTypes(OnReceived) {
      console.log("** AddPipelinesToNodeTypes() **");
      $rootScope.Http({
        method: 'GET',
        url: $rootScope.webAddress + 'repository_pipelines',
        headers: { 'Content-Type': 'application/json' },
        data: {
        },
      },
      function(message) {
        console.log("+++"+JSON.stringify(message.data));

        // Remove pipeline types from the $scope.node_types list:

        // Add pipeline node types to the list:
        message.data.data.forEach(
          function (pipeline) {
            pipeline.style = $scope.NodeStyle.PIPELINE_NODE; 
            $scope.node_types.push(pipeline);
          }
        );  

        if ((OnReceived != undefined) && (OnReceived != null)) {
            OnReceived();
        }
      },
      function(message) {
        console.log("** AddPipelinesToNodeTypes() Error **");
      });    
    };

    function GetStoredPipelinesList() {
      console.log("** GetStoredPipelinesList() **");
      $rootScope.Http({
        method: 'GET',
        url: $rootScope.webAddress + 'repository_pipelines',
        headers: { 'Content-Type': 'application/json' },
        data: {
        },
      },
      function(message) {
        console.log("+++"+JSON.stringify(message.data));
        
        EnableCanvasInputKey = false;
        var modalInstance = $modal.open({
            animation: true,
            templateUrl: 'partials/forms/form_list.html',
            controller: 'FormOpenFileController',
            resolve: {
                type: function () {
                  return "Pipeline";
                },
                items: function () {
                    return message.data;
                }
            }
        });
        modalInstance.result.then(
        function (result) {
          for (var i = 0; i < result.length; i++) {
            LoadPipeline(result[i].name);
          } 

          // This document is not modified yet, so "saved" is true.
          if ($scope.DocsNavTabs.selected_tab != null) {
              $scope.DocsNavTabs.selected_tab.saved = true;
          }

          // LoadPipeline('pipeline_gccontent');
          // LoadExperiment('GC Content');
          EnableCanvasInputKey = true;
        },
        function () {
          EnableCanvasInputKey = true;
        });
      },
      function(message) {
        console.log("** GetStoredPipelinesList() Error **");
      });
    };

    function GetStoredExperimentsList() {
      console.log("** GetStoredExperimentsList() **");
      $rootScope.Http({
          method: 'GET',
          url: $rootScope.webAddress + 'repository_experiments',
          headers: { 'Content-Type': 'application/json' },
          data: {
          },
      },
      function(message) {
        EnableCanvasInputKey = false;
        var modalInstance = $modal.open({
            animation: true,
            templateUrl: 'partials/forms/form_list.html',
            controller: 'FormOpenFileController',
            resolve: {
                type: function () {
                    return "Experiment";
                },
                items: function () {
                    return message.data;
                }
            }
        });
        modalInstance.result.then(
        function (result) {
          for (var i = 0; i < result.length; i++) {
            LoadExperiment(result[i].name);
          } 

          // This document is not modified yet, so "saved" is true.
          if ($scope.DocsNavTabs.selected_tab != null) {
            $scope.DocsNavTabs.selected_tab.saved = true;
          }

          // LoadPipeline('pipeline_gccontent');
          // LoadExperiment('GC Content');
          EnableCanvasInputKey = true;
        },
        function () {
          EnableCanvasInputKey = true;
        });
      },
      function(message) {
        console.log("** GetStoredExperimentsList() Error **");
      });
    }

    ////////////////////////////////////////////////////////////////////////////
    // PIPELINE FUNCTIONS
    ////////////////////////////////////////////////////////////////////////////

    function CreateNode(id, enabled, type, left, top, value, outputs) {

        switch(type) {
          case 'console':
            value = 'This is an example of output console:<br /><br />result: 5<br />';
            break;
          case 'chart':
            value = GetDataExample1();
            break;
          case 'boxplot':
            value = GetDataExample2();
            break;
          case 'donutchart':
            value = GetDataExample3();
            break;
        }

        var new_node_id = id;
        if (new_node_id == null) {
            new_node_id = GetCurrentDocument().next_id;
            GetCurrentDocument().next_id++;
        } else {
            if (new_node_id >= GetCurrentDocument().next_id) {
                GetCurrentDocument().next_id = new_node_id+1;
            }
        }

        var new_node = {
            id: new_node_id * 1,
            type: type,
            selected: false,
            enabled: enabled,
            value: value,
            position: {
                top: top,
                left: left,
            },
            inputs: [],
            outputs: (outputs == null)?[]:outputs,
            temp: {
                width: null, // depends on the theme
                height: null, // depends on the theme
                // pointer to its type:
                type_obj: arrays.FindArrayElementById($scope.node_types, type),
                inputs_areas: [], // depends on the theme
                outputs_areas: [], // depends on the theme
                focused_input: null, // pointer to the own selected input
                focused_output: null, // pointer to the own selected output
            },
        };

        if (new_node.temp.type_obj != null) {
          for (i = 0; i < new_node.temp.type_obj.inputs.length; i++) {
              new_node.inputs.push({ id: i });
          }
          if (outputs == null) {
              for (i = 0; i < new_node.temp.type_obj.outputs.length; i++) {
                  new_node.outputs.push({ id: i, to: [] });
              }
          }

          GetCurrentDocumentNodes().push(new_node);

          if (new_node.temp.type_obj.style == $scope.NodeStyle.GRAPH_NODE) {
              CreateOutputTab(new_node);
          }
        } else {
            console.log("*******************************************" + type);
        }

        return new_node;
    };

    function RemoveNode(node_id) {
      var index = arrays.FindArrayElementIndexById(GetCurrentDocumentNodes(), node_id);
      GetCurrentDocumentNodes().splice(index, 1);

      // Remove all node outputs to the removed node
      for (var i = 0; i < GetCurrentDocumentNodes().length; i++) {
        var node = GetCurrentDocumentNodes()[i];
        
        for (var j = 0; j < node.outputs.length; j++) {
          var output = node.outputs[j];

          for (var k = 0; k < output.to.length; k++) {
            if (output.to[k].node_id == node_id) {
              output.to.splice(k, 1);
              k = 0; // restart
            }
          }
        }
      }
    };

    function MoveTheNodeToFirstLayer(node_id) {
        var old_index = null;

        for (var i = 0; ((i < GetCurrentDocumentNodes().length) && (old_index == null)); i++) {
            if (GetCurrentDocumentNodes()[i].id == node_id) {
                old_index = i;
            }
        }

        if (old_index != null) {
            var new_index = GetCurrentDocumentNodes().length - 1;

            GetCurrentDocumentNodes().splice(new_index, 0, GetCurrentDocumentNodes().splice(old_index, 1)[0]);
        }
    };


    ////////////////////////////////////////////////////////////////////////////
    // CANVAS FUNCTIONS
    ////////////////////////////////////////////////////////////////////////////

    function ClearCanvas(ctx, width, height, color) {
        ctx.save();

        ctx.fillStyle = color;
        ctx.fillRect(-1000, -1000, width, height);

        ctx.restore();
    };

    function DrawGridLines(ctx, left, top, width, height,
                           lineWidth, strokeStyle, distance_between_lines) {
        ctx.save();
        
        ctx.beginPath();

        var y = top;
        for (var x = left; x < left+width; x += distance_between_lines) {
            ctx.moveTo(x, y);
            ctx.lineTo(x, y+height);
        }

        var x = left;
        for (var y = top; y < top+height; y += distance_between_lines) {
            ctx.moveTo(x, y);
            ctx.lineTo(x+width, y);
        }

        ctx.strokeStyle = strokeStyle;
        ctx.lineWidth = lineWidth;
        ctx.stroke();

        ctx.restore();
    };

    function DrawTriangle(ctx, pointing_right, x, y, width, height,
                          lineWidth, strokeStyle, radius,
                          fillStyle, opacity, shadow) {
        ctx.save();

        if(strokeStyle != null) {
            ctx.strokeStyle = strokeStyle;
        }

        if (typeof radius === 'number') {
            radius = {tl: radius, tr: radius, br: radius, bl: radius};
        }

        var middle_height = (height/2);

        ctx.beginPath();
        if (pointing_right) {
            var middle_width = (width/6)*5;

            ctx.moveTo(x + radius.tl, y);
            ctx.lineTo(x + middle_width, y);
            ctx.lineTo(x + width, y + middle_height);
            ctx.lineTo(x + middle_width, y + height);
            ctx.lineTo(x + radius.bl, y + height);
            ctx.quadraticCurveTo(x, y + height,
                                 x, y + height - radius.bl);
            ctx.lineTo(x, y + radius.tl);
            ctx.quadraticCurveTo(x, y,
                                 x + radius.tl, y);

        } else {
            var middle_width = (width/6)*1;
            ctx.moveTo(x, y + middle_height);
            ctx.lineTo(x + middle_width, y);
            ctx.lineTo(x + width - radius.tr, y);
            ctx.quadraticCurveTo(x + width, y,
                                 x + width, y + radius.tr);
            ctx.lineTo(x + width, y + height - radius.br);
            ctx.quadraticCurveTo(x + width, y + height,
                                 x + width - radius.br, y + height);
            ctx.lineTo(x + middle_width, y + height);
/*
            var middle_width = (width/6)*1;
            ctx.moveTo(x, y + middle_height);
            ctx.lineTo(x + middle_width, y);
            ctx.lineTo(x + width - radius.tr, y);
            ctx.quadraticCurveTo(x + width, y,
                                 x + width, y + radius.tr);
            ctx.lineTo(x + width, y + height - radius.br);
            ctx.quadraticCurveTo(x + width, y + height,
                                 x + width - radius.br, y + height);
            ctx.lineTo(x + middle_width, y + height);
*/
        }
        ctx.closePath();

        if(lineWidth != null) {
            ctx.lineWidth = lineWidth;
        }
        if (shadow != null) {
            ctx.shadowColor = shadow;
            ctx.shadowOffsetX = 2;
            ctx.shadowOffsetY = 2;
            ctx.shadowBlur = 10 ;
        }

        ctx.stroke();

        if (fillStyle != null) {
            ctx.fillStyle = fillStyle;
            ctx.fill();
        }

        ctx.restore();
    }
     
    function DrawRect(ctx, x, y, width, height, lineWidth, strokeStyle, radius,
                      fillStyle, shadow, rectType) {
        ctx.save();

        if (typeof radius === 'number') {
            radius = {tl: radius, tr: radius, br: radius, bl: radius};
        }

        if(lineWidth != null) {
            ctx.lineWidth = lineWidth;
        }

        if(strokeStyle != null) {
            ctx.strokeStyle = strokeStyle;
        }

        ctx.beginPath();
        ctx.moveTo(x + radius.tl, y);

        switch(rectType) {
            case 'file':
                ctx.lineTo(x + width - radius.tr, y);
                ctx.quadraticCurveTo(x + width, y, x + width, y + radius.tr);
                ctx.lineTo(x + width, y + height - radius.br);
                ctx.quadraticCurveTo(x + width, y + height,
                x + width - radius.br, y + height);
                ctx.quadraticCurveTo(x + (width / 4)*3, y + height - 10,
                                     x + (width / 4)*2, y + height);
                ctx.quadraticCurveTo(x + (width / 4)*1, y + height + 10,
                                     x + (width / 4)*0, y + height);
                ctx.quadraticCurveTo(x, y + height, x, y + height - radius.bl);
                ctx.lineTo(x, y + radius.tl);
                ctx.quadraticCurveTo(x, y, x + radius.tl, y);
                break;
            case 'input_data':
                ctx.lineTo(x + width - radius.tr, y);
                ctx.quadraticCurveTo(x + width, y, x + width, y + radius.tr);
                ctx.lineTo(x + width, y + 50);
                ctx.lineTo(x + width - 10, y + height);
                ctx.lineTo(x - 10, y + height);
                ctx.lineTo(x, y + 50);
                ctx.lineTo(x, y + radius.tl);
                ctx.quadraticCurveTo(x, y, x + radius.tl, y);
                break;
            default:
                ctx.lineTo(x + width - radius.tr, y);
                ctx.quadraticCurveTo(x + width, y, x + width, y + radius.tr);
                ctx.lineTo(x + width, y + height - radius.br);
                ctx.quadraticCurveTo(x + width, y + height,
                x + width - radius.br, y + height);
                ctx.lineTo(x + radius.bl, y + height);
                ctx.quadraticCurveTo(x, y + height, x, y + height - radius.bl);
                ctx.lineTo(x, y + radius.tl);
                ctx.quadraticCurveTo(x, y, x + radius.tl, y);
                break;
        }
        

        ctx.closePath();
        ctx.stroke();
        if (shadow != null) {
            ctx.shadowColor = shadow;
            ctx.shadowOffsetX = 2;
            ctx.shadowOffsetY = 2;
            ctx.shadowBlur = 10;
        } else {
            ctx.shadowOffsetX = 0;
            ctx.shadowOffsetY = 0;
            ctx.shadowBlur = 0;
        }

        if (fillStyle != null) {
            ctx.fillStyle = fillStyle;
            ctx.fill();
        }


        ctx.restore();
    };

    function DrawBocata(ctx, x, y, width, height, lineWidth, strokeStyle, radius,
                      fillStyle, shadow, arrow) {

        DrawRect(ctx, x, y,
                  width, height,
                  lineWidth, strokeStyle, radius,
                  fillStyle, shadow, 'rectangle');
        //----------------------------------------------------------------------
        return;
        //----------------------------------------------------------------------

        var d = 35;
        var r = 5;

/*        if ((arrow == "left") || (arrow == "right")) {
          d = height / 5;
        }
        if ((arrow == "top") || (arrow == "bottom")) {
          d = width / 10;
        }
*/
        ctx.save();

        if (typeof radius === 'number') {
            radius = {tl: radius, tr: radius, br: radius, bl: radius};
        }

        if(lineWidth != null) {
            ctx.lineWidth = lineWidth;
        }

        if(strokeStyle != null) {
            ctx.strokeStyle = strokeStyle;
        }

        if (arrow == "top") {
          ctx.beginPath();
          ctx.moveTo(x + radius.tl, y);
//--
          ctx.lineTo(x + d, y);
          ctx.lineTo(x + d + d/2, y - d);
          ctx.lineTo(x + 2*d, y);
//--
          ctx.lineTo(x + width - radius.tr, y);
          ctx.quadraticCurveTo(x + width, y, x + width, y + radius.tr);
          ctx.lineTo(x + width, y + height - radius.br);
          ctx.quadraticCurveTo(x + width, y + height,
          x + width - radius.br, y + height);
          ctx.lineTo(x + radius.bl, y + height);
          ctx.quadraticCurveTo(x, y + height, x, y + height - radius.bl);
          ctx.lineTo(x, y + radius.tl);
          ctx.quadraticCurveTo(x, y, x + radius.tl, y);
          ctx.closePath();
          ctx.stroke();
        }


        if (arrow == "right") {
          ctx.beginPath();
          ctx.moveTo(x + radius.tl, y);
          ctx.lineTo(x + width - radius.tr, y);
          ctx.quadraticCurveTo(x + width, y, x + width, y + radius.tr);
//--
          ctx.lineTo(x + width, y + radius.tr + d);
          ctx.lineTo(x + width + d, y + radius.tr + d + d/2);
          ctx.lineTo(x + width, y + radius.tr + 2*d);
//--
          ctx.lineTo(x + width, y + height - radius.br);
          ctx.quadraticCurveTo(x + width, y + height,
          x + width - radius.br, y + height);
          ctx.lineTo(x + radius.bl, y + height);
          ctx.quadraticCurveTo(x, y + height, x, y + height - radius.bl);
          ctx.lineTo(x, y + radius.tl);
          ctx.quadraticCurveTo(x, y, x + radius.tl, y);
          ctx.closePath();
          ctx.stroke();
        }

        if (arrow == "bottom") {
          ctx.beginPath();
          ctx.moveTo(x + radius.tl, y);
          ctx.lineTo(x + width - radius.tr, y);
          ctx.quadraticCurveTo(x + width, y, x + width, y + radius.tr);
          ctx.lineTo(x + width, y + height - radius.br);
          ctx.quadraticCurveTo(x + width, y + height,
          x + width - radius.br, y + height);
//--
          ctx.lineTo(x + radius.bl + d*2, y + height);
          ctx.lineTo(x + radius.bl + d + d/2, y + height + d);
          ctx.lineTo(x + radius.bl + d, y + height);
//--
          ctx.lineTo(x + radius.bl, y + height);
          ctx.quadraticCurveTo(x, y + height, x, y + height - radius.bl);
          ctx.lineTo(x, y + radius.tl);
          ctx.quadraticCurveTo(x, y, x + radius.tl, y);
          ctx.closePath();
          ctx.stroke();
        }

        if (arrow == "left") {
          ctx.beginPath();
          ctx.moveTo(x + radius.tl, y);
          ctx.lineTo(x + width - radius.tr, y);
          ctx.quadraticCurveTo(x + width, y, x + width, y + radius.tr);
          ctx.lineTo(x + width, y + height - radius.br);
          ctx.quadraticCurveTo(x + width, y + height,
          x + width - radius.br, y + height);
          ctx.lineTo(x + radius.bl, y + height);
          ctx.quadraticCurveTo(x, y + height, x, y + height - radius.bl);
//--
/*
          ctx.lineTo(x, y + radius.tl + d);
          ctx.lineTo(x - d, y + radius.tl + d + d/2);
          ctx.lineTo(x, y + radius.tl + d*2);
*/

          ctx.lineTo(x, y + radius.tl + d*2);
          ctx.lineTo(x - d, y + radius.tl + d + d/2 + r);
          ctx.quadraticCurveTo(x - d - r*1.5, y + radius.tl + d + d/2 + r, x - d - r*1.5, y + radius.tl + d + d/2);
          ctx.quadraticCurveTo(x - d - r*1.5, y + radius.tl + d + d/2 - r, x - d, y + radius.tl + d + d/2 - r);
          ctx.lineTo(x - d, y + radius.tl + d + d/2 - r);
          ctx.lineTo(x, y + radius.tl + d);
//--
          ctx.lineTo(x, y + radius.tl);
          ctx.quadraticCurveTo(x, y, x + radius.tl, y);
          ctx.closePath();
          ctx.stroke();

        }


        if (shadow != null) {
            ctx.shadowColor = shadow;
            ctx.shadowOffsetX = 2;
            ctx.shadowOffsetY = 2;
            ctx.shadowBlur = 10;
        } else {
            ctx.shadowOffsetX = 0;
            ctx.shadowOffsetY = 0;
            ctx.shadowBlur = 0;
        }

        if (fillStyle != null) {
            ctx.fillStyle = fillStyle;
            ctx.fill();
        }


        ctx.restore();
    };

    function SetTextShadow(ctx, h_shadow, v_shadow, blur_radius, color) {
        ctx.shadowColor = color;
        ctx.shadowOffsetX = h_shadow;
        ctx.shadowOffsetY = v_shadow;
        ctx.shadowBlur = blur_radius;
    };

    // This is the quick draw text
    function DrawText(ctx, font, text_color, shadow_color, text, 
             x, y, textAlign) {
        ctx.save();
        ctx.font = font;
        ctx.textAlign = textAlign;
        ctx.fillStyle = text_color;
        if (shadow_color != null)
            SetTextShadow(ctx, 1, 1, 0, shadow_color);
        //ctx.clip();
        ctx.fillText(text, x, y);
        ctx.restore();
    };

    // This draw text writes the text as in a cell.
    /* Do not use "font px". Instead, use "font pt" */
    function DrawTextRect(ctx, font, highlight_font, text_color, text, x, y, width, height,
                          line_space_px, // This is the total line height space (Not the font height size)
                          span, adapt_height, draw_rect, draw_arrow,
                          lineWidth, strokeStyle, radius, fillStyle, shadow) {
      var ret = {
        "width":width,
        "height":height,
      };

      ctx.save();
      ctx.font = font;
      ctx.fillStyle = text_color;

      text = ReplaceAll(text, "<br />", " [EOL] ");
      text = ReplaceAll(text, "\n", " [EOL] ");
      text = ReplaceAll(text, "<b>", " <b> ");
      text = ReplaceAll(text, "</b>", " </b> ");

      // Two loops: 
      //   The first one, calculates the area.
      //   The second one, draws the box and writes the text.
      for (k = 0; k < 2; k++) {
        var words = text.split(' ');
        var inside_rect = true;
        var current_textline_width = 0;
        var current_textline_height = 0;

        if (k == 1) {
          if (draw_rect) {
            if (adapt_height) {
              DrawBocata(ctx, x, y, ret.width, ret.height, lineWidth, strokeStyle, radius, fillStyle, shadow, draw_arrow);

            } else {
              DrawBocata(ctx, x, y, width, height, lineWidth, strokeStyle, radius, fillStyle, shadow, draw_arrow);
            }
          }
        }

        var y_correction = parseInt(ctx.font);

        // Loop each text word
        for (var i = 0; ((i < words.length) && (inside_rect)); i++) {
          if (words[i] == "[EOL]") {
            current_textline_width = 0;
            current_textline_height += word_size.height;
          }
          else {
            if (words[i] == "</b>") {
              ctx.font = font;
            }
            else {
              if (words[i] == "<b>") {
                ctx.font = highlight_font;
              }
              else {
                if (i < words.length - 1) {
                  words[i] = words[i] + " ";
                }

                // Mesure each word with its final space
                var word_size = {
                  "width":ctx.measureText(words[i]).width,
                  "height":line_space_px // parseInt(ctx.font) * line_space_percent <-- No es fiable
                }

                if (words[i] != " ") {
                  if (current_textline_width + word_size.width + span < width) {
                    // write the word at the end of the current line
                    if (k == 1) ctx.fillText(words[i], x + span + current_textline_width, y + y_correction + span + current_textline_height);
                    current_textline_width += word_size.width;
                  } else {
                    // set an EOL and write the word at the begining of the new line
                    current_textline_width = word_size.width;
                    current_textline_height += word_size.height;

                    if ((!adapt_height) && (current_textline_height + span > height)) {
                      inside_rect = false;
                      if (k == 1) ctx.fillText("...", x + span, y + y_correction + span + current_textline_height);
                    } else {
                      if (k == 1) ctx.fillText(words[i], x + span, y + y_correction + span + current_textline_height);
                    }
                  }
                }
              }
            }
          }
        }

        if (adapt_height) {
          ret.height = span + word_size.height + current_textline_height + span;
        }
      }

      ctx.restore();



      return ret;
    };

    function DrawCircle(ctx, x, y, radius, 
                       lineWidth, strokeStyle, fillStyle, shadow) {
        ctx.save();
        ctx.beginPath();
        ctx.arc(x, y, radius, 0, 2 * Math.PI);

        if(lineWidth != null) {
            ctx.lineWidth = lineWidth;
        }

        if(strokeStyle != null) {
            ctx.strokeStyle = strokeStyle;
        }

        if (shadow != null) {
            ctx.shadowColor = shadow;
            ctx.shadowOffsetX = 2;
            ctx.shadowOffsetY = 2;
            ctx.shadowBlur = 10 ;
        }

        if (fillStyle != null) {
            ctx.fillStyle = fillStyle;
            ctx.fill();
        }
        ctx.stroke();
        ctx.restore();
    };

    function IsHit(mousex, mousey, node) {
        return ((mousex >= node.position.left) &&
                (mousex <= node.position.left + node.temp.width) &&
                (mousey >= node.position.top) &&
                (mousey <= node.position.top + node.temp.height));
    };

    function DrawPixel(ctx, x, y) {
        ctx.save();
        ctx.fillStyle = "rgba(255,255,255,1)";
        ctx.fillRect( x, y, 2, 2 );
        ctx.stroke();
        ctx.restore();   
    };

    function DrawLine(ctx, strokeStyle, lineWidth, shadow,
                      x1, y1, x2, y2, adjust) {
        var reverse_adjust = 1;

        if (adjust != null) {
            if (x1 > x2) {
                reverse_adjust = -1;
            }
        }

        if (x1 < x2) {
            start_point = { x: x1, y: y1 };
            end_point =   { x: x2, y: y2 };
        } else {
            start_point = { x: x2, y: y2 };
            end_point =   { x: x1, y: y1 };
        }
        
        diffx = (end_point.x - start_point.x);

        middle_x = start_point.x + diffx / 2;

        if (y1 < y2) {
            middle_y = y1 + (y2 - y1) / 2;
        } else {
            middle_y = y2 + (y1 - y2) / 2;
        }

        var control_points = [
            { 
                x: start_point.x + (diffx / 4) * reverse_adjust,
                y: start_point.y
            },
            { 
                x: middle_x,
                y: middle_y
            },
            { 
                x: end_point.x - (diffx / 4) * reverse_adjust,
                y: end_point.y
            },
        ];
        
        // DrawPixel(ctx,start_point.x,start_point.y);
        // DrawPixel(ctx,control_points[0].x,control_points[0].y);
        // DrawPixel(ctx,control_points[1].x,control_points[1].y);
        // DrawPixel(ctx,control_points[2].x,control_points[2].y);
        // DrawPixel(ctx,end_point.x,end_point.y);
        
        ctx.save();
        ctx.beginPath();
        if (strokeStyle != null) ctx.strokeStyle = strokeStyle;
        if (lineWidth != null) ctx.lineWidth = lineWidth;
        if (shadow != null) {
            ctx.shadowColor = shadow;
            ctx.shadowOffsetX = 1;
            ctx.shadowOffsetY = 1;
            ctx.shadowBlur = 2;
        }

        ctx.moveTo(start_point.x, start_point.y);
        ctx.quadraticCurveTo(
                          control_points[0].x, control_points[0].y,
                          control_points[1].x, control_points[1].y);
        ctx.quadraticCurveTo(
                          control_points[2].x, control_points[2].y,
                          end_point.x, end_point.y);

        /*
        Right Arrow
        end_point.x -= 6;
        ctx.lineTo(end_point.x - 10, end_point.y - 8);
        ctx.moveTo(end_point.x, end_point.y);
        ctx.lineTo(end_point.x - 10, end_point.y + 8);
        */

        ctx.stroke();
        ctx.restore();   

        DrawCircle(ctx, start_point.x, start_point.y, 5, 
                       lineWidth, strokeStyle, 'white', shadow);


        DrawCircle(ctx, end_point.x, end_point.y, 5, 
                       lineWidth, strokeStyle, 'white', shadow);

    }

    function DrawNodeConnections(ctx, node, strokeStyle, lineWidth, shadow) {
        node.outputs.forEach(function(output) {
            if (output.to != null) {
                for (var i = 0; i < output.to.length; i++) {
                    var node_to = arrays.FindArrayElementById(
                                                          GetCurrentDocumentNodes(), 
                                                          output.to[i].node_id);
                    if (node_to != null) {
                        var connection_area_to = arrays.FindArrayElementById(
                                                      node_to.temp.inputs_areas,
                                                      output.to[i].input_id);
                        if (connection_area_to != null) {
                            var connection_area_from = 
                            arrays.FindArrayElementById(node.temp.outputs_areas,
                                                        output.id);
                            if (connection_area_from != null) {

                                // if (node.temp.focused_input != null) {
                                //   if (node.temp.focused_input.id == ) {
                                //   }
                                // }
                                lineWidth_to_use = lineWidth;

                                // Highlight current connection line:
                                if (($scope.connector_selected != null) &&
                                    ($scope.connector_selected.node != null) &&
                                    ($scope.connector_selected.connector != null)) {

//                                    if  (($scope.connector_selected.node.id == node.id) && ($scope.connector_selected.connector.id == connection_area_from.id)) {
                                    if ( (($scope.connector_selected.node.id == node.id) && ($scope.connector_selected.connector.id == connection_area_from.id) && ($scope.connector_selected.direction == "output")) ||
                                         (($scope.connector_selected.node.id == node_to.id) && ($scope.connector_selected.connector.id == output.to[i].input_id) && ($scope.connector_selected.direction == "input"))) {
                                      lineWidth_to_use = 5;
                                    }
                                }

                                DrawLine(ctx, strokeStyle, lineWidth_to_use, shadow,
                                        node.position.left + 
                                        connection_area_from.x,
                                        node.position.top +
                                        connection_area_from.y,
                                        node_to.position.left +
                                        connection_area_to.x,
                                        node_to.position.top +
                                        connection_area_to.y, true);
                            }
                        }
                    }
                }
            }
        });
    };

    function DrawTitle(ctx, node, style) {
        var lineWidth = 0.5;
        var border_color = (node.selected)?style.NODE_SELECTED_BORDER_COLOR:style.NODE_BORDER_COLOR;

        DrawRect(ctx, node.position.left, node.position.top,
                      node.temp.width, style.NODE_TITLE_HEIGHT,
                      lineWidth, border_color, {tl: style.NODE_BOX_CORNER_RADIUS, tr: style.NODE_BOX_CORNER_RADIUS, br: 0, bl: 0}, ((node.enabled)?style.TITLE_BACKGROUND_COLOR:style.NODE_DISABLED_COLOR), null, 'rectangle');

        var title = (node.type.toUpperCase());
        if (title.substr(0,5) == 'CALC_') {
          title = title.substr(5, 1000);
        }
        title = title.split('_').join(' ');

        DrawText(ctx, fonts.NodeTitle, ((node.enabled)?style.TITLE_TEXT_COLOR:style.NODE_BORDER_COLOR), null, title + ((node.enabled)?"":" (disabled)"),  /* (($scope.debug_mode)?" (" + node.id + ")":"") + */
                 node.position.left + (node.temp.width/2), node.position.top + (style.NODE_TITLE_HEIGHT/2)+5, "center");
    };

    function DrawNodeConnectors(ctx, node, style,
                                side,
                                connectors,
                                conector_areas,
                                focused,
                                text_position_correction,
                                labeled_connector_names) {

        for (var i = 0; i < conector_areas.length; i++) {
            var x = node.position.left + conector_areas[i].x;
            var y = node.position.top + conector_areas[i].y;

            var border_color = style.NODE_BORDER_COLOR;

            if ((focused != null) && (connectors[i].id == focused.id)) {
                border_color = style.NODE_SELECTED_BORDER_COLOR;
            }

            if (labeled_connector_names) {
                var lineWidth = 1;
                $scope.ctx.font = fonts.ConnectorName; //style.CONNECTOR_TEXT_WIDTH + " 13px Roboto";
                //var text_width = $scope.ctx.measureText(connectors[i].name).width + 35;


                if (side=='left') { 
                    /*DrawTriangle(ctx, true, 
                                 x + text_position_correction - 20 + 5, y - style.CONNECTOR_HEIGHT/2 - 1,
                                 text_width, style.CONNECTOR_HEIGHT + 2,
                                 lineWidth, style.NODE_BORDER_COLOR,
                                 style.NODE_BOX_CORNER_RADIUS,
                                 style.NODE_BACKGROUND_COLOR, 0.2, null);*/
                  /*  DrawRect(ctx, x + text_position_correction - 20 + 5, y - style.CONNECTOR_HEIGHT/2 - 1,
                              10, style.CONNECTOR_HEIGHT + 2,
                              lineWidth, style.NODE_BORDER_COLOR, 0,
                              'lightgray', null, 'rectangle');*/
                } else {
                    /*DrawTriangle(ctx, false,
                                 x + text_position_correction - text_width + 20 - 5, y - style.CONNECTOR_HEIGHT/2 - 1,
                                 text_width, style.CONNECTOR_HEIGHT + 2,
                                 lineWidth, style.NODE_BORDER_COLOR,
                                 style.NODE_BOX_CORNER_RADIUS,
                                 style.NODE_BACKGROUND_COLOR, 0.2, null);*/
                    /*DrawRect(ctx, x + text_position_correction + 5, y - style.CONNECTOR_HEIGHT/2 - 1,
                              10, style.CONNECTOR_HEIGHT + 2,
                              lineWidth, style.NODE_BORDER_COLOR, 0,
                              style.TITLE_BACKGROUND_COLOR, null, 'rectangle');*/
                }
            }

            connector_color = style.CONNECTOR_OPEN_COLOR;

            DrawCircle(ctx, x, y, style.CONNECTOR_HEIGHT/2, 
                  2, border_color, connector_color, null);

            switch(node.temp.type_obj.style) {
                case $scope.NodeStyle.CALCULATION_NODE:
                case $scope.NodeStyle.GRAPH_NODE:
                case $scope.NodeStyle.EXTERNAL_VIEWER_NODE:
                case $scope.NodeStyle.PIPELINE_NODE:
                    if (conector_areas[i].required) {
                      //if(IsThisNodeInputConnectorEmpty(node.id, conector_areas[i].id)) {
                      //  DrawCircle(ctx, x, y, style.CONNECTOR_HEIGHT/8, 2, 'red', 'red', null);
                      //} else {
                        DrawCircle(ctx, x, y, style.CONNECTOR_HEIGHT/8, 2, border_color, border_color, null);
                      //}
                    }
//3573
                    break;
            };
          
            if ((i != 0) && (connectors[i] != undefined) && (connectors[i-1] != undefined) && (connectors[i].group != connectors[i-1].group)) {
/*
(ctx, strokeStyle, lineWidth, shadow,
                      x1, y1, x2, y2, adjust)
*/
              ctx.setLineDash([4, 4]);
              DrawLine(ctx, border_color, 0.5, null,
                       x + text_position_correction, y - style.CONNECTOR_HEIGHT/1.3,
                       x + node.temp.width / 2 , y - style.CONNECTOR_HEIGHT/1.3);
              ctx.setLineDash([0, 0]);
            }


            if ((connectors[i] != undefined) && (connectors[i].name != 'Foreach')) {
                DrawText(ctx, fonts.ConnectorName, //style.CONNECTOR_TEXT_WIDTH + " 13px Roboto",
                         style.CONNECTOR_TEXT_COLOR,
                         style.CONNECTOR_TEXT_SHADOW_COLOR,
                         connectors[i].name, 
                         x + text_position_correction, y + 4, side);
            }
        }
    }

    function DrawDebugLabel(ctx, label, x, y, background_color) {
        DrawCircle(ctx, x, y, 14, 2, 'black', background_color, null);
        DrawText(ctx, fonts.NodeTitle, 'black', null, label, x, y + 4, "center");            
    };

    function DrawNodeLogo(ctx, node, style, x, y, draw_background_circle) {
        if ($scope.debug_mode == false) {
            if (draw_background_circle) {
                ctx.drawImage(arrays.FindArrayElementById(images, $scope.IconImage.ICON_BACKGROUND).image, x, y, 29, 28);
            }
            var e = arrays.FindArrayElementById(images, node.temp.type_obj.style);
            if (e != null) {
               ctx.drawImage(e.image, x, y, 29, 28);
            }
        } else {
            //DrawDebugLabel(ctx, (node.temp.execution_order==null)?'?':(node.temp.execution_order + 1), x + 37, y + 14, 'yellow');
            DrawDebugLabel(ctx, node.id, x + 14, y + 14, 'white');
        }
    };

    function DrawNodeValue(ctx, node, style) {
        if (node.value != null) {

            switch(node.type) {
                case 'bool':
                    DrawNodeImage(ctx, node, style,
                                  (node.value == "TRUE")?$scope.IconImage.IMAGE_NODE_BOOL_ON:$scope.IconImage.IMAGE_NODE_BOOL_OFF,
                                  node.position.left + node.temp.width/4,
                                  node.position.top + style.NODE_TITLE_HEIGHT + 4,
                                  85, 40, false);

                    break;
                default:
                    var value = node.value;
                    /*var MAX_CHARS = 20;
                    if (value.length > MAX_CHARS) {
                        value = node.value.substr(0, MAX_CHARS) + "...";
                    }*/
                    DrawText(ctx, fonts.NodeValue, // "400 13px Roboto", 
                            'black', null, value, 
                             node.position.left + (node.temp.width/2),
                             node.position.top + 25 + style.NODE_TITLE_HEIGHT + 4, "center");
                    break;
            }
        }
    };

    function DrawInputNode(ctx, node, style) {
        if (node.value == 'Foreach') {
        } else {
            var lineWidth = 1;
            var border_color = (node.selected)?style.NODE_SELECTED_BORDER_COLOR:style.NODE_BORDER_COLOR;

            DrawTriangle(ctx, true, node.position.left, node.position.top,
                         node.temp.width, node.temp.height,
                         lineWidth, border_color,
                         style.NODE_BOX_CORNER_RADIUS,
                         ((node.enabled)?style.NODE_BACKGROUND_COLOR:style.NODE_DISABLED_COLOR), 0.2, '#333');

            // Selection:
            if ($scope.node_selected == node) {
                DrawTriangle(ctx, true, node.position.left, node.position.top,
                             node.temp.width, node.temp.height,
                             2, style.NODE_SELECTED_BORDER_COLOR,
                             style.NODE_BOX_CORNER_RADIUS,
                             null, 0.2, null);
            }

            DrawRect(ctx, node.position.left, node.position.top,
                      35, node.temp.height,
                      lineWidth, border_color, style.NODE_BOX_CORNER_RADIUS,
                      style.TITLE_BACKGROUND_COLOR, null, 'rectangle');
            DrawNodeLogo(ctx, node, style,
                         node.position.left+4, 
                         node.position.top + (node.temp.height/2) + style.NODE_TITLE_HEIGHT - 29/2, true);
            DrawNodeConnectors(ctx, node, style, 'left', node.temp.type_obj.inputs,
                             node.temp.inputs_areas, node.temp.focused_input, 15, false);
            DrawNodeConnectors(ctx, node, style, 'right',node.temp.type_obj.outputs,
                             node.temp.outputs_areas, node.temp.focused_output,-15, false);
            DrawNodeValue(ctx, node, style);
        }
    };

    function DrawCalculationNode(ctx, node, style) {
        var lineWidth = 1;
        var border_color = (node.selected)?style.NODE_SELECTED_BORDER_COLOR:style.NODE_BORDER_COLOR;
        DrawRect(ctx, node.position.left, node.position.top,
                  node.temp.width, node.temp.height,
                  lineWidth, border_color, style.NODE_BOX_CORNER_RADIUS,
                  ((node.enabled)?style.NODE_BACKGROUND_COLOR:style.NODE_DISABLED_COLOR), '#333', 'rectangle');

        // Selection:
        if ($scope.node_selected == node) {
            DrawRect(ctx, node.position.left, node.position.top,
                      node.temp.width, node.temp.height,
                      2, style.NODE_SELECTED_BORDER_COLOR, style.NODE_BOX_CORNER_RADIUS,
                      null, null, 'rectangle');
        }


        DrawTitle(ctx, node, style);
        DrawNodeLogo(ctx, node, style,
                     node.position.left + node.temp.width - 29,
                     node.position.top+1, true);
        DrawNodeConnectors(ctx, node, style, 'left', node.temp.type_obj.inputs,
                         node.temp.inputs_areas, node.temp.focused_input, 15, false);
        DrawNodeConnectors(ctx, node, style, 'right',node.temp.type_obj.outputs,
                         node.temp.outputs_areas, node.temp.focused_output,-15, false);
    };

    function DrawOutputNode(ctx, node, style) {
        var lineWidth = 1;
        var border_color = (node.selected)?style.NODE_SELECTED_BORDER_COLOR:style.NODE_BORDER_COLOR;

        DrawTriangle(ctx, false, node.position.left, node.position.top,
                     node.temp.width, node.temp.height,
                     lineWidth, border_color,
                     style.NODE_BOX_CORNER_RADIUS,
                     ((node.enabled)?style.NODE_BACKGROUND_COLOR:style.NODE_DISABLED_COLOR), 0.2, '#333');

        // Selection:
        if ($scope.node_selected == node) {
            DrawTriangle(ctx, false, node.position.left, node.position.top,
                         node.temp.width, node.temp.height,
                         2, style.NODE_SELECTED_BORDER_COLOR,
                         style.NODE_BOX_CORNER_RADIUS,
                         null, 0.2, null);
        }


        DrawRect(ctx, node.position.left + node.temp.width - 35, node.position.top,
                  35, node.temp.height,
                  lineWidth, border_color, style.NODE_BOX_CORNER_RADIUS,
                  style.TITLE_BACKGROUND_COLOR, null);
        DrawNodeLogo(ctx, node, style,
                     node.position.left + node.temp.width - 29 + 3 - 5,
                     node.position.top + (node.temp.height/2) + style.NODE_TITLE_HEIGHT - 29/2, true);
        DrawNodeConnectors(ctx, node, style, 'left', node.temp.type_obj.inputs,
                         node.temp.inputs_areas, node.temp.focused_input, 15, false);
        DrawNodeConnectors(ctx, node, style, 'right',node.temp.type_obj.outputs,
                         node.temp.outputs_areas, node.temp.focused_output,-15, false);
        DrawNodeValue(ctx, node, style);
    };

    function DrawDataNode(ctx, node, style) {
        var lineWidth = 1;
        var border_color = (node.selected)?style.NODE_SELECTED_BORDER_COLOR:style.NODE_BORDER_COLOR;


        var rectType = 'input_data';
        if ((node.type.toUpperCase()).indexOf("FILE") != -1) {
            rectType = 'file';
        }

        DrawRect(ctx, node.position.left, node.position.top,
                  node.temp.width, node.temp.height,
                  lineWidth, border_color, style.NODE_BOX_CORNER_RADIUS,
                  ((node.enabled)?style.NODE_BACKGROUND_COLOR:style.NODE_DISABLED_COLOR), 'black', rectType);

        // Selection:
        if ($scope.node_selected == node) {
            DrawRect(ctx, node.position.left, node.position.top,
                      node.temp.width, node.temp.height,
                      2, style.NODE_SELECTED_BORDER_COLOR, style.NODE_BOX_CORNER_RADIUS,
                      null, null, rectType);
        }


        DrawTitle(ctx, node, style);

        var x = node.position.left + node.temp.width - 29;
        var y = node.position.top+1;
        if ((node.type == 'foreach_value') || (node.type == 'foreach_iteration')) {
            ctx.drawImage(arrays.FindArrayElementById(images, $scope.IconImage.ICON_BACKGROUND).image, x, y, 29, 28);
            y += 3;
            ctx.drawImage(arrays.FindArrayElementById(images, $scope.IconImage.IMAGE_PIPELINE_LOOP).image, x, y, 26, 20); 
        } else {
            DrawNodeLogo(ctx, node, style, x, y, true);
        }


        //var image = arrays.FindArrayElementById(images, $scope.IconImage.IMAGE_NODE_BOOL).image;
        //image.setAttribute("stroke","0000FF");
        //image.hide_on.style.fill="yellow";

        DrawNodeConnectors(ctx, node, style, 'left', node.temp.type_obj.inputs,
                         node.temp.inputs_areas, node.temp.focused_input, 15, false);
        DrawNodeConnectors(ctx, node, style, 'right',node.temp.type_obj.outputs,
                         node.temp.outputs_areas, node.temp.focused_output,-15, false);
        DrawNodeValue(ctx, node, style);
    };

    function DrawCommentNode(ctx, node, style) {
        var lineWidth = 1;
        var border_color = (node.selected)?style.NODE_SELECTED_BORDER_COLOR:style.NODE_BORDER_COLOR;


        var rectType = 'rectangle';
        if ((node.type.toUpperCase()).indexOf("FILE") != -1) {
            rectType = 'file';
        }

        DrawRect(ctx, node.position.left, node.position.top,
                  node.temp.width, node.temp.height,
                  lineWidth, border_color, style.NODE_BOX_CORNER_RADIUS,
                  ((node.enabled)?style.NODE_BACKGROUND_COLOR:style.NODE_DISABLED_COLOR), 'black', rectType);

        // Selection:
        if ($scope.node_selected == node) {
            DrawRect(ctx, node.position.left, node.position.top,
                      node.temp.width, node.temp.height,
                      2, style.NODE_SELECTED_BORDER_COLOR, style.NODE_BOX_CORNER_RADIUS,
                      null, null, rectType);
        }


//        DrawTitle(ctx, node, style);

        var x = node.position.left + node.temp.width / 2 - 48/2;
        var y = node.position.top - 10;
//        DrawNodeLogo(ctx, node, style, x, y, false);
        ctx.drawImage(arrays.FindArrayElementById(images, node.temp.type_obj.style).image, x, y, 48, 48);


        //DrawNodeValue(ctx, node, style);
        var value = node.value;
        DrawText(ctx, fonts.Comment, // "400 13px Roboto", 
                'green', null, value, 
                 node.position.left + (node.temp.width/2),
                 node.position.top + 25 + style.NODE_TITLE_HEIGHT + 4, "center");


    };

    function DrawNullConnection(ctx, node, style) {
        var lineWidth = 1;
        var border_color = (node.selected)?style.NODE_SELECTED_BORDER_COLOR:style.NODE_BORDER_COLOR;

        //DrawRect(ctx, node.position.left, node.position.top,
        //                  node.temp.width, node.temp.height,
        //                  2, style.NODE_SELECTED_BORDER_COLOR, style.NODE_BOX_CORNER_RADIUS,
        //                  null, null, 'rectangle');

        ctx.drawImage(arrays.FindArrayElementById(images, node.temp.type_obj.style).image,
                                                  node.position.left, 
                                                  node.position.top,
                                                  16, 16); // size of null_connection.svg
    };

    function DrawNodeImage(ctx, node, style, image_id, x, y, width, height, clip) {
        if (clip) {
            // DrawCircle(ctx, x + width/2, y + height/2, 35, 3, style.FRAMEWORK_COLOR, 'transparent', null);

            ctx.save();
            ctx.beginPath();
            ctx.arc(x + width/2, y + height/2, 35, 0, 2 * Math.PI);
            ctx.closePath();
            ctx.clip();
        }

        ctx.drawImage(arrays.FindArrayElementById(images, image_id).image,
                      x, y,
                      width, height);

        if (clip) {
            ctx.restore();

            DrawCircle(ctx, x + width/2, y + height/2, 35, 3, style.FRAMEWORK_COLOR, 'transparent', null);
        }
    };

    function DrawGraphNode(ctx, node, style) {
        var lineWidth = 1;
        var border_color = (node.selected)?style.NODE_SELECTED_BORDER_COLOR:style.NODE_BORDER_COLOR;

        var node_background_image = null;
        var image_pos_x = node.position.left + 110;

        switch(node.type) {
            case 'chart':
                node_background_image = $scope.IconImage.IMAGE_NODE_CHART;
                break;
            case 'boxplot':
                node_background_image = $scope.IconImage.IMAGE_NODE_BOXPLOT;
                break;
            case 'donutchart':
                node_background_image = $scope.IconImage.IMAGE_NODE_DONUTCHART;
                break;
            case 'R Export':
                node_background_image = $scope.IconImage.IMAGE_NODE_EXPORT;
                break;
            case 'TFA Viewer':
                node_background_image = $scope.IconImage.IMAGE_TFA_VIEWER;
                break;
            case 'Print Data':
                node_background_image = $scope.IconImage.IMAGE_NODE_PRINT_DATA;
                break;
            case 'console': // by default
            default:
                node_background_image = $scope.IconImage.IMAGE_NODE_CONSOLE;  // by default
                image_pos_x = node.position.left + 45;
                break;
        }


        DrawRect(ctx, node.position.left, node.position.top,
                  node.temp.width, node.temp.height,
                  lineWidth, border_color, style.NODE_BOX_CORNER_RADIUS,
                  ((node.enabled)?style.NODE_BACKGROUND_COLOR:style.NODE_DISABLED_COLOR), 'black', 'rectangle');

        // Selection:
        if ($scope.node_selected == node) {
            DrawRect(ctx, node.position.left, node.position.top,
                      node.temp.width, node.temp.height,
                      2, style.NODE_SELECTED_BORDER_COLOR, style.NODE_BOX_CORNER_RADIUS,
                      null, null, 'rectangle');
        }

        DrawTitle(ctx, node, style);
        DrawNodeLogo(ctx, node, style,
                     node.position.left + node.temp.width - 29,
                     node.position.top+1, true);
        DrawNodeImage(ctx, node, style,
                      node_background_image,
                      image_pos_x,
                      node.position.top + style.NODE_TITLE_HEIGHT + 7,
                      80, 80, true);       
        DrawNodeConnectors(ctx, node, style, 'left', node.temp.type_obj.inputs,
                         node.temp.inputs_areas, node.temp.focused_input, 15, false);
        DrawNodeConnectors(ctx, node, style, 'right',node.temp.type_obj.outputs,
                         node.temp.outputs_areas, node.temp.focused_output,-15, false);
    };

    function DrawPipelineNode(ctx, node, style) {
        var lineWidth = 1;
        var border_color = (node.selected)?style.NODE_SELECTED_BORDER_COLOR:style.NODE_BORDER_COLOR;

        DrawRect(ctx, node.position.left, node.position.top,
                  node.temp.width, node.temp.height,
                  lineWidth, border_color, style.NODE_BOX_CORNER_RADIUS,
                  ((node.enabled)?current_theme.PIPELINE_BACKGROUND_COLOR:style.NODE_DISABLED_COLOR), 'black', 'rectangle');

        var loop_section_height = 30;

/*
        DrawRect(ctx, node.position.left, node.position.top + node.temp.height - loop_section_height,
                  80 , loop_section_height,
                  lineWidth, border_color, style.NODE_BOX_CORNER_RADIUS,
                  style.NODE_LOOP_COLOR, null, 'rectangle');
*/
        var loop_image_pos = { x: node.position.left + 15, y: node.position.top + 3 + node.temp.height - loop_section_height, w: 26, h: 20 };
       // ctx.drawImage(arrays.FindArrayElementById(images, $scope.IconImage.ICON_BACKGROUND).image, node.position.left + 15, node.position.top + node.temp.height - loop_section_height, 29, 28);
        ctx.drawImage(arrays.FindArrayElementById(images, $scope.IconImage.IMAGE_PIPELINE_LOOP_BLACK).image,
                      loop_image_pos.x, loop_image_pos.y,
                      loop_image_pos.w, loop_image_pos.h);

        DrawText(ctx, fonts.ConnectorName, //style.CONNECTOR_TEXT_WIDTH + " 13px Roboto",
                 style.CONNECTOR_TEXT_COLOR,
                 style.CONNECTOR_TEXT_SHADOW_COLOR,
                 (node.temp.type_obj.properties.loop_name!="")?node.temp.type_obj.properties.loop_name + "'s List":"", 
                 loop_image_pos.x + loop_image_pos.w + 5 , loop_image_pos.y + 3*(loop_image_pos.h / 4) + 1, 'left');

        // Selection:
        if ($scope.node_selected == node) {
            DrawRect(ctx, node.position.left, node.position.top,
                      node.temp.width, node.temp.height,
                      2, style.NODE_SELECTED_BORDER_COLOR, style.NODE_BOX_CORNER_RADIUS,
                      null, null, 'rectangle');
        }

        DrawTitle(ctx, node, style);
        DrawNodeLogo(ctx, node, style,
                     node.position.left + node.temp.width - 29,
                     node.position.top+1, true);
        DrawNodeConnectors(ctx, node, style, 'left', node.temp.type_obj.inputs,
                         node.temp.inputs_areas, node.temp.focused_input, 15, true);
        DrawNodeConnectors(ctx, node, style, 'right',node.temp.type_obj.outputs,
                         node.temp.outputs_areas, node.temp.focused_output,-15, true);
    };


    function DrawNode(ctx, node) {
        var style = current_theme.node[node.temp.type_obj.style];
        
        switch(node.temp.type_obj.style) {
            case $scope.NodeStyle.INPUT_NODE:
                DrawInputNode(ctx, node, style);
                break;
            case $scope.NodeStyle.CALCULATION_NODE:
                DrawCalculationNode(ctx, node, style);
                break;
            case $scope.NodeStyle.OUTPUT_NODE:
                DrawOutputNode(ctx, node, style);
                break;
            case $scope.NodeStyle.DATA_NODE:
                DrawDataNode(ctx, node, style);
                break;
            case $scope.NodeStyle.NULL_CONNECTION:
                DrawNullConnection(ctx, node, style);
                break;
            case $scope.NodeStyle.GRAPH_NODE:
            case $scope.NodeStyle.EXTERNAL_VIEWER_NODE:
                DrawGraphNode(ctx, node, style);
                break;
            case $scope.NodeStyle.PIPELINE_NODE:
                DrawPipelineNode(ctx, node, style);
                break;
            case $scope.NodeStyle.COMMENT_NODE:
                DrawCommentNode(ctx, node, style);
                break;
        };
    };
    

    function DrawEditorType() {
        $scope.ctx.save();
        $scope.ctx.fillStyle = "rgba(255,255,0,0.1)";
        $scope.ctx.strokeStyle = "rgba(255,255,0,0.1)";
        $scope.ctx.shadowColor = 'red';
        $scope.ctx.shadowOffsetX = 2;
        $scope.ctx.shadowOffsetY = 2;
        $scope.ctx.shadowBlur = 10 ;
        $scope.ctx.lineWidth = 0.20;

        switch($scope.GetEditorType()) {
            case $scope.FileType.EXPERIMENT:
                $scope.ctx.drawImage(arrays.FindArrayElementById(images, $scope.IconImage.ICON_CALCULATION).image, $scope.DocsNavTabs.selected_tab.page.CanvasPosition.x + 0, $scope.DocsNavTabs.selected_tab.page.CanvasPosition.y + 0, 290, 280);
                break;
            case $scope.FileType.PIPELINE:
                $scope.ctx.drawImage(arrays.FindArrayElementById(images, $scope.IconImage.ICON_PIPELINE).image, $scope.DocsNavTabs.selected_tab.page.CanvasPosition.x + 0, $scope.DocsNavTabs.selected_tab.page.CanvasPosition.y + 0, 290, 280);
                break;
        };
        $scope.ctx.restore();
    };

    function DrawPageTitleBox(ctx, x, y, min_box_width) {
/*
        var labels = "";
        var descriptions = "";

        var properties      = GetCurrentDocument().properties;
        var properties_keys = Object.keys(properties);
        var tab_space       = 175;
        var line_height     = 40;
        var cell_span       = 20;
        var box_width       = 1000;

        for (var i = 0; i < properties_keys.length; i++) {
          var key = properties_keys[i];
          if (key != 'type') {
            if (properties[properties_keys[i]] != "") {
              labels += BeautifierKey(key);
              labels += "<br />";
              descriptions += properties[properties_keys[i]];
              descriptions += "<br />";
            }
          }
        }

        DrawTextRect($scope.ctx, fonts.PageHeaderLabel, fonts.PageHeaderLabel, current_theme.CANVAS_BIG_LINES_COLOR, labels,       x,             y, tab_space, line_height, line_height, cell_span, true, false, false, null, null, null, null, null);
        DrawTextRect($scope.ctx, fonts.PageHeaderText,  fonts.PageHeaderText,  current_theme.CANVAS_BIG_LINES_COLOR, descriptions, x + tab_space, y, box_width, line_height, line_height, cell_span, true, false, false, null, null, null, null, null);
*/

        var descriptions = "";

        var properties      = GetCurrentDocument().properties;
        var properties_keys = Object.keys(properties);
        var line_height     = 40;
        var cell_span       = 20;
        var box_width       = 1000;
        var fontType        = fonts.PageHeaderText;

        for (var i = 0; i < properties_keys.length; i++) {
          var key = properties_keys[i];
          if (key != 'type') {
            if (properties[properties_keys[i]] != "") {
              switch(key) {
                case 'type':
                  fontType = null;
                  break;
                case 'name':
                  fontType = fonts.PageHeaderName;
                  break;
                case 'email':
                  fontType = fonts.PageHeaderAuthor;
                  break;
                case 'date':                
                  fontType = null;
                  break;
                case 'description':
                  fontType = fonts.PageHeaderAuthor;
                  break;
              }             

              if (fontType != null) {
                dimensions = DrawTextRect($scope.ctx, fontType,  fontType,  current_theme.CANVAS_TITLE_BOX_FONT_COLOR, properties[properties_keys[i]], x, y, box_width, line_height, line_height, cell_span, true, false, false, null, null, null, null, null);
                y += dimensions.height - 40;
              }
            }
          }
        }
    };

    function DrawPage(x, y, width, height, page_info) {
        var left       = ($scope.paint_page_borders)?(x * width):0;
        var top        = ($scope.paint_page_borders)?(y * height):0;
        var border_padding = ($scope.paint_page_borders)?100:0;

        width -= 20;
        height -= 20;

        DrawRect($scope.ctx, left, top,
                 //width, height, // <----------- page fixed size
                 page_info.width, page_info.height, // <--------------- page not fixed size
                 1, ($scope.paint_page_borders)?'black':'white', {tl: 0, tr: 0, br: 0, bl: 0},
                 current_theme.PAPER_BACKGROUND_COLOR, ($scope.paint_page_borders)?'black':null, 'rectangle');

        //DrawEditorType();
        if ($scope.ShowGrid == true) {
            DrawGridLines($scope.ctx, left + border_padding, top + border_padding, page_info.width - border_padding*2, page_info.height - border_padding*2,
                          0.1, current_theme.CANVAS_SMALL_LINES_COLOR,
                          current_theme.CANVAS_SMALL_LINES_DISTANCE);

            DrawGridLines($scope.ctx, left + border_padding, top + border_padding, page_info.width - border_padding*2, page_info.height - border_padding*2,
                          0.4, current_theme.CANVAS_BIG_LINES_COLOR,
                          current_theme.CANVAS_BIG_LINES_DISTANCE);
        }

        DrawRect($scope.ctx, left + border_padding, top + border_padding,
                 page_info.width - border_padding*2, page_info.height - border_padding*2,
                 2, current_theme.CANVAS_BIG_LINES_COLOR, {tl: 0, tr: 0, br: 0, bl: 0},
                 null, null, 'rectangle');

        DrawPageTitleBox($scope.ctx, x + border_padding + 2, y + border_padding + 2, current_theme.CANVAS_BIG_LINES_DISTANCE * 9);
    };

    function BeautifierKey(key) {
      var ret = key;
      switch(key) {
        case 'type': ret = 'Type:'; break;
        case 'name': ret = 'Name:'; break;
        case 'email': ret = 'Author/s:'; break;
        case 'date': ret = 'Date:'; break;
        case 'description': ret = 'Description:'; break;
        case 'loop_name': ret = 'Loop Name:'; break;
      }
      return ret;
    }

    function DrawScene() {
        if (drawing) return;

        //console.log("drawing scene...");

        drawing = true;

        ClearCanvas($scope.ctx,
                    $scope.paper.width * 100,
                    $scope.paper.height * 100,
                    ($scope.paint_page_borders)?current_theme.CANVAS_BACKGROUND_COLOR:'white');

//        for (i = 0; i < num_papers.x; i++) {
//            for (j = 0; j < num_papers.y; j++) {
//            }
//        }

        DrawPage(0, 0, $scope.paper.width, $scope.paper.height, GetCurrentDocument().page);

        GetCurrentDocumentNodes().forEach(function(node) {
            DrawNodeConnections($scope.ctx, node,
                                current_theme.CONNECTOR_LINE_COLOR,
                                current_theme.CONNECTOR_LINE_WIDTH,
                                current_theme.CONNECTOR_LINE_SHADOW);
        });


        // Draw nodes and Calculate page dimensions for the current graph

        if (GetCurrentDocumentNodes().length != 0) {
          GetCurrentDocument().page.width = current_theme.DRAWING_WIDTH;
          GetCurrentDocument().page.height = current_theme.DRAWING_HEIGHT;
        }

        GetCurrentDocumentNodes().forEach(function(node) {
            DrawNode($scope.ctx, node);

            if (node.position.left + node.temp.width + 200 > GetCurrentDocument().page.width) {
              GetCurrentDocument().page.width = node.position.left + node.temp.width + 200;  // a little of right free space 
            }
            if (node.position.top + node.temp.height + 200 > GetCurrentDocument().page.height) {
              GetCurrentDocument().page.height = node.position.top + node.temp.height + 200;  // a little of bottom free space 
            }
        });

        if ($scope.debug_mode == true) {
            //DrawRect($scope.ctx, CanvasPosition.x, CanvasPosition.y,
              //           160, 40,
                //         1, 'black', 0,
                  //       'yellow', null, 'rectangle');
/*
            var editor_type = $scope.GetEditorType();
            if (editor_type == $scope.FileType.EXPERIMENT) {
              DrawText($scope.ctx, fonts.Default,
                      'black', null, "DEBUG MODE - EXPERIMENT", 
                       0, 30, "left");
            } else {
              if (editor_type == $scope.FileType.PIPELINE) {
                DrawText($scope.ctx, fonts.Default,
                        'black', null, "DEBUG MODE - PIPELINE", 
                         0, 30, "left");
              } else {
                DrawText($scope.ctx, fonts.Default,
                        'black', null, "DEBUG MODE", 
                         0, 30, "left");
              }
            }
*/
/*
            GetCurrentDocumentNodes().forEach(function(node) {
              node.temp.inputs_areas.forEach(function(area) {
                DrawRect($scope.ctx, node.position.left + area.left, node.position.top + area.top, area.width, area.height,
                         2, current_theme.CANVAS_BIG_LINES_COLOR, {tl: 0, tr: 0, br: 0, bl: 0},
                         null, 'black', 'rectangle');
              });
              node.temp.outputs_areas.forEach(function(area) {
                DrawRect($scope.ctx, node.position.left + area.left, node.position.top + area.top, area.width, area.height,
                         2, current_theme.CANVAS_BIG_LINES_COLOR, {tl: 0, tr: 0, br: 0, bl: 0},
                         null, 'black', 'rectangle');
              });
            });

*/
        }

        // =====================================================================
        // Show HELP
        // =====================================================================
        
        if (($scope.connector_selected != null) && ($scope.connector_selected.connector != null)) {
          if (($scope.connector_selected.node.temp.type_obj.style == $scope.NodeStyle.PIPELINE_NODE) ||
              ($scope.connector_selected.node.temp.type_obj.style == $scope.NodeStyle.CALCULATION_NODE)) {
            DrawHelpNodeConnector($scope.ctx,
                                  $scope.connector_selected,
                                  ($scope.InputConnectorSelected())?"input":"output",
                                  $scope.connector_selected.node.position.left + $scope.connector_selected.node.temp.width + 38,
                                  $scope.connector_selected.node.position.top - 45,
                                  current_theme);
          }
        } else {
          if ($scope.node_selected != null) {
            if ($scope.node_selected.temp.type_obj.style == $scope.NodeStyle.CALCULATION_NODE) {
              DrawHelpCalculationNode($scope.ctx,
                           $scope.node_selected,
                           $scope.node_selected.position.left + $scope.node_selected.temp.width + 38,
                           $scope.node_selected.position.top - 45,
                           current_theme);
            }
            if ($scope.node_selected.temp.type_obj.style == $scope.NodeStyle.PIPELINE_NODE) {
              DrawHelpPipelineNode($scope.ctx,
                           $scope.node_selected,
                           $scope.node_selected.position.left + $scope.node_selected.temp.width + 38,
                           $scope.node_selected.position.top - 45,
                           current_theme);
            }
          }
        }

        drawing = false;
    }


    function DrawHelpNodeConnector(ctx, connector, direction, x, y, current_theme) {
        var text = "";
        var help_defined = false;
  
        if (direction == "input") {
          connector_info = arrays.FindArrayElementById(connector.node.temp.type_obj.inputs, connector.connector.id);
        }
        if (direction == "output") {
          connector_info = arrays.FindArrayElementById(connector.node.temp.type_obj.outputs, connector.connector.id);
        }

        if ((connector_info != undefined) && (connector_info != null)) {
          if ((connector_info.group != undefined) &&
              (connector_info.group != "")) {
            if (help_defined) {  text += "\n"; }
            text += "<b>Group:</b>\n";
            text += connector_info.group;
            text += "\n";
            help_defined = true;
          }

          if ((connector_info.name != undefined) &&
              (connector_info.name != "")) {
            if (help_defined) {  text += "\n"; }
            text += ((direction=="input")?"<b>Input Name:</b>\n":"<b>Output Name:</b>\n");
            text += connector_info.name;
            text += "\n";
            help_defined = true;
          }

          if ((connector_info.type != undefined) &&
              (connector_info.type != "")) {
            if (help_defined) {  text += "\n"; }
            text += "<b>Type:</b>\n";
            text += connector_info.type;
            text += "\n";
            help_defined = true;
          }

          if ((connector_info.long_name != undefined) &&
              (connector_info.long_name != "")) {
            if (help_defined) {  text += "\n"; }
            text += "<b>Long Name:</b>\n";
            text += connector_info.long_name;
            text += "\n";
            help_defined = true;
          }

          if ((connector_info.description != undefined) &&
              (connector_info.description != "")) {
            if (help_defined) {  text += "\n"; }
            text += "<b>Description:</b>\n";
            text += connector_info.description;
            text += "\n";
            help_defined = true;
          }

          if ((connector_info.example != undefined) &&
              (connector_info.example != "")) {
            if (help_defined) {  text += "\n"; }
            text += "<b>Example:</b>\n";
            text += connector_info.example;
            text += "\n";
            help_defined = true;
          }

          if ((connector_info.only != undefined) &&
              (connector_info.only != "")) {
            if (help_defined) {  text += "\n"; }
            text += "<b>Use Only:</b>\n";
            text += connector_info.only;
            text += "\n";
            help_defined = true;
          }

          if ((connector_info.def_val != undefined) &&
              (connector_info.def_val != "")) {
            if (help_defined) {  text += "\n"; }
            text += "<b>Default Value:</b>\n";
            text += connector_info.def_val;
            text += "\n";
            help_defined = true;
          }

          if ((connector_info.min_value != undefined) &&
              (connector_info.min_value != "") &&
              (connector_info.max_value != NOT_DEFINED)) {
            if (help_defined) {  text += "\n"; }
            text += "<b>Minimum Value:</b>\n";
            text += connector_info.min_value;
            text += "\n";
            help_defined = true;
          }

          if ((connector_info.max_value != undefined) &&
              (connector_info.max_value != "") &&
              (connector_info.max_value != NOT_DEFINED)) {
            if (help_defined) {  text += "\n"; }
            text += "<b>Maximum Value:</b>\n";
            text += connector_info.max_value;
            text += "\n";
            help_defined = true;
          }

          if ((connector_info.required != undefined) &&
              (connector_info.required != "")) {
            if (help_defined) {  text += "\n"; }
            text += "<b>Required:</b>\n";
            text += (connector_info.required==1)?"Yes":"No";
            // text += "\n"; <-- The last one does not have an EOL here
            help_defined = true;
          }

          if (help_defined) {
            DrawTextRect(ctx,
                         fonts.HelpText,                 // font
                         fonts.HelpTextBold,             // highlight font
                         current_theme.HELP_TEXT_COLOR,
                         text,
                         x,
                         y,
                         current_theme.HELP_WIDTH,       // width
                         40,                             // height
                         18,                             // line_space
                         current_theme.HELP_CELL_SPAN,
                         true,                           // adapt_height
                         true,                           // draw_rect
                         'left',                         // draw arrow
                         current_theme.HELP_BORDER_WIDTH,
                         current_theme.HELP_BORDER_COLOR,
                         current_theme.HELP_RADIUS,
                         current_theme.HELP_BACKGROUND_COLOR,
                         current_theme.HELP_SHADOW);
          }
        }
    };

    function DrawHelpCalculationNode(ctx, node, x, y, current_theme) {
        var text = "";
        var help_defined = false;

        if ((node.temp.type_obj.brief_description != undefined) &&
            (node.temp.type_obj.brief_description != "")) {
          if (help_defined) {  text += "\n"; }
          text += "<b>Brief Description:</b>\n";
          text += node.temp.type_obj.brief_description;
          text += "\n";
          help_defined = true;
        }

        if ((node.temp.type_obj.authors != undefined) &&
            (node.temp.type_obj.authors != "")) {
          if (help_defined) {  text += "\n"; }
          text += "<b>Authors:</b>\n";
          text += node.temp.type_obj.authors;
          text += "\n";
          help_defined = true;
        }

        if ((node.temp.type_obj.copyright != undefined) &&
            (node.temp.type_obj.copyright != "")) {
          if (help_defined) {  text += "\n"; }
          text += "<b>Copyright:</b>\n";
          text += node.temp.type_obj.copyright;
          text += "\n";
          help_defined = true;
        }

        if ((node.temp.type_obj.citations != undefined) &&
            (node.temp.type_obj.citations != "")) {
          if (help_defined) {  text += "\n"; }
          text += "<b>Citations:</b>\n";
          text += node.temp.type_obj.citations;
          text += "\n";
          help_defined = true;
        }

        if ((node.temp.type_obj.see_also != undefined) &&
            (node.temp.type_obj.see_also != "")) {
          if (help_defined) {  text += "\n"; }
          text += "<b>See_also:</b>\n";
          text += node.temp.type_obj.see_also;
          text += "\n";
          help_defined = true;
        }

        if ((node.temp.type_obj.description != undefined) &&
            (node.temp.type_obj.description != "")) {
          if (help_defined) {  text += "\n"; }
          text += "<b>Description:</b>\n";
          text += node.temp.type_obj.description;
          // text += "\n"; <-- The last one does not have an EOL here
          help_defined = true;
        }

        if (help_defined) {
          DrawTextRect(ctx,
                       fonts.HelpText,                 // font
                       fonts.HelpTextBold,             // highlight font
                       current_theme.HELP_TEXT_COLOR,
                       text,
                       x,
                       y,
                       current_theme.HELP_WIDTH,       // width
                       40,                             // height
                       18,                             // line_space
                       current_theme.HELP_CELL_SPAN,
                       true,                           // adapt_height
                       true,                           // draw_rect
                       'left',                         // draw arrow
                       current_theme.HELP_BORDER_WIDTH,
                       current_theme.HELP_BORDER_COLOR,
                       current_theme.HELP_RADIUS,
                       current_theme.HELP_BACKGROUND_COLOR,
                       current_theme.HELP_SHADOW);
        }
    };

    function DrawHelpPipelineNode(ctx, node, x, y, current_theme) {
        var text = "";
        var help_defined = false;

        if ((node.temp.type_obj.properties.name != undefined) &&
            (node.temp.type_obj.properties.name != "")) {
          if (help_defined) {  text += "\n"; }
          text += "<b>Pipeline Name:</b>\n";
          text += node.temp.type_obj.properties.name;
          text += "\n";
          help_defined = true;
        }

        if ((node.temp.type_obj.properties.email != undefined) &&
            (node.temp.type_obj.properties.email != "")) {
          if (help_defined) {  text += "\n"; }
          text += "<b>Authors:</b>\n";
          text += node.temp.type_obj.properties.email;
          text += "\n";
          help_defined = true;
        }

        if ((node.temp.type_obj.properties.description != undefined) &&
            (node.temp.type_obj.properties.description != "")) {
          if (help_defined) {  text += "\n"; }
          text += "<b>Description:</b>\n";
          text += node.temp.type_obj.properties.description;
          text += "\n";
          help_defined = true;
        }

        if ((node.temp.type_obj.properties.loop_name != undefined) &&
            (node.temp.type_obj.properties.loop_name != "")) {
          if (help_defined) {  text += "\n"; }
          text += "<b>Loop Name:</b>\n";
          text += node.temp.type_obj.properties.loop_name;
          text += "\n";
          help_defined = true;
        }

        if ((node.temp.type_obj.properties.inputs != undefined) &&
            (node.temp.type_obj.properties.inputs != "")) {
          if (help_defined) {  text += "\n"; }
          text += "<b>Inputs Description:</b>\n";
          text += node.temp.type_obj.properties.inputs;
          text += "\n";
          help_defined = true;
        }

        if ((node.temp.type_obj.properties.outputs != undefined) &&
            (node.temp.type_obj.properties.outputs != "")) {
          if (help_defined) {  text += "\n"; }
          text += "<b>Outputs Description:</b>\n";
          text += node.temp.type_obj.properties.outputs;
          text += "\n";
          help_defined = true;
        }

        if ((node.temp.type_obj.properties.date != undefined) &&
            (node.temp.type_obj.properties.date != "")) {
          if (help_defined) {  text += "\n"; }
          text += "<b>Date:</b>\n";
          text += node.temp.type_obj.properties.date;
          // text += "\n"; <-- The last one does not have an EOL here
          help_defined = true;
        }

        if (help_defined) {
          DrawTextRect(ctx,
                       fonts.HelpText,                 // font
                       fonts.HelpTextBold,             // highlight font
                       current_theme.HELP_TEXT_COLOR,
                       text,
                       x,
                       y,
                       current_theme.HELP_WIDTH,       // width
                       40,                             // height
                       18,                             // line_space
                       current_theme.HELP_CELL_SPAN,
                       true,                           // adapt_height
                       true,                           // draw_rect
                       'left',                         // draw arrow
                       current_theme.HELP_BORDER_WIDTH,
                       current_theme.HELP_BORDER_COLOR,
                       current_theme.HELP_RADIUS,
                       current_theme.HELP_BACKGROUND_COLOR,
                       current_theme.HELP_SHADOW);
        }
    };

    ////////////////////////////////////////////////////////////////////////////
    // CANVAS STYLE
    ////////////////////////////////////////////////////////////////////////////

    var themes = [
        // CRAG
        {
            // CANVAS
            PAPER_BACKGROUND_COLOR: '#fff', //010 //#efefef
            CANVAS_BACKGROUND_COLOR: '#eee', //bbb
            CANVAS_TITLE_BOX_FONT_COLOR: '#6faf6f',
            CANVAS_BIG_LINES_DISTANCE: 100,
            CANVAS_BIG_LINES_COLOR: '#6faf6f',
            CANVAS_SMALL_LINES_COLOR: '#6faf6f',
            CANVAS_SMALL_LINES_DISTANCE: 25,
            INPUT_BACKGROUND_COLOR: '#fff',
            INPUT_TEXT_COLOR: '#000',
            DRAWING_WIDTH: 2000,
            DRAWING_HEIGHT: 1400,
            CONNECTOR_LINE_COLOR: '#aca', //#8d9a85', //'#6f845f',
            CONNECTOR_LINE_WIDTH: 2,
            CONNECTOR_LINE_SHADOW: 'lightgray',
            // Help style
            HELP_WIDTH: 400,
            HELP_CELL_SPAN: 15,
            HELP_TEXT_COLOR: '#445f2e',
            HELP_BORDER_WIDTH: 2,
            HELP_BORDER_COLOR: 'rgba(144,155,144,0.8)',
            HELP_RADIUS: {tl: 5, tr: 5, br: 5, bl: 5},
            HELP_BACKGROUND_COLOR: 'rgba(244,255,244,1)', //'rgba(255,255,224,1)', //
            HELP_SHADOW: 'gray',
            PIPELINE_BACKGROUND_COLOR: '#EAF2CB',

            node: [
                {   // CALCULATION
                    NODE_TITLE_HEIGHT: 30,
                    MIN_NODE_WIDTH: 16,
                    MIN_NODE_HEIGHT: 16,
                    NODE_BACKGROUND_COLOR: '#fff',
                    NODE_BOX_CORNER_RADIUS: 0,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: '#6f845f',
                    NODE_SELECTED_BORDER_COLOR: '#99d651',
                    TITLE_BACKGROUND_COLOR: '#445f2e',
                    TITLE_TEXT_COLOR: '#fff', // #99d651
                    CONNECTOR_TEXT_COLOR: '#445f2e',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null,
                    CONNECTOR_OPEN_COLOR: 'white',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: '#6f845f',
                    NODE_DISABLED_COLOR: '#eee',
                },
                {   // INPUT
                    NODE_TITLE_HEIGHT: 0,
                    MIN_NODE_WIDTH: 200,
                    MIN_NODE_HEIGHT: 50,
                    NODE_BACKGROUND_COLOR: '#fff',
                    NODE_BOX_CORNER_RADIUS: 0,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 0,
                    NODE_BORDER_COLOR: '#6f845f',
                    NODE_SELECTED_BORDER_COLOR: '#99d651',
                    TITLE_BACKGROUND_COLOR: '#445f2e',
                    TITLE_TEXT_COLOR: '#fff',  //445f2e
                    CONNECTOR_TEXT_COLOR: '#445f2e',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null,
                    CONNECTOR_OPEN_COLOR: 'white',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: '#6f845f',
                    NODE_DISABLED_COLOR: '#eee',
                },
                {   // OUTPUT
                    NODE_TITLE_HEIGHT: 0,
                    MIN_NODE_WIDTH: 200,
                    MIN_NODE_HEIGHT: 50,
                    NODE_BACKGROUND_COLOR: '#fff',
                    NODE_BOX_CORNER_RADIUS: 0,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 0,
                    NODE_BORDER_COLOR: '#6f845f',
                    NODE_SELECTED_BORDER_COLOR: '#99d651',
                    TITLE_BACKGROUND_COLOR: '#445f2e',
                    TITLE_TEXT_COLOR: '#fff',
                    CONNECTOR_TEXT_COLOR: '#445f2e',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null,
                    CONNECTOR_OPEN_COLOR: 'white',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: '#6f845f',
                    NODE_DISABLED_COLOR: '#eee',
                },
                {   // GRAPH
                    NODE_TITLE_HEIGHT: 30,
                    MIN_NODE_WIDTH: 200,
                    MIN_NODE_HEIGHT: 125,
                    NODE_BACKGROUND_COLOR: '#fff',
                    NODE_BOX_CORNER_RADIUS: 0,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: '#6f845f',
                    NODE_SELECTED_BORDER_COLOR: '#99d651',
                    TITLE_BACKGROUND_COLOR: '#445f2e',
                    TITLE_TEXT_COLOR: '#fff',
                    CONNECTOR_TEXT_COLOR: '#445f2e',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null,
                    CONNECTOR_OPEN_COLOR: 'white',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: '#6f845f',
                    NODE_DISABLED_COLOR: '#eee',
                },
                {   // DATA
                    NODE_TITLE_HEIGHT: 30,
                    MIN_NODE_WIDTH: 180,
                    MIN_NODE_HEIGHT: 50,
                    NODE_BACKGROUND_COLOR: '#fff',
                    NODE_BOX_CORNER_RADIUS: 0,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: '#6f845f',
                    NODE_SELECTED_BORDER_COLOR: '#99d651',
                    TITLE_BACKGROUND_COLOR: '#445f2e',
                    TITLE_TEXT_COLOR: '#fff',
                    CONNECTOR_TEXT_COLOR: '#445f2e',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null,
                    CONNECTOR_OPEN_COLOR: 'white',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: '#6f845f',
                    NODE_DISABLED_COLOR: '#eee',
                },
                {   // PIPELINE
                    NODE_TITLE_HEIGHT: 30,
                    MIN_NODE_WIDTH: 150,
                    MIN_NODE_HEIGHT: 50,
                    NODE_BACKGROUND_COLOR: '#fff',
                    NODE_BOX_CORNER_RADIUS: 0,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: '#6f845f',
                    NODE_SELECTED_BORDER_COLOR: '#99d651',
                    TITLE_BACKGROUND_COLOR: '#445f2e',
                    TITLE_TEXT_COLOR: '#fff',
                    CONNECTOR_TEXT_COLOR: '#445f2e',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null,
                    CONNECTOR_OPEN_COLOR: 'white',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: '#6f845f',
                    NODE_DISABLED_COLOR: '#eee',

                    NODE_LOOP_COLOR: '#b1c4a1', // <-- Only in Pipeline Nodes
                },            
                {   // NULL_CONNECTION
                    NODE_TITLE_HEIGHT: 0,
                    MIN_NODE_WIDTH: 16,
                    MIN_NODE_HEIGHT: 16,
                    NODE_BACKGROUND_COLOR: '#fff',
                    NODE_BOX_CORNER_RADIUS: 0,
                    CONNECTOR_HEIGHT: 0,
                    CONNECTOR_WIDTH: 0,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: '#6f845f',
                    NODE_SELECTED_BORDER_COLOR: '#99d651',
                    TITLE_BACKGROUND_COLOR: '#445f2e',
                    TITLE_TEXT_COLOR: '#fff',
                    CONNECTOR_TEXT_COLOR: '#445f2e',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null,
                    CONNECTOR_OPEN_COLOR: 'white',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: '#6f845f',
                    NODE_DISABLED_COLOR: '#eee',
                },
                {   // COMMENT_NODE
                    NODE_TITLE_HEIGHT: 30,
                    MIN_NODE_WIDTH: 280,
                    MIN_NODE_HEIGHT: 100,
                    NODE_BACKGROUND_COLOR: '#ffeeaa',
                    NODE_BOX_CORNER_RADIUS: 0,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: '#6f845f',
                    NODE_SELECTED_BORDER_COLOR: '#99d651',
                    TITLE_BACKGROUND_COLOR: '#445f2e',
                    TITLE_TEXT_COLOR: '#fff',
                    CONNECTOR_TEXT_COLOR: '#445f2e',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null,
                    CONNECTOR_OPEN_COLOR: 'white',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: '#6f845f',
                    NODE_DISABLED_COLOR: '#eee',
                },
                {   // EXTERNAL_VIEWER_NODE
                    NODE_TITLE_HEIGHT: 30,
                    MIN_NODE_WIDTH: 200,
                    MIN_NODE_HEIGHT: 125,
                    NODE_BACKGROUND_COLOR: '#fff',
                    NODE_BOX_CORNER_RADIUS: 0,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: '#6f845f',
                    NODE_SELECTED_BORDER_COLOR: '#99d651',
                    TITLE_BACKGROUND_COLOR: '#445f2e',
                    TITLE_TEXT_COLOR: '#fff',
                    CONNECTOR_TEXT_COLOR: '#445f2e',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null,
                    CONNECTOR_OPEN_COLOR: 'white',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: '#6f845f',
                    NODE_DISABLED_COLOR: '#eee',
                },
            ],
        },
        // Modern
        {
            // CANVAS
            PAPER_BACKGROUND_COLOR: '#ddd',
            CANVAS_BACKGROUND_COLOR: '#eee',
            CANVAS_TITLE_BOX_FONT_COLOR: '#989898',
            CANVAS_BIG_LINES_DISTANCE: 100,
            CANVAS_BIG_LINES_COLOR: '#bababa',
            CANVAS_SMALL_LINES_COLOR: '#999',
            CANVAS_SMALL_LINES_DISTANCE: 25,
            INPUT_BACKGROUND_COLOR: '#ddd',
            INPUT_TEXT_COLOR: '#000',
            DRAWING_WIDTH: 2000,
            DRAWING_HEIGHT: 1400,
            CONNECTOR_LINE_COLOR: 'gray', //'#888',
            CONNECTOR_LINE_WIDTH: 2,
            CONNECTOR_LINE_SHADOW: 'lightgray',
            // Help style
            HELP_WIDTH: 400,
            HELP_CELL_SPAN: 15,
            HELP_TEXT_COLOR: 'black',
            HELP_BORDER_WIDTH: 2,
            HELP_BORDER_COLOR: 'black',
            HELP_RADIUS: {tl: 5, tr: 5, br: 5, bl: 5},
            HELP_BACKGROUND_COLOR: 'lightyellow',
            HELP_SHADOW: 'gray',
            PIPELINE_BACKGROUND_COLOR: '#f0b',

            node: [
                {
                    // NODE
                    NODE_TITLE_HEIGHT: 30,
                    MIN_NODE_WIDTH: 150,
                    MIN_NODE_HEIGHT: 50,
                    NODE_BACKGROUND_COLOR: '#ddd',
                    NODE_BOX_CORNER_RADIUS: 0,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: '#888',
                    NODE_SELECTED_BORDER_COLOR: '#4285f4',
                    TITLE_BACKGROUND_COLOR: '#4285f4',
                    TITLE_TEXT_COLOR: 'white',
                    CONNECTOR_TEXT_COLOR: 'black',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null,
                    CONNECTOR_OPEN_COLOR: 'white',
                    CONNECTOR_CLOSED_COLOR: 'yellow',
                    FRAMEWORK_COLOR: 'white',
                    NODE_DISABLED_COLOR: '#ddd',
                },
                 {   // INPUT
                    NODE_TITLE_HEIGHT: 0,
                    MIN_NODE_WIDTH: 200,
                    MIN_NODE_HEIGHT: 50,
                    NODE_BACKGROUND_COLOR: '#ddd',
                    NODE_BOX_CORNER_RADIUS: 0,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 0,
                    NODE_BORDER_COLOR: '#888',
                    NODE_SELECTED_BORDER_COLOR: '#4285f4',
                    TITLE_BACKGROUND_COLOR: '#4285f4',
                    TITLE_TEXT_COLOR: 'white',
                    CONNECTOR_TEXT_COLOR: 'black',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null,
                    CONNECTOR_OPEN_COLOR: 'white',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: 'white',
                    NODE_DISABLED_COLOR: '#ddd',
                },
                {   // OUTPUT
                    NODE_TITLE_HEIGHT: 0,
                    MIN_NODE_WIDTH: 200,
                    MIN_NODE_HEIGHT: 50,
                    NODE_BACKGROUND_COLOR: '#ddd',
                    NODE_BOX_CORNER_RADIUS: 0,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 0,
                    NODE_BORDER_COLOR: '#888',
                    NODE_SELECTED_BORDER_COLOR: '#4285f4',
                    TITLE_BACKGROUND_COLOR: '#4285f4',
                    TITLE_TEXT_COLOR: 'white',
                    CONNECTOR_TEXT_COLOR: 'black',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null,
                    CONNECTOR_OPEN_COLOR: 'white',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: 'white',
                    NODE_DISABLED_COLOR: '#ddd',
                },
                {   // GRAPH
                    NODE_TITLE_HEIGHT: 30,
                    MIN_NODE_WIDTH: 200,
                    MIN_NODE_HEIGHT: 125,
                    NODE_BACKGROUND_COLOR:  '#ddd',
                    NODE_BOX_CORNER_RADIUS: 0,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: '#888',
                    NODE_SELECTED_BORDER_COLOR: '#4285f4',
                    TITLE_BACKGROUND_COLOR: '#4285f4',
                    TITLE_TEXT_COLOR: 'white',
                    CONNECTOR_TEXT_COLOR: 'black',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null,
                    CONNECTOR_OPEN_COLOR: 'white',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: '#888',
                    NODE_DISABLED_COLOR: '#ddd',
                },
                {   // DATA
                    NODE_TITLE_HEIGHT: 30,
                    MIN_NODE_WIDTH: 180,
                    MIN_NODE_HEIGHT: 50,
                    NODE_BACKGROUND_COLOR: '#ddd',
                    NODE_BOX_CORNER_RADIUS: 0,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: '#888',
                    NODE_SELECTED_BORDER_COLOR: '#4285f4',
                    TITLE_BACKGROUND_COLOR: '#4285f4',
                    TITLE_TEXT_COLOR: 'white',
                    CONNECTOR_TEXT_COLOR: 'black',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null,
                    CONNECTOR_OPEN_COLOR: 'white',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: 'white',
                    NODE_DISABLED_COLOR: '#ddd',
                },
                {   // PIPELINE
                    NODE_TITLE_HEIGHT: 30,
                    MIN_NODE_WIDTH: 150,
                    MIN_NODE_HEIGHT: 50,
                    NODE_BACKGROUND_COLOR: '#ddd',
                    NODE_BOX_CORNER_RADIUS: 0,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: '#888',
                    NODE_SELECTED_BORDER_COLOR: '#4285f4',
                    TITLE_BACKGROUND_COLOR: '#4285f4',
                    TITLE_TEXT_COLOR: 'white',
                    CONNECTOR_TEXT_COLOR: 'black',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null,
                    CONNECTOR_OPEN_COLOR: 'white',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: 'white',
                    NODE_DISABLED_COLOR: '#ddd',

                    NODE_LOOP_COLOR: '#eee', // <-- Only in Pipeline Nodes
                }, 
                {   // NULL_CONNECTION
                    NODE_TITLE_HEIGHT: 0,
                    MIN_NODE_WIDTH: 16,
                    MIN_NODE_HEIGHT: 16,
                    NODE_BACKGROUND_COLOR: '#ddd',
                    NODE_BOX_CORNER_RADIUS: 0,
                    CONNECTOR_HEIGHT: 0,
                    CONNECTOR_WIDTH: 0,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: '#888',
                    NODE_SELECTED_BORDER_COLOR: '#4285f4',
                    TITLE_BACKGROUND_COLOR: '#4285f4',
                    TITLE_TEXT_COLOR: 'white',
                    CONNECTOR_TEXT_COLOR: 'black',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null,
                    CONNECTOR_OPEN_COLOR: 'white',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: 'white',
                    NODE_DISABLED_COLOR: '#ddd',
                },
                {   // COMMENT_NODE
                    NODE_TITLE_HEIGHT: 30,
                    MIN_NODE_WIDTH: 180,
                    MIN_NODE_HEIGHT: 50,
                    NODE_BACKGROUND_COLOR: '#ddd',
                    NODE_BOX_CORNER_RADIUS: 0,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: '#888',
                    NODE_SELECTED_BORDER_COLOR: '#4285f4',
                    TITLE_BACKGROUND_COLOR: '#4285f4',
                    TITLE_TEXT_COLOR: 'white',
                    CONNECTOR_TEXT_COLOR: 'black',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null,
                    CONNECTOR_OPEN_COLOR: 'white',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: 'white',
                    NODE_DISABLED_COLOR: '#ddd',
                },
                {   // EXTERNAL_VIEWER_NODE
                    NODE_TITLE_HEIGHT: 30,
                    MIN_NODE_WIDTH: 200,
                    MIN_NODE_HEIGHT: 125,
                    NODE_BACKGROUND_COLOR: '#fff',
                    NODE_BOX_CORNER_RADIUS: 0,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: '#6f845f',
                    NODE_SELECTED_BORDER_COLOR: '#99d651',
                    TITLE_BACKGROUND_COLOR: '#445f2e',
                    TITLE_TEXT_COLOR: '#fff',
                    CONNECTOR_TEXT_COLOR: '#445f2e',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null,
                    CONNECTOR_OPEN_COLOR: 'white',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: '#6f845f',
                    NODE_DISABLED_COLOR: '#eee',
                },
            ],
        },
        // Dark
        {
            // CANVAS
            PAPER_BACKGROUND_COLOR: '#555', //'#eee', '#393939'
            CANVAS_BACKGROUND_COLOR: '#333', //',
            CANVAS_TITLE_BOX_FONT_COLOR: '#323232',
            CANVAS_BIG_LINES_DISTANCE: 100,
            CANVAS_BIG_LINES_COLOR: '#444', //'#212121',
            CANVAS_SMALL_LINES_COLOR: '#222', //'#000',
            CANVAS_SMALL_LINES_DISTANCE: 25,
            INPUT_BACKGROUND_COLOR: '#535353',
            INPUT_TEXT_COLOR: '#000',
            DRAWING_WIDTH: 2000,
            DRAWING_HEIGHT: 1400,
            CONNECTOR_LINE_COLOR: 'gray', //'black',
            CONNECTOR_LINE_WIDTH: 1,
            CONNECTOR_LINE_SHADOW: 'black',
            // Help style
            HELP_WIDTH: 400,
            HELP_CELL_SPAN: 15,
            HELP_TEXT_COLOR: 'black',
            HELP_BORDER_WIDTH: 2,
            HELP_BORDER_COLOR: 'black',
            HELP_RADIUS: {tl: 5, tr: 5, br: 5, bl: 5},
            HELP_BACKGROUND_COLOR: 'lightyellow',
            HELP_SHADOW: 'gray',
            PIPELINE_BACKGROUND_COLOR: '#f0b',

            node: [
                {
                    // NODE
                    NODE_TITLE_HEIGHT: 30,
                    MIN_NODE_WIDTH: 150,
                    MIN_NODE_HEIGHT: 50,
                    NODE_BACKGROUND_COLOR: 'rgba(255,255,255,0.2)',
                    NODE_BOX_CORNER_RADIUS: 15,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: 'black',
                    NODE_SELECTED_BORDER_COLOR: 'orange',
                    TITLE_BACKGROUND_COLOR: '#222',
                    TITLE_TEXT_COLOR: '#aaa',
                    CONNECTOR_TEXT_COLOR: 'black',
                    CONNECTOR_TEXT_WIDTH: '700',
                    CONNECTOR_TEXT_SHADOW_COLOR: null, //'#8e8e8e',
                    CONNECTOR_OPEN_COLOR: '#999',
                    CONNECTOR_CLOSED_COLOR: 'yellow',
                    FRAMEWORK_COLOR: '#222',
                    NODE_DISABLED_COLOR: '#ddd',
                },
                {   // INPUT
                    NODE_TITLE_HEIGHT: 0,
                    MIN_NODE_WIDTH: 200,
                    MIN_NODE_HEIGHT: 50,
                    NODE_BACKGROUND_COLOR: 'rgba(255,255,255,0.2)',
                    NODE_BOX_CORNER_RADIUS: 15,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 0,
                    NODE_BORDER_COLOR: 'black',
                    NODE_SELECTED_BORDER_COLOR: 'orange',
                    TITLE_BACKGROUND_COLOR: '#222',
                    TITLE_TEXT_COLOR: '#aaa',
                    CONNECTOR_TEXT_COLOR: 'black',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null, //'#8e8e8e',
                    CONNECTOR_OPEN_COLOR: '#999',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: '#222',
                    NODE_DISABLED_COLOR: '#ddd',
                },
                {   // OUTPUT
                    NODE_TITLE_HEIGHT: 0,
                    MIN_NODE_WIDTH: 200,
                    MIN_NODE_HEIGHT: 50,
                    NODE_BACKGROUND_COLOR: 'rgba(255,255,255,0.2)',
                    NODE_BOX_CORNER_RADIUS: 15,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 0,
                    NODE_BORDER_COLOR: 'black',
                    NODE_SELECTED_BORDER_COLOR: 'orange',
                    TITLE_BACKGROUND_COLOR: '#222',
                    TITLE_TEXT_COLOR: '#aaa',
                    CONNECTOR_TEXT_COLOR: 'black',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null, //'#8e8e8e',
                    CONNECTOR_OPEN_COLOR: '#999',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: '#222',
                    NODE_DISABLED_COLOR: '#ddd',
                },
                {   // GRAPH
                    NODE_TITLE_HEIGHT: 30,
                    MIN_NODE_WIDTH: 200,
                    MIN_NODE_HEIGHT: 125,
                    NODE_BACKGROUND_COLOR: 'rgba(255,255,255,0.2)', /* 'rgba(0,0,0,0.5)',*/
                    NODE_BOX_CORNER_RADIUS: 15,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: 'black',
                    NODE_SELECTED_BORDER_COLOR: 'orange',
                    TITLE_BACKGROUND_COLOR: '#222',
                    TITLE_TEXT_COLOR: '#aaa',
                    CONNECTOR_TEXT_COLOR: 'black',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null, //'#8e8e8e',
                    CONNECTOR_OPEN_COLOR: '#999',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: '#222',
                    NODE_DISABLED_COLOR: '#ddd',
                },
                {   // DATA
                    NODE_TITLE_HEIGHT: 30,
                    MIN_NODE_WIDTH: 180,
                    MIN_NODE_HEIGHT: 50,
                    NODE_BACKGROUND_COLOR: 'rgba(255,255,255,0.2)',
                    NODE_BOX_CORNER_RADIUS: 15,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: 'black',
                    NODE_SELECTED_BORDER_COLOR: 'orange',
                    TITLE_BACKGROUND_COLOR: '#222',
                    TITLE_TEXT_COLOR: '#aaa',
                    CONNECTOR_TEXT_COLOR: 'black',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null, //'#8e8e8e',
                    CONNECTOR_OPEN_COLOR: '#999',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: '#222',
                    NODE_DISABLED_COLOR: '#ddd',
                },
                {   // PIPELINE
                    NODE_TITLE_HEIGHT: 30,
                    MIN_NODE_WIDTH: 150,
                    MIN_NODE_HEIGHT: 50,
                    NODE_BACKGROUND_COLOR: 'rgba(255,255,255,0.2)',
                    NODE_BOX_CORNER_RADIUS: 15,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: 'black',
                    NODE_SELECTED_BORDER_COLOR: 'orange',
                    TITLE_BACKGROUND_COLOR: '#222',
                    TITLE_TEXT_COLOR: '#aaa',
                    CONNECTOR_TEXT_COLOR: 'black',
                    CONNECTOR_TEXT_WIDTH: '700',
                    CONNECTOR_TEXT_SHADOW_COLOR: null, //'#8e8e8e',
                    CONNECTOR_OPEN_COLOR: '#999',
                    CONNECTOR_CLOSED_COLOR: 'yellow',
                    FRAMEWORK_COLOR: '#222',
                    NODE_DISABLED_COLOR: '#ddd',

                    NODE_LOOP_COLOR: 'rgba(255,255,255,0.2)', // <-- Only in Pipeline Nodes
                }, 
                {   // NULL_CONNECTION
                    NODE_TITLE_HEIGHT: 0,
                    MIN_NODE_WIDTH: 16,
                    MIN_NODE_HEIGHT: 16,
                    NODE_BACKGROUND_COLOR: 'rgba(255,255,255,0.2)',
                    NODE_BOX_CORNER_RADIUS: 0,
                    CONNECTOR_HEIGHT: 0,
                    CONNECTOR_WIDTH: 0,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: 'black',
                    NODE_SELECTED_BORDER_COLOR: 'orange',
                    TITLE_BACKGROUND_COLOR: '#222',
                    TITLE_TEXT_COLOR: '#aaa',
                    CONNECTOR_TEXT_COLOR: 'black',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null, //'#8e8e8e',
                    CONNECTOR_OPEN_COLOR: '#999',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: '#222',
                    NODE_DISABLED_COLOR: '#ddd',
                },
                {   // COMMENT_NODE
                    NODE_TITLE_HEIGHT: 30,
                    MIN_NODE_WIDTH: 180,
                    MIN_NODE_HEIGHT: 50,
                    NODE_BACKGROUND_COLOR: 'rgba(255,255,255,0.2)',
                    NODE_BOX_CORNER_RADIUS: 15,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: 'black',
                    NODE_SELECTED_BORDER_COLOR: 'orange',
                    TITLE_BACKGROUND_COLOR: '#222',
                    TITLE_TEXT_COLOR: '#aaa',
                    CONNECTOR_TEXT_COLOR: 'black',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null, //'#8e8e8e',
                    CONNECTOR_OPEN_COLOR: '#999',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: '#222',
                    NODE_DISABLED_COLOR: '#ddd',
                },
                {   // EXTERNAL_VIEWER_NODE
                    NODE_TITLE_HEIGHT: 30,
                    MIN_NODE_WIDTH: 200,
                    MIN_NODE_HEIGHT: 125,
                    NODE_BACKGROUND_COLOR: '#fff',
                    NODE_BOX_CORNER_RADIUS: 0,
                    CONNECTOR_HEIGHT: 16,
                    CONNECTOR_WIDTH: 16,
                    DISTANCE_BETWEEN_CONNECTORS: 5,
                    NODE_BORDER_COLOR: '#6f845f',
                    NODE_SELECTED_BORDER_COLOR: '#99d651',
                    TITLE_BACKGROUND_COLOR: '#445f2e',
                    TITLE_TEXT_COLOR: '#fff',
                    CONNECTOR_TEXT_COLOR: '#445f2e',
                    CONNECTOR_TEXT_WIDTH: '400',
                    CONNECTOR_TEXT_SHADOW_COLOR: null,
                    CONNECTOR_OPEN_COLOR: 'white',
                    CONNECTOR_CLOSED_COLOR: '#f9a01c',
                    FRAMEWORK_COLOR: '#6f845f',
                    NODE_DISABLED_COLOR: '#eee',
                },
            ],
        },
    ];

    // Retorna el valor més gran entre la mida del text (+added) i el previous value
    function GetWiderText(ctx, font, text, added, previous_value) {
        var ret = previous_value;
        ctx.font = font;
        var text_width = ctx.measureText(text).width + added;
        if (text_width > ret) {
            ret = text_width;
        }
        return ret;
    };

    function SetOneNodeTheme(node) {

        var style = current_theme.node[node.temp.type_obj.style];
        var node_value = ((node.temp.type_obj.style != $scope.NodeStyle.GRAPH_NODE) && (node.temp.type_obj.style != $scope.NodeStyle.EXTERNAL_VIEWER_NODE))?node.value:0;

        var max_width = 
            GetWiderText($scope.ctx, fonts.NodeTitle, node.type, 120, // Added some space to the node title for the node id and the node logo
            GetWiderText($scope.ctx, fonts.NodeValue, node_value, style.CONNECTOR_WIDTH * 2, 0) // Added the connectors space to the node value width
        ); 

        if ((node.temp.type_obj.style == $scope.NodeStyle.INPUT_NODE) || (node.temp.type_obj.style == $scope.NodeStyle.OUTPUT_NODE)) {
            max_width+=50;
        }

        var max_input_text_len = 0;
        node.temp.type_obj.inputs.forEach(function(connector){
            max_input_text_len = GetWiderText($scope.ctx, fonts.ConnectorName, connector.name, 0, max_input_text_len);
        });

        var max_output_text_len = 0;
        node.temp.type_obj.outputs.forEach(function(connector){
            max_output_text_len = GetWiderText($scope.ctx, fonts.ConnectorName, connector.name, 0, max_output_text_len);
        });

        var left_and_right_texts_length = max_input_text_len + max_output_text_len + style.CONNECTOR_WIDTH * 2 + 20; // 20 is a little of space between texts

        if (node.temp.type_obj.style == $scope.NodeStyle.NULL_CONNECTION) {
            node.temp.width = style.MIN_NODE_WIDTH;
        } else {
          if (left_and_right_texts_length > max_width) {
              max_width = left_and_right_texts_length;
          }

          if (max_width < style.MIN_NODE_WIDTH) {
              max_width = style.MIN_NODE_WIDTH;
          }
          node.temp.width = max_width;
        }

        node.temp.inputs_areas = [];
        node.temp.outputs_areas = [];

        var initial_position_y = 0;

        if (node.temp.type_obj.style == $scope.NodeStyle.NULL_CONNECTION) {
          initial_position_y = 5;
        } else {
          initial_position_y = style.NODE_TITLE_HEIGHT + 25;
        }

        var distance_between_connectors = style.CONNECTOR_HEIGHT + style.DISTANCE_BETWEEN_CONNECTORS;
        var x = 0;
        var y = 0;


        for (var i = 0; i < node.inputs.length; i++) {
            if (node.temp.type_obj.style == $scope.NodeStyle.PIPELINE_NODE) {
                if (i == 0) { // The "Foreach" connectotr is the id number 0 but we want it at the bottom of all other connectors
                    y = initial_position_y + ((node.inputs.length - 1) * distance_between_connectors) + 10;
                } else {
                    y = initial_position_y + ((i-1) * distance_between_connectors);
                }
            } else {
                y = initial_position_y + (i * distance_between_connectors);
            }


            node.temp.inputs_areas.push({ left: x-(style.CONNECTOR_HEIGHT/2),
                                          top:  y-(style.CONNECTOR_HEIGHT/2),
                                          width: style.CONNECTOR_WIDTH,
                                          height: style.CONNECTOR_HEIGHT,
                                          x: x,
                                          y: y,
                                          id: node.inputs[i].id,
                                          required: (node.temp.type_obj.inputs[i].required == "1") });
        }



        switch(node.temp.type_obj.style) {
            case $scope.NodeStyle.CALCULATION_NODE:
            case $scope.NodeStyle.PIPELINE_NODE:
                follow_previous_items = false;
                num_connectors = node.temp.type_obj.inputs.length + node.temp.type_obj.outputs.length;
                break;
            case $scope.NodeStyle.INPUT_NODE:
            case $scope.NodeStyle.OUTPUT_NODE:
            case $scope.NodeStyle.DATA_NODE:
            case $scope.NodeStyle.NULL_CONNECTION:
            case $scope.NodeStyle.GRAPH_NODE:
            case $scope.NodeStyle.EXTERNAL_VIEWER_NODE:
            case $scope.NodeStyle.COMMENT_NODE:
                follow_previous_items = false;
                num_connectors = (node.temp.type_obj.inputs.length > node.temp.type_obj.outputs.length)?node.temp.type_obj.inputs.length:node.temp.type_obj.outputs.length;
                break;
        };

        if (node.temp.type_obj.style == $scope.NodeStyle.NULL_CONNECTION) {
          node.temp.height = style.MIN_NODE_HEIGHT;
        } else {

          if (follow_previous_items) {
            node.temp.height = style.NODE_TITLE_HEIGHT + style.CONNECTOR_HEIGHT * num_connectors + style.DISTANCE_BETWEEN_CONNECTORS * num_connectors + 30;
          }
          else {
            var max_side_connectors = (node.inputs.length > node.outputs.length)?node.inputs.length:node.outputs.length; 
            node.temp.height = style.NODE_TITLE_HEIGHT + style.CONNECTOR_HEIGHT * max_side_connectors + style.DISTANCE_BETWEEN_CONNECTORS * max_side_connectors + 30;
          }

          if (node.temp.height < style.MIN_NODE_HEIGHT) {
              node.temp.height = style.MIN_NODE_HEIGHT;
          }
        }

        //if (node.temp.type_obj.style == $scope.NodeStyle.PIPELINE_NODE) {
            // Case of input "Foreach"
            // We want this input at the bottom of the node.
            // node.temp.inputs_areas[node.temp.inputs_areas.length - 1].top = node.temp.inputs_areas[node.temp.inputs_areas.length - 1].y = node.temp.height - 15;
        //}

        for (var i = 0; i < node.outputs.length; i++) {
            var x = node.temp.width;
            var y = 0;
            if (follow_previous_items) {
                y = initial_position_y + (node.inputs.length * distance_between_connectors) + (i * distance_between_connectors);
            } else {
                y = initial_position_y + (i * distance_between_connectors);
            }

            var required = false;
            if ((node.temp.type_obj != null) && (node.temp.type_obj.outputs.length > 0)) {
                if (node.temp.type_obj.outputs[i] != undefined) {
                    required = (node.temp.type_obj.outputs[i].required == "1");
                }
            }

            node.temp.outputs_areas.push({
                                            left: x-(style.CONNECTOR_HEIGHT/2),
                                            top:  y-(style.CONNECTOR_HEIGHT/2),
                                            width: style.CONNECTOR_WIDTH,
                                            height: style.CONNECTOR_HEIGHT,
                                            x: x,
                                            y: y,
                                            id: node.outputs[i].id,
                                            required: required
            });
        }
    };

    function SetNodesTheme() {
        if (GetCurrentDocumentNodes() != null) {
          GetCurrentDocumentNodes().forEach(function(node) {
              SetOneNodeTheme(node);
          });
        }
    };


    ////////////////////////////////////////////////////////////////////////////
    // INPUT
    ////////////////////////////////////////////////////////////////////////////

    $scope.InputVisible = function() {
        return ($scope.input_visible==true);
    };

    function UserIsSettingNodeValue() {
        return (node_selected_for_write != null);
    };

    function SetNodeValueFromTextInput(accept_new_value) {
        if (node_selected_for_write != null) {
            var input = document.getElementById("input");
            if (accept_new_value) {
                node_selected_for_write.value = input.value;
                SetOneNodeTheme(node_selected_for_write);

                // The value of this type of node must be saved into the pipeline properties:
                if(node_selected_for_write.type == 'foreach_value') {
                    GetCurrentDocument().properties.loop_name = input.value;
                }
            }
            input.value = "";
            $scope.input_visible = false;
            $scope.DoApply();
            node_selected_for_write = null;
            DrawScene();
        }
    };

    function ShowInput(node) {
        var header_height = HEADER_HEIGHT;
        var input = document.getElementById("input");
        var x = 0, y = 0, w = 0, h = 0, font_size = 0;

        // let's translate the position depending on the canvas position:
        x -=  $scope.DocsNavTabs.selected_tab.page.CanvasPosition.x;
        y -=  $scope.DocsNavTabs.selected_tab.page.CanvasPosition.y;

        // the node position is allways in the same place but in different scale:
        x += node.position.left + 10; // +10 and +38 is because we do not want to place the input at the top-left node corner but over the node value.

        
        if ((node.type == "input") || (node.type == "output")) {
            // If node does not have a caption
            y += node.position.top + 10;
        } else {
            // If node has a caption
            y += node.position.top + 38;
        }

        // le't apply the scale:
        x *= (GetCurrentDocumentZoom() / 100);
        y *= (GetCurrentDocumentZoom() / 100);

        // the header height is allways the same and it does not depend on the scale. Let's add it:
        y += header_height;

        // The node width and height are always the same:
        w = node.temp.width - 20;
        h = node.temp.height - 60;

        // But in different scale:
        // le't apply the scale:
        w *= (GetCurrentDocumentZoom() / 100);
        h *= (GetCurrentDocumentZoom() / 100);

        input.style.left = x + "px";
        input.style.top = y + "px";
        input.style.width = w + "px";
        input.style.height = h + "px";

        // Font size depend on the scale:
        input.style.font = fonts.NodeValue;

        font_size = fonts.NodeValue.substr(0,fonts.NodeValue.indexOf("pt")); // Example: "13px robotoregular"
        //font_size = 12;
        font_size *= (GetCurrentDocumentZoom() / 100);

        input.style.fontSize = font_size + "pt";

        input.style.backgroundColor = current_theme.INPUT_BACKGROUND_COLOR;
        input.style.color = current_theme.INPUT_TEXT_COLOR;

        $scope.input_visible = true;
        input.value = node.value;
        $scope.DoApply();
        node_selected_for_write = node;
        input.focus();
    };

    ////////////////////////////////////////////////////////////////////////////
    // CANVAS EVENTS
    ////////////////////////////////////////////////////////////////////////////

    $scope.DoZoom = function() {
        // With these lines you do not need the zoom_previous variable
        // Reset all canvas transformations:
        $scope.canvas.width  = window.innerWidth;
        $scope.canvas.height = window.innerHeight - 80;

        // The origin is at (0,0)
        // Lets scale the canvas:
        $scope.ctx.scale(GetCurrentDocumentZoom() / 100, GetCurrentDocumentZoom() / 100);

        // Translate the canvas to the right position:
        $scope.ctx.translate(-$scope.DocsNavTabs.selected_tab.page.CanvasPosition.x,
                             -$scope.DocsNavTabs.selected_tab.page.CanvasPosition.y);

        DrawScene();
    };

    $scope.ZoomUp = function(step) { // arrives a positive value
        if (step == null) {
          step = 10;
        }

        if (GetCurrentDocumentZoom() < 200) {
          SetCurrentDocumentZoom(GetCurrentDocumentZoom() + step);
        }
        if (GetCurrentDocumentZoom() > 200) {
          GetCurrentDocumentZoom(200);
        }

        // DrawScene();
        $scope.DoApply(); // Update the value. Then, a watch(.zoom) calls the DrawScene
//        $scope.DoZoom();
    };

    $scope.ZoomDown = function(step) { // arrives a negative value
        if (step == null) {
          step = -10;
        }

        if (GetCurrentDocumentZoom() > 20) {
          SetCurrentDocumentZoom(GetCurrentDocumentZoom() + step);
        }
        if (GetCurrentDocumentZoom() < 20) {
          GetCurrentDocumentZoom(20);
        }

//        DrawScene();
        $scope.DoApply(); // Update the value. Then, a watch(.zoom) calls the DrawScene
//        $scope.DoZoom();
    };

    $scope.MoveCanvasLeft = function(step) {
        if (step == null) step = MOVE_STEP;
//        if (CanvasPosition.x < $scope.paper.width * num_papers.x) {
            $scope.DocsNavTabs.selected_tab.page.CanvasPosition.x += step;
            $scope.ctx.translate(-step, 0);
            DrawScene();
//        }
    };

    $scope.MoveCanvasRight = function(step) {
        if (step == null) step = MOVE_STEP;
//        if (CanvasPosition.x > 0) {
            $scope.DocsNavTabs.selected_tab.page.CanvasPosition.x -= step;
            $scope.ctx.translate(step, 0);
            DrawScene();
//        }
    };

    $scope.MoveCanvasDown = function(step) {
        if (step == null) step = MOVE_STEP;
//        if (CanvasPosition.y > 0) {
            $scope.DocsNavTabs.selected_tab.page.CanvasPosition.y -= step;
            $scope.ctx.translate(0, step);
            DrawScene();
//        }
    };

    $scope.ResetCanvasMovement = function() {
        $scope.ctx.translate($scope.DocsNavTabs.selected_tab.page.CanvasPosition.x,
                             $scope.DocsNavTabs.selected_tab.page.CanvasPosition.y);
        $scope.DocsNavTabs.selected_tab.page.CanvasPosition.x = 0;
        $scope.DocsNavTabs.selected_tab.page.CanvasPosition.y = 0;
        DrawScene();
    };


    $scope.MoveCanvasUp = function(step) {
        if (step == null) step = MOVE_STEP;
//        if (CanvasPosition.y < $scope.paper.height * num_papers.y) {
            $scope.DocsNavTabs.selected_tab.page.CanvasPosition.y += step;
            $scope.ctx.translate(0, -step);
            DrawScene();
//        }
    };

    var apply_again = true;
    function UpdateMousePosition(canvas, event) {
        $scope.mouse_x = event.pageX - canvas.offsetLeft;
        $scope.mouse_y = event.pageY - canvas.offsetTop - 36; // Adjust this number for better selecting connectors when the mouse is over them;

        //Apply the same current zoom transformation to the mouse coordinates:

        $scope.mouse_x /= (GetCurrentDocumentZoom() / 100);
        $scope.mouse_y /= (GetCurrentDocumentZoom() / 100);

        //Apply the canvas tranlation to the mouse coordinates:
        if($scope.DocsNavTabs.selected_tab != null) {
            $scope.mouse_x += $scope.DocsNavTabs.selected_tab.page.CanvasPosition.x;
            $scope.mouse_y += $scope.DocsNavTabs.selected_tab.page.CanvasPosition.y;
        }

        if ($scope.debug_mode == true) {
            $scope.DoApply();
            apply_again = true;
        } else {
            if (apply_again == true) {
                apply_again = false;
                $scope.DoApply();
            }
        }
    };

    function ShowPipeline(pipeline_id) {
      var pipeline_tab_id = FindTabByName(pipeline_id);

      UnselectPreviousDocumentObjects();

      if (pipeline_tab_id == -1) {
        LoadPipeline(pipeline_id);
      } else {
        SelectTab($scope.DocsNavTabs, pipeline_tab_id);
        DrawScene();
        $scope.DoApply();
      }

      $scope.DoZoom(); // This function does the zoom but it also ensures that the canvas position is in its place.
    };

    function SetCanvasEvents() {

        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Disable text selection on the canvas:
        // (for prevent automatic change of the pointer cursor by a text cursor)
        $scope.canvas.onselectstart = function () { return false; } // ie
        $scope.canvas.onmousedown = function () { return false; } // mozilla
        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        $scope.canvas.addEventListener('dblclick', function(){ 

            SetNodeValueFromTextInput(true);

            GetCurrentDocumentNodes().forEach(function(node) {
                redraw_need = false;

              /*
                if ((node.selected == true) &&
                    (node.temp.type_obj.style == $scope.NodeStyle.GRAPH_NODE)) {
                  $scope.OnNodeGraphSelected(node.id);
                  $scope.DoApply();
                }
              */              

                if ((node.selected == true) &&
                    (node.temp.type_obj.style == $scope.NodeStyle.PIPELINE_NODE)) {
                  ShowPipeline(node.temp.type_obj.id);


/*
                    CreateEmptyDocument();

                    CreateNode(6, 'output', 1000, 375, 'total', null);
                    CreateNode(5, 'output', 1000, 675, 'total', null);
                    CreateNode(3, 'bool', 425, 625, "TRUE", [{"id":0,"to":[{"node_id":1,"input_id":1}]}]);
                    CreateNode(4, 'bool', 425, 325, "FALSE", [{"id":0,"to":[{"node_id":0,"input_id":1}]}]);
                    CreateNode(0, 'gc-content', 725, 300, '', [{"id":0,"to":[{"node_id":6,"input_id":0}]}]);
                    CreateNode(1, 'gc-content', 725, 600, '', [{"id":0,"to":[{"node_id":5,"input_id":0}]}]);
                    CreateNode(2, 'input', 200, 475, 'vector', [{"id":0,"to":[{"node_id":0,"input_id":0},{"node_id":1,"input_id":0}]}]);
                    GetCurrentDocument().properties..name = "gc_content_pipeline";

                    $scope.DoApply();

                    SetNodesTheme();
                    DrawScene();
*/
                }

                if ((node.selected == true) &&
                    ((node.temp.type_obj.style == $scope.NodeStyle.DATA_NODE) ||
                     (node.temp.type_obj.style == $scope.NodeStyle.INPUT_NODE) ||
                     (node.temp.type_obj.style == $scope.NodeStyle.OUTPUT_NODE) ||
                     (node.temp.type_obj.style == $scope.NodeStyle.COMMENT_NODE) ||
                     (node.temp.type_obj.style == $scope.NodeStyle.GRAPH_NODE) ||
                     (node.temp.type_obj.style == $scope.NodeStyle.EXTERNAL_VIEWER_NODE)
                    )) {
                    switch(node.type) {
                        case 'TFA Viewer':
                            $scope.OpenTFAViewer(node.id);
                            break;
                        case 'bool':
                            if (node.value == "FALSE") { 
                                node.value = "TRUE"; 
                            }
                            else {
                                node.value = "FALSE";
                            }
                            redraw_need = true;
                            break;
                        case 'foreach_iteration':
                            break;
                        case 'foreach_value':
                            //break;
                        default:
                            ShowInput(node);
                            break;
                    }
                }

                if (redraw_need) {
                    DrawScene();
                }
            });
        });

        $scope.OpenTFAViewer = function(id) {
            // find those nodes that their outputs are inputs of the current node
            var tfa = "";
            var stats = "";
            var gff = "";
            var weight = "";

            file_node = FindNodeLinkedToThisConnector(id, 0); // 0 is the TFA connector
            if (file_node != null) { tfa = file_node.node.value.replace(/\//g, "slash"); }

            file_node = FindNodeLinkedToThisConnector(id, 3); // 3 is the stats connector
            if (file_node != null) { stats = file_node.node.value.replace(/\//g, "slash"); }

            file_node = FindNodeLinkedToThisConnector(id, 1); // 1 is the gff connector
            if (file_node != null) { gff = file_node.node.value.replace(/\//g, "slash"); }

            file_node = FindNodeLinkedToThisConnector(id, 2); // 2 is the weight connector
            if (file_node != null) { weight = file_node.node.value.replace(/\//g, "slash"); }

            $window.open("http://localhost:3001/#/load/" + tfa + "/" + stats + "/" + gff + "/" + weight, "_blank");
        };

        $scope.canvas.addEventListener('mousedown', function(event) {
            /*
            if (event.which === 3) { // right click
              // This is important:
              // context menu items does not refresh their ng-if (ng-disabled, ...)
              // contition unless the scope is applied here on mouse down:
              // ===================
              $scope.DoApply();
              // ===================

              return;
            }
            */

            if (event.which === 1) { // left click
              if (key_pressed == 'Shift') {
              }

              SetNodeValueFromTextInput(true);

              UpdateMousePosition(this, event);

              // The search of the selected node must be down from the user's nearest layer.
              // That means that the search must be done from the last node to the first one:
              //for (var node_index = nodes.length-1; node_index >= 0; node_index--) {
                  //var node = nodes[node_index];
              GetCurrentDocumentNodes().forEach(function(node) {

                  // Start joining connectors:
                  if ((node.temp.focused_input != null) ||
                      (node.temp.focused_output != null)) {
                      if ($scope.joining_connectors == null) {

                          // Document is being modified for joining connectos:
                          $scope.DocsNavTabs.selected_tab.saved = false;
                          $scope.DoApply();

                          var direction = (node.temp.focused_input != null)?'input':'output';
                          var focused_connector = (node.temp.focused_input != null)?node.temp.focused_input:node.temp.focused_output;

                          var done = false;

                          if (direction == 'input') {
                              // Start creating a connection from the input of a node to another node

                              var found = false;
                              for (var n = 0; ((n < GetCurrentDocumentNodes().length) && (!found)); n++) {
                                  for (var o = 0; ((o < GetCurrentDocumentNodes()[n].outputs.length) && (!found)); o++) {
                                      for(var i = 0; ((i < GetCurrentDocumentNodes()[n].outputs[o].to.length) && (!found)); i++) {
                                          if ((GetCurrentDocumentNodes()[n].outputs[o].to[i].node_id == node.id) &&
                                              (GetCurrentDocumentNodes()[n].outputs[o].to[i].input_id == focused_connector.id)) {
                                              found = true;

                                              $scope.joining_connectors = {
                                                  from: { node: GetCurrentDocumentNodes()[n], 
                                                          connector: GetCurrentDocumentNodes()[n].outputs[o], 
                                                          direction: 'output',
                                                        },
                                                  to: null,
                                              };

                                              GetCurrentDocumentNodes()[n].outputs[o].to.splice(i, 1);


                                              
                                              // Remove value from intput/output when it is disconnected
                                              // from its node:
                                              /*
                                              if ((GetCurrentDocumentNodes()[n].type == "input") ||
                                                  (GetCurrentDocumentNodes()[n].type == "output")) {
                                                  GetCurrentDocumentNodes()[n].value = null;
                                              }

                                              if ((node.type == "input") ||
                                                  (node.type == "output")) {
                                                  node.value = null;
                                              }
                                              */
                                              
                                             
                                              done = true;
                                          }
                                      }
                                  }
                              }
                          }

                          if (done == false) {
                            if (direction == 'output') {
                              // Start creating a connection from the output of a node to another node

                              // Document is being modified for joining connectos:
                              $scope.DocsNavTabs.selected_tab.saved = false;
                              $scope.DoApply();

                              /*
                              // Pipelines and Calculations Outputs can only have one connection per output
                              if ((node.temp.type_obj.style == $scope.NodeStyle.PIPELINE_NODE) ||
                                  (node.temp.type_obj.style == $scope.NodeStyle.CALCULATION_NODE)) {
                                // Remove previous connection of this calculation/pipeline output 
                                node.outputs[focused_connector.id].to = [];
                              }
                              */
                            }

                            $scope.joining_connectors = {
                                from: { node: node, 
                                        connector: focused_connector, 
                                        direction: direction,
                                      },
                                to: null,
                            };
                          }
                      }
                  } else {
                      // Node selected.
                      $scope.OnNodeGraphSelected(node.id);

                      // Node selected.
                      // Start dragging the node. (unless the mouse is up)
                      if (IsHit($scope.mouse_x, $scope.mouse_y, node) == true) {

                          // A node is clicked but here we do not know if it is for moving it or for opening a pipeline.
                          // We will know it on the mouse move / mouse up event

                          prev_mouse_x = $scope.mouse_x;
                          prev_mouse_y = $scope.mouse_y;
                          dragging_id = node.id;

                          MoveTheNodeToFirstLayer(node.id);
                      }
                  }
              });
              //}


              if (($scope.joining_connectors == null) && // Not joining connectors
                  (dragging_id == null))                 // Not dragging nodes
              {
                moving_canvas = true;
                $scope.SetMousePointer();
              }
            } // left click
        }, false);

        /*
        Returns (ret.result == true) if:
            "ret.a" is the object of "type1" and
            "ret.b" is the object of "type2"
        */
        function JoinObjectsAndTypes(comp_a, comp_b, type1, type2, a, b) {
            var ret = {
                result: false,
                a: null,
                b: null
            };
            if ((comp_a == type1) && (comp_b == type2)) {
                ret = {
                    result: true,
                    a: a,
                    b: b
                };
            } else {
                if ((comp_a == type2) && (comp_b == type1)) {
                    ret = {
                        result: true,
                        a: b,
                        b: a
                    };
                }
            }
            return ret;
        }

        function FindNodeLinkedToThisConnector(node_id, connector_id) {
            var found_node = null;
            for (var n = 0; ((n < GetCurrentDocumentNodes().length) && (found_node == null)); n++) {
                for (var o = 0; ((o < GetCurrentDocumentNodes()[n].outputs.length) && (found_node == null)); o++) {
                    for(var i = 0; ((i < GetCurrentDocumentNodes()[n].outputs[o].to.length) && (found_node == null)); i++) {
                        if ((GetCurrentDocumentNodes()[n].outputs[o].to[i].node_id == node_id) &&
                            (GetCurrentDocumentNodes()[n].outputs[o].to[i].input_id == connector_id)) {
                            found_node = {
                                node: GetCurrentDocumentNodes()[n],
                                output_id: o,
                                output_number: i
                            };
                        }
                    }
                }
            }
            return found_node;
        };

        function RemoveAllLinksToThisNodeInputConnector(node_id, connector_id) {
            var found_node = FindNodeLinkedToThisConnector(node_id, connector_id);
            if (found_node != null) {
                found_node.node.outputs[found_node.output_id].to.splice(found_node.output_number, 1);
            }
        };

        function IsThisNodeInputConnectorEmpty(node_id, connector_id) {
            var empty = true;
            for (var n = 0; ((n < GetCurrentDocumentNodes().length) && (empty)); n++) {
                var node = GetCurrentDocumentNodes()[n];
                for (var o = 0; ((o < node.outputs.length) && (empty)); o++) {
                    var output = node.outputs[o];
                    for (var t = 0; ((t < output.to.length) && (empty)); t++) {
                        var to_connector = output.to[t];
                        if ((to_connector.node_id == node_id) &&
                            (to_connector.input_id == connector_id)) {
                            empty = false;
                        }
                    }
                }
            }
            return empty;
        };

        function IsThisNodeOutputConnectorEmpty(node_id, connector_id) {
            var node = arrays.FindArrayElementById(GetCurrentDocumentNodes(), node_id);
            var empty = (node.outputs[connector_id].to.length == 0);
            return empty;
        };

        $scope.InputConnectorSelected = function() {
          return (($scope.ConnectorSelected() == true) && ($scope.connector_selected.direction == "input"));
        };

        $scope.OutputConnectorSelected = function() {
          return (($scope.ConnectorSelected() == true) && ($scope.connector_selected.direction == "output"));
        };

        $scope.ConnectorSelected = function() {
          return (($scope.connector_selected.node != null) && ($scope.connector_selected.connector != null));
        };

        $scope.OnAddVariable = function(value) {
          if ($scope.InputConnectorSelected()) {
            if (IsThisNodeInputConnectorEmpty($scope.connector_selected.node.id,
                                              $scope.connector_selected.connector.id) == true) {
                $scope.CreateNodeToConnector($scope.connector_selected.node,
                                             $scope.connector_selected,
                                             $scope.NodeStyle.DATA_NODE,
                                             value);
            }
          }

          if ($scope.OutputConnectorSelected()) {
            if (IsThisNodeOutputConnectorEmpty($scope.connector_selected.node.id,
                                               $scope.connector_selected.connector.id) == true) {
                $scope.CreateNodeToConnector($scope.connector_selected.node,
                                             $scope.connector_selected,
                                             $scope.NodeStyle.DATA_NODE,
                                             value);
            }
          }
        };

        $scope.OnAddInput = function() {
          if ($scope.GetEditorType() == $scope.FileType.PIPELINE) {
              if ($scope.InputConnectorSelected()) {
  /*
              if (($scope.connector_selected.node != null) &&
                  ($scope.connector_selected.connector != null) &&
                  ($scope.connector_selected.direction == "input")) {
  */
                  if (IsThisNodeInputConnectorEmpty($scope.connector_selected.node.id,
                                                    $scope.connector_selected.connector.id) == true) {
                      $scope.CreateNodeToConnector($scope.connector_selected.node,
                                                   $scope.connector_selected,
                                                   $scope.NodeStyle.INPUT_NODE,
                                                   null);
                  }
              }
          }
        };

        $scope.OnAddOutput = function() {
          if ($scope.GetEditorType() == $scope.FileType.PIPELINE) {
              if ($scope.OutputConnectorSelected()) {
/*
              if (($scope.connector_selected.node != null) &&
                  ($scope.connector_selected.connector != null) &&
                  ($scope.connector_selected.direction == "output")) {
*/
                  if (IsThisNodeOutputConnectorEmpty($scope.connector_selected.node.id,
                                                    $scope.connector_selected.connector.id) == true) {
                      $scope.CreateNodeToConnector($scope.connector_selected.node,
                                                   $scope.connector_selected,
                                                   $scope.NodeStyle.OUTPUT_NODE,
                                                   null);
                  }
              }
          }
        };

        

        $scope.SelectedNodes = function() {
          return ($scope.node_selected != null);
        };

        $scope.OnSetDryRun = function() {
          if ($scope.SelectedNodes()) {
            $scope.node_selected.enabled = !$scope.node_selected.enabled;
            DrawScene();

            // Document is being modified for enabling / disabling nodes:
            $scope.DocsNavTabs.selected_tab.saved = false;
            $scope.DoApply();
/*
            for (var i = 0; i < GetCurrentDocumentNodes().length; i++) {
                if ((GetCurrentDocumentNodes()[i].selected == true) &&
                    ((GetCurrentDocumentNodes()[i].temp.type_obj.style == $scope.NodeStyle.CALCULATION_NODE) ||
                     (GetCurrentDocumentNodes()[i].temp.type_obj.style == $scope.NodeStyle.PIPELINE_NODE))
                    ) {
                  GetCurrentDocumentNodes()[i].enabled = !GetCurrentDocumentNodes()[i].enabled;
                }
            }
            DrawScene();
*/
          }
        };

        $scope.OnRemoveNode = function() {
          if ($scope.SelectedNodes()) {
            var remove_nodes_list = [];

            for (var i = 0; i < GetCurrentDocumentNodes().length; i++) {
                if (GetCurrentDocumentNodes()[i].selected == true) {
                    remove_nodes_list.push(GetCurrentDocumentNodes()[i]);
                }
            }


            if (remove_nodes_list.length > 0) {
              var message = "";
              if (remove_nodes_list.length == 1) {
                message = "Are you sure that you want to remove the node \"" + remove_nodes_list[0].type + "\"?";
              } else {
                message = "Are you sure that you want to remove " + remove_nodes_list.length + " nodes?";
              }
              MessagesFactory.confirm(message, 
              function() {  // Yes

                if ((remove_nodes_list[0].type != 'foreach_value') && (remove_nodes_list[0].type != 'foreach_iteration')) {

                    if (remove_nodes_list[0].temp.type_obj.style == $scope.NodeStyle.GRAPH_NODE) {
                      RemoveOutputTab(remove_nodes_list[0]);
                    }

                    for (var i = 0; i < remove_nodes_list.length; i++) {
                      // Remove the node
                      RemoveNode(remove_nodes_list[i].id);
                    }
                } else {
                    MessagesFactory.alert("Foreach nodes cannot be removed. Do not use them if you do not need them.");
                }

                DrawScene();
              },
              function() {  // No
              });
            }
          }
        };

        $scope.OnShowHideGrid = function() {
          $scope.ShowGrid = !$scope.ShowGrid;
          DrawScene();
        };

        $scope.OnShowHideDebugInformation = function() {
          $scope.debug_mode = !$scope.debug_mode;
          DrawScene();
        };

        $scope.canvas.addEventListener('contextmenu', function(e) {
          if (e.button === 2) {
            e.preventDefault();
            return false;
          }
        }, false);

        $scope.canvas.addEventListener('mouseup', function(event) {

            if (node_dragged) {
              // Document is being modified for moving nodes:
              $scope.DocsNavTabs.selected_tab.saved = false;
              $scope.DoApply();
            }

            dragging_id = null;
            node_dragged = false;
            prev_mouse_x = null;
            prev_mouse_y = null;

            if (moving_canvas) {  // Stop moving the canvas
              moving_canvas = false;
            }

            if ($scope.joining_connectors != null) {
                if (($scope.joining_connectors.from != null) &&
                    ($scope.joining_connectors.to != null)) {
                    if ($scope.joining_connectors.from.direction != $scope.joining_connectors.to.direction) {

                        // 
                        var res = JoinObjectsAndTypes($scope.joining_connectors.from.direction,
                                                      $scope.joining_connectors.to.direction,
                                                      'input',
                                                      'output',
                                                      $scope.joining_connectors.from,
                                                      $scope.joining_connectors.to);
                        if (res.result == true) {

                            var accumulative_input = arrays.FindArrayElementById(res.a.node.temp.type_obj.inputs, res.a.connector.id).accumulative;

                            if (accumulative_input == true) {
                              // Some nodes (such as Graph nodes) can have more than one node connected to the same input (input accumulative == true)
                              // [node 1]----->[graph]
                              // [node 2]-----^
                            }
                            else {
                              // All the other nodes with non accumulative inputs can have only one node connected to every of their inputs.
                              // So, remove all input connections before adding the current connector
// I remove this line because I saw that I need a "text file variable" to be 
// RemoveAllLinksToThisNodeInputConnector(res.a.node.id, res.a.connector.id);
                            }

                            // When input nodes only had one connection:
                            /*
                            if (res.b.node.temp.type_obj.style == $scope.NodeStyle.INPUT_NODE) {
                              // Input nodes can only have one connection to other node:
                              res.b.connector.to = [{node_id: res.a.node.id, input_id: res.a.connector.id}];
                            } else {
                                res.b.connector.to.push({node_id: res.a.node.id, input_id: res.a.connector.id});
                            }
                            */

                            res.b.connector.to.push({node_id: res.a.node.id, input_id: res.a.connector.id});
                        }


                        // Join INPUT_NODE with a node (its input connector):
                        var res = JoinObjectsAndTypes($scope.joining_connectors.from.node.temp.type_obj.style,
                                                      $scope.joining_connectors.to.node.temp.type_obj.style,
                                                      $scope.NodeStyle.INPUT_NODE,
                                                      $scope.NodeStyle.CALCULATION_NODE,
                                                      $scope.joining_connectors.from,
                                                      $scope.joining_connectors.to);
                        if (res.result == true) {
                             
                            if (res.a.node.value == "") { // Assign input value name only if it is blank
                                res.a.node.value = arrays.FindArrayElementById(res.b.node.temp.type_obj.inputs,
                                                                           res.b.connector.id).name;
                            }
                        }


                        // Join OUTPUT_NODE with a node (its output connector):
                        var res = JoinObjectsAndTypes($scope.joining_connectors.from.node.temp.type_obj.style,
                                                      $scope.joining_connectors.to.node.temp.type_obj.style,
                                                      $scope.NodeStyle.OUTPUT_NODE,
                                                      $scope.NodeStyle.CALCULATION_NODE,
                                                      $scope.joining_connectors.from,
                                                      $scope.joining_connectors.to);

                        if (res.result == true) {
                            if (res.a.node.value == "") { // Assign output value name only if it is blank
                                res.a.node.value = arrays.FindArrayElementById(res.b.node.temp.type_obj.outputs,
                                                                               res.b.connector.id).name;
                            }
                        }
                    }
                }
            }

            $scope.joining_connectors = null;
            DrawScene();
           
            $scope.SetMousePointer();

        }, false);

        //http://phrogz.net/tmp/CANVAS_zoom_to_cursor.html



        var handleScroll = function(evt){
            if (UserIsSettingNodeValue()==true) {
                return;
            }

	        var delta = evt.wheelDelta ? evt.wheelDelta/150 : evt.detail ? -evt.detail : 0;

	        if (delta > 0) {
                $scope.ZoomUp(delta);
            } else {
                $scope.ZoomDown(delta);
            }
	        //return evt.preventDefault() && false;
        };

        $scope.canvas.addEventListener('DOMMouseScroll', handleScroll, false);
        $scope.canvas.addEventListener('mousewheel', handleScroll, false);
        $scope.canvas.addEventListener('mouseover', function(){
            mouse_over_editor_canvas = true;
        }, false);
        $scope.canvas.addEventListener('mouseout', function(){
            mouse_over_editor_canvas = false;
        }, false);


        window.addEventListener('keyup', function(event) {
          key_pressed = "";
        });


        //http://www.cambiaresearch.com/articles/15/javascript-char-codes-key-codes
        window.addEventListener('keydown', function(event) {
            key_pressed = event.key;

            if (UserIsSettingNodeValue()==true) {
                if(event.keyCode == 27) { // Key 'ESC'
                    SetNodeValueFromTextInput(false); // discard new value
                }
                if(event.keyCode == 13) { // Key 'Enter'
                    SetNodeValueFromTextInput(true); // accept new value
                }
    
                return; // <---- Any other key press is discarded when user is setting a node value
            }

            if (($state.current.name != "experiment_editor") && ($state.current.name != "pipeline_editor")) {
              return;
            }
            if (mouse_over_editor_canvas == false) {
              return;
            }
            if (!EnableCanvasInputKey) {
              return;
            }

            if(event.keyCode == 73) { // Key 'i'
              $scope.OnAddInput();
            }

            if(event.keyCode == 79) { // Key 'o'
              $scope.OnAddOutput();
            }

            if(event.keyCode == 86) { // Key 'v'
              $scope.OnAddVariable();
            }

            if(event.keyCode == 78) { // Key 'n'
              /*
                if ($scope.InputConnectorSelected()) {
                    if (IsThisNodeInputConnectorEmpty($scope.connector_selected.node.id,
                                                      $scope.connector_selected.connector.id) == true) {
                        $scope.CreateNodeToConnector($scope.connector_selected.node,
                                                     $scope.connector_selected,
                                                     $scope.NodeStyle.NULL_CONNECTION);
                    }
                }
                if ($scope.InputConnectorSelected()) {
                    if (IsThisNodeOutputConnectorEmpty($scope.connector_selected.node.id,
                                                      $scope.connector_selected.connector.id) == true) {
                        $scope.CreateNodeToConnector($scope.connector_selected.node,
                                                     $scope.connector_selected,
                                                     $scope.NodeStyle.NULL_CONNECTION);
                    }
                }
              */
            }

            if(event.keyCode == 67) { // Key 'c'
              /*
                $scope.OnOpenChart();
              */
            }

            if(event.keyCode == 68) { // Key 'd'
                $scope.OnShowHideDebugInformation();
            }

            //if(event.keyCode == 70) { // Key 'f'
            //}

            if(event.keyCode == 80) { // Key 'p'
            }

            if(event.keyCode == 71) { // Key 'g'
              $scope.OnShowHideGrid();
            }

            if(event.keyCode == 72) { // Key 'h'
            }
            if(event.keyCode == 37) { // 'Left Arrow
                event.preventDefault();
                if (event.ctrlKey == true) {
                  $scope.MoveAllNodesLeft();
                } else {
                  $scope.RemoveBlurFromZoomSlider();
                  $scope.MoveCanvasRight();
                }
            }
            if(event.keyCode == 38) { // 'Up Arrow
                event.preventDefault();
                if (event.ctrlKey == true) {
                  $scope.MoveAllNodesUp();
                } else {
                  $scope.RemoveBlurFromZoomSlider();
                  $scope.MoveCanvasDown();
                }
            }
            if(event.keyCode == 39) { // 'Right Arrow
                event.preventDefault();
                if (event.ctrlKey == true) {
                  $scope.MoveAllNodesRight();
                } else {
                  $scope.RemoveBlurFromZoomSlider();
                  $scope.MoveCanvasLeft();
                }
            }
            if(event.keyCode == 40) { // 'Down Arrow
                event.preventDefault();
                if (event.ctrlKey == true) {
                  $scope.MoveAllNodesDown();
                } else {
                  $scope.RemoveBlurFromZoomSlider();
                  $scope.MoveCanvasUp();
                }
            }
            if(event.keyCode == 107) { // 'Add Key
                $scope.ZoomUp();
            }
            if(event.keyCode == 109) { // 'Substract Key
                $scope.ZoomDown();
            }

            if(event.keyCode == 8) {  // 'Dry Run Key
              $scope.OnSetDryRun();
            }

            if(event.keyCode == 46) { // 'Supr Remove Key
              $scope.OnRemoveNode();
            }

        }, false);

        function GridNearestValue(value) {
            var ret = value;
/*
            ret /= current_theme.CANVAS_SMALL_LINES_DISTANCE;
            ret = Math.round(ret);
            ret *= current_theme.CANVAS_SMALL_LINES_DISTANCE;
            ret = Math.round(ret);
*/
            return ret;
        }

        $scope.canvas.addEventListener('mousemove', function(event) {
            UpdateMousePosition(this, event);

            // ================================================
            // Move the canvas on dragging the mouse
            // ================================================
            if (moving_canvas == true) {
              $scope.RemoveBlurFromZoomSlider();

              if (event.movementY < 0)  {
                $scope.MoveCanvasUp(event.movementY*(-1));
              } else {
                $scope.MoveCanvasDown(event.movementY);
              }

              if (event.movementX < 0)  {
                $scope.MoveCanvasLeft(event.movementX*(-1));
              } else {
                $scope.MoveCanvasRight(event.movementX);
              }
            }
            // ================================================

            var selection_changed = false;
            var mouse_over_node = false;
            var connector_selection_changed = false;

            if ($scope.joining_connectors != null) {
                $scope.joining_connectors.to = null;
            }

            if (dragging_id == null) {
                $scope.node_selected = null;
            }

            $scope.connector_selected = {node: null, connector: null, direction: null};

            GetCurrentDocumentNodes().forEach(function(node) {

                if (dragging_id == null) {
                    mouse_over_node = IsHit($scope.mouse_x, $scope.mouse_y, node);
                    selection_changed |= (mouse_over_node != node.selected);
                    node.selected = mouse_over_node;

                    if (mouse_over_node) {
                        $scope.node_selected = node;
                    }

                    // Connectors of this node can only be selected / unselected if this node is not the "to" of $scope.joining_connectors:
                    if (($scope.joining_connectors == null) ||
                       (($scope.joining_connectors != null) && ($scope.joining_connectors.from.node != node))) {
                        // Determine if any input / output connector is selected:
                        // node.temp.focused_input = null;
                        // node.temp.focused_output = null;

                        var iterations = [ 
                                {ite: 'input', areas: node.temp.inputs_areas, focused: node.temp.focused_input},
                                {ite: 'output', areas: node.temp.outputs_areas, focused: node.temp.focused_output}
                        ];

                        var MAGNETIC_CONNECTION = 20; //20;

                        iterations.forEach(function(iter) {
                            var one_connector_selected = false;

                            iter.areas.forEach(function(connector) {


                                if (($scope.mouse_x >= node.position.left + connector.left - MAGNETIC_CONNECTION) &&
                                    ($scope.mouse_x <= node.position.left + connector.left + connector.width + MAGNETIC_CONNECTION) &&
                                    ($scope.mouse_y >= node.position.top + connector.top) &&
                                    ($scope.mouse_y <= node.position.top + connector.top + connector.height)) {

                                    one_connector_selected = true;

                                    if ((iter.focused == null) || ((iter.focused != null) && (iter.focused.id != connector.id))) {
                                        connector_selection_changed = true;
                                    }
                                    
                                    if (iter.ite == 'input') {
                                        node.temp.focused_input = arrays.FindArrayElementById(node.inputs, connector.id);
                                    }
                                    if (iter.ite == 'output') {
                                        node.temp.focused_output = arrays.FindArrayElementById(node.outputs, connector.id);
                                    }

                                    var inout_conn = null;
                                    if (iter.ite == 'input') {
                                        inout_conn = arrays.FindArrayElementById(node.temp.type_obj.inputs, connector.id);
                                    }
                                    if (iter.ite == 'output') {
                                        inout_conn = arrays.FindArrayElementById(node.temp.type_obj.outputs, connector.id);
                                    }
                                    $scope.connector_selected = {node: node, connector: inout_conn, direction: iter.ite};

                                }
                            });

                            if (one_connector_selected == false) {
                                if (iter.focused != null) {
                                    connector_selection_changed = true;
                                }
                                if (iter.ite == 'input') node.temp.focused_input = null;
                                if (iter.ite == 'output') node.temp.focused_output = null;
                            }

                            if ($scope.joining_connectors != null) {
                                if (iter.focused != null) {
                                    if (node != $scope.joining_connectors.from.node) {  // "node from" and "node to" cannot be the same.
                                        $scope.joining_connectors.to = { 
                                            node: node,
                                            connector: iter.focused,
                                            direction: iter.ite,
                                        };
                                        console.log("endind joining connector: direction: " + $scope.joining_connectors.to.direction +". Node: " + $scope.joining_connectors.to.node.id + ". Connector: " + $scope.joining_connectors.to.connector.id);
                                    }
                                } else {
                                   // $scope.joining_connectors.to = null;
                                   // console.log("endind joining connector: Node: null. Connector: null");
                                }
                            }
                        });
                    }

                } else {
                    if (node.id == dragging_id) {
                        if ((prev_mouse_x != null) && (prev_mouse_y != null)) {

                            node_dragged = true;

                            if ($scope.ShowGrid == true) {
                                // GRID MAGNETIC
                                $scope.mouse_x = GridNearestValue($scope.mouse_x);
                                $scope.mouse_y = GridNearestValue($scope.mouse_y);
                            }

                            node.position.left += ($scope.mouse_x-prev_mouse_x);
                            node.position.top += ($scope.mouse_y-prev_mouse_y);

                            if ($scope.ShowGrid == true) {
                                // GRID MAGNETIC
                                node.position.left = GridNearestValue(node.position.left);
                                node.position.top = GridNearestValue(node.position.top);
                            }

                        }

                        prev_mouse_x = $scope.mouse_x;
                        prev_mouse_y = $scope.mouse_y;
                    }
                }
            });

            if ((selection_changed == true) || 
                (dragging_id != null) || 
                (connector_selection_changed == true) ||
                ($scope.joining_connectors != null)) {
                DrawScene();
            }

            $scope.SetMousePointer();

            // The new ongoing connection:
            if ($scope.joining_connectors != null) {
                var areaFrom = null;
                if ($scope.joining_connectors.from.direction == 'input') {
                    areaFrom = arrays.FindArrayElementById($scope.joining_connectors.from.node.temp.inputs_areas, $scope.joining_connectors.from.connector.id);
                } else {
                    areaFrom = arrays.FindArrayElementById($scope.joining_connectors.from.node.temp.outputs_areas, $scope.joining_connectors.from.connector.id);
                }

                // MAGNETIC CONNECTION
                if ($scope.joining_connectors.to == null) {
                    DrawLine($scope.ctx,'orange', 1, 'black',
                             $scope.mouse_x, $scope.mouse_y, 
                             $scope.joining_connectors.from.node.position.left + areaFrom.x, $scope.joining_connectors.from.node.position.top + areaFrom.y);
                } else {
                    var areaTo = null;
                    if ($scope.joining_connectors.to.direction == 'input') {
                        areaTo = arrays.FindArrayElementById($scope.joining_connectors.to.node.temp.inputs_areas, $scope.joining_connectors.to.connector.id);
                    } else {
                        areaTo = arrays.FindArrayElementById($scope.joining_connectors.to.node.temp.outputs_areas, $scope.joining_connectors.to.connector.id);
                    }

                    DrawLine($scope.ctx,'orange', 1, 'black',
                             $scope.joining_connectors.to.node.position.left + areaTo.x, $scope.joining_connectors.to.node.position.top + areaTo.y,
                             $scope.joining_connectors.from.node.position.left + areaFrom.x, $scope.joining_connectors.from.node.position.top + areaFrom.y);
                }
            }

        }, false);
    };          

    $scope.SetMousePointer = function() {
        if (moving_canvas == true) {
            // Moving the canvas
            $scope.canvas.style.cursor = 'move';
        } else {
            // Default pointer (arrow) if the mouse is over a connector:
            if ($scope.connector_selected.connector!= null) {
                $scope.canvas.style.cursor = 'crosshair'; // crosshair
            } else {
                // Default pointer (arrow) if the mouse is not over any node:
                if ($scope.node_selected == null) {
                    $scope.canvas.style.cursor = 'default';
                } else {
                    if (dragging_id == null) {
                        // Pointer cursor if the mouse if over a node but it is not dragging it:
                        // $scope.canvas.style.cursor = 'pointer';
                        $scope.canvas.style.cursor = 'default';
                    } else {
                        // Pointer cursor if the mouse if over a node and it is dragging it:
                        $scope.canvas.style.cursor = 'move';
                    }
                }
            }
        }
    };

	// ========================================================================
	// 
	// ========================================================================

    // default_value could be null or undefined
    $scope.CreateNodeToConnector = function(node, connector, new_node_type, default_value) {
        var header_height = HEADER_HEIGHT;
        var separation = 0;
        var connector_type = "";
        var inputs = null;
        var outputs = null;
        var new_node = null;
        var side = "";
        var remove_other_links = null;


        switch(new_node_type) {
            case $scope.NodeStyle.INPUT_NODE:
                side = "left";
                separation = -250;
                connector_type = "input";
                inputs = null;
                outputs = [{"id":0,"to":[{
                            "node_id": node.id * 1,
                            "input_id": connector.connector.id * 1
                           }]}];
                remove_other_links = node.temp.type_obj.inputs;
                break;
            case $scope.NodeStyle.OUTPUT_NODE:
                side = "right";
                separation = 50;
                connector_type = "output";
                inputs = null;
                outputs = null;
                remove_other_links = node.temp.type_obj.outputs;
                break;
            case $scope.NodeStyle.DATA_NODE:
                connector_type = connector.connector.type;

                if (connector.direction == "input") {
                    side = "left";
                    separation = -200;
                    inputs = null;
                    outputs = [{"id":0,"to":[{
                                "node_id": node.id * 1,
                                "input_id": connector.connector.id * 1
                               }]}];
                }

                if (connector.direction == "output") {
                    side = "right";
                    separation = 200;
                    inputs = null;
                    outputs = null;
                }
                break;
            case $scope.NodeStyle.NULL_CONNECTION:
                connector_type = "null_connection";

                header_height = 0;

                if (connector.direction == "input") {
                    side = "left";
                    separation = -50;
                    inputs = null;
                    outputs = [{"id":0,"to":[{
                                "node_id": node.id * 1,
                                "input_id": connector.connector.id * 1
                               }]}];
                }

                if (connector.direction == "output") {
                    side = "right";
                    separation = 50;
                    inputs = null;
                    outputs = null;
                }
                break;
            default: // $scope.NodeStyle.GRAPH_NODE
                side = "right";
                separation = 50;
                connector_type = new_node_type;
                inputs = null;
                outputs = null;
                remove_other_links = null;
                break;
        }




        new_node = CreateNode(null,
                              true,
                              connector_type,
                              $scope.mouse_x + separation,
                              $scope.mouse_y - header_height, 
                              inputs,
                              outputs);

        if ((default_value != undefined) && (default_value != null)) {
            new_node.value = default_value;
        }

        if (remove_other_links != null) {
            new_node.value = arrays.FindArrayElementById(remove_other_links,
                                                         connector.connector.id).name;
        }

        if (side == "left") {
        }
        if (side == "right") {
            node.outputs[connector.connector.id].to.push({
                                                "node_id": new_node.id * 1,
                                                "input_id": 0
                                               });
        }

        SetNodesTheme();
        DrawScene();
    }


    $scope.MoveAllNodesLeft = function() {
      for (var n = 0; n < GetCurrentDocumentNodes().length; n++) {
        var node = GetCurrentDocumentNodes()[n];
        node.position.left -= current_theme.CANVAS_SMALL_LINES_DISTANCE;
      }
      DrawScene();
    }

    $scope.MoveAllNodesRight = function() {
      for (var n = 0; n < GetCurrentDocumentNodes().length; n++) {
        var node = GetCurrentDocumentNodes()[n];
        node.position.left += current_theme.CANVAS_SMALL_LINES_DISTANCE;
      }
      DrawScene();
    }

    $scope.MoveAllNodesUp = function() {
      for (var n = 0; n < GetCurrentDocumentNodes().length; n++) {
        var node = GetCurrentDocumentNodes()[n];
        node.position.top -= current_theme.CANVAS_SMALL_LINES_DISTANCE;
      }
      DrawScene();
    }

    $scope.MoveAllNodesDown = function() {
      for (var n = 0; n < GetCurrentDocumentNodes().length; n++) {
        var node = GetCurrentDocumentNodes()[n];
        node.position.top += current_theme.CANVAS_SMALL_LINES_DISTANCE;
      }
      DrawScene();
    }

    $scope.RemoveBlurFromZoomSlider = function() {
        // Unfocus the slider in order to not zoom the canvas when user preses
        // left and right arrows to move the canvas:
        var zoom_slider = document.getElementById("zoom_slider");
        if (zoom_slider != null) {
            zoom_slider.blur();
        }
    };

	// ========================================================================
	// WATCHES
	// ========================================================================

    $scope.$watch('theme_id_selected', function (newValue, oldValue) {
        current_theme = themes[$rootScope.theme_id_selected];
        SetNodesTheme();
        DrawScene();
    }, true); 

    $scope.$watch('DocsNavTabs.selected_tab.page.zoom.current', function (newValue, oldValue) {
      $scope.DocsNavTabs.selected_tab.page.zoom.previous = oldValue;
      $scope.DoZoom();
    }, true); 


	// ========================================================================
	// DRAG & DROP
	// ========================================================================

    $scope.handleDrop = function(item_type, dest_id, position) {
        var header_height = HEADER_HEIGHT;

        CreateNode(null,
                   true,
                   item_type,
                   (position.clientX) / (GetCurrentDocumentZoom() / 100) + $scope.DocsNavTabs.selected_tab.page.CanvasPosition.x,
                   (position.clientY- header_height) / (GetCurrentDocumentZoom() / 100) + $scope.DocsNavTabs.selected_tab.page.CanvasPosition.y, '', null);
        SetNodesTheme();
        DrawScene();
    }

    $scope.AddNodeToThePage = function(item_type) {
        var header_height = HEADER_HEIGHT;

        CreateNode(null,
                   true,
                   item_type,
                   $scope.mouse_x,
                   $scope.mouse_y,
                   '',
                   null);
        SetNodesTheme();
        DrawScene();
    }

    $scope.AddPlotToTheNode = function(item_type) {
      if ($scope.OutputConnectorSelected()) {
          $scope.CreateNodeToConnector($scope.connector_selected.node,
                                       $scope.connector_selected,
                                       item_type);
      }
    };


	// ========================================================================
	// OUTPUTS (CHARTS, CONSOLES, ...)
	// ========================================================================

    $scope.ShowIfOutputConsoleIsSelected = function() {
        var ret = false;
        var options_nav_tabs = $scope.GetOutputsNavTabs();
        if ((options_nav_tabs != null) &&
            (options_nav_tabs.selected_tab != null)) {
            ret = (options_nav_tabs.selected_tab.id == 0);
        }

        return ret;
    };

    $scope.ShowIfOutputSelectedIs = function(id) {
        var ret = false;
        var options_nav_tabs = $scope.GetOutputsNavTabs();
        if ((options_nav_tabs != null) &&
            (options_nav_tabs.selected_tab != null) &&
            (options_nav_tabs.selected_tab.node != null)) {
            ret = (options_nav_tabs.selected_tab.node.id == id);
        }
        return ret;
    };


    function GetDataExample1() {
        var value = {
          labels: ["January", "February", "March", "April", "May", "June", "July"],
          series: ['Series A', 'Series B'],
          data: [
              [65, 59, 80, 81, 56, 55, 40],
              [28, 48, 40, 19, 86, 27, 90]
            ]
        };
        return value;
    };

    function GetDataExample2() {
        var value = [
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
            },
            {
                label: "Sample B",
                values: {
                    Q1: 300,
                    Q2: 350,
                    Q3: 400,
                    whisker_low: 225,
                    whisker_high: 425,
                    outliers: [175, 450, 480]
                }
            },
            {
                label: "Sample C",
                values: {
                    Q1: 100,
                    Q2: 200,
                    Q3: 300,
                    whisker_low: 25,
                    whisker_high: 400,
                    outliers: [450, 475]
                }
            },
            {
                label: "Sample D",
                values: {
                    Q1: 75,
                    Q2: 100,
                    Q3: 125,
                    whisker_low: 50,
                    whisker_high: 300,
                    outliers: [450]
                }
            },
            {
                label: "Sample E",
                values: {
                    Q1: 325,
                    Q2: 400,
                    Q3: 425,
                    whisker_low: 225,
                    whisker_high: 475,
                    outliers: [50, 100, 200]
                }
            }
        ];
        return value;
    };

    function GetDataExample3() {
        var value = [
            {
                key: "One",
                y: 5
            },
            {
                key: "Two",
                y: 2
            },
            {
                key: "Three",
                y: 9
            },
            {
                key: "Four",
                y: 7
            },
            {
                key: "Five",
                y: 4
            },
            {
                key: "Six",
                y: 3
            },
            {
                key: "Seven",
                y: .5
            }
        ];
        return value;
    };

    // User selects an Output Tab
    $scope.OnOutputTabPress = function(nav_tabs, id) {
        SelectTab(nav_tabs, id);

/*
        switch(nav_tabs.selected_tab.data.node.temp.type_obj.id) {
          case 'console':
            $scope.console = nav_tabs.selected_tab.data.node.value;
            //$scope.DoApply();
            break;
          case 'chart':
            $scope.AngularChartData = nav_tabs.selected_tab.data.node.value.data;
            $scope.AngularChartLabels = nav_tabs.selected_tab.data.node.value.labels;
            $scope.AngularChartSeries = nav_tabs.selected_tab.data.node.value.series;
            break;
          case 'donutchart':
            $scope.NVD3Options = {
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
            };
            $scope.NVD3Data = nav_tabs.selected_tab.data.node.value;
            //$scope.DoApply();
            break;
          case 'boxplot':
            $scope.NVD3Options = {
              chart: {
                type: 'boxPlotChart',
                height: 450,
                margin : {
                  top: 20,
                  right: 20,
                  bottom: 30,
                  left: 50
                },
                color:['darkblue', 'darkorange', 'green', 'darkred', 'darkviolet'],
                x: function(d){return d.label;},
                //y: function(d){return d.values.Q3;},
                maxBoxWidth: 55,
                yDomain: [0, 500]
              }
            };
            $scope.NVD3Data = nav_tabs.selected_tab.data.node.value;
            //$scope.DoApply();
            break;
        }
*/
        DrawScene();
      $scope.RefreshNVD3ChartByTabId(id);
    };


	// ========================================================================
	// NEW, LOAD, SAVE
	// ========================================================================

    function NewDocument() {
        //! nodes = [];
        DrawScene();
    };

    function GetMatrixTypeEquivalent(type) {
        var ret = type;

        if (ret.indexOf("_matrix") != -1) {
            // The type is already a matrix
        } else {
            if (ret.indexOf("_vector") != -1) {
                // Convert vector type into a matrix type
                ret = ReplaceAll(ret, "_vector", "_matrix");
            } else {
                if (ret.indexOf("_file") != -1) {
                    // File types must remain as file types
                } else {
                    if (ret.indexOf("string") != -1) {
                        // strings must be converted into matrices, too.
                        ret += "_matrix";
                    } else {
                        // Convert scalar type into a matrix type
                        ret += "_matrix";
                    }
                }
            }
        }
        
        return ret;
    };

    function SepareValueAndOrder(text) {
        var ret = {
            value: text,
            order: 0
        }
        
        if (text.indexOf(":") != -1) {
            ret.order = text.substr(0, text.indexOf(":"));
            if (isNaN(ret.order)) { // For example "hello:world". hello is not a number
                ret.order = 0;
            } else { // For example "3:world". 3 is a number
                ret.value = text.substr(text.indexOf(":") + 1);
            }
        }
            
        return ret;
    };

    function GetDocumentInterface(current_document) {
      var result = "";
      var ordered_inputs_list = [];
      var ordered_outputs_list = [];
      var missing_input_connections = false;
      var missing_output_connections = false;

      //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      // Create the ordered_inputs_list and the ordered_outputs_list
      //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

      var id = 0;
      for (var i = 0; i < current_document.nodes.length; i++) {
        var node = current_document.nodes[i];

        if (node.type == "input") {
          // Looking for the type of the current input.
          var the_input_type = '';

          // ***************
          // *** FOREACH ***
          // ***************
          if (node.value == 'Foreach') {
            the_input_type = 'string_vector';
          // ***************
          } else {
              // The type is in the connected node "[x]"
              // Nodes are liked in this way ["current input"]->[x]->[]->[]
              connected_node = arrays.FindArrayElementById(current_document.nodes,
                                                           node.outputs[0].to[0].node_id);
              if (connected_node != null) {
                connected_node_type = arrays.FindArrayElementById($scope.node_types,
                                                                  connected_node.type);
                connected_connector = connected_node_type.inputs[node.outputs[0].to[0].input_id];
                if (connected_connector != undefined) {
                    the_input_type = connected_connector.type;
                }
              }
          }

          separed = SepareValueAndOrder(node.value);

          if (the_input_type != '') {
              ordered_inputs_list.push({
                id: null,
                name: separed.value,
                type: the_input_type,
                order: separed.order
              });

              id++;
          } else {
            missing_input_connections = true;
          }
        }
      }
      id = 0;
      for (var i = 0; i < current_document.nodes.length; i++) {
        var node = current_document.nodes[i];

        if (node.type == "output") {
          // Looking for the type of the current output.
          // The type is in the connected node "[x]"
          // Nodes are liked in this way []->[]->["x"]->["current output"].
          // Note: ["x"] could connect to more than one nodes from the same output connection.
          var found = false;
          for (var j = 0; ((j < current_document.nodes.length) && (!found)); j++) {
            var nodeJ = current_document.nodes[j];

            for (var k = 0; ((k < nodeJ.outputs.length) && (!found)); k++) {
              for (var m = 0; ((m < nodeJ.outputs[k].to.length) && (!found)); m++) {
                if (nodeJ.outputs[k].to[m].node_id == node.id) {
                  found = true;
                  connected_node_type = arrays.FindArrayElementById($scope.node_types, nodeJ.type);
                  connected_connector = connected_node_type.outputs[m];

                  separed = SepareValueAndOrder(node.value);

                  if (connected_connector != undefined) {
                      ordered_outputs_list.push({
                        id: null,
                        name: separed.value,
                        type: GetMatrixTypeEquivalent(connected_connector.type),
                        order: separed.order
                      });
                  }

                  id++;
                }
              }
            }
          }

          if (!found) {
            missing_output_connections = true;
          }
        }
      }

      //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      // Orther both lists by the "order" value of their nodes
      //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

      ordered_inputs_list.sort(function(a, b) { return a.order > b.order; });
      ordered_outputs_list.sort(function(a, b) { return a.order > b.order; });

      //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      // Export info
      //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

      result += "\"interface\": {\n";

      result += "\"inputs\": [\n";
      for (var i = 0; i < ordered_inputs_list.length; i++) {
        if (i != 0) { result += ","; }
        result += "{\"id\":" + i + ",\"name\":\"" + ordered_inputs_list[i].name + "\",\"type\":\"" + ordered_inputs_list[i].type + "\"}";
      }

      result += "],\n";
      result += "\"outputs\": [\n";
      for (var i = 0; i < ordered_outputs_list.length; i++) {
        if (i != 0) { result += ","; }
        result += "{\"id\":" + i + ",\"name\":\"" + ordered_outputs_list[i].name + "\",\"type\":\"" + ordered_outputs_list[i].type + "\"}";
      }
      result += "]\n";
      result += "}";

      if ((missing_input_connections) || (missing_output_connections)) {
        //!TODO: Error that must be controlled
      }

      return result;
    };

    function GetDocumentNodes(current_document) {
      var result = "";

      result += "\"nodes\": [\n";
      for (var i = 0; i < current_document.nodes.length; i++) {
        var node = current_document.nodes[i];

        result += "{\"id\":";
        result += node.id;
        result += ",\"enabled\":";
        result += node.enabled;
        result += ",\"type\":\"";
        result += node.type;
        result += "\",\"x\":";
        result += node.position.left;
        result += ",\"y\":";
        result += node.position.top;
        result += ",\"value\":\"";
        result += (node.value != null)?node.value:"";
        result += "\",\"outputs\":";
        if (node.outputs.length == 0) result+= "[]";
        else result += JSON.stringify(node.outputs);

        if (i < current_document.nodes.length - 1) {
          result += "},\n";
        }
        else {
          result += "}\n";
        }
      }

      result += "\n]";

      return result;
    };


    function SaveExperiment(properties) {
        console.log("** SaveExperiment() **");

        var current_document = GetCurrentDocument();

        var data_str = "";
        data_str += "{\n";
        data_str += "\"properties\":" + JSON.stringify(properties) + ",\n";
        data_str += GetDocumentNodes(current_document) + "\n";
        data_str += "}\n";

        // MessagesFactory.alert(data_str);
        var data = JSON.parse(data_str);

        var send = {
          method: 'PUT',
          url: $rootScope.webAddress + 'repository_experiments/' + properties.name,
          headers: { 'Content-Type': 'application/json' },
          data: { data }
        };

        $rootScope.Http(send,
        function(message) {
          // Update document tab:
          GetCurrentDocument().properties = properties;
          DrawScene();

          // MessagesFactory.alert("Experiment Saved");
          $scope.DocsNavTabs.selected_tab.saved = true;
        },
        function(message) {
          MessagesFactory.alert("Not Saved");
        });
    };

    function SavePipeline(properties) {
        console.log("** SavePipeline() **");

        var current_document = GetCurrentDocument();

        var data_str = "";
        data_str += "{\n";
        data_str += "\"properties\":" + JSON.stringify(properties) + ",\n";
        data_str += GetDocumentInterface(current_document) + ",\n";
        data_str += GetDocumentNodes(current_document) + "\n";
        data_str += "}\n";

        // MessagesFactory.alert(data_str);
        var data = JSON.parse(data_str);

        var send = {
          method: 'PUT',
          url: $rootScope.webAddress + 'repository_pipelines/' + properties.name,
          headers: { 'Content-Type': 'application/json' },
          data: { data }
        };

        $rootScope.Http(send,
        function(message) {
          // Update document tab:
          GetCurrentDocument().properties = properties;
          GetCurrentDocument().saved = true;
          DrawScene();

          // MessagesFactory.alert("Pipeline Saved");
        },
        function(message) {
          MessagesFactory.alert("Not Saved");
        });
    };

    $scope.OnSave = function() {
        EnableCanvasInputKey = false;

        if (GetCurrentDocument().properties.type == $scope.FileType.EXPERIMENT) {
          var modalInstance = $modal.open({
              animation: true,
              templateUrl: 'partials/forms/form_experiment_properties.html',
              controller: 'FormExperimentPropertiesController',
              resolve: {
                  properties: function () {
                      return GetCurrentDocument().properties;
                  }
              }
          });
          modalInstance.result.then(
          function (properties) {
            EnableCanvasInputKey = true;
            SaveExperiment(properties);
          },
          function () {
            EnableCanvasInputKey = true;
          });
        }
        else {
          if (GetCurrentDocument().properties.type == $scope.FileType.PIPELINE) {
            var modalInstance = $modal.open({
                animation: true,
                templateUrl: 'partials/forms/form_pipeline_properties.html',
                controller: 'FormPipelinePropertiesController',
                resolve: {
                    properties: function () {
                        return GetCurrentDocument().properties;
                    }
                }
            });
            modalInstance.result.then(
            function (properties) {
              EnableCanvasInputKey = true;
              SavePipeline(properties);
            },
            function () {
              EnableCanvasInputKey = true;
            });
          }
        }
    };

	// ========================================================================
	// PLAY
	// ========================================================================






    function InformNodesAboutTheirExecutionOrder(execution_list) {
        // Inform each node of "nodes" about their execution order:

        for (var i = 0; i < GetCurrentDocumentNodes().length; i++) {
            GetCurrentDocumentNodes()[i].temp.execution_order = null;
        }
        for (var i = 0; i < execution_list.length; i++) {
            var node = arrays.FindArrayElementById(GetCurrentDocumentNodes(), execution_list[i].id);
            if (node != null) {
                node.temp.execution_order = i;
            }
        }

        if ($scope.debug_mode == true) {
            DrawScene();
        }
    };

    function SendExperimentAndGetCode(experiment_nodes) {
        console.log("** SendExperimentAndGetCode() **");

        $rootScope.Http({
		        method: 'POST',
		        url: $rootScope.webAddress + 'get_experiment_code',
		        headers: { 'Content-Type': 'application/json' },
		        data: {
              experiment: {
                name: GetCurrentDocument().properties.name,
                nodes: experiment_nodes,
                node_types: $scope.node_types // <<-- we are sending this information to the CM but CM should already have it.
              }
		        },
        },
        function(message) {
	      $scope.stdout = prepareOutput(message.data.data);
          CreateGraphs();
        },
        function(message) {
        });
    };


    function SendExperimentToBeExecuted(experiment_nodes) {
        console.log("** SendExperimentToBeExecuted() **");

        $rootScope.Http({
		        method: 'POST',
		        url: $rootScope.webAddress + 'execute_repository_experiment',
		        headers: { 'Content-Type': 'application/json' },
		        data: {
              experiment: {
                name: GetCurrentDocument().properties.name,
                nodes: experiment_nodes,
                node_types: $scope.node_types // <<-- we are sending this information to the CM but CM should already have it.
              }
		        },
        },
        function(message) {
          /*
          var data = JSON.parse(message.data.data);
          var experiment = $scope.GetSelectedExperiment();
          experiment.exec_data.num_instructions = data.num_instructions;
          experiment.exec_data.executed_instructions = data.executed_instructions;
          experiment.exec_data.job_done = Math.round(data.executed_instructions * 100 / data.num_instructions, 0);
          */
        },
        function(message) {
          console.log("** SendExperimentToBeExecuted() Error **");
        });
    };


    function PlayExperiment(dry_mode) {
      // Save the experiment first
      SaveExperiment(GetCurrentDocument().properties);

      var experiment_nodes = [];

      for (var i = 0; i < GetCurrentDocumentNodes().length; i++) {

          var experiment_node = {
              id: GetCurrentDocumentNodes()[i].id,
              enabled: GetCurrentDocumentNodes()[i].enabled,
              type: GetCurrentDocumentNodes()[i].type,
              value: GetCurrentDocumentNodes()[i].value,
              temp: { type_obj: GetCurrentDocumentNodes()[i].temp.type_obj },
              node_type_inputs: GetCurrentDocumentNodes()[i].inputs.length,
              inputs: [],
              outputs: GetCurrentDocumentNodes()[i].outputs,
              num_inputs_satisfied: 0
          };

          experiment_nodes.push(experiment_node);
      }

      if (dry_mode) {
          SendExperimentAndGetCode(experiment_nodes);
      } else {
          SendExperimentToBeExecuted(experiment_nodes);
      }

      // Enlist the experiment id to be notified when the experiment ends:
      var selected_experiment = $scope.GetSelectedExperiment();
      if (selected_experiment != null) {
        OngoingExperimentsList.push({id: selected_experiment.experiment_id});
      }
    };

    $scope.OnPlay = function() {
      if (GetCurrentDocument().properties.type == $scope.FileType.EXPERIMENT) {

        /*
        var selected_experiment = $scope.GetSelectedExperiment();

        if (selected_experiment != null) {

            // Remove the previous results and logs
            $scope.OnClearExperiment(selected_experiment.experiment_id);

            // Remove the previous experiment
            $scope.OnRemoveExperiment(selected_experiment.experiment_id);
        }
        */

        PlayExperiment(false);
      }

      /*
        $scope.OnCleanOutput();

        var experiment_nodes = [];

        for (var i = 0; i < GetCurrentDocumentNodes().length; i++) {

            var experiment_node = {
                id: GetCurrentDocumentNodes()[i].id,
                enabled: GetCurrentDocumentNodes()[i].enabled,
                type: GetCurrentDocumentNodes()[i].type,
                value: GetCurrentDocumentNodes()[i].value,
                temp: { type_obj: GetCurrentDocumentNodes()[i].temp.type_obj },
                node_type_inputs: GetCurrentDocumentNodes()[i].inputs.length,
                inputs: [],
                outputs: GetCurrentDocumentNodes()[i].outputs,
                num_inputs_satisfied: 0
            };

            experiment_nodes.push(experiment_node);
        }

        SendExperimentToBeExecuted(experiment_nodes);
      */

/*
        var dependecies_list = CreateDependenciesList();

//      var summary_dependencies = "";
//
//      summary_dependencies += "Dependencies List:<br />";
//      for (var i = 0; i < dependecies_list.length; i++) {
//          summary_dependencies += GetNodeInfo(dependecies_list[i]);
//      }
//
//      MessagesFactory.alert(summary_dependencies);

        var execution_list = CreateExecutionList(dependecies_list);

        InformNodesAboutTheirExecutionOrder(execution_list);

        GenerateCode(execution_list);
       
//      var summary_execution = "";
//
//      summary_execution += "Dependencies List:<br />";
//      for (var i = 0; i < dependecies_list.length; i++) {
//          summary_execution += GetNodeInfo(dependecies_list[i]);
//      }
//      summary_execution += "<br /><br />";
//      summary_execution += "Execution List:<br />";
//      for (var i = 0; i < execution_list.length; i++) {
//          summary_execution += GetNodeInfo(execution_list[i]);
//      }
//
//      MessagesFactory.alert(summary_execution);
*/
        
    };

    $scope.OnGetCode = function() {
      if (GetCurrentDocument().properties.type == $scope.FileType.EXPERIMENT) {
        PlayExperiment(true);
      }
    };


    $scope.OnClearExperiment = function(experiment_id) {
      var selected_experiment = $scope.GetExperiment(experiment_id);
      $rootScope.Http(
        {
          method:  'DELETE',
          url:     $rootScope.webAddress + 'results/' + selected_experiment.experiment_id,
          headers: { 'Content-Type': 'application/json' },
          params:  { "experiment_id": selected_experiment.experiment_id },
          data:    {},
        },
        function(message) {
        },
        function(message) {
          AlertService.error("Output could not be cleared.");
          PlayExperiment(false);
        }    
      ); 
    };

  // ========================================================================
	// EXPERIMENTS GRAPHS
	// ========================================================================

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
    if (($scope.stdout == null) || ($scope.stdout == "")) {
      return;
    }

    graph_list = [];

    // Example:
    // <br />node|4|boxplot|0|{"id":"s","type":"string","value":"Example 1"}<br />

    // $scope.stdout contains:
    //  [EXPERIMENT_START]
    //  ...
    //  [EXPERIMENT_END]
    //  [EXPERIMENT_START]
    //  ...
    //  [EXPERIMENT_END]

    var last_experiment_log = "[EMPTY]";
    var experiment_parts =  $scope.stdout.split('[EXPERIMENT_START]');
    if (experiment_parts.length > 0) {
      last_experiment_log = experiment_parts[experiment_parts.length - 1];
    }

    // Before, the node can started with this string: "<br />node|"
    // But now, it starts with "<br />&nbsp;node|" or "<br />&nbsp;&nbsp;node|" or ...

    var node_pos = 0;
    var find_start_node = "&nbsp;node|";
    do {
      node_pos = last_experiment_log.indexOf(find_start_node, node_pos + 1);
      if (node_pos != -1) {

        var beautiful_var_name = "";
        var beautiful_param_name = "";
        var num_input = 0;
        var graph_node = {
          "node":0,
          "type":"",
          "inputs":[]
        };

        var eol_pos = last_experiment_log.indexOf("<br />",  node_pos + 1);
        if (eol_pos != -1) {
          try {
            var line = last_experiment_log.substr(node_pos, eol_pos - node_pos);

            // line = "<br />node|4|boxplot|0|beautiful name|param name|{"id":"s","type":"string","value":"Example 1"}"

            line = ReplaceAll(line, find_start_node, "");
            line = line.substr(line.indexOf("|") + 1);

            // line = "4|boxplot|0|beautiful name|param name|{"id":"s","type":"string","value":"Example 1"}"

            graph_node.node = line.substr(0, line.indexOf("|"));
            line = line.substr(line.indexOf("|") + 1);

            // line = "boxplot|0|beautiful name|param name|{"id":"s","type":"string","value":"Example 1"}"
            // beautiful_var_name = "";
            // beautiful_param_name = "";
            // num_input = 0;
            //  var graph_node = {
            //   "node":4,<-----
            //   "type":"",
            //   "inputs":[]
            // };

            graph_node.type = line.substr(0, line.indexOf("|"));
            line = line.substr(line.indexOf("|") + 1);

            // line = "0|beautiful name|param name|{"id":"s","type":"string","value":"Example 1"}"
            // beautiful_var_name = "";
            // beautiful_param_name = "";
            // num_input = 0;
            //  var graph_node = {
            //   "node":4,
            //   "type":"boxplot",<-----
            //   "inputs":[]
            // };

            num_input = line.substr(0, line.indexOf("|"));
            line = line.substr(line.indexOf("|") + 1);

            // line = "beautiful name|param name|{"id":"s","type":"string","value":"Example 1"}"
            // beautiful_var_name = "";
            // beautiful_param_name = "";
            // num_input = 0;<-----
            //  var graph_node = {
            //   "node":4,
            //   "type":"boxplot",
            //   "inputs":[]
            // };

            beautiful_var_name = line.substr(0, line.indexOf("|"));
            line = line.substr(line.indexOf("|") + 1);
            // line = "param name|{"":"","id":"s","type":"string","value":"Example 1"}"
            // beautiful_var_name = "beautiful name"; <-----
            // beautiful_param_name = "";
            // num_input = 0;
            //  var graph_node = {
            //   "node":4,
            //   "type":"boxplot",
            //   "inputs":[]
            // };

            beautiful_param_name = line.substr(0, line.indexOf("|"));
            line = line.substr(line.indexOf("|") + 1);
            // line = "{"":"","id":"s","type":"string","value":"Example 1"}"
            // beautiful_var_name = "beautiful name";
            // beautiful_param_name = "param name"; <-----
            // num_input = 0;
            //  var graph_node = {
            //   "node":4,
            //   "type":"boxplot",
            //   "inputs":[]
            // };

            var new_input = JSON.parse(line);

            graph_node.inputs.push(new_input);

            line = "";

            // line = ""
            // beautiful_var_name = "beautiful name";
            // beautiful_param_name = "param name";
            // num_input = 0;
            //  var graph_node = {
            //   "node":4,
            //   "type":"boxplot",
            //   "inputs":[{"id":"s","type":"string","value":"Example 1"}]<-----
            // };
        
            graph_node.inputs[0].name = beautiful_var_name;
            graph_node.inputs[0].param = beautiful_param_name;
            graph_node.inputs[0].id = num_input;

            //  var graph_node = {
            //   "node":4,
            //   "type":"boxplot",
            //   "inputs":[{"name":"beautiful name",<-----
            //              "param":"param name", <-----
            //              "id":"0", <-----
            //              "type":"string","value":"Example 1"}]
            // };

            var graph_found = null;
            for (var i = 0; ((i < graph_list.length) && (graph_found == null)); i++) {
              if (graph_list[i].node == graph_node.node) {
                graph_found = graph_list[i];
              }
            }

            if (graph_found != null) {
              /*
              var found = false;
              for (var j = 0; ((j < graph_found.inputs.length) && (found == false)); j++) {
                found = (graph_found.inputs[j].id == graph_node.inputs[0].id);
              }
              if (!found) {
                // New input for existing graph
                graph_found.inputs.push(graph_node.inputs[0]);
              }
              */
              graph_found.inputs.push(graph_node.inputs[0]);
            } else {
              // New graph with first input
              graph_list.push(graph_node);
            }

            /*
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
            */
          }
          catch(e) {
            AlertService.error(e + "\n" + line);
          }

        }
      }
    } while(node_pos != -1);

    /*
    $scope.charts = [
    ];
    $scope.consoles = [
    ];
    */
    $scope.ClearExperimentGraphs();

    for (var i = 0; i < graph_list.length; i++) {
      switch(graph_list[i].type) {
        // =====================================================================
        case "console":
        // =====================================================================
          var new_chart = {
            "id":graph_list[i].node,// $scope.charts.length+1,
            "type":"console" //<--- This is the id used by the view for filtering the list of charts.
            //END_CHART_PROPERTIES
          };
          $scope.charts.push(new_chart);
          break;

        // =====================================================================
        case "chart":
        // =====================================================================
          var new_chart = {
            "id":graph_list[i].node,// $scope.charts.length+1,
            "type":"chart", //<--- This is the id used by the view for filtering the list of charts.
            "data":[], 
            "labels":[],
            "series":[]
            //END_CHART_PROPERTIES
          };

          for (var j = 0; j < graph_list[i].inputs.length; j++) {
            new_chart.data.push(graph_list[i].inputs[j].value);
            new_chart.series.push(graph_list[i].inputs[j].name);
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

        case "Print&nbsp;Data":
          var new_console = {
            "id":graph_list[i].node,// $scope.consoles.length+1,
            "data":""
          };

          for (var j = 0; j < graph_list[i].inputs.length; j++) {
            new_console.data += graph_list[i].inputs[j].value;
          }
          new_console.data += "<br />";

          $scope.consoles.push(new_console);

          break;

        case "R&nbsp;Export":
          var new_console = {
            "id":graph_list[i].node,// $scope.consoles.length+1,
            "data":""
          };

          new_console.data =  "# R CSV Import:<br />";
          new_console.data += "# mydata <- read.table(\"file.csv\", header=TRUE, sep=\",\")<br />";
          new_console.data += "<br />";



          var max_vector_length = 0;
          for (var j = 0; j < graph_list[i].inputs.length; j++) {
            // This is the code for building the header when multiple outputs go to the same R Export node.
            // Disactivated because if the output is only one matrix, we do not have its headers and this code returns ("")
            /*
            new_console.data += "\"" + graph_list[i].inputs[j].name + "\"";
            new_console.data += ",";
            */

            if (graph_list[i].inputs[j].value.length > max_vector_length) {
              max_vector_length = graph_list[i].inputs[j].value.length;
            }
          }
          /*new_console.data += "<br />";*/


          for (var k = 0; k < max_vector_length; k++) {
            for (var j = 0; j < graph_list[i].inputs.length; j++) {
              if (k < graph_list[i].inputs[j].value.length) {
                if (IsObject(graph_list[i].inputs[j].value[k]) == true) {
                    // It is a matrix
                    new_console.data += graph_list[i].inputs[j].value[k].values;
                } else {
                    // It is a vector
                    new_console.data += graph_list[i].inputs[j].value[k];
                }
              }
              if (!((k == max_vector_length -1) && (j == graph_list[i].inputs.length -1))) { new_console.data += ","; }
            }
            new_console.data += "<br />";
          }

          $scope.consoles.push(new_console);

          break;

        // =====================================================================
        case "boxplot":
        // =====================================================================

        /*
        {"name":"Theta(Wt)","param":"Q1","id":"multiboxplot/15_10_15/calc-boxplot-values_3_0","type":"double","value":"14.4"}
        {"name":"Theta(Wt)","param":"Q2","id":"multiboxplot/15_10_15/calc-boxplot-values_3_1","type":"double","value":"14.45"}
        {"name":"Theta(Wt)","param":"Q3","id":"multiboxplot/15_10_15/calc-boxplot-values_3_2","type":"double","value":"14.6"}
        {"name":"Theta(Wt)","param":"Min","id":"multiboxplot/15_10_15/calc-boxplot-values_3_3","type":"double","value":"14.4"}
        {"name":"Theta(Wt)","param":"Max","id":"multiboxplot/15_10_15/calc-boxplot-values_3_4","type":"double","value":"14.7"}
        {"name":"Theta(Wt)","param":"Outliers","id":"","type":"double_vector","value":["10.2","14.1"]}
        {"name":"Theta(Wt)","param":"Q1","id":"multiboxplot/15_10_15/calc-boxplot-values_3_0","type":"double","value":"10.2"}
        {"name":"Theta(Wt)","param":"Q2","id":"multiboxplot/15_10_15/calc-boxplot-values_3_1","type":"double","value":"12.05"}
        {"name":"Theta(Wt)","param":"Q3","id":"multiboxplot/15_10_15/calc-boxplot-values_3_2","type":"double","value":"13.5"}
        {"name":"Theta(Wt)","param":"Min","id":"multiboxplot/15_10_15/calc-boxplot-values_3_3","type":"double","value":"10.1"}
        {"name":"Theta(Wt)","param":"Max","id":"multiboxplot/15_10_15/calc-boxplot-values_3_4","type":"double","value":"14.2"}
        {"name":"Theta(Wt)","param":"Outliers","id":"","type":"double_vector","value":[]}
        {"name":"Theta(Wt)","param":"Q1","id":"multiboxplot/15_10_15/calc-boxplot-values_3_0","type":"double","value":"10.2"}
        {"name":"Theta(Wt)","param":"Q2","id":"multiboxplot/15_10_15/calc-boxplot-values_3_1","type":"double","value":"14.15"}
        {"name":"Theta(Wt)","param":"Q3","id":"multiboxplot/15_10_15/calc-boxplot-values_3_2","type":"double","value":"16.2"}
        {"name":"Theta(Wt)","param":"Min","id":"multiboxplot/15_10_15/calc-boxplot-values_3_3","type":"double","value":"10.2"}
        {"name":"Theta(Wt)","param":"Max","id":"multiboxplot/15_10_15/calc-boxplot-values_3_4","type":"double","value":"17.2"}
        {"name":"Theta(Wt)","param":"Outliers","id":"","type":"double_vector","value":["0"]}

node|5|boxplot|0|Theta/nt(Wat)|Q1|{"id":"multichart/11_40_31/calc-boxplot-values_5_0","type":"double","value":"14.4"}
node|5|boxplot|0|Theta/nt(Wat)|Q2|{"id":"multichart/11_40_31/calc-boxplot-values_5_1","type":"double","value":"14.45"}
node|5|boxplot|0|Theta/nt(Wat)|Q3|{"id":"multichart/11_40_31/calc-boxplot-values_5_2","type":"double","value":"14.6"}
node|5|boxplot|0|Theta/nt(Wat)|Min|{"id":"multichart/11_40_31/calc-boxplot-values_5_3","type":"double","value":"14.4"}
node|5|boxplot|0|Theta/nt(Wat)|Max|{"id":"multichart/11_40_31/calc-boxplot-values_5_4","type":"double","value":"14.7"}
node|5|boxplot|0|Theta/nt(Wat)|Outliers|{"id":"","type":"double_vector","value":["10.2","14.1"]}

node|5|boxplot|1|Theta/nt(Taj)|Q1|{"id":"multichart/11_40_31/calc-boxplot-values_5_0","type":"double","value":"10.2"}
node|5|boxplot|1|Theta/nt(Taj)|Q2|{"id":"multichart/11_40_31/calc-boxplot-values_5_1","type":"double","value":"12.05"}
node|5|boxplot|1|Theta/nt(Taj)|Q3|{"id":"multichart/11_40_31/calc-boxplot-values_5_2","type":"double","value":"13.5"}
node|5|boxplot|1|Theta/nt(Taj)|Min|{"id":"multichart/11_40_31/calc-boxplot-values_5_3","type":"double","value":"10.1"}
node|5|boxplot|1|Theta/nt(Taj)|Max|{"id":"multichart/11_40_31/calc-boxplot-values_5_4","type":"double","value":"14.2"}
node|5|boxplot|1|Theta/nt(Taj)|Outliers|{"id":"","type":"double_vector","value":[]}

node|5|boxplot|2|Theta/nt(Fu&Li)|Q1|{"id":"multichart/11_40_31/calc-boxplot-values_5_0","type":"double","value":"10.2"}
node|5|boxplot|2|Theta/nt(Fu&Li)|Q2|{"id":"multichart/11_40_31/calc-boxplot-values_5_1","type":"double","value":"14.15"}
node|5|boxplot|2|Theta/nt(Fu&Li)|Q3|{"id":"multichart/11_40_31/calc-boxplot-values_5_2","type":"double","value":"16.2"}
node|5|boxplot|2|Theta/nt(Fu&Li)|Min|{"id":"multichart/11_40_31/calc-boxplot-values_5_3","type":"double","value":"10.2"}
node|5|boxplot|2|Theta/nt(Fu&Li)|Max|{"id":"multichart/11_40_31/calc-boxplot-values_5_4","type":"double","value":"17.2"}
node|5|boxplot|2|Theta/nt(Fu&Li)|Outliers|{"id":"","type":"double_vector","value":["0"]}

        */

        var new_boxplot_list = [];

        for (var j = 0; j < graph_list[i].inputs.length; j+=6) {
          var new_box_plot = {
            label: graph_list[i].inputs[j+0].name, // "inputs[j+0].name" but "inputs[j+0..6].name" have all the same name.
            values: {
                Q1: graph_list[i].inputs[j+0].value * 1,
                Q2: graph_list[i].inputs[j+1].value * 1,
                Q3: graph_list[i].inputs[j+2].value * 1,
                whisker_low: graph_list[i].inputs[j+3].value * 1,
                whisker_high: graph_list[i].inputs[j+4].value * 1,
                outliers: graph_list[i].inputs[j+5].value
            }
          };
          new_boxplot_list.push(new_box_plot);

          var domain = {
            min: new_box_plot.values.whisker_low,
            max: new_box_plot.values.whisker_high
          };

          // Update domain
          for (var k = 0; k < graph_list[i].inputs[5].value.length; k++) {
            var outlier = graph_list[i].inputs[5].value[k] * 1;
            if (outlier < domain.min) { domain.min = outlier; }
            if (outlier > domain.max) { domain.max = outlier; }
          }

          domain.max = Math.ceil(domain.max);
          domain.min = Math.floor(domain.min);
        }


/*
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
*/





          var new_boxplot_chart = {
            "id":graph_list[i].node,// $scope.charts.length+1,
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
                ,yDomain: [domain.min, domain.max]
              }
            },
            "data":new_boxplot_list,
            "config":"config",
            "events":"events",
            "api_content":{}
            //END_CHART_PROPERTIES
          };

          $scope.charts.push(new_boxplot_chart);

          break;

        // =====================================================================
        case 'donutchart':
        // =====================================================================
          var new_donutchart = {
            "id":graph_list[i].node,// $scope.charts.length+1,
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
            //END_CHART_PROPERTIES
          };

          $scope.charts.push(new_donutchart);
          break;
      }
    }

    // =========================================================================
    // Colorize console &
    // Errors / Warnings Count
    // =========================================================================

    var errors = [];
    var warnings = [];
/* 
    for (var i = 0; i < $scope.node_types.length; i++) {
      if ($scope.node_types[i].style == $scope.NodeStyle.DATA_NODE) {
        $scope.stdout = ReplaceAll($scope.stdout, "--as&nbsp;" + $scope.node_types[i].id, "--as&nbsp;<span style='color: blue'>" + $scope.node_types[i].id + "</span>");
      }
      if ($scope.node_types[i].style == $scope.NodeStyle.CALCULATION_NODE) {
        $scope.stdout = ReplaceAll($scope.stdout, $scope.node_types[i].id, "<b>" + $scope.node_types[i].id + "</b>");
      }
    }
*/
    $scope.stdout_original = $scope.stdout;

    for (var i = 0; i < commands_list.length; i++) {
      $scope.stdout = ReplaceAll($scope.stdout, "&nbsp;" + commands_list[i].id, "&nbsp;<span style='color: blue'>" + commands_list[i].id + "</span>");
      //$scope.stdout = ReplaceAll($scope.stdout, "&#36;&nbsp;" + commands_list[i].id, "&#36;&nbsp;<span style='color: blue'>" + commands_list[i].id + "</span>");
    }

    var stdout_lines = $scope.stdout.split('<br />');
    $scope.stdout = "";

    for (var i = 0; i < stdout_lines.length; i++) {
      var line = stdout_lines[i];

      if ((line!="")&&(line.indexOf("$&nbsp;") == 0)) {
        // It is a code line

        var line_parts = line.split('"');
        if (line_parts.length == 1) {
          // the line does not contain (")
        } else {
          // the line contains (")
          line = "";
          var quotes_start = true;
          for (var j = 0; j < line_parts.length; j++) {
            line += line_parts[j];

            if (quotes_start) {
              if (j+1 < line_parts.length) {
                line += "<span style='color: orange'>\"";
                quotes_start = false;
              }
            } else {
              line += "\"</span>";
              quotes_start = true;
            }
          }
        }
      }
      else {
        // It is a result line
        if (line.indexOf("Error:") == -1) {
            if (line.indexOf("Warning:") == -1) {
              // The result is normal
              line = "<span style='color: #89a000'>" + line + "</span>";
            } else {
              // The result is a warning
              line = line.split('Warning:').join("<span class='warning_message'><b>Warning:'");
              line += "</b></span>";
              warnings.push(line);
            }
        } else {
          // The result is an error
          line = line.split('Error:').join("<span class='error_message'><b>Error:'");
          line += "</b></span>";
          errors.push(line);
        }
      }
    
      $scope.stdout += line;

      $scope.stdout += "<br />";
    }

    // =========================================================================
    // Error Report
    // =========================================================================

    $scope.stdout += "<hr>";

    if (errors.length > 0) {
        $scope.stdout += "<span class='ko_result'><b>EXECUTION FAILED. " + errors.length + " Errors and " + warnings.length + " Warnings.</b></span><br />";
    } else {
        $scope.stdout += "<span class='ok_result'><b>EXECUTION SUCCESSFUL. ";
        if (warnings.length > 0) {
            $scope.stdout += warnings.length;
            $scope.stdout += " Warnings.";
        }
        $scope.stdout += "</b></span><br />";
    }

    $scope.stdout += "<hr>";
  };

  $scope.trustAsHtml = function(string) {
      return $sce.trustAsHtml(string);
  };

  // ========================================================================
	// EXPERIMENTS PAGE EVENTS
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

	$rootScope.OnSelectExperiment = function(experiment) {
        $rootScope.selected_experiment_id = experiment.experiment_id;
        LoadExperiment(experiment.name);

		$rootScope.OnGetOutput();
		$scope.OnQueryExperiment();
	};

	$scope.OnCreateExperiment = function() {
		$scope.ClearExperimentOutputs();

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
    var selected_experiment = $scope.GetSelectedExperiment();
    if ((selected_experiment.status == 'NOT_STARTED') ||
        (selected_experiment.status == 'OPEN')) {
  		$scope.show_query_experiment = true;
    }
	};

	$scope.OnExecuteCommand = function() {
    var selected_experiment = $scope.GetSelectedExperiment();

    // The first command executed changes the status to open:
    if (selected_experiment.status == 'NOT_STARTED') {
      selected_experiment.status = 'OPEN';
    }

    if (selected_experiment.status == 'OPEN') {

      if ($scope.cmd == "dm") {
          var send = {
            method: 'GET',
            url: $rootScope.webAddress + 'datavariables/' + selected_experiment.experiment_id,
            headers: { 'Content-Type': 'application/json' },
            params: { "experiment_id": selected_experiment.experiment_id },
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
          $scope.ClearExperimentOutputs();
          var send = {
            method: 'PUT',
            url: $rootScope.webAddress + 'results/' + selected_experiment.experiment_id + '/' + encodeURIComponent($scope.cmd),
            headers: { 'Content-Type': 'application/json' },
            params: { "experiment_id": selected_experiment.experiment_id, "cmd": $scope.cmd },
            data: {},
          };

          if ($scope.cmd == "exit") {
            $rootScope.Http(send, function(message) {
                                    $scope.OnCloseQueryExperiment();
                                  },
                                  function(message) {
                                    AlertService.error("Command NOT executed.");
                                  });

            selected_experiment.status = 'CLOSING...';
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

    function prepareOutput(output) {

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

        // Code Identatation
        // =================

        if (output != null) {
            lines = output.split("<br />");
            output = "";
            var ident = 0;
            var ident_spaces = 4;
            var it_is_a_command = false;

            for (var i = 0; i < lines.length; i++) {
                var line = lines[i];

                if (line.indexOf("$&nbsp;else") != -1) {
                    ident -= ident_spaces;
                }

                if (line.indexOf("$&nbsp;endif") != -1) {
                    ident -= ident_spaces;
                }

                if (line.indexOf("$&nbsp;end-for") != -1) {
                    ident -= ident_spaces;
                }

                it_is_a_command = (line.indexOf("$&nbsp;") == 0);

                if (it_is_a_command) {
                    output += "$&nbsp;";
                }
                for(var t = 0; t < ident; t++) {
                    output += "&nbsp;";
                }

                if (it_is_a_command) {
                    output += line.substring("$&nbsp;".length);
                } else {
                    output += "&nbsp;&nbsp;" + line;
                }

                output += "<br />";

                if (line.indexOf("$&nbsp;if&nbsp;") != -1) {
                    ident += ident_spaces;
                }

                if (line.indexOf("$&nbsp;for&nbsp;") != -1) {
                    ident += ident_spaces;
                }

                if (line.indexOf("$&nbsp;else") != -1) {
                    ident += ident_spaces;
                }
            }
        }

        return output;
    };

	$rootScope.OnGetOutput = function() {
        $scope.ClearExperimentOutputs();

        var selected_experiment = $scope.GetSelectedExperiment();

        if (selected_experiment.status == 'OPEN') {
		    $rootScope.Http({
		            method: 'GET',
		            url: $rootScope.webAddress + 'results/' + selected_experiment.experiment_id,
				    headers: { 'Content-Type': 'application/json' },
				    params: { "experiment_id": selected_experiment.experiment_id },
		            data: {},
	        },
		    function(message) {
			    $scope.stdout = prepareOutput(message.data.data.result);
                CreateGraphs();
		    },
		    function(message) {
       			AlertService.error("Command NOT executed.");
		    });
        }
	};

	$scope.OnCleanOutput = function() {
    var selected_experiment = $scope.GetSelectedExperiment();

    if (selected_experiment.status == 'OPEN') {
      try {
        $rootScope.Http(
          {
            method:  'DELETE',
            url:     $rootScope.webAddress + 'results/' + selected_experiment.experiment_id,
            headers: { 'Content-Type': 'application/json' },
            params:  { "experiment_id": selected_experiment.experiment_id },
            data:    {},
          },
          function(message) {
            $rootScope.OnGetOutput();
          },
          function(message) {
		        AlertService.error("Command NOT executed.");
          }
        );
      } catch(e) {
        AlertService.error("OnCleanOutput catch: " + e);
      }
    } else {
      AlertService.error("This experiment is not available.");
    }
	};

	// ========================================================================
	// EXPERIMENTS VISIBILITY
	// ========================================================================

	$scope.ShowCleanOutputButton = function() {
		return ($scope.stdout != "");
	};

	$scope.ClearExperimentGraphs = function()  {
    $scope.charts = [];
    $scope.consoles = [];
  }

	$scope.ClearExperimentOutputs = function()  {
    $scope.stdout_original = "";  // The original one
    $scope.stdout = "";           // The colorized one
    $scope.ClearExperimentGraphs();
	};

	$scope.SetExperimentKey = function(lm_key, bin_key)  {
		$scope.key = lm_key + "-" + bin_key;
	};

	////$scope.IsExperimentSelected = function() {
////		return (($scope.selected_experiment != null) && ($scope.selected_experiment.experiment_id != ""));
////	};

	$scope.ShowQueryExperiment = function() {
		return $scope.show_query_experiment;
	};

	$scope.OnCloseQueryExperiment = function() {
		$scope.show_query_experiment = false;
	};

// +++++


  $scope.GetExperiment = function(experiment_id) {
    var ret = null;

    for (var i = 0; ((i < $rootScope.experiments_list.length) &&
                     (ret == null)); i++) {
      if ($rootScope.experiments_list[i].experiment_id == experiment_id) {
        ret = $rootScope.experiments_list[i];
      }
    }

    return ret;
  };

  $scope.GetSelectedExperiment = function() {
    return $scope.GetExperiment($rootScope.selected_experiment_id);
  };


  $scope.InformExperimentFinished = function(experiment_id) {
    var experiment = $scope.GetExperiment();

    if (experiment == null) {
      experiment = $rootScope.experiments_list[0]; 
    }

    if (experiment.exec_data.job_done == 100) {
      var found = arrays.FindArrayElementById(OngoingExperimentsList, experiment_id);
      if (found != null) {
        arrays.RemoveElementById(OngoingExperimentsList, experiment_id);
//        $scope.OnOutputTabPress($scope.GetOutputsNavTabs(), experiment_id);


      	$rootScope.OnSelectExperiment(experiment);

      }
    }
    return "Finished";
  };


        // =====================
        // UNREGISTER DATA FILES
        // =====================
	    function GetFileName(path_file_name) {
            return path_file_name.split('/').pop();

	    };

	    function GetPath(path_file_name) {
            var len = (path_file_name.split('/')).length;          // a/b/c/d/file.txt   len =5
            path_file_name = path_file_name.split('/', len-1).join('/')      // path_file_name = a/b/c/d 
            path_file_name += '/';  // path_file_name = a/b/c/d/
            return path_file_name;
	    };

        $scope.OnUnregisterDataFile = function() {

          if ($scope.SelectedNodes()) {
            var unregisterFile = {
                "location":GetPath($scope.node_selected.value),
                "filename":GetFileName($scope.node_selected.value)
            };

            MessagesFactory.confirm("Are you sure that you want to unregister the data file " + unregisterFile.location + unregisterFile.filename + "?", 
            function() {  // Yes
                var send = {
                  method: 'DELETE',
                  url: $rootScope.webAddress + 'datafiles/' + ReplaceAll(unregisterFile.location, '/', 'slash') + '/' + ReplaceAll(unregisterFile.filename, '/', 'slash'),
                  headers: { 'Content-Type': 'application/json' },
                  data: {}
                };

                $rootScope.Http(send,
                function(message) {
                    alert('File unregistered');
                    GetDataFilesList(null);
                },
                function(message) {
                    alert('File could not be unregistered');
                });
            },
            function() {  // No
            });
          }
        };


	$scope.init();
});







