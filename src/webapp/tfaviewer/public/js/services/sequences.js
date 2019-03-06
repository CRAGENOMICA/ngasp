CRAG.factory('sequences', function ($http) {
  return {

    GetFrequencies: function(seq) {
        var ret = { A:0, T:0, C:0, G:0, N:0, O:0 };

        for (var i = 0; i < seq.length; i++) {
            if (seq[i] == 'A') { ret.A++; } else {
            if (seq[i] == 'T') { ret.T++; } else {
            if (seq[i] == 'C') { ret.C++; } else {
            if (seq[i] == 'G') { ret.G++; } else {
            if (seq[i] == 'N') { ret.N++; } else { ret.O++; }}}}}
        }

        return ret;
    },


    // This function returns the base (A/T/C/G) with max frequency
    GetMaxFrequencyBase: function(count) {
        var retb = 'N';
        var retc = 0;

        if (count.A > retc) { retc = count.A; retb = 'A'; }
        if (count.T > retc) { retc = count.T; retb = 'T'; }
        if (count.C > retc) { retc = count.C; retb = 'C'; }
        if (count.G > retc) { retc = count.G; retb = 'G'; }

        return retb;
    }

  };
});

