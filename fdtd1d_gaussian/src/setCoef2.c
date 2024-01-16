#include <stdio.h>
#include <stdlib.h>

#include "../../common_include/common_parameter.h"
#include "../../common_include/checkAlloc1DDouble.h"
#include "../../common_include/setCoef2.h"

double *setCoef2(double *eps,double *sigma,double dt,int x_length){

    double *coef2;

    dt=(dx/light_speed)*time_margin;

    coef2=checkAlloc1DDouble("coef2",x_length);

    for(int x=0;x<x_length;x++){
        coef2[x]=(2.0*dt)/((2.0*eps[x]+sigma[x]*dt)*dx);
    }

    return coef2;
}
