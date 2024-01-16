#include <stdio.h>
#include <stdlib.h>

#include "../../common_include/common_parameter.h"
#include "../../common_include/setEps.h"
#include "../../common_include/checkAlloc1DDouble.h"

double *setEps(int x_length){

    double *eps;

    eps=checkAlloc1DDouble("eps",x_length);

    for(int i=0;i<x_length;i++){
        eps[i]=eps0;
    }

    return eps;
}
