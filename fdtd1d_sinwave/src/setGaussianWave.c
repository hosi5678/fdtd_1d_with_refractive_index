#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "../../common_include/common_parameter.h"
#include "../../common_include/setGaussianWave.h"
#include "../../common_include/set1DDoubleCSV_Column.h"
#include "../../common_include/checkAlloc1DDouble.h"
#include "../../common_include/getFilePath.h"
#include "../../common_include/fft.h"

double *setGaussianWave(int length){

    static double *gaussian;

    double I0=pulseAmplitude;

    gaussian=checkAlloc1DDouble("in gaussian",length);

    // #pragma omp parallel for
    for(int i=0;i<length;i++){
		gaussian[i]=I0*exp(-gaussian_alpha*pow((i-gaussianPeaktimePosition),2.0));
	}

    char *file_path;
    file_path=getFilePath(csv_dir,"input_gaussian_time",csv_extension);

    // #pragma omp parallel for
    set1DDoubleCSV_Column(gaussian,file_path,length);

    // for fft
    double *fft_gaussian;
    fft_gaussian=checkAlloc1DDouble("in gaussian wave setting",fft_length);

    for(int time=0;time<fft_length;time++){
        fft_gaussian[time]=gaussian[time];
    }

    // int csv_dir_len;
    // csv_dir_len=strlen(csv_dir);

    // int func_name_len;
    // func_name_len=strlen(__func__);

    // int extension_len;
    // extension_len=strlen("_fft.csv");

    // char *file_path;
    // file_path=(char *)calloc(csv_dir_len+func_name_len+extension_len+1,sizeof(char));

    // strcat(file_path,csv_dir);
    // strcat(file_path,__func__);
    // strcat(file_path,"_fft.csv");


    file_path=getFilePath(csv_dir,"after_fft_gaussian_freq",csv_extension);

    // printf("(in gaussian) %s\n",file_path);

    fft(fft_gaussian,file_path,fft_length);

    return gaussian;

}
