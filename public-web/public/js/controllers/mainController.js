CRAG.controller('MainController', function($scope, $rootScope, $http, $state, $window) {

  $scope.debug = "hola";
  $scope.customer_description = "Center for Research in Agricultural Genomics.";

  $scope.menu = [
    {
      state: 'home',
      menu_title: '',
      page_title: '',
      inside_menu: 'home'
    },
    {
      state: 'how_to_use',
      menu_title: 'Get Started',
      page_title: 'How To Get Started With ngasp',
      inside_menu: 'software'
    },
    {
      state: 'downloads',
      menu_title: 'Downloads',
      page_title: 'Downloads',
      inside_menu: 'software'
    },
    {
      state: 'commands',
      menu_title: 'Commands',
      page_title: 'Commands',
      inside_menu: 'docs'
    },
    {
      state: 'calculations',
      menu_title: 'Calculations',
      page_title: 'Calculations',
      inside_menu: 'docs'
    },
    {
      state: 'mstatspop',
      menu_title: 'Commands > mstatspop',
      page_title: 'Commands > mstatspop',
      inside_menu: 'docs'
    },
    {
      state: 'examples',
      menu_title: 'Command Line Execution Samples',
      page_title: 'Command Line Execution Samples',
      inside_menu: 'docs'
    },
    {
      state: 'pipeline',
      menu_title: 'Pipeline',
      page_title: 'Pipeline',
      inside_menu: 'docs'
    },
    {
      state: 'captures',
      menu_title: 'Demo & Screenshots',
      page_title: 'Demo & Screenshots',
      inside_menu: 'docs'
    },
    {
      state: 'project',
      menu_title: 'The Project',
      page_title: 'The Project',
      inside_menu: 'about'
    },
    {
      state: 'team',
      menu_title: 'The Team',
      page_title: 'The Team',
      inside_menu: 'about'
    }     
  ];


  // https://perishablepress.com/best-method-for-email-obfuscation/

  $scope.GetEmailName = function(email) {
    return email.substring(0, email.lastIndexOf("@"));
  }

  $scope.GetEmailDomain = function(email) {
    return email.substring(email.lastIndexOf("@") +1, email.lastIndexOf("."));
  }

  $scope.GetEmailExtension = function(email) {
    return email.substr(email.lastIndexOf("."));
  }



  $scope.team = [
    {
      name: 'Dr. Sebastián E. Ramos-Onsins',
      title: 'Principal Investigator',
      program: 'Plant and Animal Genomics Program',
      where: 'Centre for Research in Agricultural Genomics (CRAG)',
      dept: '',
      group: '',
      room: '',
      adress: 'Campus UAB - Edifici CRAG | 08193 Bellaterra | Barcelona',
      country: 'Spain',
      email: 'sebastian.ramos@cragenomica.es',
      picture: 'sebas.jpg'
    },
    {
      name: 'Dr. Gonzalo Vera',
      title: 'Head of Scientific IT',
      program: '',
      where: 'Centre for Research in Agricultural Genomics (CRAG)',
      dept: 'Bioinformatics Core Unit',
      group: '',
      room: '',
      adress: 'Campus UAB - Edifici CRAG | 08193 Bellaterra | Barcelona',
      country: 'Spain',
      email: 'gonzalo.vera@cragenomica.es',
      picture: 'gonzalo.jpg'
    },    
    {
      name: 'Joan Jené',
      title: 'Lead Programmer of ngasp Project',
      program: 'Plant and Animal Genomics Program',
      where: 'Centre for Research in Agricultural Genomics (CRAG)',
      dept: '',
      group: '',
      room: '',
      adress: 'Campus UAB - Edifici CRAG | 08193 Bellaterra | Barcelona',
      country: 'Spain',
      email: 'joan.jene@cragenomica.es',
      picture: 'joan.jpg'
    },
    {
      name: 'Dr. Porfidio Hernández Budé',
      title: 'Research Collaborator',
      program: '',
      where: 'Universitat Autònoma de Barcelona',
      dept: 'Computer Science (ETSE)',
      group: 'Computer Architecture and Operating System Department',
      room: '',
      adress: 'Campus UAB - Edifici Q | 08193 Bellaterra | Barcelona',
      country: 'Spain',
      email: 'porfidio.hernandez@uab.es',
      picture: 'porfi.jpg'
    },

    {
      name: 'Dr. Miguel Pérez-Enciso',
      title: 'Research Collaborator',
      program: 'Plant and Animal Genomics Program',
      where: 'Centre for Research in Agricultural Genomics (CRAG)',
      dept: '',
      group: '',
      room: '',
      adress: 'Campus UAB - Edifici CRAG | 08193 Bellaterra | Barcelona',
      country: 'Spain',
      email: 'miguel.perez@cragenomica.es',
      picture: 'miguel.jpg'
    },

    {
      name: 'Dr. Julio Rozas',
      title: 'Research Collaborator',
      program: '',
      where: 'Facultat de Biologia Universitat de Barcelona',
      dept: 'Departament de Genètica',
      group: '',
      room: '',
      adress: 'Diagonal 643 | Barcelona 08028',
      country: 'Spain',
      email: 'jrozas@ub.edu',
      picture: 'julio.jpg'
    },

    {
      name: 'Javier Navarro',
      title: 'PhD Student and Sys Admin',
      program: '',
      where: '',
      dept: '',
      group: '',
      room: '',
      adress: 'Campus UAB - Edifici CRAG | 08193 Bellaterra | Barcelona',
      country: 'Spain',
      email: 'javier.navarro@cragenomica.es',
      picture: 'javier.jpg'
    },

    {
      name: 'Luca Ferreti',
      title: 'Research Collaborator',
      program: '',
      where: 'The Pirbright Institute',
      dept: '',
      group: 'Integrative Biology',
      room: '',
      adress: '',
      country: 'UK',
      email: 'luca.ferretti@gmail.com',
      picture: 'luca.jpg'
    },
  ];

  $scope.commands = [
    {
      name: 'mstatspop'
    }/*,
    {
      name: 'load'
    }*/
  ]

  $scope.selected_team_member = -1;

  $scope.SelectTeamMember = function(team_member_id) {
    $scope.selected_team_member = team_member_id;
  };

  $scope.IsTeamMemberSelected = function(team_member_id) {
    return ($scope.selected_team_member == team_member_id);
  };


  $scope.page_title = '';

	$scope.init = function() {
    $scope.debug = "adios";

    for (i = 0; i < $scope.menu.length; i++) {
      if ($state.is($scope.menu[i].state)) {
        $scope.page_title = $scope.menu[i].page_title;
      }
    }
  };

  $scope.goTo = function(state_name) {
    $state.go(state_name);
  };

  $scope.IsActive = function (menu_name) {
    var found = false;

    for (i = 0; i < $scope.menu.length; i++) {
      if ($state.is($scope.menu[i].state)) {
        if ($scope.menu[i].inside_menu == menu_name) {
          found = true;
        } 
      }
    }

    return ((found)?'menu_active':'');
  };

  $scope.SetCustomerDescription = function(customer_name) {
    if (customer_name == 'crag') {
      $scope.customer_description = "Center for Research in Agricultural Genomics.";
    }
    if (customer_name == 'agaur') {
      $scope.customer_description = "Agència de Gestió d'Ajuts Universitaris i de Recerca.";
    }
    if (customer_name == 'generalitat') {
      $scope.customer_description = "Generalitat de Catalunya. Departament d'Economia i Coneixement.";
    }
    if (customer_name == 'ministerio') {
      $scope.customer_description = "Ministerio de España. Ministerio de Economía y Competitividad.";
    }
    if (customer_name == 'europa') {
      $scope.customer_description = "Unión Europea. Fondo europeo de Desarrollo Regional.";
    }
  }

	$scope.init();
});






