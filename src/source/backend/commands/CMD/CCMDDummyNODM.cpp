/* Add your LICENSE & COPYRIGHT note */
/**
*    \brief 			CCMDDummy.cpp
*    \details
*    \author
*    \version
*    \date
*/

#include "CCMDDummy.h"

#include <string>
//#include <iostream>
//#include <fstream>
//using namespace std;

#include "../../language/CStringTable.h"
#include "../../commands/CAllCommands.h"

CCMDDummy::CCMDDummy()
: ICommand(CMD_Dummy,
           CMD_Dummy_ABB,
           CMD_Dummy_DESC,
           UNDEFINED_STRING,
           UNDEFINED_STRING,
           UNDEFINED_STRING) {
}

CCMDDummy::~CCMDDummy() {
}

/// ============================================================================
/// COMMAND OPTIONS
/// ============================================================================
void CCMDDummy::DefineCommandOptions() {
  /// Command options:
  /*BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(STANDARD_GROUP_FLAGS,                                       // Group
                    DATA_MENU,                                                  // Data Type
                    Dummy_INPUT_SHORT,                                     // Short Name
                    Dummy_INPUT_LONG,                                      // Long Name
                    Dummy_INPUT_DESC,                                      // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  
    SET_OPTION_INFO(STANDARD_GROUP_FLAGS,                                       // Group
                    DATA_MENU,                                                  // Data Type
                    Dummy_BASE_SHORT,                                     // Short Name
                    Dummy_BASE_LONG,                                      // Long Name
                    Dummy_BASE_DESC,                                      // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required

  END_COMMAND_INTERFACE_DEFINITION*/
}

bool CCMDDummy::Prepare() {
  run_only_help_ = false;

/// ============================================================================
/// CALCS
/// ============================================================================
  //DM_NEW_CALC(calc_Dummy_)

/// ============================================================================
/// DATAS
/// ============================================================================
  //DM_NEW_DATA(DNAvector)
  //DM_NEW_DATA(percentage);
  //DM_NEW_DATA(total);
  
  CDataCharVector* DNAvector = new CDataCharVector;
  CDataBoolean* percentage = new CDataBoolean;

  //DM_GET_DATA3(CDataStdString, all_command_line_, STR(ALL_COMMAND_LINE))
  CDataStdString* all_command_line_ = new CDataStdString;
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
        case KeyString::Dummy_INPUT_SHORT:                 //-f fasta.fa
          DNAvector->set_text_string(arguments);
        break;
               
        case KeyString::Dummy_BASE_SHORT:                 //-b A/T/C/G
          percentage->set_value_string(arguments);
        break;
        
        case 'h':                   //-h
          run_only_help_ = true;
        break;

        default:
        break;
      }
    }
  }

  return true;
}

void CCMDDummy::Run() {
  CCalcDummy* calc_Dummy_ = new CCalcDummy;
  calc_Dummy_->SetInput(DNAvector);
  calc_Dummy_->SetInput(percentage);
//  calc_Dummy_->SetOutput(total);
  calc_Dummy_->Prepare();
  calc_Dummy_->Calculate(manager()->all_commands()->dry_run());
  calc_Dummy_->Finalize();
}

void CCMDDummy::Finalize() {
  /// Clean the command to reuse it later:
 //DM_DEL_CALC(calc_Dummy_)

/// ============================================================================
/// DATAS
/// ============================================================================
 // DM_DEL_DATA(DNAvector)
  //DM_DEL_DATA(percentage);
  //DM_DEL_DATA(total);
  //DM_DEL_ALL_LOCAL_DATA
}
