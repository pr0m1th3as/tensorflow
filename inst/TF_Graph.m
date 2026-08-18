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

classdef TF_Graph < handle
  ## -*- texinfo -*-
  ## @deftp {tensorflow} TF_Graph
  ##
  ## A TensorFlow Graph, holding the operations a Session executes.
  ##
  ## A @code{TF_Graph} owns the Graph it wraps and releases it when the object
  ## is destroyed.  A @code{TF_Session} keeps a reference to the Graph it was
  ## created over, so a Graph is never released while a Session still needs it,
  ## whatever order the variables are cleared in.
  ##
  ## @end deftp

  properties (SetAccess = private)

    ## -*- texinfo -*-
    ## @deftp {TF_Graph} {property} Pointer
    ## The @code{uint64} pointer to the Graph, for use with the @code{OCT}
    ## interface.  It is 0 once the Graph has been released.
    ## @end deftp
    Pointer = uint64 (0);

  endproperties

  methods (Access = public)

    ## -*- texinfo -*-
    ## @deftypefn  {TF_Graph} {@var{obj} =} TF_Graph ()
    ##
    ## Create an empty Graph.
    ##
    ## @end deftypefn
    function this = TF_Graph ()

      this.Pointer = tensorflow ("TF_NewGraph");

    endfunction

    ## -*- texinfo -*-
    ## @deftypefn  {TF_Graph} {@var{names} =} operationNames (@var{obj})
    ##
    ## Return the name of every operation in the Graph as a cellstr row vector.
    ##
    ## @end deftypefn
    function names = operationNames (this)

      if (nargin != 1)
        print_usage ();
      endif
      names = this.operationField ("TF_OperationName");

    endfunction

    ## -*- texinfo -*-
    ## @deftypefn  {TF_Graph} {@var{types} =} operationTypes (@var{obj})
    ##
    ## Return the type of every operation in the Graph as a cellstr row vector,
    ## in the same order as @code{operationNames}.
    ##
    ## @end deftypefn
    function types = operationTypes (this)

      if (nargin != 1)
        print_usage ();
      endif
      types = this.operationField ("TF_OperationOpType");

    endfunction

    ## -*- texinfo -*-
    ## @deftypefn  {TF_Graph} {@var{tf} =} hasOperation (@var{obj}, @var{name})
    ##
    ## Return true if the Graph holds an operation named @var{name}.
    ##
    ## @end deftypefn
    function tf = hasOperation (this, name)

      if (nargin != 2)
        print_usage ();
      endif
      this.assertValid ("TF_Graph.hasOperation");
      if (! (ischar (name) && isrow (name)))
        error ("TF_Graph.hasOperation: NAME must be a character vector.");
      endif
      tf = tensorflow ("TF_GraphOperationByName", this.Pointer, name) != 0;

    endfunction

    ## -*- texinfo -*-
    ## @deftypefn  {TF_Graph} {@var{n} =} numOutputs (@var{obj}, @var{name})
    ##
    ## Return the number of outputs of the operation named @var{name}.
    ##
    ## @end deftypefn
    function n = numOutputs (this, name)

      if (nargin != 2)
        print_usage ();
      endif
      n = double (tensorflow ("TF_OperationNumOutputs", ...
                              this.operationByName (name, "TF_Graph.numOutputs")));

    endfunction

    ## -*- texinfo -*-
    ## @deftypefn  {TF_Graph} {} delete (@var{obj})
    ##
    ## Release the Graph.
    ##
    ## This is called automatically when no variable refers to the object any
    ## more, and calling it a second time does nothing.
    ##
    ## @end deftypefn
    function delete (this)

      if (this.Pointer != 0)
        tensorflow ("TF_DeleteGraph", this.Pointer);
      endif
      this.Pointer = uint64 (0);

    endfunction

  endmethods

  methods (Hidden)

    ## Return the pointer to the named operation, raising if it is absent
    function ptr = operationByName (this, name, caller)
      this.assertValid (caller);
      if (! (ischar (name) && isrow (name)))
        error ("%s: NAME must be a character vector.", caller);
      endif
      ptr = tensorflow ("TF_GraphOperationByName", this.Pointer, name);
      if (ptr == 0)
        error ("%s: the Graph holds no operation named '%s'.", caller, name);
      endif
    endfunction

  endmethods

  methods (Access = private)

    ## Apply an OCT interface call returning a string to every operation
    function out = operationField (this, call)
      this.assertValid (["TF_Graph." call]);
      opers = tensorflow ("TF_GraphOperations", this.Pointer);
      out = cell (1, numel (opers));
      for i = 1:numel (opers)
        out{i} = tensorflow (call, opers(i));
      endfor
    endfunction

    function assertValid (this, caller)
      if (this.Pointer == 0)
        error ("%s: the Graph has already been released.", caller);
      endif
    endfunction

  endmethods

  methods (Static, Hidden)

    ## Wrap a Graph pointer that came from the OCT interface
    function this = fromPointer (ptr)
      this = TF_Graph ();
      tensorflow ("TF_DeleteGraph", this.Pointer);
      this.Pointer = uint64 (ptr);
    endfunction

  endmethods

endclassdef
