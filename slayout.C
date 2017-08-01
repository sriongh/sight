////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2013, Lawrence Livermore National Security, LLC.
// Produced at the Lawrence Livermore National Laboratory.
// Written by the Greg Bronevetsky <bronevetsky1@llnl.gov> / <greg@bronevetsky.com>. 
//
// LLNL-CODE-642002
// All rights reserved.
//
// This file is part of Sight. For details, see https://e-reports-ext.llnl.gov/pdf/781752.pdf or
// https://github.com/bronevet/sight.
//
// Licensed under the GNU Lesser General Public License (Lesser GPU) Version 2.1, 
// February 1999; you may not use this file except in compliance with the License.  
// The full licence is included in file LICENCE and you may obtain a copy of the 
// License at: 
// https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
// implied. See the License for the specific language governing
// permissions and limitations under the license.
////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <list>
#include <iostream>
#include <string>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "process.h"
//#include "process.C"
#include <iostream>
using namespace std;
using namespace sight;
#include "sight_layout.h"
using namespace sight::layout;

//#define VERBOSE

int main(int argc, char** argv) {
  if(argc!=1 && argc!=2) { cerr<<"Usage: slayout fName"<<endl; exit(-1); }
  char* fName=NULL;
  if(argc==2) fName = argv[1];

  FILE* f;
  if(argc==1)
    f = stdin;
  else {
    // Make sure the file exists and is not a directory
    struct stat s;
    int err = stat(fName, &s);
    string structureFName;
    if(-1 == err) {
      if(ENOENT == errno) { cerr << "ERROR: path \""<<fName<<"\" does not exist!"<<endl; exit(-1); }
      else                { perror("stat"); exit(-1); }
    } else {
      if(S_ISDIR(s.st_mode)) { //cerr << "ERROR: path \""<<fName<<"\" is a directory!"<<endl; exit(-1); }
        // Open the structure file within the directory
        structureFName = txt() << fName << "/structure";
      } else {
        // exists but is no dir
        structureFName = fName;
      }
    }
  
    f = fopen(structureFName.c_str(), "r");
    if(f==NULL) { cerr << "ERROR opening file \""<<structureFName<<"\" for reading! "<<strerror(errno)<<endl; exit(-1); }
  }

  
  FILEStructureParser parser(f, 10000);
  
  layoutStructure(parser);

  if(argc==2)
    fclose(f);
}
