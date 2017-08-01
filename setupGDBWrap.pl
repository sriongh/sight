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

use warnings;
use strict;

# This script points gdbwrap.cgi to the line within sight.C at which gdb should break.
# This is done by scanning sight.C for the line that contains a special comment and then
# writing this line number into gdbLineNum.pl, which is required by gdbwrap.cgi

open(my $fin, "<sight_structure.C") || die "ERROR opening file sight_structure.C for reading $!";
my $lnum=1;
my $found=0;
while(my $line = <$fin>) {
  chomp $line;
  if($line =~ /THIS COMMENT MARKS THE SPOT IN THE CODE AT WHICH GDB SHOULD BREAK/) {
    $found = 1;
    last;
  }
  $lnum++;
}
close($fin);

if(!$found) { die "ERROR: cannot find the line within sight_structure.C where gdb should break!"; }

open(my $fout, ">gdbLineNum.pl") || die "ERROR opening file gdbLineNum.pl for writing! $!";
print $fout "\$main::gdbLineNum = ",($lnum+1),";\n";
close($fout);
