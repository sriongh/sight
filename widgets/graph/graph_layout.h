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

class graphLayoutHandlerInstantiator : layoutHandlerInstantiator {
  public:
  graphLayoutHandlerInstantiator();
};
extern graphLayoutHandlerInstantiator graphLayoutHandlerInstance;

typedef common::graphEdge<anchor> graphEdge;

class graph: public block
{
  protected:
  /*class node {
    public:
    int ID;
    std::string label;
    anchor a;
      
    node() : ID(-1), label("") {}
    node(int ID, std::string label, const anchor& a) : ID(ID), label(label), a(a) {}
  };*/
  
  // Maps a block's location to its ID and label
  std::map<anchor, std::string> nodes;
  // The maximum ID associated with any node in this graph
  int maxNodeID;
  
  std::list<graphEdge> edges;
  
  // The path the directory where output files of the graph widget are stored
  // Relative to current path
  static std::string outDir;
  // Relative to root of HTML document
  static std::string htmlOutDir;
    
  // Unique ID of this graph object
  int graphID;
  
  // Maximum ID assigned to any graph object
  //static int maxWidgetID;
  
  // Maps the IDs of the currently active graphs to their graph objects
  static std::map<int, graph*> active;
  
  // Records whether this graph has already been output by a call to outputCanvizDotGraph()
  bool graphOutput;

  // Counts the number of sub graphs that have been created within this one
  int subGraphCounter;
  
  public:
  
  graph(properties::iterator props);
  ~graph();

  // Generates and returns the dot graph code for this graphgenDotGraph
  virtual std::string genDotGraph();
  
  // Given a string representation of a dot graph, emits the graph's visual representation 
  // as a Canviz widget into the debug output.
  void outputCanvizDotGraph(std::string dot);
  
  // Initialize the environment within which generated graphs will operate, including
  // the JavaScript files that are included as well as the directories that are available.
  static void initEnvironment();
 
  // Sets the structure of the current graph by specifying its dot encoding
  void setGraphEncoding(std::string dotText);
  static void* setGraphEncoding(properties::iterator props);
 
  // Add a directed edge from the location of the from anchor to the location of the to anchor
  void addDirEdge(anchor from, anchor to);
  static void* addDirEdge(properties::iterator props);
  
  // Add an undirected edge between the location of the a anchor and the location of the b anchor
  void addUndirEdge(anchor a, anchor b);
  static void* addUndirEdge(properties::iterator props);

  // Add an invisible undirected edge between the location of the a anchor and the location of the b anchor
  void addInvisEdge(anchor a, anchor b);
  static void* addInvisEdge(properties::iterator props);

  // Add a node to the graph
  void addNode(anchor a, std::string label);
  static void* addNode(properties::iterator props);

  // Start a sub-graph
  void startSubGraph();
  void startSubGraph(const std::string& label);
  static void* startSubGraph(properties::iterator props);

  // End a sub-graph
  //void endSubGraph();
  static void endSubGraph(void* obj);
  
  // Called to notify this block that a sub-block was started/completed inside of it. 
  // Returns true of this notification should be propagated to the blocks 
  // that contain this block and false otherwise.
  bool subBlockEnterNotify(block* subBlock) { return false; }
  bool subBlockExitNotify (block* subBlock) { return false; }
};

}; // namespace layout
}; // namespace sight
