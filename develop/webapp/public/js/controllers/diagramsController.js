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
CRAG.controller('DiagramsController', function($scope, $rootScope, logs, docs) {

    var interval_work = null;

	$scope.init = function () {
        $rootScope.ActivateLoading();
        interval_work = setInterval($scope.Start, 100);
    };

	var theme = "simple"; // 'simple' / 'hand'
	var EOL = "\n";

	function CreateDiagram(title, text, div_num) {

		/*
		var iLabel = document.createElement('label');
		iLabel.id = 'label' + div_num;
		iLabel.innerHTML = title;
		iLabel.className = 'diagram_title';
		document.getElementById('diagrams').appendChild(iLabel);
		*/

    if (document.getElementById('diagrams') != null) {
		  var iDiv = document.createElement('div');
		  iDiv.id = 'diagram' + div_num;
		  iDiv.className = 'diagram';
		  document.getElementById('diagrams').appendChild(iDiv);

		  var br1 = document.createElement("br");
		  document.getElementById('diagrams').appendChild(br1);

		  text = "Title: " + title + EOL + text;
		  var diagram = Diagram.parse(text);
		  diagram.drawSVG("diagram" + div_num, {theme: theme});
    }
	};

	$scope.Start = function () {
    clearInterval(interval_work);

		/*document.body.style.backgroundColor = "white";*/

		var div_num = 1;

    if ($rootScope.selected_case_id == null) {
      for (var i = 0; i < $rootScope.traceability_matrix.length; i++) {
        var use_case = $rootScope.traceability_matrix[i];
        div_num = DrawDiagram(use_case.id, use_case.name, div_num);
      }
    } else {
      div_num = DrawDiagram($rootScope.selected_case_id, $rootScope.selected_case_title, div_num);
    }



    $rootScope.StopLoading();
    $scope.$apply();
	};

  function DrawDiagram(id, title, div_num) {
    if (id == 'BUS-GEN-003') {
      var title = title;
		  var text = 
                 "Jenkins->Git:GetSourceCode()" + EOL +
                 "Git-->Jenkins:SourceCode" + EOL +

                 "Jenkins->Sonar:AnalyzeSourceCode(SourceCode)" + EOL +
                 "Sonar-->Jenkins:Analysis" + EOL +

                 "Jenkins->Gradle:Build()" + EOL +
                 "Gradle-->Jenkins:Binary" + EOL +

                 "Jenkins->Gradle:RunTests()" + EOL +
                 "Gradle-->Jenkins:TestResult" + EOL +

                 "Jenkins->Gradle:CreatePackage()" + EOL +
                 "Gradle-->Jenkins:Package" + EOL +

		  ""; CreateDiagram(title, text, div_num++);
    }

    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
  	  var title = "System: Connection Types";
		  var text = "User (HTML View)->Controller (JS): Client Javascript" + EOL +
				     "Controller (JS)->NodeJs (JS): http RESTfull with JSON" + EOL +
				     "NodeJs (JS)->CentralManager (JS): Server Javascript (response socket)" + EOL +
				     "CentralManager (JS)->LocalManager (ngaSP C++): net.io socket JSON" + EOL +
				     "LocalManager (ngaSP C++)->Experiment (ngaSP C++ MultiThreading): Named Pipe To Experiment" + EOL +
				     "Experiment (ngaSP C++ MultiThreading)->LocalManager (ngaSP C++): Named Pipe From Experiment" + EOL +
				     "LocalManager (ngaSP C++)-->CentralManager (JS): same net.io socket JSON" + EOL +
				     "CentralManager (JS)-->Controller (JS): http RESTfull with JSON (response socket)" + EOL +
				     "CentralManager (JS)->Controller (JS): http RESTfull with JSON (permanent socket)";
		  CreateDiagram(title, text, div_num++);
	  }

    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
  	  var title = "Server: Start Up";
		  var text = "NodeJs->CentralManager: Start()" + EOL +
				     "CentralManager->CentralManager: createServer()" + EOL +
				     "CentralManager->CentralManager: Start Event: ReceiveMensagesFromLocalManagers()" + EOL +
				     "CentralManager->CMTimer: Start Automatic Task: interval_update_LMList = setInterval(AutomaticRequestOfLocalManagersList)";
		  CreateDiagram(title, text, div_num++);
    }

    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
      var title = "Client Browser: Connection with the Central Manager";
		  var text = "MainWebController->NodeJs: io.on('connection'(socket))" + EOL +
				     "NodeJs->CentralManager: client_socket = SetClientSocket(socket)" + EOL +
   					   "MainWebController->NodeJs: io.sockets.on('connect'(client))" + EOL +
   					   "NodeJs->CentralManager: AddClient(client)" + EOL +
				     "CentralManager->MainWebController: [All Clients]NotifyRefreshRequired('CLIENTS_LIST')" + EOL +
                        "";
		  CreateDiagram(title, text, div_num++);
    }
    
    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
      var title = "Client Browser: Disconnection from the Central Manager";
		  var text = "MainWebController->NodeJs: io.sockets.on('disconnect'(client))" + EOL +
   					   "NodeJs->CentralManager: RemoveClient(client)" + EOL +
				     "CentralManager->MainWebController: [All Clients]NotifyRefreshRequired('CLIENTS_LIST')" + EOL +
                        "";
		  CreateDiagram(title, text, div_num++);
    }
          
    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
  	  var title = "Local Manager: Enroll";
		  var text = "LocalManager->CentralManager: SendMsgToCentralManagerNetSocket('HELLO', capabilities)" + EOL +
				     "CentralManager->CentralManager: lm_id = GenerateRandomId(5)" + EOL +
				     "CentralManager->CentralManager: EnlistNewLocalManager(lm_id, address, socket, capabilities)" + EOL +
				     "CentralManager->LocalManager: SendMsgToLocalManagerNetSocket('HELLO', lm_id)" + EOL +
				     "LocalManager->LocalManager: SaveOwnLocalManagerId(lm_id)" + EOL +
				     "CentralManager->MainWebController: NotifyRefreshRequired('LM_LIST|EXPERIMENTS_LIST')" + EOL +
				     "MainWebController->MainWebController: socket.on('REFRESH_REQUIRED')" + EOL +
				     "Note over MainWebController: OnRefreshLocalManagersList()" + EOL +
				     "Note over MainWebController: OnRefreshExperimentsList()";
		  CreateDiagram(title, text, div_num++);
    }
    
    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
      var title = "Use Case: Create Experiment";
		  var text = "User->ExperimentsController: $scope.OnCreateExperiment(experiment_name)" + EOL +
				     "ExperimentsController->NodeJs: $http.post('/experiments', experiment_name)" + EOL +
				     "NodeJs->CentralManager: RequestCreateExperiment(response_id, experiment_name)" + EOL +
				     "CentralManager->CentralManager: experiment_id = GetNextExperimentId()" + EOL +
				     "CentralManager->CentralManager: EnlistNewExperiment(experiment_id, experiment_name)" + EOL +
				     "CentralManager-->ExperimentsController: ResponseRequestOK(response_id, experiment_id)" + EOL +
				     "Note over ExperimentsController: OnRefreshExperimentsList()" + EOL +
				     "CentralManager-->ExperimentsController: ResponseRequestError(response_id)";
		  CreateDiagram(title, text, div_num++);
    }
    
    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
  		var title = "Use Case: Execute Command";
		  var text = "User->ExperimentsController: $scope.OnExecuteCommand(experiment_id, cmd)" + EOL +
				     "ExperimentsController->NodeJs: $http.put('/experiments/{experiment_id}', cmd)" + EOL +
				     "NodeJs->CentralManager: RequestExecuteCommand(response_id, experiment_id, cmd)" + EOL +
				     "CentralManager->CentralManager: lm = GetLocalManagerByExperimentId(experiment_id)" + EOL +
				     "CentralManager->CentralManager: if (lm is null) AssignLessUsedLocalManagerToExperiment(experiment_id)" + EOL +
				     "CentralManager-->ExperimentsController: if (lm is still null) ResponseRequestError(response_id) and End" + EOL +
				     "CentralManager->ExperimentsController: if (lm assigned) NotifyRefreshRequired('EXPERIMENTS_LIST')" + EOL +
				     "ExperimentsController->ExperimentsController: socket.on('REFRESH_REQUIRED')" + EOL +
				     "Note over ExperimentsController: OnRefreshExperimentsList()" + EOL +
				     "CentralManager->LocalManager: SendMsgToLocalManagerNetSocket(lm,'RUN', experiment_id, cmd)" + EOL +
				     "LocalManager->LocalManager: ExecuteCommand(experiment_id, cmd)" + EOL +
				     "LocalManager->LocalManager: experiment = FindExperimentById(experiment_id)" + EOL +
				     "LocalManager->Experiment: If experiment is null: Execute new and Enlist it" + EOL +
                       "Note over LocalManager: See 'Change in the Experiments List'" + EOL +
				     "Experiment->Experiment: WaitMessageFromLocalManager()" + EOL +
				     "LocalManager->Experiment: SendPipeMessageToExperiment('RUN', cmd)" + EOL +
				     "LocalManager->LocalManager: WaitMessageFromExperiment()" + EOL +
				     "Experiment->Experiment: CController.pushInstruction(cmd)" + EOL +
				     "Experiment->LocalManager: SendPipeMessageToLocalManager('OK')" + EOL +
				     "LocalManager->CentralManager: SendMsgToCentralManagerNetSocket('RUN', experiment_id, cmd, 'OK')" + EOL +
				     "CentralManager->CentralManager: socket.on('data') 'RUN'" + EOL +
				     "CentralManager-->ExperimentsController: ResponseRequestOK(response_id)" + EOL +
				     "Note over ExperimentsController: OnGetOutput()" + EOL +
				     "CentralManager-->ExperimentsController: ResponseRequestError(response_id)";
		  CreateDiagram(title, text, div_num++);
    }
    
    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
  		var title = "Use Case: Get Experiment Output";
		  var text = "User->ExperimentsController: $scope.OnGetOutput(experiment_id)" + EOL +
				     "ExperimentsController->NodeJs: $http.get('/experiments/{experiment_id}')" + EOL +
				     "NodeJs->CentralManager: RequestExperimentOutput(response_id, experiment_id)" + EOL +
				     "CentralManager->CentralManager: lm = GetLocalManagerByExperimentId(experiment_id)" + EOL +
				     "CentralManager->LocalManager: SendMsgToLocalManagerNetSocket(lm,'GET_EXPERIMENT_RESULT', experiment_id)" + EOL +
				     "LocalManager->LocalManager: GetExperimentResult(experiment_id)" + EOL +
				     "LocalManager->LocalManager: experiment = FindExperimentById(experiment_id)" + EOL +
				     "Experiment->Experiment: WaitMessageFromLocalManager()" + EOL +
				     "LocalManager->Experiment: SendPipeMessageToExperiment('SAVE_COUT_FILE')" + EOL +
				     "LocalManager->LocalManager: WaitMessageFromExperiment()" + EOL +
	    			   "Experiment->Logger: WriteCoutFile()" + EOL +
				     "Logger->ExperimentOutputFile: Write()" + EOL +
				     "Experiment->LocalManager: SendPipeMessageToLocalManager('OK')" + EOL +
				     "LocalManager->ExperimentOutputFile: Read()" + EOL +
				     "ExperimentOutputFile-->LocalManager: data" + EOL +
				     "LocalManager->CentralManager: SendMsgToCentralManagerNetSocket('GET_EXPERIMENT_RESULT', experiment_id, data)" + EOL +
				     "CentralManager->CentralManager: socket.on('data') 'GET_EXPERIMENT_RESULT'" + EOL +
				     "CentralManager-->ExperimentsController: ResponseRequestOK(response_id, data)" + EOL +
				     "CentralManager-->ExperimentsController: ResponseRequestError(response_id)";
		  CreateDiagram(title, text, div_num++);
    }
    
    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
  		var title = "Use Case: Clean Experiment Output";
		  var text = "User->ExperimentsController: $scope.OnCleanOutput(experiment_id)" + EOL +
				     "ExperimentsController->NodeJs: $http.delete('/experiments/{experiment_id}')" + EOL +
				     "NodeJs->CentralManager: RequestCleanExperimentOutput(response_id, experiment_id)" + EOL +
				     "CentralManager->CentralManager: lm=GetLocalManagerByExperimentId(experiment_id)" + EOL + 
				     "CentralManager->LocalManager: SendMsgToLocalManagerNetSocket(lm,'CLEAN_EXPERIMENT_RESULT', experiment_id)" + EOL +
				     "LocalManager->LocalManager: CleanExperimentResult(experiment_id)" + EOL +
				     "LocalManager->LocalManager: experiment = FindExperimentById(experiment_id)" + EOL +
				     "Experiment->Experiment: WaitMessageFromLocalManager()" + EOL +
				     "LocalManager->Experiment: SendPipeMessageToExperiment('CLEAN_EXPERIMENT_RESULT')" + EOL +
				     "LocalManager->LocalManager: WaitMessageFromExperiment()" + EOL +
				     "Experiment->ExperimentOutputFile: Remove file" + EOL +
				     "Experiment->LocalManager: SendPipeMessageToLocalManager('OK')" + EOL +
				     "LocalManager->CentralManager: SendMsgToCentralManagerNetSocket('CLEAN_EXPERIMENT_RESULT', experiment_id, 'OK')" + EOL +
				     "CentralManager-->ExperimentsController: ResponseRequestOK(response_id)" + EOL +
				     "CentralManager-->ExperimentsController: ResponseRequestError(response_id)";
		  CreateDiagram(title, text, div_num++);
    }
    
    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
  		var title = "Use Case: Close Experiment";
		  var text = "User->ExperimentsController: $scope.OnExecuteCommand(experiment_id, 'exit')" + EOL +
				     "Note over User: See 'Execute Command'" + EOL +
                       "Experiment->Experiment: On Exit: ClosePipes()";
		  CreateDiagram(title, text, div_num++);
    }
    
    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
  		var title = "Use Case: Refresh Local Managers List By User Request";
		  var text = "User->MainWebController: $scope.OnRefreshLocalManagersList()" + EOL +
				     "MainWebController->NodeJs: $http.get('/localmanagers')" + EOL +
				     "NodeJs->CentralManager: RequestLocalManagersList(response_id)" + EOL +
				     "CentralManager->CentralManager: exported_list = ExportLocalManagersList()" + EOL +
				     "CentralManager-->MainWebController: ResponseRequestOK(response_id, exported_list)" + EOL +
				     "CentralManager-->MainWebController: ResponseRequestError(response_id)";
		  CreateDiagram(title, text, div_num++);
    }
    
    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
  		var title = "Use Case: Refresh Experiments List By User Request";
		  var text = "User->MainWebController: $scope.OnRefreshExperimentsList()" + EOL +
				     "MainWebController->NodeJs: $http.get('/experiments')" + EOL +
				     "NodeJs->CentralManager: RequestExperimentsList(response_id)" + EOL +
				     "CentralManager->CentralManager: exported_list = ExportExperimentsList()" + EOL +
				     "CentralManager-->MainWebController: ResponseRequestOK(response_id, exported_list)" + EOL +
				     "CentralManager-->MainWebController: ResponseRequestError(response_id)";
		  CreateDiagram(title, text, div_num++);
    }
    
    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
  		var title = "Use Case: Close Server";
		  var text = "User->NetworkController: $scope.OnCloseServer()" + EOL +
				     "NetworkController->NodeJs: $http.delete('/servers')" + EOL +
				     "NodeJs->CentralManager: RequestCloseServer(response_id, server)" + EOL +
				     "CentralManager->CMTimer: clearInterval(interval_update_LMList)" + EOL +
				     "CentralManager->LocalManager: [ALL] SendMsgToLocalManagerNetSocket(lm,'CLOSE')" + EOL +
				     "LocalManager->LocalManager: [ALL] experiment = FindExperimentById(experiment_id)" + EOL +
				     "LocalManager->Experiment: SendPipeMessageToExperiment('RUN', 'exit')" + EOL +
				     "Note over Experiment: Closed" + EOL +
				     "Note over LocalManager: Closed" + EOL +
				     "CentralManager->CentralManager: Wait all LM are state = 'CLOSE_LM'" + EOL +
				     "CentralManager-->NetworkController: ResponseRequestOK(response_id, 'OK')";
		  CreateDiagram(title, text, div_num++);
    }
    
    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
  		var title = "(Esborrar) Update Net Nodes (treure el timer)";
		  var text = "CMTimer->CentralManager: AutomaticRequestOfLocalManagersList()";
		  CreateDiagram(title, text, div_num++);

		  var title = "Central Manager: Check Local Manager Status";
		  var text = "CMTimer->CentralManager: CheckAllLocalManagersStatus()" + EOL +

				     "CentralManager->CentralManager: [ALL] lm = GetLocalManagerById(experiment_id)" + EOL +
				     "CentralManager->CentralManager: If previous lm.status = '...' then, lm.status = 'CONNECTION_LOST' " + EOL +
				     "CentralManager->CentralManager: Else lm.status = '...'" + EOL +
				     "CentralManager->LocalManager: [ALL] SendMsgToLocalManagerNetSocket('STATUS')" + EOL +
				     "LocalManager->LocalManager: GetOwnStatus()" + EOL +
				     "LocalManager->CentralManager: SendMsgToCentralManagerNetSocket('STATUS', 'OK')" + EOL +
				     "CentralManager->MainWebController: On some new 'CONNECTION_LOST' then, NotifyRefreshRequired('LM_LIST')" + EOL
		  "";
		  CreateDiagram(title, text, div_num++);
    }
    
    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
  		var title = "Local Manager: Check Experiments Status";
		  var text = "LMTimer->LocalManager: CheckAllExperimentsStatus()" + EOL +
			         "Experiment->Experiment: WaitMessageFromLocalManager()" + EOL +
				     "LocalManager->LocalManager: [ALL] experiment = GetExperimentById(1..n)" + EOL +
				     "LocalManager->LocalManager: If experiment pipe is not active (cause the binary is closed) then, experiment.status = 'CLOSED' " + EOL +
				     "LocalManager->LocalManager: If previous experiment.status = '...' then, experiment.status = 'CONNECTION_LOST' " + EOL +
				     "LocalManager->LocalManager: Else experiment.status = '...'" + EOL +
				     "LocalManager->Experiment: SendPipeMessageToExperiment('STATUS')" + EOL +
				     "LocalManager->LocalManager: WaitMessageFromExperiment()" + EOL +
			         "Experiment->Experiment: GetOwnStatus()" + EOL +
	   			   "Experiment->LocalManager: If currentInstruction is Null then SendPipeMessageToLocalManager(status) ['OPEN']" + EOL +
	   			   "Experiment->LocalManager: If currentInstruction is Not Null then SendPipeMessageToLocalManager(status) ['WORKING']" + EOL +
				     "LocalManager->LocalManager: UpdateExperiment" + EOL +
                       "Note over LocalManager: See 'Change in the Experiments List'" + EOL +
		  "";
		  CreateDiagram(title, text, div_num++);
    }
    
    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
  		var title = "Local Manager: Change in the Experiments List";
		  var text = "LocalManager->CentralManager: If ExperimentsList has changed: SendMsgToCMNetSocket(lm_id, 'EXPERIMENTS_LIST', experiments_list)" + EOL +
				     "CentralManager->CentralManager: Update Experiments List" + EOL +
				     "CentralManager->MainWebController: [BroadCast] NotifyRefreshRequired('EXPERIMENTS_LIST')" + EOL +
                       "Note over MainWebController: OnRefreshExperimentsList()";
		  CreateDiagram(title, text, div_num++);
    }
    
    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
  		var title = "Local Manager: Ensure Enrollment";
		  var text = "LMTimer->LocalManager: EnsureEnrollment()" + EOL +
				     "LocalManager->CentralManager: SendMsgToCentralManagerNetSocket('STILL_HERE', capabilities, lm_id)" + EOL +
				     "Note over CentralManager: On local_manager in state 'CONNECTION_LOST' then:" + EOL +
				     "CentralManager->CentralManager: ReconnectLocalManager(lm_id, address, socket, capabilities)" + EOL +
				     "CentralManager->MainWebController: NotifyRefreshRequired('LM_LIST|EXPERIMENTS_LIST')" + EOL +
				     "MainWebController->MainWebController: socket.on('REFRESH_REQUIRED')" + EOL +
				     "Note over MainWebController: OnRefreshLocalManagersList()" + EOL +
				     "Note over MainWebController: OnRefreshExperimentsList()";
		  CreateDiagram(title, text, div_num++);
    }

	  if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
  	  var title = "Master Tasks";
  	  var text = 
                 "Note over Master: INIT ENGINE" + EOL +
                 "Note over Master: INIT GLOBAL DM" + EOL +
                 "Note over Master: INIT CREATE WORKERS" + EOL +
                 "Note over Master: WAIT ALL WORKERS TO BE READY" + EOL +
                 "Note over Master: WAIT CM INSTRUCTIONS" + EOL +
                 "Note over Master: SELECT WORKER TO EXECUTE CALCULATION" + EOL +
		  ""; CreateDiagram(title, text, div_num++);
    }

    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
      var title = "Master - Init Engine";
		  var text = 
                 "Master->Master: InitEngine()" + EOL +
		  ""; CreateDiagram(title, text, div_num++);
    }

    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
      var title = "Master - Init Global DM";
		  var text = 
                 "Master->Master: InitGlobalDataManager()" + EOL +
		  ""; CreateDiagram(title, text, div_num++);
    }

    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 999)) {
      var title = "Master - Create Workers";
		  var text = 
                 "Master->Worker: CreateWorker()" + EOL +
                 "Master->Master: WaitAllWorkers()" + EOL +
                 "Worker-->Master: Ready(worker_id)" + EOL +
                 "Master-->WorkersList: Enlist(worker_id)" + EOL +
		  ""; CreateDiagram(title, text, div_num++);
    }

    if (($rootScope.selected_case_id == null) || ($rootScope.selected_case_id == 1)) {
      var title = "The Master selects a worker to execute a calculation";
		  var text = 
                 "Master->Master: WaitForFreeWorker()" + EOL +
                 "WorkersList-->Master: worker_id" + EOL +
                 "Master->Worker: ExecuteStep(worker_id, calc_id, inputs, outputs)" + EOL +
                 "Master->Master: WaitWorkerTask()" + EOL +
                 "Worker->Worker: DoTask()" + EOL +
                 "Worker-->Master: SendResult(result)" + EOL +
                 "Master->WorkersList: SetFreeWorker(worker_id)" + EOL +
		  ""; CreateDiagram(title, text, div_num++);
    }

    return div_num;
  };

	$scope.init();
});


