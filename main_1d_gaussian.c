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
#include "./common_include/getFilePath.h"
#include "./common_include/setGaussianWave.h"
#include "./common_include/set1DEyHz.h"
#include "./common_include/setEtyCSV.h"
#include "./common_include/set_ey_timestep_csv.h"
#include "./common_include/set1DDoubleCSV_Column.h"
#include "./common_include/fft.h"
#include "./common_include/dft.h"
#include "./common_include/getPeak.h"
#include "./common_include/gaussian_memo.h"

int main(void) {

    printf("Gaussian Pulse Excitation.\n");

    time_t start_clock, end_clock;

    start_clock = clock();

    double dt =(dx/(sqrt(dimension)*light_speed))*time_margin;

    double const *const *ety_const_2d_plane;
    double *exciteWave;

    char *file_name;

    int excite_point=(cells-1)/2;

    int fft_timestep_start=2*gaussianPeaktimePosition+cells;
    int fft_timestep_end=fft_timestep_start+fft_length;

    int calculation_timestep=fft_timestep_end;

    printf("(main) cells=%d\n",cells);
    printf("(main) fft length=%d\n",fft_length);
    printf("(main) calc timestep=%d\n",calculation_timestep);
    printf("(main) gaussian peak=%d\n",gaussianPeaktimePosition);

    // wave initialize
    exciteWave=checkAlloc1DDouble("excite wave",calculation_timestep);

    exciteWave=setGaussianWave(calculation_timestep);

    // 1 dimensional fdtd calculation
    ety_const_2d_plane=set1DEyHz(
       cells,
       calculation_timestep,
       exciteWave,
       excite_point,
       dt
    );

    file_name=getFilePath(csv_dir,"eyt_plane_2d",csv_extension);

    setEtyCSV(ety_const_2d_plane,file_name,fft_timestep_end);

    set_ey_timestep_csv(ety_const_2d_plane,"./ey_timestep_csvs/",calculation_timestep);

    // fft calculation , array allocation
    double *fft_array=checkAlloc1DDouble("in main fft alloc",fft_length);

    // data copy
    for(int time=fft_timestep_start;time<fft_timestep_start+fft_length;time++){

        for(int x=0;x<cells;x++){
            if(x==excite_point){
                fft_array[time-fft_timestep_start]=ety_const_2d_plane[time][x];
            }

        }
    }

    // fft_processing

    file_name=getFilePath(csv_dir,"before_fft_eyt_time",csv_extension);

    // set csv value
    set1DDoubleCSV_Column(fft_array,file_name,fft_length);

    file_name=getFilePath(csv_dir,"after_fft_eyt_freq",csv_extension);

    const double *fft_wave=fft(fft_array,file_name,fft_length);

    file_name=getFilePath(csv_dir,"getPeak_of_fft",csv_extension);

    getPeak(fft_wave,file_name,fft_length);

    gaussian_memo(fft_wave);

    free(exciteWave);
    free(fft_array);
    free(file_name);

    end_clock = clock();

    printf("(main) processing time=%f(sec)\n", (double)(end_clock-start_clock)/CLOCKS_PER_SEC);

    return 0;
}
