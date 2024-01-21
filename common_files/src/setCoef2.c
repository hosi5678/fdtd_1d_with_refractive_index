#include <stdio.h>
#include <stdlib.h>

#include "../include/common_parameter.h"
#include "../include/checkAlloc1DDouble.h"
#include "../include/setCoef2.h"
#include "../include/get_dt.h"

double *setCoef2(double *eps,double *sigma,int x_length){

    double *coef2;

    double dt=get_dt();

    coef2=checkAlloc1DDouble("coef2",x_length);

    for(int x=0;x<x_length;x++){
        coef2[x]=(2.0*dt)/((2.0*eps[x]+sigma[x]*dt)*dx);
    }

    return coef2;
}
