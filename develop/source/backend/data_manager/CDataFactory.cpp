/*
 * ngasp, a computational solution for performing next generation analysis of 
 * sequence polymorphisms using NGS data.
 * Copyright (c) 2015-2017, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez,
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
/**
 *  \brief     CDataFactory.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      April 27, 2015
 *  \pre
 *  \bug
 *  \warning
*/

#include "CDataFactory.h"


#include "../language/CStringTable.h"
#include "../util/CStringTools.h"
#include "IData.h"

#include "Data/CDataBoolean.h"
#include "Data/CDataBooleanVector.h"
#include "Data/CDataBooleanMatrix.h"
#include "Data/CDataBooleanCube.h"

#include "Data/CDataChar.h"
#include "Data/CDataCharVector.h"
#include "Data/CDataCharMatrix.h"
#include "Data/CDataCharCube.h"

#include "Data/CDataInt.h"
#include "Data/CDataIntVector.h"
#include "Data/CDataIntMatrix.h"
#include "Data/CDataIntCube.h"

#include "Data/CDataInt64.h"
#include "Data/CDataInt64Vector.h"
#include "Data/CDataInt64Matrix.h"
#include "Data/CDataInt64Cube.h"

#include "Data/CDataFloat.h"
#include "Data/CDataFloatVector.h"
#include "Data/CDataFloatMatrix.h"
#include "Data/CDataFloatCube.h"

#include "Data/CDataDouble.h"
#include "Data/CDataDoubleVector.h"
#include "Data/CDataDoubleMatrix.h"
#include "Data/CDataDoubleCube.h"

#include "Data/CDataStdString.h"
#include "Data/CDataStdStringVector.h"
#include "Data/CDataStdStringMatrix.h"

#include "Data/CDataStringSet.h"

#include "IDataValue.cpp"
#include "IDataVector.cpp"
#include "IDataMatrix.cpp"
#include "IDataCube.cpp"

#include "Data/CDataSam.h"
#include "Data/CDataBam.h"
#include "Data/CDataBamIndex.h"
#include "Data/CDataBCF.h"
#include "Data/CDataVCF.h"
#include "Data/CDataMpileup.h"
#include "Data/CDataFasta.h"
#include "Data/CDataTextFile.h"
#include "Data/CDataTFasta.h"
#include "Data/CDataGTF.h"
#include "Data/CDataBed.h"
#include "Data/CDataGFF.h"
#include "Data/CDataSNP.h"
#include "Data/CDataGFasta.h"
#include "Data/CDataBed.h"
#include "Data/CDataWeightsFile.h"


CDataFactory::CDataFactory() {
////    // DATA TYPE, PRIMARY_TYPE, COLLECTION_TYPE
//    data_map_[KeyString::DATA_BOOLEAN]        = new DataInfo(KeyString::DATA_BOOLEAN,    CollectionType::PRIMITIVE );
//    data_map_[KeyString::DATA_BOOLEAN_VECTOR] = new DataInfo(KeyString::DATA_BOOLEAN,    CollectionType::VECTOR );
//    data_map_[KeyString::DATA_BOOLEAN_MATRIX] = new DataInfo(KeyString::DATA_BOOLEAN,    CollectionType::MATRIX );
//    data_map_[KeyString::DATA_BOOLEAN_CUBE]   = new DataInfo(KeyString::DATA_BOOLEAN,    CollectionType::CUBE );
//    data_map_[KeyString::DATA_CHAR]           = new DataInfo(KeyString::DATA_CHAR,       CollectionType::PRIMITIVE );
//    data_map_[KeyString::DATA_CHAR_VECTOR]    = new DataInfo(KeyString::DATA_CHAR,       CollectionType::VECTOR );
//    data_map_[KeyString::DATA_CHAR_MATRIX]    = new DataInfo(KeyString::DATA_CHAR,       CollectionType::MATRIX );
//    data_map_[KeyString::DATA_CHAR_CUBE]      = new DataInfo(KeyString::DATA_CHAR,       CollectionType::CUBE );
//    data_map_[KeyString::DATA_INT]            = new DataInfo(KeyString::DATA_INT,        CollectionType::PRIMITIVE );
//    data_map_[KeyString::DATA_INT_VECTOR]     = new DataInfo(KeyString::DATA_INT,        CollectionType::VECTOR );
//    data_map_[KeyString::DATA_INT_MATRIX]     = new DataInfo(KeyString::DATA_INT,        CollectionType::MATRIX );
//    data_map_[KeyString::DATA_INT_CUBE]       = new DataInfo(KeyString::DATA_INT,        CollectionType::CUBE );
//    data_map_[KeyString::DATA_INT64]          = new DataInfo(KeyString::DATA_INT64,      CollectionType::PRIMITIVE );
//    data_map_[KeyString::DATA_INT64_VECTOR]   = new DataInfo(KeyString::DATA_INT64,      CollectionType::VECTOR );
//    data_map_[KeyString::DATA_INT64_MATRIX]   = new DataInfo(KeyString::DATA_INT64,      CollectionType::MATRIX );
//    data_map_[KeyString::DATA_INT64_CUBE]     = new DataInfo(KeyString::DATA_INT64,      CollectionType::CUBE );
//    data_map_[KeyString::DATA_FLOAT]          = new DataInfo(KeyString::DATA_FLOAT,      CollectionType::PRIMITIVE );
//    data_map_[KeyString::DATA_FLOAT_VECTOR]   = new DataInfo(KeyString::DATA_FLOAT,      CollectionType::VECTOR );
//    data_map_[KeyString::DATA_FLOAT_MATRIX]   = new DataInfo(KeyString::DATA_FLOAT,      CollectionType::MATRIX );
//    data_map_[KeyString::DATA_FLOAT_CUBE]     = new DataInfo(KeyString::DATA_FLOAT,      CollectionType::CUBE );
//    data_map_[KeyString::DATA_DOUBLE]         = new DataInfo(KeyString::DATA_DOUBLE,     CollectionType::PRIMITIVE );
//    data_map_[KeyString::DATA_DOUBLE_VECTOR]  = new DataInfo(KeyString::DATA_DOUBLE,     CollectionType::VECTOR );
//    data_map_[KeyString::DATA_DOUBLE_MATRIX]  = new DataInfo(KeyString::DATA_DOUBLE,     CollectionType::MATRIX );
//    data_map_[KeyString::DATA_DOUBLE_CUBE]    = new DataInfo(KeyString::DATA_DOUBLE,     CollectionType::CUBE );
//    data_map_[KeyString::DATA_STRING_SET]     = new DataInfo(KeyString::UNDEFINED_STRING,       CollectionType::PRIMITIVE );
//    data_map_[KeyString::DATA_STD_STRING]     = new DataInfo(KeyString::UNDEFINED_STRING,       CollectionType::PRIMITIVE );
//

  // Please, put "int64" before "int" because if they are not in this order when
  // I colorize the source code the result is:
  //     <color>int</color>
  //     <color>int</color>64
  // The basic type must be at the end, too. Because if it is not then the 
  // result is like:
  //     <color>int</color>
  //     <color>int</color>_vector
  
    data_map_[KeyString::DATA_BOOLEAN_VECTOR]    = new CDataBooleanVector();
    data_map_[KeyString::DATA_BOOLEAN_MATRIX]    = new CDataBooleanMatrix();
    data_map_[KeyString::DATA_BOOLEAN_CUBE]      = new CDataBooleanCube();
    data_map_[KeyString::DATA_BOOLEAN]           = new CDataBoolean();
    data_map_[KeyString::DATA_CHAR_VECTOR]       = new CDataCharVector();
    data_map_[KeyString::DATA_CHAR_MATRIX]       = new CDataCharMatrix();
    data_map_[KeyString::DATA_CHAR_CUBE]         = new CDataCharCube();
    data_map_[KeyString::DATA_CHAR]              = new CDataChar();
    data_map_[KeyString::DATA_INT64_VECTOR]      = new CDataInt64Vector();
    data_map_[KeyString::DATA_INT64_MATRIX]      = new CDataInt64Matrix();
    data_map_[KeyString::DATA_INT64_CUBE]        = new CDataInt64Cube();
    data_map_[KeyString::DATA_INT64]             = new CDataInt64();
    data_map_[KeyString::DATA_INT_VECTOR]        = new CDataIntVector();
    data_map_[KeyString::DATA_INT_MATRIX]        = new CDataIntMatrix();
    data_map_[KeyString::DATA_INT_CUBE]          = new CDataIntCube();
    data_map_[KeyString::DATA_INT]               = new CDataInt();
    data_map_[KeyString::DATA_FLOAT_VECTOR]      = new CDataFloatVector();
    data_map_[KeyString::DATA_FLOAT_MATRIX]      = new CDataFloatMatrix();
    data_map_[KeyString::DATA_FLOAT_CUBE]        = new CDataFloatCube();
    data_map_[KeyString::DATA_FLOAT]             = new CDataFloat();
    data_map_[KeyString::DATA_DOUBLE_VECTOR]     = new CDataDoubleVector();
    data_map_[KeyString::DATA_DOUBLE_MATRIX]     = new CDataDoubleMatrix();
    data_map_[KeyString::DATA_DOUBLE_CUBE]       = new CDataDoubleCube();
    data_map_[KeyString::DATA_DOUBLE]            = new CDataDouble();
    data_map_[KeyString::DATA_STRING_SET]        = new CDataStringSet();
    data_map_[KeyString::DATA_STD_STRING_VECTOR] = new CDataStdStringVector();
    data_map_[KeyString::DATA_STD_STRING_MATRIX] = new CDataStdStringMatrix();
    data_map_[KeyString::DATA_STD_STRING]        = new CDataStdString();
    data_map_[KeyString::DATA_BAM_INDEX]         = new CDataBamIndex();
    data_map_[KeyString::DATA_BAM]               = new CDataBam();
    data_map_[KeyString::DATA_SAM]               = new CDataSam();
    data_map_[KeyString::DATA_BCF]               = new CDataBCF();
    data_map_[KeyString::DATA_VCF]               = new CDataVCF();
    data_map_[KeyString::DATA_MPILEUP]           = new CDataMpileup();
    data_map_[KeyString::DATA_FASTA]             = new CDataFasta();
    data_map_[KeyString::DATA_TEXT_FILE]         = new CDataTextFile();
    data_map_[KeyString::DATA_TFASTA]            = new CDataTFasta();
    data_map_[KeyString::DATA_GTF]               = new CDataGTF();
    data_map_[KeyString::DATA_BED]               = new CDataBed();  
    data_map_[KeyString::DATA_GFF]               = new CDataGFF();  
    data_map_[KeyString::DATA_SNP]               = new CDataSNP();
    data_map_[KeyString::DATA_GFASTA]            = new CDataGFasta();
    data_map_[KeyString::DATA_WEIGHTS]           = new CDataWeightsFile();
    
            
}

CDataFactory::~CDataFactory() {
  std::map<KeyString, IData *>::iterator it;
  for (it = data_map_.begin(); it != data_map_.end(); ++it) {
    // Delete the Data object:
    delete it->second;
    it->second = NULL;
  }
  data_map_.clear();  // Remove all elements from the map
}

IData *CDataFactory::GetData(KeyString data_id) {
  IData *new_data = NULL;

  if (data_map_[data_id] != NULL) {
    new_data = data_map_[data_id]->clone();
  }

//  switch (data_id) {
//    case KeyString::DATA_BOOLEAN:
//      new_data = new CDataBoolean();
//      break;
//    case KeyString::DATA_BOOLEAN_VECTOR:
//      new_data = new CDataBooleanVector();
//      break;
//    case KeyString::DATA_BOOLEAN_MATRIX:
//      new_data = new CDataBooleanMatrix();
//      break;
//    case KeyString::DATA_BOOLEAN_CUBE:
//      new_data = new CDataBooleanCube();
//      break;
//    case KeyString::DATA_CHAR:
//      new_data = new CDataChar();
//      break;
//    case KeyString::DATA_CHAR_VECTOR:
//      new_data = new CDataCharVector();
//      break;
//    case KeyString::DATA_CHAR_MATRIX:
//      new_data = new CDataCharMatrix();
//      break;
//    case KeyString::DATA_CHAR_CUBE:
//      new_data = new CDataCharCube();
//      break;
//    case KeyString::DATA_INT:
//      new_data = new CDataInt();
//      break;
//    case KeyString::DATA_INT_VECTOR:
//      new_data = new CDataIntVector();
//      break;
//    case KeyString::DATA_INT_MATRIX:
//      new_data = new CDataIntMatrix();
//      break;
//    case KeyString::DATA_INT_CUBE:
//      new_data = new CDataIntCube();
//      break;
//    case KeyString::DATA_INT64:
//      new_data = new CDataInt64();
//      break;
//    case KeyString::DATA_INT64_VECTOR:
//      new_data = new CDataInt64Vector();
//      break;
//    case KeyString::DATA_INT64_MATRIX:
//      new_data = new CDataInt64Matrix();
//      break;
//    case KeyString::DATA_INT64_CUBE:
//      new_data = new CDataInt64Cube();
//      break;
//    case KeyString::DATA_FLOAT:
//      new_data = new CDataFloat();
//      break;
//    case KeyString::DATA_FLOAT_VECTOR:
//      new_data = new CDataFloatVector();
//      break;
//    case KeyString::DATA_FLOAT_MATRIX:
//      new_data = new CDataFloatMatrix();
//      break;
//    case KeyString::DATA_FLOAT_CUBE:
//      new_data = new CDataFloatCube();
//      break;
//    case KeyString::DATA_DOUBLE:
//      new_data = new CDataDouble();
//      break;
//    case KeyString::DATA_DOUBLE_VECTOR:
//      new_data = new CDataDoubleVector();
//      break;
//    case KeyString::DATA_DOUBLE_MATRIX:
//      new_data = new CDataDoubleMatrix();
//      break;
//    case KeyString::DATA_DOUBLE_CUBE:
//      new_data = new CDataDoubleCube();
//      break;
//    case KeyString::DATA_STRING_SET:
//      new_data = new CDataStringSet();
//      break;
//    case KeyString::DATA_STD_STRING:
//      new_data = new CDataStdString();
//      break;
//    default:
//      new_data = NULL;
//      break;
//  }

  return new_data;
}

IData *CDataFactory::GetData(std::string type) {
  IData *new_data = NULL;

  bool calc_found = false;
  std::map<KeyString, IData *>::iterator it;
  for (it = data_map_.begin(); ((it != data_map_.end()) &&
                                (!calc_found)); ++it) {
    if (it->second->type() == type) {
      calc_found = true;
      new_data = GetData(it->second->type_key());
    }
  }

  return new_data;
}

/**
 * This function is used for the pipeline developer when he/she assigns memory
 * to a data in a pipeline.
 */
void CDataFactory::ReserveMemory(IData *data,
                                 long int tables,
                                 long int regs,
                                 long int length,
                                 long int *lens,
                                 std::string default_value) {

  if (data->type_key() == KeyString::DATA_BOOLEAN_VECTOR) {
    CDataBooleanVector *p = static_cast<CDataBooleanVector *>(data);
    if (p != NULL) {
      //!20160505 replace (a,b,c) by (a*b,c)
      p->ReserveMemory(regs * length, CStringTools::ToBoolean(default_value));
    }
  }

  if (data->type_key() == KeyString::DATA_BOOLEAN_MATRIX) {
    CDataBooleanMatrix *p = static_cast<CDataBooleanMatrix *>(data);
    if (p != NULL) {
      if (lens == 0) p->ReserveMemory(regs, length, CStringTools::ToBoolean(default_value));
      else p->ReserveMemory(regs, lens, CStringTools::ToBoolean(default_value));
    }
  }

  if (data->type_key() == KeyString::DATA_BOOLEAN_CUBE) {
    CDataBooleanCube   *p = static_cast<CDataBooleanCube *>(data);
    if (p != NULL) {
      p->ReserveMemory(tables, regs, length,
                       CStringTools::ToBoolean(default_value));
    }
  }

  if (data->type_key() == KeyString::DATA_CHAR_VECTOR) {
    CDataCharVector    *p = static_cast<CDataCharVector *>(data);
    if (p != NULL) {
      //!20160505 replace (a,b,c) by (a*b,c)
      p->ReserveMemory(regs * length, CStringTools::ToBoolean(default_value));
    }
  }

  if (data->type_key() == KeyString::DATA_CHAR_MATRIX) {
    CDataCharMatrix    *p = static_cast<CDataCharMatrix *>(data);
    if (p != NULL) {
      if (lens == 0) p->ReserveMemory(regs, length, CStringTools::ToBoolean(default_value));
      else p->ReserveMemory(regs, lens, CStringTools::ToBoolean(default_value));
    }
  }

  if (data->type_key() == KeyString::DATA_CHAR_CUBE) {
    CDataCharCube      *p = static_cast<CDataCharCube *>(data);
    if (p != NULL) {
      p->ReserveMemory(tables, regs, length,
                       CStringTools::ToBoolean(default_value));
    }
  }

  if (data->type_key() == KeyString::DATA_INT_VECTOR) {
    CDataIntVector     *p = static_cast<CDataIntVector *>(data);
    if (p != NULL) {
      //!20160505 replace (a,b,c) by (a*b,c)
      p->ReserveMemory(regs * length, CStringTools::ToBoolean(default_value));
    }
  }

  if (data->type_key() == KeyString::DATA_INT_MATRIX) {
    CDataIntMatrix     *p = static_cast<CDataIntMatrix *>(data);
    if (p != NULL) {
      if (lens == 0) p->ReserveMemory(regs, length, CStringTools::ToBoolean(default_value));
      else p->ReserveMemory(regs, lens, CStringTools::ToBoolean(default_value));
    }
  }

  if (data->type_key() == KeyString::DATA_INT_CUBE) {
    CDataIntCube       *p = static_cast<CDataIntCube *>(data);
    if (p != NULL) {
      p->ReserveMemory(tables, regs, length,
                       CStringTools::ToBoolean(default_value));
    }
  }

  if (data->type_key() == KeyString::DATA_INT64_VECTOR) {
    CDataInt64Vector   *p = static_cast<CDataInt64Vector *>(data);
    if (p != NULL) {
      //!20160505 replace (a,b,c) by (a*b,c)
      p->ReserveMemory(regs * length, CStringTools::ToBoolean(default_value));
    }
  }

  if (data->type_key() == KeyString::DATA_INT64_MATRIX) {
    CDataInt64Matrix   *p = static_cast<CDataInt64Matrix *>(data);
    if (p != NULL) {
      if (lens == 0) p->ReserveMemory(regs, length, CStringTools::ToBoolean(default_value));
      else p->ReserveMemory(regs, lens, CStringTools::ToBoolean(default_value));
    }
  }

  if (data->type_key() == KeyString::DATA_INT64_CUBE) {
    CDataInt64Cube     *p = static_cast<CDataInt64Cube *>(data);
    if (p != NULL) {
      p->ReserveMemory(tables, regs, length,
                       CStringTools::ToBoolean(default_value));
    }
  }

  if (data->type_key() == KeyString::DATA_FLOAT_VECTOR) {
    CDataFloatVector   *p = static_cast<CDataFloatVector *>(data);
    if (p != NULL) {
      //!20160505 replace (a,b,c) by (a*b,c)
      p->ReserveMemory(regs * length, CStringTools::ToBoolean(default_value));
    }
  }

  if (data->type_key() == KeyString::DATA_FLOAT_MATRIX) {
    CDataFloatMatrix   *p = static_cast<CDataFloatMatrix *>(data);
    if (p != NULL) {
      if (lens == 0) p->ReserveMemory(regs, length, CStringTools::ToBoolean(default_value));
      else p->ReserveMemory(regs, lens, CStringTools::ToBoolean(default_value));
    }
  }

  if (data->type_key() == KeyString::DATA_FLOAT_CUBE) {
    CDataFloatCube     *p = static_cast<CDataFloatCube *>(data);
    if (p != NULL) {
      p->ReserveMemory(tables, regs, length,
                       CStringTools::ToBoolean(default_value));
    }
  }

  if (data->type_key() == KeyString::DATA_DOUBLE_VECTOR) {
    CDataDoubleVector  *p = static_cast<CDataDoubleVector *>(data);
    if (p != NULL) {
      //!20160505 replace (a,b,c) by (a*b,c)
      p->ReserveMemory(regs * length, CStringTools::ToBoolean(default_value));
    }
  }

  if (data->type_key() == KeyString::DATA_DOUBLE_MATRIX) {
    CDataDoubleMatrix  *p = static_cast<CDataDoubleMatrix *>(data);
    if (p != NULL) {
      if (lens == 0) p->ReserveMemory(regs, length, CStringTools::ToBoolean(default_value));
      else p->ReserveMemory(regs, lens, CStringTools::ToBoolean(default_value));
    }
  }

  if (data->type_key() == KeyString::DATA_DOUBLE_CUBE) {
    CDataDoubleCube    *p = static_cast<CDataDoubleCube *>(data);
    if (p != NULL) {
      p->ReserveMemory(tables, regs, length,
                       CStringTools::ToBoolean(default_value));
    }
  }



//  switch (data->type_key()) {
//    case KeyString::DATA_BOOLEAN:
//      break;
//    case KeyString::DATA_BOOLEAN_VECTOR:
//      static_cast<IDataVector<unit8_t> *>(data)->ReserveMemory(regs, length,
//                                        CStringTools::ToBoolean(default_value));
//      break;
//    case KeyString::DATA_BOOLEAN_MATRIX:
//      static_cast<IDataMatrix<unit8_t> *>(data)->ReserveMemory(regs, length,
//                                        CStringTools::ToBoolean(default_value));
//      break;
//    case KeyString::DATA_BOOLEAN_CUBE:
//      static_cast<IDataCube<unit8_t> *>(data)->ReserveMemory(tables, regs, length,
//                                        CStringTools::ToBoolean(default_value));
//      break;
//    case KeyString::DATA_CHAR:
//      break;
//    case KeyString::DATA_CHAR_VECTOR:
//      static_cast<IDataVector<char> *>(data)->ReserveMemory(regs, length,
//                                           CStringTools::ToChar(default_value));
//      break;
//    case KeyString::DATA_CHAR_MATRIX:
//      static_cast<IDataMatrix<char> *>(data)->ReserveMemory(regs, length,
//                                           CStringTools::ToChar(default_value));
//      break;
//    case KeyString::DATA_CHAR_CUBE:
//      static_cast<IDataCube<char> *>(data)->ReserveMemory(tables, regs, length,
//                                           CStringTools::ToChar(default_value));
//      break;
//    case KeyString::DATA_INT:
//      break;
//    case KeyString::DATA_INT_VECTOR:
//      static_cast<IDataVector<int> *>(data)->ReserveMemory(regs, length,
//                                            CStringTools::ToInt(default_value));
//      break;
//    case KeyString::DATA_INT_MATRIX:
//      static_cast<IDataMatrix<int> *>(data)->ReserveMemory(regs, length,
//                                            CStringTools::ToInt(default_value));
//      break;
//    case KeyString::DATA_INT_CUBE:
//      static_cast<IDataCube<int> *>(data)->ReserveMemory(tables, regs, length,
//                                            CStringTools::ToInt(default_value));
//      break;
//    case KeyString::DATA_INT64:
//      break;
//    case KeyString::DATA_INT64_VECTOR:
//      static_cast<IDataVector<long int> *>(data)->ReserveMemory(regs, length,
//                                          CStringTools::ToInt64(default_value));
//      break;
//    case KeyString::DATA_INT64_MATRIX:
//      static_cast<IDataMatrix<long int> *>(data)->ReserveMemory(regs, length,
//                                          CStringTools::ToInt64(default_value));
//      break;
//    case KeyString::DATA_INT64_CUBE:
//      static_cast<IDataCube<long int> *>(data)->ReserveMemory(tables, regs, length
//                                        , CStringTools::ToInt64(default_value));
//      break;
//    case KeyString::DATA_FLOAT:
//      break;
//    case KeyString::DATA_FLOAT_VECTOR:
//      static_cast<IDataVector<float> *>(data)->ReserveMemory(regs, length,
//                                          CStringTools::ToFloat(default_value));
//      break;
//    case KeyString::DATA_FLOAT_MATRIX:
//      static_cast<IDataMatrix<float> *>(data)->ReserveMemory(regs, length,
//                                          CStringTools::ToFloat(default_value));
//      break;
//    case KeyString::DATA_FLOAT_CUBE:
//      static_cast<IDataCube<float> *>(data)->ReserveMemory(tables, regs, length,
//                                          CStringTools::ToFloat(default_value));
//      break;
//    case KeyString::DATA_DOUBLE:
//      break;
//    case KeyString::DATA_DOUBLE_VECTOR:
//      static_cast<IDataVector<double> *>(data)->ReserveMemory(regs, length,
//                                         CStringTools::ToDouble(default_value));
//      break;
//    case KeyString::DATA_DOUBLE_MATRIX:
//      static_cast<IDataMatrix<double> *>(data)->ReserveMemory(regs, length,
//                                         CStringTools::ToDouble(default_value));
//      break;
//    case KeyString::DATA_DOUBLE_CUBE:
//      static_cast<IDataCube<double> *>(data)->ReserveMemory(tables, regs, length
//                                       , CStringTools::ToDouble(default_value));
//      break;
//    case KeyString::DATA_STRING_SET:
//      break;
//    case KeyString::DATA_STD_STRING:
//      break;
//    default:
//      break;
//  }

}





//
///**
// * This function returns the basic type of a given type.
// * For example, the basic type of an int vector or an int matrix is an int.
// */
//KeyString
//CDataFactory::GetPrimitiveTypeFrom(KeyString data_id) {
//  KeyString ret = KeyString::UNDEFINED_STRING;
//  if (data_map_[data_id] != NULL) {;
//    ret = data_map_[data_id]->primitive();
//  }
////
////  switch(data_id) {
////    case KeyString::DATA_CHAR:
////    case KeyString::DATA_CHAR_VECTOR:
////    case KeyString::DATA_CHAR_MATRIX:
////    case KeyString::DATA_CHAR_CUBE:
////      ret = KeyString::DATA_CHAR;
////      break;
////    case KeyString::DATA_INT:
////    case KeyString::DATA_INT_VECTOR:
////    case KeyString::DATA_INT_MATRIX:
////    case KeyString::DATA_INT_CUBE:
////      ret = KeyString::DATA_INT;
////      break;
////    case KeyString::DATA_INT64:
////    case KeyString::DATA_INT64_VECTOR:
////    case KeyString::DATA_INT64_MATRIX:
////    case KeyString::DATA_INT64_CUBE:
////      ret = KeyString::DATA_INT64;
////      break;
////    case KeyString::DATA_FLOAT:
////    case KeyString::DATA_FLOAT_VECTOR:
////    case KeyString::DATA_FLOAT_MATRIX:
////    case KeyString::DATA_FLOAT_CUBE:
////      ret = KeyString::DATA_FLOAT;
////      break;
////    case KeyString::DATA_DOUBLE:
////    case KeyString::DATA_DOUBLE_VECTOR:
////    case KeyString::DATA_DOUBLE_MATRIX:
////    case KeyString::DATA_DOUBLE_CUBE:
////      ret = KeyString::DATA_DOUBLE;
////      break;
////    case KeyString::DATA_BOOLEAN:
////    case KeyString::DATA_BOOLEAN_VECTOR:
////    case KeyString::DATA_BOOLEAN_MATRIX:
////    case KeyString::DATA_BOOLEAN_CUBE:
////      ret = KeyString::DATA_BOOLEAN;
////      break;
////    default:
////      ret = KeyString::UNDEFINED_STRING;
////      break;
////  }
//
//  return ret;
//}
//
//
//CollectionType
//CDataFactory::GetCollectionType(KeyString data_id) {
//  CollectionType ret = CollectionType::TYPE_UNDEFINED;
//
//  if (data_map_[data_id] != NULL) {;
//    ret = data_map_[data_id]->collection;
//  }
//
////  switch(data_id) {
////    case KeyString::DATA_CHAR:
////    case KeyString::DATA_INT:
////    case KeyString::DATA_INT64:
////    case KeyString::DATA_FLOAT:
////    case KeyString::DATA_DOUBLE:
////    case KeyString::DATA_BOOLEAN:
////    // Datas that do not have multiple dimensions:
////    case KeyString::DATA_STD_STRING:
////    case KeyString::DATA_STRING_SET:
////      ret = CollectionType::PRIMITIVE;
////      break;
////    case KeyString::DATA_CHAR_VECTOR:
////    case KeyString::DATA_INT_VECTOR:
////    case KeyString::DATA_INT64_VECTOR:
////    case KeyString::DATA_FLOAT_VECTOR:
////    case KeyString::DATA_DOUBLE_VECTOR:
////    case KeyString::DATA_BOOLEAN_VECTOR:
////      ret = CollectionType::VECTOR;
////      break;
////    case KeyString::DATA_CHAR_MATRIX:
////    case KeyString::DATA_INT_MATRIX:
////    case KeyString::DATA_INT64_MATRIX:
////    case KeyString::DATA_FLOAT_MATRIX:
////    case KeyString::DATA_DOUBLE_MATRIX:
////    case KeyString::DATA_BOOLEAN_MATRIX:
////      ret = CollectionType::MATRIX;
////      break;
////    case KeyString::DATA_CHAR_CUBE:
////    case KeyString::DATA_INT_CUBE:
////    case KeyString::DATA_INT64_CUBE:
////    case KeyString::DATA_FLOAT_CUBE:
////    case KeyString::DATA_DOUBLE_CUBE:
////    case KeyString::DATA_BOOLEAN_CUBE:
////      ret = CollectionType::CUBE;
////      break;
////    default:
////      ret = CollectionType::TYPE_UNDEFINED;
////      break;
////  }
//
//  return ret;
//}

/**
 * The only valid types for indexing vector, matrices and cubes.
 * Example vector[i]. 'i' must be a number (int or int64). It can not be a char,
 * float, ...
 */
bool CDataFactory::ValidIndexType(CDataAccess *data) {
  KeyString data_type = CDataFactory::GetType(data);

  return ((data_type == KeyString::DATA_INT) ||
          (data_type == KeyString::DATA_INT64));
}

KeyString CDataFactory::GetType(CDataAccess *data) {
  KeyString ret = KeyString::UNDEFINED_STRING;

  if (data->IsSet()) {
    if (data->data_object() != NULL) {
      if ((data->data_variable() == "") ||
          (data->data_variable() == STR(VARIABLE_DATA)) ||
          (data->data_variable() == STR(VARIABLE_VALUE))) {
        // this data access is an object: (a, a.value or a.data)
        ret = data->data_object()->type_key();
      } else {
        // this data access is an object.variable:
        if ((data->data_variable() == STR(VARIABLE_TABLES)) ||
            (data->data_variable() == STR(VARIABLE_REGS)) ||
            (data->data_variable() == STR(VARIABLE_LENGTH))) {
          ret = KeyString::DATA_INT64;
        }
      }
    } else {
      // this data access is an scalar
      // Let's go to decide its type:
      std::string str_val = CStringTools::ToString(data->value());

      if (CStringTools::ToString(CStringTools::ToBoolean(str_val)) == str_val) {
        ret = KeyString::DATA_BOOLEAN;
      } else {
        if (CStringTools::ToString(CStringTools::ToInt64(str_val)) == str_val) {
          ret = KeyString::DATA_INT;
          // But It could be a DATA_INT64 too.
        } else {
          if (CStringTools::ToString(CStringTools::ToDouble(str_val)) == str_val) {
            ret = KeyString::DATA_DOUBLE;
            // But It could be a DATA_FLOAT too.
          } else {
            if (CStringTools::ToString(CStringTools::ToChar(str_val)) == str_val) {
              ret = KeyString::DATA_STD_STRING;
              // But It could be a DATA_CHAR of one character.
            } else {
              ret = KeyString::DATA_STD_STRING;
            }
          }
        }
      }
    }
  }

  return ret;
}

bool CDataFactory::CompatibleTypes(CDataAccess *to, CDataAccess *from) {
  KeyString to_type   = CDataFactory::GetType(to);
  KeyString from_type = CDataFactory::GetType(from);

  // Incompatible cases:
  return
  !(
    // Example: int num_bases = 'a'
    ((from_type == KeyString::DATA_CHAR) &&
     (to_type == KeyString::DATA_INT)) ||

    // Example: long int num_bases = 'a'
    ((from_type == KeyString::DATA_CHAR) &&
     (to_type == KeyString::DATA_INT64))
  );
}

std::string CDataFactory::GetDataTypesInformation(void) {
  std::string ret = "{";
  ret += "\"datatypes\":[";

  std::map<KeyString, IData *>::iterator it;
  for (it = data_map_.begin(); it != data_map_.end(); ++it) {

    if (it != data_map_.begin()) {
      ret += ",";
    }
    ret += "{";
    ret += "\"id\":\"" + it->second->type() + "\"";
    ret += "}";
  }

  ret += "]";
  ret += "}";

  return ret;
}