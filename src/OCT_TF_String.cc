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
// OCTAVE specific functions referenced by the TF_String classdef
// -----------------------------------------------------------------------------

// TF_TString* TF_NewTString(void);
octave_value OCT_TF_NewTString (void)
{
  TF_TString* ts = reinterpret_cast<TF_TString*> (malloc (sizeof (TF_TString)));
  octave_uint64 ptr = (uint64_t) ts;
  octave_value plhs = ptr;
  return plhs;
}

// TF_TString* TF_LoadTString(charMatrix src_str);
octave_value OCT_TF_LoadTString (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_LoadTString' OCTAVE function.");
  }
  // Check octave_value type for character vector
  if (! args(1).is_char_matrix () || args(1).rows () != 1)
  {
    error ("tensorflow: 2nd argument must be a character vector "
           "to be parsed to the 'TF_LoadTString' OCTAVE function.");
  }
  // Get character vector and its length
  charMatrix src_str = args(1).char_matrix_value ();
  size_t str_len = (size_t) args(1).numel ();
  // Create a TString and return its pointer
  TF_TString* ts = reinterpret_cast<TF_TString*> (malloc (sizeof (TF_TString)));
  TF_StringInit (ts);
  TF_StringCopy (ts, src_str.data (), str_len);
  octave_uint64 ptr = (uint64_t) ts;
  octave_value plhs = ptr;
  return plhs;
}

// charMatrix src_str TF_SaveTString(TF_TString* tstring);
octave_value OCT_TF_SaveTString (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_SaveTString' OCTAVE function.");
  }
  // Check octave_value type for uint64 pointer to TString
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the TString parsed to the 'TF_SaveTString' OCTAVE function.");
  }
  // Get pointer to target TString
  TF_TString* tstring = (TF_TString*) args(1).uint64_value ();
  // Get pointer to string data and copy it to charMatrix
  const char* tf_str = TF_StringGetDataPointer (tstring);
  octave_value plhs;
  plhs = charMatrix (tf_str);
  return plhs;
}

// -----------------------------------------------------------------------------
// C API functions referenced by the TF_String classdef
// -----------------------------------------------------------------------------

// TF_CAPI_EXPORT extern void TF_StringInit(TF_TString *t);
void OCT_TF_StringInit (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_StringInit' C API function.");
  }
  // Check octave_value type for uint64 pointer to TString
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the TString parsed to the 'TF_StringInit' C API function.");
  }
  // Get pointer to target TString
  TF_TString* tstring = (TF_TString*) args(1).uint64_value ();
  TF_StringInit (tstring);
}

// TF_CAPI_EXPORT extern void TF_StringCopy(TF_TString *dst, const char *src,
//                                          size_t size);
void OCT_TF_StringCopy (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_StringCopy' C API function.");
  }
  // Check octave_value type for pointer to TString
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the TString parsed to the 'TF_StringCopy' C API function.");
  }
  // Check octave_value type for character vector as source string
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character vector defining "
           "the source string parsed to the 'TF_StringCopy' C API function.");
  }
  // Check octave_value type for uint64 scalar as size of string
  if (! args(3).is_uint64_type () || args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 scalar "
           "value defining the size of the source string parsed "
           "to the 'TF_StringCopy' C API function.");
  }
  // Get pointer to target TString
  TF_TString* tstring = (TF_TString*) args(1).uint64_value ();
  // Get source string
  charMatrix source = args(2).char_matrix_value ();
  // Get size of source string
  size_t size = args(3).uint64_value ();
  TF_StringCopy (tstring, source.data (), size);
}

// TF_CAPI_EXPORT extern void TF_StringAssignView(TF_TString *dst,
//                                                const char *src, size_t size);
void OCT_TF_StringAssignView (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_StringAssignView' C API function.");
  }
  // Check octave_value type for pointer to TString
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "TString parsed to the 'TF_StringAssignView' C API function.");
  }
  // Check octave_value type for character vector as source string
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character vector defining the "
           "source string parsed to the 'TF_StringAssignView' C API function.");
  }
  // Check octave_value type for uint64 scalar as size of string
  if (! args(3).is_uint64_type () || args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 scalar "
           "value defining the size of the source string parsed "
           "to the 'TF_StringAssignView' C API function.");
  }
  // Get pointer to target TString
  TF_TString* tstring = (TF_TString*) args(1).uint64_value ();
  // Get source string
  charMatrix source = args(2).char_matrix_value ();
  // Get size of source string
  size_t size = args(3).uint64_value ();
  TF_StringAssignView (tstring, source.data (), size);
}

// TF_CAPI_EXPORT extern const char *TF_StringGetDataPointer(const TF_TString *tstr);
octave_value OCT_TF_StringGetDataPointer (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required for "
           "the 'TF_StringGetDataPointer' C API function.");
  }
  // Check octave_value type for pointer to TString
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "TString parsed to the 'TF_StringGetDataPointer' C API function.");
  }
  // Get pointer to TString
  TF_TString* tstring = (TF_TString*) args(1).uint64_value();
  // Get pointer to string data
  const char* str_data = TF_StringGetDataPointer (tstring);
  octave_uint64 str_ptr = (uint64_t) str_data;
  octave_value plhs = str_ptr;
  return plhs;
}

// TF_CAPI_EXPORT extern TF_TString_Type TF_StringGetType(const TF_TString *str);
octave_value OCT_TF_StringGetType (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_StringGetType' C API function.");
  }
  // Check octave_value type for pointer to TString
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "TString parsed to the 'TF_StringGetType' C API function.");
  }
  // Get pointer to TString
  TF_TString* tstring = (TF_TString*) args(1).uint64_value();
  // Get type of TString and return its code as uint32
  TF_TString_Type tstype = TF_StringGetType (tstring);
  octave_uint32 ts = static_cast<int> (tstype);
  octave_value plhs = ts;
  return plhs;
}

// TF_CAPI_EXPORT extern size_t TF_StringGetSize(const TF_TString *tstr);
octave_value OCT_TF_StringGetSize (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_StringGetSize' C API function.");
  }
  // Check octave_value type for pointer to TString
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the TString parsed to the 'TF_StringGetSize' C API function.");
  }
  // Get pointer to TString
  TF_TString* tstring = (TF_TString*) args(1).uint64_value();
  // Get size of TString
  size_t len = TF_StringGetSize (tstring);
  octave_uint64 strlen = (uint64_t) len;
  octave_value plhs = strlen;
  return plhs;
}

// TF_CAPI_EXPORT extern size_t TF_StringGetCapacity(const TF_TString *str);
octave_value OCT_TF_StringGetCapacity (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_StringGetCapacity' C API function.");
  }
  // Check octave_value type for pointer to TString
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the TString parsed to the 'TF_StringGetCapacity' C API function.");
  }
  // Get pointer to TString
  TF_TString* tstring = (TF_TString*) args(1).uint64_value();
  // Get capacity of TString
  size_t cap = TF_StringGetCapacity (tstring);
  octave_uint64 strcap = (uint64_t) cap;
  octave_value plhs = strcap;
  return plhs;
}

// TF_CAPI_EXPORT extern void TF_StringDealloc(TF_TString *tstr);
void OCT_TF_StringDealloc (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_StringDealloc' C API function.");
  }
  // Check octave_value type for pointer to TString
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the TString parsed to the 'TF_StringDealloc' C API function.");
  }
  // Get pointer to TString
  TF_TString* tstring = (TF_TString*) args(1).uint64_value();
  // Deallocate TString
  TF_StringDealloc (tstring);
}
