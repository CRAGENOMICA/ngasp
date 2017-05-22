/// ---------------------------------------------------------------------------
/// @file server.js
/// @namespace ngaSP
/// Module for starting the application server.
/// ---------------------------------------------------------------------------

var policies	  	= require('./models/policies');
var express    		= require('express');
var bodyParser 		= require('body-parser');
var app             = express();
var server          = require('http').Server(app);
const v8            = require('v8');
var tfa_addon       = require('./addons/tfa_addon/build/Release/tfa_addon');
var present         = require('present');

v8.setFlagsFromString('--max_old_space_size=409600000');


app.use(bodyParser.json());
app.use(express.static(__dirname + '/public'));
policies.DisableSameOrigin(app);
policies.EnableMethods(app, "GET, POST, PUT, DELETE");


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
// /:aux req.params.aux
// req.body

// =============================================================================
// For getting the elapsed time of the functions
// =============================================================================
var time = null;

function StartTimer() {
    time = process.hrtime();
    // console.time("label");
};

function GetElapsedTime() {
    // console.timeEnd("label");
    var diff = process.hrtime(time);
    return (`${diff[0] * 1e9 + diff[1]} ns`);
};

// =============================================================================
// 
// =============================================================================

/*
Return:
{
    transaction_id: 0, // This trasaction ID is not unique. The client can ask for more than one file in one trasaction.
    time: 0,           // The elapsed time for getting the data
    error: {},         // Error message if any
    data: {
        data: [
            { order: 0, id: '', seq: '' }
        ],
        items: 0,
        max_seq_bases: 0
    }
}
*/
app.post("/sequences", function (req, res) {
    //console.log("/sequences");
    // -------------------------------------------------------------------------
    var ret = {
        'transaction_id' : req.body.transaction_id * 1,
        'time'           : '',
        'error'          : {},
        'data'           : {}
    };
    StartTimer();
    // -------------------------------------------------------------------------

    try {
        var str = tfa_addon.get_sequences_by_pos(req.body.file_name,
                                                 req.body.start * 1,
                                                 req.body.step * 1);
        ret.data = JSON.parse(str);
    } catch (ex) {
        ret.error = ex;
    }

    // -------------------------------------------------------------------------
    ret.time = GetElapsedTime();
    //console.log(JSON.stringify(ret));
    res.send(ret);
    // -------------------------------------------------------------------------
});


/*
Return:
{
    transaction_id: 0, // This trasaction ID is not unique. The client can ask for more than one file in one trasaction.
    time: 0,           // The elapsed time for getting the data
    error: {},         // Error message if any
    data: {
        data: "abc"
    }
}
*/
app.post("/statistics", function (req, res) {
    //console.log("/statistics");
    // -------------------------------------------------------------------------
    var ret = "{" +
        "\"transaction_id\":"+ req.body.transaction_id * 1 + "," + 
        "\"time\":\"\"," + 
        "\"error\":{}," + 
        "\"data\":{\"data\":[";
    StartTimer();
    // -------------------------------------------------------------------------


    try {
        var str = tfa_addon.get_statistics(req.body.file_name);

        // file_content.data replacements:
        str = str.replace(/\n/g, "},");
        str = str.replace(/:\t/g, "\":\"");
        str = str.replace(/\t/g, "\",\"");
        str = str.replace(/,\"}/g, "}");
        str = str.replace(/infile\"/g, "{\"infile\"");

        ret += str;
        ret += "{}]}}";

        ret = JSON.parse(ret);

    } catch (ex) {
        ret.error = ex;
    }

    // -------------------------------------------------------------------------
    ret.time = GetElapsedTime();
    //console.log(JSON.stringify(ret));
    res.send(ret);
    // -------------------------------------------------------------------------
});

/*
Return:
{
    transaction_id: 0, // This trasaction ID is not unique. The client can ask for more than one file in one trasaction.
    time: 0,           // The elapsed time for getting the data
    error: {},         // Error message if any
    data: {
        data: "abc"
    }
}
*/
app.post("/gff", function (req, res) {
    //console.log("/gff");
    // -------------------------------------------------------------------------
    var ret = {
        'transaction_id' : req.body.transaction_id * 1,
        'time'           : '',
        'error'          : {},
        'data'           : {'data':[]}
    };
    StartTimer();
    // -------------------------------------------------------------------------


    try {
        var str = tfa_addon.get_gff(req.body.file_name);

        var lines = str.split("\n");
        for (var i = 2; i < lines.length; i++) { // i = 2 means to remove first two header lines
            var line = lines[i];
            var cols = line.split("\t");

            if ((cols.length > 8) &&
                (cols[2] == "CDS") &&
                (cols[8].indexOf("_criteria_") != -1)){

                var p = cols[8].split("\"");
                if ((p.length > 1) && (p[0] == "gene_id ")) {
                    var gene_id = p[1];

                    ret.data.data.push({
                        'gene_id':gene_id,
                        //'seqname':cols[0],
                        //'source':cols[1],
                        //'feature':cols[2],
                        'start':cols[3],
                        'end':cols[4],
                        //'score':cols[5],
                        'strand':cols[6]
                        //'frame':cols[7],
                        //'attributes':cols[8]
                    });
                }
            }
        }
    } catch (ex) {
        ret.error = ex;
    }

    // -------------------------------------------------------------------------
    ret.time = GetElapsedTime();
    //console.log("/gff return:" + JSON.stringify(ret));
    res.send(ret);
    // -------------------------------------------------------------------------
});

/*
Return:
{
    transaction_id: 0, // This trasaction ID is not unique. The client can ask for more than one file in one trasaction.
    time: 0,           // The elapsed time for getting the data
    error: {},         // Error message if any
    data: {
        data: "abc"
    }
}
*/
app.post("/weights", function (req, res) {
    //console.log("/weights");
    // -------------------------------------------------------------------------
    var ret = {
        'transaction_id' : req.body.transaction_id * 1,
        'time'           : '',
        'error'          : {},
        'data'           : {'data':[]}
    };
    StartTimer();
    // -------------------------------------------------------------------------


    try {
        var str = tfa_addon.get_weights(req.body.file_name);

        // From mstatspop's weights file to a list of POSITION
        // where WEIGHTPOS is 0 or WEIGHTVAR is 0

        var lines = str.split("\n");
        for (var i = 1; i < lines.length; i++) { // i = 1 means to remove first header line
            var line = lines[i];

            var cols = line.split("\t");

            var pos = cols[0] * 1;
            var weight_pos = cols[1] * 1;
            var weight_var = cols[2] * 1;

            if ((weight_pos != 0) && (weight_var != 0)) {
                ret.data.data.push(
                    pos
                );
            }
        }
    } catch (ex) {
        ret.error = ex;
    }

    // -------------------------------------------------------------------------
    ret.time = GetElapsedTime();
    //console.log(JSON.stringify(ret));
    res.send(ret);
    // -------------------------------------------------------------------------
});

/*
Call this function for closing all addon open files.
{
    transaction_id: 0, // This trasaction ID is not unique. The client can ask for more than one file in one trasaction.
    time: 0,           // The elapsed time for getting the data
    error: {},         // Error message if any
    data: {}
}
*/
app.delete("/close", function (req, res) {
    //console.log("/close");
    // -------------------------------------------------------------------------
    var ret = {
        'transaction_id' : req.body.transaction_id * 1,
        'time'           : '',
        'error'          : {},
        'data'           : {}
    };
    StartTimer();
    // -------------------------------------------------------------------------


    try {
        str = tfa_addon.close_files();
        ret = JSON.parse(str);
    } catch (ex) {
        ret.error = ex;
    }

    // -------------------------------------------------------------------------
    ret.transaction_id = req.body.transaction_id * 1;
    ret.time = GetElapsedTime();
    //console.log(JSON.stringify(ret));
    res.send(ret);
    // -------------------------------------------------------------------------
});

// =============================================================================
// 
// =============================================================================

function exitHandler(options, err) {

    tfa_addon.close_files();

    if (options.cleanup) {
        console.log('clean');
    }
    if (err) {
        console.log(err.stack);
    }
    if (options.exit) {
        process.exit();
    }
}

//do something when app is closing
process.on('exit', exitHandler.bind(null,{cleanup:true}));

//catches ctrl+c event
process.on('SIGINT', exitHandler.bind(null, {exit:true}));

//catches uncaught exceptions
process.on('uncaughtException', exitHandler.bind(null, {exit:true}));


server.listen(3001);

