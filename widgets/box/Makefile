##//////////////////////////////////////////////////////////////////////////////
## Copyright (c) 2013, Lawrence Livermore National Security, LLC.
## Produced at the Lawrence Livermore National Laboratory.
## Written by the Greg Bronevetsky <bronevetsky1@llnl.gov> / <greg@bronevetsky.com>. 
##
## LLNL-CODE-642002
## All rights reserved.
##
## This file is part of Sight. For details, see https://e-reports-ext.llnl.gov/pdf/781752.pdf or
## https://github.com/bronevet/sight.
##
## Licensed under the GNU Lesser General Public License (Lesser GPU) Version 2.1, 
## February 1999; you may not use this file except in compliance with the License.  
## The full licence is included in file LICENCE and you may obtain a copy of the 
## License at: 
## https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html
##
## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS" BASIS,
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
## implied. See the License for the specific language governing
## permissions and limitations under the license.
##//////////////////////////////////////////////////////////////////////////////

all: box_api_cpp.o box_merge.o box_layout.o

box_api_cpp.o: box_api_cpp.C box_api_cpp.h ../../attributes/attributes_common.h ../../sight_structure.h
	${CCC} ${SIGHT_CFLAGS} box_api_cpp.C -I.. -DROOT_PATH="\"${ROOT_PATH}\"" -c -o box_api_cpp.o

box_merge.o: box_merge.C box_merge.h ../../attributes/attributes_structure.h ../../sight_structure.h
	${CCC} ${SIGHT_CFLAGS} box_merge.C -I.. -DROOT_PATH="\"${ROOT_PATH}\"" -c -o box_merge.o

box_layout.o: box_layout.C box_layout.h ../../attributes/attributes_layout.h ../../sight_layout.h
	${CCC} ${SIGHT_CFLAGS} box_layout.C -I.. -DROOT_PATH="\"${ROOT_PATH}\"" -c -o box_layout.o


