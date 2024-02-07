#include <stdio.h>
#include <stdlib.h>

#include "../include/common_parameter.h"
#include "../include/init2DdoublePlane.h"
#include "../include/symmetryCheck.h"
#include "../include/antisymmetryCheck.h"
#include "../include/checkAlloc1DDouble.h"
#include "../include/setEps.h"
#include "../include/setSigma.h"
#include "../include/setCoef1.h"
#include "../include/setCoef2.h"
#include "../include/setCoef3.h"
#include "../include/set1DEyHz.h"
#include "../include/getFilePath.h"
#include "../include/set1DDoubleCSV_Column.h"

const double * const *set1DEyHz(
    int x_length,
    int time_length,
    double *src_J,
    int excite_point,
    double dt,
    double *ey_max,
    double *ey_min


) {

    double *sigma,*eps;
    double *coef1,*coef2,*coef3;

    double *ey,*hz;

    eps=setEps(x_length);
    sigma=setSigma(x_length);

    coef1=setCoef1(eps,sigma,x_length);
    coef2=setCoef2(eps,sigma,x_length);
    coef3=setCoef3(eps,sigma,x_length);

        // ey initialize
    ey=checkAlloc1DDouble("ey calloc",x_length);

    // hz initialize
    hz=checkAlloc1DDouble("hz calloc",x_length-1);

    double coef4=dt/(u0*dx);

    double **ety_2d_plane;

    ety_2d_plane=init2DdoublePlane(time_length,x_length);

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
            if(ey[x]>*ey_max) *ey_max=ey[x];
            if(*ey_min>ey[x]) *ey_min=ey[x];
        }

        symmetryCheck(ey,x_length,time);
        antisymmetryCheck(hz,x_length-1,time);

    } // time-loop

    printf("(ey max)(x1.1)  ey max=%.15f\n",*ey_max*1.1);
    printf("(ey min)(x1.1)  ey min=%.15f\n",*ey_min*1.1);

    double *ey_range=checkAlloc1DDouble("in ey range.",2);
    ey_range[0]=*ey_max*1.1;
    ey_range[1]=*ey_min*1.1;

    char *file_path;
    file_path=getFilePath(csv_dir,"ey_range",csv_extension);

    set1DDoubleCSV_Column(ey_range,file_path,2);

    free(eps);
    free(sigma);
    free(coef1);
    free(coef2);
    free(coef3);
    free(hz);
    free(ey);

    free(ey_range);

    return (const double * const *)ety_2d_plane;

}
