// copyright xxxx
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

// 定数の設定
#include "./common_include/common_parameter.h"
#include "./common_include/checkAlloc1DDouble.h"
#include "./common_include/init2DdoublePlane.h"
#include "./common_include/setEps.h"
#include "./common_include/setSigma.h"
#include "./common_include/setCoef1.h"
#include "./common_include/setCoef2.h"
#include "./common_include/setCoef3.h"
#include "./common_include/getFilePath.h"
#include "./common_include/setSinWave.h"
#include "./common_include/setGaussianWave.h"
#include "./common_include/set1DEyHz.h"
#include "./common_include/setEtyCSV.h"
#include "./common_include/set_ey_timestep_csv.h"
#include "./common_include/set1DDoubleCSV_Column.h"
#include "./common_include/fft.h"
#include "./common_include/getPeak.h"
#include "./common_include/memo.h"

int main(void) {

    time_t start_clock, end_clock;

    start_clock = clock();

    double dt;

    // not setting time margin(couse 1D)
    dt =(dx/(sqrt(dimension)*light_speed))*time_margin;

    double *sigma;
    double *eps;

    double *coef1;
    double *coef2;
    double *coef3;

    double *ey;
    double *hz;

    double **ety_2d_plane;
    double const *const *ety_const_2d_plane;
    double *exciteWave;

    char *file_name;

    int excite_point;

    excite_point=(cells-1)/2;

    int fft_timestep_start;
    int fft_timestep_end;

    fft_timestep_start=0;//2*gaussianPeaktimePosition+cells; // sinのときは0にする。
    fft_timestep_end=fft_timestep_start+fft_length;

    int calculation_timestep;
    calculation_timestep=fft_timestep_end;

    printf("(main) cells=%d\n",cells);
    printf("(main) fft length=%d\n",fft_length);
    printf("(main) calc timestep=%d\n",calculation_timestep);
    printf("(main) gaussian peak=%d\n",gaussianPeaktimePosition);
    printf("angular frequency number=%d\n",angular_frequency_num);

    // ey initialize
    ey=checkAlloc1DDouble("ey calloc",cells);

    // hz initialize
    hz=checkAlloc1DDouble("hz calloc",cells-1);

    // wave initialize
    exciteWave=checkAlloc1DDouble("excite wave",calculation_timestep);

    // eps initialize
    eps=checkAlloc1DDouble("eps",cells);

    // sigma initialize
    sigma=checkAlloc1DDouble("sigma",cells);

    // coef1 initialize
    coef1=checkAlloc1DDouble("coef1",cells);

    // coef2 initialize
    coef2=checkAlloc1DDouble("coef2",cells);

    // coef3 initialize
    coef3=checkAlloc1DDouble("coef3",cells);

    eps=setEps(cells);

    sigma=setSigma(cells);

    // exciteWave=setGaussianWave(calculation_timestep);
    exciteWave=setSinWave(calculation_timestep);


    coef1=setCoef1(eps,sigma,cells);
    coef2=setCoef2(eps,sigma,cells);
    coef3=setCoef3(eps,sigma,cells);

    double coef4;

    coef4=dt/(u0*dx);

    // 1 dimensional fdtd calculation
    ety_2d_plane=set1DEyHz(
        coef1,
        coef2,
        coef3,
        coef4,
        ey,
        hz,
        exciteWave,
        excite_point,
        calculation_timestep
    );

    ety_const_2d_plane=(double const *const *)ety_2d_plane;

    file_name=getFilePath(csv_dir,"eyt_plane_2d",csv_extension);

    setEtyCSV(ety_const_2d_plane,file_name,fft_timestep_end);

    set_ey_timestep_csv(ety_const_2d_plane,"./ey_timestep_csvs/",fft_timestep_end);

    // fft calculation , array allocation
    double *fft_array;
    fft_array=checkAlloc1DDouble("in main fft alloc",fft_length);

    // data copy
    for(int time=fft_timestep_start;time<fft_timestep_start+fft_length;time++){

        for(int x=0;x<cells;x++){
            if(x==excite_point){
                fft_array[time-fft_timestep_start]=ety_2d_plane[time][x];
            }

        }
    }

    // fft_processing

    const double *fft_wave;

    file_name=getFilePath(csv_dir,"before_fft_eyt_time",csv_extension);

    // set csv value
    set1DDoubleCSV_Column(fft_array,file_name,fft_length);

    file_name=getFilePath(csv_dir,"after_fft_eyt_freq",csv_extension);

    fft_wave=fft(fft_array,file_name,fft_length);

    file_name=getFilePath(csv_dir,"getPeak_of_fft",csv_extension);

    getPeak(fft_wave,file_name,fft_length);

    // printf("func_name=%s,length=%ld\n",__func__,strlen(__func__));
    // printf("csv_dir=%s\n",csv_dir);

    memo(fft_wave);

    free(eps);
    free(sigma);
    free(coef1);
    free(coef2);
    free(coef3);
    free(hz);
    free(ey);

    free(exciteWave);
    free(ety_2d_plane);
    free(fft_array);
    free(file_name);

    end_clock = clock();

    printf("(main) processing time=%f(sec)\n", (double)(end_clock-start_clock)/CLOCKS_PER_SEC);

    return 0;
}
