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

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <set>
#include <sys/types.h>

namespace sight {
// Create directory workDir/dirName. The path of the created directory is returned.
std::string createDir(std::string workDir, std::string dirName);

// Copy dirName from the source code path to the workDir
std::string copyDir(std::string workDir, std::string dirName);
  
// Open a freshly-allocated output stream to write a file with the given name and return a pointer to the object.
std::ofstream& createFile(std::string fName);

// Returns a string that contains n tabs
std::string tabs(int n);

// Given a string and a line width returns a variant of the string where line breaks are inserted
// at approximately every lineWidth characters.
std::string wrapStr(std::string str, unsigned int lineWidth);

// Returns the human-readable representation of the given list of strings
std::string list2str(const std::list<std::string>& l);

// Returns the human-readable representation of the given vector of strings
std::string vector2str(const std::vector<std::string>& v);

// Returns the human-readable representation of the given set of strings
std::string set2str(const std::set<std::string>& l);

// Adapted from http://stackoverflow.com/questions/675039/how-can-i-create-directory-tree-in-c-linux
// Returns the directory and file name portion of the given path
std::pair<std::string, std::string> path2filedir(std::string s);

// Creates the directory with the given path, creating any sub-directories within it
// If isDir is true, s is a directory. Otherwise, it is a file and thus, we need to create its parent directory.
int mkpath(std::string s, mode_t mode, bool isDir=true);

} // namespace sight

