/*
Copyright (C) 2024 Andreas Bertsatos <abertsatos@biol.uoa.gr>
Copyright (C) 2024 Linux BCKP <linuxbckp@gmail.com>

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
// C API functions referenced by the TF_Status classdef
// -----------------------------------------------------------------------------

// TF_CAPI_EXPORT extern TF_Status* TF_NewStatus(void);
octave_value OCT_TF_NewStatus (void)
{
  TF_Status* newStatus = TF_NewStatus ();
  octave_uint64 ptr = (uint64_t) newStatus;
  octave_value plhs = ptr;
  return plhs;
}

// TF_CAPI_EXPORT extern void TF_DeleteStatus(TF_Status*);
void OCT_TF_DeleteStatus (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_DeleteStatus' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Status parsed to the 'TF_DeleteStatus' C API function.");
  }
  TF_Status* status = (TF_Status*) args(1).uint64_value ();
  TF_DeleteStatus (status);
}

// TF_CAPI_EXPORT extern void TF_SetStatus(TF_Status* s, TF_Code code,
//                                         const char* msg);
void OCT_TF_SetStatus (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_SetStatus' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer "
           "to the Status parsed to the 'TF_SetStatus' C API function.");
  }
  // Check octave_value type for Status Code
  if (! args(2).is_uint32_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint32 scalar "
           "indexing the appropriate TF_Code to be parsed to the "
           "'TF_SetStatus' C API function.");
  }
  // Check octave_value type for character vector for status message
  if (! args(3).is_char_matrix () || args(3).rows () != 1)
  {
    error ("tensorflow: 4th argument must be a character "
           "vector defining the message to be parsed to the "
           "'TF_SetStatus' C API function.");
  }
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(1).uint64_value ();
  // Get status code
  TF_Code code = (TF_Code) args(2).uint_value ();
  // Get message
  charMatrix msg = args(3).char_matrix_value ();
  TF_SetStatus (status, code, msg.data());
}

// TF_CAPI_EXPORT void TF_SetPayload(TF_Status* s, const char* key,
//                                   const char* value);
void OCT_TF_SetPayload (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_SetPayload' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer "
           "to the Status parsed to the 'TF_SetPayload' C API function.");
  }
  // Check octave_value type for character vector for key
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character vector defining "
           "the 'key' to be parsed to the 'TF_SetPayload' C API function.");
  }
  // Check octave_value type for character vector for value
  if (! args(3).is_char_matrix () || args(3).rows () != 1)
  {
    error ("tensorflow: 4th argument must be a character vector defining "
           "the 'value' to be parsed to the 'TF_SetPayload' C API function.");
  }
  // Get pointer to status
  TF_Status* status = (TF_Status*) args(1).uint64_value ();
  // Get key
  charMatrix key = args(2).char_matrix_value ();
  // Get value
  charMatrix value = args(3).char_matrix_value ();
  TF_SetPayload (status, key.data (), value.data ());
}

// TF_CAPI_EXPORT extern void TF_ForEachPayload(const TF_Status* s,
//                                              TF_PayloadVisitor visitor,
//                                              void* capture);
void OCT_TF_ForEachPayload (OCT_ARGS)
{
  error ("tensorflow: 'TF_ForEachPayload' C API function not supported yet.");
}

// TF_CAPI_EXPORT extern void TF_SetStatusFromIOError(TF_Status* s, int error_code,
//                                                    const char* context);
void OCT_TF_SetStatusFromIOError (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_SetStatusFromIOError' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Status parsed to the 'TF_SetStatusFromIOError' C API function.");
  }
  // Check octave_value type for error_code
  if (! args(2).isinteger () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an integer "
           "scalar defining an error_code to be parsed to "
           "the 'TF_SetStatusFromIOError' C API function.");
  }
  // Check octave_value type for character vector for message
  if (! args(3).is_char_matrix () || args(3).rows () != 1)
  {
    error ("tensorflow: 4th argument must be a character "
           "vector defining the context to be parsed to the "
           "'TF_SetStatusFromIOError' C API function.");
  }
  // Get pointer to status
  TF_Status* status = (TF_Status*) args(1).uint64_value ();
  // Get error_code
  int error_code = args(2).int_value();
  // Get message
  charMatrix context = args(3).char_matrix_value ();
  TF_SetStatusFromIOError (status, error_code, context.data());
}

// TF_CAPI_EXPORT extern TF_Code TF_GetCode(const TF_Status* s);
octave_value OCT_TF_GetCode (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_GetCode' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer "
           "to the Status parsed to the 'TF_GetCode' C API function.");
  }
  // Get pointer to Status
  const TF_Status* status = (TF_Status*) args(1).uint64_value ();
  // Get Status Code
  TF_Code code = TF_GetCode (status);
  octave_uint32 cd = static_cast<int> (code);
  octave_value plhs = cd;
  return plhs;
}

// TF_CAPI_EXPORT extern const char* TF_Message(const TF_Status* s);
octave_value OCT_TF_Message (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_Message' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer "
           "to the Status parsed to the 'TF_Message' C API function.");
  }
  // Get pointer to Status
  const TF_Status* status = (TF_Status*) args(1).uint64_value ();
  // Get Status message
  const char* msg = TF_Message (status);
  charMatrix msg_ = msg;
  octave_value plhs = msg_;
  return plhs;
}

// -----------------------------------------------------------------------------
// C API status constants in tf_status.h
// -----------------------------------------------------------------------------

// #define TF_OK TSL_OK
octave_value OCT_TF_OK (void)
{
  octave_uint32 st = TF_OK;
  octave_value plhs = st;
  return plhs;
}

// #define TF_CANCELLED TSL_CANCELLED
octave_value OCT_TF_CANCELLED (void)
{
  octave_uint32 st = TF_CANCELLED;
  octave_value plhs = st;
  return plhs;
}

// #define TF_UNKNOWN TSL_UNKNOWN
octave_value OCT_TF_UNKNOWN (void)
{
  octave_uint32 st = TF_UNKNOWN;
  octave_value plhs = st;
  return plhs;
}

// #define TF_INVALID_ARGUMENT TSL_INVALID_ARGUMENT
octave_value OCT_TF_INVALID_ARGUMENT (void)
{
  octave_uint32 st = TF_INVALID_ARGUMENT;
  octave_value plhs = st;
  return plhs;
}

// #define TF_DEADLINE_EXCEEDED TSL_DEADLINE_EXCEEDED
octave_value OCT_TF_DEADLINE_EXCEEDED (void)
{
  octave_uint32 st = TF_DEADLINE_EXCEEDED;
  octave_value plhs = st;
  return plhs;
}

// #define TF_NOT_FOUND TSL_NOT_FOUND
octave_value OCT_TF_NOT_FOUND (void)
{
  octave_uint32 st = TF_NOT_FOUND;
  octave_value plhs = st;
  return plhs;
}

// #define TF_ALREADY_EXISTS TSL_ALREADY_EXISTS
octave_value OCT_TF_ALREADY_EXISTS (void)
{
  octave_uint32 st = TF_ALREADY_EXISTS;
  octave_value plhs = st;
  return plhs;
}

// #define TF_PERMISSION_DENIED TSL_PERMISSION_DENIED
octave_value OCT_TF_PERMISSION_DENIED (void)
{
  octave_uint32 st = TF_PERMISSION_DENIED;
  octave_value plhs = st;
  return plhs;
}

// #define TF_UNAUTHENTICATED TSL_UNAUTHENTICATED
octave_value OCT_TF_UNAUTHENTICATED (void)
{
  octave_uint32 st = TF_UNAUTHENTICATED;
  octave_value plhs = st;
  return plhs;
}

// #define TF_RESOURCE_EXHAUSTED TSL_RESOURCE_EXHAUSTED
octave_value OCT_TF_RESOURCE_EXHAUSTED (void)
{
  octave_uint32 st = TF_RESOURCE_EXHAUSTED;
  octave_value plhs = st;
  return plhs;
}

// #define TF_FAILED_PRECONDITION TSL_FAILED_PRECONDITION
octave_value OCT_TF_FAILED_PRECONDITION (void)
{
  octave_uint32 st = TF_FAILED_PRECONDITION;
  octave_value plhs = st;
  return plhs;
}

// #define TF_ABORTED TSL_ABORTED
octave_value OCT_TF_ABORTED (void)
{
  octave_uint32 st = TF_ABORTED;
  octave_value plhs = st;
  return plhs;
}

// #define TF_OUT_OF_RANGE TSL_OUT_OF_RANGE
octave_value OCT_TF_OUT_OF_RANGE (void)
{
  octave_uint32 st = TF_OUT_OF_RANGE;
  octave_value plhs = st;
  return plhs;
}

// #define TF_UNIMPLEMENTED TSL_UNIMPLEMENTED
octave_value OCT_TF_UNIMPLEMENTED (void)
{
  octave_uint32 st = TF_UNIMPLEMENTED;
  octave_value plhs = st;
  return plhs;
}

// #define TF_INTERNAL TSL_INTERNAL
octave_value OCT_TF_INTERNAL (void)
{
  octave_uint32 st = TF_INTERNAL;
  octave_value plhs = st;
  return plhs;
}

// #define TF_UNAVAILABLE TSL_UNAVAILABLE
octave_value OCT_TF_UNAVAILABLE (void)
{
  octave_uint32 st = TF_UNAVAILABLE;
  octave_value plhs = st;
  return plhs;
}

// #define TF_DATA_LOSS TSL_DATA_LOSS
octave_value OCT_TF_DATA_LOSS (void)
{
  octave_uint32 st = TF_DATA_LOSS;
  octave_value plhs = st;
  return plhs;
}
