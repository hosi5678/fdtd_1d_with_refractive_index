#include <stdio.h>
#include <stdlib.h>

#include "../../common_include/setSigma.h"
#include "../../common_include/common_parameter.h"
#include "../../common_include/checkAlloc1DDouble.h"

double *setSigma(int x_length){

    double *sigma;

    sigma=checkAlloc1DDouble("sigma",x_length);

    for(int i=0;i<x_length;i++){
        sigma[i]=0.0;
    }

    return sigma;

}
