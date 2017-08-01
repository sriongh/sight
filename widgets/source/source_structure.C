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

#include "../../sight_structure.h"
#include "../../sight_common.h"
#include "source_structure.h"
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
namespace structure {

source::source(std::string label, const source::reg& r,                            properties* props) :
  scope(label, scope::minimum, setProperties(label, source::regions(r), NULL, props))
{}

source::source(std::string label, const source::reg& r,     const attrOp& onoffOp, properties* props) :
  scope(label, scope::minimum, setProperties(label, source::regions(r), &onoffOp, props))
{}

source::source(std::string label, const source::regions& r,                        properties* props) :
  scope(label, scope::minimum, setProperties(label, r, NULL, props))
{}

source::source(std::string label, const source::regions& r, const attrOp& onoffOp, properties* props) :
  scope(label, scope::minimum, setProperties(label, r, &onoffOp, props))
{}

// Sets the properties of this object
properties* source::setProperties(std::string label, const source::regions& r, const attrOp* onoffOp, properties* props)
{
  if(props==NULL) props = new properties();
    
  // If the current attribute query evaluates to true (we're emitting debug output) AND
  // either onoffOp is not provided or its evaluates to true
  if(attributes->query() && (onoffOp? onoffOp->apply(): true)) {
    props->active = true;
    map<string, string> pMap;
    pMap["numRegions"] = txt() << r.size();
    int i=0;
    for(regions::const_iterator rj=r.begin(); rj!=r.end(); rj++, i++) {
      pMap[txt()<<"fName_"<<i]     = rj->fName;
      pMap[txt()<<"startLine_"<<i] = rj->startLine;
      pMap[txt()<<"endLine_"<<i]   = rj->endLine;
    }
    props->add("source", pMap);
  }
  else
    props->active = false;
  return props;
}

// Directly calls the destructor of this object. This is necessary because when an application crashes
// Sight must clean up its state by calling the destructors of all the currently-active sightObjs. Since 
// there is no way to directly call the destructor of a given object when it may have several levels
// of inheritance above sightObj, each object must enable Sight to directly call its destructor by calling
// it inside the destroy() method. The fact that this method is virtual ensures that calling destroy() on 
// an object will invoke the destroy() method of the most-derived class.
void source::destroy() {
  if(destroyed) return;
}

source::~source() {
  assert(!destroyed);
}

/*****************************************
 ***** SourceMergeHandlerInstantiator *****
 *****************************************/

SourceMergeHandlerInstantiator::SourceMergeHandlerInstantiator() { 
  (*MergeHandlers   )["source"]       = SourceMerger::create;
  (*MergeKeyHandlers)["source"]       = SourceMerger::mergeKey;
}
SourceMergeHandlerInstantiator SourceMergeHandlerInstance;


/***********************
 ***** SourceMerger ****
 ***********************/

SourceMerger::SourceMerger(std::vector<std::pair<properties::tagType, properties::iterator> > tags,
                         map<string, streamRecord*>& outStreamRecords,
                         vector<map<string, streamRecord*> >& inStreamRecords,
                         properties* props) : 
        ScopeMerger(advance(tags), outStreamRecords, inStreamRecords, 
                    setProperties(tags, outStreamRecords, inStreamRecords, props)) { }

// Sets the properties of the merged object
properties* SourceMerger::setProperties(std::vector<std::pair<properties::tagType, properties::iterator> > tags,
                                       map<string, streamRecord*>& outStreamRecords,
                                       vector<map<string, streamRecord*> >& inStreamRecords,
                                       properties* props) {
  if(props==NULL) props = new properties();
  
  map<string, string> pMap;
  properties::tagType type = streamRecord::getTagType(tags); 
  if(type==properties::unknownTag) { cerr << "ERROR: inconsistent tag types when merging Scope!"<<endl; exit(-1); }
  if(type==properties::enterTag) {
    assert(tags.size()>0);

    vector<string> names = getNames(tags); assert(allSame<string>(names));
    assert(*names.begin() == "source");
    
    vector<long> numRegionsV = str2int(getValues(tags, "numRegions"));
    assert(allSame<long>(numRegionsV));
    int numRegions = *numRegionsV.begin();
    pMap["numRegions"] = txt()<<numRegions;
    
    for(int i=0; i<numRegions; i++) {
      vector<string> fName = getValues(tags, txt()<<"fName_"<<i);
      assert(allSame<string>(fName));
      pMap[txt()<<"fName_"<<i] = *fName.begin();

      vector<string> startLine = getValues(tags, txt()<<"startLine_"<<i);
      assert(allSame<string>(startLine));
      pMap[txt()<<"startLine_"<<i] = *startLine.begin();

      vector<string> endLine = getValues(tags, txt()<<"endLine_"<<i);
      assert(allSame<string>(endLine));
      pMap[txt()<<"endLine_"<<i] = *endLine.begin();
    }
    
    props->add("source", pMap);
  } else {
    props->add("source", pMap);
  }
  
  return props;
}

// Sets a list of strings that denotes a unique ID according to which instances of this merger's 
// tags should be differentiated for purposes of merging. Tags with different IDs will not be merged.
// Each level of the inheritance hierarchy may add zero or more elements to the given list and 
// call their parents so they can add any info,
void SourceMerger::mergeKey(properties::tagType type, properties::iterator tag, 
                           const std::map<std::string, streamRecord*>& inStreamRecords, MergeInfo& info) {
  ScopeMerger::mergeKey(type, tag.next(), inStreamRecords, info);
  
  if(type==properties::unknownTag) { cerr << "ERROR: inconsistent tag types when computing merge attribute key!"<<endl; exit(-1); }
  if(type==properties::enterTag) {
    info.add(properties::get(tag, "numRegions"));
    int numRegions = properties::getInt(tag, "numRegions");
    
    for(int i=0; i<numRegions; i++) {
      info.add(properties::get(tag, txt()<<"fName_"<<i));
      info.add(properties::get(tag, txt()<<"startLine_"<<i));
      info.add(properties::get(tag, txt()<<"endLine_"<<i));
    }
  }
}

}; // namespace structure
}; // namespace sight
