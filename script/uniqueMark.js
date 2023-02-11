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

// Hash that maps unique IDs to the array of ID of the blocks they are mapped to
var uniqueIDs2BlockID={};

// Hash that maps each uniqueBlockID to the hash where the keys are the labels associated with the unique blockID
var uniqueBlockIDs2Labels={};

// Hash that maps each blockID to a hash where the keys are the unique IDs mapped to it
var blockID2UniqueIDs={};

function registerUniqueMark(blockID, allUIDs, allLabels) {
  // Map each unique ID in allUIDs to blockID and each label in allLabels
  for(var ID in allUIDs) { if(allUIDs.hasOwnProperty(ID)) {
    if(!(allUIDs[ID] in uniqueIDs2BlockID)) {
      uniqueIDs2BlockID[allUIDs[ID]] = [];
      uniqueBlockIDs2Labels[allUIDs[ID]] = {};
    }
    
    uniqueIDs2BlockID[allUIDs[ID]].push(blockID);
    for(label in allLabels) { if(allLabels.hasOwnProperty(label)) {
      uniqueBlockIDs2Labels[allUIDs[ID]][allLabels[label]]=1;
    } }
  } }
  
  // Map blockID to all unique IDs in allUIDs
  if(!(blockID in blockID2UniqueIDs)) blockID2UniqueIDs[blockID] = {};
  for(var ID in allUIDs) { if(allUIDs.hasOwnProperty(ID)) {
     blockID2UniqueIDs[blockID][allUIDs[ID]] = 1;
  } }
}

// Given a blockID returns a concatenation of the labels associated with all the uniqueIDs mapped to this blockID,
// with the individual labels separated by string sep.
function getUniqueIDLabelFromBlockID(blockID, sep) {
  var fullLabel="";
  for(uniqueID in blockID2UniqueIDs[blockID]) { if(blockID2UniqueIDs[blockID].hasOwnProperty(uniqueID)) {
    for(label in uniqueBlockIDs2Labels[uniqueID]) { if(uniqueBlockIDs2Labels[uniqueID].hasOwnProperty(label)) {
      if(fullLabel != "") fullLabel += sep;
      fullLabel += label;
    }}
  }}
  
  return fullLabel;
}

// Given a uniqueID returns a concatenation of the labels associated with it, with the individual labels separated by string sep.
function getUniqueIDLabel(uniqueID, sep) {
  var fullLabel="";
  for(label in uniqueBlockIDs2Labels[uniqueID]) { if(uniqueBlockIDs2Labels[uniqueID].hasOwnProperty(label)) {
    if(fullLabel != "") fullLabel += sep;
    fullLabel += label;
  }}
  
  return fullLabel;
}
