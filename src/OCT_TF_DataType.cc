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
// OCTAVE specific functions referenced by the TF_Tensor classdef
// -----------------------------------------------------------------------------

// charMatrix TF_DataTypeName(TF_DataType dt);
octave_value OCT_TF_DataTypeName (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_DataTypeName' OCTAVE function.");
  }
  // Check octave_value type for DataType
  if (! args(1).is_uint32_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint32 scalar "
           "indexing the appropriate TF_DataType to be parsed to "
           "the 'TF_DataTypeName' OCTAVE function.");
  }
  // Get DataType id as uint32 value and return char string
  string dtype;
  switch (args(1).uint_value ())
  {
    case 1: dtype  = "TF_FLOAT"; break;
    case 2: dtype  = "TF_DOUBLE"; break;
    case 3: dtype  = "TF_INT32"; break;
    case 4: dtype  = "TF_UINT8"; break;
    case 5: dtype  = "TF_INT16"; break;
    case 6: dtype  = "TF_INT8"; break;
    case 7: dtype  = "TF_STRING"; break;
    case 8: dtype  = "TF_COMPLEX64"; break;
    case 9: dtype  = "TF_INT64"; break;
    case 10: dtype = "TF_BOOL"; break;
    case 11: dtype = "TF_QINT8"; break;
    case 12: dtype = "TF_QUINT8"; break;
    case 13: dtype = "TF_QINT32"; break;
    case 14: dtype = "TF_BFLOAT16"; break;
    case 15: dtype = "TF_QINT16"; break;
    case 16: dtype = "TF_QUINT16"; break;
    case 17: dtype = "TF_UINT16"; break;
    case 18: dtype = "TF_COMPLEX128"; break;
    case 19: dtype = "TF_HALF"; break;
    case 20: dtype = "TF_RESOURCE"; break;
    case 21: dtype = "TF_VARIANT"; break;
    case 22: dtype = "TF_UINT32"; break;
    case 23: dtype = "TF_UINT64"; break;
    case 24: dtype = "TF_FLOAT8_E5M2"; break;
    case 25: dtype = "TF_FLOAT8_E4M3FN"; break;
    case 29: dtype = "TF_INT4"; break;
    case 30: dtype = "TF_UINT4"; break;
  }
  charMatrix dt_str = dtype.c_str ();
  octave_value plhs = dt_str;
  return plhs;
}

// -----------------------------------------------------------------------------
// C API functions referenced by the TF_DataType classdef
// -----------------------------------------------------------------------------

// TF_CAPI_EXPORT extern size_t TF_DataTypeSize(TF_DataType dt);
octave_value OCT_TF_DataTypeSize (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_DataTypeSize' C API function.");
  }
  // Check octave_value type for DataType
  if (! args(1).is_uint32_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint32 scalar "
           "indexing the appropriate TF_DataType to be parsed to "
           "the 'TF_DataTypeSize' C API function.");
  }
  // Get DataType and return its id as uint32 value
  TF_DataType type = (TF_DataType) args(1).uint_value ();
  size_t dt_size = TF_DataTypeSize (type);
  octave_uint64 size = (uint64_t) dt_size;
  octave_value plhs = size;
  return plhs;
}
