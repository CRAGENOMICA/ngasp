CRAG.factory('dao', function ($http) {
  return {

    GetTFAData: function(transaction_id, viewer, file_type, first_sequence, num_of_sequences, parent, OnError) {
        $http({
            method: 'POST',
            url: 'sequences',
            headers: { 'Content-Type': 'application/json' },
            params: { },
            data: { "transaction_id":transaction_id, "file_name":viewer.files[file_type].file_name, "start": first_sequence, "step": num_of_sequences }, // All file content if start and step are -1
        })
        .then(function(data){parent.DataReceived(transaction_id, viewer, file_type, data);}, function(){OnError(transaction_id)});
    },

    GetGFF: function(transaction_id, viewer, file_type, parent, OnError) {
        $http({
            method: 'POST',
            url: 'gff',
            headers: { 'Content-Type': 'application/json' },
            params: { },
            data: { "transaction_id":transaction_id, "file_name": viewer.files[file_type].file_name },
        })
        .then(function(data){parent.DataReceived(transaction_id, viewer, file_type, data);}, function(){OnError(transaction_id)});
    },

    GetWeights: function(transaction_id, viewer, file_type, parent, OnError) {
        $http({
            method: 'POST',
            url: 'weights',
            headers: { 'Content-Type': 'application/json' },
            params: { },
            data: { "transaction_id":transaction_id, "file_name": viewer.files[file_type].file_name },
        })
        .then(function(data){parent.DataReceived(transaction_id, viewer, file_type, data);}, function(){OnError(transaction_id)});
    },

    GetStatistics: function(transaction_id, viewer, file_type, parent, OnError) {
        $http({
            method: 'POST',
            url: 'statistics',
            headers: { 'Content-Type': 'application/json' },
            params: { },
            data: { "transaction_id":transaction_id, "file_name": viewer.files[file_type].file_name },
        })
        .then(function(data){parent.DataReceived(transaction_id, viewer, file_type, data);}, function(){OnError(transaction_id)});
    },

    CloseServerFile: function(transaction_id, OnOk, OnError) {
        $http({
                method: 'DELETE',
                url: 'close',
                headers: { 'Content-Type': 'application/json' },
                params: { },
                data: { "transaction_id":transaction_id },
        })
        .then(function(data){OnOk(transaction_id, data);}, function(){OnError(transaction_id)});
    }

  };
});

