#include <stdio.h>
#include <stdlib.h>

#include "../../common_include/common_parameter.h"
#include "../../common_include/init2DdoublePlane.h"
#include "../../common_include/symmetryCheck.h"
#include "../../common_include/antisymmetryCheck.h"

double **set1DEyHz(
    double *coef1,
    double *coef2,
    double *coef3,
    double coef4,
    double *ey,
    double *hz,
    double *src_J,
    int excite_point,
    int calc_time_length
) {

    
    double ey_max=0.0;
    double ey_min=0.0;

    static double **ety_2d_plane;

    ety_2d_plane=init2DdoublePlane(calc_time_length,cells);

        for (int time=0; time < calc_time_length; time++) {

        double J;

        for ( int x = 1; x < cells-1 ; x++ ) {
            if(x==excite_point) {
                J=src_J[time];
            }else{
                J=0.0;
            }

            ey[x]=coef1[x]*ey[x]-coef2[x]*(hz[x]-hz[x-1])-coef3[x]*J;

        }

        for(int x=0;x<cells-1;x++){
            hz[x]=hz[x]-coef4*(ey[x+1]-ey[x]);
        }

        for(int x=0;x<cells;x++){
            ety_2d_plane[time][x]=ey[x];
            if(ey[x]>ey_max) ey_max=ey[x];
            if(ey_min>ey[x]) ey_min=ey[x];
        }

        symmetryCheck(ey,cells,time);
        antisymmetryCheck(hz,cells-1,time);

    } // time-loop

    // for(int time=0;time<calc_time_length;time++){
    //     printf("time=%d\n",time);
    //     for(int x=0;x<cells;x++){
    //         printf("%d,%f\n",x,ety_2d_plane[time][x]);
    //     }
    // }

    // printf("(in set ey hz)ey max=%.15f\n",ey_max);
    // printf("(in set ey hz)ey min=%.15f\n",ey_min);
    printf("(in set ey hz)(x1.1)  ey max=%.15f\n",ey_max*1.1);
    printf("(in set ey hz)(x1.1)  ey min=%.15f\n",ey_min*1.1);

    return ety_2d_plane;

}
