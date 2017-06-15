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
/*
  // ===========================================================================
  var experiments_status_list = [];

  this.AddExperimentToStatusList = function(experiment) {
    var experiment_status = self.GetExperimentFromStatusList();
    if (experiment_status == null) {
      experiments_status_list.push({
        "id": experiment,
        "total_instructions": 0,
        "executed_instructions": 0,
        "finished": false
      });
    }
  };

  this.GetExperimentFromStatusList = function(experiment) {
    return arrays.FindArrayElementById(experiments_status_list, experiment);
  };

  this.RemoveExperimentFromStatusList = function(experiment) {
    for (i = 0; i < experiments_status_list.length; i++) {
      if (experiments_status_list[i].id == experiment) {
        experiments_status_list.splice(i, 1);
        break;
      }
    }
  };
  // ===========================================================================
*/

/// ---------------------------------------------------------------------------
/// @file cm.js
/// @namespace ngaSP
/// Module description
/// ---------------------------------------------------------------------------

// ============================================================================
// INCLUDES
// ============================================================================

var Constants		= require('./constants');
var cte = new Constants();

var StringTable		= require("./strings.js");
var string_table = new StringTable();

var cout			= require("./logs");
var string_tools 	= require('./string_tools');
var math_tools		= require('./math_tools');

var split = require('split');
var fs = require('fs');

var shell = require('shelljs');

// ============================================================================
// CONSTANTS
// ============================================================================

var NodeStyle = { // Must be consecutive numbers (for accessing an array). They are defined in the pipelineEditorController, too. They must match!
    CALCULATION_NODE:     0,
    INPUT_NODE:           1,
    OUTPUT_NODE:          2,
    GRAPH_NODE:           3,
    DATA_NODE:            4,
    PIPELINE_NODE:        5,
    NULL_CONNECTION:      6
};

var VAR_INI = "";
var VAR_FIN = "/";

// var REPOSITORY_PATH = __dirname + "/../repository/";
// var REPOSITORY_PATH = "/repository/";
   var REPOSITORY_PATH = __dirname + "/../../repository/";
var REPO_PIPELINES_PATH = REPOSITORY_PATH + "pipelines/";
var REPO_EXPERIMENTS_PATH = REPOSITORY_PATH + "experiments/";

// ============================================================================
// EXPORT
// ============================================================================

module.exports = function() {
	this.net = require('net');				// Net communication between CM
											// and all its Local Managers

	this.local_managers_list  = [];  		// List of local managers
	this.experiments_list  = [];  			// List of experiments
    this.clients_list = [];                 // List of connected browsers

	this.client_response_list = [];			// client response objects
	this.client_socket = null;				// Current web client socket

	var self = this;						// Pointer to access this object inside the class
	var interval_check_LMs_status = null;	// Interval for checking connection with all local managers


    this.data_files_list  = [];  		    // List of data files

    this.SetClientSocket = function(sock) {
        this.client_socket = sock;
        cout.cm("Set client socket: " + this.client_socket);
    };


	// ============================================================================
	// MESSAGES FROM NODE (server.js) TO THE CENTRAL MANAGER
	// (PUBLIC METHODS)
	// ============================================================================

	/// Description.
	this.Start = function() {
		cout.cm("Starting...");

		// This function receives each local manager messages via lm_socket.
		self.net.createServer(function(lm_socket) {
			self.ReceiveMensagesFromLocalManagers(lm_socket);
		}).listen(cte.PORT_CM(), cte.HOST());

		cout.cm(string_table.CM_LISTENING() + cte.HOST() + " " + cte.PORT_CM() + ".");

        self.loadDataFilesTable();

		cout.cm("Starting the interval for updating the local managers list...");
		interval_check_LMs_status = setInterval(self.CheckAllLocalManagersStatus, cte.TIME_REFRESH_LM_LIST());
		cout.cm("Started.");


	};



	// ============================================================================
	// CLIENT RESPONSE LIST
	// ============================================================================
	this.GetNextClientResponseId = function() {
		var next_id = 0;

		for (i = 0; i < self.client_response_list.length; i++) {
			if (self.client_response_list[i].response_id > next_id) {
				next_id = self.client_response_list[i].response_id;
			}
		}	

		next_id++;
		cout.cm("Next client response Id: '" + next_id + "'.");

		return next_id;
	};

	this.PushClientResponse = function(response) {
		var client_response = {
			response_id: self.GetNextClientResponseId(),
			response: response
		};
		self.client_response_list.push(client_response);

		return client_response.response_id;
	};

	this.PopClientResponse = function(response_id) {
		var client_response = null;

		var found = false;
		for (i = 0; ((i < self.client_response_list.length) && (client_response == null)); i++) {
			if (self.client_response_list[i].response_id == response_id) {
				client_response = self.client_response_list[i];
				self.client_response_list.splice(i, 1);
			}
		}

		return client_response;
	};

	// ============================================================================
	// USER REQUESTS
	// ============================================================================

  this.CreateExperiment = function(new_experiment_name) {
		cout.cm("Let's check if this experiment name already exists.");

    experiment_id = -1;
		for (i = 0; ((i < self.experiments_list.length) && (experiment_id == -1)); i++) {
			if (self.experiments_list[i].name == new_experiment_name) {
        experiment_id = self.experiments_list[i].experiment_id;
      }
		}

		if (experiment_id == -1) {
			cout.cm("Let's create the experiment.");
			var experiment_id = self.GetNextExperimentId();
			new_experiment = self.EnlistNewExperiment(experiment_id, new_experiment_name);
      experiment_id = new_experiment.experiment_id;
		}

    return experiment_id;
  };

	/// Description.
	/// @param {res} Description.
	/// @param {new_experiment_id} Description.
	this.RequestCreateExperiment = function(response_id, new_experiment_name) {
    var experiment_id = self.CreateExperiment(new_experiment_name);

    if (experiment_id != -1) {
			self.ResponseRequestOK(response_id, experiment_id);
    } else {
			self.ResponseRequestError(response_id, "This experiment name is already in use.");
    }
	};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + NODE UTIL FUNCTIONS
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  this.MoveNodesByType = function(input_list, output_list, type) {
      for (var i = 0; i < input_list.length; i++) {
          if (input_list[i].type == type) {
              output_list.push(input_list[i]);
              input_list.splice(i, 1);
              i--;
          }
      }
  };

  this.MoveNodesByStyle = function(input_list, output_list, style) {
      for (var i = 0; i < input_list.length; i++) {
          if (input_list[i].style == style) {
              output_list.push(input_list[i]);
              input_list.splice(i, 1);
              i--;
          }
      }
  };

  this.PrintNodes = function(title, nodes) {
    var info = title + ":\n";
    for (var i = 0; i < nodes.length; i++) {
      info += "Type: " + nodes[i].type + ". " +
              "Id: " + nodes[i].id + ". " +
              "Value: " + nodes[i].value + ". " +
              "Inputs: " + nodes[i].num_inputs_satisfied + "/" + nodes[i].node_type_inputs + ".\n";
    }
		cout.cm(info);
  };

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + ARRAY UTIL FUNCTIONS
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  this.FindArrayElementById = function(array, id) {
      var ret = null;
      for (var i = 0; ((i < array.length) && (ret == null)); i++) {
          if (array[i].id == id) {
              ret = array[i];
          }
      }
      return ret;
  };

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + STRING UTIL FUNCTIONS
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  this.TextToVarName = function(text) {
    var var_name = "";
    
    for (var i = 0; i < text.length; i++) {
      if ((text[i] == ' ') || (text[i] == '\t') || (text[i] == '\n')) {
        var_name += '_';
      } else {
        if (
            ((text[i] >= 'a') && (text[i] <= 'z')) ||
            ((text[i] >= 'A') && (text[i] <= 'Z')) ||
            ((text[i] >= '0') && (text[i] <= '1')) ||
             (text[i] == '}') ||
             (text[i] == '{')
        ) {
          var_name += text[i];
        }
      }
    }

    var_name = var_name.toLowerCase();

    return var_name;
  };

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + TIME UTIL FUNCTIONS
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  this.GetDate = function() {
    var date = new Date;

    var seconds = date.getSeconds();
    var minutes = date.getMinutes();
    var hour = date.getHours();

    return hour + "_" + minutes + "_" + seconds;
  }


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + PLANNER
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  this.GeneratePipelineCode = function(parent, node, node_types, input_pipeline_vars, output_pipeline_vars) {
    cout.cm("Generating Pipeline Code... (parent="+parent+". node.type=" + node.type + ")\n");

    var result = self.GetFromRepository('PIPELINE', node.type);

    // Add some information that it is not stored in the pipeline
    for (var i = 0; i < result.nodes.length; i++) {
      // Add empty inputs:
      result.nodes[i].inputs = [];

      // Add the type_obj pointer to the node:
      result.nodes[i].temp = { type_obj: null };
      result.nodes[i].temp.type_obj = self.FindArrayElementById(node_types, result.nodes[i].type);

      // Add:
      result.nodes[i].node_type_inputs = result.nodes[i].temp.type_obj.inputs.length;
    }


    // cout.cm("The pipeline has this number of nodes: " + result.nodes.length);

    parent = parent + VAR_INI + self.TextToVarName(node.type) + "/" + node.id + VAR_FIN;
    var code = self.GenerateCodeFromNodeList(parent, result.nodes, node_types, input_pipeline_vars, output_pipeline_vars, true);

    // cout.cm("****** PIPELINE GENERATED CODE ******");
    // cout.cm(JSON.stringify(code));
    // cout.cm("****** ");
    // Replace all "input nodes" by "input variables":
    
    // Replace all "output nodes" by "output variables":

    return code;
  };

  this.GenerateCodeFromNodeList = function(parent, nodes, node_types, input_pipeline_vars, output_pipeline_vars, b_pipeline) {
    cout.cm("Generating code from node list... (parent=" + parent + ")\n");

    var dependecies_list = self.CreateDependenciesList(nodes);
    // self.PrintNodes('Dependencies List', dependecies_list);

    var execution_list = self.CreateExecutionList(dependecies_list);
    // self.PrintNodes('Execution List', execution_list);

    var code = self.GenerateCode(parent, execution_list, nodes, node_types, input_pipeline_vars, output_pipeline_vars, b_pipeline);

    return code;
  };

  var FIRST_EXPERIMENT_CMD = "print --text \"[EXPERIMENT_START]\" --eol";
  var LAST_EXPERIMENT_CMD  = "print --text \"[EXPERIMENT_END]\" --eol";

	/// Description.
	/// @param {res} Description.
	/// @param {experiment} Description.
  this.RequestExecuteExperiment = function(response_id, experiment, dry_run) {
    cout.cm("Request execute experiment... (experiment.name=" + experiment.name + ")\n");

    var experiment_id = self.CreateExperiment(experiment.name);
    if (experiment_id != -1) {
      /*
        Use this when executing more than one experiment at the same time:
        var parent = VAR_INI + self.TextToVarName(experiment.name) + VAR_FIN;
        parent += VAR_INI + self.GetDate() + VAR_FIN;
      */
      var parent = "";

      var code = self.GenerateCodeFromNodeList(parent, experiment.nodes, experiment.node_types, [], [], false);

		  local_manager = self.GetLocalManagerByExperimentId(experiment_id);

		  // If this experiment does not have a local manager assigned to it, it is because this 
		  // is the first experiment command to be lauched. Let's find a free local manager to 
		  // launch this experiment.
		  if (local_manager == null) {
			  local_manager = self.AssignLessUsedLocalManagerToExperiment(experiment_id);
			  self.NotifyRefreshRequired("EXPERIMENTS_LIST", true);
		  }


		  if (local_manager == null) {
			  self.ResponseRequestError(response_id, "The experiment can not be assigned to any local manager.");
      } else {
        // Clear previous log
//        cout.cm("Sending Command to LM: clear");
//        self.SendMsgToLMNetSocket(response_id, local_manager, "RUN", experiment_id, "clear", null);


        // Adding extra commands:
        code.unshift({parent:null,node_id:null,code:FIRST_EXPERIMENT_CMD});                             // 6th command
        code.unshift({parent:null,node_id:null,code:"constant --name FALSE --by 0"});                   // 4rd command
        code.unshift({parent:null,node_id:null,code:"constant --name TRUE  --by 1"});                   // 3rd command
        code.unshift({parent:null,node_id:null,code:"set-value --to $encoding --eq \"english_bn\""});   // 2nd command
        code.unshift({parent:null,node_id:null,code:"verbose --level debug"});                          // 1st command

        code.push({parent:null,node_id:null,code:LAST_EXPERIMENT_CMD});                                 // Last command

        // Initialize the experiment execution data:
        var experiment = self.GetExperimentById(local_manager.lm_id, experiment_id);
        experiment.exec_data.num_instructions = code.length;
        experiment.exec_data.executed_instructions = 0;
        experiment.exec_data.job_done = 0;

        var all_code = "";

        // Executing commands:
        for (var i = 0; i < code.length; i++) {
            command = code[i].code;

            if (!dry_run) {
                cout.cm("Sending Command to LM: " + command);
                self.SendMsgToLMNetSocket(response_id, local_manager, "RUN", experiment_id, command, null);
                /////////NO: self.SendMessageToWeb("RESULT", {cmd:"this command",result:"this result"});
            } else {
                all_code += "$&nbsp;" + command;
                all_code += "<br />";
            }
        }

        if (dry_run) {
            self.ResponseRequestOK(response_id, all_code);
        }
      }

    } else {
      self.ResponseRequestError(response_id, "CreateExperiment(experiment.name) FAILED: experiment = " + JSON.stringify(experiment));
    }

    // Return the total number of instructions:
    self.ResponseRequestOK(response_id, '{"num_instructions":' + code.length + ',"executed_instructions":0}');
	};


  this.CreateDependenciesList = function(nodes) {
    cout.cm("Creating dependencies list...\n");

    // Create the dependecies_list:
    // It is a list without graphical information.
    // It is a list with connections to output nodes and to input nodes, too.
    var dependecies_list = [];

    // cout.cm(JSON.stringify(nodes));

    for (var i = 0; i < nodes.length; i++) {

        var dependency_node = {
            id: nodes[i].id,
            enabled: nodes[i].enabled,
            type: nodes[i].type,
            value: (nodes[i].value != null)?this.RemoveOrderFromValue(nodes[i].value):"",
            temp: { type_obj: nodes[i].temp.type_obj },
            node_type_inputs: nodes[i].inputs.length,
            inputs: [],
            outputs: nodes[i].outputs,
            num_inputs_satisfied: 0
        };

        dependecies_list.push(dependency_node);
    }

    // Let's inform every dependency node about their inputs:
    // Loop dependency nodes:
    for (var i = 0; i < dependecies_list.length; i++) {
        var dep_node = dependecies_list[i];

        // Loop output connections of every dependency node:
        for (j = 0; j < dep_node.outputs.length; j++) {
            var output = dep_node.outputs[j];

            // Searching all nodes connected to the current output connection:
            for (k = 0; k < output.to.length; k++) {
                var to_node = self.FindArrayElementById(dependecies_list, output.to[k].node_id);

                // This enlisted output node has this current "node" as an input.
                // Let's inform the enlisted output node about it:

                var to_node_input = self.FindArrayElementById(to_node.inputs, output.to[k].input_id); // Get the node input "input_id"

                if (to_node_input == null) {  // It this input is null, lets create it and lets initialize it with one "from" connection
                  var a = {
                    id: output.to[k].input_id,
                    from: [
                      {
                        node_id: dep_node.id,
                        output_id: output.id,
                        type: dep_node.type,
                        name: dep_node.value //!20170217 dep_node.temp.type_obj.outputs[output.id].name
                      }
                    ]
                  };
                  to_node.inputs.push(a);

cout.cm("////////////////// inputs.Push: " + JSON.stringify(a));

                }
                else { // If this input exits then add a new connection to its "from" list:
                  var a = {
                    node_id: dep_node.id,
                    output_id: output.id,
                    type: dep_node.type,
                    name: dep_node.temp.type_obj.outputs[output.id].name
                  };
                  to_node_input.from.push(a);
cout.cm("////////////////// inputs.from.Push: " + JSON.stringify(a));
                }
            }
        }

    }

    // Last retouch: inputs must be ordered by id:
    for (var i = 0; i < dependecies_list.length; i++) {
        var dep_node = dependecies_list[i];
        dep_node.inputs.sort(function(a, b) {
            return (a.id > b.id);
        });
    }

    return dependecies_list;
  };

  this.CreateExecutionList = function(dependecies_list) {
    cout.cm("Creating execution list...\n");

      // Create the execution list:
      // It is a list ordered to be executed
      var execution_list = [];
      var execution_list_updated = true;

      // First, move all "input" nodes from the dependecies_list to the execution_list:
      self.MoveNodesByType(dependecies_list, execution_list, "input");

      // Now, move all data nodes from the dependecies_list to the execution_list:
      self.MoveNodesByStyle(dependecies_list, execution_list, NodeStyle.DATA_NODE);

      while ((dependecies_list.length > 0) && (execution_list_updated == true)) {
          execution_list_updated = false;

          for (var i = 0; i < dependecies_list.length; i++) {
              var node = dependecies_list[i];

              if (node != "output") {
                  node.num_inputs_satisfied = 0;
                  for (j = 0; j < node.inputs.length; j++) {
                      var p = self.FindArrayElementById(execution_list, node.inputs[j].from[0].node_id); //!fixit
                      if (p != null) {
                          node.num_inputs_satisfied++;
                      }
                  }

                  if (node.inputs.length == node.num_inputs_satisfied) {
                      // **** node.inputs.length is the number of inputs with a connection. And,
                      // **** node.num_inputs_satisfied is the number of inputs connected with a node already in the execution list
                      // **** node.node_type_inputs.length is the number of total node inputs (but this is not used here)

                      // move the node from dependencies_list to execution_list:
                      execution_list.push(node);
                      dependecies_list.splice(i, 1); i--;
                      execution_list_updated = true;
                  }
              }
          }
      }

      // Last, move all "output" nodes from the dependecies_list to the execution_list:
      self.MoveNodesByType(dependecies_list, execution_list, "output");

      return execution_list;
  };

  this.GetNodeInputs = function(parent, execution_list, i, input_pipeline_vars, code, node, free_conversion_variables) {
    var ret = [];

    // Loop Inputs definition (we loop this list because it has all input definitions and it has all them in the right order)
    for (var j = 0; j < execution_list[i].temp.type_obj.inputs.length; j++) {
      var this_node_input_id = execution_list[i].temp.type_obj.inputs[j].id;
      var this_node_input_type = execution_list[i].temp.type_obj.inputs[j].type;
      var this_node_id = execution_list[i].id;
      var this_node_type = execution_list[i].temp.type_obj.id;
      var accumulative_input = execution_list[i].temp.type_obj.inputs[j].accumulative;

      // Does this node have this input connected?
      // If it is an accumulative input this input could be connected to more than one node
      var found_at_least_one = false;
      for (var k = 0; k < execution_list[i].inputs.length; k++) {
        if (execution_list[i].inputs[k].id == this_node_input_id) {
          // var connected = self.FindArrayElementById(execution_list[i].inputs, this_node_input_id);
          var one_input = execution_list[i].inputs[k];

          if (one_input != null) { // The input is one_input

            for (var m = 0; m < one_input.from.length; m++) {
              found_at_least_one = true;

              var connected = one_input.from[m];

              var from_type = connected.type; //!fixit
              var from_name = parent + from_type + "_" + connected.node_id + "_" + connected.output_id; //!fixit

              // An "input node" is connected to this node input connection.
              if (from_type == "input") {
                // The "input node" name must be replaced by the "experiment variable". The list "input_pipeline_vars" has the relation between "input names" and "variable names":
                var found = false;
                for (var p = 0; ((p < input_pipeline_vars.length) && (!found)); p++) {
                  if (input_pipeline_vars[p].input_name == from_name) {
                    from_name = input_pipeline_vars[p].var_name;  // Assign the name of the variable
                    from_type = input_pipeline_vars[p].var_type;  // Assign the type of the variable (instead of "input")
                    found = true;
                  }
                }
              }



              // If from and to are not of the same type then a data convertion must be done
              // With these exceptions:
              if ((this_node_type == "Print Data") || (this_node_type == "R Export")) {
                //
              }
              else {
                  if (from_type != this_node_input_type) {
                    // Conversions are treated only in the input side
                    var previous_from_name = from_name;
                    from_name = parent + this_node_input_type + "_in_" + this_node_id + "_" + this_node_input_id + "_" + m; // the from name will be the new created variable
                    
                    code.push({parent:parent,node_id:node.id,code:"dim -n " + from_name + " --as " + this_node_input_type});
                    code.push({parent:parent,node_id:node.id,code:"set-value --to " + from_name + " --eq " + previous_from_name});

                    // And also, it must be created the code for freeing this temporary variable
                    free_conversion_variables.push({parent:parent,node_id:node.id,code:"delete -n " + from_name});
                  }
              }

              ret.push({
                var_name: from_name,
                name:     connected.name
              });
            }
          }
        }
      }

      if (!found_at_least_one) {
        // The input is not connected:
        ret.push({
          var_name: "null",
          name:     "null"
        });
      }
    }

    return ret;
  };

  this.GetNodeOutputs = function(parent, execution_list, i, nodes_list, code, node, output_temporary_variables, output_pipeline_vars) {
    var ret = [];

    // Loop outputs definition (we loop this list because it has all outputs definitions and it has all them in the right order)
    for (var j = 0; j < execution_list[i].temp.type_obj.outputs.length; j++) {
      var this_node_output_id = execution_list[i].temp.type_obj.outputs[j].id;
      var this_node_output_type = execution_list[i].temp.type_obj.outputs[j].type;
      var this_node_id = execution_list[i].id;
      var this_node_type = execution_list[i].type;
      
      // Does this node have this output connected?
      var connected = self.FindArrayElementById(execution_list[i].outputs, this_node_output_id);
      if ((connected != null) && (connected.to[0] != null)) { // The output is connected
        // Calculations & Pipelines can only have one connected for each output . So, to[0].
        var destination_node = self.FindArrayElementById(nodes_list, connected.to[0].node_id);
        var to_type = self.FindArrayElementById(destination_node.temp.type_obj.inputs, connected.to[0].input_id).type;
        var to_name = parent + to_type + "_" + connected.to[0].node_id + "_" + connected.to[0].input_id;  //<<<<
        var to_style = destination_node.temp.type_obj.style;



        var output_node_connected = false;
        // An "output node" is connected from this node output connection.
        if (to_type == "output") {
          // The "output node" name must be replaced by the "experiment variable". The list "output_pipeline_vars" has the relation between "output names" and "variable names":
          for (var p = 0; ((p < output_pipeline_vars.length) && (!output_node_connected)); p++) {
            if (output_pipeline_vars[p].output_name == to_name) {
              to_name = output_pipeline_vars[p].var_name;  // Assign the name of the variable
              to_type = output_pipeline_vars[p].var_type;  // Assign the type of the variable (instead of "output")
              output_node_connected = true;
            }
          }
        } 
//!20170214

        if ((to_style != NodeStyle.DATA_NODE) &&   // If the output is not going to a variable then a variable must be created
           (destination_node.type != "output"))  { // And if the calculation output is not a pipeline output node
          to_name = parent + this_node_type + "_" + this_node_id + "_" + this_node_output_id;
          code.push({parent:parent,node_id:node.id,code:"dim -n " + to_name + " --as " + this_node_output_type});
          // And also, it must be created the code for freeing this temporary variable
          output_temporary_variables.push({node_id:node.id,temp_var:to_name});
          
        } else {
        //code.push({parent:parent,node_id:node.id,code:"print --text \"***" + " to_type="+to_type+" to_style="+to_style+" to_name="+to_name + " this_node_output_id=" + this_node_output_id + " this_node_output_type="+this_node_output_type + "\""});
        }


        // Conversions are treated only in the input side

        // Add the output name
        ret.push({
          var_name: to_name,
          name:     "hola"
        });
      }
      else {
        // The output is not connected:
        ret.push({
          var_name: "null",
          name:     "null"
        });
      }

    }

    return ret;
  };

  this.FromArrayToComaSeparatedString = function(v) {
    var ret = "";

    for (var j = 0; j < v.length; j++) {
      if (j != 0) {
        ret += ",";
      }
      ret += v[j].var_name;
    }

    return ret;
  }

  this.TranslateType = function(type) {
    var ret = type;

    if (type == "foreach_iteration") {
        ret = "int64";
    }
    if (type == "foreach_value") {
        ret = "string";
    }

    return ret;
  }

  // This function gets this string "a/0/b/3/" and it returns "a/0/"
  this.GetParent = function(parent_reference) {
    var pos = 0;
    var ref = parent_reference;

    if (ref != '') {
        for (i = 0; i < 3; i++) {
          if (ref != '') {
            pos = ref.lastIndexOf('/');
            if (pos != -1) {
              ref = ref.substring(0, pos);
            }
          }
        }
        ref += '/';
    }

    return ref;
  }

  // param "input_pipeline_vars": 
  // [
  //   {
  //      "connector_name": "Output File Name",
  //      "var_name":       "experiment_1_14_21_37string_1_0"
  //      "var_type":       "string"
  //   },
  //   {
  //      "connector_name": "BAM files",
  //      "var_name":       "experiment_1_14_21_37string_vector_2_0"
  //      "var_type":       "string"
  //   }
  // ]
  // 
  // param "output_pipeline_vars":
  // [
  //   {
  //      "connector_name": "Filtered Statistics",
  //      "var_name":       "experiment_1_14_21_37text-file_9_0"
  //      "var_type":       "string"
  //   }
  // ]
  this.GenerateCode = function(parent, execution_list, nodes_list, node_types, input_pipeline_vars, output_pipeline_vars, b_pipeline) {
    cout.cm("Generating ngasp code... (parent=" + parent + ")\n");

    var code = [];

    var load_values_set = false;

    var num_open_ifs = 0;


    // We want to add the ".input_name" to the "input_pipeline_vars" and 
    // the ".output_name" to the "output_pipeline_vars":
    // We loop only input and output nodes:

    // ***************************
    // *** FOREACH SOURCE CODE ***
    // ***************************
    var foreach_nodes_found = 0;
    var foreach_vector_name = '';
    var foreach_iterator_name = '';
    var foreach_value_name = '';
    // ***************************

    for (var i = 0; i < execution_list.length; i++) {
        var node = execution_list[i];

        switch(node.temp.type_obj.style) {
            case NodeStyle.INPUT_NODE:
                if ((node.outputs.length > 0) && (node.outputs[0].to.length > 0)) {
                  var input_name = parent + node.type + "_" + node.id + "_0"; // --as " + to_connector.type;
                  for (var j = 0; j < input_pipeline_vars.length; j++) {
                    if (input_pipeline_vars[j].connector_name == node.value) {
                      input_pipeline_vars[j].input_name = input_name;
                      break; // <--------------------------------------------- get out of this loop
                    }
                  }
                } else {
                    // ***************************
                    // *** FOREACH SOURCE CODE ***
                    // ***************************
                    if ((node.type == 'input') && (node.value == 'Foreach')) {
                        foreach_nodes_found++;

                        // Find the variable connected to this the pipeline input:
                        for (var j = 0; j < input_pipeline_vars.length; j++) {
                          if (input_pipeline_vars[j].connector_name == 'Foreach') {
                            foreach_vector_name = input_pipeline_vars[j].var_name;
                            break; // <--------------------------------------------- get out of this loop
                          }
                        }

                        // foreach_vector_name = self.GetParent(parent) + "string_vector_" + node.id + "_0";
                    }                    
                    // ***************************
                }
                break;
            case NodeStyle.OUTPUT_NODE:
                var output_name = parent + node.type + "_" + node.id + "_0";
                for (var j = 0; j < output_pipeline_vars.length; j++) {
                  if (output_pipeline_vars[j].connector_name == node.value) {
                    output_pipeline_vars[j].output_name = output_name;
                    break; // <--------------------------------------------- get out of this loop
                  }
                }
                break;
        };
    }

    // Now we have something like this:
    // input_pipeline_vars: 
    // [
    //   {
    //      "connector_name": "Output File Name",
    //      "var_name":       "experiment_1_14_21_37string_1_0"
    //      "var_type":       "string",
    //      "input_name":     "input_1_0"
    //   },
    //   {
    //      "connector_name": "BAM files",
    //      "var_name":       "experiment_1_14_21_37string_vector_2_0"
    //      "var_type":       "string",
    //      "input_name":     "input_2_0"
    //   }
    // ]
    // output_pipeline_vars: 
    // [
    //   {
    //      "connector_name": "Filtered Statistics",
    //      "var_name":       "experiment_1_14_21_37text-file_9_0"
    //      "var_type":       "string",
    //      "output_name":    "output_1_0"
    //   }
    // ]

    // ***************************
    // *** FOREACH SOURCE CODE ***
    // ***************************
    if (b_pipeline == true) {

        for (var i = 0; i < execution_list.length; i++) {
            var node = execution_list[i];

            if ((node.type == 'foreach_iteration') || (node.type == 'foreach_value')) {  // This is the creation of the loop variables (value & iteration number):
                switch(node.temp.type_obj.style) {
                    case NodeStyle.DATA_NODE:
                        code.push({parent:parent,node_id:node.id,code:"dim -n " + parent + node.type + "_" + node.id + "_0 --as " + self.TranslateType(node.type)});
                        code.push({parent:parent,node_id:node.id,code:"set-value --to " + parent + node.type + "_" + node.id + "_0 --eq \"" + node.value + "\""});
                        // code += EOL;
                        break;
                };

                if (node.type == 'foreach_iteration') {
                    foreach_nodes_found++;
                    foreach_iterator_name = parent + node.type + "_" + node.id + "_0";
                }

                if (node.type == 'foreach_value') {
                    foreach_nodes_found++;
                    foreach_value_name = parent + node.type + "_" + node.id + "_0";
                }
            }

            if (foreach_nodes_found == 3) {
                // START OF LOOP
                if (foreach_vector_name != "") { // Pipeline without a vector to interate. This pipeline will be executed only one time.
                    code.push({parent:parent,node_id:node.id,code:"for --data " + foreach_vector_name + " --ite " + foreach_iterator_name + " --from 0 --to " + foreach_vector_name + ".reg_length --inc 1"});
                    code.push({parent:parent,node_id:node.id,code:"set-value --to " + foreach_value_name + " --eq " + foreach_vector_name + "[" + foreach_iterator_name + "]"});
                    code.push({parent:parent,node_id:node.id,code:"print -n " + foreach_iterator_name + " --text \"iteration: \" --mode value --eol"});
                    code.push({parent:parent,node_id:node.id,code:"print -n " + foreach_value_name + " --text \"value: \" --mode value  --eol"});
                }

                foreach_nodes_found = 0;
            }
        }
    }
    // ***************************

    // All pipeline DATA variables are created here. Just after the "for". They will be created at the beginning of every iteration and they will be destroy at the end of every iteration, too.

    for (var i = 0; i < execution_list.length; i++) {
        var node = execution_list[i];

        if (!((node.type == 'foreach_iteration') || (node.type == 'foreach_value'))) {  // This If prevents from creating the loop variables again (value & iteration number):
            switch(node.temp.type_obj.style) {
                case NodeStyle.DATA_NODE:
                    code.push({parent:parent,node_id:node.id,code:"dim -n " + parent + node.type + "_" + node.id + "_0 --as " + self.TranslateType(node.type)});
                    code.push({parent:parent,node_id:node.id,code:"set-value --to " + parent + node.type + "_" + node.id + "_0 --eq \"" + node.value + "\""});
                    // code += EOL;
                    break;
            };
        }
    }



    var output_temporary_variables = [];

    for (var i = 0; i < execution_list.length; i++) {
        var node = execution_list[i];

        var free_conversion_variables = [];

        switch(node.temp.type_obj.style) {
            case NodeStyle.CALCULATION_NODE:
              //--------------------------------------------------------------
              // INPUTS
              //--------------------------------------------------------------
              var inputs = self.FromArrayToComaSeparatedString(self.GetNodeInputs(parent, execution_list, i, input_pipeline_vars, code, node, free_conversion_variables));

              //--------------------------------------------------------------

              //--------------------------------------------------------------
              // OUTPUTS
              //--------------------------------------------------------------
              var outputs = self.FromArrayToComaSeparatedString(self.GetNodeOutputs(parent, execution_list, i, nodes_list, code, node, output_temporary_variables, output_pipeline_vars));
              //--------------------------------------------------------------

              if (foreach_iterator_name == "") {
                  code.push({parent:parent,node_id:node.id,code:"set-value --to $iteration_number --eq \"-1\"" });
                  code.push({parent:parent,node_id:node.id,code:"set-value --to $iteration_value --eq \"\"" });
              } else {
                  code.push({parent:parent,node_id:node.id,code:"set-value --to $iteration_number --eq " + foreach_iterator_name });
                  code.push({parent:parent,node_id:node.id,code:"set-value --to $iteration_value --eq " + foreach_value_name });
              }

              code.push({parent:parent,node_id:node.id,code:"calc -n " + parent + node.type + "_" + node.id + " --as " + node.type});
              code.push({parent:parent,node_id:node.id,code:"set-value --to " + parent + node.type + "_" + node.id + ".inputs --eq \"" + inputs + "\""});
              code.push({parent:parent,node_id:node.id,code:"set-value --to " + parent + node.type + "_" + node.id + ".outputs --eq \"" + outputs + "\""});

              if (!node.enabled) {
                code.push({parent:parent,node_id:-1,code:"dry-run -x true"});
              }
              code.push({parent:parent,node_id:node.id,code:"run-calculation -n " + parent + node.type + "_" + node.id});
              code.push({parent:parent,node_id:node.id,code:"delete -n " + parent + node.type + "_" + node.id});
              if (!node.enabled) {
                code.push({parent:parent,node_id:-1,code:"dry-run -x false"});
              }

              for (var fcv=0; fcv < free_conversion_variables.length; fcv++) {
                code.push(free_conversion_variables[fcv]);
              }

              code.push({parent:parent,node_id:node.id,code:"if --ref $result --eq 0"});
              num_open_ifs++;


//              code.push({parent:parent,node_id:node.id,code:"if --ref $result --ne 0"}); // 0 is RESULT_OK
//              code.push({parent:parent,node_id:node.id,code:"  exit"});
//              code.push({parent:parent,node_id:node.id,code:"endif"});

              break;
            case NodeStyle.OUTPUT_NODE:
              break;
            case NodeStyle.GRAPH_NODE:
                //--------------------------------------------------------------
                // INPUTS
                //--------------------------------------------------------------
                var inputs = self.GetNodeInputs(parent, execution_list, i, input_pipeline_vars, code, node, free_conversion_variables);
                //--------------------------------------------------------------

                if ((node.type == "chart")||(node.type == "R Export")||(node.type == "Print Data")) {
                  for (var j = 0; j < inputs.length; j++) {
                    if (inputs[j] != "null") {
                      code.push({parent:parent,node_id:node.id,code:"print -n " + inputs[j].var_name + " --mode json --text \"node|" + node.id + "|" + node.type + "|" + j + "|" + inputs[j].name + "||\" --eol"});
                    }
                  }
                }

                if (node.type == "boxplot") {
                  for (var j = 0; j < inputs.length; j++) {
                    if (inputs[j] != "null") {
                      var calc_name = parent + "calc-boxplot-values_" + node.id;
                      var v1 = calc_name + "_0";
                      var v2 = calc_name + "_1";
                      var v3 = calc_name + "_2";
                      var v4 = calc_name + "_3";
                      var v5 = calc_name + "_4";
                      var v6 = calc_name + "_5";

                      code.push({parent:parent,node_id:node.id,code:"dim -n " + v1 + " --as double"});
                      code.push({parent:parent,node_id:node.id,code:"dim -n " + v2 + " --as double"});
                      code.push({parent:parent,node_id:node.id,code:"dim -n " + v3 + " --as double"});
                      code.push({parent:parent,node_id:node.id,code:"dim -n " + v4 + " --as double"});
                      code.push({parent:parent,node_id:node.id,code:"dim -n " + v5 + " --as double"});
                      code.push({parent:parent,node_id:node.id,code:"dim -n " + v6 + " --as double_vector"});

                      code.push({parent:parent,node_id:node.id,code:"calc -n " + calc_name + " --as calc-boxplot-values"});
                      code.push({parent:parent,node_id:node.id,code:"set-value --to " + calc_name + ".inputs --eq \"" + inputs[j].var_name + "\""});
                      code.push({parent:parent,node_id:node.id,code:"set-value --to " + calc_name + ".outputs --eq \"" + v1 + "," + v2 + "," + v3 + "," + v4 + "," + v5 + "," + v6 + "\""});
                      code.push({parent:parent,node_id:node.id,code:"run-calculation -n " + calc_name});
                      code.push({parent:parent,node_id:node.id,code:"print -n " + v1 + " --mode json --text \"node|" + node.id + "|" + node.type + "|" + j + "|" + inputs[j].name + "|Q1|\" --eol"});
                      code.push({parent:parent,node_id:node.id,code:"print -n " + v2 + " --mode json --text \"node|" + node.id + "|" + node.type + "|" + j + "|" + inputs[j].name + "|Q2|\" --eol"});
                      code.push({parent:parent,node_id:node.id,code:"print -n " + v3 + " --mode json --text \"node|" + node.id + "|" + node.type + "|" + j + "|" + inputs[j].name + "|Q3|\" --eol"});
                      code.push({parent:parent,node_id:node.id,code:"print -n " + v4 + " --mode json --text \"node|" + node.id + "|" + node.type + "|" + j + "|" + inputs[j].name + "|Min|\" --eol"});
                      code.push({parent:parent,node_id:node.id,code:"print -n " + v5 + " --mode json --text \"node|" + node.id + "|" + node.type + "|" + j + "|" + inputs[j].name + "|Max|\" --eol"});
                      code.push({parent:parent,node_id:node.id,code:"print -n " + v6 + " --mode json --text \"node|" + node.id + "|" + node.type + "|" + j + "|" + inputs[j].name + "|Outliers|\" --eol"});

                      code.push({parent:parent,node_id:node.id,code:"delete -n " + calc_name});
                      code.push({parent:parent,node_id:node.id,code:"delete -n " + v1});
                      code.push({parent:parent,node_id:node.id,code:"delete -n " + v2});
                      code.push({parent:parent,node_id:node.id,code:"delete -n " + v3});
                      code.push({parent:parent,node_id:node.id,code:"delete -n " + v4});
                      code.push({parent:parent,node_id:node.id,code:"delete -n " + v5});
                      code.push({parent:parent,node_id:node.id,code:"delete -n " + v6});
                    }
                  }
                }
                break;
            case NodeStyle.PIPELINE_NODE:
              var the_input_pipeline_vars = [];
              var the_output_pipeline_vars = [];

              // Let's create the folowing tables:
              // "the_input_pipeline_vars": 
              // [
              //   {
              //      "connector_name": "Output File Name",
              //      "var_name":       "experiment_1_14_21_37string_1_0"
              //      "var_type":       "string"
              //   },
              //   {
              //      "connector_name": "BAM files",
              //      "var_name":       "experiment_1_14_21_37string_vector_2_0"
              //      "var_type":       "string"
              //   }
              // ]
              // 
              // "the_output_pipeline_vars":
              // [
              //   {
              //      "connector_name": "Filtered Statistics",
              //      "var_name":       "experiment_1_14_21_37text-file_9_0"
              //      "var_type":       "string"
              //   }
              // ]

              // Get a list of those variables that are connected as inputs of the pipeline node:
              for (var s = 0; s < node.inputs.length; s++) {
                var connector = self.FindArrayElementById(node.temp.type_obj.inputs, node.inputs[s].id);
                
                if ((connector != null) && (node.inputs[s] != null) && (node.inputs[s].from[0] != null)) {

                    if (node.inputs[s].from[0].type == "input") {
                      // This would be wrong for the "the_input_pipeline_vars":
                      //   {
                      //      "connector_name": "Output File Name",
                      //      "var_name":       "input_1_0"
                      //      "var_type":       "input"
                      //   }
                      // The input must be replaced by the input variable of the parent.
                      for(var c = 0; c < input_pipeline_vars.length; c++) {

//console.log("+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*");
//console.log(JSON.stringify(input_pipeline_vars[c]));
//console.log(JSON.stringify(node.inputs[s].from[0]));
                          if (node.inputs[s].from[0].name == input_pipeline_vars[c].connector_name) {
//console.log("in");
                            the_input_pipeline_vars.push({
                              var_name: input_pipeline_vars[c].var_name,
                              var_type: input_pipeline_vars[c].var_type,
                              connector_name: connector.name
                            });
                          }
                      }
//console.log("+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*");

                    }
                    else {
                        // The input node can not have a input has an input variable of type DATA
                        the_input_pipeline_vars.push({
                          var_name: parent + node.inputs[s].from[0].type + "_" + node.inputs[s].from[0].node_id + "_0", //!fixit
                          var_type: node.inputs[s].from[0].type, //!fixit
                          connector_name: connector.name
                        });
                    }

                }
              }

              // Get a list of those variables that are connected as outputs of the pipeline node:
              for (var s = 0; s < node.outputs.length; s++) {
                var connector = self.FindArrayElementById(node.temp.type_obj.outputs, node.outputs[s].id);
                if ((connector != null) && (node.outputs[s] != null) && (node.outputs[s].to[0] != null)) {
//console.log("+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*");
//console.log(JSON.stringify(node.outputs[s].to[0]));
                    var connected_to = self.FindArrayElementById(execution_list, node.outputs[s].to[0].node_id);
//console.log(JSON.stringify(connected_to));
//console.log("+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*");

                    if (connected_to.type == "output") {
                      // This would be wrong for the "the_output_pipeline_vars":
                      //   {
                      //      "connector_name": "Filtered Statistics",
                      //      "var_name":       "output_1_0"
                      //      "var_type":       "output"
                      //   }
                      // The output must be replaced by the output variable of the parent.
                      for(var c = 0; c < output_pipeline_vars.length; c++) {
//console.log("+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*");
//console.log(JSON.stringify(output_pipeline_vars[c]));
//console.log(JSON.stringify(node.outputs[s].to[0]));

                          if (connected_to.value == output_pipeline_vars[c].connector_name) {
//console.log("in");
                            the_output_pipeline_vars.push({
                              var_name: output_pipeline_vars[c].var_name,
                              var_type: output_pipeline_vars[c].var_type,
                              connector_name: connector.name
                            });
                          }
//console.log("+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*");
                      }
                    }
                    else {
                        the_output_pipeline_vars.push({
                          var_name: parent + connected_to.type + "_" + node.outputs[s].to[0].node_id + "_" + node.outputs[s].to[0].input_id,
                          var_type: connected_to.type, //node.outputs[s].to[0].node_id.type,
                          connector_name: connector.name
                        });
                    }

                }
              }

              var pipeline_code = self.GeneratePipelineCode(parent, node, node_types, the_input_pipeline_vars, the_output_pipeline_vars);

              for (var pc=0; pc < pipeline_code.length; pc++) {
                code.push(pipeline_code[pc]);
              }

              break;
        };
    }


    for (var i = 0; i < num_open_ifs; i++) {
      code.push({parent:parent,node_id:node.id,code:"endif"});
    }
    num_open_ifs = 0;

//! *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
// Accumulate iteration results into matrices
//! *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
    if (b_pipeline == true) {
        for (var i = 0; i < execution_list.length; i++) {
            var node = execution_list[i];

            switch(node.temp.type_obj.style) {
                case NodeStyle.OUTPUT_NODE:
                    // Find out the "node" that is connected to this "output node".
                    // This node will contain the iteration result
                    var output_connected_to = '';
                    if ((node.inputs.length > 0) && (node.inputs[0].from.length > 0)) {
                        output_connected_to = parent + node.inputs[0].from[0].type + "_" + node.inputs[0].from[0].node_id + "_0"; //!fixit

                        // Find the output matrix variable where the result must be accumulated
                        var output_matrix_name = '';
                        for(var j = 0; j < output_pipeline_vars.length; j++) {
                            if (output_pipeline_vars[j].connector_name == node.value) {
                                output_matrix_name = output_pipeline_vars[j].var_name;
                            }
                        }
                        if ( output_matrix_name.indexOf("_file") == -1) { // If the pipeline output is not a file.
                            // The user do not have to set a matappend at the end of the pipeline. This matappend is set here automatically
                            code.push({parent:parent,node_id:node.id,code:"matappend --to  " + output_matrix_name + " --add " + output_connected_to + " --index " + foreach_iterator_name});
                            code.push({parent:parent,node_id:node.id,code:"print -n  " + output_matrix_name + " --mode value --eol"});
                        } else {
                            // Files are not concatenated automatically. The user must set a concatenate files calculator at the end of the pipeline
                        }
                    }
                    break;
            };
        }
    }
//! *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

    // Remove all output temporary variables created
    for (var i = 0; i < output_temporary_variables.length; i++) {
      code.push({parent:parent,node_id:output_temporary_variables[i].node_id,code:"delete -n " + output_temporary_variables[i].temp_var});
    }

//    if ((input_pipeline_vars.length == 0) && (output_pipeline_vars.length == 0)) {
      // This is not a pipeline. This is the experiment. So, the DATA_NODEs won't be deleted.
//    } else {

    // ***************************
    // *** FOREACH SOURCE CODE ***
    // ***************************
    // END OF LOOP
    if (b_pipeline == true) {
        // this generates something like
        //    ... append pipeline outputs
        //    del -n foreach_variable
        //    del -n foreach_variable
        //   end -for
        //   ... copy pipeline output variables
        //   del -n other_variables
        //   del -n other_variables


        for (var j = 0; j < 2; j++) {
            for (var i = 0; i < execution_list.length; i++) {
                var node = execution_list[i];

                if (node.temp.type_obj.style == NodeStyle.DATA_NODE) {
                    var var_name = parent + node.type + "_" + node.id + "_0";

                    if (((j == 0) && (var_name.indexOf('/foreach_') == -1)) ||
                        ((j == 1) && (var_name.indexOf('/foreach_') != -1))) {
                        code.push({parent:parent,node_id:node.id,code:"delete -n " + var_name});
                    }
                }
            }
            if (j == 0) {
                if (foreach_vector_name != "") { // If it is "" is because the pipeline has no vector to iterate. It has to be executed only one time and it has not a "for"
                    code.push({parent:parent,node_id:-1,code:"end-for"});
                }
            }
        }
    }
    // ***************************


    return code;
  };
/*
  // *************************************************************************
  // YAML FORMAT
  // *************************************************************************
  function GenerateCode(execution_list) {
      var code = "";
      var variables = "";
      var calculations = "";

      var load_values_set = false;

      for (var i = 0; i < execution_list.length; i++) {
          var node = execution_list[i];

          switch(node.temp.type_obj.style) {
              case $scope.NodeStyle.INPUT_NODE:
                  // The first node connected to the input is used to know the input type:
                  var to_node = arrays.FindArrayElementById(nodes_list, node.outputs[0].to[0].node_id);
                  var to_node_type = arrays.FindArrayElementById(node_types, to_node.type);
                  var to_connector = arrays.FindArrayElementById(to_node_type.inputs, node.outputs[0].to[0].input_id);

                  variables += "&nbsp;&nbsp;&nbsp;&nbsp;- name: " + node.type + "_" + node.id + "_0<br />";
                  variables += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;as: " + to_connector.type + EOL;
                  variables += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;value: " + EOL;
                  variables += EOL;
                  break;
              case $scope.NodeStyle.CALCULATION_NODE:
                  var inputs = "";
                  for (var j = 0; j < execution_list[i].inputs.length; j++) {
                      var input_var = execution_list[i].inputs[j];
                      inputs += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- " + input_var.from_type + "_" + input_var.from_node_id + "_" + input_var.from_output_id + EOL;
                  }

                  var outputs = "";
                  for (var j = 0; j < node.temp.type_obj.outputs.length; j++) {
                      var output_var = node.temp.type_obj.outputs[j];
                      outputs += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- " + output_var.name + "_" + node.id + "_" + output_var.id + EOL;
                  }

                  calculations += "&nbsp;&nbsp;&nbsp;&nbsp;- name: " + node.type + "_" + node.id + EOL;
                  calculations += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;type: " + node.type + EOL;
                  calculations += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;inputs:<br />";
                  calculations += inputs;
                  calculations += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;outputs:<br />";
                  calculations += outputs;
                  calculations += EOL;
                  break;
              case $scope.NodeStyle.OUTPUT_NODE:
                  // code += "print --json -n " + node.value + "_" + node.inputs[0].from_node_id + "_" + node.inputs[0].from_output_id + EOL;
                  break;
              case $scope.NodeStyle.DATA_NODE:
                  variables += "&nbsp;&nbsp;&nbsp;&nbsp;- name: " + node.type + "_" + node.id + "_0<br />";
                  variables += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;as: " + node.type + EOL;
                  variables += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;value: " + node.value + EOL;
                  variables += EOL;
                  break;
              case $scope.NodeStyle.GRAPH_NODE:
                  break;
              case $scope.NodeStyle.PIPELINE_NODE:
                  //code += "call pipeline<br />";
                  //code += EOL;
                  break;
          };
      }

      code += "%YAML 1.2<br />";
      code += EOL;
      code += "# Do not modify this file because it was generated automatically<br />";
      code += EOL;
      code += "# ==============================================================================<br />";
      code += "# ngaSP Pipeline Properties <br />";
      code += "# ==============================================================================<br />";
      code += "# name        : <br />";
      code += "# description :<br />";
      code += "# date        : 17 Nov, 2015.<br />";
      code += "# ==============================================================================<br />";
      code += EOL;
      code += "include: tests/pipelines/yaml/constants.yaml<br />";
      code += EOL;
      code += "variables:<br />";
      code += variables;
      code += "experiment: load<br />";
      code += EOL;
      code += "calculations:<br />";
      code += calculations;

      $scope.console = code;
  };
*/



  this.CheckName = function(name, type) {
    var exists = false;

    var path;

    if (type == 'PIPELINE') {
      path = REPO_PIPELINES_PATH;
    }
    if (type == 'EXPERIMENT') {
      path = REPO_EXPERIMENTS_PATH;
    }

    var files = fs.readdirSync(path);
    for(var i in files) {
      if (!exists) {
        exists = (files[i] == (name + ".json"));
      }
    }

    return exists;
  };

  this.GetFromRepository = function(type, id) {
    cout.cm("Geting from repository... (type=" + type + ", id=" + id + ")\n");

    var result = {nodes: []};

    var path;

    if (type == 'PIPELINE') {
      path = REPO_PIPELINES_PATH;
    }
    if (type == 'EXPERIMENT') {
      path = REPO_EXPERIMENTS_PATH;
    }

    if (id == 'LIST') {
      if (type == 'PIPELINE') {
        result = {pipelines:[]};
        // loop files
        var files = fs.readdirSync(path);
        for(var i in files) {
          var text = fs.readFileSync(path + "/" + files[i], 'utf8');
          var one_pipeline = JSON.parse(text);
          var one_interface_with_id = one_pipeline.interface;
          one_interface_with_id.id = one_pipeline.properties.name;
          one_interface_with_id.properties = one_pipeline.properties;

          result.pipelines.push(one_interface_with_id);
        }
      }
      if (type == 'EXPERIMENT') {
        result = {experiments:[]};
        // loop files
        var files = fs.readdirSync(path);
        for(var i in files) {
          var extension_pos = files[i].lastIndexOf(".");
          if (extension_pos != -1) {
            result.experiments.push({name:files[i].substring(0, extension_pos)});
          }
        }
      }
    }
    else {
      path += id;
      path += ".json";

      var text = fs.readFileSync(path, 'utf8');
      result = JSON.parse(text);
    }

    return result;
  };

  this.SetToRepository = function(type, id, data) {
    var ret = true;

    cout.cm("SetToRepository...\n");

    var path;

    if (type == 'PIPELINE') {
      path = REPO_PIPELINES_PATH;
    }
    if (type == 'EXPERIMENT') {
      path = REPO_EXPERIMENTS_PATH;
    }

    path += id;
    path += ".json";

    var data_str = JSON.stringify(data);

    try {
      fs.writeFileSync(path, data_str, 'utf8');
    } catch (e) {
      ret = false;
    }

    return ret;
  };


  this.RequestCheckExperimentName = function(response_id, name) {
    cout.cm("RequestCheckExperimentName...\n");

    var result = self.CheckName(name, 'EXPERIMENT');
    self.ResponseRequestOK(response_id, result);
  };

  this.RequestCheckPipelineName = function(response_id, name) {
    cout.cm("RequestCheckPipelineName...\n");

    var result = self.CheckName(name, 'PIPELINE');
    self.ResponseRequestOK(response_id, result);
  };

  this.RequestStoredPipelinesList = function(response_id) {
    cout.cm("RequestStoredPipelinesList...\n");

    var result = self.GetFromRepository('PIPELINE', 'LIST');
    self.ResponseRequestOK(response_id, result.pipelines);
  };

  this.RequestPipeline = function(response_id, id) {
    cout.cm("RequestPipeline... (id=" + id + ")\n");

    var result = self.GetFromRepository('PIPELINE', id);
    self.ResponseRequestOK(response_id, result);
  };

  this.RequestStoredExperimentsList = function(response_id) {
    cout.cm("RequestStoredExperimentsList...\n");

    var result = self.GetFromRepository('EXPERIMENT', 'LIST');
    self.ResponseRequestOK(response_id, result.experiments);
  };

  this.RequestExperiment = function(response_id, id) {
    cout.cm("RequestExperiment... (id=" + id + ")\n");

    var result = self.GetFromRepository('EXPERIMENT', id);
    self.ResponseRequestOK(response_id, result);
  };

  this.RequestStoreExperiment = function(response_id, id, data) {
    cout.cm("RequestStoreExperiment... (id=" + id + ")\n");

    if (self.SetToRepository('EXPERIMENT', id, data) == true) {
      self.ResponseRequestOK(response_id, null);
    } else {
      self.ResponseRequestError(response_id, null);
    }
  };

  this.RequestStorePipeline = function(response_id, id, data) {
    cout.cm("RequestStorePipeline... (id=" + id + ")\n");

    if (self.SetToRepository('PIPELINE', id, data) == true) {
      self.ResponseRequestOK(response_id, null);
    } else {
      self.ResponseRequestError(response_id, null);
    }
  };

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	/// Description.
	/// @param {res} Description.
	/// @param {experiment_id} Description.
	/// @param {cmd} Description.
	this.RequestExecuteCommand = function(response_id, experiment_id, cmd) {
		local_manager = self.GetLocalManagerByExperimentId(experiment_id);

		// If this experiment does not have a local manager assigned to it, it is because this 
		// is the first experiment command to be lauched. Let's find a free local manager to 
		// launch this experiment.
		if (local_manager == null) {
			local_manager = self.AssignLessUsedLocalManagerToExperiment(experiment_id);
			self.NotifyRefreshRequired("EXPERIMENTS_LIST", true);
		}

		if (local_manager != null) {
      // When executed, the CM will receive a "RUN" response. Then, the CM will
      // send a broadcast message to web users asking them for getting their output.
      // The user session could have been closed several times until the experiment is done.
      // If the user session is closed now then the user will have to ask for the
      // experiment result later.
      // So, the response_id must be null.
			self.SendMsgToLMNetSocket(null, local_manager, "RUN", experiment_id, cmd, null);

      // It means that the instrucction has been sent correctly to be executed.
      // The response_id is used only once.
      self.ResponseRequestOK(response_id, "OK");
		} else {
      // The experiment can not be assigned to any local manager.
      // It means that the instrucction could not be sent to be executed.
      // The response_id is used only once.
      self.ResponseRequestOK(response_id, "KO");
		}
	};

	/// Description.
	/// @param {res} Description.
	/// @param {experiment_id} Description.
	this.RequestExperimentOutput = function(response_id, experiment_id) {
		cout.cm(string_table.USER_REQUEST_EXPERIMENT_OUTPUT() + experiment_id + ".");

		local_manager = self.GetLocalManagerByExperimentId(experiment_id);

		if (local_manager != null) {
			self.SendMsgToLMNetSocket(response_id, local_manager, "GET_EXPERIMENT_RESULT", experiment_id, null, null);
		} else {
			self.ResponseRequestError(response_id, "Local manager not found.");
		}
	};


	/// Description.
	/// @param {res} Description.
	/// @param {experiment_id} Description.
	this.RequestCleanExperimentOutput = function(response_id, experiment_id) {
		local_manager = self.GetLocalManagerByExperimentId(experiment_id);

		if (local_manager != null) {
			self.SendMsgToLMNetSocket(response_id, local_manager, "CLEAN_EXPERIMENT_RESULT", experiment_id, null, null);
		}
	};

	/// Description.
	/// @param {res} Description.
	/// @param {experiment_id} Description.
	this.RequestRemoveExperiment = function(response_id, experiment_id) {
		local_manager = self.GetLocalManagerByExperimentId(experiment_id);

		if (local_manager != null) {
      self.RemoveExperiment(experiment_id);
			self.SendMsgToLMNetSocket(response_id, local_manager, "CLOSE_EXPERIMENT", experiment_id, null, null);
		}
	};

	/// This functions sends the "local managers list" to the web in its current status.
	/// @param {res} Description.
	this.RequestLocalManagersList = function(response_id) {
		cout.cm("Getting the local managers list...");

		var exported_list = self.ExportLocalManagersList();

		self.ResponseRequestOK(response_id, exported_list);
	};

	/// This functions sends the "experiments list" to the web in its current status.
	/// @param {res} Description.
	this.RequestExperimentsList = function(response_id) {
		cout.cm("Getting the experiments list...");

		var exported_list = self.ExportExperimentsList();

		self.ResponseRequestOK(response_id, exported_list);
	};

    /// This functions sends the "clients list" to the web.
    this.RequestClientsList = function(response_id) {
		cout.cm("Getting the clients list...");

        var exported_list = self.ExportClientsList();

		self.ResponseRequestOK(response_id, exported_list);
    };

    /// This functions sends the "calculations list" to the web.
    this.RequestCalculationsList = function(response_id) {
		cout.cm("Getting the calculations list...");

        var local_manager = self.GetFirstFreeLocalManager();

        if (local_manager != null) {
            self.SendMsgToLMNetSocket(response_id, local_manager, "CALCULATIONS_LIST", null, null, null);
        }
    };

    /// This functions sends the "commands list" to the web.
    this.RequestCommandsList = function(response_id) {
		cout.cm("Getting the commands list...");

        var local_manager = self.GetFirstFreeLocalManager();

        if (local_manager != null) {
            self.SendMsgToLMNetSocket(response_id, local_manager, "COMMANDS_LIST", null, null, null);
        }
    };

    /// This functions sends the "data types list" to the web.
    this.RequestDataTypesList = function(response_id) {
		cout.cm("Getting the data types list...");

        var local_manager = self.GetFirstFreeLocalManager();

        if (local_manager != null) {
            self.SendMsgToLMNetSocket(response_id, local_manager, "DATA_TYPES_LIST", null, null, null);
        }
    };

    /// This functions sends all "data manager variables" to the web.
    this.RequestDataManagerVariables = function(response_id, experiment_id) {
		cout.cm("Getting all data manager variables...");

        local_manager = self.GetLocalManagerByExperimentId(experiment_id);

		    if (local_manager != null) {
          self.SendMsgToLMNetSocket(response_id, local_manager, "DATA_MANAGER_VARIABLES", experiment_id, null, null);
		    }
    };

	/// This function send the close signal to every local manager.
	/// @param {res} Description.
	/// @param {server} Description.
	this.RequestCloseServer = function(response_id, server) {
		// Clear active intervals:
		cout.cm("Stopping the interval for cheking all local managers status...");
		clearInterval(interval_check_LMs_status);

		cout.cm("Sending the close signal to every LM...");

		for (i = 0; i < self.local_managers_list.length; i++) {
			self.SendMsgToLMNetSocket(response_id, self.local_managers_list[i], "CLOSE_LM", null, null, null);
		}

		cout.cm("Wait all LM to be closed...");

		// Wait all LM to be closed
		var _flagCheck = setInterval(function() {
			any_lm_open = false;

			for (i = 0; ((i < self.local_managers_list.length) && (any_lm_open == false)); i++) {
				if (self.local_managers_list[i].status == "OPEN") {
					any_lm_open = true;
				}
			}

			if(any_lm_open == false) {
				clearInterval(_flagCheck);
				cout.cm("All LM are closed.");
				cout.cm("Node: Server closed.");
				server.close();
			}

		}, 100); // interval set at 1000 milliseconds (= 1 second)

		self.ResponseRequestOK(response_id, "OK");
	};

	// ============================================================================
	// COMMUNICATION METHODS
	// (PRIVATE METHODS)
	// ============================================================================

	/// Description.
	/// @param {local_manager} Description.
	/// @param {data} Description.
	this.SendMsgToLMNetSocket = function(response_id, local_manager, command, experiment_id, cmd, result) {
		if ((local_manager.status == "OPEN") || (local_manager.status == "...")) {
			var to = "LM " + local_manager.lm_id;

			var message = {
				command: command,
				data: {
					lm_id: local_manager.lm_id,
					response_id: response_id,
					cmd: cmd,
					experiment_id: experiment_id,
					result: result
				}
			};

			cout.cmSend(to, JSON.stringify(message));

      local_manager.sock.write(JSON.stringify(message)+cte.EOT());
		} else {
			cout.cm("(1) I can not send the message to the local manager because it is closed.");
			self.ResponseRequestError(response_id, "(1) I can not send the message to the local manager because it is closed.");
		}
	};

	/// CM answers to a previous user request.
	/// @param {result} Description.
	/// @param {data} Description.
	this.ResponseRequestOK = function(response_id, data) {
		var client_response = self.PopClientResponse(response_id);  // one usage only
		if ((client_response != null) && (client_response.response != null)) {
			var message = {
				data: data,
			};

			cout.cmSend("WEB", "Response OK: " + JSON.stringify(message));
			client_response.response.send(message);	
		} else {
			cout.cm("(2) I can not send the message to the web page because the client_response is null.");
		}
	};

	this.ResponseRequestError = function(response_id, data) {
		var client_response = self.PopClientResponse(response_id);  // one usage only
		if ((client_response != null) && (client_response.response != null)) {
			var message = {
				data: data,
			};

			cout.cmSend("WEB", "Response Error: " + JSON.stringify(message));
			client_response.response.status(500).send(message);	
		} else {
			cout.cm("(3) I can not send the message to the web page because the client_response is null.");
		}
	}

	/// CM Initiate the conversation.
	/// @param {event} Description.
	/// @param {data} Description.
	this.SendMessageToWeb = function(event, data, do_broadcast) {
		if (self.client_socket != null) {
			var message = {
				command: event,
				data: data,
			};

			cout.cmSend("WEB", "event: " + event + ". message: " + message);
			self.client_socket.emit(event, message);

      if(do_broadcast) {
        self.client_socket.broadcast.emit(event, message);
      }
/*
            // These are those events that must be sent to all clients:
            // --------------------------------------------------------
            if ((event == "REFRESH_REQUIRED") && (data.indexOf("CLIENTS_LIST") != -1)) {
                    self.client_socket.broadcast.emit(event, message);
            } else {
                if ((event == "REFRESH_REQUIRED") && (data.indexOf("EXPERIMENTS_LIST") != -1)) {
                    self.client_socket.broadcast.emit(event, message);
                }
            }
*/
		} else {
			cout.cm("(3) I can not send the message to the web page because the socket is null.");
		}
	};


	// ============================================================================
	// MESSAGES FROM LOCAL MANAGERS TO THE CENTRAL MANAGER
	// (PRIVATE METHODS)
	// ============================================================================

  this.ReceiveMensagesFromLocalManagers = function(lm_socket) {
    var from = lm_socket.remoteAddress + ":" + lm_socket.remotePort;

    // When sending multiple messages to a Node.js tcp socket, they get streamed as a single message
    // For example: "{"command":"CALCULATIONS_LIST","data":{.......}]}]}"}}{"command":"DATA_TYPES_LIST","data":{"......
    // The Local Manager must send messages ended with "\n"
    var stream = lm_socket.pipe(split());
    stream.on("data", function(data) {
      try {
	      message = JSON.parse(data);
      } catch (e) {
        console.error("\n");
        console.error("-+-+-+-+-+-+-+-+-+--+-+\n");
        console.error("message = JSON.parse(data); FAILS.\n");
        console.error("data    = " + data + "\n");
        return console.error("-+-+-+-+-+-+-+-+-+--+-+\n" + e);
      }

		  if (message.command == "HELLO") {

			  lm_id = math_tools.GenerateRandomId(5);

			  new_local_manager = self.EnlistNewLocalManager(lm_id, from, lm_socket, message.data.result);

			  self.SendMsgToLMNetSocket(-1, new_local_manager, "HELLO", null, null, new_local_manager.lm_id);

			  self.NotifyRefreshRequired("LM_LIST|EXPERIMENTS_LIST", true);
		  }
		  else {
		  // ============================================================================
		  // MESSAGES FROM LOCAL MANAGERS TO THE CENTRAL MANAGER
		  // (AND RESPONSES TO THE WEB BROWSER)
		  // ============================================================================

		  // --------------------------------------------------------------------
		  if (message.command == "STILL_HERE") {  // The LM says I am still here and CM refreshes its capabilities
		  // --------------------------------------------------------------------
			  var lm = self.GetLocalManagerById(message.data.lm_id);
			  if (lm != null) {
				  lm.status = "OPEN";
				  lm.capabilities = message.data.result;
			  }
		  }
		  else {
		  // --------------------------------------------------------------------
		  if (message.command == "RUN") {
		  // --------------------------------------------------------------------
        // Update the experiment execution data:
        var experiment = self.GetExperimentById(message.data.lm_id, message.data.experiment_id);
        if (experiment.exec_data.num_instructions == 0) {
          experiment.exec_data.job_done = 0;
        } else {
          // Update the experiment progress
          if (experiment.exec_data.job_done < 100) {
            experiment.exec_data.executed_instructions++;
            experiment.exec_data.job_done = Math.round((experiment.exec_data.executed_instructions * 100) / (experiment.exec_data.num_instructions));
          }

          // Detect the end of the experiment:
          if (message.data.cmd == LAST_EXPERIMENT_CMD) {
            experiment.exec_data.executed_instructions = experiment.exec_data.num_instructions;
            experiment.exec_data.job_done = 100;
          }

          // Client must update his/her experiments list:
          self.NotifyRefreshRequired("EXPERIMENTS_LIST", true);
        }


        // The desired way to inform the web user that the instruction is done correctly / or has failed would
        // be sending him/her a direct message. But, it is posible that his/her session is closed now
        // so a broadcast message is thrown to every active user to ask for the result of his/her output.

        // cout.cm("Notify RUN_END=" + message.data.experiment_id + "\n");
			  // self.NotifyRefreshRequired("RUN_END=" + message.data.experiment_id); //  + "]";

			  // NO: if (message.data.result == "OK") {
			  // NO:   self.ResponseRequestOK(message.data.response_id, message.data.result);
			  // NO: } else {
				// NO:   self.ResponseRequestError(message.data.response_id, message.data.result);
			  // NO: }
		  }
		  else {
		  // --------------------------------------------------------------------
		  if (message.command == "STATUS") {
		  // --------------------------------------------------------------------
			  if (message.data.result == "OK") {
				  // in this case response_id contains the selected local manager id 
				  var lm = self.GetLocalManagerById(message.data.lm_id);
				  if (lm != null) {
					  lm.status = "OPEN";
				  }
			  }
		  }
		  else {
		  // --------------------------------------------------------------------
		  if (message.command == "CLEAN_EXPERIMENT_RESULT") {
		  // --------------------------------------------------------------------
			  if (message.data.result == "OK") {
				  self.ResponseRequestOK(message.data.response_id, message.data.result);
			  } else {
				  self.ResponseRequestError(message.data.response_id, message.data.result);
			  }
		  }
		  else {
		  // --------------------------------------------------------------------
		  if (message.command == "GET_EXPERIMENT_RESULT") {
		  // --------------------------------------------------------------------


cout.cm("Sending the experiment output to the web!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
cout.cm("message.data = " + message.data);

			  self.ResponseRequestOK(message.data.response_id, message.data);
		  }
		  else {
		  // --------------------------------------------------------------------
		  if (message.command == "CALCULATIONS_LIST") {
		  // --------------------------------------------------------------------
			  self.ResponseRequestOK(message.data.response_id, message.data);
		  }
		  else {
		  // --------------------------------------------------------------------
		  if (message.command == "COMMANDS_LIST") {
		  // --------------------------------------------------------------------
			  self.ResponseRequestOK(message.data.response_id, message.data);
		  }
		  else {
		  // --------------------------------------------------------------------
		  if (message.command == "DATA_TYPES_LIST") {
		  // --------------------------------------------------------------------
			  self.ResponseRequestOK(message.data.response_id, message.data);
		  }
		  else {
		  // --------------------------------------------------------------------
		  if (message.command == "DATA_MANAGER_VARIABLES") {
		  // --------------------------------------------------------------------
			  self.ResponseRequestOK(message.data.response_id, message.data);
		  }
		  else {
		  // --------------------------------------------------------------------
		  if (message.command == "CLOSE_EXPERIMENT") {
		  // --------------------------------------------------------------------
			  self.ResponseRequestOK(message.data.response_id, message.data);
		  }
		  else {
		  // --------------------------------------------------------------------
		  if (message.command == "EXPERIMENTS_LIST") {
		  // --------------------------------------------------------------------
			  cout.cm("******* Received the experiments list from the local manager: " + message.data.lm_id + ". List: " + JSON.stringify(message.data.result));
			  cout.cm("Let's update the experiments of this local manager and notify the change to every user");

                var updated_lm_experiments_list = JSON.parse(message.data.result);

                for (var i = 0; i < updated_lm_experiments_list.length; i++) {
                    experiment = self.GetExperimentById(message.data.lm_id, updated_lm_experiments_list[i].experiment_id);
                    if (experiment != null) {
                        experiment.status = updated_lm_experiments_list[i].status;
                    }
                }

                self.NotifyRefreshRequired("EXPERIMENTS_LIST", true);
		  }
		  else {
			  cout.cm(string_table.LM_DATA_NOT_RECOGNIZED() + JSON.stringify(message));
		  }}}}}}}}}}}}
		});

				
		lm_socket.on("close", function(data) {
			cout.cm(string_table.LOCAL_MANAGER_IS_CLOSED() + from);
			
            local_manager = self.GetLocalManagerBySocket(this);
			if (local_manager != null) {
				local_manager.status = "CLOSED";
				cout.cm("The local manager says 'close'.");
                self.NotifyRefreshRequired("LM_LIST|EXPERIMENTS_LIST", true);
            }
		});
	
		lm_socket.on("end", function() {
			cout.cm(string_table.LOCAL_MANAGER_IS_DISCONNECTED() + from);
			
			local_manager = self.GetLocalManagerBySocket(this);
			if (local_manager != null) {
				local_manager.status = "CLOSED";
				cout.cm("The local manager says good bye.");
                self.NotifyRefreshRequired("LM_LIST|EXPERIMENTS_LIST", true);
			}
		});

		lm_socket.on("error", function(e) {
			cout.cmRec(from+"_error", e);
			cout.cm(string_table.LOCAL_MANAGER_SENDS_ERROR() + from + ": " + e);
		});
	};


	// ============================================================================
	// NOTIFICATIONS TO THE USER. (Initiated by the CM)
	// ============================================================================

	this.NotifyRefreshRequired = function(data, do_broadcast) {
		self.SendMessageToWeb("REFRESH_REQUIRED", data, do_broadcast);
	};

	// ============================================================================
	// CENTRAL MANAGER AUTOMATIC TASKS
	// ============================================================================

	this.CheckAllLocalManagersStatus = function() {
		cout.cm("Checking all local managers status...");

		var new_lost_LMs = 0;

		for (i = 0; i < self.local_managers_list.length; i++) {
			if (self.local_managers_list[i].status == "...") {
				self.local_managers_list[i].status = "CONNECTION_CLOSED";
				new_lost_LMs++;
			} else {
				self.local_managers_list[i].status = "...";
				self.SendMsgToLMNetSocket(-1, self.local_managers_list[i], "STATUS", null, null, null);
			}
		}

		if (new_lost_LMs > 0) {
			self.NotifyRefreshRequired("LM_LIST", false);
		}
	}

	// ============================================================================
	// CLIENTS LIST
	// ============================================================================

    this.AddClient = function(client) {
        cout.cm("Add Client: " + client.conn.remoteAddress);

        self.clients_list.push(client); 
        self.NotifyRefreshRequired("CLIENTS_LIST", true);
    };

    this.RemoveClient = function(client) {
        cout.cm("Remove Client: " + client.conn.remoteAddress);

        self.clients_list.splice(self.clients_list.indexOf(client), 1);
        self.NotifyRefreshRequired("CLIENTS_LIST", true);
    };

	this.ExportClientsList = function() {
		var exported_list = [];

		for (i = 0; i < self.clients_list.length; i++) {
			var user = {
				"address" : self.clients_list[i].conn.remoteAddress,
			};
			exported_list.push(user);
		}

		return exported_list;
	};

	// ============================================================================
	// LOCAL MANAGERS LIST
	// ============================================================================

	this.EnlistNewLocalManager = function(lm_id, address, socket, capabilities) {
		var new_local_manager = {
			"address" : address,
			"lm_id" : lm_id,
			"sock" : socket,
			"capabilities" : capabilities,
			"used" : 0,
			"status" : "OPEN"
		};
		self.local_managers_list.push(new_local_manager);
		return new_local_manager;
	};

	this.ExportLocalManagersList = function() {
		var exported_list = [];

		for (i = 0; i < self.local_managers_list.length; i++) {
			var lm = {
				"address" : self.local_managers_list[i].address,
				"lm_id" : self.local_managers_list[i].lm_id,
				"capabilities" : self.local_managers_list[i].capabilities,
				"used" : self.local_managers_list[i].used,
				"status" : self.local_managers_list[i].status
			};
			exported_list.push(lm);
		}

		return exported_list;
	};

	/// Description.
	/// @param {lm_id} Description.
	this.GetLocalManagerByExperimentId = function(experiment_id) {
		cout.cm(string_table.SEARCHING_LOCAL_MANAGER());

		// Find the Local Manager with the selected key:
		var local_manager = null;
		for (i = 0; ((i < self.experiments_list.length) && (local_manager == null)); i++) {
			if (self.experiments_list[i].experiment_id == experiment_id) {
				local_manager = self.GetLocalManagerById(self.experiments_list[i].lm_id);
			}
		}	

		if (local_manager == null) {
			cout.cm(string_table.LOCAL_MANAGER_NOT_FOUND());
		} else {
			cout.cm(string_table.LOCAL_MANAGER_FOUND());
		}

		return local_manager;
	};

	/// Description.
	/// @param {socket} Description.
	this.GetLocalManagerById = function(lm_id) {
		cout.cm(string_table.SEARCHING_LOCAL_MANAGER());

		var lm = -1;
		for (i = 0; ((i < self.local_managers_list.length) && (lm == -1)); i++) {
			if (self.local_managers_list[i].lm_id == lm_id) {
				lm = i;
			}
		}	

		if (lm == -1) {
			cout.cm(string_table.LOCAL_MANAGER_NOT_FOUND());
		} else {
			cout.cm(string_table.LOCAL_MANAGER_FOUND());
		}

		return self.local_managers_list[lm];
	};

	/// Description.
	/// @param {socket} Description.
	this.GetLocalManagerBySocket = function(socket) {
		cout.cm(string_table.SEARCHING_LOCAL_MANAGER());

		// Find the Local Manager with the selected key:
		var lm = -1;
		for (i = 0; ((i < self.local_managers_list.length) && (lm == -1)); i++) {
			if (self.local_managers_list[i].sock == socket) {
				lm = i;
			}
		}	

		if (lm == -1) {
			cout.cm(string_table.LOCAL_MANAGER_NOT_FOUND());
		} else {
			cout.cm(string_table.LOCAL_MANAGER_FOUND());
		}

		return self.local_managers_list[lm];
	};

  this.GetFirstFreeLocalManager = function() {
    var local_manager = null;
    cout.cm(string_table.SEARCHING_BEST_LOCAL_MANAGER());

    var less_used_i = -1;
    var less_used_value = 99999;

    // Find the less used Local Manager:
    for (i = 0; i < self.local_managers_list.length; i++) { 
      if (self.local_managers_list[i].status == "OPEN") {
        if (self.local_managers_list[i].used < less_used_value) {
          less_used_value = self.local_managers_list[i].used;
          less_used_i = i;
        }
      } else {
        cout.cm("He trobat un LM que no està obert. status: '" + self.local_managers_list[i].status + "'.");
      }
    }

    if (less_used_i != -1) {
      local_manager = self.local_managers_list[less_used_i];
    }

    return local_manager;
  };

	/// Description.
	this.AssignLessUsedLocalManagerToExperiment = function(experiment_id) {
		var local_manager = self.GetFirstFreeLocalManager();

		if (local_manager != null) {
			var experiment = self.GetExperimentById(null, experiment_id);
      if (experiment != null) {
  			experiment.lm_id = local_manager.lm_id;
        experiment.status = "OPEN";
  			local_manager.used++;
      } else {
        cout.cm("I could not find the experiment...");
      }
		}

		return local_manager;
	};

	// ============================================================================
	// EXPERIMENTS LIST
	// ============================================================================

	this.EnlistNewExperiment = function(experiment_id, new_experiment_name) {
		var new_experiment = {
			experiment_id: experiment_id,
			name: new_experiment_name,
      status: 'NOT_STARTED',
			lm_id: null,
      exec_data: {
        num_instructions: 0,
        executed_instructions: 0,
        job_done: 0
      }
		};

		self.experiments_list.push(new_experiment);
		return new_experiment;
	};

  this.RemoveExperiment = function(experiment_id) {
    for (i = 0; i < self.experiments_list.length; i++) {
      if (self.experiments_list[i].experiment_id == experiment_id) {
        self.experiments_list.splice(i, 1);
        break;
      }
    }
  };

	this.ExportExperimentsList = function() {
		var exported_list = [];

		for (i = 0; i < self.experiments_list.length; i++) {
			var experiment = {
				"experiment_id" : self.experiments_list[i].experiment_id,
				"name" : self.experiments_list[i].name,
        "status" : self.experiments_list[i].status,
				"lm_id" : self.experiments_list[i].lm_id,
        "exec_data": {
          "num_instructions": self.experiments_list[i].exec_data.num_instructions,
          "executed_instructions": self.experiments_list[i].exec_data.executed_instructions,
          "job_done": self.experiments_list[i].exec_data.job_done
        }
			};
			exported_list.push(experiment);
		}

		return exported_list;
	};

	this.GetNextExperimentId = function() {
		var next_id = 0;

		for (i = 0; i < self.experiments_list.length; i++) {
			if (self.experiments_list[i].experiment_id > next_id) {
				next_id = self.experiments_list[i].experiment_id;
			}
		}	

		next_id++;
		cout.cm("Next experiment Id: '" + next_id + "'.");

		return next_id;
	};

	this.GetExperimentById = function(lm_id, experiment_id) {
		var experiment = null;

		cout.cm("Find experiment id: '" + experiment_id + "'.");

		for (i = 0; ((i < self.experiments_list.length) && (experiment == null)); i++) {
			if ((self.experiments_list[i].lm_id == lm_id) &&
                (self.experiments_list[i].experiment_id == experiment_id)) {
				experiment = self.experiments_list[i];
			}
		}	

		if (experiment != null) {
			cout.cm("Experiment found.");
		} else {
			cout.cm("Experiment not found.");
		}

		return experiment;
	};

    this.RemoveOrderFromValue = function (text) {
        var ret = text;
        
        if (typeof text != 'object') {
            if (text.indexOf(":") != -1) {
                var order = text.substr(0, text.indexOf(":"));
                if (isNaN(order)) { // For example "hello:world". hello is not a number. Return "hello:world".
                    ret = text;
                } else { // For example "3:world". 3 is a number. Return only "world".
                    ret = text.substr(text.indexOf(":") + 1);
                }
            }
        }
            
        return ret;
    };

// ============================================================================
// UPLOAD DATA FILES / RETRIEVE LIST OF DATA FILES
// ============================================================================

    this.loadDataFilesTable = function() {
        var ret = true;

        cout.cm("Reading data files table...");

        try {
          var text = fs.readFileSync(cte.DATA_FILES_TABLE_FILE(), 'utf8');
          if (text != "") {
              self.data_files_list = JSON.parse(text);
          } else {
              self.data_files_list = [];
          }
        } catch (e) {
          self.data_files_list = [];
          ret = false;
        }

        return ret;
    };

    this.saveDataFilesTable = function() {
        var ret = true;

        cout.cm("Writing data files table...");

        try {
          fs.writeFileSync(cte.DATA_FILES_TABLE_FILE(), JSON.stringify(self.data_files_list), 'utf8');
        } catch (e) {
          ret = false;
        }

        return ret;
    };

    this.RequestRegisterDataFile = function (req, res) {

        cout.cm("Registering data files...");

        newFile = {
            "location":cte.SERVER_DATA_FOLDER(),
            "filename":req.headers.filename
        };

        if (req.headers.subpath != undefined) {
            newFile.location += req.headers.subpath;
            if (newFile.location[newFile.length-1] != '/') {
                newFile.location += '/';
            }
        }

/*
        var found = false;
        for (var i = 0; ((i < self.data_files_list.length) && (!found)); i++) {
            found = ((self.data_files_list[i].location == newFile.location) &&
                     (self.data_files_list[i].filename == newFile.filename));
        }

        if (!found) {
*/
        if (self.FindArrayElementById(self.data_files_list, newFile) == null) {

            self.data_files_list.push(newFile);
            self.saveDataFilesTable();

            if (req.headers.upload == 'yes') {

                shell.mkdir('-p', newFile.location);

                res.writeHead(200);
                req.pipe(fs.createWriteStream(newFile.location + newFile.filename));

                var fileSize = req.headers['content-length'];
                var uploadedBytes = 0 ;

                req.on('data',function(d) {
                    uploadedBytes += d.length;
                    var p = (uploadedBytes/fileSize) * 100;
                    res.write("Uploading " + parseInt(p)+ " %\n");
                });

                req.on('end',function(){
                    res.end("File Upload Complete\n");
                });
            }

            if (req.headers.upload == 'no') {
                res.writeHead(200);
                res.end("File Reference Upload Complete\n");
            }    
        } else {
            res.writeHead(200);
            res.end("File Exists\n");
        }
    };


    this.RequestDataFilesList = function (response_id) {
		var exported_list = self.data_files_list;

		self.ResponseRequestOK(response_id, exported_list);
    };

};

