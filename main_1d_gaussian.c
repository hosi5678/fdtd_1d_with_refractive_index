// copyright kenicni hoshi hosi5678@gmail.com Copyright free.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// 定数の設定
#include "./common_files/include/common_parameter.h"
#include "./common_files/include/get_dt.h"
#include "./common_files/include/checkAlloc1DDouble.h"
#include "./common_files/include/getFilePath.h"
#include "./common_files/include/setGaussianWave.h"
#include "./common_files/include/set1DEyHz.h"
#include "./common_files/include/set1DEyHz_half_calc.h"
#include "./common_files/include/setEtyCSV.h"
#include "./common_files/include/set_vec_timestep_csv.h"
#include "./common_files/include/set1DDoubleCSV_Column.h"
#include "./common_files/include/getPeak.h"
#include "./common_files/include/frequency_analysis.h"

#include "./fdtd1d_gaussian/include/memo_gaussian.h"

int main(void) {

    printf("Gaussian Pulse Excitation.\n");

    time_t start_clock, end_clock;

    start_clock = clock();

    double *exciteWave;

    char *file_name;

    int x_cells=1+2*(air_layer_half_side+reflactive_layer_half_side+pml_layer_half_side);

    int excite_point=air_layer_half_side+reflactive_layer_half_side+pml_layer_half_side; //(cells-1)/2;

    int fft_timestep_start=2*gaussianPeaktimePosition+excite_point;
    int fft_timestep_end=fft_timestep_start+fft_length;

    int calculation_timestep=fft_timestep_end;

    printf("(main) x_cells(total)=%d\n",x_cells);
    printf("(main) fft length=%d\n",fft_length);
    printf("(main) calc timestep=%d\n",calculation_timestep);
    printf("(main) gaussian peak=%d\n",gaussianPeaktimePosition);
    printf("(main) excite point=%d\n",excite_point);

    // gaussian wave setting
    exciteWave=setGaussianWave(calculation_timestep);

    double ey_max=0.0;
    double ey_min=0.0;

    const double **ey_t_plane;

    // 1 dimensional fdtd calculation
    ey_t_plane=set1DEyHz_half_calc(
       x_cells,
       calculation_timestep,
       exciteWave,
       excite_point,
       &ey_max,
       &ey_min
    );

    // fft calculation , array allocation
    double *fft_array=checkAlloc1DDouble("in main fft alloc",fft_length);

    // data copy
    for(int time=fft_timestep_start;time<fft_timestep_start+fft_length;time++){
        fft_array[time-fft_timestep_start]=ey_t_plane[time][excite_point];
    }
    

    // fft_processing
    // file name setting
    file_name=getFilePath(csv_dir,"before_fft_ey_t_time",csv_extension);

    // set csv value
    set1DDoubleCSV_Column(fft_array,file_name,fft_length);

    file_name=getFilePath(csv_dir,"after_fft_ey_t_freq",csv_extension);

    const double *fft_wave=frequency_analysis(fft_array,file_name,fft_length);

    file_name=getFilePath(csv_dir,"getPeak_of_fft",csv_extension);

    const int *peak;

    peak=getPeak(fft_wave,file_name,fft_length);

    printf("(main) gaussian fft peak df=%d\n",(int)round(fft_length/(2.0*x_cells)));

    memo_gaussian(peak,&ey_max,&ey_min,x_cells,calculation_timestep);

    free(exciteWave);
    free(fft_array);
    free(file_name);

    end_clock = clock();

    printf("(main) processing time=%f(sec)\n", (double)(end_clock-start_clock)/CLOCKS_PER_SEC);

    return 0;
}
