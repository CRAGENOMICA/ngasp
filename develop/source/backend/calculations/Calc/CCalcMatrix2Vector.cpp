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
/**
 *  \brief     CCalcMatrix2Vector.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      February 15, 2017
 *  \pre
 *  \bug
 *  \warning
 */
#include "CCalcMatrix2Vector.h"

#include "../../language/CStringTable.h"

CCalcMatrix2Vector::CCalcMatrix2Vector()
: ICalculation(KeyString::CALC_MATRIX2VECTOR,
KeyString::CALC_MATRIX2VECTOR_BRIEF_DESC,
KeyString::CALC_MATRIX2VECTOR_DESC,
KeyString::NGASP_AUTHORS,
KeyString::MSTATSPOP_COPYRIGHT,
KeyString::GENERIC_CITATIONS,
KeyString::UNDEFINED_STRING) {
    
BEGIN_CALCULATION_INTERFACE_DEFINITION
  SET_INPUT_INFO(string_matrix_, // Variable
    UNDEFINED_STRING, // Group
    CCALCMATRIX2VECTOR_STRING_MATRIX, // Short Name
    UNDEFINED_STRING, // Long Name
    CCALCMATRIX2VECTOR_STRING_MATRIX_DESC, // Description
    UNDEFINED_STRING, // Matrix2Vector
    UNDEFINED_STRING, // Use only if
    CCALCMATRIX2VECTOR_STRING_MATRIX, // Default value
    UNDEFINED_VALUE, // Min. Value
    UNDEFINED_VALUE, // Max. Value
    OPTTYPE_optional) // Required
  SET_INPUT_INFO(pos_, // Variable
    UNDEFINED_STRING, // Group
    CCALCMATRIX2VECTOR_STRING_POS, // Short Name
    UNDEFINED_STRING, // Long Name
    CCALCMATRIX2VECTOR_STRING_POS_DESC, // Description
    UNDEFINED_STRING, // Matrix2Vector
    UNDEFINED_STRING, // Use only if
    CCALCMATRIX2VECTOR_STRING_POS_DEFV, // Default value
    UNDEFINED_VALUE, // Min. Value
    UNDEFINED_VALUE, // Max. Value
    OPTTYPE_optional) // Required
  SET_INPUT_INFO(column_, // Variable
    UNDEFINED_STRING, // Group
    CCALCMATRIX2VECTOR_STRING_COLUMN, // Short Name
    UNDEFINED_STRING, // Long Name
    CCALCMATRIX2VECTOR_STRING_COLUMN_DESC, // Description
    UNDEFINED_STRING, // Matrix2Vector
    UNDEFINED_STRING, // Use only if
    CCALCMATRIX2VECTOR_STRING_COLUMN_DEFV, // Default value
    UNDEFINED_VALUE, // Min. Value
    UNDEFINED_VALUE, // Max. Value
    OPTTYPE_optional) // Required
  SET_INPUT_INFO(remove_index_, // Variable
    UNDEFINED_STRING, // Group
    CCALCMATRIX2VECTOR_STRING_REMOVE_INDEX, // Short Name
    UNDEFINED_STRING, // Long Name
    CCALCMATRIX2VECTOR_STRING_REMOVE_INDEX_DESC, // Description
    UNDEFINED_STRING, // Matrix2Vector
    UNDEFINED_STRING, // Use only if
    CCALCMATRIX2VECTOR_STRING_REMOVE_INDEX_DEFV, // Default value
    UNDEFINED_VALUE, // Min. Value
    UNDEFINED_VALUE, // Max. Value
    OPTTYPE_optional) // Required
  SET_INPUT_INFO(flattern_unique_, // Variable
    UNDEFINED_STRING, // Group
    CCALCMATRIX2VECTOR_STRING_FLAT_UNIQUE, // Short Name
    UNDEFINED_STRING, // Long Name
    CCALCMATRIX2VECTOR_STRING_FLAT_UNIQUE_DESC, // Description
    UNDEFINED_STRING, // Matrix2Vector
    UNDEFINED_STRING, // Use only if
    CCALCMATRIX2VECTOR_STRING_FLAT_UNIQUE_DEFV, // Default value
    UNDEFINED_VALUE, // Min. Value
    UNDEFINED_VALUE, // Max. Value
    OPTTYPE_optional) // Required
  SET_INPUT_INFO(sort_items_, // Variable
    UNDEFINED_STRING, // Group
    CCALCMATRIX2VECTOR_STRING_SORT_ITEMS, // Short Name
    UNDEFINED_STRING, // Long Name
    CCALCMATRIX2VECTOR_STRING_SORT_ITEMS_DESC, // Description
    UNDEFINED_STRING, // Matrix2Vector
    UNDEFINED_STRING, // Use only if
    CCALCMATRIX2VECTOR_STRING_SORT_ITEMS_DEFV, // Default value
    UNDEFINED_VALUE, // Min. Value
    UNDEFINED_VALUE, // Max. Value
    OPTTYPE_optional) // Required


  SET_OUTPUT_INFO(string_vector_, // Variable
    UNDEFINED_STRING, // Group
    CCALCMATRIX2VECTOR_STRING_VECTOR, // Short Name
    UNDEFINED_STRING, // Long Name
    CCALCMATRIX2VECTOR_STRING_VECTOR_DESC, // Description
    UNDEFINED_STRING, // Matrix2Vector
    UNDEFINED_STRING, // Use only if
    UNDEFINED_STRING, // Default value
    UNDEFINED_VALUE, // Min. Value
    UNDEFINED_VALUE, // Max. Value
    OPTTYPE_optional) // Required
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcMatrix2Vector::~CCalcMatrix2Vector() {
}

void CCalcMatrix2Vector::Prepare(void) {
    DM_GET_INPUTS
    DM_INPUT(string_matrix_)
    DM_INPUT(pos_)
    DM_INPUT(column_)
    DM_INPUT(remove_index_)
    DM_INPUT(flattern_unique_)
    DM_INPUT(sort_items_)
    DM_GET_OUTPUTS
    DM_OUTPUT(string_vector_)
    DM_END
}
/** ****************************************************************************
 * this calculation only works with string matrices and vectors
 * *****************************************************************************
 */
void CCalcMatrix2Vector::Calculate(bool dry_run) {
    if (dry_run == true) {
        return;
    }
    
    IDataVector<std::string> p;
   
    if (string_matrix_->Size() == 0) {
        string_vector_->DeleteMemory();
        WARNING_MSG
                << "The matrix is empty..." 
                END_MSG;        
    }
    else {
        size_t start = 0;
        if (remove_index_->value() == 1) {
            start = 1; // discard the first column or the first row
        }
        
        if (flattern_unique_->value() == 0) {
            if ( ((column_->value() == 0) && (pos_->value() < string_matrix_->regs())) ||
                   ((column_->value() == 1) && (pos_->value() < string_matrix_->reg_length()))){
                string_vector_->DeleteMemory();

                
                if (column_->value() == 0) {   // return the matrix row number "pos_"
                    for(size_t i = start; i < (string_matrix_->operator [](pos_->value())).reg_length(); i++) {
                        std::string aux = (string_matrix_->operator [](pos_->value())).operator [](i);
                        string_vector_->PushBack(aux);
                    }
                } else {   // return the matrix col number "pos_"
                    for(size_t i = start; i < string_matrix_->regs(); i++) {
                        std::string aux = (string_matrix_->operator [](i)).operator [](pos_->value());
                        string_vector_->PushBack(aux);
                    }
                }
            }
            else {
              ERROR_MSG
                      << "Out of range. The position is " << pos_->value()
                      << " while the size of the matrix is " << string_matrix_->Size()
                      << "..."
                      END_MSG;
            }            
        }
        else {
            for (size_t r = 0; r < string_matrix_->regs(); r++) {
                for(size_t i = start; i < (string_matrix_->operator [](r)).reg_length(); i++) {
                    std::string aux = (string_matrix_->operator [](r)).operator [](i);
                    string_vector_->UniquePushBack(aux);
                }
            }
            
            if (sort_items_->value()) {
                string_vector_->Sort();
            }
        }

    }
}

void CCalcMatrix2Vector::Finalize(void) {
    DM_DEL_ALL_LOCAL_DATA
}
