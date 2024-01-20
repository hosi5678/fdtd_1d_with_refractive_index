#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/common_parameter.h"
#include "../include/frequency_analysis.h"
#include "../include/fft.h"
#include "../include/dft.h"
#include "../include/checkAlloc1DDouble.h"
#include "../include/check_2_n_power.h"

const double *frequency_analysis(
    const double *srcVec,
    const char *src_file_name,
    int length
) {

    FILE *fp;

    double *vec;
    const double *ret_vec;

    char *file_name;

    int flag=check_2_n_power(length);

    vec=checkAlloc1DDouble("in frequency analysis.",length);

    for(int i=0;i<length;i++){
        vec[i]=srcVec[i];
    }

    if(flag==0) {
        printf("use fft.\n");
        ret_vec=fft(vec,src_file_name,length);
    } else {
        printf("use dft.\n");
        ret_vec=dft(vec , src_file_name, fft_length);
    }

        free(vec);
        return ret_vec;
}
