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

#pragma once

#include <list>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "../../sight_common.h"
#include "../../sight_layout.h"

namespace sight {
namespace layout {

class parallelLayoutHandlerInstantiator  : layoutHandlerInstantiator{
  public:
  parallelLayoutHandlerInstantiator();
};
extern parallelLayoutHandlerInstantiator parallelLayoutHandlerInstance;

class commSend: public uniqueMark
{
  std::string recvIDs;
  public:
  commSend(properties::iterator props);
  public:
    
  // Called to notify this block that a sub-block was started/completed inside of it. 
  // Returns true of this notification should be propagated to the blocks 
  // that contain this block and false otherwise.
  bool subBlockEnterNotify(block* subBlock) { return false; }
  bool subBlockExitNotify (block* subBlock) { return false; }
  
  // Called to enable the block to print its entry and exit text
  void printEntry(std::string loadCmd);
  void printExit();
  
  ~commSend();
}; // commSend 
void* commSendEnterHandler(properties::iterator props);
void  commSendExitHandler(void* obj);

class commRecv: public uniqueMark
{
  std::string sendIDs;
  public:
  commRecv(properties::iterator props);
  public:
    
  // Called to notify this block that a sub-block was started/completed inside of it. 
  // Returns true of this notification should be propagated to the blocks 
  // that contain this block and false otherwise.
  bool subBlockEnterNotify(block* subBlock) { return false; }
  bool subBlockExitNotify (block* subBlock) { return false; }
  
  // Called to enable the block to print its entry and exit text
  void printEntry(std::string loadCmd);
  void printExit();
  
  ~commRecv();
}; // commRecv
void* commRecvEnterHandler(properties::iterator props);
void  commRecvExitHandler(void* obj);

class commBar: public uniqueMark
{
  std::string barIDs;
  public:
  commBar(properties::iterator props);
  public:
    
  // Called to notify this block that a sub-block was started/completed inside of it. 
  // Returns true of this notification should be propagated to the blocks 
  // that contain this block and false otherwise.
  bool subBlockEnterNotify(block* subBlock) { return false; }
  bool subBlockExitNotify (block* subBlock) { return false; }
  
  // Called to enable the block to print its entry and exit text
  void printEntry(std::string loadCmd);
  void printExit();
  
  ~commBar();
}; // commBar
void* commBarEnterHandler(properties::iterator props);
void  commBarExitHandler(void* obj);
}; // namespace layout
}; // namespace sight
