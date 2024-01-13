#include <stdio.h>
#include <stdlib.h>

#include "../../common_include/common_parameter.h"
#include "../../common_include/getEy.h"


double *getEy(double *ey,double *hz,double *sigma,double *wave){

    double dt;
    
    dt=0.95*dx/light_speed;

    for(int x=0;x<cells;x++){

        double coef1,coef2,coef3;

            coef1=(2.0*eps0-sigma[x]*dt)/(2.0*eps0+sigma[x]);
            coef2=(2.0*dt)/((2.0*eps0+sigma[x]*dt)*dx);
            coef3=(2.0*dt)/(2.0*eps0+sigma[x]*dt);

            ey[x]=coef1*ey[x]-coef2*(hz[x+1]-hz[x])+coef3*wave[x];

        }

    return ey;
}
