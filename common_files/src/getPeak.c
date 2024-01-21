#include <stdio.h>
#include <stdlib.h>

#include "../include/common_parameter.h"
#include "../include/getPeak.h"
#include "../include/checkAlloc1DInt.h"

const int *getPeak(const double *wave,const char *src_file_name,int length){

    FILE *fp;
    fp=fopen(src_file_name,"w");

    if(NULL==fp){
        printf("(get peak) file open error.%s\n",src_file_name);
        exit(1);
    }

    int *peak;

    peak=checkAlloc1DInt("peak",fft_peak_number);

    int count=0;

	for(int i=0;i<length-2;i++){

		if(wave[i+1]>wave[i] && wave[i+1]>wave[i+2]){
			if(count<fft_peak_number){
                    printf("%d,%.15f\n",i+1,wave[i+1]);
                    fprintf(fp,"%d,%.15e\n",i+1,wave[i+1]);
                    peak[count]=i+1;
                count++;

            }

		}
	}

    fclose(fp);

    return (const int *)peak;

}
