/*
 * ngasp, a computational solution for performing next generation analysis of 
 * sequence polymorphisms using NGS data.
 * Copyright (c) 2015-2016, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez,
 * Centre for Research in Agricultural Genomics.
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
CRAG.factory('docs', function ($rootScope, arrays) {
  return {
    CASE_START_PROCESS:  1,
    CASE_MANUAL_PROCESS: 2,
    CASE_SYSTEM_PROCESS: 3,

    To3Digits: function(value) {
      var ret = value;
      if (value < 10) {
        ret = '00'+value;
      } else {
        if (value < 100) {
          ret = '0'+value;
        }
      }
      return ret;
    },

    GetId: function(name) {
      var name2 = "";
      for (i = 0; i < name.length; i++) {
        if ( ((name[i] >= 'a') && (name[i] <= 'z')) ||
             ((name[i] >= 'A') && (name[i] <= 'Z')) ||
             ((name[i] >= '0') && (name[i] <= '9')) || 
             (name[i] == ' ')) {
          name2 += name[i];
        }
      }

      var vector = name2.split(" ");
      switch(vector.length) {
        case 0:
          ret = "";
          break;
        case 1:
          ret = vector[0].substr(0,3);
          break;
        case 2:
          ret = vector[0].substr(0,1) + vector[1].substr(0,2);
          break;
        default:
          ret = vector[0].substr(0,1) + vector[1].substr(0,1) + vector[vector.length-1].substr(0,1);
          break;
      }
      
      ret = ret.toUpperCase();
      return ret;
    },


    /*
      Example: If our dictionary is like this:

        term: "Central Manager"   definition: "It is an application"
        term: "CM"                definition: ">Central Manager"

      The following call:
        
        GetDefinition(">Central Manager")

      Returns: "It is an application"
    */
    GetDefinition: function(definition) {
      var ret = "";

      if (definition.substr(0,1) == '>') {
        var related_to_term = definition.substr(1) ;
        for (var i = 0; ((i < $rootScope.definitions.length) && (ret == "")); i++) {
          if ($rootScope.definitions[i].term == related_to_term) {
            ret = $rootScope.definitions[i].definition;
          }
        }
      } else {
        ret = definition;
      }

      return ret;
    },

    /*
      Link to the definition in two steps. Change all words to be defined by [[[i]]] and then
      change all [[[i]]] by their definitions. This prevents the application from define words
      of previous definitions.
    */
    LinkToDefinition: function(text) {
      // Replace "words to be defined" by "[[[i]]]":
      for (var i = 0; i < $rootScope.definitions.length; i++) {
        text = text.replace($rootScope.definitions[i].term, 
                            "<span class=\"cursor_hand\" data-toggle=\"tooltip\" data-placement=\"top\" title=\"[[["+i+"]]]\"><i>"+$rootScope.definitions[i].term+"</i></span>");
      }

      // Replace all "[[[i]]]" by their definitions:
      for (var i = 0; i < $rootScope.definitions.length; i++) {
        text = text.replace("[[["+i+"]]]", this.GetDefinition($rootScope.definitions[i].definition));
      }

      return text;
    },

    AddModule: function(urs, name) {
      var module = {id:this.GetId(name),name:name,list:[],show:true};
      urs.push(module);
      return module;
    },

    AddCategory: function(module, name) {
      var category = {id:this.GetId(name),name:name,list:[],show:true};
      module.list.push(category);
      return category;
    },

    AddSection: function(category, name) {
      var section = {id:this.GetId(name),name:name,list:[],show:true};
      category.list.push(section);
      return section;
    },

    AddRequirement: function(section, order, description, type, done, why_removed) {
      var type_l;
      switch(type) {
        case "M":
          type_l = "Mandatory requirement.";
          break;
        case "D":
          type_l = "Desirable requirement.";
          break;
        case "O":
          type_l = "Optional requirement.";
          break;
        case "E":
          type_l = "Possible future enhancement.";
          break;
      }
      type_long = "<span class=\"cursor_hand\" data-toggle=\"tooltip\" data-placement=\"top\" title=\""+type_l+"\">"+type+"</span>";
      section.list.push({id:order,desc:this.LinkToDefinition(description),type:type,type_long:type_long,done:done,why_removed:why_removed});
    },

    AddToDictionary: function(term, definition) {
      $rootScope.definitions.push({id:$rootScope.definitions.length,term:term,definition:definition});
    },

    AddUser: function(user_name) {
      $rootScope.current_user_name = user_name;
      this.AddCase(null, user_name, null);
    },

    AddCase: function(id, name, case_type) {
      if ( (case_type == this.CASE_START_PROCESS) ||
           (case_type == this.CASE_MANUAL_PROCESS)) {
        $rootScope.current_user_case = name;
      }

      if (id == -1) { id = $rootScope.traceability_matrix.length + 2; }
      if ($rootScope.current_user_case == undefined) {
        $rootScope.current_user_case = "GEN";
      }

      var new_case = {
        id: (id!=null)?(this.GetId($rootScope.current_user_name) + '-' + this.GetId($rootScope.current_user_case) + '-' + this.To3Digits(id)):null,
        name: name,
        case_type: case_type,
        has_urs: false,
        list: []
      };

      if (id != null) {
        for(var i = 0; i < $rootScope.URS_list.length; i++) {
            new_case.list.push({
              id: $rootScope.URS_list[i].id,
              value: false
            });
        }
      }

      $rootScope.traceability_matrix.push(new_case);

      return new_case;
    },

    SetURS: function(case_id, urs_id) {
      var the_case = arrays.FindArrayElementById($rootScope.traceability_matrix, case_id.id);

      if (the_case != null) {
        var urs = arrays.FindArrayElementById(the_case.list, urs_id);

        if (urs != null) {
          urs.value = true;
          var set_urs_used = arrays.FindArrayElementById($rootScope.URS_list, urs_id);
          if (set_urs_used != null) {
            set_urs_used.used = true;
            the_case.has_urs = true;
          }
        }
      }
    }

  };
});

