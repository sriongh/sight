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

#include <vector>
#include <map>
using namespace std;

#include "sight_structure.h"
#include "widgets/graph/graph_structure.h"
using namespace sight;
using namespace sight::structure;

#include "sight_merge.h"
using namespace sight::merge;

int main(int argc, char** argv) {
  if(argc<2) { cerr<<"Usage: hier_merge outDir [fNames]"<<endl; exit(-1); }
  vector<FILEStructureParser*> fileParsers;
  const char* outDir = argv[1];
  //mergeType mt = str2MergeType(string(argv[2]));
  if(argc>2) {
    for(int i=2; i<argc; i++) {
      fileParsers.push_back(new FILEStructureParser(argv[i], 10000));
    }
  } else {
    cout << "Reading input directories from stdin\n";
    for (std::string line; std::getline(std::cin, line);) {
      //std::cout << line << std::endl;
      fileParsers.push_back(new FILEStructureParser(line, 10000));
    }
  }

  #ifdef VERBOSE
  SightInit(argc, argv, "hier_merge", txt()<<outDir<<".hier_merge");
  dbg << "#fileParserRefs="<<fileParsers.size()<<endl;
  #else
  SightInit_LowLevel();
  #endif
  
  // Set the working directory in the dbgStreamMerger class (it is a static variable). This must be done before an instance of this class is created
  // since the first and only instance of this class will read this working directory and write all output there.
  dbgStreamMerger::workDir = string(outDir);
  
  //dbgStreamStreamRecord::enterBlock(inStreamRecords);
#ifdef VERBOSE
  graph g;
  anchor outgoingA; 
#endif

  MergeState state(fileParsers
                   #ifdef VERBOSE
                   , g, anchor::noAnchor, outgoingA
                   #endif
                  );
  state.merge();
  
  // Close all the parsers and their files
  for(vector<FILEStructureParser*>::iterator p=fileParsers.begin(); p!=fileParsers.end(); p++)
    delete *p;
  
  return 0;
}
