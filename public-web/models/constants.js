/// ---------------------------------------------------------------------------
/// @file constants.js
/// @namespace ngaSP
/// Module description
/// ---------------------------------------------------------------------------

module.exports = function() {
// ============================================================================
// CONSTANTS: SERVER
// ============================================================================

	this.HOST 						     = function() { return "127.0.0.1"; };
	this.PORT_WEB 					   = function() { return 3000; };
	this.PORT_CM 					     = function() { return 6969; };
	this.PUBLIC_FOLDER 				 = function() { return "/public"; };
};

