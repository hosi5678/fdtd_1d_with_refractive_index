#include <stdio.h>
#include <stdlib.h>

#include "../include/common_parameter.h"
#include "../include/checkAlloc1DDouble.h"
#include "../include/setCoef1.h"

double *setCoef1(double *eps,double *sigma,double dt,int x_length){

    double *coef1;

    dt=(dx/light_speed)*time_margin;

    coef1=checkAlloc1DDouble("coef1",x_length);

    for(int x=0;x<x_length;x++){
        coef1[x]=(2.0*eps[x]-sigma[x]*dt)/(2.0*eps[x]+sigma[x]*dt);
    }

    return coef1;
}
