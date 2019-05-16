#!/usr/bin/env bash
#Creation of ${MY_Command} command

if [ $# -eq 1 ]
then
  MY_Command=$1
else
  MY_Command="Dummy"
fi

if [ -f ./source/backend/commands/CMD/CCMD${MY_Command}.h ]
then
    read -n 1 -r -p "Command ${MY_Command} found will be overwritten. Continue? (y/n): "
    echo    # (optional) move to a new line
    if [[ ! $REPLY =~ ^[Yy]$ ]]
    then
        exit 1
    fi
else
	# creation of control requeriments

	# addition of command to ./source/backend/language/CStringTable.h
	sed -i -e 's|  _COMMAND_LAST,|//@{\n/// --------------------------------------------------------------------------\n CMD_'"${MY_Command}"',\n  CMD_'"${MY_Command}"'_ABB,\n  CMD_'"${MY_Command}"'_DESC,\n//@}\n\n  _COMMAND_LAST,|g' ./source/backend/language/CStringTable.h

	# addition of command to ./source/backend/language/CStringTable.cpp    
  sed -i -e 's|  strings_\[ENGLISH_COL\]\[_COMMAND_LAST\]|  strings_\[ENGLISH_COL\]\[CMD_'"${MY_Command}"'\] = \"'"${MY_Command}"'\"\;\n  strings_\[ENGLISH_COL\]\[CMD_'"${MY_Command}"'_ABB\] = \"'"${MY_Command}"'\";\n  strings_\[ENGLISH_COL\]\[CMD_'"${MY_Command}"'_DESC\] = \"'"${MY_Command}"' description\";\n\n  strings_\[ENGLISH_COL\]\[_COMMAND_LAST\]|g' ./source/backend/language/CStringTable.cpp

	# addition of command to ./source/backend/commands/CCMDFactory.cpp
	sed -i -e 's|//_COMMAND_LAST|\#include "CMD/CCMD'"${MY_Command}"'.h"\n//_COMMAND_LAST|g' ./source/backend/commands/CCommandFactory.cpp
	sed -i -e 's|    //list _COMMAND_LAST|list->push_back(new CCMD'"${MY_Command}"'());\n    //list _COMMAND_LAST|g' ./source/backend/calculations/CCommandFactory.cpp
	
	echo "File ./source/backend/language/CStringTable.h modified to add ${MY_Command}"
	echo "File ./source/backend/language/CStringTable.cpp modified to add ${MY_Command}"
	echo "File ./source/backend/commands/CCommandFactory.cpp modified to add ${MY_Command}"
fi

touch ./source/backend/commands/CMD/CCMD${MY_Command}.h
touch ./source/backend/commands/CMD/CCMD${MY_Command}.cpp

#creation of CCMD${MY_Command}.h
cat << EOF > ./source/backend/commands/CMD/CCMD${MY_Command}.h
/* Add your LICENSE & COPYRIGHT note */
/**
*    \\brief 			CCMD${MY_Command}.h
*    \\details
*    \\author
*    \\version
*    \\date
*/

#ifndef BACKEND_SRC_COMMANDS_CMD_CCMD${MY_Command}_H_
#define BACKEND_SRC_COMMANDS_CMD_CCMD${MY_Command}_H_

#include "../ICommand.h"

class CCMD${MY_Command} : public ICommand {
 public:
  CCMD${MY_Command}();
  virtual ~CCMD${MY_Command}();

 public:
  void DefineCommandOptions();
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

};

#endif    // BACKEND_SRC_COMMANDS_CMD_CCMD${MY_Command}_H_

EOF

#creation of CCMD${MY_Command}.cpp
cat << EOF > ./source/backend/commands/CMD/CCMD${MY_Command}.cpp
/* Add your LICENSE & COPYRIGHT note */
/**
*    \\brief 			CCMD${MY_Command}.cpp
*    \\details
*    \\author
*    \\version
*    \\date
*/

#include "CCMD${MY_Command}.h"

#include <string>

#include "../../language/CStringTable.h"
#include "../../data_manager/CDataManager.h"

CCMD${MY_Command}::CCMD${MY_Command}()
: ICommand(CMD_${MY_Command},
           CMD_${MY_Command}_ABB,
           CMD_${MY_Command}_DESC,
           NGASP_AUTHORS,
           MSTATSPOP_COPYRIGHT,
           GENERIC_CITATIONS,
           UNDEFINED_STRING) {
}

CCMD${MY_Command}::~CCMD${MY_Command}() {
}

/// ============================================================================
/// COMMAND OPTIONS
/// ============================================================================
void CCMDmstatspop::DefineCommandOptions() {
  /// Command options:
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(STANDARD_GROUP_FLAGS,                                       // Group
                    DATA_MENU,                                                  // Data Type
                    'f',                                     // Short Name
                    UNDEFINED_STRING,                                      // Long Name
                    UNDEFINED_STRING,                                      // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  
    SET_VALUE_INFO(FORMAT_FILE_FASTA,                                           // Value
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   false)                                                       // Default Value (true / false)
    SET_VALUE_INFO(FORMAT_FILE_TFASTA,                                          // Value
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   false)                                                       // Default Value (true / false)
    SET_VALUE_INFO(FORMAT_FILE_MS,                                              // Value
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   false)                                                       // Default Value (true / false)

  
    SET_OPTION_INFO(STANDARD_GROUP_FLAGS,                                       // Group
                    DATA_ONE_VALUE,                                                  // Data Type
                    'l',                                      // Short Name
                    UNDEFINED_STRING,                                       // Long Name
                    UNDEFINED_STRING,                                       // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required

    SET_OPTION_INFO(STANDARD_GROUP_FLAGS,                                       // Group
                    DATA_MENU,                                                  // Data Type
                    'b',                                     // Short Name
                    UNDEFINED_STRING,                                      // Long Name
                    UNDEFINED_STRING,                                      // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  END_COMMAND_INTERFACE_DEFINITION
}

void CCMD${MY_Command}::Prepare(void) {
  run_only_help_ = false;

  DM_GET_DATA3(CDataStdString, all_command_line_, STR(ALL_COMMAND_LINE))
  all_command_line_->set_value(this->instruction()->GetAllCommandLine());
  
/// ============================================================================
/// COMMAND PARAMS
/// ============================================================================
  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments, one_argument;

  if (instruction()->command_arguments()->size() == 1) {
    run_only_help_ = true;
  } else {
    while (getopt_long_own(&option, &arguments)) {
      switch (option) {
        /// Command options:
        case 'f':                 //-f fasta.fa
        break;
        
        case 'l':                 //-l 1
        break;
        
        case 'b':                 //-b A/T/C/G
        break;
        
        case 'h':                   //-h
          run_only_help_ = true;
        break;
      }
    }
  }

  return true;
}

void CCMD${MY_Command}::Run() {
  std::cout << "when done this comand will print the number of -b bases in the -l line of the -f fasta file\n";
}

void CCMD${MY_Command}::Finalize(void) {
  /// Clean the command to reuse it later:
  DM_DEL_ALL_LOCAL_DATA
}
EOF

echo "File created: ./source/backend/commands/CMD/CCMD${MY_Command}.h"
echo "File created: ./source/backend/commands/CMD/CCMD${MY_Command}.cpp"
