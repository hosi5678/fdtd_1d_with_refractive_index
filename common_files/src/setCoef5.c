#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/common_parameter.h"
#include "../include/checkAlloc1DDouble.h"
#include "../include/setCoef5.h"
#include "../include/get_dt.h"

double *setCoef5(double *eps,int x_length){

   // printf("in coef5:\n");

    double *coef5,*sigma;

    double dt=get_dt();

    coef5=checkAlloc1DDouble("coef4",x_length);
    sigma=checkAlloc1DDouble("coef4_sigma",x_length);

    for(int x=0;x<pml_layer-1;x++){
      sigma[x]=cu_sigma*(pow((pml_layer-(double)(x+0.5))/pml_layer,4.0));
    }

    // for(int x=x_length-(pml_layer-1);x<x_length;x++){
    //   sigma[x]=sigma[x_length-1-x];
    // }

    for(int x=0;x<x_length;x++){
         printf("sigma[%d]=%.10f\n",x,sigma[x]);
    }

    for(int x=0;x<x_length;x++){
        coef5[x]=(2.0*eps[x]*dt)/((2.0*eps[x]+sigma[x]*dt)*dx*u0);
    }

   //  for(int x=0;x<x_length;x++){
   //       printf("coef5[%d]=%.10f\n",x,coef5[x]);
   //  }


    return coef5;
}
