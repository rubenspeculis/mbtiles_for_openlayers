
/**
 * @file
 * Layer handler for Mbtiles layers
 */

/**
 * Openlayer layer handler for Mbtiles layer
 */
Drupal.openlayers.layer.mbtiles = function(title, map, options) {
  if (OpenLayers.Util.isArray(options.maxExtent)) {
    options.maxExtent = OpenLayers.Bounds.fromArray(options.maxExtent);
  }

  if (options.inverse == true) {
    options.getURL = function(bounds) {
      var res = this.map.getResolution();
      var x = Math.round((bounds.left - this.maxExtent.left) / (res * this.tileSize.w));
      var y = Math.round((bounds.bottom - this.tileOrigin.lat) / (res * this.tileSize.h));
      var z = this.map.getZoom();

	    var ymax = 1 << z;
      y = ymax - y - 1;

      return this.url + this.layername + "/" + z + "/" + x + "/" + y + "." + this.type;
    }
  }
  options.projection = new OpenLayers.Projection(options.projection);
  return new OpenLayers.Layer.TMS(title, options.url, options);
};
