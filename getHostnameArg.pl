#!/usr/bin/perl

##//////////////////////////////////////////////////////////////////////////////
## Copyright (c) 2013, Lawrence Livermore National Security, LLC.
## Produced at the Lawrence Livermore National Laboratory.
## Written by the Greg Bronevetsky <bronevetsky1@llnl.gov> / <greg@bronevetsky.com>. 
##
## LLNL-CODE-642002
## All rights reserved.
##
## This file is part of Sight. For details, see https://e-reports-ext.llnl.gov/pdf/781752.pdf or
## https://github.com/bronevet/sight.
##
## Licensed under the GNU Lesser General Public License (Lesser GPU) Version 2.1, 
## February 1999; you may not use this file except in compliance with the License.  
## The full licence is included in file LICENCE and you may obtain a copy of the 
## License at: 
## https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html
##
## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS" BASIS,
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
## implied. See the License for the specific language governing
## permissions and limitations under the license.
##//////////////////////////////////////////////////////////////////////////////

use strict;

# This script tests the command line parameters that hostname makes available
use IPC::Open3;

run("hostname --skldfj");
if(run("hostname --aldns")) { print "--as"; }
elsif(run("hostname --all-fqdns")) { print "--all-fqdns"; }
elsif(run("hostname --fqdn")) { print "--fqdn"; }
elsif(run("hostname")) { }
else {  die "hostname command not functional!"; }

# Runs the given command, returns true on success and false on failure
sub run
{
  my ($cmd) = @_;

  my $pid = open3(my $in, my $out, my $err, $cmd) || die "ERROR running command \"$cmd\"!"; 
  waitpid($pid, 0);
  my $child_exit_status = $? >> 8;
  #print "child_exit_status=$child_exit_status\n";
  return $child_exit_status==0;
}
