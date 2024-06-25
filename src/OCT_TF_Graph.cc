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

#include "tensorflow.h"

// -----------------------------------------------------------------------------
// C API functions referenced by the TF_Graph classdef
// -----------------------------------------------------------------------------

// TF_CAPI_EXPORT extern TF_Graph* TF_NewGraph(void);
octave_value OCT_TF_NewGraph (void)
{
  TF_Graph* newGraph = TF_NewGraph ();
  octave_uint64 ptr = (uint64_t) newGraph;
  octave_value plhs = ptr;
  return plhs;
}

// TF_CAPI_EXPORT extern void TF_DeleteGraph(TF_Graph*);
void OCT_TF_DeleteGraph (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_DeleteGraph' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer "
           "to the Graph parsed to the 'TF_DeleteGraph' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  TF_DeleteGraph (graph);
}

// TF_CAPI_EXPORT extern void TF_GraphSetTensorShape(TF_Graph* graph,
//                                                   TF_Output output,
//                                                   const int64_t* dims,
//                                                   const int num_dims,
//                                                   TF_Status* status);
void OCT_TF_GraphSetTensorShape (OCT_ARGS)
{
  if (nrhs < 6)
  {
    error ("tensorflow: five extra argumenta are required for "
           "the 'TF_GraphSetTensorShape' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Graph parsed to the 'TF_GraphSetTensorShape' C API function.");
  }
  // Check octave_value type for pointer to Output
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer to "
           "the Output parsed to the 'TF_GraphSetTensorShape' C API function.");
  }
  // Check octave_value type for size and number of dimensions for Tensor
  if (! args(3).is_int64_type () || ! args(3).rows () == 1)
  {
    error ("tensorflow: 4th argument must be an int64 scalar or "
           "vector defining the size of the dimensions of the Tensor "
           "to be parsed to the 'TF_GraphSetTensorShape' C API function.");
  }
  if (! args(4).is_int32_type () || ! args(4).is_scalar_type ())
  {
    error ("tensorflow: 5th argument must be an int32 scalar "
           "defining the number of the dimensions of the Tensor to "
           "be parsed to the 'TF_GraphSetTensorShape' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(5).is_uint64_type () || ! args(5).is_scalar_type ())
  {
    error ("tensorflow: 6th argument must be an uint64 scalar pointer to the "
           "Status parsed to the 'TF_GraphSetTensorShape' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  // Get pointer to Output
  TF_Output output = *((TF_Output*) args(2).uint64_value ());
  // Get size and number of dimensions for Tensor
  int64NDArray sz = args(3).int64_array_value ();
  int num_dims = args(4).int32_scalar_value ();
  OCTAVE_LOCAL_BUFFER (int64_t, dim_size, num_dims);
  for (int i = 0; i < num_dims; i++) {dim_size[i] = sz(i);}
  const int64_t* dims = dim_size;
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(5).uint64_value ();
  // Set Tensor shape referenced by Output in Graph
  TF_GraphSetTensorShape (graph, output, dims, num_dims, status);
}

// TF_CAPI_EXPORT extern int TF_GraphGetTensorNumDims(TF_Graph* graph,
//                                                    TF_Output output,
//                                                    TF_Status* status);
octave_value OCT_TF_GraphGetTensorNumDims (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_GraphGetTensorNumDims' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "Graph parsed to the 'TF_GraphGetTensorNumDims' C API function.");
  }
  // Check octave_value type for pointer to Output
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer to the "
           "Output parsed to the 'TF_GraphGetTensorNumDims' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(3).is_uint64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 scalar pointer to the "
           "Status parsed to the 'TF_GraphGetTensorNumDims' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  // Get pointer to Output
  TF_Output output = *((TF_Output*) args(2).uint64_value ());
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(3).uint64_value ();
  // Get Tensor number of dimensions referenced by Output in Graph
  octave_int32 num_dims = TF_GraphGetTensorNumDims (graph, output, status);
  octave_value plhs = num_dims;
  return plhs;
}

// TF_CAPI_EXPORT extern void TF_GraphGetTensorShape(TF_Graph* graph,
//                                                   TF_Output output,
//                                                   int64_t* dims, int num_dims,
//                                                   TF_Status* status);
octave_value OCT_TF_GraphGetTensorShape (OCT_ARGS)
{
  if (nrhs < 5)
  {
    error ("tensorflow: four extra arguments are required for "
           "the 'TF_GraphGetTensorShape' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Graph parsed to the 'TF_GraphGetTensorShape' C API function.");
  }
  // Check octave_value type for pointer to Output
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer to "
           "the Output parsed to the 'TF_GraphGetTensorShape' C API function.");
  }
  // Check octave_value type for number of dimensions of Tensor
  // referenced by the Output in Graph
  if (! args(3).is_int32_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an int32 scalar "
           "defining the number of the dimensions of the Tensor "
           "referenced by the Output in Graph to be parsed to "
           "the 'TF_GraphGetTensorShape' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(4).is_uint64_type () || ! args(4).is_scalar_type ())
  {
    error ("tensorflow: 5th argument must be an uint64 scalar pointer to "
           "the Status parsed to the 'TF_GraphGetTensorShape' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  // Get pointer to Output
  TF_Output output = *((TF_Output*) args(2).uint64_value ());
  // Get number of dimensions for new Tensor
  int num_dims = args(3).int32_scalar_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(4).uint64_value ();
  // Preallocate 'dims' to parse them into TF_GraphGetTensorShape
  int64_t* dims = (int64_t*) calloc (num_dims, sizeof (int64_t));
  // Get shape (size of dimensions) of Tensor referenced by Output in Graph
  TF_GraphGetTensorShape (graph, output, dims, num_dims, status);
  octave_int64 dim_sz = *(uint64_t*) dims;
  octave_value plhs = dim_sz;
  free (dims);
  return plhs;
}

// TF_CAPI_EXPORT extern TF_OperationDescription* TF_NewOperationLocked(TF_Graph* graph,
//                                                                      const char* op_type,
//                                                                      const char* oper_name);
octave_value OCT_TF_NewOperationLocked (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_NewOperationLocked' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Graph parsed to the 'TF_NewOperationLocked' C API function.");
  }
  // Check octave_value type for character vector of Operation type
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character vector defining the "
           "operation type parsed to the 'TF_NewOperationLocked' C API function.");
  }
  // Check octave_value type for character vector of Operation name
  if (! args(3).is_char_matrix () || args(3).rows () != 1)
  {
    error ("tensorflow: 4th argument must be a character vector defining the "
           "operation name parsed to the 'TF_NewOperationLocked' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  // Get character vector of Operation type in Graph
  charMatrix op_type = args(2).char_matrix_value ();
  // Get character vector of Operation name in Graph
  charMatrix op_name = args(3).char_matrix_value ();
  // Get new locked operation
  TF_OperationDescription* op_desc = TF_NewOperationLocked (graph, op_type.data (),
                                                            op_name.data ());
  octave_uint64 str_ptr = (uint64_t) op_desc;
  octave_value plhs = str_ptr;
  return plhs;
}

// TF_CAPI_EXPORT extern TF_OperationDescription* TF_NewOperation(TF_Graph* graph,
//                                                                const char* op_type,
//                                                                const char* oper_name);
octave_value OCT_TF_NewOperation (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_NewOperation' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Graph parsed to the 'TF_NewOperation' C API function.");
  }
  // Check octave_value type for character vector of Operation type
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character vector defining the "
           "operation type parsed to the 'TF_NewOperation' C API function.");
  }
  // Check octave_value type for character vector of Operation name
  if (! args(3).is_char_matrix () || args(3).rows () != 1)
  {
    error ("tensorflow: 4th argument must be a character vector defining the "
           "operation name parsed to the 'TF_NewOperation' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  // Get character vector of Operation type in Graph
  charMatrix op_type = args(2).char_matrix_value ();
  // Get character vector of Operation name in Graph
  charMatrix op_name = args(3).char_matrix_value ();
  // Get new operation
  TF_OperationDescription* op_desc = TF_NewOperation (graph, op_type.data (),
                                                     op_name.data ());
  octave_uint64 str_ptr = (uint64_t) op_desc;
  octave_value plhs = str_ptr;
  return plhs;
}

// TF_CAPI_EXPORT extern TF_Operation* TF_GraphOperationByName(TF_Graph* graph,
//                                                             const char* oper_name);
octave_value OCT_TF_GraphOperationByName (OCT_ARGS)
{
  if (nrhs < 3)
  {
    error ("tensorflow: two extra arguments are required "
           "for the 'TF_GraphOperationByName' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Graph parsed to the 'TF_GraphOperationByName' C API function.");
  }
  // Check octave_value type for character vector of Operation name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character "
           "vector defining the operation name parsed to "
           "the 'TF_GraphOperationByName' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  // Get character vector of Operation name in Graph
  charMatrix op_name = args(2).char_matrix_value ();
  // Get operation
  TF_Operation* oper = TF_GraphOperationByName (graph, op_name.data ());
  octave_uint64 str_ptr = (uint64_t) oper;
  octave_value plhs = str_ptr;
  return plhs;
}

// TF_CAPI_EXPORT extern TF_Operation* TF_GraphNextOperation(TF_Graph* graph,
//                                                           size_t* pos);
octave_value OCT_TF_GraphNextOperation (OCT_ARGS)
{
  if (nrhs < 3)
  {
    error ("tensorflow: two extra arguments are required "
           "for the 'TF_GraphNextOperation' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Graph parsed to the 'TF_GraphNextOperation' C API function.");
  }
  // Check octave_value type for position of Operation
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar "
           "value defining the position of operation parsed to "
           "the 'TF_GraphNextOperation' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  // Get position of Operation in Graph
  size_t* op_pos = (size_t*) args(2).int64_value ();
  // Get operation
  TF_Operation* oper = TF_GraphNextOperation (graph, op_pos);
  octave_uint64 str_ptr = (uint64_t) oper;
  octave_value plhs = str_ptr;
  return plhs;
}

// TF_CAPI_EXPORT extern void TF_GraphToGraphDef(TF_Graph* graph,
//                                               TF_Buffer* output_graph_def,
//                                               TF_Status* status);
void OCT_TF_GraphToGraphDef (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_GraphToGraphDef' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Graph parsed to the 'TF_GraphToGraphDef' C API function.");
  }
  // Check octave_value type for pointer to Buffer
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer to "
           "the Buffer parsed to the 'TF_GraphToGraphDef' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(3).is_uint64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 scalar pointer to "
           "the Status parsed to the 'TF_GraphToGraphDef' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  // Get pointer to Buffer
  TF_Buffer* output_graph_def = (TF_Buffer*) args(2).uint64_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(3).uint64_value ();
  // Get output Graph definition to Buffer
  TF_GraphToGraphDef (graph, output_graph_def, status);
}

// TF_CAPI_EXPORT extern void TF_GraphGetOpDef(TF_Graph* graph,
//                                             const char* op_name,
//                                             TF_Buffer* output_op_def,
//                                             TF_Status* status);
void OCT_TF_GraphGetOpDef (OCT_ARGS)
{
  if (nrhs < 5)
  {
    error ("tensorflow: four extra arguments are required "
           "for the 'TF_GraphGetOpDef' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Graph parsed to the 'TF_GraphGetOpDef' C API function.");
  }
  // Check octave_value type for character vector of Operation name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character vector defining the "
           "operation name parsed to the 'TF_GraphGetOpDef' C API function.");
  }
  // Check octave_value type for pointer to Buffer
  if (! args(3).is_uint64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 scalar pointer to "
           "the Buffer parsed to the 'TF_GraphGetOpDef' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(4).is_uint64_type () || ! args(4).is_scalar_type ())
  {
    error ("tensorflow: 5th argument must be an uint64 scalar pointer to "
           "the Status parsed to the 'TF_GraphGetOpDef' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  // Get character vector of Operation name in Graph
  charMatrix op_name = args(2).char_matrix_value ();
  // Get pointer to Buffer
  TF_Buffer* output_op_def = (TF_Buffer*) args(3).uint64_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(4).uint64_value ();
  // Get output Operation definition to Buffer
  TF_GraphGetOpDef (graph, op_name.data (), output_op_def, status);
}

// TF_CAPI_EXPORT extern void TF_GraphVersions(TF_Graph* graph,
//                                             TF_Buffer* output_version_def,
//                                             TF_Status* status);
void OCT_TF_GraphVersions (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_GraphVersions' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Graph parsed to the 'TF_GraphVersions' C API function.");
  }
  // Check octave_value type for pointer to Buffer
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer to "
           "the Buffer parsed to the 'TF_GraphVersions' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(3).is_uint64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 scalar pointer to "
           "the Status parsed to the 'TF_GraphVersions' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  // Get pointer to Buffer
  TF_Buffer* output_version_def = (TF_Buffer*) args(2).uint64_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(3).uint64_value ();
  // Get Tensor number of dimensions referenced by Output in Graph
  TF_GraphVersions (graph, output_version_def, status);
}

// TF_CAPI_EXPORT extern TF_ImportGraphDefResults* TF_GraphImportGraphDefWithResults(
//                                                 TF_Graph* graph, const TF_Buffer* graph_def,
//                                                 const TF_ImportGraphDefOptions* options,
//                                                 TF_Status* status);
octave_value OCT_TF_GraphImportGraphDefWithResults (OCT_ARGS)
{
  if (nrhs < 5)
  {
    error ("tensorflow: four extra arguments are required for the "
           "'TF_GraphImportGraphDefWithResults' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 "
           "scalar pointer to the Graph parsed to the "
           "'TF_GraphImportGraphDefWithResults' C API function.");
  }
  // Check octave_value type for pointer to Buffer
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 "
           "scalar pointer to the Buffer parsed to the "
           "'TF_GraphImportGraphDefWithResults' C API function.");
  }
  // Check octave_value type for pointer to ImportGraphDefOptions
  if (! args(3).is_uint64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 scalar "
           "pointer to the ImportGraphDefOptions parsed to the "
           "'TF_GraphImportGraphDefWithResults' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(4).is_uint64_type () || ! args(4).is_scalar_type ())
  {
    error ("tensorflow: 5th argument must be an uint64 "
           "scalar pointer to the Status parsed to the "
           "'TF_GraphImportGraphDefWithResults' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  // Get pointer to Buffer
  const TF_Buffer* graph_def = (TF_Buffer*) args(2).uint64_value ();
  // Get pointer to ImportGraphDefOptions
  const TF_ImportGraphDefOptions* options = (TF_ImportGraphDefOptions*)
                                             args(3).uint64_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(4).uint64_value ();
  // Get ImportGraphDefResults and return its pointer
  TF_ImportGraphDefResults* graph_def_res = TF_GraphImportGraphDefWithResults (
                                            graph, graph_def, options, status);
  octave_uint64 gdr_ptr = (uint64_t) graph_def_res;
  octave_value plhs = gdr_ptr;
  return plhs;
}

// TF_CAPI_EXPORT extern void TF_GraphImportGraphDefWithReturnOutputs(TF_Graph* graph,
//                                                                    const TF_Buffer* graph_def,
//                                                                    const TF_ImportGraphDefOptions* options,
//                                                                    TF_Output* return_outputs,
//                                                                    int num_return_outputs,
//                                                                    TF_Status* status);
void OCT_TF_GraphImportGraphDefWithReturnOutputs (OCT_ARGS)
{
  if (nrhs < 7)
  {
    error ("tensorflow: six extra arguments are required for the "
           "'TF_GraphImportGraphDefWithReturnOutputs' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 "
           "scalar pointer to the Graph parsed to the "
           "'TF_GraphImportGraphDefWithReturnOutputs' C API function.");
  }
  // Check octave_value type for pointer to Buffer
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 "
           "scalar pointer to the Buffer parsed to the "
           "'TF_GraphImportGraphDefWithReturnOutputs' C API function.");
  }
  // Check octave_value type for pointer to ImportGraphDefOptions
  if (! args(3).is_uint64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 scalar "
           "pointer to the ImportGraphDefOptions parsed to the "
           "'TF_GraphImportGraphDefWithReturnOutputs' C API function.");
  }
  // Check octave_value type for pointer to Output(s)
  if (! args(4).is_uint64_type () || ! args(4).is_scalar_type ())
  {
    error ("tensorflow: 5th argument must be an uint64 scalar "
           "pointer to the Output parsed to the "
           "'TF_GraphImportGraphDefWithReturnOutputs' C API function.");
  }
  // Check octave_value type for number of return Output(s)
  if (! args(5).is_int32_type () || ! args(5).is_scalar_type ())
  {
    error ("tensorflow: 6th argument must be an int32 scalar value "
           "with the number of Output parsed to the "
           "'TF_GraphImportGraphDefWithReturnOutputs' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(6).is_uint64_type () || ! args(6).is_scalar_type ())
  {
    error ("tensorflow: 7th argument must be an uint64 "
           "scalar pointer to the Status parsed to the "
           "'TF_GraphImportGraphDefWithReturnOutputs' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  // Get pointer to Buffer
  const TF_Buffer* graph_def = (TF_Buffer*) args(2).uint64_value ();
  // Get pointer to ImportGraphDefOptions
  const TF_ImportGraphDefOptions* options = (TF_ImportGraphDefOptions*)
                                             args(3).uint64_value ();
  // Get pointer to Output(s)
  TF_Output* output = (TF_Output*) args(4).uint64_value ();
  // Get number of return Output(s)
  int num_return_outputs = args(5).int32_scalar_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(6).uint64_value ();
  // Import Graph definition with return Output(s)
  TF_GraphImportGraphDefWithReturnOutputs (graph, graph_def, options, output,
                                           num_return_outputs, status);
}

// TF_CAPI_EXPORT extern void TF_GraphImportGraphDef(TF_Graph* graph,
//                                                   const TF_Buffer* graph_def,
//                                                   const TF_ImportGraphDefOptions* options,
//                                                   TF_Status* status);
void OCT_TF_GraphImportGraphDef (OCT_ARGS)
{
  if (nrhs < 5)
  {
    error ("tensorflow: four extra arguments are required for "
           "the 'TF_GraphImportGraphDef' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Graph parsed to the 'TF_GraphImportGraphDef' C API function.");
  }
  // Check octave_value type for pointer to Buffer
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer to the "
           "Buffer parsed to the 'TF_GraphImportGraphDef' C API function.");
  }
  // Check octave_value type for pointer to ImportGraphDefOptions
  if (! args(3).is_uint64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 scalar "
           "pointer to the ImportGraphDefOptions parsed to the "
           "'TF_GraphImportGraphDef' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(4).is_uint64_type () || ! args(4).is_scalar_type ())
  {
    error ("tensorflow: 5th argument must be an uint64 scalar pointer to the "
           "Status parsed to the 'TF_GraphImportGraphDef' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  // Get pointer to Buffer
  const TF_Buffer* graph_def = (TF_Buffer*) args(2).uint64_value ();
  // Get pointer to ImportGraphDefOptions
  const TF_ImportGraphDefOptions* options = (TF_ImportGraphDefOptions*)
                                             args(3).uint64_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(4).uint64_value ();
  // Import Graph definitions
  TF_GraphImportGraphDef (graph, graph_def, options, status);
}

// TF_CAPI_EXPORT extern void TF_GraphCopyFunction(TF_Graph* g,
//                                                 const TF_Function* func,
//                                                 const TF_Function* grad,
//                                                 TF_Status* status);
void OCT_TF_GraphCopyFunction (OCT_ARGS)
{
  if (nrhs < 5)
  {
    error ("tensorflow: four extra arguments are required for the "
           "'TF_GraphCopyFunction' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Graph parsed to the 'TF_GraphCopyFunction' C API function.");
  }
  // Check octave_value type for pointer to Function
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer to the "
           "Function parsed to the 'TF_GraphCopyFunction' C API function.");
  }
  // Check octave_value type for pointer to Gradient
  if (! args(3).is_uint64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 scalar pointer to the "
           "Gradient parsed to the 'TF_GraphCopyFunction' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(4).is_uint64_type () || ! args(4).is_scalar_type ())
  {
    error ("tensorflow: 5th argument must be an uint64 scalar pointer to "
           "the Status parsed to the 'TF_GraphCopyFunction' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  // Get pointer to Function
  const TF_Function* func = (TF_Function*) args(2).uint64_value ();
  // Get pointer to Gradient
  const TF_Function* grad = (TF_Function*) args(3).uint64_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(4).uint64_value ();
  // Import function and its gradient into Graph
  TF_GraphCopyFunction (graph, func, grad, status);
}

// TF_CAPI_EXPORT extern int TF_GraphNumFunctions(TF_Graph* g);
octave_value OCT_TF_GraphNumFunctions (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_GraphNumFunctions' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Graph parsed to the 'TF_GraphNumFunctions' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  // Get number of functions in Graph
  octave_int32 num_func = TF_GraphNumFunctions (graph);
  octave_value plhs = num_func;
  return plhs;
}

// TF_CAPI_EXPORT extern int TF_GraphGetFunctions(TF_Graph* g, TF_Function** funcs,
//                                                int max_func, TF_Status* status);
octave_value OCT_TF_GraphGetFunctions (OCT_ARGS)
{
  if (nrhs < 3)
  {
    error ("tensorflow: two extra arguments are required "
           "for the 'TF_GraphGetFunctions' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Graph parsed to the 'TF_GraphGetFunctions' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer to "
           "the Status parsed to the 'TF_GraphGetFunctions' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  // Get maximum number of functions from Graph
  int max_func = TF_GraphNumFunctions (graph);
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(3).uint64_value ();
  // Create an array of pointers to Functions to be retrieved from Graph
  TF_Function** funcs = new TF_Function*[max_func];
  // Get Function pointers from Graph
  int ret_func = TF_GraphGetFunctions (graph, funcs, max_func, status);
  // Copy pointers to retrieved functions into returning octave value
  dim_vector oct_dims;
  oct_dims.resize (2);
  oct_dims(0) = 1;
  oct_dims(1) = max_func;
  uint64NDArray oct_data(oct_dims);
  for (int i = 0; i < ret_func; i++)
  {
    oct_data(0,i) = (uint64_t) *(funcs + i);
  }
  octave_value plhs = oct_data;
  return plhs;
}

// TF_CAPI_EXPORT extern TF_WhileParams TF_NewWhile(TF_Graph* g, TF_Output* inputs,
//                                                  int ninputs, TF_Status* status);
octave_value OCT_TF_NewWhile (OCT_ARGS)
{
  if (nrhs < 5)
  {
    error ("tensorflow: four extra arguments are required "
           "for the 'TF_NewWhile' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Graph parsed to the 'TF_NewWhile' C API function.");
  }
  // Check octave_value type for pointer to Output
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer "
           "to the Output parsed to the 'TF_NewWhile' C API function.");
  }
  // Check octave_value type for number of inputs
  if (! args(3).is_int32_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an int32 scalar value defining "
           "the number of inputs parsed to the 'TF_NewWhile' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(4).is_uint64_type () || ! args(4).is_scalar_type ())
  {
    error ("tensorflow: 5th argument must be an uint64 scalar pointer "
           "to the Status parsed to the 'TF_NewWhile' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  // Get pointer to Output
  TF_Output* inputs = (TF_Output*) args(2).uint64_value ();
  // Get number of inputs
  int ninputs = args(3).int_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(4).uint64_value ();
  // Get WhileParams and return its pointer
  TF_WhileParams wp = TF_NewWhile (graph, inputs, ninputs, status);
  TF_WhileParams* ret_wp = &wp;
  octave_uint64 wp_ptr = (uint64_t) ret_wp;
  octave_value plhs = wp_ptr;
  return plhs;
}

// TF_CAPI_EXPORT void TF_AddGradients(TF_Graph* g, TF_Output* y, int ny,
//                                     TF_Output* x, int nx, TF_Output* dx,
//                                     TF_Status* status, TF_Output* dy);
void OCT_TF_AddGradients (OCT_ARGS)
{
  if (nrhs < 9)
  {
    error ("tensorflow: eight extra arguments are required "
           "for the 'TF_AddGradients' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Graph parsed to the 'TF_AddGradients' C API function.");
  }
  // Check octave_value type for pointer to Output y
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer to "
           "the Output 'y' parsed to the 'TF_AddGradients' C API function.");
  }
  // Check octave_value type for number of inputs y
  if (! args(3).is_int32_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an int32 scalar "
           "value defining the number of inputs 'y' parsed to "
           "the 'TF_AddGradients' C API function.");
  }
  // Check octave_value type for pointer to Output x
  if (! args(4).is_uint64_type () || ! args(4).is_scalar_type ())
  {
    error ("tensorflow: 5th argument must be an uint64 scalar pointer to "
           "the Output 'x' parsed to the 'TF_AddGradients' C API function.");
  }
  // Check octave_value type for number of inputs x
  if (! args(5).is_int32_type () || ! args(5).is_scalar_type ())
  {
    error ("tensorflow: 6th argument must be an int32 scalar "
           "value defining the number of inputs 'x' parsed to "
           "the 'TF_AddGradients' C API function.");
  }
  // Check octave_value type for pointer to Output dx
  if (! args(6).is_uint64_type () || ! args(6).is_scalar_type ())
  {
    error ("tensorflow: 7th argument must be an uint64 scalar pointer to "
           "the Output 'dx' parsed to the 'TF_AddGradients' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(7).is_uint64_type () || ! args(7).is_scalar_type ())
  {
    error ("tensorflow: 8th argument must be an uint64 scalar pointer "
           "to the Status parsed to the 'TF_AddGradients' C API function.");
  }
  // Check octave_value type for pointer to Output dy
  if (! args(8).is_uint64_type () || ! args(8).is_scalar_type ())
  {
    error ("tensorflow: 9th argument must be an uint64 scalar pointer to "
           "the Output 'dy' parsed to the 'TF_AddGradients' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  // Get pointer to Output y
  TF_Output* y = (TF_Output*) args(2).uint64_value ();
  // Get number of inputs y
  int ny = args(3).int_value ();
  // Get pointer to Output x
  TF_Output* x = (TF_Output*) args(4).uint64_value ();
  // Get number of inputs x
  int nx = args(5).int_value ();
  // Get pointer to Output dx
  TF_Output* dx = (TF_Output*) args(6).uint64_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(7).uint64_value ();
  // Get pointer to Output dy
  TF_Output* dy = (TF_Output*) args(8).uint64_value ();
  // Add Gradient
  TF_AddGradients (graph, y, ny, x, nx, dx, status, dy);
}

// TF_CAPI_EXPORT void TF_AddGradientsWithPrefix(TF_Graph* g, const char* prefix,
//                                               TF_Output* y, int ny,
//                                               TF_Output* x, int nx,
//                                               TF_Output* dx, TF_Status* status,
//                                               TF_Output* dy);
void OCT_TF_AddGradientsWithPrefix (OCT_ARGS)
{
  if (nrhs < 10)
  {
    error ("tensorflow: nine extra arguments are required "
           "for the 'TF_AddGradientsWithPrefix' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "Graph parsed to the 'TF_AddGradientsWithPrefix' C API function.");
  }
  // Check octave_value type for character vector of prefix name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character vector defining the "
           "prefix name parsed to the 'TF_AddGradientsWithPrefix' C API function.");
  }
  // Check octave_value type for pointer to Output y
  if (! args(3).is_uint64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 scalar pointer to the "
           "Output 'y' parsed to the 'TF_AddGradientsWithPrefix' C API function.");
  }
  // Check octave_value type for number of inputs y
  if (! args(4).is_int32_type () || ! args(4).is_scalar_type ())
  {
    error ("tensorflow: 5th argument must be an int32 scalar "
           "value defining the number of inputs 'y' parsed to the "
           "'TF_AddGradientsWithPrefix' C API function.");
  }
  // Check octave_value type for pointer to Output x
  if (! args(5).is_uint64_type () || ! args(5).is_scalar_type ())
  {
    error ("tensorflow: 6th argument must be an uint64 scalar pointer to the "
           "Output 'x' parsed to the 'TF_AddGradientsWithPrefix' C API function.");
  }
  // Check octave_value type for number of inputs x
  if (! args(6).is_int32_type () || ! args(6).is_scalar_type ())
  {
    error ("tensorflow: 7th argument must be an int32 scalar "
           "value defining the number of inputs 'x' parsed to the "
           "'TF_AddGradientsWithPrefix' C API function.");
  }
  // Check octave_value type for pointer to Output dx
  if (! args(7).is_uint64_type () || ! args(7).is_scalar_type ())
  {
    error ("tensorflow: 8th argument must be an uint64 scalar pointer to the "
           "Output 'dx' parsed to the 'TF_AddGradientsWithPrefix' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(8).is_uint64_type () || ! args(8).is_scalar_type ())
  {
    error ("tensorflow: 9th argument must be an uint64 scalar pointer to the "
           "Status parsed to the 'TF_AddGradientsWithPrefix' C API function.");
  }
  // Check octave_value type for pointer to Output dy
  if (! args(9).is_uint64_type () || ! args(9).is_scalar_type ())
  {
    error ("tensorflow: 10th argument must be an uint64 scalar pointer to the "
           "Output 'dy' parsed to the 'TF_AddGradientsWithPrefix' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  // Get character vector of Operation name in Graph
  charMatrix prefix = args(2).char_matrix_value ();
  // Get pointer to Output y
  TF_Output* y = (TF_Output*) args(3).uint64_value ();
  // Get number of inputs y
  int ny = args(4).int_value ();
  // Get pointer to Output x
  TF_Output* x = (TF_Output*) args(5).uint64_value ();
  // Get number of inputs x
  int nx = args(6).int_value ();
  // Get pointer to Output dx
  TF_Output* dx = (TF_Output*) args(7).uint64_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(8).uint64_value ();
  // Get pointer to Output dy
  TF_Output* dy = (TF_Output*) args(9).uint64_value ();
  // Add Gradient
  TF_AddGradientsWithPrefix (graph, prefix.data (), y, ny, x, nx, dx, status, dy);
}

// TF_CAPI_EXPORT extern TF_Function* TF_GraphToFunction(const TF_Graph* fn_body,
//                       const char* fn_name, unsigned char append_hash_to_fn_name,
//                       int num_opers, const TF_Operation* const* opers, int ninputs,
//                       const TF_Output* inputs, int noutputs, const TF_Output* outputs,
//                       const char* const* output_names, const TF_FunctionOptions* opts,
//                       const char* description, TF_Status* status);
octave_value OCT_TF_GraphToFunction (OCT_ARGS)
{
  error ("tensorflow: 'TF_GraphToFunction' C API function not supported yet.");
}

// TF_CAPI_EXPORT extern TF_Function* TF_GraphToFunctionWithControlOutputs(const TF_Graph* fn_body,
//                       const char* fn_name, unsigned char append_hash_to_fn_name, int num_opers,
//                       const TF_Operation* const* opers, int ninputs, const TF_Output* inputs,
//                       int noutputs, const TF_Output* outputs, const char* const* output_names,
//                       int ncontrol_outputs, const TF_Operation* const* control_outputs,
//                       const char* const* control_output_names, const TF_FunctionOptions* opts,
//                       const char* description, TF_Status* status);
octave_value OCT_TF_GraphToFunctionWithControlOutputs (OCT_ARGS)
{
  error ("tensorflow: 'TF_GraphToFunctionWithControlOutputs' C API function not supported yet.");
}
