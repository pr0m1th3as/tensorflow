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

classdef TF_Session < handle
  ## -*- texinfo -*-
  ## @deftp {tensorflow} TF_Session
  ##
  ## A TensorFlow Session, which executes the operations of a Graph.
  ##
  ## A @code{TF_Session} owns the Session it wraps, closes and releases it when
  ## the object is destroyed, and keeps a reference to its @code{TF_Graph} so
  ## that the Graph outlives it whatever order the variables are cleared in.
  ##
  ## Operations are named by strings of the form @qcode{'name'} or
  ## @qcode{'name:index'}, where @var{index} is the zero based output index of
  ## the operation and defaults to 0.
  ##
  ## @end deftp

  properties (SetAccess = private)

    ## -*- texinfo -*-
    ## @deftp {TF_Session} {property} Pointer
    ## The @code{uint64} pointer to the Session, for use with the @code{OCT}
    ## interface.  It is 0 once the Session has been released.
    ## @end deftp
    Pointer = uint64 (0);

    ## -*- texinfo -*-
    ## @deftp {TF_Session} {property} Graph
    ## The @code{TF_Graph} the Session executes.
    ## @end deftp
    Graph = [];

  endproperties

  methods (Access = public)

    ## -*- texinfo -*-
    ## @deftypefn  {TF_Session} {@var{obj} =} TF_Session (@var{graph})
    ##
    ## Create a Session executing the operations of @var{graph}, which must be a
    ## @code{TF_Graph} object.
    ##
    ## @end deftypefn
    function this = TF_Session (graph)

      if (nargin == 0)
        return;
      endif
      if (nargin != 1)
        print_usage ();
      endif
      if (! isa (graph, "TF_Graph"))
        error ("TF_Session: GRAPH must be a TF_Graph object.");
      endif
      opts = tensorflow ("TF_NewSessionOptions");
      status = tensorflow ("TF_NewStatus");
      ptr = tensorflow ("TF_NewSession", graph.Pointer, opts, status);
      tensorflow ("TF_DeleteSessionOptions", opts);
      __tf_check__ (status, "TF_Session");
      this.Pointer = ptr;
      this.Graph = graph;

    endfunction

    ## -*- texinfo -*-
    ## @deftypefn  {TF_Session} {@var{out} =} run (@var{obj}, @var{inputs}, @var{values}, @var{outputs})
    ##
    ## Execute the Graph and return the requested outputs.
    ##
    ## @var{inputs} names the operations the values are fed to and @var{outputs}
    ## names the operations whose values are wanted, both either a character
    ## vector or a cellstr vector, each name optionally carrying an output index
    ## as @qcode{'name:index'}.  @var{values} holds the values fed to
    ## @var{inputs}, either an Octave array, a @code{TF_Tensor}, or a cell array
    ## of either, and must have as many elements as @var{inputs}.
    ##
    ## @var{out} is an Octave array when a single output is requested, and a
    ## cell array of them otherwise.
    ##
    ## @end deftypefn
    function out = run (this, inputs, values, outputs)

      if (nargin != 4)
        print_usage ();
      endif
      this.assertValid ("TF_Session.run");
      inputs = TF_Session.asCellstr (inputs, "INPUTS", "TF_Session.run");
      outputs = TF_Session.asCellstr (outputs, "OUTPUTS", "TF_Session.run");
      if (! iscell (values))
        values = {values};
      endif
      if (numel (values) != numel (inputs))
        error (["TF_Session.run: VALUES must have as many elements as", ...
                " INPUTS."]);
      endif
      ## Resolve every name to an Output, and every value to a Tensor.  The
      ## Tensors built here are owned locally and released before returning,
      ## while those handed in by the caller are left alone.
      in_ptr = zeros (1, numel (inputs), "uint64");
      val_ptr = zeros (1, numel (values), "uint64");
      own = false (1, numel (values));
      out_ptr = zeros (1, numel (outputs), "uint64");
      unwind_protect
        for i = 1:numel (inputs)
          in_ptr(i) = this.resolveOutput (inputs{i}, "TF_Session.run");
          if (isa (values{i}, "TF_Tensor"))
            val_ptr(i) = values{i}.Pointer;
          else
            val_ptr(i) = tensorflow ("TF_LoadTensor", values{i});
            own(i) = true;
          endif
        endfor
        for i = 1:numel (outputs)
          out_ptr(i) = this.resolveOutput (outputs{i}, "TF_Session.run");
        endfor
        status = tensorflow ("TF_NewStatus");
        res = tensorflow ("TF_SessionRun", this.Pointer, uint64 (0), ...
                          in_ptr, val_ptr, out_ptr, uint64 ([]), ...
                          uint64 (0), status);
        __tf_check__ (status, "TF_Session.run");
        out = cell (1, numel (res));
        for i = 1:numel (res)
          out{i} = tensorflow ("TF_SaveTensor", res(i));
          tensorflow ("TF_DeleteTensor", res(i));
        endfor
        if (numel (out) == 1)
          out = out{1};
        endif
      unwind_protect_cleanup
        for i = 1:numel (val_ptr)
          if (own(i) && val_ptr(i) != 0)
            tensorflow ("TF_DeleteTensor", val_ptr(i));
          endif
        endfor
        for i = 1:numel (in_ptr)
          if (in_ptr(i) != 0)
            tensorflow ("TF_DeleteOutput", in_ptr(i));
          endif
        endfor
        for i = 1:numel (out_ptr)
          if (out_ptr(i) != 0)
            tensorflow ("TF_DeleteOutput", out_ptr(i));
          endif
        endfor
      end_unwind_protect

    endfunction

    ## -*- texinfo -*-
    ## @deftypefn  {TF_Session} {@var{s} =} devices (@var{obj})
    ##
    ## Return the devices the Session can execute on as a struct array with
    ## fields @qcode{'Name'}, @qcode{'Type'}, @qcode{'MemoryBytes'} and
    ## @qcode{'Incarnation'}.
    ##
    ## @end deftypefn
    function s = devices (this)

      if (nargin != 1)
        print_usage ();
      endif
      this.assertValid ("TF_Session.devices");
      status = tensorflow ("TF_NewStatus");
      list = tensorflow ("TF_SessionListDevices", this.Pointer, status);
      __tf_check__ (status, "TF_Session.devices");
      unwind_protect
        n = tensorflow ("TF_DeviceListCount", list);
        s = struct ("Name", cell (1, n), "Type", cell (1, n), ...
                    "MemoryBytes", cell (1, n), "Incarnation", cell (1, n));
        for i = 1:n
          status = tensorflow ("TF_NewStatus");
          idx = int32 (i - 1);
          s(i).Name = tensorflow ("TF_DeviceListName", list, idx, status);
          s(i).Type = tensorflow ("TF_DeviceListType", list, idx, status);
          s(i).MemoryBytes = tensorflow ("TF_DeviceListMemoryBytes", list, idx, status);
          s(i).Incarnation = tensorflow ("TF_DeviceListIncarnation", list, idx, status);
          __tf_check__ (status, "TF_Session.devices");
        endfor
      unwind_protect_cleanup
        tensorflow ("TF_DeleteDeviceList", list);
      end_unwind_protect

    endfunction

    ## -*- texinfo -*-
    ## @deftypefn  {TF_Session} {} delete (@var{obj})
    ##
    ## Close and release the Session.
    ##
    ## This is called automatically when no variable refers to the object any
    ## more, and calling it a second time does nothing.
    ##
    ## @end deftypefn
    function delete (this)

      if (this.Pointer != 0)
        status = tensorflow ("TF_NewStatus");
        tensorflow ("TF_CloseSession", this.Pointer, status);
        tensorflow ("TF_DeleteSession", this.Pointer, status);
        tensorflow ("TF_DeleteStatus", status);
      endif
      this.Pointer = uint64 (0);
      this.Graph = [];

    endfunction

  endmethods

  methods (Access = private)

    ## Build an Output from a 'name' or 'name:index' string.  The caller owns
    ## the returned pointer.
    function ptr = resolveOutput (this, name, caller)
      idx = 0;
      colon = strfind (name, ":");
      if (! isempty (colon))
        tail = name(colon(end)+1:end);
        num = str2double (tail);
        if (! isnan (num) && num == fix (num) && num >= 0)
          idx = num;
          name = name(1:colon(end)-1);
        endif
      endif
      oper = this.Graph.operationByName (name, caller);
      nout = tensorflow ("TF_OperationNumOutputs", oper);
      if (idx >= double (nout))
        error ("%s: operation '%s' has %d output(s), index %d requested.", ...
               caller, name, double (nout), idx);
      endif
      ptr = tensorflow ("TF_NewOutput", oper, int32 (idx));
    endfunction

    function assertValid (this, caller)
      if (this.Pointer == 0)
        error ("%s: the Session has already been released.", caller);
      endif
    endfunction

  endmethods

  methods (Static, Access = public)

    ## -*- texinfo -*-
    ## @deftypefn  {TF_Session} {@var{obj} =} TF_Session.fromSavedModel (@var{dirname})
    ## @deftypefnx {TF_Session} {@var{obj} =} TF_Session.fromSavedModel (@var{dirname}, @var{tags})
    ##
    ## Load a SavedModel from the directory @var{dirname} and return a Session
    ## over the Graph it was exported with.
    ##
    ## @var{tags} identifies the MetaGraphDef to load, either a character vector
    ## or a cellstr vector, and defaults to @qcode{@{'serve'@}}.
    ##
    ## @end deftypefn
    function this = fromSavedModel (dirname, tags)

      if (nargin < 1 || nargin > 2)
        print_usage ();
      endif
      if (nargin < 2)
        tags = {"serve"};
      endif
      if (! (ischar (dirname) && isrow (dirname)))
        error (["TF_Session.fromSavedModel: DIRNAME must be a character", ...
                " vector."]);
      endif
      if (! isfolder (dirname))
        error ("TF_Session.fromSavedModel: '%s' is not a directory.", dirname);
      endif
      tags = TF_Session.asCellstr (tags, "TAGS", "TF_Session.fromSavedModel");
      graph = TF_Graph ();
      opts = tensorflow ("TF_NewSessionOptions");
      status = tensorflow ("TF_NewStatus");
      ptr = tensorflow ("TF_LoadSessionFromSavedModel", opts, uint64 (0), ...
                        dirname, tags, graph.Pointer, uint64 (0), status);
      tensorflow ("TF_DeleteSessionOptions", opts);
      __tf_check__ (status, "TF_Session.fromSavedModel");
      this = TF_Session ();
      this.Pointer = ptr;
      this.Graph = graph;

    endfunction

  endmethods

  methods (Static, Access = private)

    ## Accept a character vector or a cellstr vector and return a cellstr row
    function c = asCellstr (val, argname, caller)
      if (ischar (val) && isrow (val))
        c = {val};
      elseif (iscellstr (val))
        c = val(:).';
      else
        error ("%s: %s must be a character vector or a cellstr vector.", ...
               caller, argname);
      endif
    endfunction

  endmethods

endclassdef
