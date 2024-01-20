#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/common_parameter.h"
#include "../include/frequency_analysis.h"
#include "../include/fft.h"
#include "../include/dft.h"
#include "../include/checkAlloc1DDouble.h"

void frequency_analysis(double const *const *srcVec,char *file_name,int point,
int fft_start,int length) {

    FILE *fp;

    double *vec;

    vec=checkAlloc1DDouble("in frequency analysis.",length);

    for(int time=fft_start;time<fft_start+length;time++){

        for (int x=0 ; x<cells ; x++ ) {

            if( x == point ){
                vec[time]=srcVec[time][x];
            }
        }

    }

    int check=fft_length;
    int flag=0;

        while ( check > 1) {
            if ( check%2 ==1 ) flag++;
                check>>=1;
        }

       if (flag > 0) {
            printf("flag=%d\n" , flag);
            printf("use dft.\n");
            dft(vec , file_name, fft_length);
        } else {
            printf("use fft.\n");
            fft(vec , file_name, fft_length);
        }
    }
