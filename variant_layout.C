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

#include "sight_layout.h"
#include "sight_common.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>

using namespace std;
using namespace sight::common;

namespace sight {
namespace layout {

// Record the layout handlers in this file
void* variantEnterHandler(properties::iterator props) { variant* v=new variant(props); return v; }
void  variantExitHandler(void* obj) { variant* v = static_cast<variant*>(obj); delete v; }
void* interVariantHandler(properties::iterator props) { 
  dbg.ownerAccessing();
  dbg << endl << "</td><td>" << endl;
  dbg.userAccessing();
  return NULL;
}
  
variantLayoutHandlerInstantiator::variantLayoutHandlerInstantiator() { 
  // Called when a group of variants are entered or exited
  (*layoutEnterHandlers)["variants"] = &variantEnterHandler;
  (*layoutExitHandlers) ["variants"] = &variantExitHandler;
  // Called between individual variants within a group
  (*layoutEnterHandlers)["inter_variants"] = &interVariantHandler;
}
variantLayoutHandlerInstantiator variantLayoutHandlerInstance;

variant::variant(properties::iterator props) : 
  scope("Variants", 
        false, // ownFile
        true,  // ownColor
        false, // labelInteractive
        false, // labelShown
        true)  // summaryEntry
{
  numVariants = props.getInt("numSubDirs");

  dbg.ownerAccessing();
  dbg << "<table border=1 width=\"100\%\"><tr><td colspan=\""<<numVariants<<"\">Variants</td></tr>"<<endl;
  dbg << "<tr><td>"<<endl;
  //dbg << "<script type=\"text/javascript\">"<<loadCmd<<"</script>"<<endl;
  
  dbg.flush();
  dbg.userAccessing();  
}

variant::~variant() { 
  // Close this scope
  dbg.ownerAccessing();
  dbg << "</td></tr></table>"<<endl;
  dbg.userAccessing();  
}

}; // namespace layout
}; // namespace sight
