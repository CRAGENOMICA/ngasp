CRAG.service('vcte', function () {

    // -------------------------------------------------------------------------
    // VIEWER
    // -------------------------------------------------------------------------

    this.CANVAS_BACKGROUND_COLOR = 'white';
    this.DNA_TABLE_POS_X         = 5;
    this.DNA_TABLE_POS_Y         = 0;
    this.DNA_TABLE_HEIGHT        = 710; // This is the total table height (it is the header + content heights)
    this.CONTROL_WIDTH           = 1488; // All control width withs statistics

    // -------------------------------------------------------------------------
    // VIEWER HEADER
    // -------------------------------------------------------------------------
    this.CTRL_MAIN_COLOR         = '#445F2E'; //'#596780'; //'#64738F';

    // -------------------------------------------------------------------------
    // VIEWER HEADER
    // -------------------------------------------------------------------------

    this.DNA_TABLE_HEADER_HEIGHT = 50;
    this.DNA_TABLE_HEADER_LINE2 = this.DNA_TABLE_HEADER_HEIGHT - 8;
    
    // -------------------------------------------------------------------------
    // FILE NAMES HEADER
    // -------------------------------------------------------------------------
    
    this.FILE_NAMES_BACKGROUND_COLOR = '#697F58'; //'#495468';

    // -------------------------------------------------------------------------
    // VIEWER COLUMNS
    // -------------------------------------------------------------------------

    this.TABLE_COLUMN_1_WIDTH = 70;
    this.TABLE_COLUMN_2_WIDTH = 100;
    this.TABLE_COLUMN_3_WIDTH = 50;
    this.TABLE_COLUMN_4_WIDTH = 3;
    this.TABLE_COLUMN_5_WIDTH = 500; //892
    this.CELL_SPAN            = 5;
    this.DNA_TABLE_WIDTH      = this.TABLE_COLUMN_1_WIDTH + 
                                this.TABLE_COLUMN_2_WIDTH + 
                                this.TABLE_COLUMN_3_WIDTH +
                                this.TABLE_COLUMN_4_WIDTH +  
                                this.TABLE_COLUMN_5_WIDTH;

    // -------------------------------------------------------------------------
    // VIEWER LEGEND
    // -------------------------------------------------------------------------

    this.LEGEND_POS_X            = 5;
    this.LEGEND_POS_Y            = this.DNA_TABLE_POS_Y + this.DNA_TABLE_HEIGHT + 8;
    this.LEGEND_HEIGHT           = 25;

    // -------------------------------------------------------------------------
    // BASES VIEW
    // -------------------------------------------------------------------------

    this.BASE_COLORS = {
/*      'G': "#d7191c", //"#F78C19",
        'T': "#fdae61", //"#00843A",
        'A': "#abd9e9", //"#006BB5",
        'C': "#2c7bb6", //"#293194",
        'N': "lightgray"
*/
        'G': "#666", // "#7b3294", // lila oscuro
        'T': "#aa0000", //"#c2a5cf", // lila clarito
        'A': "lightgreen", //"#a6dba0", // verde clarito
        'C': "lightblue", // "#008837", // verde oscuro
        'N': "#f7f7f7"  // blanco

    };

    this.NO_COLOR             = '#f7f7f7';

    // -------------------------------------------------------------------------
    // OUTGROUP VIEW (http://colorbrewer2.org)
    // -------------------------------------------------------------------------

    this.COLOR_OUTGROUP       = '#008837'; // verde oscuro
    this.COLOR_SNP            = '#7b3294'; // lila oscuro
    this.COLOR_NO_ANCESTRY    = '#c2a5cf'; // lila clarito
    this.MISSING_OUTGROUP     = '#f7f7f7'; // blanco

    // -------------------------------------------------------------------------
    // FREQUENCIES VIEW (http://colorbrewer2.org)
    // -------------------------------------------------------------------------

    this.COLOR_MAX_FREQ       = '#7b3294'; // lila oscuro
    this.COLOR_OTHER          = '#a6dba0'; // verde clarito
    this.MISSING_FREQ         = '#f7f7f7'; // blanco

    // -------------------------------------------------------------------------
    // STATISTICS VIEW
    // -------------------------------------------------------------------------

    this.STATISTICS_MARGIN    = 5; // Between the TFA viewer and the first statistic
    this.STATISTICS_WIDTH     = this.CONTROL_WIDTH - this.STATISTICS_MARGIN - this.DNA_TABLE_WIDTH;
    this.STAT_SPAN            = 1;  // Separation between statistics
    this.STAT_LINE_COLOR      = this.CTRL_MAIN_COLOR; // Color of the main statistic chart line.
    this.STAT_LINE_SIZE       = 1;
    this.STAT_QUAD_COLOR      = this.CTRL_MAIN_COLOR;
    this.STAT_QUAD_SIZE       = 1.5;
    this.STATISTIC_BORDERS_PADDING = 10;
    this.STATS_LINES_COLOR    = '#727c8e'; //this.CTRL_MAIN_COLOR;

    // -------------------------------------------------------------------------
    // FONTS
    // -------------------------------------------------------------------------

    this.FONTS = {
        base:              {font: "bold 6pt monospace", color: '#fff',     missing_color: '#666', sel_color: '#000'},
        table_header:      {font: "bold 8pt monospace", color: '#ccc', /*C3C7D8',*/  sel_color: '#fff'},
        table_file_header: {font: "bold 8pt monospace", color: '#ccc', /*C3C7D8',*/  sel_color: '#fff'},
        table_rownum:      {font: "bold 8pt monospace", color: '#ccc', /*C3C7D8',*/  sel_color: '#fff'},
        table_id:          {font: "bold 8pt monospace", color: '#000',     sel_color: '#000'},
        legend_info:       {font: "bold 8pt monospace", color: '#666',     sel_color: '#000'},
        stats_values:      {font: "bold 8pt monospace", color: '#666',     sel_color: '#fff'},
        gene:              {font: "bold 8pt monospace", color: this.CTRL_MAIN_COLOR,  sel_color: '#000'}
    };

    this.MIN_SHOW_TEXT_SIZE   = 5;  // This is the size of the smaller text. Less than it, the text disapperars.

    // -------------------------------------------------------------------------
    // PRECISION
    // -------------------------------------------------------------------------

    this.DECIMALS_PRECISION   = 10000;  // The number of 0s is the number of decimals

    // -------------------------------------------------------------------------
    // INFORMATION
    // -------------------------------------------------------------------------

    this.INFO_POS_X = this.DNA_TABLE_POS_X + 
                      this.DNA_TABLE_WIDTH + 
                      this.STATISTICS_MARGIN;
    this.INFO_POS_Y = this.DNA_TABLE_POS_Y + 
                      this.DNA_TABLE_HEADER_HEIGHT + 
                      this.DNA_TABLE_HEIGHT;

    // -------------------------------------------------------------------------
    // GENES
    // -------------------------------------------------------------------------

    this.GENE_COLUMN_BACKGROUND = '#fefeff';
    this.GENE_ARROW_COLOR       = this.CTRL_MAIN_COLOR;
    this.GENE_BOX_COLOR         = '#5BC0DE';
    this.GENE_SPAN              = 16;

    // -------------------------------------------------------------------------
    // VIEW TYPES
    // -------------------------------------------------------------------------

    this.ViewType = {
        OUTGROUP    : 0,
        FREQUENCY   : 1,
        BASES       : 2
    };

    this.views = [
        {'id':this.ViewType.OUTGROUP,  'view_name':"Outgroup"},
        {'id':this.ViewType.FREQUENCY, 'view_name':"Frequency"},
        {'id':this.ViewType.BASES,     'view_name':"Bases"}
    ];

    // -------------------------------------------------------------------------
    // FILE TYPES
    // -------------------------------------------------------------------------

    this.FileType = {
        TFA     : 0,
        GFF     : 1,
        WEIGHTS : 2,
        STATS   : 3
    };

});

CRAG.factory('viewer', function ($rootScope, drawing, vcte, sequences, ngProgressFactory, dao) {
  return {

    // =========================================================================
    // CONTROL DATA FUNCTIONS
    // =========================================================================

    ResizeColumn: function(viewer) {
        $rootScope.SetWait(true);

        var new_value = vcte.TABLE_COLUMN_5_WIDTH;

        var pos_ori_x = vcte.DNA_TABLE_POS_X + viewer.dna_table_width;
        var pos_des_x = viewer.mouse.x;
        var diff      = pos_des_x - pos_ori_x;

        viewer.table_column_5_width += diff;
        viewer.dna_table_width = vcte.TABLE_COLUMN_1_WIDTH + 
                                 vcte.TABLE_COLUMN_2_WIDTH + 
                                 vcte.TABLE_COLUMN_3_WIDTH +
                                 vcte.TABLE_COLUMN_4_WIDTH +
                                 viewer.table_column_5_width;
        viewer.statistics_width = vcte.CONTROL_WIDTH - vcte.STATISTICS_MARGIN - viewer.dna_table_width;

        this.RecalculateSizesForRenderingTFA(viewer);
        this.NormalizeStatisticalDataForRenderingIt(viewer);
        this.OnDrawControl(viewer);

        $rootScope.SetWait(false);
    },

    ResetViewerData: function(viewer, canvas, ctx) {
        viewer.canvas                = canvas;                // The canvas
        viewer.ctx                   = ctx;                    // The canvas' context
        viewer.progressbar           = $rootScope.progressbar; // The Progress Bar
        viewer.position              = 0;                      // First visible sequence
        viewer.max_position          = 0;                      // Last visible sequence
        viewer.position_prev         = 0;                      // Previous value of 'position'
        viewer.max_position_prev     = 0;                      // Previous value of 'max_position'
        viewer.mouse                 = { 'x': -1, 'y': -1 };   // Mouse position in pixels
        viewer.cell_selected         = { 'x': -1, 'y': -1 };   // Table cell selected
        viewer.stat_selected         = '';                     // Mouse over this statistic
        viewer.zoom                  = { 'start':-1,           // Zoom from start position. Always -1 except when user wants to zoom. Then, it has a value != -1 but then position and max_position are set and zoom gets -1 again.
                                         'previous': [],       // List of previous zooms {position:0, max_position:0}
                                         'unzooming': false    // true if user is undoing the last zooming
                                       };
        viewer.seq_width             = 0;                      // Size in pixels of a sequence
        viewer.seq_height            = 0;
        viewer.table_column_5_width  = vcte.TABLE_COLUMN_5_WIDTH;
        viewer.statistics_width      = vcte.STATISTICS_WIDTH;
        viewer.dna_table_width       = vcte.DNA_TABLE_WIDTH;
        viewer.stat_col_width        = 0;                      // Size of statistical chart columns
        viewer.start_selection_point = null;            // Coordinates of the first point in a square selection
        viewer.view_type             = vcte.ViewType.OUTGROUP;
        viewer.information =                         // Information about the mouse selected viewer area
            {
                'mouse_over'   : '',                    // 'viewer' / 'stats' / ''
                'viewer' : { 'gene_id': '', 'base': '' },
                'stats'  : { 'range': { 'min': 0, 'max': 0 },
                             'window': { 'start': 0, 'end': 0 },
                             'value': 0
                           },
                'show'   : true            // Show information dialog (true / false)
            };
        viewer.transactions = {
            'last_transaction_id': 0,       // This id is used for asking for data to the server. For example: the client wants 3 files in one transaction. Then, all three files have id=0. But just after, the client wants another file. This last file will have transaction id++.
            'list': []                      // List of transactions. Example: {'transaction_id':0, 'wait_for':0, 'arrived':0}
        };
        viewer.files = [
            {
                'id':vcte.FileType.TFA, 
                'file_name':"",             // File name
                'full_load':false,          // Set to true for getting all the file content (not only fron position to max_position)
                'data':[],                  // List of T-Fasta sequences {order:3000, id:"3001", seq:"CCCCCNNNCCCC"}
                'items':0,                  // Total number of items (visible and hidden)
                'max_seq_bases':0           // Maximum number of bases per sequence
            },
            {
                'id':vcte.FileType.GFF,     
                'file_name':"",             // File name
                'data':[]                   // List GFF records filtered by CDS and criteria {gene_id:'abc',start:'2000',end:'3000',strand:'+'/'-'/'.'}
            },
            {
                'id':vcte.FileType.WEIGHTS, 
                'file_name':"",             // File name
                'data':[]                   // List of positions of those weights that have a 0 in the secord or third column [4183,4184,4186,...]
            },
            {
                'id':vcte.FileType.STATS,   
                'file_name':"",             // File name
                'data':[],                  // mstatspop output in JSON format {infile:"./file.tfa",start_window:"1000",end_window:"2000","Theta(Wat)[0]":"0.0000",...}
                'stats_names':[],           // Statistics names {selected:true/false, name:""}
                'data_norm':[],             // Data prepared to be rendered {"Theta(Wat)[0]":0,...}
                'num_visible_charts':0,     // Number of visible charts
                'minmax':{},                // Ranges of every statistic {"Theta(Wat)[0]":{min:-1,max:1,min_ori:-2,max_ori:2},...}.
                                            // min & max are normalized with an extra border span. min_ori and max_ori are the original minimum and maximum values.
                'genes':[]                  // {'gene_id':'','start':0,'end':0},...
            }
        ];
        viewer.stats_options = {
            'show_curve_line': true,
            'show_quadratic_line': false,
            'show_range': true,
            'show_genes': false,
            'show_value': false
        };
    },

    

    // transaction_id and response.data.transaction_id are the same
    DataReceived: function(transaction_id, viewer, data_type_id, response) {
        //console.log("DataReceived");

        viewer.files[data_type_id].data = response.data.data.data;

        // =====================================================================
        // PROCESS HERE TASKS THAT REQUIRE ONLY ONE DATA SOURCE
        // =====================================================================
        switch(data_type_id) {
            case vcte.FileType.TFA:
                // user requested for (max_position - position) sequences of the T-Fasta file.
                // Here these sequences arrive. But, if the user asked for too many sequences here only arrive a limitted number of them.
                // In this case, when sequences are limitated, for example to the 50% they arrive from position to max_position jumping one sequence every time.
                // So, here we don't to worry about this because the first one is at position and the last one is at max_position.
                // Is the DrawSequences function that must draw the sequences correctly.
                // Note: "items" has the total number of sequences in the file.

                viewer.files[vcte.FileType.TFA].items = response.data.data.items;
                viewer.files[vcte.FileType.TFA].max_seq_bases = response.data.data.max_seq_bases;
                this.RecalculateSizesForRenderingTFA(viewer);

                if (viewer.files[vcte.FileType.TFA].full_load) {
                    viewer.position = 0;
                    viewer.max_position = response.data.data.items;
                }

                this.OnChangePosition(viewer); // It does not require other data. It only requires position and max_position
                break;
            case vcte.FileType.GFF:
                break;
            case vcte.FileType.WEIGHTS:
                break;
            case vcte.FileType.STATS:
                viewer.files[vcte.FileType.STATS].data_norm = [];
                viewer.files[vcte.FileType.STATS].num_visible_charts = 0;
                viewer.files[vcte.FileType.STATS].minmax = {};
                this.CreateListOfStatsNames(viewer);  // It only requires STATS data
                this.SelectDefaultStatistics(viewer); // It only requires STATS data
                break;
        }

        // Find out if all data arrived

        var t = this.GetTransaction(viewer, response.data.transaction_id);
        if (t != null) {
            t.arrived++;

            // Update progress bar

            viewer.progressbar.set((t.arrived * 100) / t.wait_for);

            // All data arrived. We can execute tasks that require mixing data:

            if (t.arrived == t.wait_for) {
                viewer.progressbar.complete();

                // =================================================================
                // PROCESS HERE TASKS THAT REQUIRE DIFFERENT DATA SOURCES
                // =================================================================
                this.NormalizeStatisticalDataForRenderingIt(viewer); // <-- It requires TFA and STATS data
                this.OnAllFilesLoaded(viewer);
            }
        }
    },


    GetTransaction: function(viewer, transaction_id) {
        var ret = null;

        for (var i = 0; ((i < viewer.transactions.list.length) && (ret == null)); i++) {
            var t = viewer.transactions.list[i];
            if (t.transaction_id == transaction_id) {
                ret = t;
            }
        }

        return ret;
    },

    LoadFiles: function(viewer, full_load) {
        //console.log("LoadFiles");

        viewer.progressbar.setColor('#ff0000');
        viewer.progressbar.set(0);
        viewer.progressbar.start();

        var first_pos = 0;
        var step = 0;
        var file_type = 0;

        // Set the loading animation

        $rootScope.SetWait(true);


        // Clear the list of previous zooms if we are going to load a new file
        if (full_load) {
            this.ZoomListClear(viewer);
        }

        // Initialize the data loaded variable to false for all data types:

        if (full_load) {
            for (var i = 0; i < viewer.files.length; i++) {
                viewer.files[i].data = [];
            }
        } else {
            viewer.files[vcte.FileType.TFA].data = [];
        }


        viewer.files[vcte.FileType.TFA].full_load = full_load;

        if (full_load) {
            first_pos = -1;
            step = -1;
        } else {
            first_pos = viewer.position;
            step = viewer.max_position - viewer.position;
        }


        var transaction_id = viewer.transactions.last_transaction_id;
        var wait_for = 0;

        if (viewer.files[vcte.FileType.TFA].file_name != "") { wait_for++; }
        if (full_load) {
            if (viewer.files[vcte.FileType.GFF].file_name != "") { wait_for++; }
            if (viewer.files[vcte.FileType.WEIGHTS].file_name != "") { wait_for++; }
            if (viewer.files[vcte.FileType.STATS].file_name != "") { wait_for++; }
        }

        viewer.transactions.list.push({
            'transaction_id': transaction_id,
            'wait_for'      : wait_for,
            'arrived'       : 0
        });

        if (viewer.files[vcte.FileType.TFA].file_name != "") {
            dao.GetTFAData(transaction_id, viewer, vcte.FileType.TFA, first_pos, step, this, function(transaction_id){});
        }

        if (full_load) {
            if (viewer.files[vcte.FileType.GFF].file_name != "") {
                dao.GetGFF(transaction_id, viewer, vcte.FileType.GFF, this, function(transaction_id){});
            }

            if (viewer.files[vcte.FileType.WEIGHTS].file_name != "") {
                dao.GetWeights(transaction_id, viewer, vcte.FileType.WEIGHTS, this, function(transaction_id){});
            }

            if (viewer.files[vcte.FileType.STATS].file_name != "") {
                dao.GetStatistics(transaction_id, viewer, vcte.FileType.STATS, this, function(transaction_id){});
            }
        }

        viewer.transactions.last_transaction_id++;
    },

    OnAllFilesLoaded: function(viewer) {
        //console.log("OnAllFilesLoaded");

        $rootScope.SetWait(false);

        // drawing.ClearCanvas(ctx_, canvas_.width, canvas_.height, CANVAS_BACKGROUND_COLOR);

        this.OnDrawControl(viewer);
    },


    ViewerHasData: function(viewer) {
        var ret = false;

        if (viewer.files[vcte.FileType.TFA].data != null) {
            ret = (viewer.files[vcte.FileType.TFA].data.length > 0);
        }
        return ret;
    },

    StatsHasData: function(viewer) {
        var ret = false;

        if (viewer.files[vcte.FileType.STATS].data != null) {
            ret = (viewer.files[vcte.FileType.STATS].data.length > 0);
        }
        return ret;
    },


    // =========================================================================
    // CONTROL DRAWING FUNCTIONS
    // =========================================================================

    DrawEmptyControl: function(viewer) {

        drawing.ClearCanvas(viewer.ctx, viewer.canvas.width, viewer.canvas.height, vcte.CANVAS_BACKGROUND_COLOR);

        var control_width = viewer.dna_table_width + vcte.STATISTICS_MARGIN + viewer.statistics_width;
        drawing.DrawRect(viewer.ctx, vcte.DNA_TABLE_POS_X, vcte.DNA_TABLE_POS_Y, control_width + 1, vcte.DNA_TABLE_HEIGHT + 1, 'black');
        drawing.DrawRect(viewer.ctx, vcte.DNA_TABLE_POS_X, vcte.DNA_TABLE_POS_Y, control_width, vcte.DNA_TABLE_HEIGHT, 'white');

        this.DrawTableHeader(viewer);
        this.DrawStatisticsHeaders(viewer);
        this.DrawSeparationColumn(viewer);
        this.DrawFileNames(viewer);
    },

    DrawTableHeader: function(viewer) {
        // console.log("DrawTableHeader");

        var x = vcte.DNA_TABLE_POS_X;
        var y = vcte.DNA_TABLE_POS_Y;

        var data_tfa = viewer.files[vcte.FileType.TFA].data;

        viewer.ctx.save();

            drawing.DrawRect(viewer.ctx, x, y + vcte.DNA_TABLE_HEADER_HEIGHT, vcte.TABLE_COLUMN_1_WIDTH, vcte.DNA_TABLE_HEIGHT - vcte.DNA_TABLE_HEADER_HEIGHT, vcte.CTRL_MAIN_COLOR); /* "No." column background */
            drawing.DrawRect(viewer.ctx, x + vcte.TABLE_COLUMN_1_WIDTH, y + vcte.DNA_TABLE_HEADER_HEIGHT, vcte.TABLE_COLUMN_2_WIDTH, vcte.DNA_TABLE_HEIGHT - vcte.DNA_TABLE_HEADER_HEIGHT, '#F8F8F8'); /* "Header" column background */
            drawing.DrawRect(viewer.ctx, x, y, viewer.dna_table_width + vcte.STATISTICS_MARGIN, vcte.DNA_TABLE_HEADER_HEIGHT, vcte.CTRL_MAIN_COLOR);  /* No. Header Gene .... row background*/

            viewer.ctx.font = vcte.FONTS.table_header.font;
            viewer.ctx.fillStyle = vcte.FONTS.table_header.color;
            viewer.ctx.textAlign = "left";

            viewer.ctx.fillText("No.", x + vcte.CELL_SPAN, y + vcte.DNA_TABLE_HEADER_LINE2);
            x += vcte.TABLE_COLUMN_1_WIDTH;

            viewer.ctx.fillText("Header", x + vcte.CELL_SPAN, y + vcte.DNA_TABLE_HEADER_LINE2);
            x += vcte.TABLE_COLUMN_2_WIDTH;

            viewer.ctx.fillText("Gene", x + vcte.CELL_SPAN, y + vcte.DNA_TABLE_HEADER_LINE2);
            x += vcte.TABLE_COLUMN_3_WIDTH;

            viewer.ctx.fillText("", x + vcte.CELL_SPAN, y + vcte.DNA_TABLE_HEADER_LINE2);
            x += vcte.TABLE_COLUMN_4_WIDTH;

            if (data_tfa.length > 0) {
                for (var i = 0; i < data_tfa[0].seq.length; i++) {
                    var draw_text = false;

                    if (i == viewer.cell_selected.x) {
                        viewer.ctx.fillStyle = vcte.FONTS.table_header.sel_color;
                        drawing.DrawCircle(viewer.ctx, x + 3, y + vcte.DNA_TABLE_HEADER_HEIGHT - 3 , 2, 'white');
                        draw_text = true;
                    } else {
                        if (viewer.seq_width > 20) {
                            viewer.ctx.fillStyle = vcte.FONTS.table_header.color;
                            draw_text = true;
                        } else {
                            draw_text = false;
                        }
                    }

                    if (draw_text) {
                        viewer.ctx.fillText(i, x, y + vcte.DNA_TABLE_HEADER_LINE2);
                    }

                    /*
                    if (i > 100) {
                        viewer.ctx.save();
                            viewer.ctx.translate(x + (viewer.seq_width/3)*1, y+ vcte.DNA_TABLE_HEADER_LINE2 - 3);
                            viewer.ctx.rotate(-0.45);
                            viewer.ctx.fillText(i, 0, 0);
                        viewer.ctx.restore();
                    }
                    else {
                        viewer.ctx.fillText(i, x, y + vcte.DNA_TABLE_HEADER_LINE2);
                    }
                    */

                    x += viewer.seq_width;
                }
            }

        viewer.ctx.restore();
    },
 
    DrawTableRownCoutColumn: function(viewer, y, order, id) {
        // console.log("DrawTableRownCoutColumn");

        var x = vcte.DNA_TABLE_POS_X;
        var yy = y;

        y = y + (viewer.seq_height/3)*2;

        var active_cell = ((order - viewer.position == viewer.cell_selected.y) && (viewer.cell_selected.y >= 0));  //&& ((viewer.cell_selected.x >= 0)
        var draw_text = false;

        // If the cell is actived       
        if (active_cell == true) {
            draw_text = true;

            // Draw the active cell pointer
            drawing.DrawCircle(viewer.ctx, x + 3, y - 3 , 2, 'white');

            if (id != "") {
                drawing.DrawCircle(viewer.ctx, x + vcte.TABLE_COLUMN_1_WIDTH + 3, y - 3 , 2, 'black');
            }

            viewer.ctx.fillStyle = vcte.FONTS.table_rownum.sel_color;
        } else {
            // The cell is not actived.
            // Its text will be drawn if the zoom is enought for the user to read it
            if (viewer.seq_height > vcte.MIN_SHOW_TEXT_SIZE) {
                draw_text = true;

                viewer.ctx.fillStyle = vcte.FONTS.table_rownum.color;
            }
        }

        if (draw_text) {
            viewer.ctx.font = vcte.FONTS.table_rownum.font;
            viewer.ctx.textAlign = "left";
            viewer.ctx.fillText(order, x + vcte.CELL_SPAN, y);
        }

        x += vcte.TABLE_COLUMN_1_WIDTH;

        // Draw the header content:

        if (draw_text == true) {

            viewer.ctx.save();
                // Clip for not writing the sequence id over the next column:
                drawing.DrawRect(viewer.ctx, x, yy -25, vcte.TABLE_COLUMN_2_WIDTH, 50, null);
                viewer.ctx.clip();

                viewer.ctx.font = vcte.FONTS.table_id.font;
                viewer.ctx.fillStyle = vcte.FONTS.table_id.color;
                viewer.ctx.textAlign = "left";
                viewer.ctx.fillText(id, x + vcte.CELL_SPAN, y);

                viewer.information.viewer.gene_id = id;

            viewer.ctx.restore();
        }
    },

    DrawBaseChar: function(viewer, x, y, base) {
        // console.log("DrawBaseChar");

        if (viewer.seq_height > vcte.MIN_SHOW_TEXT_SIZE) {
            if (base == 'N') {
                viewer.ctx.fillStyle = vcte.FONTS.base.missing_color;
            }
            else {
                viewer.ctx.fillStyle = vcte.FONTS.base.color;
            }
            viewer.ctx.fillText(base, x, y);
        }
    },

    DrawStartBasesGroup: function(viewer, x, y, color) {
        // console.log("DrawStartBasesGroup");

        viewer.ctx.beginPath();
        viewer.ctx.moveTo(x,y);
        viewer.ctx.fillStyle = color;
    },

    DrawEndBasesGroup: function(viewer, x, y, ini_x, h) {
        // console.log("DrawEndBasesGroup");

        viewer.ctx.lineTo(x,     y);
        viewer.ctx.lineTo(x,     y + h);
        viewer.ctx.lineTo(ini_x, y + h);
        viewer.ctx.closePath();
        viewer.ctx.fill();
    },

    DrawGeneBlock: function(viewer, x, y, start, end) {
        // console.log("DrawGeneBlock");

        drawing.DrawRect(viewer.ctx, x + vcte.TABLE_COLUMN_1_WIDTH + vcte.TABLE_COLUMN_2_WIDTH + vcte.GENE_SPAN,
                 y + start,
                 vcte.TABLE_COLUMN_3_WIDTH - (vcte.GENE_SPAN * 2),
                 end - start,
                 vcte.GENE_BOX_COLOR);

    },

    DrawGene: function(viewer, x, y, id, start, end, dir) {
        // console.log("DrawGene");

        viewer.files[vcte.FileType.STATS].genes.push({
            'gene_id': id,
            'start'  : start,
            'end'    : end
        });
   
        viewer.ctx.save();

            x += vcte.TABLE_COLUMN_1_WIDTH;
            x += vcte.TABLE_COLUMN_2_WIDTH;
            x += vcte.GENE_SPAN / 2;


            viewer.ctx.strokeStyle = vcte.GENE_ARROW_COLOR;
            viewer.ctx.fillStyle = viewer.ctx.strokeStyle;
            viewer.ctx.lineWidth = 6;


            var arrow_head_size = vcte.GENE_SPAN / 2;
            var limit = 0;
            var arrow_length = 10;


            // Draw Arrow Line
            y += viewer.ctx.lineWidth;
            viewer.ctx.beginPath();
            if (dir == '-') {
                viewer.ctx.moveTo(x, y + start);
            }
            if (dir == '+') {
                viewer.ctx.moveTo(x, y + start - viewer.ctx.lineWidth);
            }
//            viewer.ctx.lineTo(x, (y + start + arrow_length < y + end)?y + start + arrow_length:y + end);
            viewer.ctx.lineTo(x, y + start + arrow_length);
            viewer.ctx.closePath();
            viewer.ctx.stroke();


            if (dir == '-') {
               // Draw Arrow Head (Up)
                viewer.ctx.beginPath();
                viewer.ctx.moveTo(x, y + start - viewer.ctx.lineWidth);
                viewer.ctx.lineTo(x + arrow_head_size, y + start + arrow_head_size - viewer.ctx.lineWidth);
                viewer.ctx.lineTo(x - arrow_head_size, y + start + arrow_head_size - viewer.ctx.lineWidth);
                viewer.ctx.closePath();
                viewer.ctx.fill();
            }


            if (dir == '+') {
                // Draw Arrow Head (Down)
                viewer.ctx.beginPath();
                viewer.ctx.moveTo(x, y + start + arrow_length + viewer.ctx.lineWidth);
                viewer.ctx.lineTo(x + arrow_head_size, y + start + arrow_length - arrow_head_size + viewer.ctx.lineWidth);
                viewer.ctx.lineTo(x - arrow_head_size, y + start + arrow_length - arrow_head_size + viewer.ctx.lineWidth);
                viewer.ctx.closePath();
                viewer.ctx.fill();
            }

            y -= viewer.ctx.lineWidth;


            x += vcte.GENE_SPAN / 2;

            viewer.ctx.lineWidth = 1;

            var w = vcte.TABLE_COLUMN_3_WIDTH - vcte.GENE_SPAN * 2;

            viewer.ctx.strokeStyle = vcte.GENE_BOX_COLOR;

            // Draw Gene lINE
            viewer.ctx.beginPath();
            viewer.ctx.moveTo(x + w/2, y + start);
            viewer.ctx.lineTo(x + w/2, y + end);
            viewer.ctx.closePath();
            viewer.ctx.stroke();

            x -= vcte.GENE_SPAN;

            // Draw Gene Box Limits

            viewer.ctx.strokeStyle = vcte.GENE_ARROW_COLOR;

            viewer.ctx.setLineDash([1, 2]);

            viewer.ctx.beginPath();
            viewer.ctx.moveTo(x, y + start);
            viewer.ctx.lineTo(x + w + vcte.GENE_SPAN*2, y + start);
            viewer.ctx.closePath();
            viewer.ctx.stroke();

            viewer.ctx.beginPath();
            viewer.ctx.moveTo(x, y + end);
            viewer.ctx.lineTo(x + w + vcte.GENE_SPAN*2, y + end);
            viewer.ctx.closePath();
            viewer.ctx.stroke();


            viewer.ctx.save();
                // Clip the following gene_id text

                viewer.ctx.beginPath();
                viewer.ctx.moveTo(x, y + start);
                viewer.ctx.lineTo(x + w + vcte.GENE_SPAN*2, y + start);
                viewer.ctx.lineTo(x + w + vcte.GENE_SPAN*2, y + end);
                viewer.ctx.lineTo(x, y + end);
                viewer.ctx.closePath();
                viewer.ctx.clip();


                // Draw the gene_id text

                var pos_text =  y + start + arrow_length * 3;
                viewer.ctx.font = vcte.FONTS.gene.font;
                viewer.ctx.fillStyle = vcte.FONTS.gene.color;
                viewer.ctx.textAlign = "right";
                viewer.ctx.translate(x + 12, pos_text);
                viewer.ctx.rotate(-Math.PI/2);
                viewer.ctx.fillText(id, 0, 0);

            viewer.ctx.restore();

        viewer.ctx.restore();
    },

    DrawGeneIds: function(viewer) {
        viewer.ctx.save();
            // console.log("DrawGeneIds");

            viewer.files[vcte.FileType.STATS].genes = [];

            // This function draws all gene ids but it clips the drawing area.
            // It is important to draw all because cut gens draw properly.

            var x = vcte.DNA_TABLE_POS_X;
            var y = vcte.DNA_TABLE_POS_Y;
            var data_gff = viewer.files[vcte.FileType.GFF].data;

            var BOTTOM_DRAWING_LIMIT_PX_WITHOUT_Y = vcte.DNA_TABLE_HEIGHT - vcte.DNA_TABLE_HEADER_HEIGHT;

            y += vcte.DNA_TABLE_HEADER_HEIGHT; //<------ y is now inside the drawing area (it is POS_Y + HEADER)


            drawing.DrawRect(viewer.ctx, x + vcte.TABLE_COLUMN_1_WIDTH + vcte.TABLE_COLUMN_2_WIDTH, y, vcte.TABLE_COLUMN_3_WIDTH, BOTTOM_DRAWING_LIMIT_PX_WITHOUT_Y, vcte.GENE_COLUMN_BACKGROUND);
            viewer.ctx.clip(); // <----------- CLIP


            var cur = {id: '', start: -1, end: -1, start_px: 0, end_px: 0, dir: ''};
            var prev = {id: '', start: -1, end: -1, start_px: 0, end_px: 0, dir: ''};
            var painted = false;

            for (var i = 0; i < data_gff.length; i++) {
                cur = {
                    id: data_gff[i].gene_id,
                    start: data_gff[i].start * 1,
                    end: data_gff[i].end * 1,
                    start_px: (data_gff[i].start * 1 - viewer.position) * viewer.seq_height,
                    end_px: (data_gff[i].end * 1 - viewer.position) * viewer.seq_height,
                    dir: data_gff[i].strand
                }

                this.DrawGeneBlock(viewer, x, y, cur.start_px, cur.end_px);

                if (cur.id != prev.id) {
                    if (prev.start != -1) {
                        // draw previous gene rectagle and arrow
                        this.DrawGene(viewer, x, y,
                                      prev.id,
                                      prev.start_px, 
                                      prev.end_px,
                                      prev.dir);

                    }

                    // a new gene starts
                    prev = {                    //<---- The prev structure has the start_px of the first block of the gene
                        id: cur.id,             //      and the end_px of the last block of the gen
                        start: cur.start,
                        start_px: cur.start_px,
                        end: -1,
                        end_px: 0,
                        dir: ''
                    }
                    painted = false; //*
                }
                else {
                    painted = false;

                    prev.end = cur.end;
                    prev.end_px = cur.end_px;

                    prev.dir = (cur.dir != '.')?cur.dir:prev.dir;
                }
            }

            // draw previous gene rectagle and arrow
            this.DrawGene(viewer, x, y,
                          prev.id, 
                          prev.start_px,
                          prev.end_px,
                          prev.dir);

        viewer.ctx.restore();
    },

    DrawSequences: function(viewer) {
        // console.log("DrawSequences");
       
        this.DrawTableHeader(viewer);

        var data_tfa = viewer.files[vcte.FileType.TFA].data;
        var data_weights = viewer.files[vcte.FileType.WEIGHTS].data;

        var x = vcte.DNA_TABLE_POS_X;
        var y = vcte.DNA_TABLE_POS_Y + vcte.DNA_TABLE_HEADER_HEIGHT;

        var color = '';
        var count = { A:0, T:0, C:0, G:0 };

        viewer.ctx.font = vcte.FONTS.base.font;
        viewer.ctx.textAlign = "left";       

        var inside_path = false;
        var previous_color = '';

        if (data_tfa.length > 0) {


            // Here we know that the T-Fasta sequences start at position and end at max_position (step = max_position - position).
            // And we know that there are data.length seequences. But it is posible that data.length is less that step because there is a limit of sequences to be gotten from the file.
            // So, sometimes we will draw every sequences consecutively and sometimes we will draw them jumping a number of missing sequences.

            // Let's paint all sequences from position to max_position. Even though it is posible that we have less (data_tfa.lenght could be < than step)

            // viewer.seq_height is the height of every sequence if we had all sequences from position to max_position
            // but if we have a limitted number of sequences between this range, the height of the sequence must be bigger
            var h = viewer.seq_height * ((viewer.max_position - viewer.position) / data_tfa.length);

            /*
            Example:

                From position     = 0000
                To max_position   = 0009
                data_tfa[3]       = [0000, order=0][0003, order=3][0006, order=6]

                r loops from position to max_position  = position
                i loops the data_tfa array             = 0

                r   id      i
                0   0000    0
                1   0001    1
                2   0002    1
                3   0003    1
                4   0004    2
                5   0005    2
                6   0006    2
                7   0007    3
                8   0008    3
                9   0009    3
            */

            var i = 0;
            for(var r = viewer.position; r < viewer.max_position; r++) {

                if ((i < data_tfa.length) && (data_tfa[i].order*1 == r)) {
                    order = data_tfa[i].order * 1;
                    id    = data_tfa[i].id;
                    seq   = data_tfa[i].seq;
                    i++;
                    this.DrawTableRownCoutColumn(viewer, y, r, id);
                } else {
                    // print previous sequence because we do not have the current one
                    this.DrawTableRownCoutColumn(viewer, y, r, id); // If no ID then show the previous ID. Before, id param was ""
                    y += viewer.seq_height;
                    continue; //<-----------------------------------------------------------------------
                }


                x = vcte.DNA_TABLE_POS_X + vcte.TABLE_COLUMN_1_WIDTH + vcte.TABLE_COLUMN_2_WIDTH + vcte.TABLE_COLUMN_3_WIDTH + vcte.TABLE_COLUMN_4_WIDTH;


                inside_path = false;
                previous_color = ' ';
                previous_base = ' ';
                previous_x = 0;

                switch(viewer.view_type) {
                    case vcte.ViewType.OUTGROUP:
                        break;
                    case vcte.ViewType.FREQUENCY:
                        count = sequences.GetFrequencies(seq);
                        max_freq_base = sequences.GetMaxFrequencyBase(count);
                        break;
                    case vcte.ViewType.BASES:
                        break;
                }


                var force_to_color = '';

                if (data_weights.length > 0) {
                    if (data_weights.indexOf(id*1) == -1) {
                        force_to_color = vcte.NO_COLOR;
                    }
                }

                for (var j = 0; j < seq.length; j++) {
                    base = seq[j];

                    if (force_to_color == '') {
                        switch(viewer.view_type) {
                            case vcte.ViewType.OUTGROUP:
                                outgroup_base = seq[seq.length - 1];
                                if (outgroup_base == 'N') {
                                    if (base == 'N') { color = vcte.MISSING_OUTGROUP; }
                                    else { color = vcte.COLOR_NO_ANCESTRY; }
                                } else {
                                    if (base == 'N') { color = vcte.MISSING_OUTGROUP; }
                                    else { color = (base == outgroup_base)?vcte.COLOR_OUTGROUP:vcte.COLOR_SNP; }
                                }
                                break;
                            case vcte.ViewType.FREQUENCY:
                                if (base == 'N') { color = vcte.MISSING_FREQ; }
                                else {
                                    if (base == max_freq_base) { color = vcte.COLOR_MAX_FREQ; }
                                    else { color = vcte.COLOR_OTHER; }
                                }
                                break;
                            case vcte.ViewType.BASES:
                                color = vcte.BASE_COLORS[base];
                                break;
                        }
                    }
                    else {
                        color = force_to_color;
                    }

                    if (inside_path == false) {
                        inside_path = true;
                        previous_color = color;
                        previous_base = base;

                        this.DrawStartBasesGroup(viewer, x, y, color);
                        previous_x = x;
                    }

                    if (previous_base != base) {
                        inside_path = false;

                        this.DrawEndBasesGroup(viewer, x + viewer.seq_width, y, previous_x, h);

                        this.DrawBaseChar(viewer, previous_x, y + (viewer.seq_height / 3)*2, previous_base);

                        if (j < seq.length - 1) { // It is not the last one
                            this.DrawStartBasesGroup(viewer, x, y, color);
                            previous_x = x;
                        }
                    }

                    x += viewer.seq_width;
                }

                if (inside_path == true) {
                    this.DrawEndBasesGroup(viewer, x, y, previous_x, h);
                    this.DrawBaseChar(viewer, previous_x, y + (viewer.seq_height / 3)*2, previous_base);
                }

                x = 0;
                y += viewer.seq_height;
            }
        }
    },

    DrawLegend: function(viewer) {
        // console.log("DrawLegend");

        var x = vcte.LEGEND_POS_X;
        var y = vcte.LEGEND_POS_Y;


        // Remove previous legend
        drawing.DrawRect(viewer.ctx, x, y, viewer.dna_table_width, vcte.LEGEND_HEIGHT, 'white'); // -10, -19 and +300 are extra space

        viewer.ctx.font = vcte.FONTS.legend_info.font;
        viewer.ctx.fillStyle = vcte.FONTS.legend_info.color;
        viewer.ctx.textAlign = "left";

        switch(viewer.view_type) {
            case vcte.ViewType.OUTGROUP:
                v = [{text:'Equal to Outgroup',color:vcte.COLOR_OUTGROUP}, {text:'Missing',color:vcte.MISSING_OUTGROUP}, {text:'SNP',color:vcte.COLOR_SNP}, {text:'No Ancestry',color:vcte.COLOR_NO_ANCESTRY}, {text:'Discarded (By weights)',color:vcte.NO_COLOR}];
                break;
            case vcte.ViewType.FREQUENCY:
                v = [{text:'Max frequency',color:vcte.COLOR_MAX_FREQ}, {text:'Missing',color:vcte.MISSING_FREQ}, {text:'Other',color:vcte.COLOR_OTHER}, {text:'Discarded (By weights)',color:vcte.NO_COLOR}];
                break;
            case vcte.ViewType.BASES:
                v = [{text:'T',color:vcte.BASE_COLORS['T']}, {text:'C',color:vcte.BASE_COLORS['C']}, {text:'G',color:vcte.BASE_COLORS['G']}, {text:'A',color:vcte.BASE_COLORS['A']}, {text:'N',color:vcte.BASE_COLORS['N']}, {text:'Discarded (By weights)',color:vcte.NO_COLOR}];
                break;
        }

        var step = 40;
        var padding_text = 7;

        x += padding_text;
        y += padding_text;

        for (var i = 0; i < v.length; i++) {
            color = v[i].color;
            drawing.DrawRect(viewer.ctx, x, y, 10, 10, color, 'black');
            viewer.ctx.fillStyle = 'black';
            viewer.ctx.fillText(v[i].text, x + 20, y + 8);
            x += viewer.ctx.measureText(v[i].text).width + step;
        }

        drawing.DrawRect(viewer.ctx, vcte.LEGEND_POS_X, vcte.LEGEND_POS_Y + 1, x, vcte.LEGEND_HEIGHT - 2, null, vcte.CTRL_MAIN_COLOR);

    },

    DrawSeparationColumn: function(viewer) {
        // Draw separation between viewer and stats
        drawing.DrawRect(viewer.ctx,
                         vcte.DNA_TABLE_POS_X + viewer.dna_table_width,
                         vcte.DNA_TABLE_POS_Y,
                         vcte.STATISTICS_MARGIN,
                         vcte.DNA_TABLE_HEIGHT,
                         vcte.CTRL_MAIN_COLOR);
    },

    DrawStatisticsHeaders: function(viewer) {
        // console.log("DrawStatisticsHeaders");

        var data_norm = viewer.files[vcte.FileType.STATS].data_norm;

        var pos_x = vcte.DNA_TABLE_POS_X + viewer.dna_table_width + vcte.STATISTICS_MARGIN;
        var pos_y = vcte.DNA_TABLE_POS_Y;

        viewer.ctx.font = vcte.FONTS.table_header.font;
        viewer.ctx.textAlign = "left";

        if (data_norm.length > 0) {

        
            // loop statistics
            for (var key in data_norm[0]) {

                if (this.IsSelected(viewer, key)) {
                    viewer.ctx.save();
                        // Draw the chart title for the current statistic
                        drawing.DrawRect(viewer.ctx, pos_x - vcte.STAT_SPAN, pos_y, vcte.STAT_SPAN, vcte.DNA_TABLE_HEADER_HEIGHT, '#000');
                        drawing.DrawRect(viewer.ctx, pos_x, pos_y, viewer.stat_col_width, vcte.DNA_TABLE_HEADER_HEIGHT, vcte.CTRL_MAIN_COLOR);
                        viewer.ctx.clip();

                        if (key == viewer.stat_selected) {
                            viewer.ctx.fillStyle = vcte.FONTS.table_header.sel_color;
                            drawing.DrawCircle(viewer.ctx, pos_x + 4, pos_y + vcte.DNA_TABLE_HEADER_LINE2 - 3, 2, 'white');
                        } else {
                            viewer.ctx.fillStyle = vcte.FONTS.table_header.color;
                        }

                        viewer.ctx.fillText(key, pos_x + vcte.CELL_SPAN, pos_y + vcte.DNA_TABLE_HEADER_LINE2);
                    viewer.ctx.restore();

                    pos_x += viewer.stat_col_width;
                }
            }
        } else {
            drawing.DrawRect(viewer.ctx, pos_x, pos_y, viewer.statistics_width, vcte.DNA_TABLE_HEADER_HEIGHT, vcte.CTRL_MAIN_COLOR);
            //viewer.ctx.fillStyle = vcte.FONTS.table_header.color;
            //viewer.ctx.fillText("Statistics", pos_x + vcte.CELL_SPAN, pos_y + vcte.DNA_TABLE_HEADER_LINE2);
        }
    },

    GetNameRemovePath: function(file_name) {
        var ret = file_name;
        if (ret.indexOf('/') != -1) {
            ret = ret.substr(ret.lastIndexOf('/') + 1);
        }
        return ret;
    },

    DrawFileNames: function(viewer) {
        drawing.DrawRect(viewer.ctx,
                         vcte.DNA_TABLE_POS_X + 1,
                         vcte.DNA_TABLE_POS_Y,
                         vcte.TABLE_COLUMN_1_WIDTH - 2, // This -2 shows a thin vertical line between 
                         vcte.DNA_TABLE_HEADER_HEIGHT / 2,
                         vcte.FILE_NAMES_BACKGROUND_COLOR);


        drawing.DrawRect(viewer.ctx,
                         vcte.DNA_TABLE_POS_X + vcte.TABLE_COLUMN_1_WIDTH,
                         vcte.DNA_TABLE_POS_Y,
                         viewer.dna_table_width + vcte.STATISTICS_MARGIN - vcte.TABLE_COLUMN_1_WIDTH - 1, // This -1 shows a thin vertical line between t-fasta and stats
                         vcte.DNA_TABLE_HEADER_HEIGHT / 2,
                         vcte.FILE_NAMES_BACKGROUND_COLOR);

        viewer.ctx.font = vcte.FONTS.table_file_header.font;
        viewer.ctx.fillStyle = vcte.FONTS.table_file_header.color;
        viewer.ctx.textAlign = "left";

        var file_names = "T-Fasta: " + this.GetNameRemovePath(viewer.files[vcte.FileType.TFA].file_name);
        if (this.GetNameRemovePath(viewer.files[vcte.FileType.GFF].file_name) != "") {
            file_names += " | GFF: " + this.GetNameRemovePath(viewer.files[vcte.FileType.GFF].file_name);
        }
        if (this.GetNameRemovePath(viewer.files[vcte.FileType.WEIGHTS].file_name) != "") {
            file_names += " | Weights: " + this.GetNameRemovePath(viewer.files[vcte.FileType.WEIGHTS].file_name);
        }


        viewer.ctx.fillText(file_names,
                            vcte.DNA_TABLE_POS_X + vcte.TABLE_COLUMN_1_WIDTH + vcte.CELL_SPAN,
                            vcte.DNA_TABLE_POS_Y + 16);

        drawing.DrawRect(viewer.ctx,
                         vcte.DNA_TABLE_POS_X + viewer.dna_table_width + vcte.STATISTICS_MARGIN,
                         vcte.DNA_TABLE_POS_Y,
                         viewer.statistics_width,
                         vcte.DNA_TABLE_HEADER_HEIGHT / 2,
                         vcte.FILE_NAMES_BACKGROUND_COLOR);

        viewer.ctx.font = vcte.FONTS.table_file_header.font;
        viewer.ctx.fillStyle = vcte.FONTS.table_file_header.color;
        viewer.ctx.textAlign = "left";

        viewer.ctx.fillText("Statistics: " + this.GetNameRemovePath(viewer.files[vcte.FileType.STATS].file_name),
                            vcte.DNA_TABLE_POS_X + viewer.dna_table_width + vcte.STATISTICS_MARGIN + vcte.CELL_SPAN,
                            vcte.DNA_TABLE_POS_Y + 16);
    },

    DrawStatsGenes: function(viewer) {

        var x = vcte.DNA_TABLE_POS_X + viewer.dna_table_width + vcte.STATISTICS_MARGIN;
        var y = vcte.DNA_TABLE_POS_Y + vcte.DNA_TABLE_HEADER_HEIGHT;
        var w = viewer.statistics_width; //stat_col_width;
        var data_norm = viewer.files[vcte.FileType.STATS].data_norm;
        var first_stat = true;
        var bottom = vcte.DNA_TABLE_POS_Y + vcte.DNA_TABLE_HEIGHT;

        // loop statistics
        for (var key in data_norm[0]) {

            // filter statistics
            if (this.IsSelected(viewer, key)) {

                for (var i = 0; i < viewer.files[vcte.FileType.STATS].genes.length; i++) {
                    var g = viewer.files[vcte.FileType.STATS].genes[i];

                    viewer.ctx.save();

                        if (first_stat) {
                            // Draw Gene Box Limits for all statistics

                            viewer.ctx.strokeStyle = vcte.STATS_LINES_COLOR;

                            viewer.ctx.setLineDash([1, 2]);

                            viewer.ctx.beginPath();
                            viewer.ctx.moveTo(x, y + g.start);
                            viewer.ctx.lineTo(x + w, y + g.start);
                            viewer.ctx.closePath();
                            viewer.ctx.stroke();

                            viewer.ctx.beginPath();
                            viewer.ctx.moveTo(x, y + g.end);
                            viewer.ctx.lineTo(x + w, y + g.end);
                            viewer.ctx.closePath();
                            viewer.ctx.stroke();
                        }

                        // Clip the following gene_id text

                        var clip_bottom = (y + g.end < bottom)?y + g.end:bottom;

                        viewer.ctx.beginPath();
                        viewer.ctx.moveTo(x, y + g.start);
                        viewer.ctx.lineTo(x + w + vcte.GENE_SPAN*2, y + g.start);
                        viewer.ctx.lineTo(x + w + vcte.GENE_SPAN*2, clip_bottom);
                        viewer.ctx.lineTo(x, clip_bottom);
                        viewer.ctx.closePath();
                        viewer.ctx.clip();

                        // Draw the gene_id text

                        var pos_text =  y + g.start + 5;
                        viewer.ctx.font = vcte.FONTS.gene.font;
                        viewer.ctx.fillStyle = vcte.STATS_LINES_COLOR;
                        viewer.ctx.textAlign = "right";
                        viewer.ctx.translate(x + 12, pos_text);
                        viewer.ctx.rotate(-Math.PI/2);
                        viewer.ctx.fillText(g.gene_id, 0, 0);

                    viewer.ctx.restore();
                }

                x += viewer.stat_col_width;

                first_stat = false;
            }
        }

    },

    DrawStatistics: function(viewer) {
        // console.log("DrawStatistics");

        var x = vcte.DNA_TABLE_POS_X;
        var y = vcte.DNA_TABLE_POS_Y;
        var data_norm = viewer.files[vcte.FileType.STATS].data_norm;
        var data_stats = viewer.files[vcte.FileType.STATS].data;
        var data_minmax = viewer.files[vcte.FileType.STATS].minmax;


        if (data_norm.length > 0) {

            viewer.ctx.font = vcte.FONTS.stats_values.font;
            viewer.ctx.textAlign = "left";

            pos_x = x + viewer.dna_table_width + vcte.STATISTICS_MARGIN;
            var pos_y = y;

            // Draw separation between viewer and stats and the background of the statistic separations
            drawing.DrawRect(viewer.ctx, pos_x - vcte.STATISTICS_MARGIN, vcte.DNA_TABLE_POS_Y, vcte.STATISTICS_MARGIN + viewer.statistics_width, vcte.DNA_TABLE_HEIGHT, vcte.CTRL_MAIN_COLOR);

            // loop statistics
            for (var key in data_norm[0]) {

                if (this.IsSelected(viewer, key)) {

                    var prev_point = {x: -1, y: -1}; // For joining quadratic lines
                    var first_point = {x: -1, y: -1};
                    var second_point = {x: -1, y: -1};
                    var prev_middle_point = {x: -1, y: -1}; // For the continuos chart line
                    var middle_point = {x: -1, y: -1};

                    viewer.ctx.save();

                        // Draw the chart background for the current statistic
                        drawing.DrawRect(viewer.ctx, pos_x, pos_y + vcte.DNA_TABLE_HEADER_HEIGHT, viewer.stat_col_width - vcte.STAT_SPAN, vcte.DNA_TABLE_HEIGHT - vcte.DNA_TABLE_HEADER_HEIGHT, 'white');
                        viewer.ctx.clip();

                        if (viewer.stats_options.show_range) {
                            // Draw Ranges

                            viewer.ctx.font = vcte.FONTS.stats_values.font;
                            viewer.ctx.fillStyle = vcte.STATS_LINES_COLOR;
                            viewer.ctx.setLineDash([1, 2]);
                            viewer.ctx.lineWidth = 1;
                            viewer.ctx.strokeStyle = vcte.STATS_LINES_COLOR;

                            // 100% ----------------------------> viewer.stat_col_width
                            // STATISTIC_BORDERS_PADDING% ------> border_padding_px?
                            var border_padding_px = (vcte.STATISTIC_BORDERS_PADDING * viewer.stat_col_width) / 100;

                            positions = [
                                {'x':pos_x + border_padding_px, 'value':data_minmax[key].min_ori}, 
                                {'x':0, 'value':this.RoundValue(data_minmax[key].min_ori + ((data_minmax[key].max_ori - data_minmax[key].min_ori) / 3))}, 
                                {'x':0, 'value':this.RoundValue(data_minmax[key].max_ori - ((data_minmax[key].max_ori - data_minmax[key].min_ori) / 3))}, 
                                {'x':pos_x + viewer.stat_col_width - vcte.STAT_SPAN - border_padding_px, 'value':data_minmax[key].max_ori}
                            ];
                            var d = (positions[3].x - positions[0].x) / 3;
                            positions[1].x = positions[0].x + d;
                            positions[2].x = positions[0].x + 2*d;
                            

                            var pos_y_ini = pos_y + vcte.DNA_TABLE_HEADER_HEIGHT;
                            var pos_y_fin = pos_y + vcte.DNA_TABLE_HEADER_HEIGHT + vcte.DNA_TABLE_HEIGHT;

                            for (var i = 0; i < positions.length; i++) {
                                if (i == 0)                    { viewer.ctx.textAlign = "left";  } else {
                                if (i == positions.length - 1) { viewer.ctx.textAlign = "right"; } else {
                                                                 viewer.ctx.textAlign = "center";}}

                                viewer.ctx.fillText(positions[i].value, positions[i].x, pos_y_ini + 10);
                                viewer.ctx.beginPath();
                                viewer.ctx.moveTo(positions[i].x, pos_y_ini);
                                viewer.ctx.lineTo(positions[i].x, pos_y_fin);
                                viewer.ctx.closePath();
                                viewer.ctx.stroke();
                            }

                        }


                        viewer.ctx.setLineDash([0]); // [0] means solid line

                        var first_time = true;

                        var first_dot_of_current_stat = { x: -1, y: -1 };
                        var last_dot_of_current_stat = { x: -1, y: -1 };

                        // Loop all values of the current statistic.
                        for(var i = 0; i < data_norm.length; i++) {

                            // Every value has an start and and end. If they are not null we can draw a line
                            // if ((data_norm[i].start_window != null) && (data_norm[i].end_window != null)) {

                            if (data_norm[i].start_window_assigned != undefined) {
                                if (data_norm[i].start_window_assigned == true) {

                                    first_point = {x: pos_x + data_norm[i][key] * 1, y: data_norm[i].start_window * 1};
                                    second_point = {x: pos_x + data_norm[i][key] * 1, y: data_norm[i].end_window * 1};
                                    middle_point = {x: first_point.x, y: first_point.y + (second_point.y - first_point.y) / 2};

                                    // Draw vertical lines

                                    if (viewer.stats_options.show_quadratic_line) {
                                        viewer.ctx.lineWidth = vcte.STAT_QUAD_SIZE;
                                        viewer.ctx.strokeStyle = vcte.STAT_QUAD_COLOR;

                                        viewer.ctx.beginPath();
                                        viewer.ctx.moveTo(first_point.x, first_point.y);
                                        viewer.ctx.lineTo(second_point.x, second_point.y);
                                        viewer.ctx.closePath();
                                        viewer.ctx.stroke();
                                    }

                                    if (first_time) {
                                        first_time = false;
                                        first_dot_of_current_stat = { x: middle_point.x, y: middle_point.y };
                                    } else {
                                        last_dot_of_current_stat = { x: middle_point.x, y: middle_point.y };

                                        if (viewer.stats_options.show_quadratic_line) {
                                            // Join quadratic lines

                                            viewer.ctx.lineWidth = vcte.STAT_QUAD_SIZE;
                                            viewer.ctx.strokeStyle = vcte.STAT_QUAD_COLOR;

                                            viewer.ctx.beginPath();
                                            viewer.ctx.moveTo(prev_point.x, prev_point.y);
                                            viewer.ctx.lineTo(first_point.x, first_point.y);
                                            viewer.ctx.closePath();
                                            viewer.ctx.stroke();
                                        }
                
                                        // Draw main continuos line

                                        if (viewer.stats_options.show_curve_line) {
                                            viewer.ctx.lineWidth = vcte.STAT_LINE_SIZE;
                                            viewer.ctx.strokeStyle = vcte.STAT_LINE_COLOR;

                                            viewer.ctx.beginPath();
                                            viewer.ctx.moveTo(prev_middle_point.x, prev_middle_point.y);
                                            viewer.ctx.lineTo(middle_point.x, middle_point.y);
                                            viewer.ctx.closePath();
                                            viewer.ctx.stroke();
                                        }

                                        if (viewer.stats_options.show_values) {
                                            viewer.ctx.font = vcte.FONTS.stats_values.font;
                                            viewer.ctx.textAlign = "left";
                                            viewer.ctx.fillStyle = vcte.FONTS.stats_values.color;

                                            var real_rounded_value = this.RoundValue(data_stats[i][key]);
                                            viewer.ctx.fillText(real_rounded_value, middle_point.x + 10, middle_point.y);
                                        }
                                    }
                                    
                                    prev_point = {x:second_point.x, y:second_point.y};
                                    prev_middle_point = {x:middle_point.x, y:middle_point.y};
                                }
                            }
                        }


                        // Close the continuos line top and bottom
                        // when the continuos line is visible and the quadratic line is hidden
                        if ((viewer.stats_options.show_quadratic_line == false) && (viewer.stats_options.show_curve_line == true)) {
                            viewer.ctx.lineWidth = vcte.STAT_LINE_SIZE;
                            viewer.ctx.strokeStyle = vcte.STAT_LINE_COLOR;

                            // Line from top to the first point of the statistic
                            viewer.ctx.beginPath();
                            viewer.ctx.moveTo(first_dot_of_current_stat.x, pos_y + vcte.DNA_TABLE_HEADER_HEIGHT);
                            viewer.ctx.lineTo(first_dot_of_current_stat.x, first_dot_of_current_stat.y);
                            viewer.ctx.closePath();
                            viewer.ctx.stroke();

                            if ((last_dot_of_current_stat.x == -1) && (last_dot_of_current_stat.y == -1)) {
                                last_dot_of_current_stat.x = first_dot_of_current_stat.x;
                                last_dot_of_current_stat.y = first_dot_of_current_stat.y;
                            }
                            // Line from last point of the statistic to the bottom
                            viewer.ctx.beginPath();
                            viewer.ctx.moveTo(last_dot_of_current_stat.x, last_dot_of_current_stat.y);
                            viewer.ctx.lineTo(last_dot_of_current_stat.x, pos_y + vcte.DNA_TABLE_HEIGHT);
                            viewer.ctx.closePath();
                            viewer.ctx.stroke();
                        }

                        pos_x += viewer.stat_col_width;

                    viewer.ctx.restore();

                }
            }

            if (viewer.stats_options.show_genes) {
                this.DrawStatsGenes(viewer);
            }

        }

        this.DrawStatisticsHeaders(viewer);
    },


    // =========================================================================
    // SELECTION FUNCTIONS
    // =========================================================================

    IsSelected: function(viewer, stat_name) {
        // console.log("IsSelected");

        var ret = false;

        var stats_names = viewer.files[vcte.FileType.STATS].stats_names;

        for(var i = 0; i < stats_names.length; i++) {
            if (stats_names[i].name == stat_name) {
                ret = stats_names[i].selected;
                break; //<---------------------------------- break loop
            }
        }
        return ret;
    },

    GetSelectedGene: function(viewer) {
        // console.log("GetSelectedGene");
        var data_tfa = viewer.files[vcte.FileType.TFA].data;
        var data_gff = viewer.files[vcte.FileType.GFF].data;

        viewer.information.viewer.gene_id = "";


        if ((viewer.cell_selected.y > 0) && (viewer.cell_selected.y < data_tfa.length)) {

            var id = data_tfa[viewer.cell_selected.y].id * 1;

            last_gene_id_end = 0;
            viewer.information.viewer.gene_id = "";
            for (var i = 0; i < data_gff.length; i++) {
                if (id >= data_gff[i].start * 1) { // && (id <= data_gff[i].end * 1)) {
                    viewer.information.viewer.gene_id = data_gff[i].gene_id;            // It gets the last gene_id
                }

                if (data_gff[i].gene_id == viewer.information.viewer.gene_id) {
                    last_gene_id_end = data_gff[i].end * 1;
                }
            }
    
            if (id <= last_gene_id_end) { // ok
            } else {
                viewer.information.viewer.gene_id = "";
            }
        }
    },

    GetSelectedBase: function(viewer) {
        // console.log("GetSelectedBase");

        var data_tfa = viewer.files[vcte.FileType.TFA].data;

        viewer.information.viewer.base = "";

        if ((viewer.cell_selected.y > 0) && (viewer.cell_selected.y < data_tfa.length)) {
            if ((viewer.cell_selected.x >= 0) && (viewer.cell_selected.x < data_tfa[viewer.cell_selected.y].seq.length)) {
                viewer.information.viewer.base = data_tfa[viewer.cell_selected.y].seq[viewer.cell_selected.x];
            }
        }
    },

    GetSelectedStatsInfo: function(viewer) {
        // console.log("GetSelectedStatsInfo");

        var data_tfa = viewer.files[vcte.FileType.TFA].data;
        var data_stats = viewer.files[vcte.FileType.STATS].data;
        var data_minmax = viewer.files[vcte.FileType.STATS].minmax;

        if (viewer.stat_selected != "") {
            var text = "";

            if (!isNaN(viewer.position + viewer.cell_selected.y)) {
                row_num = viewer.position + viewer.cell_selected.y;

                if ((viewer.cell_selected.y < data_tfa.length) && (viewer.cell_selected.y >= 0)) {

                    var order = data_tfa[viewer.cell_selected.y].order;
                    var id = data_tfa[viewer.cell_selected.y].id;
                    var start_window = 0;
                    var end_window = 0;
                    var value = 0;

                    found = false;
                    for(var j = 0; ((j < data_stats.length) && (found == false)); j++) {
                        if ((id >= data_stats[j].start_window * 1) && (id <= data_stats[j].end_window * 1)) {
                            found = true;

                            start_window = data_stats[j]["start_window"];
                            end_window = data_stats[j]["end_window"];
                            value = data_stats[j][viewer.stat_selected];
                        }
                    }

                    viewer.information.stats.range.min    = data_minmax[viewer.stat_selected].min;
                    viewer.information.stats.range.max    = data_minmax[viewer.stat_selected].max;
                    viewer.information.stats.window.start = start_window;
                    viewer.information.stats.window.end   = end_window;
                    viewer.information.stats.value        = value;

                    /*
                    ret = "Range: [" + data_minmax[viewer.stat_selected].min + ", " + data_minmax[viewer.stat_selected].max + "]. " + 
                          "Window: [" + start_window + ", " + end_window + "]. " + 
                          "Value: " + value;
                           //"Statistic: " + viewer.stat_selected + ". " + 
                           //"Range: [" + data_minmax[viewer.stat_selected].min + ", " + data_minmax[viewer.stat_selected].max + "]. " + 
                           //"No.: " + order + ". " +
                           //"ID: " + id + ". " +
                           //"Window: [" + start_window + ", " + end_window + "]. " +
                           //"Value: " + value;
                    */
                }
            }
        }
    },

    UpdateMousePosition: function(viewer, event, canvas) {
        // console.log("UpdateMousePosition");

        viewer.mouse = {
            x: event.pageX - viewer.canvas.offsetLeft,
            y: event.pageY - viewer.canvas.offsetTop
        };

        viewer.cell_selected = {
            x: (viewer.mouse.x >= vcte.DNA_TABLE_POS_X + vcte.TABLE_COLUMN_1_WIDTH + vcte.TABLE_COLUMN_2_WIDTH + vcte.TABLE_COLUMN_3_WIDTH + vcte.TABLE_COLUMN_4_WIDTH) && (viewer.mouse.x <= vcte.DNA_TABLE_POS_X + viewer.dna_table_width + vcte.STATISTICS_MARGIN + viewer.statistics_width)?parseInt((viewer.mouse.x - vcte.DNA_TABLE_POS_X - vcte.TABLE_COLUMN_1_WIDTH - vcte.TABLE_COLUMN_2_WIDTH - vcte.TABLE_COLUMN_3_WIDTH - vcte.TABLE_COLUMN_4_WIDTH) / viewer.seq_width):-1,
            y: ((viewer.mouse.y >= vcte.DNA_TABLE_POS_Y + vcte.DNA_TABLE_HEADER_HEIGHT) && (viewer.mouse.y <= vcte.DNA_TABLE_POS_Y + vcte.DNA_TABLE_HEIGHT))?parseInt((viewer.mouse.y - vcte.DNA_TABLE_POS_Y - vcte.DNA_TABLE_HEADER_HEIGHT) / viewer.seq_height):-1
        };

        if (viewer.cell_selected.x > viewer.files[vcte.FileType.TFA].max_seq_bases - 1) {
            viewer.cell_selected.x = -1;
        }

        var stats_names = viewer.files[vcte.FileType.STATS].stats_names;

        if ((viewer.mouse.x >= vcte.DNA_TABLE_POS_X + viewer.dna_table_width + vcte.STATISTICS_MARGIN) &&
            (viewer.mouse.x < vcte.DNA_TABLE_POS_X + viewer.dna_table_width + vcte.STATISTICS_MARGIN + viewer.statistics_width) &&
            (viewer.cell_selected.y != -1)) {
            var sel = parseInt((viewer.mouse.x - vcte.DNA_TABLE_POS_X - viewer.dna_table_width - vcte.STATISTICS_MARGIN) / (viewer.stat_col_width));
            if ((sel >= 0) && (sel < stats_names.length)) {
                viewer.stat_selected = "";
                for(var i = 0; ((i < stats_names.length) && (viewer.stat_selected == "")); i++) {
                    if (stats_names[i].selected) {
                        if (sel == 0) {
                            viewer.stat_selected = stats_names[i].name;
                        } else {
                            sel--;
                        }
                    }
                }
            }
            else {
                viewer.stat_selected = "";
            }
        } else {
            viewer.stat_selected = "";
        }
    },

    // =========================================================================
    // STATISTICS FUNCTIONS
    // =========================================================================

    CreateListOfStatsNames: function(viewer) {
        // console.log("CreateListOfStatsNames");

        viewer.files[vcte.FileType.STATS].stats_names = [];
        var data_stats = viewer.files[vcte.FileType.STATS].data;

        if ((data_stats != null) && (data_stats.length > 0)) {
            for (var key in data_stats[0]) {
                if ((key != 'start_window') &&               // They are not an stadistics
                    (key != 'end_window') &&                 // 
                    (key != 'infile') &&                     // 
                    (key != 'iteration') &&                     // 
                    (key != 'npermutations') &&                     // 
                    (key != 'Length') &&                     // 
                    (key != 'Lengtht') &&                     // 
                    (key != 'mh') &&                     // 
                    (key != 'npops') &&                     // 
                    (key != 'nsam[0]') &&                     // 
                    (key != 'nsam[1]') &&                     // 
                    (key.indexOf("fr[") == -1) &&                     // 
                    (key != 'an_xo[0]') &&                     // 
                    (key != 'bn_xo[0]') &&                     // 
                    (key != 'seed') &&                       // 

                    (isNaN(data_stats[0][key]) == false) &&  // It is a number
                    (data_stats[0][key] != null)) {          // It is not null

                    viewer.files[vcte.FileType.STATS].stats_names.push({
                        'name': key,
                        'selected': false
                    });
                }
            }
        }
    },

    SelectDefaultStatistics: function(viewer) {
        // console.log("SelectDefaultStatistics");

        viewer.files[vcte.FileType.STATS].num_visible_charts = 0;
        var stats_names = viewer.files[vcte.FileType.STATS].stats_names;

        if ((stats_names != null) && (stats_names.length > 0)) {
            for (var i = 0; i < stats_names.length; i++) {
                if ((stats_names[i].name == 'TajimaD[1]') ||
                    (stats_names[i].name == 'Fst[0,1]') || 
                    (stats_names[i].name == 'PiT[0,1]')) {
                //if (stats_names[i].name.indexOf('Theta(F') != -1) {
                    stats_names[i].selected = true;
                    viewer.files[vcte.FileType.STATS].num_visible_charts++;
                } else {
                    stats_names[i].selected = false;
                }
            }
        }
    },

    CountVisibleStatistics: function(viewer) {
        // console.log("CountVisibleStatistics");

        viewer.files[vcte.FileType.STATS].num_visible_charts = 0;

        for(var k = 0; k < viewer.files[vcte.FileType.STATS].stats_names.length; k++) {
            if (viewer.files[vcte.FileType.STATS].stats_names[k].selected) {
                viewer.files[vcte.FileType.STATS].num_visible_charts++;
            }
        }
    },

    RoundValue: function(value) {
        return (Math.round(value * vcte.DECIMALS_PRECISION) / vcte.DECIMALS_PRECISION);
    },

    GetStatisticsMinMaxs: function(viewer) {
        // console.log("GetStatisticsMinMaxs");

        // We have all statistic values in "viewer.files[vcte.FileType.STATS].data".
        // For every statistic get the minimum and the maximum into viewer.files[vcte.FileType.STATS].data_norm
        viewer.files[vcte.FileType.STATS].minmax = {};


        var data_stats = viewer.files[vcte.FileType.STATS].data;
        var data_minmax = viewer.files[vcte.FileType.STATS].minmax;


        for(var k = 0; k < viewer.files[vcte.FileType.STATS].stats_names.length; k++) {
            key = viewer.files[vcte.FileType.STATS].stats_names[k].name;

            data_minmax[key] = { min:0, max:0};
            for(var i = 0; i < data_stats.length; i++) {
                var win = data_stats[i];
                if (isNaN(win[key] * 1) == false) {
                    var value = win[key] * 1;

                    if (i == 0) {
                        data_minmax[key].min = value;
                        data_minmax[key].max = value;
                    } else {
                        if (value < data_minmax[key].min) data_minmax[key].min = value;
                        if (value > data_minmax[key].max) data_minmax[key].max = value;
                    }
                }
            }
        }

        // We want to add an extra X% of range for every side. For example: Range[0,100] should be [-5,105].
        // And n min_ori and max_ori we will store the original range values
        // Min and max are rounded to X decimals.
        for (var key in data_minmax) {
            var m = data_minmax[key];
            var range = m.max - m.min;
            var extra_X = (vcte.STATISTIC_BORDERS_PADDING * range) / 100;

            m.min_ori = this.RoundValue(m.min);
            m.max_ori = this.RoundValue(m.max);

            m.min += extra_X;
            m.max -= extra_X;

            m.min = this.RoundValue(m.min);
            m.max = this.RoundValue(m.max);
        }

    },

    RecalculateSizesForRenderingTFA: function(viewer) {
        viewer.seq_width = (viewer.dna_table_width - vcte.TABLE_COLUMN_1_WIDTH - vcte.TABLE_COLUMN_2_WIDTH - vcte.TABLE_COLUMN_3_WIDTH - vcte.TABLE_COLUMN_4_WIDTH) / viewer.files[vcte.FileType.TFA].max_seq_bases;
    },

    NormalizeStatisticalDataForRenderingIt: function(viewer) {
        // console.log("NormalizeStatisticalDataForRenderingIt");

        this.GetStatisticsMinMaxs(viewer);     // It returns viewer.files[vcte.FileType.STATS].minmax.
        this.CountVisibleStatistics(viewer);   // It returns viewer.files[vcte.FileType.STATS].num_visible_charts;

        // Normalize every statistic value using the just calculated minimum and maximum
        // into viewer.files[vcte.FileType.STATS].data_norm

        viewer.files[vcte.FileType.STATS].data_norm = JSON.parse(JSON.stringify(viewer.files[vcte.FileType.STATS].data)); // Clone object


        var data_tfa = viewer.files[vcte.FileType.TFA].data;
        var data_stats = viewer.files[vcte.FileType.STATS].data;
        var data_norm = viewer.files[vcte.FileType.STATS].data_norm;
        var data_minmax = viewer.files[vcte.FileType.STATS].minmax;
        var stats_names = viewer.files[vcte.FileType.STATS].stats_names;
        

        // Normalize values

        viewer.stat_col_width = ((viewer.statistics_width) / viewer.files[vcte.FileType.STATS].num_visible_charts);

        //100% --------------------------> viewer.stat_col_width
        //STATISTIC_BORDERS_PADDING% ----> border_padding_pixels?
        var border_padding_pixels = (vcte.STATISTIC_BORDERS_PADDING * viewer.stat_col_width) / 100;

        for(var i = 0; i < data_norm.length; i++) {
            var param = data_norm[i];

            for(var k = 0; k < stats_names.length; k++) {
                key = stats_names[k].name;
 
                // MinMaxRange    is    SizeOfStatsColum-STAT_SPAN-border_padding
                // Value-min      is    X                                          /// -min because the value must be 0-based

                // X = Value * (SizeOfStatsColum-STAT_SPAN) / MinMaxRange

                if (isNaN(param[key] * 1) == false) {
                    param[key] = border_padding_pixels + ((((param[key]*1) - data_minmax[key].min_ori) * (viewer.stat_col_width - vcte.STAT_SPAN - 2*border_padding_pixels)) / (data_minmax[key].max_ori - data_minmax[key].min_ori));
                } else {
                    param[key] = 0;
                }
            }
        }

        // Translate into pixels the start_window and end_window of the data_norm
        var y = vcte.DNA_TABLE_POS_Y + vcte.DNA_TABLE_HEADER_HEIGHT;
        var h = viewer.seq_height * ((viewer.max_position - viewer.position) / data_tfa.length);

        for(var i = 0; i < data_tfa.length; i++) {
            id    = data_tfa[i].id * 1;

            found = false;
            for(var j = 0; ((j < data_stats.length) && (found == false)); j++) {
                if ((id >= data_stats[j].start_window * 1) && (id <= data_stats[j].end_window * 1)) {
                    found = true;

                    if (data_norm[j]["start_window_assigned"] == undefined) {
                        data_norm[j]["start_window_assigned"] = true;
                        data_norm[j]["start_window"] = y + (h/2);
                    }

                    data_norm[j]["end_window"] = y + (h/2);
                }
            }

            y += h;
        }
    },

    // -------------------------------------------------------------------------
    // Zoom
    // -------------------------------------------------------------------------

    ZoomListPush: function(viewer) {
        viewer.zoom.previous.push({
            'position': viewer.position,
            'max_position': viewer.max_position
        });
    },

    ZoomListClear: function(viewer) {
        viewer.zoom.previous = [];
    },

    ZoomListPop: function(viewer) {
        var ret = null;
        if (viewer.zoom.previous.length > 0) {
            ret = viewer.zoom.previous.pop();
        }
        return ret;
    },

    // =========================================================================
    // PUBLIC LISTENERS
    // =========================================================================

    OnInit: function(viewer, canvas, ctx) {
        this.ResetViewerData(viewer, canvas, ctx);
        this.DrawEmptyControl(viewer);
    },

    OnDrawControl: function(viewer) {
        // console.log("OnDrawControl");

        //if (this.ViewerHasData(viewer)) {

            $rootScope.SetWait(true);

            viewer.ctx.save();
                viewer.progressbar.setColor('#00ff00');
                viewer.progressbar.set(0);
                viewer.progressbar.start();

                this.DrawEmptyControl(viewer);
                viewer.progressbar.set(20);

                this.DrawSequences(viewer);      
                viewer.progressbar.set(40);

                this.DrawGeneIds(viewer);
                viewer.progressbar.set(60);

                this.DrawLegend(viewer);
                viewer.progressbar.set(80);
                
                this.DrawStatistics(viewer);

                this.DrawFileNames(viewer);

                viewer.progressbar.complete();
            viewer.ctx.restore();  

            $rootScope.SetWait(false);
        //}
    },

    OnChangePosition: function(viewer) {
        var ret = false;

        // Ensure that position and max_position are integer numbers:
        viewer.position = Math.floor(viewer.position);
        viewer.max_position = Math.floor(viewer.max_position);

        ret =  !((viewer.position == viewer.position_prev) && (viewer.max_position == viewer.max_position_prev));

        if (ret) { // If position has changed
            // console.log("OnChangePosition");
            // Note that althought we have data_tfa.length sequences, we have to draw (max_position - position) sequences.
            // They could be different. data_tfa.length could be a smaller number due to the limitation of sequences in memory.

            // Recalculate sequence height

            var table_height = vcte.DNA_TABLE_HEIGHT - vcte.DNA_TABLE_HEADER_HEIGHT;

            //If 1 seq/s then viewer.seq_height = table_height      also, zoom_h_ = 1 / 1
            //If 2 seq/s then viewer.seq_height = table_height / 2  also, zoom_h_ = 1 / 2
            //If 3 seq/s then viewer.seq_height = table_height / 3  also, zoom_h_ = 1 / 3

            if (viewer.max_position > viewer.position) {
                viewer.seq_height = table_height / (viewer.max_position - viewer.position);
                //zoom_h_ = 1 / (viewer.max_position - viewer.position);
            } else {
                viewer.seq_height = table_height / (viewer.position - viewer.max_position);
                //zoom_h_ = 1 / (viewer.position - viewer.max_position);
            }

            viewer.position_prev = viewer.position;
            viewer.max_position_prev = viewer.max_position;
        }

        return ret;
    },

    OnMouseWheel: function(viewer, evt) {
        // console.log("OnMouseWheel");

        var delta = evt.wheelDelta ? evt.wheelDelta/150 : evt.detail ? -evt.detail : 0;

        if (delta > 0) {
            this.OnViewerMoveUp(viewer);
        } else {
            this.OnViewerMoveDown(viewer);
        }

        evt.preventDefault();     
    },

    IsMouseOverMarginColumn: function(viewer) {
        return ((viewer.mouse.x > vcte.DNA_TABLE_POS_X + viewer.dna_table_width) && (viewer.mouse.x < vcte.DNA_TABLE_POS_X + viewer.dna_table_width + vcte.STATISTICS_MARGIN));
    },

    /*
        returns true if $apply() must be called
    */
    OnMouseMove: function(viewer, evt) {
        // console.log("OnMouseMove");
        var ret = false;

        var data_tfa = viewer.files[vcte.FileType.TFA].data;
        var data_minmax = viewer.files[vcte.FileType.STATS].minmax;

        this.UpdateMousePosition(viewer, evt);

        viewer.information.mouse_over = '';

        if (viewer.start_selection_point != null) {
            //drawing.DrawSelectionRect(viewer.ctx, viewer.mouse.x, viewer.mouse.y, viewer.start_selection_point.x - viewer.mouse.x, viewer.start_selection_point.y - viewer.mouse.y);
        }

        if (data_tfa != null) {
            this.DrawTableHeader(viewer);
            this.DrawStatisticsHeaders(viewer);
            this.DrawFileNames(viewer);

            if (viewer.cell_selected.x >= 0) {
                viewer.information.mouse_over = 'viewer';
                this.GetSelectedGene(viewer);
                this.GetSelectedBase(viewer);
            } else {
                viewer.information.mouse_over = 'stats';
                this.GetSelectedStatsInfo(viewer);
            }

            var y = vcte.DNA_TABLE_POS_Y + vcte.DNA_TABLE_HEADER_HEIGHT;


            var i = 0;
            for(var r = viewer.position; r < viewer.max_position; r++) {
                if ((i < data_tfa.length) && (data_tfa[i].order*1 == r)) {
                    id = data_tfa[i].id;
                    i++;
                } else {
                    // If no ID then show the previous ID. Before: id="";
                }
                this.DrawTableRownCoutColumn(viewer, y, r, id);
                y += viewer.seq_height;
            }
        }

        // Set Mouse Pointer
        if (viewer.mouse.x > vcte.DNA_TABLE_POS_X + viewer.dna_table_width + vcte.STATISTICS_MARGIN + viewer.statistics_width) {
            $rootScope.SetMousePointer($rootScope.MouseOverType.Nothing);
        } else {
            if (this.IsMouseOverMarginColumn(viewer)) {
                $rootScope.SetMousePointer($rootScope.MouseOverType.StatsMargin);
            } else {
                if (viewer.cell_selected.y >= 0) {
                    
                    if (viewer.mouse.x > vcte.DNA_TABLE_POS_X + vcte.TABLE_COLUMN_1_WIDTH + vcte.TABLE_COLUMN_2_WIDTH + vcte.TABLE_COLUMN_3_WIDTH + vcte.TABLE_COLUMN_4_WIDTH) {
                        $rootScope.SetMousePointer($rootScope.MouseOverType.Viewer);
                    } else {
                        $rootScope.SetMousePointer($rootScope.MouseOverType.Gene);
                    }
                } else {
                    $rootScope.SetMousePointer($rootScope.MouseOverType.Nothing);
                }
            }
        }

        if (viewer.information.show == true) {
            this.UpdateMousePosition(viewer, evt);
            angular.element('#mouse_info').css('left', viewer.mouse.x + 20 + 'px');
            angular.element('#mouse_info').css('top',  viewer.mouse.y  + 50 + 'px');
            ret = true;
        }


        if ((viewer.zoom.start != -1) && (viewer.cell_selected.y != -1)) {
            drawing.DrawRect(viewer.ctx,
                             vcte.DNA_TABLE_POS_X + vcte.TABLE_COLUMN_1_WIDTH + vcte.TABLE_COLUMN_2_WIDTH + vcte.TABLE_COLUMN_3_WIDTH,
                             vcte.DNA_TABLE_POS_Y + vcte.DNA_TABLE_HEADER_HEIGHT,
                             vcte.TABLE_COLUMN_4_WIDTH,
                             vcte.DNA_TABLE_HEIGHT - vcte.DNA_TABLE_HEADER_HEIGHT,
                             'white');

            var start_y = (viewer.zoom.start - viewer.position)      * viewer.seq_height;    // zoom.start has the row ID. If it substracts the viewer.position then it has the visible row count
            var end_y   = (viewer.cell_selected.y) * viewer.seq_height;                             // cell_selected.y has the visible row count

            if (start_y < end_y) {
                distance = end_y - start_y;
            } else {
                distance = start_y - end_y;
                start_y = end_y;
            }

            drawing.DrawRect(viewer.ctx,
                             vcte.DNA_TABLE_POS_X + vcte.TABLE_COLUMN_1_WIDTH + vcte.TABLE_COLUMN_2_WIDTH + vcte.TABLE_COLUMN_3_WIDTH,
                             vcte.DNA_TABLE_POS_Y + vcte.DNA_TABLE_HEADER_HEIGHT + start_y,
                             vcte.TABLE_COLUMN_4_WIDTH,
                             distance,
                             'black');
            
        }

        if ($rootScope.col_resizing) {
            this.ResizeColumn(viewer);
        }


        return ret;
    },

    /*
        returns true if $apply() must be called
    */
    OnMouseDown: function(viewer, evt) {
        var ret = false;

        if (viewer.start_selection_point == null) {
            this.UpdateMousePosition(viewer, evt);

            viewer.start_selection_point = {
                x: viewer.mouse.x,
                y: viewer.mouse.y
            };
        }

        if (this.IsMouseOverMarginColumn(viewer)) {
            $rootScope.col_resizing = true;
        }

        if (viewer.information.show == false) {
            if (viewer.cell_selected.y > -1) {
                if (viewer.mouse.x > vcte.DNA_TABLE_POS_X + vcte.TABLE_COLUMN_1_WIDTH + vcte.TABLE_COLUMN_2_WIDTH + vcte.TABLE_COLUMN_3_WIDTH + vcte.TABLE_COLUMN_4_WIDTH) {
                    angular.element('#mouse_info').css('left', viewer.mouse.x + 20 + 'px');
                    angular.element('#mouse_info').css('top',  viewer.mouse.y  + 50 + 'px');
                    viewer.information.show = true;
                    ret = true;
                } else {
                    if ($rootScope.CtrlKeyPressed == false) {
                        if (viewer.zoom.start == -1) {
                            this.ZoomListPush(viewer); // Enlist current zoom position for being able to undo it later
                        }
                        viewer.zoom.start = viewer.position + viewer.cell_selected.y;
                    } else {
                        viewer.zoom.unzooming = true;
                    }
                }
            }
        }

        return ret;
    },

    /*
        returns true if $apply() must be called
    */
    OnMouseUp: function(viewer, evt) {
        var ret = false;

        this.UpdateMousePosition(viewer, evt);

        viewer.start_selection_point = null;


        if ($rootScope.col_resizing) {
            $rootScope.col_resizing = false;
            $rootScope.SetMousePointer($rootScope.MouseOverType.Previous);
            this.ResizeColumn(viewer);
        }

        if (viewer.zoom.start != -1) {
            if (viewer.cell_selected.y != -1) { // it could be -1 if the mouse is out of the canvas,...
                var end = viewer.position + viewer.cell_selected.y;

                if (end != viewer.zoom.start) {

                    if (end > viewer.zoom.start) {
                        viewer.max_position = end;
                        viewer.position     = viewer.zoom.start;
                    } else {
                        viewer.position     = end;
                        viewer.max_position = viewer.zoom.start;
                    }
                    viewer.zoom.start = -1;

                    this.OnChangeSliderRange(viewer);
                }
            }

            viewer.zoom.start = -1;
        }

        if (viewer.information.show == true) {
            viewer.information.show = false;
            ret = true;
        }

        if (viewer.zoom.unzooming == true) {
            viewer.zoom.unzooming = false;

            var pos = this.ZoomListPop(viewer);
            if (pos != null) {
                viewer.position = pos.position;
                viewer.max_position = pos.max_position;
            }
        }

        return ret;
    },

    OnChangeViewType: function(viewer, new_view_type) {
        // console.log("OnChangeViewType");

        viewer.view_type = new_view_type;
        this.OnDrawControl(viewer);
    },

    OnClose: function(viewer) {
        // console.log("OnClose");
        var transaction_id = viewer.transactions.last_transaction_id++;
        dao.CloseServerFile(transaction_id, function(transaction_id, data){ }, function(transaction_id){});
        viewer.transactions.last_transaction_id++;

        var canvas = viewer.canvas;
        var ctx = viewer.ctx;
        this.ResetViewerData(viewer, canvas, ctx);
        this.DrawEmptyControl(viewer);
    },

    OnChangeSliderRange: function(viewer) {
        //console.log("OnChangeSliderRange");

        if (this.OnChangePosition(viewer) == true) {
            // if position changed to a different position, then:
            this.LoadFiles(viewer, false);
        }
    },

    OnViewerMoveUp: function(viewer) {
        var step = ((viewer.max_position - viewer.position) / 10); //10%

        if (viewer.position - step < 0) {
            step = viewer.position;
        }

        if (step < 1) { step = 1; }

        viewer.position -= step;
        viewer.max_position -= step;

        if (viewer.position < 0) {
            viewer.max_position += viewer.position * (-1);
            viewer.position = 0;
        }

//      if (step != 0) {
        this.OnChangeSliderRange(viewer);
//      }
    },

    OnViewerMoveDown: function(viewer) {
        var step = ((viewer.max_position - viewer.position) / 10); //10%

        if (viewer.max_position + step > viewer.files[vcte.FileType.TFA].items) {
            step = viewer.files[vcte.FileType.TFA].items - viewer.max_position;
        }

        if (step < 1) { step = 1; }

        viewer.position += step;
        viewer.max_position += step;

        if (viewer.max_position > viewer.files[vcte.FileType.TFA].items) {
            viewer.position -= viewer.max_position - viewer.files[vcte.FileType.TFA].items;
            viewer.max_position = viewer.files[vcte.FileType.TFA].items;
        }

//      if (step != 0) {
        this.OnChangeSliderRange(viewer);
//      }
    }


  } // end of return

});

