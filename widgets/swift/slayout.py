#!/usr/apps/python2.7.3/bin/python
# -*- coding: iso-8859-1 -*-
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

def main(argv):
  parser = argparse.ArgumentParser(description='Package programs for Swift commands')
  parser.add_argument('-sight_dir',  help='Directory where Sight is installed')
  parser.add_argument('-struct_dir',  help='Directory that contains the target structure file')
  parser.add_argument('-layout_dir',  help='Directory where we will place the laid out log representation')
  parser.add_argument('-environment', nargs='*', help='Environment of command')
  args = parser.parse_args()

  if(args.sight_dir):
   print "sight_dir "+args.sight_dir

  if(args.struct_dir):
   print "struct_dir "+args.struct_dir

  if(args.layout_dir):
   print "layout_dir "+args.layout_dir

  if(args.environment):
    # The length of the environment array must be even
    if(len(args.environment)%2 != 0) :
      print "ERROR: provided environment has an odd number of values! environment="+",".join(args.environment)
      sys.exit(-1)

    print "Environment"
    for i in range(0, len(args.environment), 2) :
      print args.environment[i]+" => "+args.environment[i+1]

  # If additional environment variables are provided, set them
  if(args.environment):
    # Add each pair of values in args.environment to os.environment
    for i in range(0, len(args.environment), 2) :
      os.environ[args.environment[i]] = args.environment[i+1];
 
  run(args.sight_dir+"/slayout "+args.struct_dir)

  run("mv "+args.struct_dir+" "+args.layout_dir);

  run("rm "+args.layout_dir+"/structure")


def run(cmd):
  print cmd
  os.system(cmd)

if __name__ == "__main__":
  main(sys.argv[1:])


