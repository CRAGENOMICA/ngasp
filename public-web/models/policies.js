/// ---------------------------------------------------------------------------
/// @file policies.js
/// @namespace ngaSP
/// Module description
/// ---------------------------------------------------------------------------

// ============================================================================
// EXPORT
// ============================================================================

module.exports = {
	DisableSameOrigin: function(app) {
		// Disable Same-domain policy:
		// To avoid error: No 'Access-Control-Allow-Origin' header is present on the requested resource.
		app.use(function(req, res, next) {
		  res.header("Access-Control-Allow-Origin", "*");
		  res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
		  next();
		});
	},
	
	EnableMethods: function(app, methods) {
		// Example: "GET, POST, PUT, DELETE, OPTIONS"
		// To avoid error: Method PUT is not allowed by Access-Control-Allow-Methods
		app.use(function(req, res, next) {
		  res.header("Access-Control-Allow-Methods", methods);
		  next();
		});
	}
};

