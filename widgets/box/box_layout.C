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

// Licence information included in file LICENCE
#include "../../sight_layout.h"
#include "../../sight_common.h"
#include <iostream>
#include <assert.h>
#include "box_layout.h"

using namespace std;

namespace sight {
namespace layout {

// Registers the handlers for object entry/exit layout. The entry handler is provided
// the beginning iteraror to the properties object that describes the object. It returns
// the C++ object that holds the decoded object or NULL if none was created.
// The exit handler provides a pointer to the object returned by the entry handler so that
// it may be deleted.
// This architecture makes it possible to do all entry/exit processing inside object 
// constructors and destructors, which is consistent with the way the interface and merging
// layers operate.
void* boxEnterHandler(properties::iterator props) { return new box(props); }
void  boxExitHandler(void* obj) { box* s = static_cast<box*>(obj); delete s; }
  
boxLayoutHandlerInstantiator::boxLayoutHandlerInstantiator() { 
  (*layoutEnterHandlers)["box"] = &boxEnterHandler;
  (*layoutExitHandlers) ["box"] = &boxExitHandler;
}
boxLayoutHandlerInstantiator boxLayoutHandlerInstance;

box::box(properties::iterator props) : block(properties::next(props))
{
  // Extract the style of this box
  style = props.get("style");

  // Record with the output stream that a new block has been entered. Don't create an entry in 
  // the summary pane for this box.
  dbg.enterBlock(this, /*newFileEntered*/ false, /*addSummaryEntry*/ false);
}

box::~box()
{ 
  // Record with the output stream that this block has been exited  
  dbg.exitBlock();
}

// Called to enable the block to print its entry and exit text
void box::printEntry(string loadCmd) {
  // Declare that we're about to emit arbitrary HTML code and ask Sight to not do any formatting
  // as it might to make user-provided text look ok in HTML
  dbg.ownerAccessing();

  // Start the div with the requested style
  dbg << "<div style=\""<<style<<"\">";

  // Return to normal mode;
  dbg.userAccessing();  
}

void box::printExit() {
  // Declare that we're about to emit arbitrary HTML code and ask Sight to not do any formatting
  // as it might to make user-provided text look ok in HTML
  dbg.ownerAccessing();

  // End the div
  dbg << "</div>";

  // Return to normal mode;
  dbg.userAccessing();  
}

}; // namespace layout
}; // namespace sight
