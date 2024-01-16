#include <stdio.h>
#include <stdlib.h>

#include "../../common_include/common_parameter.h"
#include "../../common_include/init2DdoublePlane.h"
#include "../../common_include/symmetryCheck.h"
#include "../../common_include/antisymmetryCheck.h"
#include "../../common_include/checkAlloc1DDouble.h"

#include "../../common_include/setEps.h"
#include "../../common_include/setSigma.h"
#include "../../common_include/setCoef1.h"
#include "../../common_include/setCoef2.h"
#include "../../common_include/setCoef3.h"

#include "../../common_include/set1DEyHz.h"

double const * const *set1DEyHz(
    int x_length,
    int time_length,
    double *src_J,
    int excite_point,
    double dt

) {

    double *sigma,*eps;
    double *coef1,*coef2,*coef3;

    double *ey,*hz;

    eps=setEps(x_length);
    sigma=setSigma(x_length);

    coef1=setCoef1(eps,sigma,dt,x_length);
    coef2=setCoef2(eps,sigma,dt,x_length);
    coef3=setCoef3(eps,sigma,dt,x_length);
    double coef4=dt/(u0*dx);

        // ey initialize
    ey=checkAlloc1DDouble("ey calloc",x_length);

    // hz initialize
    hz=checkAlloc1DDouble("hz calloc",x_length-1);

    double ey_max=0.0;
    double ey_min=0.0;

    double **ety_2d_plane;

    ety_2d_plane=init2DdoublePlane(time_length,cells);

        for (int time=0; time < time_length; time++) {

        double J;

        for ( int x = 1; x < x_length-1 ; x++ ) {
            if(x==excite_point) {
                J=src_J[time];
            }else{
                J=0.0;
            }

            ey[x]=coef1[x]*ey[x]-coef2[x]*(hz[x]-hz[x-1])-coef3[x]*J;

        }

        for(int x=0;x<x_length-1;x++){
            hz[x]=hz[x]-coef4*(ey[x+1]-ey[x]);
        }

        for(int x=0;x<x_length;x++){
            ety_2d_plane[time][x]=ey[x];
            if(ey[x]>ey_max) ey_max=ey[x];
            if(ey_min>ey[x]) ey_min=ey[x];
        }

        symmetryCheck(ey,x_length,time);
        antisymmetryCheck(hz,x_length-1,time);

    } // time-loop

    printf("(ey max)(x1.1)  ey max=%.15f\n",ey_max*1.1);
    printf("(ey min)(x1.1)  ey min=%.15f\n",ey_min*1.1);

    free(eps);
    free(sigma);
    free(coef1);
    free(coef2);
    free(coef3);
    free(hz);
    free(ey);

    return (double const * const *)ety_2d_plane;

}
