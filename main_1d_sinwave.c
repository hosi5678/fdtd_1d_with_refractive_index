// copyright kenicni hoshi hosi5678@gmail.com Copyright free.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// 定数の設定
#include "./common_files/include/common_parameter.h"
#include "./common_files/include/init2DdoublePlane.h"
#include "./common_files/include/getFilePath.h"
#include "./common_files/include/setSinWave.h"
#include "./common_files/include/set1DEyHz.h"
#include "./common_files/include/set1DEyHz_half_calc.h"

#include "./fdtd1d_sinwave/include/memo_sinwave.h"

int main(int argc,char **argv) {

    printf("sin Wave Excitation.\n");

    time_t start_clock, end_clock;

    start_clock = clock();

    printf("argc=%d,argv=%s\n",argc,argv[1]);


    int x_cells=1+2*(air_layer_half_side+reflactive_layer_half_side+pml_layer_half_side);

    int excite_point=air_layer_half_side+reflactive_layer_half_side+pml_layer_half_side; //(cells-1)/2;

    int calculation_timestep=fft_length;

    printf("(main) cells=%d\n",x_cells);
    printf("(main) calculation timestep=%d\n",calculation_timestep);

    const int angular_frequency_num=atoi(argv[1]);

    printf("angular frequency number=%d\n",angular_frequency_num);

    double *exciteWave;

    // wave initialize
    exciteWave=setSinWave(angular_frequency_num,calculation_timestep);

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

    memo_sinwave(angular_frequency_num,x_cells);

    free(exciteWave);
    free(ey_t_plane);

    end_clock = clock();

    printf("(main) processing time=%f(sec)\n", (double)(end_clock-start_clock)/CLOCKS_PER_SEC);

    return 0;
}
