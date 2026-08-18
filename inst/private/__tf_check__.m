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

## Delete the Status and raise its message under the name of the caller, if it
## does not report success.  The Status is deleted either way, so a caller
## never keeps one past the call it was created for.

function __tf_check__ (status, caller)

  code = tensorflow ("TF_GetCode", status);
  msg = "";
  if (code != 0)
    msg = tensorflow ("TF_Message", status);
  endif
  tensorflow ("TF_DeleteStatus", status);
  if (code != 0)
    error ("%s: %s", caller, msg);
  endif

endfunction
