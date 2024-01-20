#include <stdio.h>
#include <stdlib.h>

#include "../include/setSigma.h"
#include "../include/common_parameter.h"
#include "../include/checkAlloc1DDouble.h"

double *setSigma(int x_length){

    double *sigma;

    sigma=checkAlloc1DDouble("sigma",x_length);

    for(int i=0;i<x_length;i++){
        sigma[i]=0.0;
    }

    return sigma;

}
