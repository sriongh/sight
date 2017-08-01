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
#include "attributes_common.h"

namespace sight {
namespace layout{

class attributesLayoutHandlerInstantiator : layoutHandlerInstantiator {
  public:
  attributesLayoutHandlerInstantiator();
};
extern attributesLayoutHandlerInstantiator attributesLayoutHandlerInstance;

// ******************************
// ***** Attribute Database *****
// ******************************

// Maintains the mapping from atribute keys to values
class attributesC : public common::attributesC
{
  public:
  
  // Returns a representation of the attributes database as a JavaScript map
  std::string strJS() const;
};

extern layout::attributesC attributes;

// *******************************
// ***** Attribute Interface *****
// *******************************

// C++ interface for attribute creation, destruction
class attr
{
  // The key/value of this attribute
  std::string key;
  attrValue val;
    
  // Records whether the value that this attribute's key was assigned to before the attribute was set
  bool keyPreviouslySet;
  
  // The value that this attribute's key was assigned to before the attribute was set, if any
  attrValue oldVal;
  
  public:
  attr(properties::iterator props);
  
  ~attr();
  
  // Returns the key of this attribute
  std::string getKey() const;
  
  // Returns the value of this attribute
  const attrValue& getVal() const;
  
  // Returns the type of this attribute values's contents
  attrValue::valueType getVType() const;
  
  // Return the contents of this attribute values, aborting if there is a type incompatibility
  std::string getVStr() const;
  void*       getVPtr() const;
  long        getVInt() const;
  double      getVFloat() const;
  
  // Implementations of the relational operators
  bool operator==(const attr& that) const;
  bool operator<(const attr& that) const;
  bool operator!=(const attr& that) const
  { return !(*this == that); }
  bool operator<=(const attr& that) const
  { return *this < that || *this == that; }
  bool operator>(const attr& that) const
  { return !(*this == that) && !(*this < that); }
  bool operator>=(const attr& that) const
  { return (*this == that) || !(*this < that); }
};

}; // namespace layout
}; // namespace sight
