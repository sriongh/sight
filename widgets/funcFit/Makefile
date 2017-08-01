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

SRC = functionSetup.C ga.C parseinput.C transformation.C
OBJ = functionSetup.o ga.o parseinput.o transformation.o

GSL_PATH = ../gsl

.SUFFIXES: .c .C .o 
.C.o:
	${CCC} ${SIGHT_CFLAGS} -I${GSL_PATH}/include $^ -c -o $@

all: funcFit #ga
	
funcFit: filter.o ${OBJ} ${ROOT_PATH}/libsight_layout.*
	${CCC} -o funcFit filter.o ${OBJ} ${SIGHT_LINKFLAGS} -L${ROOT_PATH} -lsight_layout -lm -L${GSL_PATH}/lib -lgsl -lpthread -lgslcblas

ga: main.o datainput.o ${OBJ}
	${CCC} -o ga main.o ${OBJ} datainput.o -lm -L${GSL_PATH}/lib -lgsl -lpthread -lgslcblas

clean:
	rm -f funcFit
	rm -f *.o
