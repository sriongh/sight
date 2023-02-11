#!/usr/apps/python2.7.3/bin/python
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

import sys
import argparse
import os

print 'Number of arguments:', len(sys.argv), 'arguments.'
print 'Argument List:', str(sys.argv)

def main(argv):
  abspaths = []
  for i in range(0, len(argv)) :
    abspaths += [os.path.abspath(argv[i])]; 

  print str(abspaths)
 
  for i in range(0, len(argv)):
    run("mkdir tmp")
    os.chdir("tmp")
    run("cp "+abspaths[i]+" "+os.path.basename(abspaths[i])+".tar");
    run("tar -xf "+os.path.basename(abspaths[i])+".tar");
    run("mv "+os.path.basename(abspaths[i])+" ../"+os.path.basename(abspaths[i])+".unpacked");
   
def run(cmd):
  print cmd
  os.system(cmd)

if __name__ == "__main__":
  main(sys.argv[1:])


