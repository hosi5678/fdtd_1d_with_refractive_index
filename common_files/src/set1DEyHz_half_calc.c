#include <stdio.h>
#include <stdlib.h>

#include "../include/common_parameter.h"
#include "../include/get_dt.h"
#include "../include/init2DdoublePlane.h"
#include "../include/symmetryCheck.h"
#include "../include/antisymmetryCheck.h"
#include "../include/checkAlloc1DDouble.h"
#include "../include/setEps.h"
#include "../include/setSigma.h"
#include "../include/setCoef1.h"
#include "../include/setCoef2.h"
#include "../include/setCoef3.h"
#include "../include/setCoef4.h"
#include "../include/setCoef5.h"
#include "../include/getFilePath.h"
#include "../include/set1DDoubleCSV_Column.h"
#include "../include/set_vec_timestep_csv.h"

#include "../include/set1DEyHz_half_calc.h"

const double **set1DEyHz_half_calc(
    int x_length,
    int timestep,
    double *excite_J,
    int excite_point,
    double *ey_max,
    double *ey_min
) {

    double *sigma,*eps,*eps_hz;
    double *coef1,*coef2,*coef3,*coef4,*coef5;

    double *ey,*hz;

    double **ey_t=init2DdoublePlane(timestep,x_length);

    eps=setEps(x_length);
    eps_hz=setEps(x_length-1);
    sigma=setSigma(x_length);

    coef1=setCoef1(eps,sigma,x_length);
    coef2=setCoef2(eps,sigma,x_length);
    coef3=setCoef3(eps,sigma,x_length);
    coef4=setCoef4(eps_hz,x_length-1);
    coef5=setCoef5(eps_hz,x_length-1);

        // ey initialize
    ey=checkAlloc1DDouble("ey calloc",x_length);

    // hz initialize
    hz=checkAlloc1DDouble("hz calloc",x_length-1);

    for ( int time=0; time < timestep; time++ ) {

        // 励起点までは電流無しでの計算をする。
        for ( int x = 1; x <= excite_point ; x++ ) {
            ey[x]=coef1[x]*ey[x]-coef2[x]*(hz[x]-hz[x-1]);
        }

        // 励起点で電流項を付加する。
        int x=excite_point;

        ey[x]-=coef3[x]*excite_J[time];

        for (int x = excite_point+1 ; x < x_length-1 ; x++ ) {
            ey[x]=ey[x_length-1-x];
        }

        for(int x=0;x<(x_length-1)/2;x++){
            hz[x]=coef4[x]*hz[x]-coef5[x]*(ey[x+1]-ey[x]);
        }

        for(int x=(x_length-1)/2;x<x_length-1;x++){
            hz[x]=-1.0*hz[x_length-2-x];
        }

        for(int x=0;x<x_length;x++){
            if(ey[x]>*ey_max) *ey_max=ey[x];
            if(*ey_min>ey[x]) *ey_min=ey[x];
        }

        symmetryCheck(ey,x_length,time);
        antisymmetryCheck(hz,x_length-1,time);

            set_vec_timestep_csv(
                "./ey_timestep_csvs/",
                "ey_timestep_",
                ey,
                x_length,
                time
            );

            set_vec_timestep_csv(
                "./hz_timestep_csvs/","hz_timestep_",
                hz,x_length-1,
                time
            );
    
        for ( int x= 0 ; x < x_length ; x++ ){
            ey_t[time][x]=ey[x];
        }

    } // timestep-loop

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

    return (const double **)ey_t;

}
