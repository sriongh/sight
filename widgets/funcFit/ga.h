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

#include "model.h"
#include <stdio.h>
#include <gsl/gsl_fit.h>
#include <gsl/gsl_multifit.h>

#ifndef GA_H
#define	GA_H

#ifdef	__cplusplus
extern "C" {
#endif


/*Function DEFS*/
void initBitVector(GAMODEL*);
void printBitVector(FILE* log, GAMODEL*);

// Initialize the GSL matrix input and vector y with the observed data and set the vector c to 0.
// N: number of observations
// n: number of input parameters in each observation
// bitVector: indicates which parameters are included in this model
void fillMtxWithData(int N, int n, double** data, double* ydata, int* bitVector,
                     gsl_matrix *input, gsl_vector *y, gsl_vector *c);

// Trains the linear model c to be the best solution to equation y=input*c.
// N: number of observations
// n: number of input parameters in each observation
// cov: matrix to which the covariance will be written
// work: workspace for the linear solve
// chi: double to which the chi-squared error will be written
void trainLinModel(FILE* log, int N, int n,
                   gsl_matrix *input, gsl_vector *y, gsl_vector *c,
                   gsl_matrix *cov, gsl_multifit_linear_workspace *work, double& chi);

void findModels(FILE* log, GAMODEL*);
void AIC(GAMODEL*);
void MateSinglePoint(FILE* log, GAMODEL*);
void MateSinglePointLink(FILE* log, GAMODEL*);
void copyBitVector(GAMODEL*);
void mutation(GAMODEL*);
void mutationLink(GAMODEL*);
void PrintModels(FILE* log, GAMODEL*);


void RunGA(FILE* log, GAMODEL*);



    
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* GA_H */

