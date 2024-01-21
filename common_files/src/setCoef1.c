#include <stdio.h>
#include <stdlib.h>

#include "../include/common_parameter.h"
#include "../include/checkAlloc1DDouble.h"
#include "../include/setCoef1.h"
#include "../include/get_dt.h"

double *setCoef1(double *eps,double *sigma,int x_length){

    double *coef1;

    double dt=get_dt();

    coef1=checkAlloc1DDouble("coef1",x_length);

    for(int x=0;x<x_length;x++){
        coef1[x]=(2.0*eps[x]-sigma[x]*dt)/(2.0*eps[x]+sigma[x]*dt);
    }

    return coef1;
}
