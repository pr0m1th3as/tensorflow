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
// C API functions referenced by the TF_OperationDescription classdef
// -----------------------------------------------------------------------------

// TF_CAPI_EXPORT extern void TF_SetDevice(TF_OperationDescription* desc,
//                                         const char* device);
void OCT_TF_SetDevice (OCT_ARGS)
{
  if (nrhs < 3)
  {
    error ("tensorflow: two extra arguments are required "
           "for the 'TF_SetDevice' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "OperationDescription parsed to the 'TF_SetDevice' C API function.");
  }
  // Check octave_value type for character vector of device
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character vector defining "
           "the device parsed to the 'TF_SetDevice' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get character vector of device
  charMatrix device = args(2).char_matrix_value ();
  // Set device for Operation
  TF_SetDevice (desc, device.data ());
}

// TF_CAPI_EXPORT extern void TF_AddInput(TF_OperationDescription* desc,
//                                        TF_Output input);
void OCT_TF_AddInput (OCT_ARGS)
{
  if (nrhs < 3)
  {
    error ("tensorflow: two extra arguments are required "
           "for the 'TF_AddInput' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "OperationDescription parsed to the 'TF_AddInput' C API function.");
  }
  // Check octave_value type for pointer to input
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer "
           "to the input parsed to the 'TF_AddInput' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get pointer to input
  TF_Output input = *((TF_Output*) args(2).uint64_value ());
  // Add input
  TF_AddInput (desc, input);
}

// TF_CAPI_EXPORT extern void TF_AddInputList(TF_OperationDescription* desc,
//                                            const TF_Output* inputs,
//                                            int num_inputs);
void OCT_TF_AddInputList (OCT_ARGS)
{
  if (nrhs < 3)
  {
    error ("tensorflow: two extra arguments are required "
           "for the 'TF_AddInputList' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_AddInputList' C API function.");
  }
  // Check octave_value type for pointers to inputs
  if (! args(2).is_uint64_type () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be an uint64 vector of pointers "
           "to the inputs parsed to the 'TF_AddInputList' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get pointers to inputs
  uint64NDArray oct_data = args(2).int64_array_value ();
  // Get number of elements of int64 vector
  int num_inputs = (int) args(2).numel ();
  // Declare pointers for strings and lengths
  TF_Output* pointers[num_inputs];
  // Populate arrays of pointers
  for (int i = 0; i < num_inputs; i++)
  {
    pointers[i] = (TF_Output*) (uint64_t) oct_data(i);
  }
  const TF_Output* inputs = (TF_Output*) pointers;
  TF_AddInputList (desc, inputs, num_inputs);
}

// TF_CAPI_EXPORT extern void TF_AddControlInput(TF_OperationDescription* desc,
//                                               TF_Operation* input);
void OCT_TF_AddControlInput (OCT_ARGS)
{
  if (nrhs < 3)
  {
    error ("tensorflow: two extra arguments are required "
           "for the 'TF_AddControlInput' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_AddControlInput' C API function.");
  }
  // Check octave_value type for pointer to Operation
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer to "
           "the Operation parsed to the 'TF_AddControlInput' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get pointer to Output
  TF_Operation* input = (TF_Operation*) args(2).uint64_value ();
  // Add control input
  TF_AddControlInput (desc, input);
}

// TF_CAPI_EXPORT extern void TF_SetAttrString(TF_OperationDescription* desc,
//                                             const char* attr_name,
//                                             const void* value, size_t length);
void OCT_TF_SetAttrString (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_SetAttrString' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_SetAttrString' C API function.");
  }
  // Check octave_value type for character vector of attribute name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character vector defining the "
           "attribute name parsed to the 'TF_SetAttrString' C API function.");
  }
  // Check octave_value type for character vector of attribute string
  if (! args(3).is_char_matrix () || args(3).rows () != 1)
  {
    error ("tensorflow: 4th argument must be a character vector defining the "
           "attribute string parsed to the 'TF_SetAttrString' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get attribute name
  charMatrix attr_name = args(2).char_matrix_value ();
  // Get attribute string
  charMatrix attr_string = args(3).char_matrix_value ();
  // Get attribute string length
  size_t length = (size_t) args(3).numel ();
  // Set attribute string
  TF_SetAttrString (desc, attr_name.data (), attr_string.data (), length);
}

// TF_CAPI_EXPORT extern void TF_SetAttrStringList(TF_OperationDescription* desc,
//                                                 const char* attr_name,
//                                                 const void* const* values,
//                                                 const size_t* lengths,
//                                                 int num_values);
void OCT_TF_SetAttrStringList (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_SetAttrStringList' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_SetAttrStringList' C API function.");
  }
  // Check octave_value type for character vector of attribute name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character "
           "vector defining the attribute name parsed to "
           "the 'TF_SetAttrStringList' C API function.");
  }
  // Check octave_value type for cellstr vector of attribute strings
  if (! args(3).iscellstr () || args(3).rows () != 1)
  {
    error ("tensorflow: 4th argument must be a cellstr "
           "vector defining the attribute string parsed "
           "to the 'TF_SetAttrStringList' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get attribute name
  charMatrix attr_name = args(2).char_matrix_value ();
  // Get attribute strings
  Array<string> oct_data = args(3).cellstr_value ();
  // Get number of attribute strings
  int nelem = (int) args(3).numel ();
  // Declare pointers for strings and lengths
  void* strings[nelem];
  size_t lengths[nelem];
  // Populate arrays of pointers
  for (int i = 0; i < nelem; i++)
  {
    strings[i] = (void*) oct_data(i).c_str ();
    lengths[i] = (size_t) oct_data(i).length ();
  }
  const void* const* value = strings;
  const size_t* len = lengths;
  // Set attribute string list
  TF_SetAttrStringList (desc, attr_name.data (), value, len, nelem);
}

// TF_CAPI_EXPORT extern void TF_SetAttrInt(TF_OperationDescription* desc,
//                                          const char* attr_name, int64_t value);
void OCT_TF_SetAttrInt (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_SetAttrInt' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to the "
           "OperationDescription parsed to the 'TF_SetAttrInt' C API function.");
  }
  // Check octave_value type for character vector of attribute name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character vector defining the "
           "attribute name parsed to the 'TF_SetAttrInt' C API function.");
  }
  // Check octave_value type for int64 scalar value
  if (! args(3).is_int64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an int64 scalar "
           "parsed to the 'TF_SetAttrInt' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get attribute name
  charMatrix attr_name = args(2).char_matrix_value ();
  // Get attribute int64 value
  int64_t value = (size_t) args(3).int64_value ();
  // Set attribute string
  TF_SetAttrInt (desc, attr_name.data (), value);
}

// TF_CAPI_EXPORT extern void TF_SetAttrIntList(TF_OperationDescription* desc,
//                                              const char* attr_name,
//                                              const int64_t* values,
//                                              int num_values);
void OCT_TF_SetAttrIntList (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_SetAttrIntList' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_SetAttrIntList' C API function.");
  }
  // Check octave_value type for character vector of attribute name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character "
           "vector defining the attribute name parsed to "
           "the 'TF_SetAttrIntList' C API function.");
  }
  // Check octave_value type for int64 vector of values
  if (! args(3).is_int64_type () || args(3).rows () != 1)
  {
    error ("tensorflow: 4th argument must be an int64 vector "
           "parsed to the 'TF_SetAttrIntList' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get attribute name
  charMatrix attr_name = args(2).char_matrix_value ();
  // Get values from int64 vector
  int64NDArray oct_data = args(3).int64_array_value ();
  const int64_t* values = (int64_t*) oct_data.data ();
  // Get number of elements of int64 vector
  int num_values = (int) args(3).numel ();
  // Set attribute string list
  TF_SetAttrIntList (desc, attr_name.data (), values, num_values);
}

// TF_CAPI_EXPORT extern void TF_SetAttrFloat(TF_OperationDescription* desc,
//                                            const char* attr_name, float value);
void OCT_TF_SetAttrFloat (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_SetAttrFloat' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_SetAttrFloat' C API function.");
  }
  // Check octave_value type for character vector of attribute name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character vector defining the "
           "attribute name parsed to the 'TF_SetAttrFloat' C API function.");
  }
  // Check octave_value type for float value
  if (! args(3).is_single_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be a float scalar "
           "parsed to the 'TF_SetAttrFloat' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get attribute name
  charMatrix attr_name = args(2).char_matrix_value ();
  // Get attribute int64 value
  float value = args(3).float_value ();
  // Set attribute string
  TF_SetAttrFloat (desc, attr_name.data (), value);
}

// TF_CAPI_EXPORT extern void TF_SetAttrFloatList(TF_OperationDescription* desc,
//                                                const char* attr_name,
//                                                const float* values,
//                                                int num_values);
void OCT_TF_SetAttrFloatList (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_SetAttrFloatList' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_SetAttrFloatList' C API function.");
  }
  // Check octave_value type for character vector of attribute name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character "
           "vector defining the attribute name parsed to "
           "the 'TF_SetAttrFloatList' C API function.");
  }
  // Check octave_value type for int64 vector of values
  if (! args(3).is_single_type () || args(3).rows () != 1)
  {
    error ("tensorflow: 4th argument must be a float vector "
           "parsed to the 'TF_SetAttrFloatList' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get attribute name
  charMatrix attr_name = args(2).char_matrix_value ();
  // Get values from int64 vector
  FloatRowVector oct_data = args(3).float_row_vector_value ();
  const float* values = (float*) oct_data.data ();
  // Get number of elements of int64 vector
  int num_values = (int) args(3).numel ();
  // Set attribute string list
  TF_SetAttrFloatList (desc, attr_name.data (), values, num_values);
}

//TF_CAPI_EXPORT extern void TF_SetAttrBool(TF_OperationDescription* desc,
//                                           const char* attr_name,
//                                           unsigned char value);
void OCT_TF_SetAttrBool (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_SetAttrBool' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_SetAttrBool' C API function.");
  }
  // Check octave_value type for character vector of attribute name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character vector defining the "
           "attribute name parsed to the 'TF_SetAttrBool' C API function.");
  }
  // Check octave_value type for bool value
  if (! args(3).is_bool_scalar ())
  {
    error ("tensorflow: 4th argument must be a bool scalar "
           "parsed to the 'TF_SetAttrBool' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get attribute name
  charMatrix attr_name = args(2).char_matrix_value ();
  // Get attribute int64 value
  unsigned char value = (unsigned char) args(3).bool_value ();
  // Set attribute string
  TF_SetAttrBool (desc, attr_name.data (), value);
}

// TF_CAPI_EXPORT extern void TF_SetAttrBoolList(TF_OperationDescription* desc,
//                                               const char* attr_name,
//                                               const unsigned char* values,
//                                               int num_values);
void OCT_TF_SetAttrBoolList (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_SetAttrBoolList' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_SetAttrBoolList' C API function.");
  }
  // Check octave_value type for character vector of attribute name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character "
           "vector defining the attribute name parsed to "
           "the 'TF_SetAttrBoolList' C API function.");
  }
  // Check octave_value type for int64 vector of values
  if (! args(3).is_bool_matrix () || args(3).rows () != 1)
  {
    error ("tensorflow: 4th argument must be a bool vector "
           "parsed to the 'TF_SetAttrBoolList' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get attribute name
  charMatrix attr_name = args(2).char_matrix_value ();
  // Get values from int64 vector
  boolNDArray oct_data = args(3).bool_array_value ();
  const unsigned char* values = (unsigned char*) oct_data.data ();
  // Get number of elements of int64 vector
  int num_values = (int) args(3).numel ();
  // Set attribute string list
  TF_SetAttrBoolList (desc, attr_name.data (), values, num_values);
}

// TF_CAPI_EXPORT extern void TF_SetAttrType(TF_OperationDescription* desc,
//                                           const char* attr_name,
//                                           TF_DataType value);
void OCT_TF_SetAttrType (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_SetAttrType' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_SetAttrType' C API function.");
  }
  // Check octave_value type for character vector of attribute name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character vector defining the "
           "attribute name parsed to the 'TF_SetAttrType' C API function.");
  }
  // Check octave_value type for DataType of Operation
  if (! args(3).is_uint32_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint32 scalar defining "
           "the DataType parsed to the 'TF_SetAttrType' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get attribute name
  charMatrix attr_name = args(2).char_matrix_value ();
  // Get DataType
  TF_DataType value = *((TF_DataType*) args(3).uint64_value ());
  // Set attribute data type
  TF_SetAttrType (desc, attr_name.data (), value);
}

// F_CAPI_EXPORT extern void TF_SetAttrTypeList(TF_OperationDescription* desc,
//                                              const char* attr_name,
//                                              const TF_DataType* values,
//                                              int num_values);
void OCT_TF_SetAttrTypeList (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_SetAttrTypeList' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_SetAttrTypeList' C API function.");
  }
  // Check octave_value type for character vector of attribute name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character vector defining the "
           "attribute name parsed to the 'TF_SetAttrTypeList' C API function.");
  }
  // Check octave_value type for DataType of Operation
  if (! args(3).is_uint32_type () || args(3).rows () != 1)
  {
    error ("tensorflow: 4th argument must be an uint32 vector defining "
           "the DataType parsed to the 'TF_SetAttrTypeList' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get attribute name
  charMatrix attr_name = args(2).char_matrix_value ();
  // Get DataType values from uint32 vector
  uint32NDArray oct_data = args(3).int32_array_value ();
  const TF_DataType* values = (TF_DataType*) oct_data.data ();
  // Get number of elements of int64 vector
  int num_values = (int) args(3).numel ();
  // Set attribute data type list
  TF_SetAttrTypeList (desc, attr_name.data (), values, num_values);
}

// TF_CAPI_EXPORT extern void TF_SetAttrPlaceholder(TF_OperationDescription* desc,
//                                                  const char* attr_name,
//                                                  const char* placeholder);
void OCT_TF_SetAttrPlaceholder (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_SetAttrPlaceholder' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_SetAttrPlaceholder' C API function.");
  }
  // Check octave_value type for character vector of attribute name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character "
           "vector defining the attribute name parsed to "
           "the 'TF_SetAttrPlaceholder' C API function.");
  }
  // Check octave_value type for character vector of attribute placeholder
  if (! args(3).is_char_matrix () || args(3).rows () != 1)
  {
    error ("tensorflow: 4th argument must be a character vector defining the "
           "placeholder parsed to the 'TF_SetAttrPlaceholder' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get attribute name
  charMatrix attr_name = args(2).char_matrix_value ();
  // Get attribute placeholder
  charMatrix attr_placeholder = args(3).char_matrix_value ();
  // Set attribute placeholder
  TF_SetAttrPlaceholder (desc, attr_name.data (), attr_placeholder.data ());
}

// TF_CAPI_EXPORT extern void TF_SetAttrFuncName(TF_OperationDescription* desc,
//                                               const char* attr_name,
//                                               const char* value, size_t length);
void OCT_TF_SetAttrFuncName (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_SetAttrFuncName' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_SetAttrFuncName' C API function.");
  }
  // Check octave_value type for character vector of attribute name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character vector defining the "
           "attribute name parsed to the 'TF_SetAttrFuncName' C API function.");
  }
  // Check octave_value type for character vector of attribute function name
  if (! args(3).is_char_matrix () || args(3).rows () != 1)
  {
    error ("tensorflow: 4th argument must be a character vector defining the "
           "function name parsed to the 'TF_SetAttrFuncName' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get attribute name
  charMatrix attr_name = args(2).char_matrix_value ();
  // Get attribute function name
  charMatrix attr_fcn_name = args(3).char_matrix_value ();
  // Get attribute function name length
  size_t length = (size_t) args(3).numel ();
  // Set attribute function name
  TF_SetAttrFuncName (desc, attr_name.data (), attr_fcn_name.data (), length);
}

// TF_CAPI_EXPORT extern void TF_SetAttrShape(TF_OperationDescription* desc,
//                                            const char* attr_name,
//                                            const int64_t* dims, int num_dims);
void OCT_TF_SetAttrShape (OCT_ARGS)
{
  if (nrhs < 5)
  {
    error ("tensorflow: four extra arguments are required "
           "for the 'TF_SetAttrShape' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_SetAttrShape' C API function.");
  }
  // Check octave_value type for character vector of attribute name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character "
           "vector defining the attribute name parsed to "
           "the 'TF_SetAttrShape' C API function.");
  }
  // Check octave_value types for size and number of dimensions for Tensor
  if (! args(3).is_int64_type () || args(3).rows () != 1)
  {
    error ("tensorflow: 4th argument must be an int64 scalar "
           "or vector defining the size of the dimensions "
           "parsed to the 'TF_SetAttrShape' C API function.");
  }
  if (! args(4).is_int32_type () || ! args(4).is_scalar_type ())
  {
    error ("tensorflow: 5th argument must be an int32 "
           "scalar defining the number of the dimensions "
           "parsed to the 'TF_SetAttrShape' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get attribute name
  charMatrix attr_name = args(2).char_matrix_value ();
  // Get size and number of dimensions for Tensor
  int64NDArray sz = args(3).int64_array_value ();
  int num_dims = args(4).int32_scalar_value ();
  OCTAVE_LOCAL_BUFFER (int64_t, dim_size, num_dims);
  for (int i = 0; i < num_dims; i++) {dim_size[i] = sz(i);}
  const int64_t* dims = dim_size;
  // Set attribute placeholder
  TF_SetAttrShape (desc, attr_name.data (), dims, num_dims);
}

// TF_CAPI_EXPORT extern void TF_SetAttrShapeList(TF_OperationDescription* desc,
//                                                const char* attr_name,
//                                                const int64_t* const* dims,
//                                                const int* num_dims,
//                                                int num_shapes);
void OCT_TF_SetAttrShapeList (OCT_ARGS)
{
  if (nrhs < 5)
  {
    error ("tensorflow: four extra arguments are required "
           "for the 'TF_SetAttrShapeList' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_SetAttrShapeList' C API function.");
  }
  // Check octave_value type for character vector of attribute name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character "
           "vector defining the attribute name parsed to "
           "the 'TF_SetAttrShapeList' C API function.");
  }
  // Check octave_value types for size and number of dimensions for Tensor
  if (! args(3).is_int64_type () || args(3).ndims () > 2)
  {
    error ("tensorflow: 4th argument must be an int64 matrix with each "
           "row defining the size of the dimensions of the respective "
           "shape parsed to the 'TF_SetAttrShapeList' C API function.");
  }
  if (! args(4).is_int32_type () || args(4).rows () != 1)
  {
    error ("tensorflow: 5th argument must be an int32 vector "
           "defining the number of the dimensions of each shape "
           "parsed to the 'TF_SetAttrShapeList' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get attribute name
  charMatrix attr_name = args(2).char_matrix_value ();
  // Get matrix with size of dimensions as row vectors
  int64NDArray sz_dim = args(3).int64_array_value ();
  // Get vector with number of dimensions as elements
  int32NDArray n_dim = args(4).int64_array_value ();
  // Get number of shapes
  int num_shapes = (int) args(4).numel ();
  // Declare pointers for sizes and numbers of dimensions
  int64_t* dim[num_shapes];
  int num_dim[num_shapes];
  // Populate arrays of pointers
  for (int i = 0; i < num_shapes; i++)
  {
    int jk = n_dim(i);
    if (jk < 1) {jk = 1;}
    OCTAVE_LOCAL_BUFFER (int64_t, dim_size, jk);
    for (int j = 0; j < jk; j++) {dim_size[i] = sz_dim(i, j);}
    dim[i] = (int64_t*) dim_size;
    num_dim[i] = (int) n_dim(i);
  }
  const int64_t* const* dims = dim;
  const int* num_dims = num_dim;
  // Set attribute placeholder
  TF_SetAttrShapeList (desc, attr_name.data (), dims, num_dims, num_shapes);
}

// TF_CAPI_EXPORT extern void TF_SetAttrTensorShapeProto(TF_OperationDescription* desc,
//                                                       const char* attr_name,
//                                                       const void* proto,
//                                                       size_t proto_len,
//                                                       TF_Status* status);
void OCT_TF_SetAttrTensorShapeProto (OCT_ARGS)
{
  if (nrhs < 5)
  {
    error ("tensorflow: four extra arguments are required "
           "for the 'TF_SetAttrTensorShapeProto' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_SetAttrTensorShapeProto' C API function.");
  }
  // Check octave_value type for character vector of attribute name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character "
           "vector defining the attribute name parsed to "
           "the 'TF_SetAttrTensorShapeProto' C API function.");
  }
  // Check octave_value type for uint8 vector of TensorShapeProto data
  if (! args(3).is_uint8_type () || args(3).rows () != 1)
  {
    error ("tensorflow: 4th argument must be a uint8 vector of "
           "binary-serialized TensorShapeProto data parsed to "
           "the 'TF_SetAttrTensorShapeProto' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(4).is_uint64_type () || ! args(4).is_scalar_type ())
  {
    error ("tensorflow: 5th argument must be an uint64 scalar pointer to the "
           "Status parsed to the 'TF_SetAttrTensorShapeProto' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get attribute name
  charMatrix attr_name = args(2).char_matrix_value ();
  // Get TensorShapeProto data
  uint8NDArray proto = args(3).uint8_array_value ();
  // Get length of TensorShapeProto data
  size_t proto_len = (size_t) args(3).numel ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(4).uint64_value ();
  // Set TensorShapeProto
  TF_SetAttrTensorShapeProto (desc, attr_name.data (),
                              proto.data (), proto_len, status);
}

// TF_CAPI_EXPORT extern void TF_SetAttrTensorShapeProtoList(
//                            TF_OperationDescription* desc, const char* attr_name,
//                            const void* const* protos, const size_t* proto_lens,
//                            int num_shapes, TF_Status* status);
void OCT_TF_SetAttrTensorShapeProtoList (OCT_ARGS)
{
  if (nrhs < 5)
  {
    error ("tensorflow: four extra arguments are required "
           "for the 'TF_SetAttrTensorShapeProtoList' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_SetAttrTensorShapeProtoList' C API function.");
  }
  // Check octave_value type for character vector of attribute name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character "
           "vector defining the attribute name parsed to "
           "the 'TF_SetAttrTensorShapeProtoList' C API function.");
  }
  // Check octave_value type for cellstr vector of attribute strings
  if (! args(3).iscell () || args(3).rows () != 1)
  {
    error ("tensorflow: 4th argument must be a cell vector of uint8 vectors "
           "representing a list of binary-serialized TensorShapeProtos "
           "parsed to the 'TF_SetAttrTensorShapeProtoList' C API function.");
  }
  Cell tmp = args(3).cell_value();
  // Get number of shapes
  int num_shapes = tmp.numel();
  // Declare pointers for TensorShapeProtos and associated lengths
  const void* proto[num_shapes];
  size_t lens[num_shapes];
  for (int i = 0; i < num_shapes; i++)
  {
    // Check each cell contains a uint8 row vector
    if (! tmp(i).is_uint8_type () || tmp(i).rows () != 1)
    {
      error ("tensorflow: 4th argument must be a cell "
             "vector of uint8 vectors representing a list of "
             "binary-serialized TensorShapeProtos parsed to the "
             "'TF_SetAttrTensorShapeProtoList' C API function.");
    }
    // Populate arrays of pointers
    uint8NDArray uint8vec = tmp(i).uint8_array_value ();
    proto[i] = uint8vec.data ();
    lens[i] = (size_t) tmp(i).numel ();
  }
  // Check octave_value type for pointer to Status
  if (! args(4).is_uint64_type () || ! args(4).is_scalar_type ())
  {
    error ("tensorflow: 5th argument must be an uint64 "
           "scalar pointer to the Status parsed to the "
           "'TF_SetAttrTensorShapeProtoList' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get attribute name
  charMatrix attr_name = args(2).char_matrix_value ();
  // Cast TensorShapeProtos and associated lengths
  const void* const* protos = proto;
  const size_t* proto_lens = lens;
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(4).uint64_value ();
  // Set TensorShapeProtos
  TF_SetAttrTensorShapeProtoList (desc, attr_name.data (),
                                  protos, proto_lens, num_shapes, status);
}

// TF_CAPI_EXPORT extern void TF_SetAttrTensor(TF_OperationDescription* desc,
//                                             const char* attr_name,
//                                             TF_Tensor* value,
//                                             TF_Status* status);
void OCT_TF_SetAttrTensor (OCT_ARGS)
{
  if (nrhs < 5)
  {
    error ("tensorflow: four extra arguments are required "
           "for the 'TF_SetAttrTensor' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_SetAttrTensor' C API function.");
  }
  // Check octave_value type for character vector of attribute name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character "
           "vector defining the attribute name parsed to "
           "the 'TF_SetAttrTensor' C API function.");
  }
  // Check octave_value type for pointer to Tensor
  if (! args(3).is_uint64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 scalar pointer to "
           "the Tensor parsed to the 'TF_SetAttrTensor' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(4).is_uint64_type () || ! args(4).is_scalar_type ())
  {
    error ("tensorflow: 5th argument must be an uint64 scalar pointer to "
           "the Status parsed to the 'TF_SetAttrTensor' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get attribute name
  charMatrix attr_name = args(2).char_matrix_value ();
  // Get pointer to Tensor
  TF_Tensor* tensor = (TF_Tensor*) args(3).uint64_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(4).uint64_value ();
  // Set Tensor
  TF_SetAttrTensor (desc, attr_name.data (), tensor, status);
}

// TF_CAPI_EXPORT extern void TF_SetAttrTensorList(TF_OperationDescription* desc,
//                                                 const char* attr_name,
//                                                 TF_Tensor* const* values,
//                                                 int num_values,
//                                                 TF_Status* status);
void OCT_TF_SetAttrTensorList (OCT_ARGS)
{
  if (nrhs < 5)
  {
    error ("tensorflow: four extra arguments are required "
           "for the 'TF_SetAttrTensorList' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_SetAttrTensorList' C API function.");
  }
  // Check octave_value type for character vector of attribute name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character "
           "vector defining the attribute name parsed to "
           "the 'TF_SetAttrTensorList' C API function.");
  }
  // Check octave_value type for pointers to Tensors
  if (! args(3).is_uint64_type () || args(3).rows () != 1)
  {
    error ("tensorflow: 4th argument must be an uint64 vector of pointers to "
           "the Tensors parsed to the 'TF_SetAttrTensorList' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(4).is_uint64_type () || ! args(4).is_scalar_type ())
  {
    error ("tensorflow: 5th argument must be an uint64 scalar pointer to "
           "the Status parsed to the 'TF_SetAttrTensorList' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get attribute name
  charMatrix attr_name = args(2).char_matrix_value ();
  // Get pointers to Tensors
  uint64NDArray oct_data = args(3).uint64_array_value ();
  // Get number of pointers to Tensors
  int num_values = (int) oct_data.numel ();
  // Declare pointers for sizes and numbers of dimensions
  TF_Tensor* tensor[num_values];
  // Populate arrays of pointers
  for (int i = 0; i < num_values; i++)
  {
    tensor[i] = (TF_Tensor*) (uint64_t) oct_data(i);
  }
  TF_Tensor* const* values = tensor;
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(4).uint64_value ();
  // Set Tensors
  TF_SetAttrTensorList (desc, attr_name.data (), values, num_values, status);
}

// TF_CAPI_EXPORT extern void TF_SetAttrValueProto(TF_OperationDescription* desc,
//                                                 const char* attr_name,
//                                                 const void* proto,
//                                                 size_t proto_len,
//                                                 TF_Status* status);
void OCT_TF_SetAttrValueProto (OCT_ARGS)
{
  if (nrhs < 5)
  {
    error ("tensorflow: four extra arguments are required "
           "for the 'TF_SetAttrValueProto' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_SetAttrValueProto' C API function.");
  }
  // Check octave_value type for character vector of attribute name
  if (! args(2).is_char_matrix () || args(2).rows () != 1)
  {
    error ("tensorflow: 3rd argument must be a character "
           "vector defining the attribute name parsed to "
           "the 'TF_SetAttrValueProto' C API function.");
  }
  // Check octave_value type for uint8 vector of TensorShapeProto data
  if (! args(3).is_uint8_type () || args(3).rows () != 1)
  {
    error ("tensorflow: 4th argument must be a uint8 vector representing "
           "a binary serialization of an AttrValue protocol buffer parsed "
           "to the 'TF_SetAttrValueProto' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(4).is_uint64_type () || ! args(4).is_scalar_type ())
  {
    error ("tensorflow: 5th argument must be an uint64 scalar pointer to the "
           "Status parsed to the 'TF_SetAttrValueProto' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get attribute name
  charMatrix attr_name = args(2).char_matrix_value ();
  // Get TensorShapeProto data
  uint8NDArray proto = args(3).uint8_array_value ();
  // Get length of TensorShapeProto data
  size_t p_len = (size_t) args(3).numel ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(4).uint64_value ();
  // Set TensorShapeProto
  TF_SetAttrValueProto (desc, attr_name.data (), proto.data (), p_len, status);
}

// TF_CAPI_EXPORT extern TF_Operation* TF_FinishOperationLocked(
//                       TF_OperationDescription* desc, TF_Status* status);
octave_value OCT_TF_FinishOperationLocked (OCT_ARGS)
{
  if (nrhs < 3)
  {
    error ("tensorflow: two extra arguments are required "
           "for the 'TF_FinishOperationLocked' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_FinishOperationLocked' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer to the "
           "Status parsed to the 'TF_FinishOperationLocked' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(2).uint64_value ();
  // Get Operation and return its pointer
  TF_Operation* oper = TF_FinishOperationLocked (desc, status);
  octave_uint64 ptr = (uint64_t) oper;
  octave_value plhs = ptr;
  return plhs;
}

// TF_CAPI_EXPORT extern TF_Operation* TF_FinishOperation(
//                       TF_OperationDescription* desc, TF_Status* status);
octave_value OCT_TF_FinishOperation (OCT_ARGS)
{
  if (nrhs < 3)
  {
    error ("tensorflow: two extra arguments are required "
           "for the 'TF_FinishOperation' C API function.");
  }
  // Check octave_value type for pointer to OperationDescription
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar "
           "pointer to the OperationDescription parsed to the "
           "'TF_FinishOperation' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer to "
           "the Status parsed to the 'TF_FinishOperation' C API function.");
  }
  // Get pointer to OperationDescription
  TF_OperationDescription* desc = (TF_OperationDescription*) args(1).uint64_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(2).uint64_value ();
  // Get Operation and return its pointer
  TF_Operation* oper = TF_FinishOperation (desc, status);
  octave_uint64 ptr = (uint64_t) oper;
  octave_value plhs = ptr;
  return plhs;
}
