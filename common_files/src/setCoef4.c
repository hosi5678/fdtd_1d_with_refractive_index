#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/common_parameter.h"
#include "../include/checkAlloc1DDouble.h"
#include "../include/setCoef4.h"
#include "../include/get_dt.h"

double *setCoef4(double *eps,int x_length){

    double *coef4,*sigma;

    double dt=get_dt();

    coef4=checkAlloc1DDouble("coef4",x_length);
    sigma=checkAlloc1DDouble("coef4_sigma",x_length);

    for(int x=0;x<pml_layer-1;x++){
      sigma[x]=cu_sigma*(pow((pml_layer-(double)(x+0.5))/pml_layer,4.0));
    }

    for(int x=x_length-(pml_layer-1);x<x_length;x++){
      sigma[x]=sigma[x_length-1-x];
    }

   // printf("pml_layer=%d\n",pml_layer);

   //  for(int x=0;x<x_length;x++){
   //       printf("sigma[%d]=%.10f\n",x,sigma[x]);
   //  }

    for(int x=0;x<x_length;x++){
        coef4[x]=(2.0*eps[x]-sigma[x]*dt)/((2.0*eps[x]+sigma[x]*dt));
    }

   //  for(int x=0;x<x_length;x++){
   //       printf("coef4[%d]=%.10f\n",x,coef4[x]);
   //  }


    return coef4;
}
