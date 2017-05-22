CRAG.factory('drawing', function ($rootScope) {
  return {
    ClearCanvas: function(ctx, width, height, color) {
        ctx.save();

        ctx.fillStyle = color;
        ctx.fillRect(0, 0, width, height);

        ctx.restore();
    },

    DrawRect: function(ctx, x, y, w, h, color, stroke) {
        ctx.beginPath();
        ctx.moveTo(x, y);
        ctx.lineTo(x + w, y);
        ctx.lineTo(x + w, y + h);
        ctx.lineTo(x, y + h);
        ctx.closePath();

        if (color != null) {
            ctx.fillStyle = color;
            ctx.fill();
        }

        if (stroke != undefined) {
            ctx.strokeStyle = stroke;
            ctx.lineWidth = 1;
            ctx.stroke();
        }
    },

    DrawSelectionRect: function(ctx, x, y, w, h) {
        /*
        ctx.beginPath();
        ctx.moveTo(x, y);
        ctx.lineTo(x + w, y);
        ctx.lineTo(x + w, y + h);
        ctx.lineTo(x, y + h);
        ctx.closePath();

        ctx.lineWidth = 1;
        ctx.strokeStyle = color;
        ctx.stroke();
        */

        var idata = ctx.getImageData(x, y, w, h),
            buffer = idata.data,
            len = buffer.length,
            i = 0;
        for(; i < len; i += 4) {
            buffer[i] = 255 - buffer[i];
            buffer[i+1] = 255 - buffer[i+1];
            buffer[i+2] = 255 - buffer[i+2];
        }
        ctx.putImageData(idata, 0, 0);
    },


    DrawCircle: function(ctx, x, y, radius, color, line_color, line_size) {
        ctx.beginPath();
        ctx.arc(x, y, radius, 0, 2 * Math.PI, false);
        ctx.fillStyle = color;
        ctx.fill();

        if ((line_color != undefined) && (line_size != undefined)) {
            ctx.lineWidth = line_size;
            ctx.strokeStyle = line_color;
            ctx.stroke();
        }
    }

  };
});

