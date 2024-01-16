#include <stdio.h>
#include <stdlib.h>

#include "../../common_include/common_parameter.h"
#include "../../common_include/checkAlloc1DDouble.h"
#include "../../common_include/setCoef1.h"

double *setCoef1(double *eps,double *sigma,int length){

    double *coef1;
    double dt;

    dt=(dx/light_speed)*time_margin;

    coef1=checkAlloc1DDouble("coef1",length);

    for(int x=0;x<length;x++){
        coef1[x]=(2.0*eps[x]-sigma[x]*dt)/(2.0*eps[x]+sigma[x]*dt);
    }

    return coef1;
}
