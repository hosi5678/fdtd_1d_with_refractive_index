#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "../../common_include/common_parameter.h"
#include "../../common_include/dft.h"
#include "../../common_include/checkAlloc1DDouble.h"
#include "../../common_include/set1DDoubleCSV_Column.h"
#include "../../common_include/getPeak.h"

const double *dft(const double *srcWave,char * src_file_name,int length){

    double *wave;
	double *power;

    time_t start_clock,end_clock;

    printf("dft calculation start..\n");
    start_clock=clock();

    wave=checkAlloc1DDouble("in dft(src wave)",length);

    for(int time=0;time<length;time++){
        wave[time]=srcWave[time];
    }

    power=checkAlloc1DDouble("in dft(power)",length);

    for(int t=0; t<length; t++) {

        double real = 0.0;
        double imaginary = 0.0;

        for(int k=0; k<length; k++) {
            real += wave[k]*cos(2.0*pi*k*t/length);
            imaginary += -wave[k]*sin(2.0*pi*k*t/length);
        }

			power[t]=sqrt(pow(real,2.0)+pow(imaginary,2.0))/length;
    }

    set1DDoubleCSV_Column(power,src_file_name,length/2);

    printf("dft calculation end..\n");

    end_clock=clock();

    printf("(dft) processing time=%f(sec)\n", (double)(end_clock-start_clock)/CLOCKS_PER_SEC);

    free(wave);
    free(power);

    return power;

}
