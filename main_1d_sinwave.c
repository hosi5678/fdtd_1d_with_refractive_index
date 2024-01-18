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
#include "./common_include/init2DdoublePlane.h"
#include "./common_include/getFilePath.h"
#include "./common_include/setSinWave.h"
#include "./common_include/set1DEyHz.h"
#include "./common_include/setEtyCSV.h"
#include "./common_include/set_ey_timestep_csv.h"
#include "./common_include/memo_sinwave.h"

int main(int argc,char **argv) {

    printf("Sin Wave Excitation.\n");

    time_t start_clock, end_clock;

    start_clock = clock();

    double dt=(dx/(sqrt(dimension)*light_speed))*time_margin;

    printf("argc=%d,argv=%s\n",argc,argv[1]);

    const int angular_frequency_num=atoi(argv[1]);
    
    double const * const *ety_const_2d_plane;
    double *exciteWave;

    char *file_name;

    int excite_point=(cells-1)/2;

    int calculation_timestep=fft_length;

    printf("(main) cells=%d\n",cells);
    printf("(main) calculation timestep=%d\n",calculation_timestep);
    printf("angular frequency number=%d\n",angular_frequency_num);

    // wave initialize
    exciteWave=setSinWave(angular_frequency_num,calculation_timestep);

    // 1 dimensional fdtd calculation
    ety_const_2d_plane=set1DEyHz(
        cells,
        calculation_timestep,
        exciteWave,
        excite_point,
        dt
    );

    file_name=getFilePath(csv_dir,"eyt_plane_2d",csv_extension);

    setEtyCSV(ety_const_2d_plane,file_name,fft_length);

    set_ey_timestep_csv(ety_const_2d_plane,"./ey_timestep_csvs/",fft_length);

    memo_sinwave(angular_frequency_num);

    free(exciteWave);

    end_clock = clock();

    printf("(main) processing time=%f(sec)\n", (double)(end_clock-start_clock)/CLOCKS_PER_SEC);

    return 0;
}
