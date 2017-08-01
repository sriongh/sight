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
#include <stdlib.h>
#include <stdio.h>
#include "../../sight_layout.h"

namespace sight {
namespace layout {

class valSelectorLayoutHandlerInstantiator : layoutHandlerInstantiator {
  public:
  valSelectorLayoutHandlerInstantiator();
};
extern valSelectorLayoutHandlerInstantiator valSelectorLayoutHandlerInstance;

class valSelector : public sightObj
{
  protected:
  // Maps the selIDs of all the active valSelectors to their objects
  static std::map<int, valSelector*> active;
  
  int selID;
  
  public:
  
  valSelector(properties::iterator props): sightObj(props.next()) {}
  
  static void observeSelection(properties::iterator props, std::string fieldName, const std::map<std::string, std::string>& fieldSettings);
  
  // Returns a string that contains a call to a JavaScipt function that at log view time will return a value
  // It is assumed that the selector is already associated with some attribute and can get the attrValue on its own
  virtual void getSelFunction(std::string val, std::string arg)=0;
};

class colorSelector : public valSelector {
  
  public:
  colorSelector(properties::iterator prop);
  ~colorSelector();
  
  // Returns a string that contains a call to a JavaScipt function that at log view time will return a value
  // It is assumed that the selector is already associated with some attribute and can get the attrValue on its own
  void getSelFunction(std::string val, std::string arg);
};

class textColor
{
  public:
  static void* start(properties::iterator props);
  static void end   (void* obj);
};

class bgColor
{
  public:
  static void* start(properties::iterator props);
  static void end   (void* obj);
};

class borderColor
{
  public:
  static void* start(properties::iterator props);
  static void end   (void* obj);
};

}; // namespace layout
}; // namespace sight
