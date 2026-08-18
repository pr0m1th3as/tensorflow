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

## -*- texinfo -*-
## @deftypefn {tensorflow} {@var{dirname} =} __tf_test_model__ ()
##
## Return the path of the SavedModel shipped for testing.
##
## @code{@var{dirname} = __tf_test_model__ ()} returns the full path of the
## @qcode{'tf_test_model'} directory, which holds a minimal SavedModel used by
## the tests of the @code{tensorflow} interface.  The model computes
## @code{y = w * x + b} for @code{w = [2, 3, 4]} and @code{b = [1, 1, 1]}, with
## @var{w} and @var{b} stored as variables so that loading the model exercises
## the restoring of checkpointed values and not merely the importing of a graph.
## It takes a single @qcode{'float'} input of size @code{[N, 3]} named
## @qcode{'x'} and returns a single output named @qcode{'y'} of the same size.
##
## This is an internal function of the @code{tensorflow} package.
##
## @end deftypefn

## The SavedModel was produced with TensorFlow 2.21.0 for Python by
##
##   class Affine (tf.Module):
##       def __init__ (self):
##           super ().__init__ ()
##           self.w = tf.Variable ([2.0, 3.0, 4.0], dtype=tf.float32, name='w')
##           self.b = tf.Variable ([1.0, 1.0, 1.0], dtype=tf.float32, name='b')
##       @tf.function (input_signature=[tf.TensorSpec ([None, 3], tf.float32,
##                                                     name='x')])
##       def __call__ (self, x):
##           return {'y': x * self.w + self.b}
##
##   tf.saved_model.save (m, out, signatures={'serving_default': m.__call__})
##
## which names the input operation 'serving_default_x' and the output operation
## 'StatefulPartitionedCall', both at index 0.  It is exported by a newer
## TensorFlow than the libtensorflow 2.18 this package links against, and loads
## under it.

function dirname = __tf_test_model__ ()

  dirname = fullfile (fileparts (mfilename ("fullpath")), "tf_test_model");

endfunction
