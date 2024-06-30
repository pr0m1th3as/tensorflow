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
// C API functions referenced by the TF_Operation classdef
// -----------------------------------------------------------------------------

// TF_CAPI_EXPORT extern const char* TF_OperationName(TF_Operation* oper);
octave_value OCT_TF_OperationName (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_OperationName' C API function.");
  }
  // Check octave_value type for pointer to Operation
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Operation parsed to the 'TF_OperationName' C API function.");
  }
  // Get pointer to Operation
  TF_Operation* oper = (TF_Operation*) args(1).uint64_value ();
  // Get name of Operation
  const char* opname = TF_OperationName (oper);
  // Return name to Octave as charMatrix
  charMatrix op_name = opname;
  octave_value plhs = op_name;
  return plhs;
}

// TF_CAPI_EXPORT extern const char* TF_OperationOpType(TF_Operation* oper);
octave_value OCT_TF_OperationOpType (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_OperationOpType' C API function.");
  }
  // Check octave_value type for pointer to Operation
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Operation parsed to the 'TF_OperationOpType' C API function.");
  }
  // Get pointer to Operation
  TF_Operation* oper = (TF_Operation*) args(1).uint64_value ();
  // Get name of Operation
  const char* optype = TF_OperationOpType (oper);
  // Return name to Octave as charMatrix
  charMatrix op_type = optype;
  octave_value plhs = op_type;
  return plhs;
}

// TF_CAPI_EXPORT extern const char* TF_OperationDevice(TF_Operation* oper);
octave_value OCT_TF_OperationDevice (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_OperationDevice' C API function.");
  }
  // Check octave_value type for pointer to Operation
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Operation parsed to the 'TF_OperationDevice' C API function.");
  }
  // Get pointer to Operation
  TF_Operation* oper = (TF_Operation*) args(1).uint64_value ();
  // Get name of Operation
  const char* opdevice = TF_OperationDevice (oper);
  // Return name to Octave as charMatrix
  charMatrix op_device = opdevice;
  octave_value plhs = op_device;
  return plhs;
}

// TF_CAPI_EXPORT extern int TF_OperationNumOutputs(TF_Operation* oper);
octave_value OCT_TF_OperationNumOutputs (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required for "
           "the 'TF_OperationNumOutputs' C API function.");
  }
  // Check octave_value type for pointer to Operation
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "Operation parsed to the 'TF_OperationNumOutputs' C API function.");
  }
  // Get pointer to Operation
  TF_Operation* oper = (TF_Operation*) args(1).uint64_value ();
  // Get number of outputs of Operation
  int numoutputs = TF_OperationNumOutputs (oper);
  // Return number of outputs as int32
  octave_int32 num_outputs = numoutputs;
  octave_value plhs = num_outputs;
  return plhs;
}

// TF_CAPI_EXPORT extern int TF_OperationOutputListLength(TF_Operation* oper,
//                                                        const char* arg_name,
//                                                        TF_Status* status);
octave_value OCT_TF_OperationOutputListLength (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required for "
           "the 'TF_OperationOutputListLength' C API function.");
  }
  // Check octave_value type for pointer to Operation
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 "
           "scalar pointer to the Operation parsed to the "
           "'TF_OperationOutputListLength' C API function.");
  }
  // Check octave_value type for character vector of Operation output
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character vector "
           "defining the name of Output list of Operation parsed "
           "to the 'TF_OperationOutputListLength' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(3).is_uint64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 "
           "scalar pointer to the Status parsed to the "
           "'TF_OperationOutputListLength' C API function.");
  }
  // Get pointer to Operation
  TF_Operation* oper = (TF_Operation*) args(1).uint64_value ();
  // Get name of Output list
  charMatrix arg_name = args(2).char_matrix_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(3).uint64_value ();
  // Get length of Output list
  int listlen = TF_OperationOutputListLength (oper, arg_name.data (), status);
  // Return length to Octave as int32
  octave_int32 list_len = listlen;
  octave_value plhs = list_len;
  return plhs;
}

// TF_CAPI_EXPORT extern int TF_OperationNumInputs(TF_Operation* oper);
octave_value OCT_TF_OperationNumInputs (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required for "
           "the 'TF_OperationNumInputs' C API function.");
  }
  // Check octave_value type for pointer to Operation
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "Operation parsed to the 'TF_OperationNumInputs' C API function.");
  }
  // Get pointer to Operation
  TF_Operation* oper = (TF_Operation*) args(1).uint64_value ();
  // Get number of inputs of Operation
  int numinputs = TF_OperationNumInputs (oper);
  // Return number of inputs as int32
  octave_int32 num_inputs = numinputs;
  octave_value plhs = num_inputs;
  return plhs;
}

// TF_CAPI_EXPORT extern int TF_OperationInputListLength(TF_Operation* oper,
//                                                       const char* arg_name,
//                                                       TF_Status* status);
octave_value OCT_TF_OperationInputListLength (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required for "
           "the 'TF_OperationInputListLength' C API function.");
  }
  // Check octave_value type for pointer to Operation
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 "
           "scalar pointer to the Operation parsed to the "
           "'TF_OperationInputListLength' C API function.");
  }
  // Check octave_value type for character vector of Operation output
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character vector "
           "defining the name of Input list of Operation parsed "
           "to the 'TF_OperationInputListLength' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(3).is_uint64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 "
           "scalar pointer to the Status parsed to the "
           "'TF_OperationInputListLength' C API function.");
  }
  // Get pointer to Operation
  TF_Operation* oper = (TF_Operation*) args(1).uint64_value ();
  // Get name of Input list
  charMatrix arg_name = args(2).char_matrix_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(3).uint64_value ();
  // Get length of Input list
  int listlen = TF_OperationInputListLength (oper, arg_name.data (), status);
  // Return length to Octave as int32
  octave_int32 list_len = listlen;
  octave_value plhs = list_len;
  return plhs;
}

// TF_CAPI_EXPORT extern void TF_OperationAllInputs(TF_Operation* oper,
//                                                  TF_Output* inputs,
//                                                  int max_inputs);
octave_value OCT_TF_OperationAllInputs (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required for "
           "the 'TF_OperationAllInputs' C API function.");
  }
  // Check octave_value type for pointer to Operation
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "Operation parsed to the 'TF_OperationAllInputs' C API function.");
  }
  // Get pointer to Operation
  TF_Operation* oper = (TF_Operation*) args(1).uint64_value ();
  // Get number of inputs of Operation
  int max_inputs = TF_OperationNumInputs (oper);
  // Create an array of TF_Output inputs according to max_inputs
  TF_Output* inputs = reinterpret_cast<TF_Output*>
                      (malloc (sizeof (TF_Output) * max_inputs));
  // Get list of all inputs of Operation
  TF_OperationAllInputs (oper, inputs, max_inputs);
  // Return pointer to input array
  octave_uint64 ptr = (uint64_t) inputs;
  octave_value plhs = ptr;
  return plhs;
}

// TF_CAPI_EXPORT extern int TF_OperationNumControlInputs(TF_Operation* oper);
octave_value OCT_TF_OperationNumControlInputs (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required for "
           "the 'TF_OperationNumControlInputs' C API function.");
  }
  // Check octave_value type for pointer to Operation
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 "
           "scalar pointer to the Operation parsed to the "
           "'TF_OperationNumControlInputs' C API function.");
  }
  // Get pointer to Operation
  TF_Operation* oper = (TF_Operation*) args(1).uint64_value ();
  // Get number of control inputs of Operation
  int numctrlin = TF_OperationNumControlInputs (oper);
  // Return number of control inputs as int32
  octave_int32 num_ctrl_inputs = numctrlin;
  octave_value plhs = num_ctrl_inputs;
  return plhs;
}

// TF_CAPI_EXPORT extern int TF_OperationGetControlInputs(TF_Operation* oper,
//                                                        TF_Operation** control_inputs,
//                                                        int max_control_inputs);
octave_value OCT_TF_OperationGetControlInputs (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required for "
           "the 'TF_OperationGetControlInputs' C API function.");
  }
  // Check octave_value type for pointer to Operation
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 "
           "scalar pointer to the Operation parsed to the "
           "'TF_OperationGetControlInputs' C API function.");
  }
  // Get pointer to Operation
  TF_Operation* oper = (TF_Operation*) args(1).uint64_value ();
  // Get number of control inputs of Operation
  int max_control_inputs = TF_OperationNumControlInputs (oper);
  // Create an array of pointers to Operations to be retrieved from Operation
  TF_Operation** control_inputs = new TF_Operation*[max_control_inputs];
  // Get Function pointers from Graph
  int ret_control_inputs = TF_OperationGetControlInputs
                           (oper, control_inputs, max_control_inputs);
  // Copy pointers to retrieved Operations into returning octave value
  dim_vector oct_dims;
  oct_dims.resize (2);
  oct_dims(0) = 1;
  oct_dims(1) = max_control_inputs;
  uint64NDArray oct_data(oct_dims);
  for (int i = 0; i < ret_control_inputs; i++)
  {
    oct_data(0,i) = (uint64_t) *(control_inputs + i);
  }
  octave_value plhs = oct_data;
  return plhs;
}

// TF_CAPI_EXPORT extern int TF_OperationNumControlOutputs(TF_Operation* oper);
octave_value OCT_TF_OperationNumControlOutputs (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required for "
           "the 'TF_OperationNumControlOutputs' C API function.");
  }
  // Check octave_value type for pointer to Operation
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 "
           "scalar pointer to the Operation parsed to the "
           "'TF_OperationNumControlOutputs' C API function.");
  }
  // Get pointer to Operation
  TF_Operation* oper = (TF_Operation*) args(1).uint64_value ();
  // Get number of control inputs of Operation
  int numctrlout = TF_OperationNumControlOutputs (oper);
  // Return number of control inputs as int32
  octave_int32 num_ctrl_outputs = numctrlout;
  octave_value plhs = num_ctrl_outputs;
  return plhs;
}

// TF_CAPI_EXPORT extern int TF_OperationGetControlOutputs(TF_Operation* oper,
//                                                         TF_Operation** control_outputs,
//                                                         int max_control_outputs);
octave_value OCT_TF_OperationGetControlOutputs (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required for "
           "the 'TF_OperationGetControlOutputs' C API function.");
  }
  // Check octave_value type for pointer to Operation
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 "
           "scalar pointer to the Operation parsed to the "
           "'TF_OperationGetControlOutputs' C API function.");
  }
  // Get pointer to Operation
  TF_Operation* oper = (TF_Operation*) args(1).uint64_value ();
  // Get number of control inputs of Operation
  int max_control_outputs = TF_OperationNumControlInputs (oper);
  // Create an array of pointers to Operations to be retrieved from Operation
  TF_Operation** control_outputs = new TF_Operation*[max_control_outputs];
  // Get Function pointers from Graph
  int ret_control_outputs = TF_OperationGetControlOutputs
                           (oper, control_outputs, max_control_outputs);
  // Copy pointers to retrieved Operations into returning octave value
  dim_vector oct_dims;
  oct_dims.resize (2);
  oct_dims(0) = 1;
  oct_dims(1) = max_control_outputs;
  uint64NDArray oct_data(oct_dims);
  for (int i = 0; i < ret_control_outputs; i++)
  {
    oct_data(0,i) = (uint64_t) *(control_outputs + i);
  }
  octave_value plhs = oct_data;
  return plhs;
}

