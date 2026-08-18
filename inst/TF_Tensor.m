## Copyright (C) 2026 Andreas Bertsatos <abertsatos@biol.uoa.gr>
##
## This file is part of the tensorflow package for GNU Octave.
##
## This program is free software; you can redistribute it and/or modify it under
## the terms of the GNU General Public License as published by the Free Software
## Foundation; either version 3 of the License, or (at your option) any later
## version.
##
## This program is distributed in the hope that it will be useful, but WITHOUT
## ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
## FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
## more details.
##
## You should have received a copy of the GNU General Public License along with
## this program; if not, see <http://www.gnu.org/licenses/>.

classdef TF_Tensor < handle
  ## -*- texinfo -*-
  ## @deftp {tensorflow} TF_Tensor
  ##
  ## A TensorFlow Tensor holding a copy of an Octave array.
  ##
  ## A @code{TF_Tensor} owns the Tensor it wraps and releases it when the object
  ## is destroyed, so it does not have to be freed by hand.  Being a handle
  ## class, assigning it to another variable refers to the same Tensor rather
  ## than copying it, and the Tensor is released once no variable refers to it
  ## any more.
  ##
  ## The elements are repositioned on the way in and on the way out, since
  ## Octave stores arrays column major and TensorFlow stores them row major, so
  ## the shape and the element positions are those of the Octave array in both
  ## directions.
  ##
  ## @end deftp

  properties (SetAccess = private)

    ## -*- texinfo -*-
    ## @deftp {TF_Tensor} {property} Pointer
    ## The @code{uint64} pointer to the Tensor, for use with the @code{OCT}
    ## interface.  It is 0 once the Tensor has been released.
    ## @end deftp
    Pointer = uint64 (0);

  endproperties

  properties (Access = private)

    ## Whether this object is responsible for releasing the Tensor
    Owned = true;

  endproperties

  methods (Access = public)

    ## -*- texinfo -*-
    ## @deftypefn  {TF_Tensor} {@var{obj} =} TF_Tensor (@var{data})
    ##
    ## Create a Tensor holding a copy of an Octave array.
    ##
    ## @var{data} must be a non-empty numeric, logical, or character array of a
    ## data type supported by TensorFlow.  The values are copied, so @var{data}
    ## may be modified or cleared afterwards without affecting the Tensor.
    ##
    ## Called without arguments it returns an object referring to no Tensor,
    ## which every method rejects.
    ##
    ## @end deftypefn
    function this = TF_Tensor (data)

      if (nargin == 0)
        return;
      endif
      if (nargin != 1)
        print_usage ();
      endif
      if (isempty (data))
        error ("TF_Tensor: DATA must not be empty.");
      endif
      this.Pointer = tensorflow ("TF_LoadTensor", data);

    endfunction

    ## -*- texinfo -*-
    ## @deftypefn  {TF_Tensor} {@var{data} =} value (@var{obj})
    ##
    ## Return the contents of the Tensor as an Octave array.
    ##
    ## @end deftypefn
    function data = value (this)

      if (nargin != 1)
        print_usage ();
      endif
      this.assertValid ("TF_Tensor.value");
      data = tensorflow ("TF_SaveTensor", this.Pointer);

    endfunction

    ## -*- texinfo -*-
    ## @deftypefn  {TF_Tensor} {@var{sz} =} shape (@var{obj})
    ##
    ## Return the size of the Tensor as a row vector.
    ##
    ## A Tensor of no dimensions, which holds a single value, reports a size of
    ## @code{[1, 1]}, and a Tensor of one dimension reports @code{[1, N]}, so
    ## that the reported size is always that of the corresponding Octave array.
    ##
    ## @end deftypefn
    function sz = shape (this)

      if (nargin != 1)
        print_usage ();
      endif
      this.assertValid ("TF_Tensor.shape");
      nd = double (tensorflow ("TF_NumDims", this.Pointer));
      if (nd == 0)
        sz = [1, 1];
      elseif (nd == 1)
        sz = [1, double(tensorflow ("TF_Dim", this.Pointer, int32 (1)))];
      else
        sz = zeros (1, nd);
        for i = 1:nd
          sz(i) = double (tensorflow ("TF_Dim", this.Pointer, int32 (i)));
        endfor
      endif

    endfunction

    ## -*- texinfo -*-
    ## @deftypefn  {TF_Tensor} {@var{n} =} numElements (@var{obj})
    ##
    ## Return the number of elements held by the Tensor.
    ##
    ## It is deliberately not named @code{numel}, which Octave uses when
    ## resolving an indexing expression on an object.
    ##
    ## @end deftypefn
    function n = numElements (this)

      if (nargin != 1)
        print_usage ();
      endif
      this.assertValid ("TF_Tensor.numElements");
      n = double (tensorflow ("TF_TensorElementCount", this.Pointer));

    endfunction

    ## -*- texinfo -*-
    ## @deftypefn  {TF_Tensor} {@var{name} =} dataType (@var{obj})
    ##
    ## Return the name of the TensorFlow data type of the Tensor.
    ##
    ## @end deftypefn
    function name = dataType (this)

      if (nargin != 1)
        print_usage ();
      endif
      this.assertValid ("TF_Tensor.dataType");
      name = tensorflow ("TF_DataTypeName", ...
                         tensorflow ("TF_TensorType", this.Pointer));

    endfunction

    ## -*- texinfo -*-
    ## @deftypefn  {TF_Tensor} {} delete (@var{obj})
    ##
    ## Release the Tensor.
    ##
    ## This is called automatically when no variable refers to the object any
    ## more, and calling it a second time does nothing.
    ##
    ## @end deftypefn
    function delete (this)

      if (this.Pointer != 0 && this.Owned)
        tensorflow ("TF_DeleteTensor", this.Pointer);
      endif
      this.Pointer = uint64 (0);

    endfunction

  endmethods

  methods (Access = private)

    function assertValid (this, caller)
      if (this.Pointer == 0)
        error ("%s: the Tensor has already been released.", caller);
      endif
    endfunction

  endmethods

  methods (Static, Hidden)

    ## Wrap a Tensor pointer that came from the OCT interface.  OWNED tells
    ## whether this object becomes responsible for releasing it.
    function this = fromPointer (ptr, owned)
      if (nargin < 2)
        owned = true;
      endif
      this = TF_Tensor ();
      this.Pointer = uint64 (ptr);
      this.Owned = logical (owned);
    endfunction

  endmethods

endclassdef
