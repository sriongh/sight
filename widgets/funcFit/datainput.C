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

#include "main.h"
#include "model.h"

void dataInput(char* fName, MODEL* model)
{
    int i,j;
    FILE *fp = fopen(fName, "r");
    if(fp == NULL){printf("Error: Cannot open data file\n"); exit(0);}
    /*Malloc space for data*/
    model->yfunc = (double *)calloc(model->N, sizeof(double));
    model->parm = (double **)malloc(model->N*sizeof(double *));
    for(i=0; i<model->N; i++)
    {
        model->parm[i] = (double *)calloc(model->p, sizeof(double));
    }
    //Collect data
    for(i=0; i < model->N; i++)
    {
        //double tfloat = 0;
        //fscanf(fp,"%lg", &tfloat);
        //printf("yvalue %")
        fscanf(fp, "%lg", &(model->yfunc[i]));
        printf("yvalue: %f \n", model->yfunc[i]);
        for(j=0; j<model->p; j++)
        {
            fscanf(fp, "%lg", &(model->parm[i][j]));
        }
    }
}
