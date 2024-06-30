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
// OCTAVE specific functions referenced by the TF_Output classdef
// -----------------------------------------------------------------------------

// TF_Input* TF_Output()
octave_value OCT_TF_NewOutput (OCT_ARGS)
{
  TF_Output* output = reinterpret_cast<TF_Output*> (malloc (sizeof (TF_Output)));
  octave_uint64 ptr = (uint64_t) output;
  octave_value plhs = ptr;
  return plhs;
}

// void TF_DeleteOutput(TF_Output*);
void OCT_TF_DeleteOutput (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_DeleteOutput' OCTAVE function.");
  }
  // Check octave_value type for pointer to Output
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be uint64 scalar pointer to "
           "the Output parsed to the 'TF_DeleteOutput' OCTAVE function.");
  }
  // Get pointer to Input
  TF_Output* output = (TF_Output*) args(1).uint64_value ();
  free (output);
}

// -----------------------------------------------------------------------------
// C API functions referenced by the TF_Output classdef
// -----------------------------------------------------------------------------

// TF_CAPI_EXPORT extern TF_DataType TF_OperationOutputType(TF_Output oper_out);
octave_value OCT_TF_OperationOutputType (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required for "
           "the 'TF_OperationOutputType' C API function.");
  }
  // Check octave_value type for pointer to Operation
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           " Output parsed to the 'TF_OperationOutputType' C API function.");
  }
  // Get pointer to Output
  TF_Output oper_out = *((TF_Output*) args(1).uint64_value ());
  // Get DataType of Operation output
  TF_DataType dtype = TF_OperationOutputType (oper_out);
  // Return DataType as uint32
  octave_uint32 dt = static_cast<int> (dtype);
  octave_value plhs = dt;
  return plhs;
}

// TF_CAPI_EXPORT extern int TF_OperationOutputNumConsumers(TF_Output oper_out);
octave_value OCT_TF_OperationOutputNumConsumers (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required for the "
           "'TF_OperationOutputNumConsumers' C API function.");
  }
  // Check octave_value type for pointer to Operation
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 "
           "scalar pointer to the Output parsed to the "
           "'TF_OperationOutputNumConsumers' C API function.");
  }
  // Get Output from pointer
  TF_Output oper_out = *((TF_Output*) args(1).uint64_value ());
  // Get number of current consumers of Output
  int numconsumers = TF_OperationOutputNumConsumers (oper_out);
  // Return number of current consumers as int32
  octave_int32 num_consumers = numconsumers;
  octave_value plhs = num_consumers;
  return plhs;
}

// TF_CAPI_EXPORT extern int TF_OperationOutputConsumers(TF_Output oper_out,
//                                                       TF_Input* consumers,
//                                                       int max_consumers);
octave_value OCT_TF_OperationOutputConsumers (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required for "
           "the 'TF_OperationOutputConsumers' C API function.");
  }
  // Check octave_value type for pointer to Operation
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "Operation parsed to the 'TF_OperationOutputConsumers' C API function.");
  }
  // Get Output from pointer
  TF_Output oper_out = *((TF_Output*) args(1).uint64_value ());
  // Get number of inputs of Operation
  int max_consumers = TF_OperationOutputNumConsumers (oper_out);
  // Create an array of TF_Input consumers according to max_consumers
  TF_Input* consumers = reinterpret_cast<TF_Input*>
                        (malloc (sizeof (TF_Input) * max_consumers));
  // Get list of all consumers of the output of Operation
  TF_OperationOutputConsumers (oper_out, consumers, max_consumers);
  // Return pointer to input array
  octave_uint64 ptr = (uint64_t) consumers;
  octave_value plhs = ptr;
  return plhs;
}
