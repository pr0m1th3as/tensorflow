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
// C API functions referenced by the TF_Buffer classdef
// -----------------------------------------------------------------------------

// TF_CAPI_EXPORT extern TF_Buffer* TF_NewBuffer(void);
octave_value OCT_TF_NewBuffer (OCT_ARGS)
{
  TF_Buffer* newBuffer = TF_NewBuffer ();
  octave_uint64 ptr = (uint64_t) newBuffer;
  octave_value plhs = ptr;
  return plhs;
}

// TF_CAPI_EXPORT extern void TF_DeleteBuffer(TF_Buffer*);
void OCT_TF_DeleteBuffer (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_DeleteBuffer' C API function.");
  }
  // Check octave_value type for pointer to Buffer
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be uint64 scalar pointer to "
           "the Buffer parsed to the 'TF_DeleteBuffer' C API function.");
  }
  // Get pointer to Buffer
  TF_Buffer* buffer = (TF_Buffer*) args(1).uint64_value ();
  TF_DeleteBuffer (buffer);
}

// TF_CAPI_EXPORT extern TF_Buffer* TF_NewBufferFromString(const void* proto,
//                                                         size_t proto_len);
octave_value OCT_TF_NewBufferFromString (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required for "
           "the 'TF_NewBufferFromString' C API function.");
  }
  if (! (args(1).is_char_matrix () || args(1).is_uint8_type ()) || ! args(1).rows () == 1)
  {
    error ("tensorflow: 2nd argument must be either a character or a uint8 "
           "vector to be parsed to the 'TF_NewBufferFromString' C API function.");
  }
  const void* proto = args(1).mex_get_data ();
  size_t proto_len = (size_t) args(1).length ();
  TF_Buffer* newBuffer = TF_NewBufferFromString (proto, proto_len);
  octave_uint64 ptr = (uint64_t) newBuffer;
  octave_value plhs = ptr;
  return plhs;
}

// TF_CAPI_EXPORT extern TF_Buffer TF_GetBuffer(TF_Buffer* buffer);
octave_value OCT_TF_GetBuffer (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_GetBuffer' C API function.");
  }
  // Check octave_value type for pointer to Buffer
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be uint64 scalar pointer "
           "to the Buffer parsed to the 'TF_GetBuffer' C API function.");
  }
  // Get pointer to Buffer
  TF_Buffer* buffer = (TF_Buffer*) args(1).uint64_value();
  TF_Buffer newBuffer = TF_GetBuffer (buffer);
  // Transform buffer.data to uint8 vector before returning to Octave
  dim_vector oct_dims;
  oct_dims.resize (2);
  oct_dims(0) = 1;
  oct_dims(1) = newBuffer.length;
  uint8NDArray buf_data(oct_dims);
  memcpy (buf_data.fortran_vec (), newBuffer.data, newBuffer.length * sizeof (uint8_t));
  octave_value plhs = buf_data;
  return plhs;
}

// charMatrix TF_GetBufferToString(TF_Buffer* buffer);
octave_value OCT_TF_GetBufferToString (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_GetBufferToString' C API function.");
  }
  // Check octave_value type for pointer to Buffer
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be uint64 scalar pointer to "
           "the Buffer parsed to the 'TF_GetBufferToString' C API function.");
  }
  // Get pointer to Buffer
  TF_Buffer* buffer = (TF_Buffer*) args(1).uint64_value();
  TF_Buffer newBuffer = TF_GetBuffer (buffer);
  // Transform buffer.data to uint8 vector before returning to Octave
  dim_vector oct_dims;
  oct_dims.resize (2);
  oct_dims(0) = 1;
  oct_dims(1) = newBuffer.length;
  charMatrix str_data(oct_dims);
  memcpy (str_data.fortran_vec (), newBuffer.data, newBuffer.length * sizeof (uint8_t));
  octave_value plhs = str_data;
  return plhs;
}
