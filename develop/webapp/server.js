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
/// ---------------------------------------------------------------------------
/// @file server.js
/// @namespace ngaSP
/// Module for starting the application server.
/// ---------------------------------------------------------------------------

// ============================================================================
// INCLUDES
// ============================================================================
var Constants		= require('./models/constants');
var cte = new Constants();

var StringTable		= require("./models/strings.js");
var string_table = new StringTable();

var CentralManager  = require("./models/cm.js");
var central_manager = new CentralManager();

var math_tools		= require('./models/math_tools');
var string_tools	= require('./models/string_tools');
var policies	  	= require('./models/policies');
var cout			    = require('./models/logs');
var express    		= require('express');
var path       		= require('path');
var bodyParser 		= require('body-parser');

var passport      = require('passport');
var LocalStrategy = require('passport-local').Strategy;
var session       = require('express-session');
var flash         = require('connect-flash');

var walk          = require('walk');

var fs            = require('fs');
//var util            = require('util');
//util.inspect(obj, {showHidden: false, depth: 1}));

// ============================================================================
// SERVER APPLICATION
// ============================================================================

var app = express();
var http = require('http');
var server = http.Server(app);
//var server = require('http').Server(app);
var io = require('socket.io')(server);


app.use(bodyParser.json());						// JSON for client-server

app.use(express.static(__dirname +				// Define public folder
                       cte.PUBLIC_FOLDER()));
policies.DisableSameOrigin(app);				// Disable Same-domain policy
policies.EnableMethods(app, "GET, POST, PUT, DELETE");

// Walker options
var walker  = walk.walk('.', { followLinks: false });
var files   = [];

// ============================================================================
// USER ACCESS
// ============================================================================

// app.use(flash());                     // 
/*
app.use(session({secret: 'xXxXxXXxX'}));
app.use(passport.initialize());
app.use(passport.session());


passport.use(new LocalStrategy(
  function(username, password, done) {
    User.findOne({ username: username }, function (err, user) {
      if (err) { return done(err); }
      if (!user) { return done(null, false); }
      if (!user.verifyPassword(password)) { return done(null, false); }
      return done(null, user);
    });
  }
));

app.post('/login', 
  passport.authenticate('local', { failureRedirect: '/login' }),
  function(req, res) {
    res.redirect('/');
  });
*/
/*
app.get('/flash', function(req, res){
  // Set a flash message by passing the key, followed by the value, to req.flash(). 
  req.flash('info', 'Flash is back!')
  res.redirect('/');
});
 
app.get('/', function(req, res){
  // Get an array of flash messages by passing the key to req.flash() 
  res.render('index', { messages: req.flash('info') });
});
*/

// ============================================================================
// RESTful MESSAGES FROM WEB BROWSERS (From the controllers of web pages)
// ============================================================================
// Naming conventions: http://www.restapitutorial.com/lessons/restfulresourcenaming.html
// POST		/experiments		Create new experiment
// GET  	/experiments/id		Read the experiment id
// GET  	/experiments		Read all experiments
// PUT  	/experiments/id		Update experiment ******************** NO
// DELETE 	/experiments/id		Delete the experiment id ************* NO
// Use plurals


/// User request for creating a new experiment.
app.post("/results", function (req, res) {
	cout.nodeRec("WEB", "Create experiment. Name: '" + req.body.experiment_name + "'.");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestCreateExperiment(response_id, req.body.experiment_name);
});

/// User request for executing an experiment command.
app.put("/results/:experiment_id/:cmd", function (req, res) {
	console.log(JSON.stringify(req.params));
	cout.nodeRec("WEB", "Execute command. Id: '" + req.params.experiment_id + "'. Command: '" + req.params.cmd + "'.");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestExecuteCommand(response_id, req.params.experiment_id, req.params.cmd);
});

/// User request for getting the experiment output.
app.get("/results/:experiment_id", function (req, res) {
	cout.nodeRec("WEB", "Get experiment output. Id: '" + req.params.experiment_id + "'.");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestExperimentOutput(response_id, req.params.experiment_id);
});

/// User request for cleaning the experiment output.
app.delete("/results/:experiment_id", function (req, res) {
	cout.nodeRec("WEB", "Clean experiment output. Id: '" + req.params.experiment_id + "'.");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestCleanExperimentOutput(response_id, req.params.experiment_id);
});

/// User request for removing an experiment from memory.
app.delete("/experiments/:experiment_id", function (req, res) {
	console.log(JSON.stringify(req.params));
	cout.nodeRec("WEB", "Remove experiment from memory. Id: '" + req.params.experiment_id + "'.");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestRemoveExperiment(response_id, req.params.experiment_id);
});

/// User request for closing the application server.
app.delete("/servers", function (req, res) {
	cout.nodeRec("WEB", "Close the server.");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestCloseServer(response_id, server);
});

/// User request for getting the local managers list.
app.get("/localmanagers", function (req, res) {
	cout.nodeRec("WEB", "Get the local managers list.");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestLocalManagersList(response_id);
});

/// User request for getting the experiments list.
app.get("/experiments", function (req, res) {
	cout.nodeRec("WEB", "Get the experiments list.");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestExperimentsList(response_id);
});

/// User request for getting the clients list.
app.get("/clients", function (req, res) {
	cout.nodeRec("WEB", "Get the clients list.");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestClientsList(response_id);
});

/// User request for getting the calculations list.
app.get("/calculations", function (req, res) {
	cout.nodeRec("WEB", "Get the calculations list.");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestCalculationsList(response_id);
});

/// User request for getting the commands list.
app.get("/commands", function (req, res) {
	cout.nodeRec("WEB", "Get the commands list.");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestCommandsList(response_id);
});

/// User request for getting the data types list.
app.get("/datatypes", function (req, res) {
	cout.nodeRec("WEB", "Get the data types list.");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestDataTypesList(response_id);
});

/// User request for getting all data manager variables of an experiment.
app.get("/datavariables/:experiment_id", function (req, res) {
	cout.nodeRec("WEB", "Get all data manager variables of an experiment. Id: '" + req.params.experiment_id + "'.");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestDataManagerVariables(response_id, req.params.experiment_id);
});

/// User request for the ngaSP binaries list
app.get("/downloads", function (req, res) {
	cout.nodeRec("WEB", "Get downloads list.");

  walker.on('file', function(root, stat, next) {
      // Add this file to the list of files
      files.push(root + '/' + stat.name);
      next();
  });

  walker.on('end', function() {
	  var response_id = central_manager.PushClientResponse(res);
	  central_manager.RequestDataTypesList(response_id);
  });
});

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + PLANNER
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// User request for finding out if the experiment name exists.
app.get("/repository_check_experiment_name/:name", function (req, res) {
	cout.nodeRec("WEB", "Check experiment name '" + req.params.name + "'.");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestCheckExperimentName(response_id, req.params.name);
});

/// User request for finding out if the pipeline name exists.
app.get("/repository_check_pipeline_name/:name", function (req, res) {
	cout.nodeRec("WEB", "Check pipeline name '" + req.params.name + "'.");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestCheckPipelineName(response_id, req.params.name);
});

/// User request for getting the list of stored pipelines.
app.get("/repository_pipelines", function (req, res) {
	cout.nodeRec("WEB", "Get pipelines list");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestStoredPipelinesList(response_id);
});

/// User request for getting the stored pipeline nodes.
app.get("/repository_pipelines/:id", function (req, res) {
	cout.nodeRec("WEB", "Get pipeline. Id: '" + req.params.id + "'.");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestPipeline(response_id, req.params.id);
});

/// User request for getting the list of stored experiments.
app.get("/repository_experiments", function (req, res) {
	cout.nodeRec("WEB", "Get experiments list");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestStoredExperimentsList(response_id);
});

/// User request for getting the stored experiment nodes.
app.get("/repository_experiments/:id", function (req, res) {
	cout.nodeRec("WEB", "Get experiment. Id: '" + req.params.id + "'.");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestExperiment(response_id, req.params.id);
});

/// User request for storing the experiment.
app.put("/repository_experiments/:id", function (req, res) {
	cout.nodeRec("WEB", "Set experiment. Id: '" + req.params.id + "'.");
  cout.nodeRec("WEB", "++++ req.params = " + JSON.stringify(req.params));
  cout.nodeRec("WEB", "++++ req.body = " + JSON.stringify(req.body));

	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestStoreExperiment(response_id, req.params.id, req.body.data);
});

/// User request for storing the pipeline.
app.put("/repository_pipelines/:id", function (req, res) {
	cout.nodeRec("WEB", "Set pipeline. Id: '" + req.params.id + "'.");
  cout.nodeRec("WEB", "++++ req.params = " + JSON.stringify(req.params));
  cout.nodeRec("WEB", "++++ req.body = " + JSON.stringify(req.body));

	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestStorePipeline(response_id, req.params.id, req.body.data);
});

/// User request for creating a new experiment.
app.post("/execute_repository_experiment", function (req, res) {
	cout.nodeRec("WEB", "Execute experiment. Name: '" + req.body.experiment.name + "'.");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestExecuteExperiment(response_id, req.body.experiment, false);
});

/// User request for creating a new experiment.
app.post("/get_experiment_code", function (req, res) {
	cout.nodeRec("WEB", "Get experiment ngasp code. Name: '" + req.body.experiment.name + "'.");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestExecuteExperiment(response_id, req.body.experiment, true);
});

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// ============================================================================
// SERVER EVENTS
// ============================================================================

/// Web browsers connects here with the server.
/// @param {data} Description.
server.on('connection', function(data) {
});

/// The server gets an error.
/// @param {e} Description.
server.on('error', function(e) {
	cout.node(string_table.APP_ERROR() + e);
});

/// The server closes itself.
/// @param {data} Description.
server.on('close', function(data) {
	console.log("Server stoped.");
});

// ============================================================================
// WEB BROWSERS CONNECT HERE WITH SOCKET.IO.
// central_manager.client_socket will be the socket for connecting the Central
// Manager with the user web browser.
// ============================================================================

/// Description.
/// @param {socket} Description.
io.on('connection', function (socket) {
	// This way of assigning the socket is done in this way to avoid the
	// following:
	// If you have the browser open with the application and you restart the
	// node server, the socket of the browser must be reassigned in this way:
	// "socket.socket=" or the web won't receive any data.
	if (central_manager.client_socket == null) {
		cout.node("Assign current client socket...");
        central_manager.SetClientSocket(socket);
	} else {
		cout.node("Reassign current client socket...");
        central_manager.SetClientSocket(socket);
	}

    //socket.on('disconnect', function () {
    //    //socket.emit('user disconnected');
    //});
});

io.sockets.on('connect', function(client) {
    central_manager.AddClient(client);

    client.on('disconnect', function() {
        central_manager.RemoveClient(client);
    });
})


// ============================================================================
// UPLOAD DATA FILES / RETRIEVE LIST OF DATA FILES
// ============================================================================

app.post("/datafiles", function (req, res) {
    cout.node("/datafiles with '" + req.headers.filename + "'...");

    var newFile = {
        "location":cte.SERVER_DATA_FOLDER(),
        "filename":req.headers.filename
    };

    if (req.headers.subpath != undefined) {
        newFile.location += req.headers.subpath;
        if (newFile.location[newFile.length-1] != '/') {
            newFile.location += '/';
        }
    }

    var registered = false;
    var uploaded   = false;

    if (req.headers.upload == 'yes') {
        central_manager.RequestRegisterDataFile(newFile);

        // The output message is sent inside the RequestUploadDataFile because it is an async function (using res).
        uploaded = central_manager.RequestUploadDataFile(req, res, newFile);

    } else {
        // Do not upload the file, only register it
        central_manager.RequestRegisterDataFile(newFile);

        // The output message is sent here:

        res.writeHead(200);
        res.end("File Registration Completed\n");
    }

});

/// User request for getting the local managers list.
app.get("/datafiles", function (req, res) {
	cout.nodeRec("WEB", "Get data files list.");
	var response_id = central_manager.PushClientResponse(res);
	central_manager.RequestDataFilesList(response_id);
});

/// User request for unregistering a data file.
app.delete("/datafiles/:location/:filename", function (req, res) {
	cout.nodeRec("WEB", "Unregistering data file: '" + req.params.location + req.params.filename + "'.");
	var response_id = central_manager.PushClientResponse(res);

    var unregisterFile = {
        "location":req.params.location.replace(new RegExp('slash', 'g'), '/'),
        "filename":req.params.filename.replace(new RegExp('slash', 'g'), '/')
    };

	central_manager.RequestUnregisterDataFile(response_id, unregisterFile);
});


// ============================================================================
// NODE SERVER START &
// CENTRAL MANAGER START
// ============================================================================

server.listen(cte.PORT_WEB());

central_manager.Start();

