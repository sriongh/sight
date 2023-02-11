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

// Hash maps divs to the data arrays that are shown in them
var div2Data = {};

// Hash maps divs and their attribute names to the type of data the associated table contains for each
// field: "numeric", "categorical".
var dataType = {};

function showTable(data, hostDiv, sortAttrName) {
  div2Data[hostDiv] = data;

  dataType[hostDiv] = {};
  var firstObs = true;
  for(d in data) { if(data.hasOwnProperty(d)) {
    for(key in data[d]) { if(data[d].hasOwnProperty(key)) {
      // Default each attribute to numeric until we discover that this is not true
      if(firstObs) dataType[hostDiv][key] = "numeric";

      if(!isNumber(data[d][key])) dataType[hostDiv][key] = "categorical";
    } }
    
      firstObs = false;
  } }
  
  d3.select("#"+hostDiv).append("thead");
  d3.select("#"+hostDiv).append("tbody");
  
  refreshTable(hostDiv, sortAttrName);
}

function refreshTable(hostDiv, sortAttrName) {
  d3.select("#"+hostDiv).selectAll("tbody").selectAll("tr").remove();

// Header
    var th = d3.select("#"+hostDiv).selectAll("thead")
               .selectAll("th")
                     .data(jsonToArray(div2Data[hostDiv][0]))
                 .enter().append("th")
                    .attr("onclick", function (d, i) { return "refreshTable('"+ hostDiv+ "', '" + d[0] + "');";})
                    .text(function(d) { return d[0]; })

// Rows
    var tr = d3.select("#"+hostDiv).selectAll("tbody")
               .selectAll("tr")
                      .data(div2Data[hostDiv])
                 .enter().append("tr")
                    .sort(function (a, b) { 
                            return a == null || b == null ? 
                               0 : 
                               stringCompare(dataType[hostDiv][sortAttrName], a[sortAttrName], b[sortAttrName]); 
                          });

// Cells
    var td = tr.selectAll("td")
            .data(function(d) { return jsonToArray(d); })
          .enter().append("td")
            .attr("onclick", function (d, i) { return "transform('" + d[0] + "');";})
            .text(function(d) { return d[1]; });
}

function stringCompare(type, a, b) {
  if(type=="categorical") {
    a = a.toLowerCase();
    b = b.toLowerCase();
  } else {
    a = parseFloat(a);
    b = parseFloat(b);
  }
  return a > b ? 1 : a == b ? 0 : -1;
}

function jsonKeyValueToArray(k, v) {return [k, v];}

function jsonToArray(json) {
    var ret = new Array();
    var key;
    for (key in json) {
        if (json.hasOwnProperty(key)) {
            ret.push(jsonKeyValueToArray(key, json[key]));
        }
    }
    return ret;
};