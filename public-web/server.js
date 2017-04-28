/// ---------------------------------------------------------------------------
/// @file server.js
/// @namespace ngaSP
/// Module for starting the application server.
/// ---------------------------------------------------------------------------

var connect = require('connect');
var serveStatic = require('serve-static');
connect().use(serveStatic('/public')).listen(8080, function(){
    console.log('Server running on 8080...');
})

/*
// ============================================================================
// INCLUDES
// ============================================================================
var Constants		= require('./models/constants');
var cte = new Constants();
var policies	  	= require('./models/policies');
var express    		= require('express');
var bodyParser 		= require('body-parser');

// ============================================================================
// SERVER APPLICATION
// ============================================================================

var app = express();
var server = require('http').Server(app);

app.use(bodyParser.json());						         // JSON for client-server
app.use(express.static(__dirname +				     // Define public folder
                       cte.PUBLIC_FOLDER()));
policies.DisableSameOrigin(app);				       // Disable Same-domain policy
policies.EnableMethods(app, "GET, POST, PUT, DELETE");


// ============================================================================
// SERVER EVENTS
// ============================================================================

server.on('connection', function(data) {
});

server.on('close', function(data) {
});


// ============================================================================
// NODE SERVER START &
// CENTRAL MANAGER START
// ============================================================================

server.listen(cte.PORT_WEB());
*/
