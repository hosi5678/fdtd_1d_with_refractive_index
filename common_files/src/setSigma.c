#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/setSigma.h"
#include "../include/common_parameter.h"
#include "../include/checkAlloc1DDouble.h"

double *setSigma(int x_length){

    double *sigma;

    sigma=checkAlloc1DDouble("sigma",x_length);

    for(int x=0;x<pml_layer_half_side;x++){
        sigma[x]=cu_sigma*pow(((pml_layer_half_side-(double)x)/pml_layer_half_side),4.0);
    }

    for(int x=pml_layer_half_side;x<x_length;x++){
        sigma[x]=sigma[x_length-1-x];
    }

    // for (int x=0 ; x<x_length ; x++) {
    //     printf("sigma[%d]=%.15f\n",x,sigma[x]);
    // }

    return sigma;

}
