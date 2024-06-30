## Makefile for compiling and linking tensorflow octave
## interface to the C API of the tensorflow library

all:
	$(MKOCTFILE) tensorflow.cc \
               OCT_TF_Buffer.cc \
               OCT_TF_DataType.cc \
               OCT_TF_Graph.cc \
               OCT_TF_Input.cc \
               OCT_TF_Operation.cc \
               OCT_TF_OperationDescription.cc \
               OCT_TF_Output.cc \
               OCT_TF_Status.cc \
               OCT_TF_String.cc \
               OCT_TF_Tensor.cc \
               -ltensorflow
