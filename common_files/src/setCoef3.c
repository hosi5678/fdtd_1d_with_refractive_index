#include <stdio.h>
#include <stdlib.h>

#include "../include/common_parameter.h"
#include "../include/checkAlloc1DDouble.h"
#include "../include/setCoef3.h"
#include "../include/get_dt.h"

double *setCoef3(double *eps,double *sigma,int x_length){

    double *coef3;

    double dt=get_dt();

    coef3=checkAlloc1DDouble("coef3",x_length);

    for(int x=0;x<x_length;x++){
        coef3[x]=(2.0*dt)/((2.0*eps[x]+sigma[x]*dt));
    }

    return coef3;
}
