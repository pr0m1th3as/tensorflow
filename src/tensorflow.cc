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

using namespace std;

DEFUN_DLD (tensorflow, args, nargout,
          "-*- texinfo -*-\n\
 @deftypefn  {tensorflow} {@var{ref} =} tensorflow (@var{TF_name}, @dots{})\n\
 @deftypefnx {tensorflow} {@var{out} =} tensorflow (@var{TF_name}, @dots{})\n\
 @deftypefnx {tensorflow} {} tensorflow (@var{TF_name}, @dots{})\n\
\n\
\n\
This is a TensorFlow binding for GNU Octave. \
\n\n\
@code{@var{ref} = tensorflow (@var{TF_name}, @dots{})} takes a character \
vector, @var{TF_name}, defining the one of the available functions in the \
tensorflow C API (including any of the Octave specific functions) listed \
below, along with any other input arguments required by the specified \
function, and returns a memory pointer, @var{ref}, of the object created by \
the specified function.  @var{ref} is always of @qcode{uint64} type. \n\n\
\
@code{@var{out} = tensorflow (@var{TF_name}, @dots{})} may also return other \
types of @qcode{octave_value} according to the specification of the called C \
API function, as defined by @var{TF_name}.  It should be noted that all memory \
pointers to objects passed as input arguments must also be of @qcode{uint64} \
types. \n\n\
\
@code{tensorflow (@var{TF_name}, @dots{})} can also be called without any \
returning arguments depending on the specification of the called function, as \
defined by @var{TF_name}.  In such cases, @code{tensorflow} is calling \
a C API function to delete an object, in which case its pointer should also be \
deleted from Octave workspace and never be reused (reusing this pointer will \
crash Octave), or the result of the operation can be retrieved through the \
pointers of the objects passed as uinput arguments. \n\n\
\
Note that @code{tensorflow} uses the following conventions throughout its API. \
\n\n\
@itemize \n\
@item @code{uint64} is used for storing memory pointers or bytesize of data. \n\n\
@item @code{int64} is used for storing size of dimensions. \n\n\
@item @code{uint32} is used to store indexing to enumerations such as Tensor \
DataType or Status Code. \n\n\
@item @code{int32} is used for storing the number of dimensions. \n\n\
@item @code{uint8} is used for storing raw data retrieved from Buffers. \n\n\
@item All vectors must be row vectors. \n\n\
@end itemize \n\n\
\
@code{tensorflow} supports the following C API and Octave specific functions. \
Extra input arguments are identified as @var{in2}, @var{in3}, @var{in3}, etc. \
\n\n\
@itemize \n\
@item @qcode{'TF_Version'} \n\
@itemize \n\
@item @var{out} : @code{char} vector containing tensorflow C API version. \n\
@end itemize \n\
@end itemize \n\
\n\
C API functions relared to the TF_Buffer classdef \n\
@itemize \n\
@item @qcode{'TF_NewBuffer'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} pointer to new Buffer. \n\
@end itemize \n\
\n\
@item @qcode{'TF_DeleteBuffer'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Buffer to be deleted. \n\
@end itemize \n\
\n\
@item @qcode{'TF_NewBufferFromString'} \n\
@itemize \n\
@item @var{in2} : vector of @code{uint8} or @code{char} to be saved into a new Buffer. \n\
@end itemize \n\
\n\
@item @qcode{'TF_GetBuffer'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Buffer to get the data from. \n\
@end itemize \n\
@itemize \n\
@item @var{out} : vector of @code{uint8} from Buffer. \n\
@end itemize \n\
\n\
@item @qcode{'TF_GetBufferToString'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Buffer to get the data from. \n\
@end itemize \n\
@itemize \n\
@item @var{out} : vector of @code{char} from Buffer. \n\
@end itemize \n\
@end itemize \n\
\n\
C API functions relared to the TF_DataType classdef \n\
@itemize \n\
@item @qcode{'TF_DataTypeName'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint32} index to DataType. \n\
@end itemize \n\
@itemize \n\
@item @var{out} : vector of @code{char} DataType name. \n\
@end itemize \n\
@item @qcode{'TF_DataTypeSize'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint32} index to DataType. \n\
@end itemize \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} bytesize of selected DataType. \n\
@end itemize \n\
@end itemize \n\
\n\
C API functions relared to the TF_Graph classdef \n\
@itemize \n\
@item @qcode{'TF_NewGraph'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} pointer to new Graph. \n\
@end itemize \n\
\n\
@item @qcode{'TF_DeleteGraph'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Graph. \n\
@end itemize \n\
\n\
@item @qcode{'TF_GraphSetTensorShape'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Graph. \n\
@item @var{in3} : scalar @code{uint64} pointer to Output. \n\
@item @var{in4} : vector @code{uint64} size of dimensions of Output in Graph. \n\
@item @var{in5} : scalar @code{int32} number of dimensions of Output in Graph. \n\
@item @var{in6} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_GraphGetTensorNumDims'} \n\
@itemize \n\
@item @var{out} : scalar @code{int32} number of dimensions of Output in Graph. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Graph. \n\
@item @var{in3} : scalar @code{uint64} pointer to Output. \n\
@item @var{in4} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_GraphGetTensorShape'} \n\
@itemize \n\
@item @var{out} : vector @code{uint64} size of dimensions of Output in Graph. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Graph. \n\
@item @var{in3} : scalar @code{uint64} pointer to Output. \n\
@item @var{in4} : scalar @code{int32} number of dimensions of Output in Graph. \n\
@item @var{in5} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_NewOperationLocked'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} pointer to new OperationDescription. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Graph. \n\
@item @var{in3} : vector @code{char} type of new Operation. \n\
@item @var{in4} : vector @code{char} name of new Operation. \n\
@end itemize \n\
\n\
@item @qcode{'TF_NewOperation'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} pointer to new OperationDescription. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Graph. \n\
@item @var{in3} : vector @code{char} type of new Operation. \n\
@item @var{in4} : vector @code{char} name of new Operation. \n\
@end itemize \n\
\n\
@item @qcode{'TF_GraphOperationByName'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} pointer to Operation. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Graph. \n\
@item @var{in3} : vector @code{char} name of Operation in Graph. \n\
@end itemize \n\
\n\
@item @qcode{'TF_GraphNextOperation'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} pointer to Operation. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Graph. \n\
@item @var{in3} : scalar @code{uint64} position of Operation in Graph. \n\
@end itemize \n\
\n\
@item @qcode{'TF_GraphToGraphDef'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Graph. \n\
@item @var{in3} : scalar @code{uint64} pointer to Buffer. \n\
@item @var{in4} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_GraphGetOpDef'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Graph. \n\
@item @var{in3} : vector @code{char} name of OperationDefinition in Graph. \n\
@item @var{in4} : scalar @code{uint64} pointer to Buffer. \n\
@item @var{in5} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_GraphVersions'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Graph. \n\
@item @var{in4} : scalar @code{uint64} pointer to Buffer. \n\
@item @var{in5} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_GraphImportGraphDefWithResults'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} pointer to ImportGraphDefResults. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Graph. \n\
@item @var{in4} : scalar @code{uint64} pointer to Buffer. \n\
@item @var{in4} : scalar @code{uint64} pointer to ImportGraphDefOptions. \n\
@item @var{in5} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_GraphImportGraphDefWithReturnOutputs'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Graph. \n\
@item @var{in3} : scalar @code{uint64} pointer to Buffer. \n\
@item @var{in4} : scalar @code{uint64} pointer to ImportGraphDefOptions. \n\
@item @var{in5} : scalar @code{uint64} pointer to Output(s). \n\
@item @var{in6} : scalar @code{int32} number of return Output(s). \n\
@item @var{in7} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_GraphImportGraphDef'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Graph. \n\
@item @var{in3} : scalar @code{uint64} pointer to Buffer. \n\
@item @var{in4} : scalar @code{uint64} pointer to ImportGraphDefOptions. \n\
@item @var{in5} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_GraphCopyFunction'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Graph. \n\
@item @var{in3} : scalar @code{uint64} pointer to Function. \n\
@item @var{in4} : scalar @code{uint64} pointer to gradient Function. \n\
@item @var{in5} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_GraphNumFunctions'} \n\
@itemize \n\
@item @var{out} : scalar @code{int32} number of Functions in Graph. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Graph. \n\
@end itemize \n\
\n\
@item @qcode{'TF_GraphGetFunctions'} \n\
@itemize \n\
@item @var{out} : vector @code{uint64} pointer(s) to Function(s) in Graph. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Graph. \n\
@item @var{in3} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_NewWhile'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} pointer to new WhileParams. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Graph. \n\
@item @var{in3} : scalar @code{uint64} pointer to Output. \n\
@item @var{in4} : scalar @code{int32} number of inputs. \n\
@item @var{in5} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_AddGradients'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Graph. \n\
@item @var{in3} : scalar @code{uint64} pointer to Output y. \n\
@item @var{in4} : scalar @code{int32} number of inputs in y. \n\
@item @var{in5} : scalar @code{uint64} pointer to Output x. \n\
@item @var{in6} : scalar @code{int32} number of inputs in x. \n\
@item @var{in7} : scalar @code{uint64} pointer to Output dx. \n\
@item @var{in8} : scalar @code{uint64} pointer to Status. \n\
@item @var{in9} : scalar @code{uint64} pointer to Output dy. \n\
@end itemize \n\
\n\
@item @qcode{'TF_AddGradientsWithPrefix'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Graph. \n\
@item @var{in3} : vector @code{char} prefix for Gradient. \n\
@item @var{in4} : scalar @code{uint64} pointer to Output y. \n\
@item @var{in5} : scalar @code{int32} number of inputs in y. \n\
@item @var{in6} : scalar @code{uint64} pointer to Output x. \n\
@item @var{in7} : scalar @code{int32} number of inputs in x. \n\
@item @var{in8} : scalar @code{uint64} pointer to Output dx. \n\
@item @var{in9} : scalar @code{uint64} pointer to Status. \n\
@item @var{in10} : scalar @code{uint64} pointer to Output dy. \n\
@end itemize \n\
@end itemize \n\
\n\
C API functions relared to the TF_OperationDescription classdef \n\
@itemize \n\
@item @qcode{'TF_SetDevice'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{char} device name. \n\
@end itemize \n\
\n\
@item @qcode{'TF_AddInput'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : scalar @code{uint64} pointer to Output input. \n\
@end itemize \n\
\n\
@item @qcode{'TF_AddInputList'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{uint64} pointers to Output inputs. \n\
@end itemize \n\
\n\
@item @qcode{'TF_AddControlInput'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : scalar @code{uint64} pointer to Operation. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetAttrString'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{char} name of attribute. \n\
@item @var{in4} : vector @code{char} value for attribute. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetAttrStringList'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{char} name of attribute. \n\
@item @var{in4} : vector @code{cellstr} values for attribute. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetAttrInt'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{char} name of attribute. \n\
@item @var{in4} : scalar @code{int64} value for attribute. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetAttrIntList'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{char} name of attribute. \n\
@item @var{in4} : vector @code{int64} values for attribute. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetAttrFloat'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{char} name of attribute. \n\
@item @var{in4} : scalar @code{single} value for attribute. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetAttrFloatList'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{char} name of attribute. \n\
@item @var{in4} : vector @code{single} values for attribute. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetAttrBool'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{char} name of attribute. \n\
@item @var{in4} : scalar @code{logical} value for attribute. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetAttrBoolList'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{char} name of attribute. \n\
@item @var{in4} : vector @code{logical} values for attribute. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetAttrType'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{char} name of attribute. \n\
@item @var{in4} : scalar @code{uint32} DataType for attribute. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetAttrTypeList'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{char} name of attribute. \n\
@item @var{in4} : vector @code{uint32} DataTypes for attribute. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetAttrPlaceholder'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{char} name of attribute. \n\
@item @var{in4} : vector @code{char} placeholder for attribute. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetAttrFuncName'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{char} name of attribute. \n\
@item @var{in4} : vector @code{char} function name for attribute. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetAttrShape'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{char} name of attribute. \n\
@item @var{in4} : vector @code{int64} the size of the dimensions of \
the attribute's shape. \n\
@item @var{in5} : scalar @code{int32} the number of the dimensions of \
the attribute's shape. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetAttrShapeList'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{char} name of attribute. \n\
@item @var{in4} : matrix @code{int64} the size of the dimensions of \
the attribute's shapes with each row corresponding to a shape.  The rows \
representing shapes with fewer dimensions are padded with zeros.\n\
@item @var{in5} : vector @code{int32} the number of the dimensions of \
the attribute's shapes with each element corresponding to a shape.  The number \
of elements must equal the number of rows of the previous input.\n\
@end itemize \n\
\n\
@item @qcode{'TF_SetAttrTensorShapeProto'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{char} name of attribute. \n\
@item @var{in4} : vector @code{uint8} binary-serialized TensorShapeProto data. \n\
@item @var{in5} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'OCT_TF_SetAttrTensorShapeProtoList'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{char} name of attribute. \n\
@item @var{in4} : vector @code{cell} a list of binary-serialized \
TensorShapeProto data, each represented as a @code{uint8} vector. \n\
@item @var{in5} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetAttrTensor'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{char} name of attribute. \n\
@item @var{in4} : scalar @code{uint64} pointer to Tensor. \n\
@item @var{in5} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetAttrTensorList'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{char} name of attribute. \n\
@item @var{in4} : vector @code{uint64} pointers to Tensors. \n\
@item @var{in5} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetAttrValueProto'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : vector @code{char} name of attribute. \n\
@item @var{in4} : vector @code{uint8} a binary serialization of an AttrValue \
protocol buffer for attribute. \n\
@item @var{in5} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_FinishOperationLocked'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} pointer to Operation. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_FinishOperation'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} pointer to Operation. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to OperationDescription. \n\
@item @var{in3} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
@end itemize \n\
\n\
C API functions relared to the TF_Status classdef \n\
@itemize \n\
@item @qcode{'TF_NewStatus'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} pointer to new Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_DeleteStatus'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetStatus'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Status. \n\
@item @var{in3} : scalar @code{uint32} Code to Status. \n\
@item @var{in4} : vector @code{char} message to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetPayload'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Status. \n\
@item @var{in3} : vector @code{char} 'key' as payload to Status. \n\
@item @var{in4} : vector @code{char} 'value' as payload to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetStatus'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Status. \n\
@item @var{in3} : scalar @code{int32} I/O error code. \n\
@item @var{in4} : vector @code{char} message for I/O error code. \n\
@end itemize \n\
\n\
@item @qcode{'TF_GetCode'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint32} Code from Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_Message'} \n\
@itemize \n\
@item @var{out} : vector @code{char} message from Status. \n\
@end itemize \n\
@end itemize \n\
\n\
C API functions relared to the TF_TString classdef \n\
@itemize \n\
@item @qcode{'TF_NewTString'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} pointer to new TString. \n\
@end itemize \n\
\n\
@item @qcode{'TF_LoadTString'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} pointer to new TString. \n\
@end itemize \n\
@itemize \n\
@item @var{in2}: vector @code{char} character vector to new TString. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SaveTString'} \n\
@itemize \n\
@item @var{out} : vector @code{char} character vector from TString. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to new TString. \n\
@end itemize \n\
\n\
@item @qcode{'TF_StringInit'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to TString. \n\
@end itemize \n\
\n\
@item @qcode{'TF_StringCopy'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to destination TString. \n\
@item @var{in3} : vector @code{char} character vector as source string. \n\
@item @var{in4} : scalar @code{uint64} length of source string. \n\
@end itemize \n\
\n\
@item @qcode{'TF_StringAssignView'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to destination TString. \n\
@item @var{in3} : vector @code{char} character vector as source string. \n\
@item @var{in4} : scalar @code{uint64} length of source string. \n\
@end itemize \n\
\n\
@item @qcode{'TF_StringGetDataPointer'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} pointer to TString data. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to TString. \n\
@end itemize \n\
\n\
@item @qcode{'TF_StringGetType'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint32} type of TString. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to TString. \n\
@end itemize \n\
\n\
@item @qcode{'TF_StringGetSize'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} size of TString. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to TString. \n\
@end itemize \n\
\n\
@item @qcode{'TF_StringGetCapacity'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} capacity of TString. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to TString. \n\
@end itemize \n\
\n\
@item @qcode{'TF_StringDealloc'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to TString. \n\
@end itemize \n\
@end itemize \n\
\n\
C API functions relared to the TF_Tensor classdef \n\
@itemize \n\
@item @qcode{'TF_LoadTensor'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} pointer to new Tensor. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : any non-empty value of supported DataType. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SaveTensor'} \n\
@itemize \n\
@item @var{out} : any value of supported DataType. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Tensor. \n\
@end itemize \n\
\n\
@item @qcode{'TF_NewTensor'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} pointer to new Tensor. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint32} DataType code for new Tensor. \n\
@item @var{in3} : scalar @code{int64} size of dimensions for new Tensor. \n\
@item @var{in4} : scalar @code{int32} number of dimensions for new Tensor. \n\
@item @var{in5} : scalar @code{uint64} pointer to data for new Tensor. \n\
@item @var{in5} : scalar @code{uint64} bytesize of data for new Tensor. \n\
@end itemize \n\
\n\
@item @qcode{'TF_AllocateTensor'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} pointer to new Tensor. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint32} DataType code for new Tensor. \n\
@item @var{in3} : scalar @code{int64} size of dimensions for new Tensor. \n\
@item @var{in4} : scalar @code{int32} number of dimensions for new Tensor. \n\
@item @var{in5} : scalar @code{uint64} bytesize of data for new Tensor. \n\
@end itemize \n\
\n\
@item @qcode{'TF_TensorMaybeMove'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} pointer to maybe moved Tensor. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Tensor. \n\
@end itemize \n\
\n\
@item @qcode{'TF_DeleteTensor'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Tensor. \n\
@end itemize \n\
\n\
@item @qcode{'TF_TensorType'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint32} DataType code of Tensor. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Tensor. \n\
@end itemize \n\
\n\
@item @qcode{'TF_SetShape'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Tensor. \n\
@item @var{in3} : scalar @code{int64} size of dimensions for new Tensor. \n\
@item @var{in4} : scalar @code{int32} number of dimensions for new Tensor. \n\
@end itemize \n\
\n\
@item @qcode{'TF_NumDims'} \n\
@itemize \n\
@item @var{out} : scalar @code{int32} number of dimensions of Tensor. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Tensor. \n\
@end itemize \n\
\n\
@item @qcode{'TF_Dim'} \n\
@itemize \n\
@item @var{out} : vector @code{int64} size of indexed dimension of Tensor. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Tensor. \n\
@item @var{in3} : scalar @code{int32} dimension index. \n\
@end itemize \n\
\n\
@item @qcode{'TF_TensorByteSize'} \n\
@itemize \n\
@item @var{out} : vector @code{uint64} bytesize of Tensor. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Tensor. \n\
@end itemize \n\
\n\
@item @qcode{'TF_TensorData'} \n\
@itemize \n\
@item @var{out} : scalar @code{uint64} pointer to data from Tensor. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Tensor. \n\
@end itemize \n\
\n\
@item @qcode{'TF_TensorFromProto'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Buffer. \n\
@item @var{in2} : scalar @code{uint64} pointer to Tensor. \n\
@item @var{in2} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_TensorElementCount'} \n\
@itemize \n\
@item @var{out} : scalar @code{int64} number of elements in Tensor. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Tensor. \n\
@end itemize \n\
\n\
@item @qcode{'TF_TensorBitcastFrom'} \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to source Tensor. \n\
@item @var{in3} : scalar @code{uint32} DataType code for target Tensor. \n\
@item @var{in4} : scalar @code{uint64} pointer to target Tensor. \n\
@item @var{in5} : scalar @code{int64} size of dimensions for new Tensor. \n\
@item @var{in6} : scalar @code{int32} number of dimensions for new Tensor. \n\
@item @var{in7} : scalar @code{uint64} pointer to Status. \n\
@end itemize \n\
\n\
@item @qcode{'TF_TensorIsAligned'} \n\
@itemize \n\
@item @var{out} : scalar @code{bool} value for Tensor alignment. \n\
@end itemize \n\
@itemize \n\
@item @var{in2} : scalar @code{uint64} pointer to Tensor. \n\
@end itemize \n\
@end itemize \n\
\n\
@end deftypefn")
{
  int nlhs = nargout;
	int nrhs = args.length();
	octave_value plhs;
  if (nrhs == 0)
  {
    printf ("tensorflow: This is a TensorFlow binding for GNU Octave.\n");
    return plhs;
  }
  if (! args(0).is_string())
  {
    error ("tensorflow: first argument must be a character "
           "vector referencing a C API function.");
  }
  string c_api = args(0).string_value();

  // Select C_API handler
  // ---------------------------------------------------------------------------
  if (c_api == "TF_Version")
  {
    const char* out = TF_Version ();
    plhs = out;
  }
  // ---------------------------------------------------------------------------
  // C API functions referenced by the TF_Buffer classdef
  // ---------------------------------------------------------------------------
  else if (c_api == "TF_NewBuffer")
  {
    plhs = OCT_TF_NewBuffer (nrhs, args);
  }
  else if (c_api == "TF_DeleteBuffer")
  {
    OCT_TF_DeleteBuffer (nrhs, args);
  }
  else if (c_api == "TF_NewBufferFromString")
  {
    plhs = OCT_TF_NewBufferFromString (nrhs, args);
  }
  else if (c_api == "TF_GetBuffer")
  {
    plhs = OCT_TF_GetBuffer (nrhs, args);
  }
  else if (c_api == "TF_GetBufferToString")        // OCTAVE specific
  {
    plhs = OCT_TF_GetBufferToString (nrhs, args);
  }
  // ---------------------------------------------------------------------------
  // C API functions referenced by the TF_DataType classdef
  // ---------------------------------------------------------------------------
  else if (c_api == "TF_DataTypeName")             // OCTAVE specific
  {
    plhs = OCT_TF_DataTypeName (nrhs, args);
  }
  else if (c_api == "TF_DataTypeSize")
  {
    plhs = OCT_TF_DataTypeSize (nrhs, args);
  }
  // ---------------------------------------------------------------------------
  // C API functions referenced by the TF_Graph classdef
  // ---------------------------------------------------------------------------
  else if (c_api == "TF_NewGraph")
  {
    plhs = OCT_TF_NewGraph ();
  }
  else if (c_api == "TF_DeleteGraph")
  {
    OCT_TF_DeleteGraph (nrhs, args);
  }
  else if (c_api == "TF_GraphSetTensorShape")
  {
    OCT_TF_GraphSetTensorShape (nrhs, args);
  }
  else if (c_api == "TF_GraphGetTensorNumDims")
  {
    plhs = OCT_TF_GraphGetTensorNumDims (nrhs, args);
  }
  else if (c_api == "TF_GraphGetTensorShape")
  {
    plhs = OCT_TF_GraphGetTensorShape (nrhs, args);
  }
  else if (c_api == "TF_NewOperationLocked")
  {
    plhs = OCT_TF_NewOperationLocked (nrhs, args);
  }
  else if (c_api == "TF_NewOperation")
  {
    plhs = OCT_TF_NewOperation (nrhs, args);
  }
  else if (c_api == "TF_GraphOperationByName")
  {
    plhs = OCT_TF_GraphOperationByName (nrhs, args);
  }
  else if (c_api == "TF_GraphNextOperation")
  {
    plhs = OCT_TF_GraphNextOperation (nrhs, args);
  }
  else if (c_api == "TF_GraphToGraphDef")
  {
    OCT_TF_GraphToGraphDef (nrhs, args);
  }
  else if (c_api == "TF_GraphGetOpDef")
  {
    OCT_TF_GraphGetOpDef (nrhs, args);
  }
  else if (c_api == "TF_GraphVersions")
  {
    OCT_TF_GraphVersions (nrhs, args);
  }
  else if (c_api == "TF_GraphImportGraphDefWithResults")
  {
    plhs = OCT_TF_GraphImportGraphDefWithResults (nrhs, args);
  }
  else if (c_api == "TF_GraphImportGraphDefWithReturnOutputs")
  {
    OCT_TF_GraphImportGraphDefWithReturnOutputs (nrhs, args);
  }
  else if (c_api == "TF_GraphImportGraphDef")
  {
    OCT_TF_GraphImportGraphDef (nrhs, args);
  }
  else if (c_api == "TF_GraphCopyFunction")
  {
    OCT_TF_GraphCopyFunction (nrhs, args);
  }
  else if (c_api == "TF_GraphNumFunctions")
  {
    plhs = OCT_TF_GraphNumFunctions (nrhs, args);
  }
  else if (c_api == "TF_GraphGetFunctions")
  {
    plhs = OCT_TF_GraphGetFunctions (nrhs, args);
  }
  else if (c_api == "TF_NewWhile")
  {
    plhs = OCT_TF_NewWhile (nrhs, args);
  }
  else if (c_api == "TF_AddGradients")
  {
    OCT_TF_AddGradients (nrhs, args);
  }
  else if (c_api == "TF_AddGradientsWithPrefix")
  {
    OCT_TF_AddGradientsWithPrefix (nrhs, args);
  }
  else if (c_api == "TF_GraphToFunction")
  {
    plhs = OCT_TF_GraphToFunction (nrhs, args);
  }
  else if (c_api == "TF_GraphToFunctionWithControlOutputs")
  {
    plhs = OCT_TF_GraphToFunctionWithControlOutputs (nrhs, args);
  }
  // ---------------------------------------------------------------------------
  // C API functions referenced by the TF_OperationDescription classdef
  // ---------------------------------------------------------------------------
  else if (c_api == "TF_SetDevice")
  {
    OCT_TF_SetDevice (nrhs, args);
  }
  else if (c_api == "TF_AddInput")
  {
    OCT_TF_AddInput (nrhs, args);
  }
  else if (c_api == "TF_AddInputList")
  {
    OCT_TF_AddInputList (nrhs, args);
  }
  else if (c_api == "TF_AddControlInput")
  {
    OCT_TF_AddControlInput (nrhs, args);
  }
  else if (c_api == "TF_SetAttrString")
  {
    OCT_TF_SetAttrString (nrhs, args);
  }
  else if (c_api == "TF_SetAttrStringList")
  {
    OCT_TF_SetAttrStringList (nrhs, args);
  }
  else if (c_api == "TF_SetAttrInt")
  {
    OCT_TF_SetAttrInt (nrhs, args);
  }
  else if (c_api == "TF_SetAttrIntList")
  {
    OCT_TF_SetAttrIntList (nrhs, args);
  }
  else if (c_api == "TF_SetAttrFloat")
  {
    OCT_TF_SetAttrFloat (nrhs, args);
  }
  else if (c_api == "TF_SetAttrFloatList")
  {
    OCT_TF_SetAttrFloatList (nrhs, args);
  }
  else if (c_api == "TF_SetAttrBool")
  {
    OCT_TF_SetAttrBool (nrhs, args);
  }
  else if (c_api == "TF_SetAttrBoolList")
  {
    OCT_TF_SetAttrBoolList (nrhs, args);
  }
  else if (c_api == "TF_SetAttrType")
  {
    OCT_TF_SetAttrType (nrhs, args);
  }
  else if (c_api == "TF_SetAttrTypeList")
  {
    OCT_TF_SetAttrTypeList (nrhs, args);
  }
  else if (c_api == "TF_SetAttrPlaceholder")
  {
    OCT_TF_SetAttrPlaceholder (nrhs, args);
  }
  else if (c_api == "TF_SetAttrFuncName")
  {
    OCT_TF_SetAttrFuncName (nrhs, args);
  }
  else if (c_api == "TF_SetAttrShape")
  {
    OCT_TF_SetAttrShape (nrhs, args);
  }
  else if (c_api == "TF_SetAttrShapeList")
  {
    OCT_TF_SetAttrShapeList (nrhs, args);
  }
  else if (c_api == "TF_SetAttrTensorShapeProto")
  {
    OCT_TF_SetAttrTensorShapeProto (nrhs, args);
  }
  else if (c_api == "TF_SetAttrTensorShapeProtoList")
  {
    OCT_TF_SetAttrTensorShapeProtoList (nrhs, args);
  }
  else if (c_api == "TF_SetAttrTensor")
  {
    OCT_TF_SetAttrTensor (nrhs, args);
  }
  else if (c_api == "TF_SetAttrTensorList")
  {
    OCT_TF_SetAttrTensorList (nrhs, args);
  }
  else if (c_api == "TF_SetAttrValueProto")
  {
    OCT_TF_SetAttrValueProto (nrhs, args);
  }
  else if (c_api == "TF_FinishOperationLocked")
  {
    plhs = OCT_TF_FinishOperationLocked (nrhs, args);
  }
  else if (c_api == "TF_FinishOperation")
  {
    plhs = OCT_TF_FinishOperation (nrhs, args);
  }
  // ---------------------------------------------------------------------------
  // C API functions referenced by the TF_Status classdef
  // ---------------------------------------------------------------------------
  else if (c_api == "TF_NewStatus")
  {
    plhs = OCT_TF_NewStatus ();
  }
  else if (c_api == "TF_DeleteStatus")
  {
    OCT_TF_DeleteStatus (nrhs, args);
  }
  else if (c_api == "TF_SetStatus")
  {
    OCT_TF_SetStatus (nrhs, args);
  }
  else if (c_api == "TF_SetPayload")
  {
    OCT_TF_SetPayload (nrhs, args);
  }
  else if (c_api == "TF_ForEachPayload")
  {
    OCT_TF_ForEachPayload (nrhs, args);
  }
  else if (c_api == "TF_SetStatusFromIOError")
  {
    OCT_TF_SetStatusFromIOError (nrhs, args);
  }
  else if (c_api == "TF_GetCode")
  {
    plhs = OCT_TF_GetCode (nrhs, args);
  }
  else if (c_api == "TF_Message")
  {
    plhs = OCT_TF_Message (nrhs, args);
  }
  // ---------------------------------------------------------------------------
  // C API functions referenced by the TF_String classdef
  // ---------------------------------------------------------------------------
  else if (c_api == "TF_NewTString")               // OCTAVE specific
  {
    plhs = OCT_TF_NewTString ();
  }
  else if (c_api == "TF_LoadTString")              // OCTAVE specific
  {
    plhs = OCT_TF_LoadTString (nrhs, args);
  }
  else if (c_api == "TF_SaveTString")              // OCTAVE specific
  {
    plhs = OCT_TF_SaveTString (nrhs, args);
  }
  else if (c_api == "TF_StringInit")
  {
    OCT_TF_StringInit (nrhs, args);
  }
  else if (c_api == "TF_StringCopy")
  {
    OCT_TF_StringCopy (nrhs, args);
  }
  else if (c_api == "TF_StringAssignView")
  {
    OCT_TF_StringAssignView (nrhs, args);
  }
  else if (c_api == "TF_StringGetDataPointer")
  {
    plhs = OCT_TF_StringGetDataPointer (nrhs, args);
  }
  else if (c_api == "TF_StringGetType")
  {
    plhs = OCT_TF_StringGetType (nrhs, args);
  }
  else if (c_api == "TF_StringGetSize")
  {
    plhs = OCT_TF_StringGetSize (nrhs, args);
  }
  else if (c_api == "TF_StringGetCapacity")
  {
    plhs = OCT_TF_StringGetCapacity (nrhs, args);
  }
  else if (c_api == "TF_StringDealloc")
  {
    OCT_TF_StringDealloc (nrhs, args);
  }
  // ---------------------------------------------------------------------------
  // C API functions referenced by the TF_Tensor classdef
  // ---------------------------------------------------------------------------
  else if (c_api == "TF_LoadTensor")               // OCTAVE specific
  {
    plhs = OCT_TF_LoadTensor (nrhs, args);
  }
  else if (c_api == "TF_SaveTensor")               // OCTAVE specific
  {
    plhs = OCT_TF_SaveTensor (nrhs, args);
  }
  else if (c_api == "TF_NewTensor")
  {
    plhs = OCT_TF_NewTensor (nrhs, args);
  }
  else if (c_api == "TF_AllocateTensor")
  {
    plhs = OCT_TF_AllocateTensor (nrhs, args);
  }
  else if (c_api == "TF_TensorMaybeMove")
  {
    plhs = OCT_TF_TensorMaybeMove (nrhs, args);
  }
  else if (c_api == "TF_DeleteTensor")
  {
    OCT_TF_DeleteTensor (nrhs, args);
  }
  else if (c_api == "TF_TensorType")
  {
    plhs = OCT_TF_TensorType (nrhs, args);
  }
  else if (c_api == "TF_SetShape")
  {
    OCT_TF_SetShape (nrhs, args);
  }
  else if (c_api == "TF_NumDims")
  {
    plhs = OCT_TF_NumDims (nrhs, args);
  }
  else if (c_api == "TF_Dim")
  {
    plhs = OCT_TF_Dim (nrhs, args);
  }
  else if (c_api == "TF_TensorByteSize")
  {
    plhs = OCT_TF_TensorByteSize (nrhs, args);
  }
  else if (c_api == "TF_TensorData")
  {
    plhs = OCT_TF_TensorData (nrhs, args);
  }
  else if (c_api == "TF_TensorFromProto")
  {
    OCT_TF_TensorFromProto (nrhs, args);
  }
  else if (c_api == "TF_TensorElementCount")
  {
    plhs = OCT_TF_TensorElementCount (nrhs, args);
  }
  else if (c_api == "TF_TensorBitcastFrom")
  {
    OCT_TF_TensorBitcastFrom (nrhs, args);
  }
  else if (c_api == "TF_TensorIsAligned")
  {
    plhs = OCT_TF_TensorIsAligned (nrhs, args);
  }
  // ---------------------------------------------------------------------------
  else
  {
    error ("tensorflow: unrecognized reference to C API function.");
  }
  return plhs;
}

/*
%!error <tensorflow: first argument must be a character vector referencing a C API function.> ...
%! tensorflow (5);
%!error <tensorflow: unrecognized reference to C API function.> tensorflow ('');
%!test
%! assert (tensorflow ('TF_Version'), "2.15.0")
  ## ---------------------------------------------------------------------------
  ## C API functions referenced by the TF_Buffer classdef
  ## ---------------------------------------------------------------------------
%!error <tensorflow: one extra argument is required for the 'TF_DeleteBuffer' C API function.> ...
%! tensorflow ('TF_DeleteBuffer');
%!error <tensorflow: 2nd argument must be uint64 scalar pointer to the Buffer parsed to the 'TF_DeleteBuffer' C API function.> ...
%! tensorflow ('TF_DeleteBuffer', 1);

%!error <tensorflow: one extra argument is required for the 'TF_NewBufferFromString' C API function.> ...
%! tensorflow ('TF_NewBufferFromString');
%!error <tensorflow: 2nd argument must be either a character or a uint8 vector to be parsed to the 'TF_NewBufferFromString' C API function.> ...
%! tensorflow ('TF_NewBufferFromString', 1);

%!error <tensorflow: one extra argument is required for the 'TF_GetBuffer' C API function.> ...
%! tensorflow ('TF_GetBuffer');
%!error <tensorflow: 2nd argument must be uint64 scalar pointer to the Buffer parsed to the 'TF_GetBuffer' C API function.> ...
%! tensorflow ('TF_GetBuffer', 1);

%!error <tensorflow: one extra argument is required for the 'TF_GetBufferToString' C API function.> ...
%! tensorflow ('TF_GetBufferToString');
%!error <tensorflow: 2nd argument must be uint64 scalar pointer to the Buffer parsed to the 'TF_GetBufferToString' C API function.> ...
%! tensorflow ('TF_GetBufferToString', 1);

%!test
%! ref = tensorflow ('TF_NewBuffer');
%! assert (class (ref), "uint64");
%! tensorflow ('TF_DeleteBuffer', ref);

%!test
%! ref = tensorflow ('TF_NewBufferFromString', 'This');
%! assert (class (ref), "uint64");
%! out = tensorflow ('TF_GetBufferToString', ref);
%! assert (class (out), "char");
%! assert (out, 'This');
%! out = tensorflow ('TF_GetBuffer', ref);
%! assert (class (out), "uint8");
%! assert (out, uint8 ([84, 104, 105, 115]));
%! tensorflow ('TF_DeleteBuffer', ref);
%!test
%! ref = tensorflow ('TF_NewBufferFromString', uint8 ([1:5]));
%! assert (class (ref), "uint64");
%! out = tensorflow ('TF_GetBufferToString', ref);
%! assert (class (out), "char");
%! out = tensorflow ('TF_GetBuffer', ref);
%! assert (class (out), "uint8");
%! assert (out, uint8 ([1:5]));
%! tensorflow ('TF_DeleteBuffer', ref);

  ## ---------------------------------------------------------------------------
  ## C API functions referenced by the TF_DataType classdef
  ## ---------------------------------------------------------------------------
%!error <tensorflow: one extra argument is required for the 'TF_DataTypeName' OCTAVE function.> ...
%! tensorflow ('TF_DataTypeName');
%!error <tensorflow: 2nd argument must be an uint32 scalar indexing the appropriate TF_DataType to be parsed to the 'TF_DataTypeName' OCTAVE function.> ...
%! tensorflow ('TF_DataTypeName', 1);
%!test
%! assert (tensorflow ('TF_DataTypeName', uint32 (1)), "TF_FLOAT");
%! assert (tensorflow ('TF_DataTypeName', uint32 (2)), "TF_DOUBLE");
%! assert (tensorflow ('TF_DataTypeName', uint32 (3)), "TF_INT32");
%! assert (tensorflow ('TF_DataTypeName', uint32 (4)), "TF_UINT8");
%! assert (tensorflow ('TF_DataTypeName', uint32 (5)), "TF_INT16");
%! assert (tensorflow ('TF_DataTypeName', uint32 (6)), "TF_INT8");
%! assert (tensorflow ('TF_DataTypeName', uint32 (7)), "TF_STRING");
%! assert (tensorflow ('TF_DataTypeName', uint32 (8)), "TF_COMPLEX64");
%! assert (tensorflow ('TF_DataTypeName', uint32 (9)), "TF_INT64");
%! assert (tensorflow ('TF_DataTypeName', uint32 (10)), "TF_BOOL");
%! assert (tensorflow ('TF_DataTypeName', uint32 (11)), "TF_QINT8");
%! assert (tensorflow ('TF_DataTypeName', uint32 (12)), "TF_QUINT8");
%! assert (tensorflow ('TF_DataTypeName', uint32 (13)), "TF_QINT32");
%! assert (tensorflow ('TF_DataTypeName', uint32 (14)), "TF_BFLOAT16");
%! assert (tensorflow ('TF_DataTypeName', uint32 (15)), "TF_QINT16");
%! assert (tensorflow ('TF_DataTypeName', uint32 (16)), "TF_QUINT16");
%! assert (tensorflow ('TF_DataTypeName', uint32 (17)), "TF_UINT16");
%! assert (tensorflow ('TF_DataTypeName', uint32 (18)), "TF_COMPLEX128");
%! assert (tensorflow ('TF_DataTypeName', uint32 (19)), "TF_HALF");
%! assert (tensorflow ('TF_DataTypeName', uint32 (20)), "TF_RESOURCE");
%! assert (tensorflow ('TF_DataTypeName', uint32 (21)), "TF_VARIANT");
%! assert (tensorflow ('TF_DataTypeName', uint32 (22)), "TF_UINT32");
%! assert (tensorflow ('TF_DataTypeName', uint32 (23)), "TF_UINT64");
%! assert (tensorflow ('TF_DataTypeName', uint32 (24)), "TF_FLOAT8_E5M2");
%! assert (tensorflow ('TF_DataTypeName', uint32 (25)), "TF_FLOAT8_E4M3FN");
%! assert (tensorflow ('TF_DataTypeName', uint32 (29)), "TF_INT4");
%! assert (tensorflow ('TF_DataTypeName', uint32 (30)), "TF_UINT4");

%!error <tensorflow: one extra argument is required for the 'TF_DataTypeSize' C API function.> ...
%! tensorflow ('TF_DataTypeSize');
%!error <tensorflow: 2nd argument must be an uint32 scalar indexing the appropriate TF_DataType to be parsed to the 'TF_DataTypeSize' C API function.> ...
%! tensorflow ('TF_DataTypeSize', 1);
%!test
%! assert (tensorflow ('TF_DataTypeSize', uint32 (1)), uint64 (4));   ## TF_FLOAT
%! assert (tensorflow ('TF_DataTypeSize', uint32 (2)), uint64 (8));   ## TF_DOUBLE
%! assert (tensorflow ('TF_DataTypeSize', uint32 (3)), uint64 (4));   ## TF_INT32
%! assert (tensorflow ('TF_DataTypeSize', uint32 (4)), uint64 (1));   ## TF_UINT8
%! assert (tensorflow ('TF_DataTypeSize', uint32 (5)), uint64 (2));   ## TF_INT16
%! assert (tensorflow ('TF_DataTypeSize', uint32 (6)), uint64 (1));   ## TF_INT8
%! assert (tensorflow ('TF_DataTypeSize', uint32 (7)), uint64 (0));   ## TF_STRING
%! assert (tensorflow ('TF_DataTypeSize', uint32 (8)), uint64 (8));   ## TF_COMPLEX64
%! assert (tensorflow ('TF_DataTypeSize', uint32 (9)), uint64 (8));   ## TF_INT64
%! assert (tensorflow ('TF_DataTypeSize', uint32 (10)), uint64 (1));  ## TF_BOOL
%! assert (tensorflow ('TF_DataTypeSize', uint32 (17)), uint64 (2));  ## TF_UINT16
%! assert (tensorflow ('TF_DataTypeSize', uint32 (18)), uint64 (16)); ## TF_COMPLEX128
%! assert (tensorflow ('TF_DataTypeSize', uint32 (22)), uint64 (4));  ## TF_UINT32
%! assert (tensorflow ('TF_DataTypeSize', uint32 (23)), uint64 (8));  ## TF_UINT64

  ## ---------------------------------------------------------------------------
  ## C API functions referenced by the TF_Graph classdef
  ## ---------------------------------------------------------------------------
%!error <tensorflow: one extra argument is required for the 'TF_DeleteGraph' C API function.> ...
%! tensorflow ('TF_DeleteGraph');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Graph parsed to the 'TF_DeleteGraph' C API function.> ...
%! tensorflow ('TF_DeleteGraph', 1);

%!error <tensorflow: five extra argumenta are required for the 'TF_GraphSetTensorShape' C API function.> ...
%! tensorflow ('TF_GraphSetTensorShape');
%!error <tensorflow: five extra argumenta are required for the 'TF_GraphSetTensorShape' C API function.> ...
%! tensorflow ('TF_GraphSetTensorShape', 1);
%!error <tensorflow: five extra argumenta are required for the 'TF_GraphSetTensorShape' C API function.> ...
%! tensorflow ('TF_GraphSetTensorShape', 1, 2);
%!error <tensorflow: five extra argumenta are required for the 'TF_GraphSetTensorShape' C API function.> ...
%! tensorflow ('TF_GraphSetTensorShape', 1, 2, 3);
%!error <tensorflow: five extra argumenta are required for the 'TF_GraphSetTensorShape' C API function.> ...
%! tensorflow ('TF_GraphSetTensorShape', 1, 2, 3, 4);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Graph parsed to the 'TF_GraphSetTensorShape' C API function.> ...
%! tensorflow ('TF_GraphSetTensorShape', 1, 2, 3, 4, 5);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the Output parsed to the 'TF_GraphSetTensorShape' C API function.> ...
%! tensorflow ('TF_GraphSetTensorShape', uint64 (1), 2, 3, 4, 5);
%!error <tensorflow: 4th argument must be an int64 scalar or vector defining the size of the dimensions of the Tensor to be parsed to the 'TF_GraphSetTensorShape' C API function.> ...
%! tensorflow ('TF_GraphSetTensorShape', uint64 (1), uint64 (2), 3, 4, 5);
%!error <tensorflow: 5th argument must be an int32 scalar defining the number of the dimensions of the Tensor to be parsed to the 'TF_GraphSetTensorShape' C API function.> ...
%! tensorflow ('TF_GraphSetTensorShape', uint64 (1), uint64 (2), int64 (3), 4, 5);
%!error <tensorflow: 6th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_GraphSetTensorShape' C API function.> ...
%! tensorflow ('TF_GraphSetTensorShape', uint64 (1), uint64 (2), int64 (3), int32 (4), 5);

%!error <tensorflow: three extra arguments are required for the 'TF_GraphGetTensorNumDims' C API function.> ...
%! tensorflow ('TF_GraphGetTensorNumDims');
%!error <tensorflow: three extra arguments are required for the 'TF_GraphGetTensorNumDims' C API function.> ...
%! tensorflow ('TF_GraphGetTensorNumDims', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_GraphGetTensorNumDims' C API function.> ...
%! tensorflow ('TF_GraphGetTensorNumDims', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Graph parsed to the 'TF_GraphGetTensorNumDims' C API function.> ...
%! tensorflow ('TF_GraphGetTensorNumDims', 1, 2, 3);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the Output parsed to the 'TF_GraphGetTensorNumDims' C API function.> ...
%! tensorflow ('TF_GraphGetTensorNumDims', uint64 (1), 2, 3);
%!error <tensorflow: 4th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_GraphGetTensorNumDims' C API function.> ...
%! tensorflow ('TF_GraphGetTensorNumDims', uint64 (1), uint64 (2), 3);

%!error <tensorflow: four extra arguments are required for the 'TF_GraphGetTensorShape' C API function.> ...
%! tensorflow ('TF_GraphGetTensorShape');
%!error <tensorflow: four extra arguments are required for the 'TF_GraphGetTensorShape' C API function.> ...
%! tensorflow ('TF_GraphGetTensorShape', 1);
%!error <tensorflow: four extra arguments are required for the 'TF_GraphGetTensorShape' C API function.> ...
%! tensorflow ('TF_GraphGetTensorShape', 1, 2);
%!error <tensorflow: four extra arguments are required for the 'TF_GraphGetTensorShape' C API function.> ...
%! tensorflow ('TF_GraphGetTensorShape', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Graph parsed to the 'TF_GraphGetTensorShape' C API function.> ...
%! tensorflow ('TF_GraphGetTensorShape', 1, 2, 3, 4);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the Output parsed to the 'TF_GraphGetTensorShape' C API function.> ...
%! tensorflow ('TF_GraphGetTensorShape', uint64 (1), 2, 3, 4);
%!error <tensorflow: 4th argument must be an int32 scalar defining the number of the dimensions of the Tensor referenced by the Output in Graph to be parsed to the 'TF_GraphGetTensorShape' C API function.> ...
%! tensorflow ('TF_GraphGetTensorShape', uint64 (1), uint64 (2), 3, 4);
%!error <tensorflow: 5th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_GraphGetTensorShape' C API function.> ...
%! tensorflow ('TF_GraphGetTensorShape', uint64 (1), uint64 (2), int32 (3), 4);

%!error <tensorflow: three extra arguments are required for the 'TF_NewOperationLocked' C API function.> ...
%! tensorflow ('TF_NewOperationLocked');
%!error <tensorflow: three extra arguments are required for the 'TF_NewOperationLocked' C API function.> ...
%! tensorflow ('TF_NewOperationLocked', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_NewOperationLocked' C API function.> ...
%! tensorflow ('TF_NewOperationLocked', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Graph parsed to the 'TF_NewOperationLocked' C API function.> ...
%! tensorflow ('TF_NewOperationLocked', 1, 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the operation type parsed to the 'TF_NewOperationLocked' C API function.> ...
%! tensorflow ('TF_NewOperationLocked', uint64 (1), 2, 3);
%!error <tensorflow: 4th argument must be a character vector defining the operation name parsed to the 'TF_NewOperationLocked' C API function.> ...
%! tensorflow ('TF_NewOperationLocked', uint64 (1), "op_type", 3);

%!error <tensorflow: three extra arguments are required for the 'TF_NewOperation' C API function.> ...
%! tensorflow ('TF_NewOperation');
%!error <tensorflow: three extra arguments are required for the 'TF_NewOperation' C API function.> ...
%! tensorflow ('TF_NewOperation', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_NewOperation' C API function.> ...
%! tensorflow ('TF_NewOperation', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Graph parsed to the 'TF_NewOperation' C API function.> ...
%! tensorflow ('TF_NewOperation', 1, 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the operation type parsed to the 'TF_NewOperation' C API function.> ...
%! tensorflow ('TF_NewOperation', uint64 (1), 2, 3);
%!error <tensorflow: 4th argument must be a character vector defining the operation name parsed to the 'TF_NewOperation' C API function.> ...
%! tensorflow ('TF_NewOperation', uint64 (1), "op_type", 3);

%!error <tensorflow: two extra arguments are required for the 'TF_GraphOperationByName' C API function.> ...
%! tensorflow ('TF_GraphOperationByName');
%!error <tensorflow: two extra arguments are required for the 'TF_GraphOperationByName' C API function.> ...
%! tensorflow ('TF_GraphOperationByName', 1);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Graph parsed to the 'TF_GraphOperationByName' C API function.> ...
%! tensorflow ('TF_GraphOperationByName', 1, 2);
%!error <tensorflow: 3rd argument must be a character vector defining the operation name parsed to the 'TF_GraphOperationByName' C API function.> ...
%! tensorflow ('TF_GraphOperationByName', uint64 (1), 2);

%!error <tensorflow: two extra arguments are required for the 'TF_GraphNextOperation' C API function.> ...
%! tensorflow ('TF_GraphNextOperation');
%!error <tensorflow: two extra arguments are required for the 'TF_GraphNextOperation' C API function.> ...
%! tensorflow ('TF_GraphNextOperation', 1);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Graph parsed to the 'TF_GraphNextOperation' C API function.> ...
%! tensorflow ('TF_GraphNextOperation', 1, 2);
%!error <tensorflow: 3rd argument must be an uint64 scalar value defining the position of operation parsed to the 'TF_GraphNextOperation' C API function.> ...
%! tensorflow ('TF_GraphNextOperation', uint64 (1), 2);

%!error <tensorflow: three extra arguments are required for the 'TF_GraphToGraphDef' C API function.> ...
%! tensorflow ('TF_GraphToGraphDef');
%!error <tensorflow: three extra arguments are required for the 'TF_GraphToGraphDef' C API function.> ...
%! tensorflow ('TF_GraphToGraphDef', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_GraphToGraphDef' C API function.> ...
%! tensorflow ('TF_GraphToGraphDef', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Graph parsed to the 'TF_GraphToGraphDef' C API function.> ...
%! tensorflow ('TF_GraphToGraphDef', 1, 2, 3);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the Buffer parsed to the 'TF_GraphToGraphDef' C API function.> ...
%! tensorflow ('TF_GraphToGraphDef', uint64 (1), 2, 3);
%!error <tensorflow: 4th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_GraphToGraphDef' C API function.> ...
%! tensorflow ('TF_GraphToGraphDef', uint64 (1), uint64 (2), 3);

%!error <tensorflow: four extra arguments are required for the 'TF_GraphGetOpDef' C API function.> ...
%! tensorflow ('TF_GraphGetOpDef');
%!error <tensorflow: four extra arguments are required for the 'TF_GraphGetOpDef' C API function.> ...
%! tensorflow ('TF_GraphGetOpDef', 1);
%!error <tensorflow: four extra arguments are required for the 'TF_GraphGetOpDef' C API function.> ...
%! tensorflow ('TF_GraphGetOpDef', 1, 2);
%!error <tensorflow: four extra arguments are required for the 'TF_GraphGetOpDef' C API function.> ...
%! tensorflow ('TF_GraphGetOpDef', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Graph parsed to the 'TF_GraphGetOpDef' C API function.> ...
%! tensorflow ('TF_GraphGetOpDef', 1, 2, 3, 4);
%!error <tensorflow: 3rd argument must be a character vector defining the operation name parsed to the 'TF_GraphGetOpDef' C API function.> ...
%! tensorflow ('TF_GraphGetOpDef', uint64 (1), 2, 3, 4);
%!error <tensorflow: 4th argument must be an uint64 scalar pointer to the Buffer parsed to the 'TF_GraphGetOpDef' C API function.> ...
%! tensorflow ('TF_GraphGetOpDef', uint64 (1), "op_name", 3, 4);
%!error <tensorflow: 5th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_GraphGetOpDef' C API function.> ...
%! tensorflow ('TF_GraphGetOpDef', uint64 (1), "op_name", uint64 (3), 4);

%!error <tensorflow: three extra arguments are required for the 'TF_GraphVersions' C API function.> ...
%! tensorflow ('TF_GraphVersions');
%!error <tensorflow: three extra arguments are required for the 'TF_GraphVersions' C API function.> ...
%! tensorflow ('TF_GraphVersions', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_GraphVersions' C API function.> ...
%! tensorflow ('TF_GraphVersions', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Graph parsed to the 'TF_GraphVersions' C API function.> ...
%! tensorflow ('TF_GraphVersions', 1, 2, 3);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the Buffer parsed to the 'TF_GraphVersions' C API function.> ...
%! tensorflow ('TF_GraphVersions', uint64 (1), 2, 3);
%!error <tensorflow: 4th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_GraphVersions' C API function.> ...
%! tensorflow ('TF_GraphVersions', uint64 (1), uint64 (2), 3);

%!error <tensorflow: four extra arguments are required for the 'TF_GraphImportGraphDefWithResults' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDefWithResults');
%!error <tensorflow: four extra arguments are required for the 'TF_GraphImportGraphDefWithResults' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDefWithResults', 1);
%!error <tensorflow: four extra arguments are required for the 'TF_GraphImportGraphDefWithResults' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDefWithResults', 1, 2);
%!error <tensorflow: four extra arguments are required for the 'TF_GraphImportGraphDefWithResults' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDefWithResults', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Graph parsed to the 'TF_GraphImportGraphDefWithResults' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDefWithResults', 1, 2, 3, 4);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the Buffer parsed to the 'TF_GraphImportGraphDefWithResults' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDefWithResults', uint64 (1), 2, 3, 4);
%!error <tensorflow: 4th argument must be an uint64 scalar pointer to the ImportGraphDefOptions parsed to the 'TF_GraphImportGraphDefWithResults' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDefWithResults', uint64 (1), uint64 (2), 3, 4);
%!error <tensorflow: 5th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_GraphImportGraphDefWithResults' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDefWithResults', uint64 (1), uint64 (2), uint64 (3), 4);

%!error <tensorflow: six extra arguments are required for the 'TF_GraphImportGraphDefWithReturnOutputs' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDefWithReturnOutputs');
%!error <tensorflow: six extra arguments are required for the 'TF_GraphImportGraphDefWithReturnOutputs' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDefWithReturnOutputs', 1);
%!error <tensorflow: six extra arguments are required for the 'TF_GraphImportGraphDefWithReturnOutputs' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDefWithReturnOutputs', 1, 2);
%!error <tensorflow: six extra arguments are required for the 'TF_GraphImportGraphDefWithReturnOutputs' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDefWithReturnOutputs', 1, 2, 3);
%!error <tensorflow: six extra arguments are required for the 'TF_GraphImportGraphDefWithReturnOutputs' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDefWithReturnOutputs', 1, 2, 3, 4);
%!error <tensorflow: six extra arguments are required for the 'TF_GraphImportGraphDefWithReturnOutputs' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDefWithReturnOutputs', 1, 2, 3, 4, 5);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Graph parsed to the 'TF_GraphImportGraphDefWithReturnOutputs' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDefWithReturnOutputs', 1, 2, 3, 4, 5, 6);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the Buffer parsed to the 'TF_GraphImportGraphDefWithReturnOutputs' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDefWithReturnOutputs', uint64 (1), 2, 3, 4, 5, 6);
%!error <tensorflow: 4th argument must be an uint64 scalar pointer to the ImportGraphDefOptions parsed to the 'TF_GraphImportGraphDefWithReturnOutputs' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDefWithReturnOutputs', uint64 (1), uint64 (2), 3, 4, 5, 6);
%!error <tensorflow: 5th argument must be an uint64 scalar pointer to the Output parsed to the 'TF_GraphImportGraphDefWithReturnOutputs' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDefWithReturnOutputs', uint64 (1), uint64 (2), uint64 (3), 4, 5, 6);
%!error <tensorflow: 6th argument must be an int32 scalar value with the number of Output parsed to the 'TF_GraphImportGraphDefWithReturnOutputs' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDefWithReturnOutputs', uint64 (1), uint64 (2), uint64 (3), uint64 (4), 5, 6);
%!error <tensorflow: 7th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_GraphImportGraphDefWithReturnOutputs' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDefWithReturnOutputs', uint64 (1), uint64 (2), uint64 (3), uint64 (4), int32 (5), 6);

%!error <tensorflow: four extra arguments are required for the 'TF_GraphImportGraphDef' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDef');
%!error <tensorflow: four extra arguments are required for the 'TF_GraphImportGraphDef' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDef', 1);
%!error <tensorflow: four extra arguments are required for the 'TF_GraphImportGraphDef' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDef', 1, 2);
%!error <tensorflow: four extra arguments are required for the 'TF_GraphImportGraphDef' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDef', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Graph parsed to the 'TF_GraphImportGraphDef' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDef', 1, 2, 3, 4);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the Buffer parsed to the 'TF_GraphImportGraphDef' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDef', uint64 (1), 2, 3, 4);
%!error <tensorflow: 4th argument must be an uint64 scalar pointer to the ImportGraphDefOptions parsed to the 'TF_GraphImportGraphDef' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDef', uint64 (1), uint64 (2), 3, 4);
%!error <tensorflow: 5th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_GraphImportGraphDef' C API function.> ...
%! tensorflow ('TF_GraphImportGraphDef', uint64 (1), uint64 (2), uint64 (3), 4);

%!error <tensorflow: four extra arguments are required for the 'TF_GraphCopyFunction' C API function.> ...
%! tensorflow ('TF_GraphCopyFunction');
%!error <tensorflow: four extra arguments are required for the 'TF_GraphCopyFunction' C API function.> ...
%! tensorflow ('TF_GraphCopyFunction', 1);
%!error <tensorflow: four extra arguments are required for the 'TF_GraphCopyFunction' C API function.> ...
%! tensorflow ('TF_GraphCopyFunction', 1, 2);
%!error <tensorflow: four extra arguments are required for the 'TF_GraphCopyFunction' C API function.> ...
%! tensorflow ('TF_GraphCopyFunction', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Graph parsed to the 'TF_GraphCopyFunction' C API function.> ...
%! tensorflow ('TF_GraphCopyFunction', 1, 2, 3, 4);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the Function parsed to the 'TF_GraphCopyFunction' C API function.> ...
%! tensorflow ('TF_GraphCopyFunction', uint64 (1), 2, 3, 4);
%!error <tensorflow: 4th argument must be an uint64 scalar pointer to the Gradient parsed to the 'TF_GraphCopyFunction' C API function.> ...
%! tensorflow ('TF_GraphCopyFunction', uint64 (1), uint64 (2), 3, 4);
%!error <tensorflow: 5th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_GraphCopyFunction' C API function.> ...
%! tensorflow ('TF_GraphCopyFunction', uint64 (1), uint64 (2), uint64 (3), 4);

%!error <tensorflow: one extra argument is required for the 'TF_GraphNumFunctions' C API function.> ...
%! tensorflow ('TF_GraphNumFunctions');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Graph parsed to the 'TF_GraphNumFunctions' C API function.> ...
%! tensorflow ('TF_GraphNumFunctions', 1);

%!error <tensorflow: two extra arguments are required for the 'TF_GraphGetFunctions' C API function.>
%! tensorflow ('TF_GraphGetFunctions');
%!error <tensorflow: two extra arguments are required for the 'TF_GraphGetFunctions' C API function.>
%! tensorflow ('TF_GraphGetFunctions', 1);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Graph parsed to the 'TF_GraphGetFunctions' C API function.> ...
%! tensorflow ('TF_GraphGetFunctions', 1, 2);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the Status parsed to the 'TF_GraphGetFunctions' C API function.> ...
%! tensorflow ('TF_GraphGetFunctions', uint64 (1), 2);

%!error <tensorflow: four extra arguments are required for the 'TF_NewWhile' C API function.> ...
%! tensorflow ('TF_NewWhile');
%!error <tensorflow: four extra arguments are required for the 'TF_NewWhile' C API function.> ...
%! tensorflow ('TF_NewWhile', 1);
%!error <tensorflow: four extra arguments are required for the 'TF_NewWhile' C API function.> ...
%! tensorflow ('TF_NewWhile', 1, 2);
%!error <tensorflow: four extra arguments are required for the 'TF_NewWhile' C API function.> ...
%! tensorflow ('TF_NewWhile', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Graph parsed to the 'TF_NewWhile' C API function.> ...
%! tensorflow ('TF_NewWhile', 1, 2, 3, 4);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the Output parsed to the 'TF_NewWhile' C API function.> ...
%! tensorflow ('TF_NewWhile', uint64 (1), 2, 3, 4);
%!error <tensorflow: 4th argument must be an int32 scalar value defining the number of inputs parsed to the 'TF_NewWhile' C API function.> ...
%! tensorflow ('TF_NewWhile', uint64 (1), uint64 (2), 3, 4);
%!error <tensorflow: 5th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_NewWhile' C API function.> ...
%! tensorflow ('TF_NewWhile', uint64 (1), uint64 (2), int32 (3), 4);

%!error <tensorflow: eight extra arguments are required for the 'TF_AddGradients' C API function.> ...
%! tensorflow ('TF_AddGradients');
%!error <tensorflow: eight extra arguments are required for the 'TF_AddGradients' C API function.> ...
%! tensorflow ('TF_AddGradients', 1);
%!error <tensorflow: eight extra arguments are required for the 'TF_AddGradients' C API function.> ...
%! tensorflow ('TF_AddGradients', 1, 2);
%!error <tensorflow: eight extra arguments are required for the 'TF_AddGradients' C API function.> ...
%! tensorflow ('TF_AddGradients', 1, 2, 3);
%!error <tensorflow: eight extra arguments are required for the 'TF_AddGradients' C API function.> ...
%! tensorflow ('TF_AddGradients', 1, 2, 3, 4);
%!error <tensorflow: eight extra arguments are required for the 'TF_AddGradients' C API function.> ...
%! tensorflow ('TF_AddGradients', 1, 2, 3, 4, 5);
%!error <tensorflow: eight extra arguments are required for the 'TF_AddGradients' C API function.> ...
%! tensorflow ('TF_AddGradients', 1, 2, 3, 4, 5, 6);
%!error <tensorflow: eight extra arguments are required for the 'TF_AddGradients' C API function.> ...
%! tensorflow ('TF_AddGradients', 1, 2, 3, 4, 5, 6, 7);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Graph parsed to the 'TF_AddGradients' C API function.> ...
%! tensorflow ('TF_AddGradients', 1, 2, 3, 4, 5, 6, 7, 8);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the Output 'y' parsed to the 'TF_AddGradients' C API function.> ...
%! tensorflow ('TF_AddGradients', uint64 (1), 2, 3, 4, 5, 6, 7, 8);
%!error <tensorflow: 4th argument must be an int32 scalar value defining the number of inputs 'y' parsed to the 'TF_AddGradients' C API function.> ...
%! tensorflow ('TF_AddGradients', uint64 (1), uint64 (2), 3, 4, 5, 6, 7, 8);
%!error <tensorflow: 5th argument must be an uint64 scalar pointer to the Output 'x' parsed to the 'TF_AddGradients' C API function.> ...
%! tensorflow ('TF_AddGradients', uint64 (1), uint64 (2), int32 (3), 4, 5, 6, 7, 8);
%!error <tensorflow: 6th argument must be an int32 scalar value defining the number of inputs 'x' parsed to the 'TF_AddGradients' C API function.> ...
%! tensorflow ('TF_AddGradients', uint64 (1), uint64 (2), int32 (3), uint64 (4), 5, 6, 7, 8);
%!error <tensorflow: 7th argument must be an uint64 scalar pointer to the Output 'dx' parsed to the 'TF_AddGradients' C API function.> ...
%! tensorflow ('TF_AddGradients', uint64 (1), uint64 (2), int32 (3), uint64 (4), int32 (5), 6, 7, 8);
%!error <tensorflow: 8th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_AddGradients' C API function.> ...
%! tensorflow ('TF_AddGradients', uint64 (1), uint64 (2), int32 (3), uint64 (4), int32 (5), uint64 (6), 7, 8);
%!error <tensorflow: 9th argument must be an uint64 scalar pointer to the Output 'dy' parsed to the 'TF_AddGradients' C API function.> ...
%! tensorflow ('TF_AddGradients', uint64 (1), uint64 (2), int32 (3), uint64 (4), int32 (5), uint64 (6), uint64 (7), 8);

%!error <tensorflow: nine extra arguments are required for the 'TF_AddGradientsWithPrefix' C API function.> ...
%! tensorflow ('TF_AddGradientsWithPrefix');
%!error <tensorflow: nine extra arguments are required for the 'TF_AddGradientsWithPrefix' C API function.> ...
%! tensorflow ('TF_AddGradientsWithPrefix', 1);
%!error <tensorflow: nine extra arguments are required for the 'TF_AddGradientsWithPrefix' C API function.> ...
%! tensorflow ('TF_AddGradientsWithPrefix', 1, 2);
%!error <tensorflow: nine extra arguments are required for the 'TF_AddGradientsWithPrefix' C API function.> ...
%! tensorflow ('TF_AddGradientsWithPrefix', 1, 2, 3);
%!error <tensorflow: nine extra arguments are required for the 'TF_AddGradientsWithPrefix' C API function.> ...
%! tensorflow ('TF_AddGradientsWithPrefix', 1, 2, 3, 4);
%!error <tensorflow: nine extra arguments are required for the 'TF_AddGradientsWithPrefix' C API function.> ...
%! tensorflow ('TF_AddGradientsWithPrefix', 1, 2, 3, 4, 5);
%!error <tensorflow: nine extra arguments are required for the 'TF_AddGradientsWithPrefix' C API function.> ...
%! tensorflow ('TF_AddGradientsWithPrefix', 1, 2, 3, 4, 5, 6);
%!error <tensorflow: nine extra arguments are required for the 'TF_AddGradientsWithPrefix' C API function.> ...
%! tensorflow ('TF_AddGradientsWithPrefix', 1, 2, 3, 4, 5, 6, 7);
%!error <tensorflow: nine extra arguments are required for the 'TF_AddGradientsWithPrefix' C API function.> ...
%! tensorflow ('TF_AddGradientsWithPrefix', 1, 2, 3, 4, 5, 6, 7, 8);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Graph parsed to the 'TF_AddGradientsWithPrefix' C API function.> ...
%! tensorflow ('TF_AddGradientsWithPrefix', 1, 2, 3, 4, 5, 6, 7, 8, 9);
%!error <tensorflow: 3rd argument must be a character vector defining the prefix name parsed to the 'TF_AddGradientsWithPrefix' C API function.> ...
%! tensorflow ('TF_AddGradientsWithPrefix', uint64 (1), 2, 3, 4, 5, 6, 7, 8, 9);
%!error <tensorflow: 4th argument must be an uint64 scalar pointer to the Output 'y' parsed to the 'TF_AddGradientsWithPrefix' C API function.> ...
%! tensorflow ('TF_AddGradientsWithPrefix', uint64 (1), "prefix", 3, 4, 5, 6, 7, 8, 9);
%!error <tensorflow: 5th argument must be an int32 scalar value defining the number of inputs 'y' parsed to the 'TF_AddGradientsWithPrefix' C API function.> ...
%! tensorflow ('TF_AddGradientsWithPrefix', uint64 (1), "prefix", uint64 (3), 4, 5, 6, 7, 8, 9);
%!error <tensorflow: 6th argument must be an uint64 scalar pointer to the Output 'x' parsed to the 'TF_AddGradientsWithPrefix' C API function.> ...
%! tensorflow ('TF_AddGradientsWithPrefix', uint64 (1), "prefix", uint64 (3), int32 (4), 5, 6, 7, 8, 9);
%!error <tensorflow: 7th argument must be an int32 scalar value defining the number of inputs 'x' parsed to the 'TF_AddGradientsWithPrefix' C API function.> ...
%! tensorflow ('TF_AddGradientsWithPrefix', uint64 (1), "prefix", uint64 (3), int32 (4), uint64 (5), 6, 7, 8, 9);
%!error <tensorflow: 8th argument must be an uint64 scalar pointer to the Output 'dx' parsed to the 'TF_AddGradientsWithPrefix' C API function.> ...
%! tensorflow ('TF_AddGradientsWithPrefix', uint64 (1), "prefix", uint64 (3), int32 (4), uint64 (5), int32 (6), 7, 8, 9);
%!error <tensorflow: 9th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_AddGradientsWithPrefix' C API function.> ...
%! tensorflow ('TF_AddGradientsWithPrefix', uint64 (1), "prefix", uint64 (3), int32 (4), uint64 (5), int32 (6), uint64 (7), 8, 9);
%!error <tensorflow: 10th argument must be an uint64 scalar pointer to the Output 'dy' parsed to the 'TF_AddGradientsWithPrefix' C API function.> ...
%! tensorflow ('TF_AddGradientsWithPrefix', uint64 (1), "prefix", uint64 (3), int32 (4), uint64 (5), int32 (6), uint64 (7), uint64 (8), 9);

## Unsupported C API function
%!error <tensorflow: 'TF_GraphToFunction' C API function not supported yet.> ...
%! tensorflow ('TF_GraphToFunction');

## Unsupported C API function
%!error <tensorflow: 'TF_GraphToFunctionWithControlOutputs' C API function not supported yet.>
%! tensorflow ('TF_GraphToFunctionWithControlOutputs')

  ## ---------------------------------------------------------------------------
  ## C API functions referenced by the TF_OperationDescription classdef
  ## ---------------------------------------------------------------------------
%!error <tensorflow: two extra arguments are required for the 'TF_SetDevice' C API function.> ...
%! tensorflow ('TF_SetDevice');
%!error <tensorflow: two extra arguments are required for the 'TF_SetDevice' C API function.> ...
%! tensorflow ('TF_SetDevice', 1);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetDevice' C API function.> ...
%! tensorflow ('TF_SetDevice', 1, 2);
%!error <tensorflow: 3rd argument must be a character vector defining the device parsed to the 'TF_SetDevice' C API function.> ...
%! tensorflow ('TF_SetDevice', uint64 (1), 2);
%!error <tensorflow: 3rd argument must be a character vector defining the device parsed to the 'TF_SetDevice' C API function.> ...
%! tensorflow ('TF_SetDevice', uint64 (1), ['a'; 'b']);

%!error <tensorflow: two extra arguments are required for the 'TF_AddInput' C API function.> ...
%! tensorflow ('TF_AddInput');
%!error <tensorflow: two extra arguments are required for the 'TF_AddInput' C API function.> ...
%! tensorflow ('TF_AddInput', 1);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_AddInput' C API function.> ...
%! tensorflow ('TF_AddInput', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_AddInput' C API function.> ...
%! tensorflow ('TF_AddInput', uint64 ([1, 2]), 2);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the input parsed to the 'TF_AddInput' C API function.> ...
%! tensorflow ('TF_AddInput', uint64 (1), 2);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the input parsed to the 'TF_AddInput' C API function.> ...
%! tensorflow ('TF_AddInput', uint64 (1), uint64 ([1, 2]));

%!error <tensorflow: two extra arguments are required for the 'TF_AddInputList' C API function.> ...
%! tensorflow ('TF_AddInputList');
%!error <tensorflow: two extra arguments are required for the 'TF_AddInputList' C API function.> ...
%! tensorflow ('TF_AddInputList', 1);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_AddInputList' C API function.> ...
%! tensorflow ('TF_AddInputList', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_AddInputList' C API function.> ...
%! tensorflow ('TF_AddInputList', uint64 ([1, 2]), 2);
%!error <tensorflow: 3rd argument must be an uint64 vector of pointers to the inputs parsed to the 'TF_AddInputList' C API function.> ...
%! tensorflow ('TF_AddInputList', uint64 (1), 2);
%!error <tensorflow: 3rd argument must be an uint64 vector of pointers to the inputs parsed to the 'TF_AddInputList' C API function.> ...
%! tensorflow ('TF_AddInputList', uint64 (1), uint64 ([1; 2]));

%!error <tensorflow: two extra arguments are required for the 'TF_AddControlInput' C API function.> ...
%! tensorflow ('TF_AddControlInput');
%!error <tensorflow: two extra arguments are required for the 'TF_AddControlInput' C API function.> ...
%! tensorflow ('TF_AddControlInput', 1);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_AddControlInput' C API function.> ...
%! tensorflow ('TF_AddControlInput', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_AddControlInput' C API function.> ...
%! tensorflow ('TF_AddControlInput', uint64 ([1, 2]), 2);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the Operation parsed to the 'TF_AddControlInput' C API function.> ...
%! tensorflow ('TF_AddControlInput', uint64 (1), 2);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the Operation parsed to the 'TF_AddControlInput' C API function.> ...
%! tensorflow ('TF_AddControlInput', uint64 (1), uint64 ([1, 2]));

%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrString' C API function.> ...
%! tensorflow ('TF_SetAttrString');
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrString' C API function.> ...
%! tensorflow ('TF_SetAttrString', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrString' C API function.> ...
%! tensorflow ('TF_SetAttrString', 1, 2);
%!error <2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrString' C API function.> ...
%! tensorflow ('TF_SetAttrString', 1, 2, 3);
%!error <2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrString' C API function.> ...
%! tensorflow ('TF_SetAttrString', uint64 ([1, 2]), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrString' C API function.> ...
%! tensorflow ('TF_SetAttrString', uint64 (1), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrString' C API function.> ...
%! tensorflow ('TF_SetAttrString', uint64 (1), ['a'; 'b'], 3);
%!error <tensorflow: 4th argument must be a character vector defining the attribute string parsed to the 'TF_SetAttrString' C API function.> ...
%! tensorflow ('TF_SetAttrString', uint64 (1), 'name', 3);
%!error <tensorflow: 4th argument must be a character vector defining the attribute string parsed to the 'TF_SetAttrString' C API function.> ...
%! tensorflow ('TF_SetAttrString', uint64 (1), 'name',  ['a'; 'b']);

%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrStringList' C API function.> ...
%! tensorflow ('TF_SetAttrStringList');
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrStringList' C API function.> ...
%! tensorflow ('TF_SetAttrStringList', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrStringList' C API function.> ...
%! tensorflow ('TF_SetAttrStringList', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrStringList' C API function.> ...
%! tensorflow ('TF_SetAttrStringList', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrStringList' C API function.> ...
%! tensorflow ('TF_SetAttrStringList', uint64 ([1, 2]), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrStringList' C API function.> ...
%! tensorflow ('TF_SetAttrStringList', uint64 (1), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrStringList' C API function.> ...
%! tensorflow ('TF_SetAttrStringList', uint64 (1), ['a'; 'b'], 3);
%!error <tensorflow: 4th argument must be a cellstr vector defining the attribute string parsed to the 'TF_SetAttrStringList' C API function.> ...
%! tensorflow ('TF_SetAttrStringList', uint64 (1), 'name', 3);
%!error <tensorflow: 4th argument must be a cellstr vector defining the attribute string parsed to the 'TF_SetAttrStringList' C API function.> ...
%! tensorflow ('TF_SetAttrStringList', uint64 (1), 'name', {3});
%!error <tensorflow: 4th argument must be a cellstr vector defining the attribute string parsed to the 'TF_SetAttrStringList' C API function.> ...
%! tensorflow ('TF_SetAttrStringList', uint64 (1), 'name', {"a", "b"; "c", "d"});

%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrInt' C API function.> ...
%! tensorflow ('TF_SetAttrInt');
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrInt' C API function.> ...
%! tensorflow ('TF_SetAttrInt', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrInt' C API function.> ...
%! tensorflow ('TF_SetAttrInt', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrInt' C API function.> ...
%! tensorflow ('TF_SetAttrInt', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrInt' C API function.> ...
%! tensorflow ('TF_SetAttrInt', uint64 ([1, 2]), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrInt' C API function.> ...
%! tensorflow ('TF_SetAttrInt', uint64 (1), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrInt' C API function.> ...
%! tensorflow ('TF_SetAttrInt', uint64 (1), ['a'; 'b'], 3);
%!error <tensorflow: 4th argument must be an int64 scalar parsed to the 'TF_SetAttrInt' C API function.> ...
%! tensorflow ('TF_SetAttrInt', uint64 (1), 'name', 3);
%!error <tensorflow: 4th argument must be an int64 scalar parsed to the 'TF_SetAttrInt' C API function.> ...
%! tensorflow ('TF_SetAttrInt', uint64 (1), 'name', int64 ([1, 2]));

%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrIntList' C API function.> ...
%! tensorflow ('TF_SetAttrIntList');
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrIntList' C API function.> ...
%! tensorflow ('TF_SetAttrIntList', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrIntList' C API function.> ...
%! tensorflow ('TF_SetAttrIntList', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrIntList' C API function.> ...
%! tensorflow ('TF_SetAttrIntList', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrIntList' C API function.> ...
%! tensorflow ('TF_SetAttrIntList', uint64 ([1, 2]), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrIntList' C API function.> ...
%! tensorflow ('TF_SetAttrIntList', uint64 (1), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrIntList' C API function.> ...
%! tensorflow ('TF_SetAttrIntList', uint64 (1), ['a'; 'b'], 3);
%!error <tensorflow: 4th argument must be an int64 vector parsed to the 'TF_SetAttrIntList' C API function.> ...
%! tensorflow ('TF_SetAttrIntList', uint64 (1), 'name', 3);
%!error <tensorflow: 4th argument must be an int64 vector parsed to the 'TF_SetAttrIntList' C API function.> ...
%! tensorflow ('TF_SetAttrIntList', uint64 (1), 'name', int64 ([1; 2]));

%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrFloat' C API function.> ...
%! tensorflow ('TF_SetAttrFloat');
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrFloat' C API function.> ...
%! tensorflow ('TF_SetAttrFloat', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrFloat' C API function.> ...
%! tensorflow ('TF_SetAttrFloat', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrFloat' C API function.> ...
%! tensorflow ('TF_SetAttrFloat', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrFloat' C API function.> ...
%! tensorflow ('TF_SetAttrFloat', uint64 ([1, 2]), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrFloat' C API function.> ...
%! tensorflow ('TF_SetAttrFloat', uint64 (1), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrFloat' C API function.> ...
%! tensorflow ('TF_SetAttrFloat', uint64 (1), ['a'; 'b'], 3);
%!error <tensorflow: 4th argument must be a float scalar parsed to the 'TF_SetAttrFloat' C API function.> ...
%! tensorflow ('TF_SetAttrFloat', uint64 (1), 'name', 3);
%!error <tensorflow: 4th argument must be a float scalar parsed to the 'TF_SetAttrFloat' C API function.> ...
%! tensorflow ('TF_SetAttrFloat', uint64 (1), 'name', single ([1, 2]));

%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrFloatList' C API function.> ...
%! tensorflow ('TF_SetAttrFloatList');
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrFloatList' C API function.> ...
%! tensorflow ('TF_SetAttrFloatList', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrFloatList' C API function.> ...
%! tensorflow ('TF_SetAttrFloatList', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrFloatList' C API function.> ...
%! tensorflow ('TF_SetAttrFloatList', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrFloatList' C API function.> ...
%! tensorflow ('TF_SetAttrFloatList', uint64 ([1, 2]), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrFloatList' C API function.> ...
%! tensorflow ('TF_SetAttrFloatList', uint64 (1), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrFloatList' C API function.> ...
%! tensorflow ('TF_SetAttrFloatList', uint64 (1), ['a'; 'b'], 3);
%!error <tensorflow: 4th argument must be a float vector parsed to the 'TF_SetAttrFloatList' C API function.> ...
%! tensorflow ('TF_SetAttrFloatList', uint64 (1), 'name', 3);
%!error <tensorflow: 4th argument must be a float vector parsed to the 'TF_SetAttrFloatList' C API function.> ...
%! tensorflow ('TF_SetAttrFloatList', uint64 (1), 'name', single ([1; 2]));

%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrBool' C API function.> ...
%! tensorflow ('TF_SetAttrBool');
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrBool' C API function.> ...
%! tensorflow ('TF_SetAttrBool', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrBool' C API function.> ...
%! tensorflow ('TF_SetAttrBool', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrBool' C API function.> ...
%! tensorflow ('TF_SetAttrBool', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrBool' C API function.> ...
%! tensorflow ('TF_SetAttrBool', uint64 ([1, 2]), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrBool' C API function.> ...
%! tensorflow ('TF_SetAttrBool', uint64 (1), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrBool' C API function.> ...
%! tensorflow ('TF_SetAttrBool', uint64 (1), ['a'; 'b'], 3);
%!error <tensorflow: 4th argument must be a bool scalar parsed to the 'TF_SetAttrBool' C API function.> ...
%! tensorflow ('TF_SetAttrBool', uint64 (1), 'name', 3);
%!error <tensorflow: 4th argument must be a bool scalar parsed to the 'TF_SetAttrBool' C API function.> ...
%! tensorflow ('TF_SetAttrBool', uint64 (1), 'name', [true, true]);

%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrBoolList' C API function.> ...
%! tensorflow ('TF_SetAttrBoolList');
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrBoolList' C API function.> ...
%! tensorflow ('TF_SetAttrBoolList', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrBoolList' C API function.> ...
%! tensorflow ('TF_SetAttrBoolList', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrBoolList' C API function.> ...
%! tensorflow ('TF_SetAttrBoolList', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrBoolList' C API function.> ...
%! tensorflow ('TF_SetAttrBoolList', uint64 ([1, 2]), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrBoolList' C API function.> ...
%! tensorflow ('TF_SetAttrBoolList', uint64 (1), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrBoolList' C API function.> ...
%! tensorflow ('TF_SetAttrBoolList', uint64 (1), ['a'; 'b'], 3);
%!error <tensorflow: 4th argument must be a bool vector parsed to the 'TF_SetAttrBoolList' C API function.> ...
%! tensorflow ('TF_SetAttrBoolList', uint64 (1), 'name', 3);
%!error <tensorflow: 4th argument must be a bool vector parsed to the 'TF_SetAttrBoolList' C API function.> ...
%! tensorflow ('TF_SetAttrBoolList', uint64 (1), 'name', [true; true]);

%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrType' C API function.> ...
%! tensorflow ('TF_SetAttrType');
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrType' C API function.> ...
%! tensorflow ('TF_SetAttrType', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrType' C API function.> ...
%! tensorflow ('TF_SetAttrType', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrType' C API function.> ...
%! tensorflow ('TF_SetAttrType', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrType' C API function.> ...
%! tensorflow ('TF_SetAttrType', uint64 ([1, 2]), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrType' C API function.> ...
%! tensorflow ('TF_SetAttrType', uint64 (1), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrType' C API function.> ...
%! tensorflow ('TF_SetAttrType', uint64 (1), ['a'; 'b'], 3);
%!error <tensorflow: 4th argument must be an uint32 scalar defining the DataType parsed to the 'TF_SetAttrType' C API function.> ...
%! tensorflow ('TF_SetAttrType', uint64 (1), 'name', 3);
%!error <tensorflow: 4th argument must be an uint32 scalar defining the DataType parsed to the 'TF_SetAttrType' C API function.> ...
%! tensorflow ('TF_SetAttrType', uint64 (1), 'name', uint32 ([1, 2]));

%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrTypeList' C API function.> ...
%! tensorflow ('TF_SetAttrTypeList');
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrTypeList' C API function.> ...
%! tensorflow ('TF_SetAttrTypeList', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrTypeList' C API function.> ...
%! tensorflow ('TF_SetAttrTypeList', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrTypeList' C API function.> ...
%! tensorflow ('TF_SetAttrTypeList', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrTypeList' C API function.> ...
%! tensorflow ('TF_SetAttrTypeList', uint64 ([1, 2]), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrTypeList' C API function.> ...
%! tensorflow ('TF_SetAttrTypeList', uint64 (1), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrTypeList' C API function.> ...
%! tensorflow ('TF_SetAttrTypeList', uint64 (1), ['a'; 'b'], 3);
%!error <tensorflow: 4th argument must be an uint32 vector defining the DataType parsed to the 'TF_SetAttrTypeList' C API function.> ...
%! tensorflow ('TF_SetAttrTypeList', uint64 (1), 'name', 3);
%!error <tensorflow: 4th argument must be an uint32 vector defining the DataType parsed to the 'TF_SetAttrTypeList' C API function.> ...
%! tensorflow ('TF_SetAttrTypeList', uint64 (1), 'name', uint32 ([1; 2]));

%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrPlaceholder' C API function.> ...
%! tensorflow ('TF_SetAttrPlaceholder');
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrPlaceholder' C API function.> ...
%! tensorflow ('TF_SetAttrPlaceholder', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrPlaceholder' C API function.> ...
%! tensorflow ('TF_SetAttrPlaceholder', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrPlaceholder' C API function.> ...
%! tensorflow ('TF_SetAttrPlaceholder', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrPlaceholder' C API function.> ...
%! tensorflow ('TF_SetAttrPlaceholder', uint64 ([1, 2]), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrPlaceholder' C API function.> ...
%! tensorflow ('TF_SetAttrPlaceholder', uint64 (1), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrPlaceholder' C API function.> ...
%! tensorflow ('TF_SetAttrPlaceholder', uint64 (1), ['a'; 'b'], 3);
%!error <tensorflow: 4th argument must be a character vector defining the placeholder parsed to the 'TF_SetAttrPlaceholder' C API function.> ...
%! tensorflow ('TF_SetAttrPlaceholder', uint64 (1), 'name', 3);
%!error <tensorflow: 4th argument must be a character vector defining the placeholder parsed to the 'TF_SetAttrPlaceholder' C API function.> ...
%! tensorflow ('TF_SetAttrPlaceholder', uint64 (1), 'name', ['a'; 'b']);

%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrFuncName' C API function.> ...
%! tensorflow ('TF_SetAttrFuncName');
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrFuncName' C API function.> ...
%! tensorflow ('TF_SetAttrFuncName', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_SetAttrFuncName' C API function.> ...
%! tensorflow ('TF_SetAttrFuncName', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrFuncName' C API function.> ...
%! tensorflow ('TF_SetAttrFuncName', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrFuncName' C API function.> ...
%! tensorflow ('TF_SetAttrFuncName', uint64 ([1, 2]), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrFuncName' C API function.> ...
%! tensorflow ('TF_SetAttrFuncName', uint64 (1), 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrFuncName' C API function.> ...
%! tensorflow ('TF_SetAttrFuncName', uint64 (1), ['a'; 'b'], 3);
%!error <tensorflow: 4th argument must be a character vector defining the function name parsed to the 'TF_SetAttrFuncName' C API function.> ...
%! tensorflow ('TF_SetAttrFuncName', uint64 (1), 'name', 3);
%!error <tensorflow: 4th argument must be a character vector defining the function name parsed to the 'TF_SetAttrFuncName' C API function.> ...
%! tensorflow ('TF_SetAttrFuncName', uint64 (1), 'name', ['a'; 'b']);

%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrShape' C API function.> ...
%! tensorflow ('TF_SetAttrShape');
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrShape' C API function.> ...
%! tensorflow ('TF_SetAttrShape', 1);
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrShape' C API function.> ...
%! tensorflow ('TF_SetAttrShape', 1, 2);
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrShape' C API function.> ...
%! tensorflow ('TF_SetAttrShape', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrShape' C API function.> ...
%! tensorflow ('TF_SetAttrShape', 1, 2, 3, 4);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrShape' C API function.> ...
%! tensorflow ('TF_SetAttrShape', uint64 ([1, 2]), 2, 3, 4);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrShape' C API function.> ...
%! tensorflow ('TF_SetAttrShape', uint64 (1), 2, 3, 4);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrShape' C API function.> ...
%! tensorflow ('TF_SetAttrShape', uint64 (1), ['a'; 'b'], 3, 4);
%!error <tensorflow: 4th argument must be an int64 scalar or vector defining the size of the dimensions parsed to the 'TF_SetAttrShape' C API function.> ...
%! tensorflow ('TF_SetAttrShape', uint64 (1), 'name', 3, 4);
%!error <tensorflow: 4th argument must be an int64 scalar or vector defining the size of the dimensions parsed to the 'TF_SetAttrShape' C API function.> ...
%! tensorflow ('TF_SetAttrShape', uint64 (1), 'name', int64 ([2; 3]), 4);
%!error <tensorflow: 5th argument must be an int32 scalar defining the number of the dimensions parsed to the 'TF_SetAttrShape' C API function.> ...
%! tensorflow ('TF_SetAttrShape', uint64 (1), 'name', int64 (2), 4);
%!error <tensorflow: 5th argument must be an int32 scalar defining the number of the dimensions parsed to the 'TF_SetAttrShape' C API function.> ...
%! tensorflow ('TF_SetAttrShape', uint64 (1), 'name', int64 (2), int32 ([1, 3]));

%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrShapeList' C API function.> ...
%! tensorflow ('TF_SetAttrShapeList');
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrShapeList' C API function.> ...
%! tensorflow ('TF_SetAttrShapeList', 1);
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrShapeList' C API function.> ...
%! tensorflow ('TF_SetAttrShapeList', 1, 2);
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrShapeList' C API function.> ...
%! tensorflow ('TF_SetAttrShapeList', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrShapeList' C API function.> ...
%! tensorflow ('TF_SetAttrShapeList', 1, 2, 3, 4);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrShapeList' C API function.> ...
%! tensorflow ('TF_SetAttrShapeList', uint64 ([1, 2]), 2, 3, 4);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrShapeList' C API function.> ...
%! tensorflow ('TF_SetAttrShapeList', uint64 (1), 2, 3, 4);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrShapeList' C API function.> ...
%! tensorflow ('TF_SetAttrShapeList', uint64 (1), ['a'; 'b'], 3, 4);
%!error <tensorflow: 4th argument must be an int64 matrix with each row defining the size of the dimensions of the respective shape parsed to the 'TF_SetAttrShapeList' C API function.> ...
%! tensorflow ('TF_SetAttrShapeList', uint64 (1), 'name', 3, 4);
%!error <tensorflow: 4th argument must be an int64 matrix with each row defining the size of the dimensions of the respective shape parsed to the 'TF_SetAttrShapeList' C API function.> ...
%! tensorflow ('TF_SetAttrShapeList', uint64 (1), 'name', int64 (ones (2, 2, 2)), 4);
%!error <tensorflow: 5th argument must be an int32 vector defining the number of the dimensions of each shape parsed to the 'TF_SetAttrShapeList' C API function.> ...
%! tensorflow ('TF_SetAttrShapeList', uint64 (1), 'name', int64 (2), 4);
%!error <tensorflow: 5th argument must be an int32 vector defining the number of the dimensions of each shape parsed to the 'TF_SetAttrShapeList' C API function.> ...
%! tensorflow ('TF_SetAttrShapeList', uint64 (1), 'name', int64 (2), int32 ([1; 3]));

%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrTensorShapeProto' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProto');
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrTensorShapeProto' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProto', 1);
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrTensorShapeProto' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProto', 1, 2);
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrTensorShapeProto' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProto', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrTensorShapeProto' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProto', 1, 2, 3, 4);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrTensorShapeProto' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProto', uint64 ([1, 2]), 2, 3, 4);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrTensorShapeProto' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProto', uint64 (1), 2, 3, 4);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrTensorShapeProto' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProto', uint64 (1), ['a'; 'b'], 3, 4);
%!error <tensorflow: 4th argument must be a uint8 vector of binary-serialized TensorShapeProto data parsed to the 'TF_SetAttrTensorShapeProto' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProto', uint64 (1), 'name', 3, 4);
%!error <tensorflow: 4th argument must be a uint8 vector of binary-serialized TensorShapeProto data parsed to the 'TF_SetAttrTensorShapeProto' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProto', uint64 (1), 'name', uint8 ([2; 3]), 4);
%!error <tensorflow: 5th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_SetAttrTensorShapeProto' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProto', uint64 (1), 'name', uint8 ([2, 3]), 4);
%!error <tensorflow: 5th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_SetAttrTensorShapeProto' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProto', uint64 (1), 'name', uint8 ([2, 3]), uint64 ([1, 2]));

%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrTensorShapeProtoList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProtoList');
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrTensorShapeProtoList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProtoList', 1);
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrTensorShapeProtoList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProtoList', 1, 2);
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrTensorShapeProtoList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProtoList', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrTensorShapeProtoList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProtoList', 1, 2, 3, 4);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrTensorShapeProtoList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProtoList', uint64 ([1, 2]), 2, 3, 4);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrTensorShapeProtoList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProtoList', uint64 (1), 2, 3, 4);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrTensorShapeProtoList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProtoList', uint64 (1), ['a'; 'b'], 3, 4);
%!error <tensorflow: 4th argument must be a cell vector of uint8 vectors representing a list of binary-serialized TensorShapeProtos parsed to the 'TF_SetAttrTensorShapeProtoList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProtoList', uint64 (1), 'name', 3, 4);
%!error <tensorflow: 4th argument must be a cell vector of uint8 vectors representing a list of binary-serialized TensorShapeProtos parsed to the 'TF_SetAttrTensorShapeProtoList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProtoList', uint64 (1), 'name', {2; 3}, 4);
%!error <tensorflow: 4th argument must be a cell vector of uint8 vectors representing a list of binary-serialized TensorShapeProtos parsed to the 'TF_SetAttrTensorShapeProtoList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProtoList', uint64 (1), 'name', {uint8([1, 2, 3]), 3}, 4);
%!error <tensorflow: 4th argument must be a cell vector of uint8 vectors representing a list of binary-serialized TensorShapeProtos parsed to the 'TF_SetAttrTensorShapeProtoList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProtoList', uint64 (1), 'name', {uint8([1, 2, 3]); uint8([1; 2])}, 4);
%!error <tensorflow: 5th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_SetAttrTensorShapeProtoList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProtoList', uint64 (1), 'name', {uint8([1, 2, 3]), uint8([1, 2])}, 4);
%!error <tensorflow: 5th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_SetAttrTensorShapeProtoList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorShapeProtoList', uint64 (1), 'name', {uint8([1, 2, 3]), uint8([1, 2])}, uint64 ([4, 5]));

%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrTensor' C API function.> ...
%! tensorflow ('TF_SetAttrTensor');
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrTensor' C API function.> ...
%! tensorflow ('TF_SetAttrTensor', 1);
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrTensor' C API function.> ...
%! tensorflow ('TF_SetAttrTensor', 1, 2);
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrTensor' C API function.> ...
%! tensorflow ('TF_SetAttrTensor', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrTensor' C API function.> ...
%! tensorflow ('TF_SetAttrTensor', 1, 2, 3, 4);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrTensor' C API function.> ...
%! tensorflow ('TF_SetAttrTensor', uint64 ([1, 2]), 2, 3, 4);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrTensor' C API function.> ...
%! tensorflow ('TF_SetAttrTensor', uint64 (1), 2, 3, 4);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrTensor' C API function.> ...
%! tensorflow ('TF_SetAttrTensor', uint64 (1), ['a'; 'b'], 3, 4);
%!error <tensorflow: 4th argument must be an uint64 scalar pointer to the Tensor parsed to the 'TF_SetAttrTensor' C API function.> ...
%! tensorflow ('TF_SetAttrTensor', uint64 (1), 'name', 3, 4);
%!error <tensorflow: 4th argument must be an uint64 scalar pointer to the Tensor parsed to the 'TF_SetAttrTensor' C API function.> ...
%! tensorflow ('TF_SetAttrTensor', uint64 (1), 'name', uint64 ([2, 3]), 4);
%!error <tensorflow: 5th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_SetAttrTensor' C API function.> ...
%! tensorflow ('TF_SetAttrTensor', uint64 (1), 'name', uint64 (3), 4);
%!error <tensorflow: 5th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_SetAttrTensor' C API function.> ...
%! tensorflow ('TF_SetAttrTensor', uint64 (1), 'name', uint64 (3), uint64 ([4, 5]));

%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrTensorList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorList');
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrTensorList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorList', 1);
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrTensorList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorList', 1, 2);
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrTensorList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorList', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrTensorList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorList', 1, 2, 3, 4);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrTensorList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorList', uint64 ([1, 2]), 2, 3, 4);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrTensorList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorList', uint64 (1), 2, 3, 4);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrTensorList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorList', uint64 (1), ['a'; 'b'], 3, 4);
%!error <tensorflow: 4th argument must be an uint64 vector of pointers to the Tensors parsed to the 'TF_SetAttrTensorList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorList', uint64 (1), 'name', 3, 4);
%!error <tensorflow: 4th argument must be an uint64 vector of pointers to the Tensors parsed to the 'TF_SetAttrTensorList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorList', uint64 (1), 'name', uint64 ([2; 3]), 4);
%!error <tensorflow: 5th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_SetAttrTensorList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorList', uint64 (1), 'name', uint64 (3), 4);
%!error <tensorflow: 5th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_SetAttrTensorList' C API function.> ...
%! tensorflow ('TF_SetAttrTensorList', uint64 (1), 'name', uint64 (3), uint64 ([4, 5]));

%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrValueProto' C API function.> ...
%! tensorflow ('TF_SetAttrValueProto');
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrValueProto' C API function.> ...
%! tensorflow ('TF_SetAttrValueProto', 1);
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrValueProto' C API function.> ...
%! tensorflow ('TF_SetAttrValueProto', 1, 2);
%!error <tensorflow: four extra arguments are required for the 'TF_SetAttrValueProto' C API function.> ...
%! tensorflow ('TF_SetAttrValueProto', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrValueProto' C API function.> ...
%! tensorflow ('TF_SetAttrValueProto', 1, 2, 3, 4);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_SetAttrValueProto' C API function.> ...
%! tensorflow ('TF_SetAttrValueProto', uint64 ([1, 2]), 2, 3, 4);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrValueProto' C API function.> ...
%! tensorflow ('TF_SetAttrValueProto', uint64 (1), 2, 3, 4);
%!error <tensorflow: 3rd argument must be a character vector defining the attribute name parsed to the 'TF_SetAttrValueProto' C API function.> ...
%! tensorflow ('TF_SetAttrValueProto', uint64 (1), ['a'; 'b'], 3, 4);
%!error <tensorflow: 4th argument must be a uint8 vector representing a binary serialization of an AttrValue protocol buffer parsed to the 'TF_SetAttrValueProto' C API function.> ...
%! tensorflow ('TF_SetAttrValueProto', uint64 (1), 'name', 3, 4);
%!error <tensorflow: 4th argument must be a uint8 vector representing a binary serialization of an AttrValue protocol buffer parsed to the 'TF_SetAttrValueProto' C API function.> ...
%! tensorflow ('TF_SetAttrValueProto', uint64 (1), 'name', uint8 ([1; 2]), 4);
%!error <tensorflow: 5th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_SetAttrValueProto' C API function.> ...
%! tensorflow ('TF_SetAttrValueProto', uint64 (1), 'name', uint8 ([1, 2]), 4);
%!error <tensorflow: 5th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_SetAttrValueProto' C API function.> ...
%! tensorflow ('TF_SetAttrValueProto', uint64 (1), 'name', uint8 ([1, 2]), uint64 ([3, 4]));

%!error <tensorflow: two extra arguments are required for the 'TF_FinishOperationLocked' C API function.> ...
%! tensorflow ('TF_FinishOperationLocked');
%!error <tensorflow: two extra arguments are required for the 'TF_FinishOperationLocked' C API function.> ...
%! tensorflow ('TF_FinishOperationLocked', 1);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_FinishOperationLocked' C API function.> ...
%! tensorflow ('TF_FinishOperationLocked', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_FinishOperationLocked' C API function.> ...
%! tensorflow ('TF_FinishOperationLocked', uint64 ([1, 2]), 2);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the Status parsed to the 'TF_FinishOperationLocked' C API function.> ...
%! tensorflow ('TF_FinishOperationLocked', uint64 (1), 2);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the Status parsed to the 'TF_FinishOperationLocked' C API function.> ...
%! tensorflow ('TF_FinishOperationLocked', uint64 (1), uint64 ([2, 2]));

%!error <tensorflow: two extra arguments are required for the 'TF_FinishOperation' C API function.> ...
%! tensorflow ('TF_FinishOperation');
%!error <tensorflow: two extra arguments are required for the 'TF_FinishOperation' C API function.> ...
%! tensorflow ('TF_FinishOperation', 1);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_FinishOperation' C API function.> ...
%! tensorflow ('TF_FinishOperation', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the OperationDescription parsed to the 'TF_FinishOperation' C API function.> ...
%! tensorflow ('TF_FinishOperation', uint64 ([1, 2]), 2);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the Status parsed to the 'TF_FinishOperation' C API function.> ...
%! tensorflow ('TF_FinishOperation', uint64 (1), 2);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the Status parsed to the 'TF_FinishOperation' C API function.> ...
%! tensorflow ('TF_FinishOperation', uint64 (1), uint64 ([2, 2]));

  ## ---------------------------------------------------------------------------
  ## C API functions referenced by the TF_Status classdef
  ## ---------------------------------------------------------------------------
%!error <tensorflow: one extra argument is required for the 'TF_DeleteStatus' C API function.> ...
%! tensorflow ('TF_DeleteStatus');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Status parsed to the 'TF_DeleteStatus' C API function.> ...
%! tensorflow ('TF_DeleteStatus', 1);

%!error <tensorflow: three extra arguments are required for the 'TF_SetStatus' C API function.> ...
%! tensorflow ('TF_SetStatus');
%!error <tensorflow: three extra arguments are required for the 'TF_SetStatus' C API function.> ...
%! tensorflow ('TF_SetStatus', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_SetStatus' C API function.> ...
%! tensorflow ('TF_SetStatus', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Status parsed to the 'TF_SetStatus' C API function.> ...
%! tensorflow ('TF_SetStatus', 1, 2, 3);
%!error <tensorflow: 3rd argument must be an uint32 scalar indexing the appropriate TF_Code to be parsed to the 'TF_SetStatus' C API function.> ...
%! tensorflow ('TF_SetStatus', uint64 (1), 2, 3);
%!error <tensorflow: 4th argument must be a character vector defining the message to be parsed to the 'TF_SetStatus' C API function.> ...
%! tensorflow ('TF_SetStatus', uint64 (1), uint32(2), 3);

%!error <tensorflow: three extra arguments are required for the 'TF_SetPayload' C API function.> ...
%! tensorflow ('TF_SetPayload');
%!error <tensorflow: three extra arguments are required for the 'TF_SetPayload' C API function.> ...
%! tensorflow ('TF_SetPayload', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_SetPayload' C API function.> ...
%! tensorflow ('TF_SetPayload', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Status parsed to the 'TF_SetPayload' C API function.> ...
%! tensorflow ('TF_SetPayload', 1, 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the 'key' to be parsed to the 'TF_SetPayload' C API function.> ...
%! tensorflow ('TF_SetPayload', uint64 (1), 2, 3);
%!error <tensorflow: 4th argument must be a character vector defining the 'value' to be parsed to the 'TF_SetPayload' C API function.> ...
%! tensorflow ('TF_SetPayload', uint64 (1), "key", 3);

## Unsupported C API function
%!error <tensorflow: 'TF_ForEachPayload' C API function not supported yet.> ...
%! tensorflow ('TF_ForEachPayload');

%!error <tensorflow: three extra arguments are required for the 'TF_SetStatusFromIOError' C API function.> ...
%! tensorflow ('TF_SetStatusFromIOError');
%!error <tensorflow: three extra arguments are required for the 'TF_SetStatusFromIOError' C API function.> ...
%! tensorflow ('TF_SetStatusFromIOError', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_SetStatusFromIOError' C API function.> ...
%! tensorflow ('TF_SetStatusFromIOError', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Status parsed to the 'TF_SetStatusFromIOError' C API function.> ...
%! tensorflow ('TF_SetStatusFromIOError', 1, 2, 3);
%!error <tensorflow: 3rd argument must be an integer scalar defining an error_code to be parsed to the 'TF_SetStatusFromIOError' C API function.> ...
%! tensorflow ('TF_SetStatusFromIOError', uint64 (1), 2, 3);
%!error <tensorflow: 4th argument must be a character vector defining the context to be parsed to the 'TF_SetStatusFromIOError' C API function.> ...
%! tensorflow ('TF_SetStatusFromIOError', uint64 (1), int32 (2), 3);

%!error <tensorflow: one extra argument is required for the 'TF_GetCode' C API function.> ...
%! tensorflow ('TF_GetCode');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Status parsed to the 'TF_GetCode' C API function.> ...
%! tensorflow ('TF_GetCode', 1);

%!error <tensorflow: one extra argument is required for the 'TF_Message' C API function.> ...
%! tensorflow ('TF_Message');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Status parsed to the 'TF_Message' C API function.> ...
%! tensorflow ('TF_Message', 1);

  ## ---------------------------------------------------------------------------
  ## C API functions referenced by the TF_TString classdef
  ## ---------------------------------------------------------------------------
%!error <tensorflow: one extra argument is required for the 'TF_LoadTString' OCTAVE function.> ...
%! tensorflow ('TF_LoadTString');
%!error <tensorflow: 2nd argument must be a character vector to be parsed to the 'TF_LoadTString' OCTAVE function.> ...
%! tensorflow ('TF_LoadTString', 1);

%!error <tensorflow: one extra argument is required for the 'TF_SaveTString' OCTAVE function.> ...
%! tensorflow ('TF_SaveTString');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the TString parsed to the 'TF_SaveTString' OCTAVE function.> ...
%! tensorflow ('TF_SaveTString', 1);

%!error <tensorflow: one extra argument is required for the 'TF_StringInit' C API function.> ...
%! tensorflow ('TF_StringInit');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the TString parsed to the 'TF_StringInit' C API function.> ...
%! tensorflow ('TF_StringInit', 1);

%!error <tensorflow: three extra arguments are required for the 'TF_StringCopy' C API function.> ...
%! tensorflow ('TF_StringCopy');
%!error <tensorflow: three extra arguments are required for the 'TF_StringCopy' C API function.> ...
%! tensorflow ('TF_StringCopy', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_StringCopy' C API function.> ...
%! tensorflow ('TF_StringCopy', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the TString parsed to the 'TF_StringCopy' C API function.> ...
%! tensorflow ('TF_StringCopy', 1, 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the source string parsed to the 'TF_StringCopy' C API function.> ...
%! tensorflow ('TF_StringCopy', uint64 (1), 2, 3);
%!error <tensorflow: 4th argument must be an uint64 scalar value defining the size of the source string parsed to the 'TF_StringCopy' C API function.> ...
%! tensorflow ('TF_StringCopy', uint64 (1), "Some text", 3);

%!error <tensorflow: three extra arguments are required for the 'TF_StringAssignView' C API function.> ...
%! tensorflow ('TF_StringAssignView');
%!error <tensorflow: three extra arguments are required for the 'TF_StringAssignView' C API function.> ...
%! tensorflow ('TF_StringAssignView', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_StringAssignView' C API function.> ...
%! tensorflow ('TF_StringAssignView', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the TString parsed to the 'TF_StringAssignView' C API function.> ...
%! tensorflow ('TF_StringAssignView', 1, 2, 3);
%!error <tensorflow: 3rd argument must be a character vector defining the source string parsed to the 'TF_StringAssignView' C API function.> ...
%! tensorflow ('TF_StringAssignView', uint64 (1), 2, 3);
%!error <tensorflow: 4th argument must be an uint64 scalar value defining the size of the source string parsed to the 'TF_StringAssignView' C API function.> ...
%! tensorflow ('TF_StringAssignView', uint64 (1), "Some text", 3);

%!error <tensorflow: one extra argument is required for the 'TF_StringGetDataPointer' C API function.> ...
%! tensorflow ('TF_StringGetDataPointer');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the TString parsed to the 'TF_StringGetDataPointer' C API function.> ...
%! tensorflow ('TF_StringGetDataPointer', 1);

%!error <tensorflow: one extra argument is required for the 'TF_StringGetType' C API function.> ...
%! tensorflow ('TF_StringGetType');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the TString parsed to the 'TF_StringGetType' C API function.> ...
%! tensorflow ('TF_StringGetType', 1);

%!error <tensorflow: one extra argument is required for the 'TF_StringGetSize' C API function.> ...
%! tensorflow ('TF_StringGetSize');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the TString parsed to the 'TF_StringGetSize' C API function.> ...
%! tensorflow ('TF_StringGetSize', 1);

%!error <tensorflow: one extra argument is required for the 'TF_StringGetCapacity' C API function.> ...
%! tensorflow ('TF_StringGetCapacity');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the TString parsed to the 'TF_StringGetCapacity' C API function.> ...
%! tensorflow ('TF_StringGetCapacity', 1);

%!error <tensorflow: one extra argument is required for the 'TF_StringDealloc' C API function.> ...
%! tensorflow ('TF_StringDealloc');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the TString parsed to the 'TF_StringDealloc' C API function.> ...
%! tensorflow ('TF_StringDealloc', 1);

  ## ---------------------------------------------------------------------------
  ## C API functions referenced by the TF_Tensor classdef
  ## ---------------------------------------------------------------------------
%!error <tensorflow: one extra argument is required for the 'TF_LoadTensor' OCTAVE function.> ...
%! tensorflow ('TF_LoadTensor');
%!error <tensorflow: 2nd argument cannot be empty, it must contain non-empty data to be parsed to the 'TF_LoadTensor' OCTAVE function.> ...
%! tensorflow ('TF_LoadTensor', []);
%!error <tensorflow: only a character vector can be loaded into Tensor. For multiple rows of characters use a cellstr array.> ...
%! tensorflow ('TF_LoadTensor', ["a", "b"; "c", "d"]);
%!error <tensorflow: 'cell' type cannot be loaded into Tensor.> ...
%! tensorflow ('TF_LoadTensor', {1, 2, 3, 4});
%!test
%! s.a = 1;
%! fail ("tensorflow ('TF_LoadTensor', s)" ,"tensorflow: 'scalar struct' type cannot be loaded into Tensor.");
%!test
%! s(1).a = 1;
%! s(2).a = 2;
%! fail ("tensorflow ('TF_LoadTensor', s)", "tensorflow: 'struct' type cannot be loaded into Tensor.");
%!error <tensorflow: 'function handle' type cannot be loaded into Tensor.> ...
%! tensorflow ('TF_LoadTensor', @(x) sum (x));

%!error <tensorflow: one extra argument is required for the 'TF_SaveTensor' OCTAVE function.> ...
%! tensorflow ('TF_SaveTensor');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Tensor parsed to the 'TF_SaveTensor' OCTAVE function.> ...
%! tensorflow ('TF_SaveTensor', 1);
%!test
%! tensor = tensorflow ('TF_AllocateTensor', uint32 (11), int64 ([2, 2]), int32 (2), uint64 (4)); # TF_QINT8
%! fail ("tensorflow ('TF_SaveTensor', tensor)", ...
%! "tensorflow: 'TF_QINT8' data type in Tensor is not supported by Octave.");
%! tensorflow ('TF_DeleteTensor', tensor);
%! clear tensor
%!test
%! tensor = tensorflow ('TF_AllocateTensor', uint32 (12), int64 ([2, 2]), int32 (2), uint64 (4)); # TF_QUINT8
%! fail ("tensorflow ('TF_SaveTensor', tensor)", ...
%! "tensorflow: 'TF_QUINT8' data type in Tensor is not supported by Octave.");
%! tensorflow ('TF_DeleteTensor', tensor);
%! clear tensor
%!test
%! tensor = tensorflow ('TF_AllocateTensor', uint32 (13), int64 ([2, 2]), int32 (2), uint64 (16)); # TF_QINT32
%! fail ("tensorflow ('TF_SaveTensor', tensor)", ...
%! "tensorflow: 'TF_QINT32' data type in Tensor is not supported by Octave.");
%! tensorflow ('TF_DeleteTensor', tensor);
%! clear tensor
%!test
%! tensor = tensorflow ('TF_AllocateTensor', uint32 (14), int64 ([2, 2]), int32 (2), uint64 (8)); # TF_BFLOAT16
%! fail ("tensorflow ('TF_SaveTensor', tensor)", ...
%! "tensorflow: 'TF_BFLOAT16' data type in Tensor is not supported by Octave.");
%! tensorflow ('TF_DeleteTensor', tensor);
%! clear tensor
%!test
%! tensor = tensorflow ('TF_AllocateTensor', uint32 (15), int64 ([2, 2]), int32 (2), uint64 (8)); # TF_QINT16
%! fail ("tensorflow ('TF_SaveTensor', tensor)", ...
%! "tensorflow: 'TF_QINT16' data type in Tensor is not supported by Octave.");
%! tensorflow ('TF_DeleteTensor', tensor);
%! clear tensor
%!test
%! tensor = tensorflow ('TF_AllocateTensor', uint32 (16), int64 ([2, 2]), int32 (2), uint64 (8)); # TF_QUINT16
%! fail ("tensorflow ('TF_SaveTensor', tensor)", ...
%! "tensorflow: 'TF_QUINT16' data type in Tensor is not supported by Octave.");
%! tensorflow ('TF_DeleteTensor', tensor);
%! clear tensor
%!test
%! tensor = tensorflow ('TF_AllocateTensor', uint32 (19), int64 ([2, 2]), int32 (2), uint64 (8)); # TF_HALF
%! fail ("tensorflow ('TF_SaveTensor', tensor)", ...
%! "tensorflow: 'TF_HALF' data type in Tensor is not supported by Octave.");
%! tensorflow ('TF_DeleteTensor', tensor);
%! clear tensor
%!test
%! tensor = tensorflow ('TF_AllocateTensor', uint32 (20), int64 ([2, 2]), int32 (2), uint64 (0)); # TF_RESOURCE
%! fail ("tensorflow ('TF_SaveTensor', tensor)", ...
%! "tensorflow: 'TF_RESOURCE' data type in Tensor is not supported by Octave.");
%! tensorflow ('TF_DeleteTensor', tensor);
%! clear tensor
%!test
%! tensor = tensorflow ('TF_AllocateTensor', uint32 (21), int64 ([2, 2]), int32 (2), uint64 (0)); # TF_VARIANT
%! fail ("tensorflow ('TF_SaveTensor', tensor)", ...
%! "tensorflow: 'TF_VARIANT' data type in Tensor is not supported by Octave.");
%! tensorflow ('TF_DeleteTensor', tensor);
%! clear tensor
%!test
%! tensor = tensorflow ('TF_AllocateTensor', uint32 (24), int64 ([2, 2]), int32 (2), uint64 (4)); # TF_FLOAT8_E5M2
%! fail ("tensorflow ('TF_SaveTensor', tensor)", ...
%! "tensorflow: 'TF_FLOAT8_E5M2' data type in Tensor is not supported by Octave.");
%! tensorflow ('TF_DeleteTensor', tensor);
%! clear tensor
%!test
%! tensor = tensorflow ('TF_AllocateTensor', uint32 (25), int64 ([2, 2]), int32 (2), uint64 (4)); # TF_FLOAT8_E4M3FN
%! fail ("tensorflow ('TF_SaveTensor', tensor)", ...
%! "tensorflow: 'TF_FLOAT8_E4M3FN' data type in Tensor is not supported by Octave.");
%! tensorflow ('TF_DeleteTensor', tensor);
%! clear tensor
%!test
%! tensor = tensorflow ('TF_AllocateTensor', uint32 (29), int64 ([2, 2]), int32 (2), uint64 (4)); # TF_INT4
%! fail ("tensorflow ('TF_SaveTensor', tensor)", ...
%! "tensorflow: 'TF_INT4' data type in Tensor is not supported by Octave.");
%! tensorflow ('TF_DeleteTensor', tensor);
%! clear tensor
%!test
%! tensor = tensorflow ('TF_AllocateTensor', uint32 (30), int64 ([2, 2]), int32 (2), uint64 (4)); # TF_UINT4
%! fail ("tensorflow ('TF_SaveTensor', tensor)", ...
%! "tensorflow: 'TF_UINT4' data type in Tensor is not supported by Octave.");
%! tensorflow ('TF_DeleteTensor', tensor);
%! clear tensor

%!error <tensorflow: five extra arguments are required for the 'TF_NewTensor' C API function.> ...
%! tensorflow ('TF_NewTensor');
%!error <tensorflow: five extra arguments are required for the 'TF_NewTensor' C API function.> ...
%! tensorflow ('TF_NewTensor', 1);
%!error <tensorflow: five extra arguments are required for the 'TF_NewTensor' C API function.> ...
%! tensorflow ('TF_NewTensor', 1, 2);
%!error <tensorflow: five extra arguments are required for the 'TF_NewTensor' C API function.> ...
%! tensorflow ('TF_NewTensor', 1, 2, 3);
%!error <tensorflow: five extra arguments are required for the 'TF_NewTensor' C API function.> ...
%! tensorflow ('TF_NewTensor', 1, 2, 3, 4);
%!error <tensorflow: 2nd argument must be an uint32 scalar indexing the appropriate TF_DataType to be parsed to the 'TF_NewTensor' C API function.> ...
%! tensorflow ('TF_NewTensor', 1, 2, 3, 4, 5);
%!error <tensorflow: 3rd argument must be an int64 scalar or vector defining the size of the dimensions of the data to be parsed to the 'TF_NewTensor' C API function.> ...
%! tensorflow ('TF_NewTensor', uint32 (1), 2, 3, 4, 5);
%!error <tensorflow: 4th argument must be an int32 scalar defining the number of the dimensions of the data to be parsed to the 'TF_NewTensor' C API function.> ...
%! tensorflow ('TF_NewTensor', uint32 (1), int64 (2), 3, 4, 5);
%!error <tensorflow: 5th argument must be an uint64 scalar pointer to the data structure to be parsed to the 'TF_NewTensor' C API function.> ...
%! tensorflow ('TF_NewTensor', uint32 (1), int64 (2), int32 (3), 4, 5);
%!error <tensorflow: 6th argument must be an uint64 scalar defining the bytesize of the data structure to be parsed to the 'TF_NewTensor' C API function.> ...
%! tensorflow ('TF_NewTensor', uint32 (1), int64 (2), int32 (3), uint64 (4), 5);

%!error <tensorflow: four extra arguments are required for the 'TF_AllocateTensor' C API function.> ...
%! tensorflow ('TF_AllocateTensor');
%!error <tensorflow: four extra arguments are required for the 'TF_AllocateTensor' C API function.> ...
%! tensorflow ('TF_AllocateTensor', 1);
%!error <tensorflow: four extra arguments are required for the 'TF_AllocateTensor' C API function.> ...
%! tensorflow ('TF_AllocateTensor', 1, 2);
%!error <tensorflow: four extra arguments are required for the 'TF_AllocateTensor' C API function.> ...
%! tensorflow ('TF_AllocateTensor', 1, 2, 3);
%!error <tensorflow: 2nd argument must be an uint32 scalar indexing the appropriate TF_DataType to be parsed to the 'TF_AllocateTensor' C API function.> ...
%! tensorflow ('TF_AllocateTensor', 1, 2, 3, 4);
%!error <tensorflow: 3rd argument must be an int64 scalar or vector defining the size of the dimensions of the data to be parsed to the 'TF_AllocateTensor' C API function.> ...
%! tensorflow ('TF_AllocateTensor', uint32 (1), 2, 3, 4);
%!error <tensorflow: 4th argument must be an int32 scalar defining the number of the dimensions of the data to be parsed to the 'TF_AllocateTensor' C API function.> ...
%! tensorflow ('TF_AllocateTensor', uint32 (1), int64 (2), 3, 4);
%!error <tensorflow: 5th argument must be an uint64 scalar defining the size of memory to be allocated by the 'TF_AllocateTensor' C API function.> ...
%! tensorflow ('TF_AllocateTensor', uint32 (1), int64 (2), int32 (3), 4);

%!error <tensorflow: one extra argument is required for the 'TF_TensorMaybeMove' C API function.> ...
%! tensorflow ('TF_TensorMaybeMove');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Tensor parsed to the 'TF_TensorMaybeMove' C API function.> ...
%! tensorflow ('TF_TensorMaybeMove', 1);

%!error <tensorflow: one extra argument is required for the 'TF_DeleteTensor' C API function.> ...
%! tensorflow ('TF_DeleteTensor');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Tensor parsed to the 'TF_DeleteTensor' C API function.> ...
%! tensorflow ('TF_DeleteTensor', 1);

%!error <tensorflow: one extra argument is required for the 'TF_TensorType' C API function.> ...
%! tensorflow ('TF_TensorType');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Tensor parsed to the 'TF_TensorType' C API function.> ...
%! tensorflow ('TF_TensorType', 1);

%!error <tensorflow: three extra arguments are required for the 'TF_SetShape' C API function.> ...
%! tensorflow ('TF_SetShape');
%!error <tensorflow: three extra arguments are required for the 'TF_SetShape' C API function.> ...
%! tensorflow ('TF_SetShape', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_SetShape' C API function.> ...
%! tensorflow ('TF_SetShape', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Tensor parsed to the 'TF_SetShape' C API function.> ...
%! tensorflow ('TF_SetShape', 1, 2, 3);
%!error <tensorflow: 3rd argument must be an int64 scalar or vector defining the size of the dimensions to be parsed to the 'TF_SetShape' C API function.> ...
%! tensorflow ('TF_SetShape', uint64 (1), 2, 3);
%!error <tensorflow: 4th argument must be an int32 scalar defining the number of the dimensions to be parsed to the 'TF_SetShape' C API function.> ...
%! tensorflow ('TF_SetShape', uint64 (1), int64 (2), 3);

%!error <tensorflow: one extra argument is required for the 'TF_NumDims' C API function.> ...
%! tensorflow ('TF_NumDims');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Tensor parsed to the 'TF_NumDims' C API function.> ...
%! tensorflow ('TF_NumDims', 1);

%!error <tensorflow: two extra arguments are required for the 'TF_Dim' C API function.> ...
%! tensorflow ('TF_Dim');
%!error <tensorflow: two extra arguments are required for the 'TF_Dim' C API function.> ...
%! tensorflow ('TF_Dim', 1);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Tensor parsed to the 'TF_Dim' C API function.> ...
%! tensorflow ('TF_Dim', 1, 2);
%!error <tensorflow: 3rd argument must be an uint32 scalar indexing the dimension to be parsed to the 'TF_Dim' C API function.> ...
%! tensorflow ('TF_Dim', uint64 (1), 2);
%!test
%! tensor = tensorflow ('TF_LoadTensor', ones (2));
%! fail ("tensorflow ('TF_Dim', tensor, int32 (3))", ...
%! "tensorflow: you are trying to index non existing dimension.");
%! tensorflow ('TF_DeleteTensor', tensor);
%! clear tensor

%!error <tensorflow: one extra argument is required for the 'TF_TensorByteSize' C API function.> ...
%! tensorflow ('TF_TensorByteSize');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Tensor parsed to the 'TF_TensorByteSize' C API function.> ...
%! tensorflow ('TF_TensorByteSize', 1);

%!error <tensorflow: one extra argument is required for the 'TF_TensorData' C API function.> ...
%! tensorflow ('TF_TensorData');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Tensor parsed to the 'TF_TensorData' C API function.> ...
%! tensorflow ('TF_TensorData', 1);

%!error <tensorflow: three extra arguments are required for the 'TF_TensorFromProto' C API function.> ...
%! tensorflow ('TF_TensorFromProto');
%!error <tensorflow: three extra arguments are required for the 'TF_TensorFromProto' C API function.> ...
%! tensorflow ('TF_TensorFromProto', 1);
%!error <tensorflow: three extra arguments are required for the 'TF_TensorFromProto' C API function.> ...
%! tensorflow ('TF_TensorFromProto', 1, 2);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Buffer parsed to the 'TF_TensorFromProto' C API function.> ...
%! tensorflow ('TF_TensorFromProto', 1, 2, 3);
%!error <tensorflow: 3rd argument must be an uint64 scalar pointer to the Tensor parsed to the 'TF_TensorFromProto' C API function.> ...
%! tensorflow ('TF_TensorFromProto', uint64 (1), 2, 3);
%!error <tensorflow: 4th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_TensorFromProto' C API function.> ...
%! tensorflow ('TF_TensorFromProto', uint64 (1), uint64 (2), 3);

%!error <tensorflow: one extra argument is required for the 'TF_TensorElementCount' C API function.> ...
%! tensorflow ('TF_TensorElementCount');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Tensor parsed to the 'TF_TensorElementCount' C API function.> ...
%! tensorflow ('TF_TensorElementCount', 1);

%!error <tensorflow: six extra arguments are required for the 'TF_TensorBitcastFrom' C API function.> ...
%! tensorflow ('TF_TensorBitcastFrom');
%!error <tensorflow: six extra arguments are required for the 'TF_TensorBitcastFrom' C API function.> ...
%! tensorflow ('TF_TensorBitcastFrom', 1);
%!error <tensorflow: six extra arguments are required for the 'TF_TensorBitcastFrom' C API function.> ...
%! tensorflow ('TF_TensorBitcastFrom', 1, 2);
%!error <tensorflow: six extra arguments are required for the 'TF_TensorBitcastFrom' C API function.> ...
%! tensorflow ('TF_TensorBitcastFrom', 1, 2, 3);
%!error <tensorflow: six extra arguments are required for the 'TF_TensorBitcastFrom' C API function.> ...
%! tensorflow ('TF_TensorBitcastFrom', 1, 2, 3, 4);
%!error <tensorflow: six extra arguments are required for the 'TF_TensorBitcastFrom' C API function.> ...
%! tensorflow ('TF_TensorBitcastFrom', 1, 2, 3, 4, 5);
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the source Tensor parsed to the 'TF_TensorBitcastFrom' C API function.> ...
%! tensorflow ('TF_TensorBitcastFrom', 1, 2, 3, 4, 5, 6);
%!error <tensorflow: 3rd argument must be an uint32 scalar value indexing the appropriate TF_DataType to be parsed to the 'TF_TensorBitcastFrom' C API function.> ...
%! tensorflow ('TF_TensorBitcastFrom', uint64 (1), 2, 3, 4, 5, 6);
%!error <tensorflow: 4th argument must be an uint64 scalar pointer to the target Tensor parsed to the 'TF_TensorBitcastFrom' C API function.> ...
%! tensorflow ('TF_TensorBitcastFrom', uint64 (1), uint32 (2), 3, 4, 5, 6);
%!error <tensorflow: 5th argument must be an int64 scalar or vector defining the size of the dimensions of the target Tensor parsed to the 'TF_TensorBitcastFrom' C API function.> ...
%! tensorflow ('TF_TensorBitcastFrom', uint64 (1), uint32 (2), uint64 (3), 4, 5, 6);
%!error <tensorflow: 6th argument must be an int32 scalar defining the number of the dimensions of the target Tensor parsed to the 'TF_TensorBitcastFrom' C API function.> ...
%! tensorflow ('TF_TensorBitcastFrom', uint64 (1), uint32 (2), uint64 (3), int64 (4), 5, 6);
%!error <tensorflow: 7th argument must be an uint64 scalar pointer to the Status parsed to the 'TF_TensorBitcastFrom' C API function.> ...
%! tensorflow ('TF_TensorBitcastFrom', uint64 (1), uint32 (2), uint64 (3), int64 (4), int32 (5), 6);

%!error <tensorflow: one extra argument is required for the 'TF_TensorIsAligned' C API function.> ...
%! tensorflow ('TF_TensorIsAligned');
%!error <tensorflow: 2nd argument must be an uint64 scalar pointer to the Tensor parsed to the 'TF_TensorIsAligned' C API function.> ...
%! tensorflow ('TF_TensorIsAligned', 1);
*/
