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
// OCTAVE specific functions referenced by the TF_Input classdef
// -----------------------------------------------------------------------------

// TF_Input* TF_NewInput()
octave_value OCT_TF_NewInput (OCT_ARGS)
{
  TF_Input* input = reinterpret_cast<TF_Input*> (malloc (sizeof (TF_Input)));
  octave_uint64 ptr = (uint64_t) input;
  octave_value plhs = ptr;
  return plhs;
}

// void TF_DeleteInput(TF_Input*);
void OCT_TF_DeleteInput (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_DeleteInput' OCTAVE function.");
  }
  // Check octave_value type for pointer to Input
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be uint64 scalar pointer to "
           "the Input parsed to the 'TF_DeleteInput' OCTAVE function.");
  }
  // Get pointer to Input
  TF_Input* input = (TF_Input*) args(1).uint64_value ();
  free (input);
}

// -----------------------------------------------------------------------------
// C API functions referenced by the TF_Input classdef
// -----------------------------------------------------------------------------

// TF_CAPI_EXPORT extern TF_DataType TF_OperationInputType(TF_Input oper_in);
octave_value OCT_TF_OperationInputType (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required for "
           "the 'TF_OperationInputType' C API function.");
  }
  // Check octave_value type for pointer to Operation
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Input parsed to the 'TF_OperationInputType' C API function.");
  }
  // Get pointer to Input
  TF_Input oper_in = *((TF_Input*) args(1).uint64_value ());
  // Get DataType of Operation input
  TF_DataType dtype = TF_OperationInputType (oper_in);
  // Return DataType as uint32
  octave_uint32 dt = static_cast<int> (dtype);
  octave_value plhs = dt;
  return plhs;
}

// TF_CAPI_EXPORT extern TF_Output TF_OperationInput(TF_Input oper_in);
octave_value OCT_TF_OperationInput (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_OperationInput' C API function.");
  }
  // Check octave_value type for pointer to Operation
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Input parsed to the 'TF_OperationInput' C API function.");
  }
  // Get pointer to Operation
  TF_Input oper_in = *((TF_Input*) args(1).uint64_value ());
  // Get output and return its pointer
  TF_Output output = TF_OperationInput (oper_in);
  TF_Output* output_ptr = &output;
  octave_uint64 ptr = (uint64_t) output_ptr;
  octave_value plhs = ptr;
  return plhs;
}
