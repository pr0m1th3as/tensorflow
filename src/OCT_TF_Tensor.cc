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

void NoOpDeallocator (void* data, size_t a, void* b) {}

// -----------------------------------------------------------------------------
// OCTAVE specific functions referenced by the TF_Tensor classdef
// -----------------------------------------------------------------------------

// TF_Tensor* TF_LoadTensor(octave_value data)
octave_value OCT_TF_LoadTensor (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_LoadTensor' OCTAVE function.");
  }
  if (args(1).isempty ())
  {
    error ("tensorflow: 2nd argument cannot be empty, it must contain non-"
           "empty data to be parsed to the 'TF_LoadTensor' OCTAVE function.");
  }
  // Get number of elements
  octave_idx_type nelem = args(1).numel ();
  // Check for row vector
  bool rowvec = false;
  if (args(1).rows () == 1) {rowvec = true;}
  // Get size and number of dimensions
  dim_vector oct_dims = args(1).dims ();
  int num_dims = args(1).ndims ();
  const octave_idx_type *tf_dims = &oct_dims.elem (0);
  // Handle 0-dimensional scalar values and 1-dimensional row vectors
  if (nelem == 1)
  {
    num_dims = 0;
    tf_dims = &oct_dims(0);
  }
  else if (rowvec)
  {
    num_dims = 1;
    tf_dims = &oct_dims(1);
  }
  // Create new Tensor according to data type
  // Copy data from Octave to Tensor and return its pointer
  TF_Tensor* newTensor;
  // TF_DOUBLE
  if (args(1).is_double_type () && ! args(1).iscomplex ())
  {
    NDArray oct_data = args(1).array_value ();
    size_t len = TF_DataTypeSize (TF_DOUBLE) * (int) nelem;
    newTensor = TF_NewTensor (TF_DOUBLE, tf_dims, num_dims,
                             (void*) oct_data.data (), len, &NoOpDeallocator, 0);
  }
  // TF_COMPLEX128
  else if (args(1).is_double_type () && args(1).iscomplex ())
  {
    ComplexNDArray oct_data = args(1).complex_array_value ();
    size_t len = TF_DataTypeSize (TF_COMPLEX128) * (int) nelem;
    newTensor = TF_NewTensor (TF_COMPLEX128, tf_dims, num_dims,
                             (void*) oct_data.data (), len, &NoOpDeallocator, 0);
  }
  // TF_FLOAT
  else if (args(1).is_single_type () && ! args(1).iscomplex ())
  {
    FloatNDArray oct_data = args(1).float_array_value ();
    size_t len = TF_DataTypeSize (TF_FLOAT) * (int) nelem;
    newTensor = TF_NewTensor (TF_FLOAT, tf_dims, num_dims,
                             (void*) oct_data.data (), len, &NoOpDeallocator, 0);
  }
  // TF_COMPLEX64
  else if (args(1).is_single_type () && args(1).iscomplex ())
  {
    FloatComplexNDArray oct_data = args(1).float_complex_array_value ();
    size_t len = TF_DataTypeSize (TF_COMPLEX64) * (int) nelem;
    newTensor = TF_NewTensor (TF_COMPLEX64, tf_dims, num_dims,
                             (void*) oct_data.data (), len, &NoOpDeallocator, 0);
  }
  // TF_INT64
  else if (args(1).is_int64_type ())
  {
    int64NDArray oct_data = args(1).int64_array_value ();
    size_t len = TF_DataTypeSize (TF_INT64) * (int) nelem;
    newTensor = TF_NewTensor (TF_INT64, tf_dims, num_dims,
                             (void*) oct_data.data (), len, &NoOpDeallocator, 0);
  }
  // TF_UINT64
  else if (args(1).is_uint64_type ())
  {
    uint64NDArray oct_data = args(1).uint64_array_value ();
    size_t len = TF_DataTypeSize (TF_UINT64) * (int) nelem;
    newTensor = TF_NewTensor (TF_UINT64, tf_dims, num_dims,
                             (void*) oct_data.data (), len, &NoOpDeallocator, 0);
  }
  // TF_INT32
  else if (args(1).is_int32_type ())
  {
    int32NDArray oct_data = args(1).int32_array_value ();
    size_t len = TF_DataTypeSize (TF_INT32) * (int) nelem;
    newTensor = TF_NewTensor (TF_INT32, tf_dims, num_dims,
                             (void*) oct_data.data (), len, &NoOpDeallocator, 0);
  }
  // TF_UINT32
  else if (args(1).is_uint32_type ())
  {
    uint32NDArray oct_data = args(1).uint32_array_value ();
    size_t len = TF_DataTypeSize (TF_UINT32) * (int) nelem;
    newTensor = TF_NewTensor (TF_UINT32, tf_dims, num_dims,
                             (void*) oct_data.data (), len, &NoOpDeallocator, 0);
  }
  // TF_INT16
  else if (args(1).is_int16_type ())
  {
    int16NDArray oct_data = args(1).int16_array_value ();
    size_t len = TF_DataTypeSize (TF_INT16) * (int) nelem;
    newTensor = TF_NewTensor (TF_INT16, tf_dims, num_dims,
                             (void*) oct_data.data (), len, &NoOpDeallocator, 0);
  }
  // TF_UINT16
  else if (args(1).is_uint16_type ())
  {
    uint16NDArray oct_data = args(1).uint16_array_value ();
    size_t len = TF_DataTypeSize (TF_UINT16) * (int) nelem;
    newTensor = TF_NewTensor (TF_UINT16, tf_dims, num_dims,
                             (void*) oct_data.data (), len, &NoOpDeallocator, 0);
  }
  // TF_INT8
  else if (args(1).is_int8_type ())
  {
    int8NDArray oct_data = args(1).int8_array_value ();
    size_t len = TF_DataTypeSize (TF_INT8) * (int) nelem;
    newTensor = TF_NewTensor (TF_INT8, tf_dims, num_dims,
                             (void*) oct_data.data (), len, &NoOpDeallocator, 0);
  }
  // TF_UINT8
  else if (args(1).is_uint8_type ())
  {
    uint8NDArray oct_data = args(1).uint8_array_value ();
    size_t len = TF_DataTypeSize (TF_UINT8) * (int) nelem;
    newTensor = TF_NewTensor (TF_UINT8, tf_dims, num_dims,
                             (void*) oct_data.data (), len, &NoOpDeallocator, 0);
  }
  // TF_BOOL
  else if (args(1).is_bool_matrix ())
  {
    boolNDArray oct_data = args(1).bool_array_value ();
    size_t len = TF_DataTypeSize (TF_BOOL) * (int) nelem;
    newTensor = TF_NewTensor (TF_BOOL, tf_dims, num_dims,
                             (void*) oct_data.data (), len, &NoOpDeallocator, 0);
  }
  // TF_STRING
  else if (args(1).is_char_matrix ())
  {
    if (! rowvec)
    {
      error ("tensorflow: only a character vector can be loaded into Tensor. "
             "For multiple rows of characters use a cellstr array.");
    }
    charMatrix oct_data = args(1).char_matrix_value ();
    size_t str_len = (size_t) args(1).numel ();
    TF_TString* tstring = reinterpret_cast<TF_TString*> (malloc (sizeof (TF_TString)));
    TF_StringInit (tstring);
    TF_StringCopy (tstring, oct_data.data (), str_len);
    int64_t dims[] = {1};
    int ndims = 1;
    newTensor = TF_NewTensor (TF_STRING, dims, ndims, tstring,
                              sizeof (TF_TString), &NoOpDeallocator, 0);
  }
  else if (args(1).iscellstr ())
  {
    Array<string> oct_data = args(1).cellstr_value ();
    if (nelem == 1)
    {
      size_t str_len = (size_t) oct_data(0).length ();
      TF_TString* tstring = reinterpret_cast<TF_TString*> (malloc (sizeof (TF_TString)));
      TF_StringInit (tstring);
      TF_StringCopy (tstring, oct_data(0).c_str (), str_len);
      int64_t dims[] = {1};
      int ndims = 0;
      newTensor = TF_NewTensor (TF_STRING, dims, ndims, tstring,
                                sizeof (TF_TString), &NoOpDeallocator, 0);
    }
    else
    {
      TF_TString* tstring[(int)nelem];
      size_t len = 0;
      for (int i = 0; i < nelem; i++)
      {
        size_t str_len = (size_t) oct_data(i).length ();
        tstring[i] = reinterpret_cast<TF_TString*> (malloc (sizeof (TF_TString)));
        TF_StringInit (tstring[i]);
        TF_StringCopy (tstring[i], oct_data(i).c_str (), str_len);
      }
      newTensor = TF_NewTensor (TF_STRING, tf_dims, num_dims, tstring,
                                sizeof (tstring), &NoOpDeallocator, 0);
    }
  }
  else
  {
    const char* oct_type = args(1).type_name ().c_str ();
    error ("tensorflow: '%s' type cannot be loaded into Tensor.", oct_type);
  }
  octave_uint64 ptr = (uint64_t) newTensor;
  octave_value plhs = ptr;
  return plhs;
}

// octave_value TF_SaveTensor(TF_Tensor* tensor)
octave_value OCT_TF_SaveTensor (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_SaveTensor' OCTAVE function.");
  }
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer "
           "to the Tensor parsed to the 'TF_SaveTensor' OCTAVE function.");
  }
  // Get pointer to Tensor
  TF_Tensor* tensor = (TF_Tensor*) args(1).uint64_value ();
  // Get data type of Tensor
  TF_DataType tf_type = TF_TensorType (tensor);
  // Get size and number of dimensions of Tensor
  int num_dims = TF_NumDims (tensor);
  dim_vector oct_dims;
  // Handle 0-dimensional scalar values and 1-dimensional row vectors
  if (num_dims == 0)
  {
    oct_dims.resize (2);
    oct_dims(0) = 1;
    oct_dims(1) = 1;
  }
  else if (num_dims == 1)
  {
    oct_dims.resize (2);
    oct_dims(0) = 1;
    oct_dims(1) = TF_Dim (tensor, 0);
  }
  else
  {
    oct_dims.resize (num_dims);
    for (int i = 0; i < num_dims; i++) {oct_dims(i) = TF_Dim (tensor, i);}
  }
  // Create new octave value according to data type
  // Copy data from Tensor to Octave value and return it.
  octave_value plhs;
  // TF_DOUBLE
  if (tf_type == TF_DOUBLE)
  {
    NDArray oct_data(oct_dims);
    memcpy (oct_data.fortran_vec (), TF_TensorData (tensor),
                                     TF_TensorByteSize (tensor));
    plhs = oct_data;
  }
  // TF_COMPLEX128
  else if (tf_type == TF_COMPLEX128)
  {
    ComplexNDArray oct_data(oct_dims);
    memcpy (oct_data.fortran_vec (), TF_TensorData (tensor),
                                     TF_TensorByteSize (tensor));
    plhs = oct_data;
  }
  // TF_FLOAT
  else if (tf_type == TF_FLOAT)
  {
    FloatNDArray oct_data(oct_dims);
    memcpy (oct_data.fortran_vec (), TF_TensorData (tensor),
                                     TF_TensorByteSize (tensor));
    plhs = oct_data;
  }
  // TF_COMPLEX64
  else if (tf_type == TF_COMPLEX64)
  {
    FloatComplexNDArray oct_data(oct_dims);
    memcpy (oct_data.fortran_vec (), TF_TensorData (tensor),
                                     TF_TensorByteSize (tensor));
    plhs = oct_data;
  }
  // TF_INT64
  else if (tf_type == TF_INT64)
  {
    int64NDArray oct_data(oct_dims);
    memcpy (oct_data.fortran_vec (), TF_TensorData (tensor),
                                     TF_TensorByteSize (tensor));
    plhs = oct_data;
  }
  // TF_UINT64
  else if (tf_type == TF_UINT64)
  {
    uint64NDArray oct_data(oct_dims);
    memcpy (oct_data.fortran_vec (), TF_TensorData (tensor),
                                     TF_TensorByteSize (tensor));
    plhs = oct_data;
  }
  // TF_INT32
  else if (tf_type == TF_INT32)
  {
    int32NDArray oct_data(oct_dims);
    memcpy (oct_data.fortran_vec (), TF_TensorData (tensor),
                                     TF_TensorByteSize (tensor));
    plhs = oct_data;
  }
  // TF_UINT32
  else if (tf_type == TF_UINT32)
  {
    uint32NDArray oct_data(oct_dims);
    memcpy (oct_data.fortran_vec (), TF_TensorData (tensor),
                                     TF_TensorByteSize (tensor));
    plhs = oct_data;
  }
  // TF_INT16
  else if (tf_type == TF_INT16)
  {
    int16NDArray oct_data(oct_dims);
    memcpy (oct_data.fortran_vec (), TF_TensorData (tensor),
                                     TF_TensorByteSize (tensor));
    plhs = oct_data;
  }
  // TF_UINT16
  else if (tf_type == TF_UINT16)
  {
    uint16NDArray oct_data(oct_dims);
    memcpy (oct_data.fortran_vec (), TF_TensorData (tensor),
                                     TF_TensorByteSize (tensor));
    plhs = oct_data;
  }
  // TF_INT8
  else if (tf_type == TF_INT8)
  {
    int8NDArray oct_data(oct_dims);
    memcpy (oct_data.fortran_vec (), TF_TensorData (tensor),
                                     TF_TensorByteSize (tensor));
    plhs = oct_data;
  }
  // TF_UINT8
  else if (tf_type == TF_UINT8)
  {
    uint8NDArray oct_data(oct_dims);
    memcpy (oct_data.fortran_vec (), TF_TensorData (tensor),
                                     TF_TensorByteSize (tensor));
    plhs = oct_data;
  }
  // TF_BOOL
  else if (tf_type == TF_BOOL)
  {
    boolNDArray oct_data(oct_dims);
    memcpy (oct_data.fortran_vec (), TF_TensorData (tensor),
                                     TF_TensorByteSize (tensor));
    plhs = oct_data;
  }
  // TF_STRING
  else if (tf_type == TF_STRING)
  {
    // Get underlying data from Tensor
    TF_TString* tstring = (TF_TString*) TF_TensorData (tensor);

    // Get number of dimensions and number of elements
    // to distinguish between character vector and cellstr array
    int ndims = TF_NumDims (tensor);
    int64_t n_elem = TF_TensorElementCount (tensor);
    if (ndims == 1 && n_elem == 1)        // Character vector
    {
      // Get pointer to string data and copy it to charMatrix
      const char* tf_str = TF_StringGetDataPointer (tstring);
      plhs = charMatrix (tf_str);
    }
    else if (ndims == 0 && n_elem == 1)   // Cellstr scalar
    {
      // Get pointer to string data and copy it to cellstr
      const char* tf_str = TF_StringGetDataPointer (tstring);
      Cell oct_data(1,1);
      oct_data(0,0) = charMatrix (tf_str);
      plhs = oct_data;
    }
    else
    {
      Cell oct_data(oct_dims);
      cout << n_elem << endl;
      for (int i = 0; i < n_elem; i++)
      {
        // This does not work !!
        // We need a way to find the pointers to each TString inside the
        // Tensor and then retrieve the string data from each TString

        //cout << "tstring[i]: " << (tstring[i]) << endl;
        //cout << "tstring[i]: " << tstring << endl;
        cout << "&tstring[i]: " << &tstring[i] << endl;
        cout << "sizeof tstring[i]: " << sizeof (tstring) << endl;
        //cout << "*tstring[i]: " << *tstring[i] << endl;
        // Get pointer to TString element
        const TF_TString* tstring_elem;
        //tstring_elem = reinterpret_cast<TF_TString*> (tstring[i]);
        //tstring_elem = *(TF_TString*) (tstring[i]);
        // Get pointer to string data and copy it to cellstr
        const char* tf_str = TF_StringGetDataPointer (&tstring[i]);
        //cout << "tf_str: " << tf_str << endl;
        oct_data(i) = charMatrix (tf_str);
      }
      plhs = oct_data;
    }
  }
  else
  {
    // Find Tensor data type
    string missing_type;
    if (tf_type == 11) {missing_type = "TF_QINT8";}
    else if (tf_type == 12) {missing_type = "TF_QUINT8";}
    else if (tf_type == 13) {missing_type = "TF_QINT32";}
    else if (tf_type == 14) {missing_type = "TF_BFLOAT16";}
    else if (tf_type == 15) {missing_type = "TF_QINT16";}
    else if (tf_type == 16) {missing_type = "TF_QUINT16";}
    else if (tf_type == 19) {missing_type = "TF_HALF";}
    else if (tf_type == 20) {missing_type = "TF_RESOURCE";}
    else if (tf_type == 21) {missing_type = "TF_VARIANT";}
    else if (tf_type == 24) {missing_type = "TF_FLOAT8_E5M2";}
    else if (tf_type == 25) {missing_type = "TF_FLOAT8_E4M3FN";}
    else if (tf_type == 29) {missing_type = "TF_INT4";}
    else if (tf_type == 30) {missing_type = "TF_UINT4";}
    error ("tensorflow: '%s' data type in Tensor is not supported by Octave.",
           missing_type.c_str ());
  }
  return plhs;
}

// -----------------------------------------------------------------------------
// C API functions referenced by the TF_Tensor classdef
// -----------------------------------------------------------------------------

// TF_CAPI_EXPORT extern TF_Tensor* TF_NewTensor(TF_DataType,
//                const int64_t* dims, int num_dims, void* data, size_t len,
//                void (*deallocator)(void* data, size_t len, void* arg),
//                void* deallocator_arg);
octave_value OCT_TF_NewTensor (OCT_ARGS)
{
  if (nrhs < 6)
  {
    error ("tensorflow: five extra arguments are required "
           "for the 'TF_NewTensor' C API function.");
  }
  // Check octave_value type for DataType for new Tensor
  if (! args(1).is_uint32_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint32 scalar "
           "indexing the appropriate TF_DataType to be parsed to "
           "the 'TF_NewTensor' C API function.");
  }
  // Check octave_value types for size and number of dimensions for new Tensor
  if (! args(2).is_int64_type () || ! args(2).rows() == 1)
  {
    error ("tensorflow: 3rd argument must be an int64 scalar or "
           "vector defining the size of the dimensions of the data "
           "to be parsed to the 'TF_NewTensor' C API function.");
  }
  if (! args(3).is_int32_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an int32 scalar "
           "defining the number of the dimensions of the data to "
           "be parsed to the 'TF_NewTensor' C API function.");
  }
  // Check octave_value types for pointer and bytesize of data for new Tensor
  if (! args(4).is_uint64_type () || ! args(4).is_scalar_type ())
  {
    error ("tensorflow: 5th argument must be an uint64 scalar pointer to the "
           "data structure to be parsed to the 'TF_NewTensor' C API function.");
  }
  if (! args(5).is_uint64_type () || ! args(5).is_scalar_type ())
  {
    error ("tensorflow: 6th argument must be an uint64 scalar "
           "defining the bytesize of the data structure to be "
           "parsed to the 'TF_NewTensor' C API function.");
  }
  // Get data type for new Tensor
  TF_DataType type = (TF_DataType) args(1).uint_value ();
  // Get size and number of dimensions for new Tensor
  int64NDArray sz = args(2).int64_array_value ();
  int num_dims = args(3).int32_scalar_value ();
  OCTAVE_LOCAL_BUFFER (int64_t, dim_size, num_dims);
  for (int i = 0; i < num_dims; i++) {dim_size[i] = sz(i);}
  const int64_t* dims = dim_size;
  // Get pointer and bytesize of data for new Tensor
  void* data = (void*) args(4).uint64_value ();
  size_t len = args(5).uint64_value ();
  // Construct new Tensor and return its pointer
  TF_Tensor* newTensor = TF_NewTensor (type, dims, num_dims, data, len,
                                       &NoOpDeallocator, 0);
  octave_uint64 ptr = (uint64_t) newTensor;
  octave_value plhs = ptr;
  return plhs;
}

// TF_CAPI_EXPORT extern TF_Tensor* TF_AllocateTensor(TF_DataType,
//                                                    const int64_t* dims,
//                                                    int num_dims, size_t len);
octave_value OCT_TF_AllocateTensor (OCT_ARGS)
{
  if (nrhs < 5)
  {
    error ("tensorflow: four extra arguments are required "
           "for the 'TF_AllocateTensor' C API function.");
  }
  // Check octave_value type for DataType for new Tensor
  if (! args(1).is_uint32_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint32 scalar "
           "indexing the appropriate TF_DataType to be parsed to "
           "the 'TF_AllocateTensor' C API function.");
  }
  // Check octave_value types for size and number of dimensions for new Tensor
  if (! args(2).is_int64_type () || ! args(2).rows() == 1)
  {
    error ("tensorflow: 3rd argument must be an int64 scalar or "
           "vector defining the size of the dimensions of the data "
           "to be parsed to the 'TF_AllocateTensor' C API function.");
  }
  if (! args(3).is_int32_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an int32 scalar "
           "defining the number of the dimensions of the data to "
           "be parsed to the 'TF_AllocateTensor' C API function.");
  }
  // Check octave_value types for bytesize of data for new Tensor
  if (! args(4).is_uint64_type () || ! args(4).is_scalar_type ())
  {
    error ("tensorflow: 5th argument must be an uint64 scalar "
           "defining the size of memory to be allocated by the "
           "'TF_AllocateTensor' C API function.");
  }
  // Get data type for new Tensor
  TF_DataType type = (TF_DataType) args(1).uint_value ();
  // Get size and number of dimensions for new Tensor
  uint64NDArray sz = args(2).int64_array_value ();
  int num_dims = args(3).int32_scalar_value ();
  OCTAVE_LOCAL_BUFFER (int64_t, dim_size, num_dims);
  for (int i = 0; i < num_dims; i++) {dim_size[i] = sz(i);}
  const int64_t* dims = dim_size;
  // Get bytesize of data of Tensor
  size_t len = args(4).uint64_value ();
  // Allocate new Tensor and return its pointer
  TF_Tensor* newTensor = TF_AllocateTensor (type, dims, num_dims, len);
  octave_uint64 ptr = (uint64_t) newTensor;
  octave_value plhs = ptr;
  return plhs;
}

// TF_CAPI_EXPORT extern TF_Tensor* TF_TensorMaybeMove(TF_Tensor* tensor);
octave_value OCT_TF_TensorMaybeMove (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_TensorMaybeMove' C API function.");
  }
  // Check octave_value type for pointer to Tensor
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Tensor parsed to the 'TF_TensorMaybeMove' C API function.");
  }
  // Get pointer to Tensor
  TF_Tensor* tensor = (TF_Tensor*) args(1).uint64_value ();
  // Relocate Tensor
  TF_Tensor* newTensor = TF_TensorMaybeMove (tensor);
  octave_uint64 ptr = (uint64_t) newTensor;
  octave_value plhs = ptr;
  return plhs;
}

// TF_CAPI_EXPORT extern void TF_DeleteTensor(TF_Tensor*);
void OCT_TF_DeleteTensor (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_DeleteTensor' C API function.");
  }
  // Check octave_value type for pointer to Tensor
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Tensor parsed to the 'TF_DeleteTensor' C API function.");
  }
  // Get pointer to Tensor
  TF_Tensor* tensor = (TF_Tensor*) args(1).uint64_value ();
  // Delete Tensor
  TF_DeleteTensor (tensor);
}

// TF_CAPI_EXPORT extern TF_DataType TF_TensorType(const TF_Tensor*);
octave_value OCT_TF_TensorType (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_TensorType' C API function.");
  }
  // Check octave_value type for pointer to Tensor
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer "
           "to the Tensor parsed to the 'TF_TensorType' C API function.");
  }
  // Get pointer to Tensor
  TF_Tensor* tensor = (TF_Tensor*) args(1).uint64_value ();
  // Get data type of Tensor
  TF_DataType dtype = TF_TensorType (tensor);
  octave_uint32 dt = static_cast<int> (dtype);
  octave_value plhs = dt;
  return plhs;
}

// TF_CAPI_EXPORT extern void TF_SetShape(TF_Tensor* tensor,
//                                        const int64_t* dims, int num_dims);
void OCT_TF_SetShape (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_SetShape' C API function.");
  }
  // Check octave_value type for pointer to Tensor
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer "
           "to the Tensor parsed to the 'TF_SetShape' C API function.");
  }
  // Check octave_value types for size and number of dimensions for Tensor
  if (! args(2).is_int64_type () || ! args(2).rows () == 1)
  {
    error ("tensorflow: 3rd argument must be an int64 scalar "
           "or vector defining the size of the dimensions to "
           "be parsed to the 'TF_SetShape' C API function.");
  }
  if (! args(3).is_int32_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an int32 "
           "scalar defining the number of the dimensions to "
           "be parsed to the 'TF_SetShape' C API function.");
  }
  // Get pointer to Tensor
  TF_Tensor* tensor = (TF_Tensor*) args(1).uint64_value ();
  // Get size and number of dimensions for reshaping Tensor
  int64NDArray sz = args(2).int64_array_value ();
  int num_dims = args(3).int32_scalar_value ();
  OCTAVE_LOCAL_BUFFER (int64_t, dim_size, num_dims);
  for (int i = 0; i < num_dims; i++) {dim_size[i] = sz(i);}
  const int64_t* dims = dim_size;
  // Reshape Tensor
  TF_SetShape (tensor, dims, num_dims);
}

// TF_CAPI_EXPORT extern int TF_NumDims(const TF_Tensor*);
octave_value OCT_TF_NumDims (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_NumDims' C API function.");
  }
  // Check octave_value type for pointer to Tensor
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer "
           "to the Tensor parsed to the 'TF_NumDims' C API function.");
  }
  // Get pointer to Tensor
  TF_Tensor* tensor = (TF_Tensor*) args(1).uint64_value ();
  // Get number of dimensions of Tensor
  octave_int32 num_dims = TF_NumDims (tensor);
  octave_value plhs = num_dims;
  return plhs;
}

// TF_CAPI_EXPORT extern int64_t TF_Dim(const TF_Tensor* tensor, int dim_index);
octave_value OCT_TF_Dim (OCT_ARGS)
{
  if (nrhs < 3)
  {
    error ("tensorflow: two extra arguments are required "
           "for the 'TF_Dim' C API function.");
  }
  // Check octave_value type for pointer to Tensor
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer "
           "to the Tensor parsed to the 'TF_Dim' C API function.");
  }
  // Check octave_value type for dimension index for Tensor
  if (! args(2).is_int32_type() || ! args(2).is_scalar_type())
  {
    error ("tensorflow: 3rd argument must be an uint32 scalar indexing "
           "the dimension to be parsed to the 'TF_Dim' C API function.");
  }
  // Get pointer to Tensor
  TF_Tensor* tensor = (TF_Tensor*) args(1).uint64_value ();
  // Get dimension index for Tensor
  int dim_index = args(2).int_value ();
  // Check for valid index
  int num_dims = TF_NumDims (tensor);
  if (dim_index > num_dims || dim_index < 1)
  {
    error ("tensorflow: you are trying to index non existing dimension.");
  }
  // Get length of indexed dimension
  int64_t dim_length = TF_Dim (tensor, dim_index - 1);
  octave_uint64 dim_len = (uint64_t) dim_length;
  octave_value plhs = dim_len;
  return plhs;
}

// TF_CAPI_EXPORT extern size_t TF_TensorByteSize(const TF_Tensor*);
octave_value OCT_TF_TensorByteSize (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_TensorByteSize' C API function.");
  }
  // Check octave_value type for pointer to Tensor
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Tensor parsed to the 'TF_TensorByteSize' C API function.");
  }
  // Get pointer to Tensor
  TF_Tensor* tensor = (TF_Tensor*) args(1).uint64_value ();
  // Get bytesize of data in Tensor
  size_t len = TF_TensorByteSize (tensor);
  octave_uint64 bytesize = (uint64_t) len;
  octave_value plhs = bytesize;
  return plhs;
}

// TF_CAPI_EXPORT extern void* TF_TensorData(const TF_Tensor*);
octave_value OCT_TF_TensorData (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_TensorData' C API function.");
  }
  // Check octave_value type for pointer to Tensor
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer "
           "to the Tensor parsed to the 'TF_TensorData' C API function.");
  }
  // Get pointer to Tensor
  TF_Tensor* tensor = (TF_Tensor*) args(1).uint64_value ();
  // Create new Buffer and pass by reference
  TF_Buffer* buffer = TF_NewBuffer ();
  buffer->data = TF_TensorData (tensor);
  buffer->length = TF_TensorByteSize (tensor);
  buffer->data_deallocator = NULL;
  // Return pointer to Buffer
  octave_uint64 b_ptr = (uint64_t) buffer;
  octave_value plhs = b_ptr;
  return plhs;
}

// TF_CAPI_EXPORT extern void TF_TensorFromProto(const TF_Buffer* from,
//                                               TF_Tensor* to, TF_Status* status);
void OCT_TF_TensorFromProto (OCT_ARGS)
{
  if (nrhs < 4)
  {
    error ("tensorflow: three extra arguments are required "
           "for the 'TF_TensorFromProto' C API function.");
  }
  // Check octave_value type for pointer to Buffer (source)
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Buffer parsed to the 'TF_TensorFromProto' C API function.");
  }
  // Check octave_value type for pointer to Tensor (target)
  if (! args(2).is_uint64_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint64 scalar pointer to "
           "the Tensor parsed to the 'TF_TensorFromProto' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(3).is_uint64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 scalar pointer to "
           "the Status parsed to the 'TF_TensorFromProto' C API function.");
  }
  // Get pointer to Buffer (source)
  const TF_Buffer* from = (TF_Buffer*) args(1).uint64_value ();
  // Get pointer to Tensor (target)
  TF_Tensor* to = (TF_Tensor*) args(2).uint64_value ();
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(3).uint64_value ();
  // Transfer Buffer to Tensor
  TF_TensorFromProto (from, to, status);
}

// TF_CAPI_EXPORT extern int64_t TF_TensorElementCount(const TF_Tensor* tensor);
octave_value OCT_TF_TensorElementCount (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_TensorElementCount' C API function.");
  }
  // Check octave_value type for pointer to Tensor
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Tensor parsed to the 'TF_TensorElementCount' C API function.");
  }
  // Get pointer to Tensor
  TF_Tensor* tensor = (TF_Tensor*) args(1).uint64_value ();
  // Get number of elements of Tensor
  octave_int64 n_elem = (int64_t) TF_TensorElementCount (tensor);
  octave_value plhs = n_elem;
  return plhs;
}

// TF_CAPI_EXPORT extern void TF_TensorBitcastFrom(const TF_Tensor* from,
//                                                 TF_DataType type, TF_Tensor* to,
//                                                 const int64_t* new_dims,
//                                                 int num_new_dims,
//                                                 TF_Status* status);
void OCT_TF_TensorBitcastFrom (OCT_ARGS)
{
  if (nrhs < 7)
  {
    error ("tensorflow: six extra arguments are required "
           "for the 'TF_TensorBitcastFrom' C API function.");
  }
  // Check octave_value type for pointer to source Tensor
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 "
           "scalar pointer to the source Tensor parsed to "
           "the 'TF_TensorBitcastFrom' C API function.");
  }
  // Check octave_value type for data type for target Tensor
  if (! args(2).is_uint32_type () || ! args(2).is_scalar_type ())
  {
    error ("tensorflow: 3rd argument must be an uint32 scalar value "
           "indexing the appropriate TF_DataType to be parsed to the "
           "'TF_TensorBitcastFrom' C API function.");
  }
  // Check octave_value type for pointer to target Tensor
  if (! args(3).is_uint64_type () || ! args(3).is_scalar_type ())
  {
    error ("tensorflow: 4th argument must be an uint64 "
           "scalar pointer to the target Tensor parsed to "
           "the 'TF_TensorBitcastFrom' C API function.");
  }
  // Check octave_value type for size and number of dimensions for target Tensor
  if (! args(4).is_int64_type () || ! args(4).rows () == 1)
  {
    error ("tensorflow: 5th argument must be an int64 scalar or "
           "vector defining the size of the dimensions of the target "
           "Tensor parsed to the 'TF_TensorBitcastFrom' C API function.");
  }
  if (! args(5).is_int32_type () || ! args(5).is_scalar_type ())
  {
    error ("tensorflow: 6th argument must be an int32 scalar "
           "defining the number of the dimensions of the target "
           "Tensor parsed to the 'TF_TensorBitcastFrom' C API function.");
  }
  // Check octave_value type for pointer to Status
  if (! args(6).is_uint64_type() || ! args(6).is_scalar_type())
  {
    error ("tensorflow: 7th argument must be an uint64 scalar pointer to "
           "the Status parsed to the 'TF_TensorBitcastFrom' C API function.");
  }
  // Get pointer to source Tensor
  TF_Tensor* s_tensor = (TF_Tensor*) args(1).uint64_value ();
  // Get data type for target Tensor
  TF_DataType dtype = (TF_DataType) args(2).uint_value ();
  // Get pointer to target Tensor
  TF_Tensor* t_tensor = (TF_Tensor*) args(3).uint64_value ();
  // Get size and number of dimensions for target Tensor
  int64NDArray sz = args(4).int64_array_value ();
  int num_dims = args(5).int_value ();
  OCTAVE_LOCAL_BUFFER (int64_t, dim_size, num_dims);
  for (int i = 0; i < num_dims; i++) {dim_size[i] = sz(i);}
  const int64_t* dims = dim_size;
  // Get pointer to Status
  TF_Status* status = (TF_Status*) args(6).uint64_value ();
  // Cast source Tensor to target Tensor
  TF_TensorBitcastFrom (s_tensor, dtype, t_tensor, dims, num_dims, status);
}

// TF_CAPI_EXPORT extern bool TF_TensorIsAligned(const TF_Tensor*);
octave_value OCT_TF_TensorIsAligned (OCT_ARGS)
{
  if (nrhs < 2)
  {
    error ("tensorflow: one extra argument is required "
           "for the 'TF_TensorIsAligned' C API function.");
  }
  // Check octave_value type for pointer to Tensor
  if (! args(1).is_uint64_type () || ! args(1).is_scalar_type ())
  {
    error ("tensorflow: 2nd argument must be an uint64 scalar pointer to "
           "the Tensor parsed to the 'TF_TensorIsAligned' C API function.");
  }
  // Get pointer to Tensor
  TF_Tensor* tensor = (TF_Tensor*) args(6).uint64_value ();
  // Get alignment status
  bool is_aligned = TF_TensorIsAligned (tensor);
  octave_value plhs = is_aligned;
  return plhs;
}
