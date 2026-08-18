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

classdef TFModel < handle
  ## -*- texinfo -*-
  ## @deftp {tensorflow} TFModel
  ##
  ## A trained TensorFlow model loaded from a SavedModel directory, for running
  ## inference.
  ##
  ## @example
  ## @group
  ## model = TFModel ("path/to/saved_model");
  ## y = model.predict (x);
  ## @end group
  ## @end example
  ##
  ## The operations feeding and reading the model are found by inspecting the
  ## Graph, following the names @code{tf.saved_model.save} gives them: the
  ## inputs are the placeholders named @qcode{'serving_default_@var{name}'} and
  ## the output is the operation named @qcode{'StatefulPartitionedCall'}.  Both
  ## are reported by the @qcode{'InputNames'} and @qcode{'OutputNames'}
  ## properties and can be given explicitly to the constructor when a model
  ## does not follow those names.
  ##
  ## Signature names are not read from the SavedModel itself, which would mean
  ## decoding the MetaGraphDef, so a model exported some other way may need its
  ## operation names supplied.  Inspect them with
  ## @code{@var{model}.Session.Graph.operationNames ()}.
  ##
  ## @end deftp

  properties (SetAccess = private)

    ## -*- texinfo -*-
    ## @deftp {TFModel} {property} Directory
    ## The directory the SavedModel was loaded from.
    ## @end deftp
    Directory = "";

    ## -*- texinfo -*-
    ## @deftp {TFModel} {property} Tags
    ## The tags the MetaGraphDef was identified by.
    ## @end deftp
    Tags = {};

    ## -*- texinfo -*-
    ## @deftp {TFModel} {property} InputNames
    ## The operations the inputs are fed to, as a cellstr row vector.
    ## @end deftp
    InputNames = {};

    ## -*- texinfo -*-
    ## @deftp {TFModel} {property} OutputNames
    ## The operations the outputs are read from, as a cellstr row vector.
    ## @end deftp
    OutputNames = {};

    ## -*- texinfo -*-
    ## @deftp {TFModel} {property} Session
    ## The @code{TF_Session} the model runs in.
    ## @end deftp
    Session = [];

  endproperties

  methods (Access = public)

    ## -*- texinfo -*-
    ## @deftypefn  {TFModel} {@var{obj} =} TFModel (@var{dirname})
    ## @deftypefnx {TFModel} {@var{obj} =} TFModel (@var{dirname}, @var{name}, @var{value}, @dots{})
    ##
    ## Load a SavedModel from the directory @var{dirname}.
    ##
    ## The following optional Name/Value pairs are accepted.
    ##
    ## @multitable @columnfractions 0.2 0.05 0.75
    ## @headitem @var{Name} @tab @tab @var{Value}
    ##
    ## @item @qcode{'Tags'} @tab @tab The tags identifying the MetaGraphDef to
    ## load, a character vector or a cellstr vector.  The default is
    ## @qcode{@{'serve'@}}.
    ##
    ## @item @qcode{'InputNames'} @tab @tab The operations to feed, a character
    ## vector or a cellstr vector.  The default is every placeholder named
    ## @qcode{'serving_default_@var{name}'}, sorted by name.
    ##
    ## @item @qcode{'OutputNames'} @tab @tab The operations to read, a character
    ## vector or a cellstr vector.  The default is every output of the operation
    ## named @qcode{'StatefulPartitionedCall'}.
    ## @end multitable
    ##
    ## @end deftypefn
    function this = TFModel (dirname, varargin)

      if (nargin < 1)
        print_usage ();
      endif
      if (mod (numel (varargin), 2) != 0)
        error ("TFModel: optional arguments must be given in Name/Value pairs.");
      endif
      tags = {"serve"};
      innames = {};
      outnames = {};
      for i = 1:2:numel (varargin)
        name = varargin{i};
        if (! (ischar (name) && isrow (name)))
          error ("TFModel: Name must be a character vector.");
        endif
        switch (lower (name))
          case 'tags'
            tags = varargin{i+1};
          case 'inputnames'
            innames = varargin{i+1};
          case 'outputnames'
            outnames = varargin{i+1};
          otherwise
            error ("TFModel: unrecognized parameter name '%s'.", name);
        endswitch
      endfor
      this.Session = TF_Session.fromSavedModel (dirname, tags);
      this.Directory = dirname;
      if (ischar (tags) && isrow (tags))
        tags = {tags};
      endif
      this.Tags = tags(:).';
      if (isempty (innames))
        innames = TFModel.discoverInputs (this.Session.Graph);
      elseif (ischar (innames) && isrow (innames))
        innames = {innames};
      endif
      if (isempty (outnames))
        outnames = TFModel.discoverOutputs (this.Session.Graph);
      elseif (ischar (outnames) && isrow (outnames))
        outnames = {outnames};
      endif
      if (! iscellstr (innames) || isempty (innames))
        error (["TFModel: no input operation was found; give them with the", ...
                " 'InputNames' parameter."]);
      endif
      if (! iscellstr (outnames) || isempty (outnames))
        error (["TFModel: no output operation was found; give them with the", ...
                " 'OutputNames' parameter."]);
      endif
      this.InputNames = innames(:).';
      this.OutputNames = outnames(:).';

    endfunction

    ## -*- texinfo -*-
    ## @deftypefn  {TFModel} {@var{y} =} predict (@var{obj}, @var{x})
    ## @deftypefnx {TFModel} {@var{y} =} predict (@var{obj}, @var{x1}, @dots{}, @var{xN})
    ##
    ## Run the model on @var{x} and return its output.
    ##
    ## As many inputs must be given as the model has @qcode{'InputNames'}, in
    ## that order.  @var{y} is an Octave array when the model has a single
    ## output, and a cell array of them otherwise.
    ##
    ## @end deftypefn
    function y = predict (this, varargin)

      if (nargin < 2)
        print_usage ();
      endif
      this.assertValid ("TFModel.predict");
      if (numel (varargin) != numel (this.InputNames))
        error ("TFModel.predict: %d input(s) expected, %d given.", ...
               numel (this.InputNames), numel (varargin));
      endif
      y = this.Session.run (this.InputNames, varargin, this.OutputNames);

    endfunction

    ## -*- texinfo -*-
    ## @deftypefn  {TFModel} {} delete (@var{obj})
    ##
    ## Release the model and the Session it runs in.
    ##
    ## @end deftypefn
    function delete (this)

      this.Session = [];

    endfunction

  endmethods

  methods (Access = private)

    function assertValid (this, caller)
      if (isempty (this.Session) || this.Session.Pointer == 0)
        error ("%s: the model has already been released.", caller);
      endif
    endfunction

  endmethods

  methods (Static, Access = private)

    ## The placeholders a serving signature feeds, which tf.saved_model.save
    ## names after the signature input.  Other placeholders, such as the
    ## 'saver_filename' of the checkpoint saver, are not model inputs.
    function names = discoverInputs (graph)
      opnames = graph.operationNames ();
      optypes = graph.operationTypes ();
      keep = strcmp (optypes, "Placeholder") & ...
             strncmp (opnames, "serving_default_", 16);
      names = sort (opnames(keep));
    endfunction

    ## The operation a serving signature returns through.  Its numbered
    ## siblings, 'StatefulPartitionedCall_1' and so on, belong to the saver.
    function names = discoverOutputs (graph)
      names = {};
      if (! graph.hasOperation ("StatefulPartitionedCall"))
        return;
      endif
      n = graph.numOutputs ("StatefulPartitionedCall");
      names = cell (1, n);
      for i = 1:n
        names{i} = sprintf ("StatefulPartitionedCall:%d", i - 1);
      endfor
    endfunction

  endmethods

endclassdef
