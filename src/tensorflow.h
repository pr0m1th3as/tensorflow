/*
Copyright (C) 2024 Andreas Bertsatos <abertsatos@biol.uoa.gr>

This file is part of the statistics package for GNU Octave.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
details.

You should have received a copy of the GNU General Public License along with
this program; if not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TENSORFLOW_H
#define TENSORFLOW_H

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <inttypes.h>
#include <iostream>

#include <octave/ov.h>
#include <octave/oct.h>
#include "c_api.h"

using namespace std;

// Define input arguments
#define OCT_ARGS int nrhs, octave_value_list args

// ---------------------------------------------------------------------------
// C API functions referenced by the TF_Buffer classdef
// ---------------------------------------------------------------------------
octave_value OCT_TF_NewBuffer (OCT_ARGS);
void OCT_TF_DeleteBuffer (OCT_ARGS);
octave_value OCT_TF_NewBufferFromString (OCT_ARGS);
octave_value OCT_TF_GetBuffer (OCT_ARGS);
octave_value OCT_TF_GetBufferToString (OCT_ARGS);  // OCTAVE specific
// ---------------------------------------------------------------------------
// C API functions referenced by the TF_DataType classdef
// ---------------------------------------------------------------------------
octave_value OCT_TF_DataTypeName (OCT_ARGS);       // OCTAVE specific
octave_value OCT_TF_DataTypeSize (OCT_ARGS);
// -----------------------------------------------------------------------------
// C API functions referenced by the TF_Graph classdef
// -----------------------------------------------------------------------------
octave_value OCT_TF_NewGraph (void);
void OCT_TF_DeleteGraph (OCT_ARGS);
void OCT_TF_GraphSetTensorShape (OCT_ARGS);
octave_value OCT_TF_GraphGetTensorNumDims (OCT_ARGS);
octave_value OCT_TF_GraphGetTensorShape (OCT_ARGS);
octave_value OCT_TF_NewOperationLocked (OCT_ARGS);
octave_value OCT_TF_NewOperation (OCT_ARGS);
octave_value OCT_TF_GraphOperationByName (OCT_ARGS);
octave_value OCT_TF_GraphNextOperation (OCT_ARGS);
void OCT_TF_GraphToGraphDef (OCT_ARGS);
void OCT_TF_GraphGetOpDef (OCT_ARGS);
void OCT_TF_GraphVersions (OCT_ARGS);
octave_value OCT_TF_GraphImportGraphDefWithResults (OCT_ARGS);
void OCT_TF_GraphImportGraphDefWithReturnOutputs (OCT_ARGS);
void OCT_TF_GraphImportGraphDef (OCT_ARGS);
void OCT_TF_GraphCopyFunction (OCT_ARGS);
octave_value OCT_TF_GraphNumFunctions (OCT_ARGS);
octave_value OCT_TF_GraphGetFunctions (OCT_ARGS);
octave_value OCT_TF_NewWhile (OCT_ARGS);
void OCT_TF_AddGradients (OCT_ARGS);
void OCT_TF_AddGradientsWithPrefix (OCT_ARGS);
octave_value OCT_TF_GraphToFunction (OCT_ARGS);
octave_value OCT_TF_GraphToFunctionWithControlOutputs (OCT_ARGS);
// -----------------------------------------------------------------------------
// C API functions referenced by the TF_OperationDescription classdef
// -----------------------------------------------------------------------------
void OCT_TF_SetDevice (OCT_ARGS);
void OCT_TF_AddInput (OCT_ARGS);
void OCT_TF_AddInputList (OCT_ARGS);
void OCT_TF_AddControlInput (OCT_ARGS);
void OCT_TF_SetAttrString (OCT_ARGS);
void OCT_TF_SetAttrStringList (OCT_ARGS);
void OCT_TF_SetAttrInt (OCT_ARGS);
void OCT_TF_SetAttrIntList (OCT_ARGS);
void OCT_TF_SetAttrFloat (OCT_ARGS);
void OCT_TF_SetAttrFloatList (OCT_ARGS);
void OCT_TF_SetAttrBool (OCT_ARGS);
void OCT_TF_SetAttrBoolList (OCT_ARGS);
void OCT_TF_SetAttrType (OCT_ARGS);
void OCT_TF_SetAttrTypeList (OCT_ARGS);
void OCT_TF_SetAttrPlaceholder (OCT_ARGS);
void OCT_TF_SetAttrFuncName (OCT_ARGS);
void OCT_TF_SetAttrShape (OCT_ARGS);
void OCT_TF_SetAttrShapeList (OCT_ARGS);
void OCT_TF_SetAttrTensorShapeProto (OCT_ARGS);
void OCT_TF_SetAttrTensorShapeProtoList (OCT_ARGS);
void OCT_TF_SetAttrTensor (OCT_ARGS);
void OCT_TF_SetAttrTensorList (OCT_ARGS);
void OCT_TF_SetAttrValueProto (OCT_ARGS);
octave_value OCT_TF_FinishOperationLocked (OCT_ARGS);
octave_value OCT_TF_FinishOperation (OCT_ARGS);
// ---------------------------------------------------------------------------
// C API functions referenced by the TF_Status classdef
// ---------------------------------------------------------------------------
octave_value OCT_TF_NewStatus (void);
void OCT_TF_DeleteStatus (OCT_ARGS);
void OCT_TF_SetStatus (OCT_ARGS);
void OCT_TF_SetPayload (OCT_ARGS);
void OCT_TF_ForEachPayload (OCT_ARGS);
void OCT_TF_SetStatusFromIOError (OCT_ARGS);
octave_value OCT_TF_GetCode (OCT_ARGS);
octave_value OCT_TF_Message (OCT_ARGS);
// ---------------------------------------------------------------------------
// C API functions referenced by the TF_String classdef
// ---------------------------------------------------------------------------
octave_value OCT_TF_NewTString (void);             // OCTAVE specific
octave_value OCT_TF_LoadTString (OCT_ARGS);        // OCTAVE specific
octave_value OCT_TF_SaveTString (OCT_ARGS);        // OCTAVE specific
void OCT_TF_StringInit (OCT_ARGS);
void OCT_TF_StringCopy (OCT_ARGS);
void OCT_TF_StringAssignView (OCT_ARGS);
octave_value OCT_TF_StringGetDataPointer (OCT_ARGS);
octave_value OCT_TF_StringGetType (OCT_ARGS);
octave_value OCT_TF_StringGetSize (OCT_ARGS);
octave_value OCT_TF_StringGetCapacity (OCT_ARGS);
void OCT_TF_StringDealloc (OCT_ARGS);
// ---------------------------------------------------------------------------
// C API functions referenced by the TF_Tensor classdef
// ---------------------------------------------------------------------------
octave_value OCT_TF_LoadTensor (OCT_ARGS);         // OCTAVE specific
octave_value OCT_TF_SaveTensor (OCT_ARGS);         // OCTAVE specific
octave_value OCT_TF_NewTensor (OCT_ARGS);
octave_value OCT_TF_AllocateTensor (OCT_ARGS);
octave_value OCT_TF_TensorMaybeMove (OCT_ARGS);
void OCT_TF_DeleteTensor (OCT_ARGS);
octave_value OCT_TF_TensorType (OCT_ARGS);
void OCT_TF_SetShape (OCT_ARGS);
octave_value OCT_TF_NumDims (OCT_ARGS);
octave_value OCT_TF_Dim (OCT_ARGS);
octave_value OCT_TF_TensorByteSize (OCT_ARGS);
octave_value OCT_TF_TensorData (OCT_ARGS);
void OCT_TF_TensorFromProto (OCT_ARGS);
octave_value OCT_TF_TensorElementCount (OCT_ARGS);
void OCT_TF_TensorBitcastFrom (OCT_ARGS);
octave_value OCT_TF_TensorIsAligned (OCT_ARGS);
#endif // TENSORFLOW_H
