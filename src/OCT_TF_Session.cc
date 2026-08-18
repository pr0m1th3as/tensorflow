/*
Copyright (C) 2026 Andreas Bertsatos <abertsatos@biol.uoa.gr>

This file is part of the tensorflow package for GNU Octave.

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

#include <vector>

#include "tensorflow.h"

// -----------------------------------------------------------------------------
// C API functions referenced by the TF_SessionOptions classdef
// -----------------------------------------------------------------------------

// TF_CAPI_EXPORT extern TF_SessionOptions* TF_NewSessionOptions(void);
octave_value OCT_TF_NewSessionOptions (void)
{
  TF_SessionOptions* newOptions = TF_NewSessionOptions ();
  octave_uint64 ptr = (uint64_t) newOptions;
  octave_value plhs = ptr;
  return plhs;
}

// TF_CAPI_EXPORT extern void TF_SetTarget(TF_SessionOptions* options,
//                                         const char* target);
void OCT_TF_SetTarget (OCT_ARGS)
{
  if (nrhs < 3)
  {
    error ("tensorflow: two extra arguments are required "
           "for the 'TF_SetTarget' C API function.");
  }
  // Check octave_value type for pointer to SessionOptions
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "SessionOptions parsed to the 'TF_SetTarget' C API function.");
  }
  // Check octave_value type for character vector of target
  if (! args(2).is_char_matrix () || args(2).rows () > 1)
  {
    error ("tensorflow: 3rd argument must be a character vector defining "
           "the target parsed to the 'TF_SetTarget' C API function.");
  }
  // Get pointer to SessionOptions
  TF_SessionOptions* options = (TF_SessionOptions*) args(1).uint64_value ();
  // Get character vector of target
  string target = args(2).string_value ();
  // Set target for SessionOptions
  TF_SetTarget (options, target.c_str ());
}

// TF_CAPI_EXPORT extern void TF_SetConfig(TF_SessionOptions* options,
//                                         const void* proto, size_t proto_len,
//                                         TF_Status* status);
void OCT_TF_SetConfig (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_SetConfig' C API function.");
  }
  // Check octave_value type for pointer to SessionOptions
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "SessionOptions parsed to the 'TF_SetConfig' C API function.");
  }
  // Check octave_value type for serialized ConfigProto
  if (! (args(2).is_char_matrix () || args(2).is_uint8_type ())
      || args(2).rows () > 1)
  {
    error ("tensorflow: 3rd argument must be either a character or a uint8 "
           "vector containing a serialized ConfigProto parsed to the "
           "'TF_SetConfig' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(3).is_uint64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 scalar pointer to "
           "the Status parsed to the 'TF_SetConfig' C API function.");
  }
  // Get pointer to SessionOptions
  TF_SessionOptions* options = (TF_SessionOptions*) args(1).uint64_value ();
  // Get serialized ConfigProto
  const void* proto = args(2).mex_get_data ();
  size_t proto_len = (size_t) args(2).numel ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(3).uint64_value ();
  // Set config for SessionOptions
  TF_SetConfig (options, proto, proto_len, status);
}

// TF_CAPI_EXPORT extern void TF_DeleteSessionOptions(TF_SessionOptions*);
void OCT_TF_DeleteSessionOptions (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_DeleteSessionOptions' C API function.");
  }
  // Check octave_value type for pointer to SessionOptions
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the SessionOptions parsed to the 'TF_DeleteSessionOptions' "
           "C API function.");
  }
  // Get pointer to SessionOptions
  TF_SessionOptions* options = (TF_SessionOptions*) args(1).uint64_value ();
  TF_DeleteSessionOptions (options);
}

// -----------------------------------------------------------------------------
// C API functions referenced by the TF_Session classdef
// -----------------------------------------------------------------------------

// TF_CAPI_EXPORT extern TF_Session* TF_NewSession(TF_Graph* graph,
//                                                 const TF_SessionOptions* opts,
//                                                 TF_Status* status);
octave_value OCT_TF_NewSession (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_NewSession' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Graph parsed to the 'TF_NewSession' C API function.");
  }
  // Check octave_value type for pointer to SessionOptions
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer to the "
           "SessionOptions parsed to the 'TF_NewSession' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(3).is_uint64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 scalar pointer to "
           "the Status parsed to the 'TF_NewSession' C API function.");
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(1).uint64_value ();
  // Get pointer to SessionOptions
  const TF_SessionOptions* opts = (TF_SessionOptions*) args(2).uint64_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(3).uint64_value ();
  // Get Session and return its pointer
  TF_Session* session = TF_NewSession (graph, opts, status);
  octave_uint64 ptr = (uint64_t) session;
  octave_value plhs = ptr;
  return plhs;
}

// TF_CAPI_EXPORT extern TF_Session* TF_LoadSessionFromSavedModel(
//     const TF_SessionOptions* session_options, const TF_Buffer* run_options,
//     const char* export_dir, const char* const* tags, int tags_len,
//     TF_Graph* graph, TF_Buffer* meta_graph_def, TF_Status* status);
octave_value OCT_TF_LoadSessionFromSavedModel (OCT_ARGS)
{
  if (nrhs < 8)
  {
    error ("tensorflow: seven extra arguments are required for the "
           "'TF_LoadSessionFromSavedModel' C API function.");
  }
  // Check octave_value type for pointer to SessionOptions
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "SessionOptions parsed to the 'TF_LoadSessionFromSavedModel' "
           "C API function.");
  }
  // Check octave_value type for pointer to run options Buffer, 0 for none
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer to the "
           "run options Buffer, or 0 for none, parsed to the "
           "'TF_LoadSessionFromSavedModel' C API function.");
  }
  // Check octave_value type for character vector of export directory
  if (! args(3).is_char_matrix () || args(3).rows () != 1)
  {
    error ("tensorflow: 4th argument must be a character vector defining the "
           "export directory parsed to the 'TF_LoadSessionFromSavedModel' "
           "C API function.");
  }
  // Check octave_value type for tags
  if (! (args(4).iscellstr () || args(4).is_char_matrix ())
      || args(4).rows () != 1)
  {
    error ("tensorflow: 5th argument must be a cellstr vector, or a character "
           "vector for a single tag, defining the tags parsed to the "
           "'TF_LoadSessionFromSavedModel' C API function.");
  }
  // Check octave_value type for pointer to Graph
  if (! args(5).is_uint64_type () || ! args(5).is_scalar_type ())
  {
    error ("tensorflow: 6th argument must be an uint64 scalar pointer to the "
           "Graph parsed to the 'TF_LoadSessionFromSavedModel' "
           "C API function.");
  }
  // Check octave_value type for pointer to MetaGraphDef Buffer, 0 for none
  if (! args(6).is_uint64_type () || ! args(6).is_scalar_type ())
  {
    error ("tensorflow: 7th argument must be an uint64 scalar pointer to the "
           "MetaGraphDef Buffer, or 0 for none, parsed to the "
           "'TF_LoadSessionFromSavedModel' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(7).is_uint64_type () || ! args(7).is_scalar_type ())
  {
    error ("tensorflow: 8th argument must be an uint64 scalar pointer to the "
           "Status parsed to the 'TF_LoadSessionFromSavedModel' "
           "C API function.");
  }
  // Get pointer to SessionOptions
  const TF_SessionOptions* opts = (TF_SessionOptions*) args(1).uint64_value ();
  // Get pointer to run options Buffer
  const TF_Buffer* run_options = (TF_Buffer*) args(2).uint64_value ();
  // Get export directory
  string export_dir = args(3).string_value ();
  // Get tags, keeping the strings alive for the duration of the call
  Array<string> oct_tags = args(4).cellstr_value ();
  int tags_len = (int) oct_tags.numel ();
  vector<const char*> tags (tags_len);
  for (int i = 0; i < tags_len; i++)
  {
    tags[i] = oct_tags(i).c_str ();
  }
  // Get pointer to Graph
  TF_Graph* graph = (TF_Graph*) args(5).uint64_value ();
  // Get pointer to MetaGraphDef Buffer
  TF_Buffer* meta_graph_def = (TF_Buffer*) args(6).uint64_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(7).uint64_value ();
  // Load Session from SavedModel and return its pointer
  TF_Session* session = TF_LoadSessionFromSavedModel (opts, run_options,
                                                      export_dir.c_str (),
                                                      tags.data (), tags_len,
                                                      graph, meta_graph_def,
                                                      status);
  octave_uint64 ptr = (uint64_t) session;
  octave_value plhs = ptr;
  return plhs;
}

// TF_CAPI_EXPORT extern void TF_CloseSession(TF_Session*, TF_Status* status);
void OCT_TF_CloseSession (OCT_ARGS)
{
  if (nrhs < 3)
  {
    error ("tensorflow: two extra arguments are required "
           "for the 'TF_CloseSession' C API function.");
  }
  // Check octave_value type for pointer to Session
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Session parsed to the 'TF_CloseSession' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer to "
           "the Status parsed to the 'TF_CloseSession' C API function.");
  }
  // Get pointer to Session
  TF_Session* session = (TF_Session*) args(1).uint64_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(2).uint64_value ();
  TF_CloseSession (session, status);
}

// TF_CAPI_EXPORT extern void TF_DeleteSession(TF_Session*, TF_Status* status);
void OCT_TF_DeleteSession (OCT_ARGS)
{
  if (nrhs < 3)
  {
    error ("tensorflow: two extra arguments are required "
           "for the 'TF_DeleteSession' C API function.");
  }
  // Check octave_value type for pointer to Session
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Session parsed to the 'TF_DeleteSession' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer to "
           "the Status parsed to the 'TF_DeleteSession' C API function.");
  }
  // Get pointer to Session
  TF_Session* session = (TF_Session*) args(1).uint64_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(2).uint64_value ();
  TF_DeleteSession (session, status);
}

// TF_CAPI_EXPORT extern void TF_SessionRun(
//     TF_Session* session, const TF_Buffer* run_options,
//     const TF_Output* inputs, TF_Tensor* const* input_values, int ninputs,
//     const TF_Output* outputs, TF_Tensor** output_values, int noutputs,
//     const TF_Operation* const* target_opers, int ntargets,
//     TF_Buffer* run_metadata, TF_Status*);
//
// The number of inputs, outputs and targets is taken from the number of
// elements of the corresponding vectors of pointers, hence the 'ninputs',
// 'noutputs' and 'ntargets' arguments of the C API function are omitted.  The
// output tensors are returned as an uint64 vector of pointers instead of being
// written into a caller supplied array.
octave_value OCT_TF_SessionRun (OCT_ARGS)
{
  if (nrhs < 9)
  {
    error ("tensorflow: eight extra arguments are required "
           "for the 'TF_SessionRun' C API function.");
  }
  // Check octave_value type for pointer to Session
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Session parsed to the 'TF_SessionRun' C API function.");
  }
  // Check octave_value type for pointer to run options Buffer, 0 for none
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer to the "
           "run options Buffer, or 0 for none, parsed to the 'TF_SessionRun' "
           "C API function.");
  }
  // Check octave_value type for pointers to input Outputs
  if (! args(3).isempty ()
      && (! args(3).is_uint64_type () || args(3).rows () != 1))
  {
    error ("tensorflow: 4th argument must be an uint64 vector of pointers to "
           "the input Outputs parsed to the 'TF_SessionRun' C API function.");
  }
  // Check octave_value type for pointers to input Tensors
  if (! args(4).isempty ()
      && (! args(4).is_uint64_type () || args(4).rows () != 1))
  {
    error ("tensorflow: 5th argument must be an uint64 vector of pointers to "
           "the input Tensors parsed to the 'TF_SessionRun' C API function.");
  }
  // Check octave_value type for pointers to output Outputs
  if (! args(5).isempty ()
      && (! args(5).is_uint64_type () || args(5).rows () != 1))
  {
    error ("tensorflow: 6th argument must be an uint64 vector of pointers to "
           "the output Outputs parsed to the 'TF_SessionRun' C API function.");
  }
  // Check octave_value type for pointers to target Operations
  if (! args(6).isempty ()
      && (! args(6).is_uint64_type () || args(6).rows () != 1))
  {
    error ("tensorflow: 7th argument must be an uint64 vector of pointers to "
           "the target Operations parsed to the 'TF_SessionRun' "
           "C API function.");
  }
  // Check octave_value type for pointer to run metadata Buffer, 0 for none
  if (! args(7).is_uint64_type () || ! args(7).is_scalar_type ())
  {
    error ("tensorflow: 8th argument must be an uint64 scalar pointer to the "
           "run metadata Buffer, or 0 for none, parsed to the 'TF_SessionRun' "
           "C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(8).is_uint64_type () || ! args(8).is_scalar_type ())
  {
    error ("tensorflow: 9th argument must be an uint64 scalar pointer to "
           "the Status parsed to the 'TF_SessionRun' C API function.");
  }
  // Check that each input Output is matched by an input Tensor
  if (args(3).numel () != args(4).numel ())
  {
    error ("tensorflow: the 4th and 5th arguments must have the same number "
           "of elements parsed to the 'TF_SessionRun' C API function.");
  }
  // Get pointer to Session
  TF_Session* session = (TF_Session*) args(1).uint64_value ();
  // Get pointer to run options Buffer
  const TF_Buffer* run_options = (TF_Buffer*) args(2).uint64_value ();
  // Get input Outputs, which must be copied into a contiguous array of
  // structures, since the C API function does not take an array of pointers
  int ninputs = (int) args(3).numel ();
  uint64NDArray oct_inputs = args(3).uint64_array_value ();
  vector<TF_Output> inputs (ninputs);
  for (int i = 0; i < ninputs; i++)
  {
    inputs[i] = *((TF_Output*) (uint64_t) oct_inputs(i));
  }
  // Get input Tensors
  uint64NDArray oct_input_values = args(4).uint64_array_value ();
  vector<TF_Tensor*> input_values (ninputs);
  for (int i = 0; i < ninputs; i++)
  {
    input_values[i] = (TF_Tensor*) (uint64_t) oct_input_values(i);
  }
  // Get output Outputs
  int noutputs = (int) args(5).numel ();
  uint64NDArray oct_outputs = args(5).uint64_array_value ();
  vector<TF_Output> outputs (noutputs);
  for (int i = 0; i < noutputs; i++)
  {
    outputs[i] = *((TF_Output*) (uint64_t) oct_outputs(i));
  }
  // Allocate the array receiving the output Tensors
  vector<TF_Tensor*> output_values (noutputs, nullptr);
  // Get target Operations
  int ntargets = (int) args(6).numel ();
  uint64NDArray oct_targets = args(6).uint64_array_value ();
  vector<const TF_Operation*> target_opers (ntargets);
  for (int i = 0; i < ntargets; i++)
  {
    target_opers[i] = (const TF_Operation*) (uint64_t) oct_targets(i);
  }
  // Get pointer to run metadata Buffer
  TF_Buffer* run_metadata = (TF_Buffer*) args(7).uint64_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(8).uint64_value ();
  // Run the Session
  TF_SessionRun (session, run_options,
                 inputs.data (), input_values.data (), ninputs,
                 outputs.data (), output_values.data (), noutputs,
                 target_opers.data (), ntargets,
                 run_metadata, status);
  // Return the pointers to the output Tensors
  dim_vector oct_dims;
  oct_dims.resize (2);
  oct_dims(0) = noutputs > 0 ? 1 : 0;
  oct_dims(1) = noutputs;
  uint64NDArray out_values (oct_dims);
  for (int i = 0; i < noutputs; i++)
  {
    out_values(i) = (uint64_t) output_values[i];
  }
  octave_value plhs = out_values;
  return plhs;
}

// TF_CAPI_EXPORT extern TF_DeviceList* TF_SessionListDevices(
//     TF_Session* session, TF_Status* status);
octave_value OCT_TF_SessionListDevices (OCT_ARGS)
{
  if (nrhs < 3)
  {
    error ("tensorflow: two extra arguments are required "
           "for the 'TF_SessionListDevices' C API function.");
  }
  // Check octave_value type for pointer to Session
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "Session parsed to the 'TF_SessionListDevices' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer to the "
           "Status parsed to the 'TF_SessionListDevices' C API function.");
  }
  // Get pointer to Session
  TF_Session* session = (TF_Session*) args(1).uint64_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(2).uint64_value ();
  // Get DeviceList and return its pointer
  TF_DeviceList* devices = TF_SessionListDevices (session, status);
  octave_uint64 ptr = (uint64_t) devices;
  octave_value plhs = ptr;
  return plhs;
}

// -----------------------------------------------------------------------------
// C API functions referenced by the TF_DeviceList classdef
// -----------------------------------------------------------------------------

// TF_CAPI_EXPORT extern void TF_DeleteDeviceList(TF_DeviceList* list);
void OCT_TF_DeleteDeviceList (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_DeleteDeviceList' C API function.");
  }
  // Check octave_value type for pointer to DeviceList
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "DeviceList parsed to the 'TF_DeleteDeviceList' C API function.");
  }
  // Get pointer to DeviceList
  TF_DeviceList* list = (TF_DeviceList*) args(1).uint64_value ();
  TF_DeleteDeviceList (list);
}

// TF_CAPI_EXPORT extern int TF_DeviceListCount(const TF_DeviceList* list);
octave_value OCT_TF_DeviceListCount (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_DeviceListCount' C API function.");
  }
  // Check octave_value type for pointer to DeviceList
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "DeviceList parsed to the 'TF_DeviceListCount' C API function.");
  }
  // Get pointer to DeviceList
  const TF_DeviceList* list = (TF_DeviceList*) args(1).uint64_value ();
  octave_idx_type count = (octave_idx_type) TF_DeviceListCount (list);
  octave_value plhs = count;
  return plhs;
}

// TF_CAPI_EXPORT extern const char* TF_DeviceListName(const TF_DeviceList* list,
//                                                     int index,
//                                                     TF_Status* status);
octave_value OCT_TF_DeviceListName (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_DeviceListName' C API function.");
  }
  // Check octave_value type for pointer to DeviceList
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "DeviceList parsed to the 'TF_DeviceListName' C API function.");
  }
  // Check octave_value type for device index
  if (! args(2).is_int32_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an int32 scalar value defining "
           "the device index parsed to the 'TF_DeviceListName' "
           "C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(3).is_uint64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 scalar pointer to the "
           "Status parsed to the 'TF_DeviceListName' C API function.");
  }
  // Get pointer to DeviceList
  const TF_DeviceList* list = (TF_DeviceList*) args(1).uint64_value ();
  // Get device index
  int index = args(2).int_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(3).uint64_value ();
  // Get device name, which is a null pointer if the index is out of bounds
  const char* name = TF_DeviceListName (list, index, status);
  octave_value plhs = name == nullptr ? "" : name;
  return plhs;
}

// TF_CAPI_EXPORT extern const char* TF_DeviceListType(const TF_DeviceList* list,
//                                                     int index,
//                                                     TF_Status* status);
octave_value OCT_TF_DeviceListType (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_DeviceListType' C API function.");
  }
  // Check octave_value type for pointer to DeviceList
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "DeviceList parsed to the 'TF_DeviceListType' C API function.");
  }
  // Check octave_value type for device index
  if (! args(2).is_int32_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an int32 scalar value defining "
           "the device index parsed to the 'TF_DeviceListType' "
           "C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(3).is_uint64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 scalar pointer to the "
           "Status parsed to the 'TF_DeviceListType' C API function.");
  }
  // Get pointer to DeviceList
  const TF_DeviceList* list = (TF_DeviceList*) args(1).uint64_value ();
  // Get device index
  int index = args(2).int_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(3).uint64_value ();
  // Get device type, which is a null pointer if the index is out of bounds
  const char* type = TF_DeviceListType (list, index, status);
  octave_value plhs = type == nullptr ? "" : type;
  return plhs;
}

// TF_CAPI_EXPORT extern int64_t TF_DeviceListMemoryBytes(
//     const TF_DeviceList* list, int index, TF_Status* status);
octave_value OCT_TF_DeviceListMemoryBytes (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_DeviceListMemoryBytes' C API function.");
  }
  // Check octave_value type for pointer to DeviceList
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "DeviceList parsed to the 'TF_DeviceListMemoryBytes' "
           "C API function.");
  }
  // Check octave_value type for device index
  if (! args(2).is_int32_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an int32 scalar value defining "
           "the device index parsed to the 'TF_DeviceListMemoryBytes' "
           "C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(3).is_uint64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 scalar pointer to the "
           "Status parsed to the 'TF_DeviceListMemoryBytes' C API function.");
  }
  // Get pointer to DeviceList
  const TF_DeviceList* list = (TF_DeviceList*) args(1).uint64_value ();
  // Get device index
  int index = args(2).int_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(3).uint64_value ();
  // Get device memory, which is -1 if the index is out of bounds
  octave_int64 memory = TF_DeviceListMemoryBytes (list, index, status);
  octave_value plhs = memory;
  return plhs;
}

// TF_CAPI_EXPORT extern uint64_t TF_DeviceListIncarnation(
//     const TF_DeviceList* list, int index, TF_Status* status);
octave_value OCT_TF_DeviceListIncarnation (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_DeviceListIncarnation' C API function.");
  }
  // Check octave_value type for pointer to DeviceList
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "DeviceList parsed to the 'TF_DeviceListIncarnation' "
           "C API function.");
  }
  // Check octave_value type for device index
  if (! args(2).is_int32_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an int32 scalar value defining "
           "the device index parsed to the 'TF_DeviceListIncarnation' "
           "C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(3).is_uint64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 scalar pointer to the "
           "Status parsed to the 'TF_DeviceListIncarnation' C API function.");
  }
  // Get pointer to DeviceList
  const TF_DeviceList* list = (TF_DeviceList*) args(1).uint64_value ();
  // Get device index
  int index = args(2).int_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(3).uint64_value ();
  // Get device incarnation, which is 0 if the index is out of bounds
  octave_uint64 incarnation = TF_DeviceListIncarnation (list, index, status);
  octave_value plhs = incarnation;
  return plhs;
}
