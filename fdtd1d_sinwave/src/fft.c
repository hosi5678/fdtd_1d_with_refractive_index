// #include "fft.h"
// #include "calc_param.h"
// #include "put_memo.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../common_include/common_parameter.h"
#include "../../common_include/fft.h"
#include "../../common_include/dft.h"
#include "../../common_include/swap.h"
#include "../../common_include/checkAlloc1DDouble.h"
#include "../../common_include/checkAlloc1DInt.h"
#include "../../common_include/set1DDoubleCSV_Column.h"
#include "../../common_include/getPeak.h"
#include "../../common_include/getFilePath.h"

const double *fft(const double *srcWave,const char *src_file_name,int length){

	static double *wave;
	time_t start_clock,end_clock;

	start_clock=clock();

	printf("fft caluculation start..\n");

	wave=checkAlloc1DDouble("in fft.",length);

	for(int time=0;time<length;time++){
		wave[time]=srcWave[time];
	}
	
	int k1,num,nhalf,phi,phi0;
	int *rot;

	double s,sc,c,a0,b0;
	double *y;
	double *power;

	power=checkAlloc1DDouble("(in fft) power..",length);

	rot=checkAlloc1DInt("(in fft) rot..",length);

	y=checkAlloc1DDouble("(in fft) y..",length);

	nhalf=length/2;
	num=length/2;

	sc=2.0*pi/length;

	while(num>=1){

	for(int j=0;j<length;j+=2*num){

		phi=rot[j]/2;
			phi0=phi+nhalf;
			c=cos(sc*phi);
			s=-sin(sc*phi);

		for(int k=j;k<j+num;k++){

         k1=k+num;

         a0=wave[k1]*c-y[k1]*s; 
			b0=wave[k1]*s+y[k1]*c;

         wave[k1]=wave[k]-a0;
			y[k1]=y[k]-b0;

         wave[k]=wave[k]+a0;
			y[k]=y[k]+b0;

         rot[k]=phi;
			rot[k1]=phi0;

        }
	}

	num=num/2;
	
	}

	for(int i=0;i<length-1;i++){
		int j;
		if((j=rot[i])>i){

			swap(&wave[i],&wave[j]);
			swap(&y[i],&y[j]);

	}

		wave[i]=sqrt(pow(wave[i],2.0)+pow(y[i],2.0))/length;

	}

	// printf("in fft file_name=%s\n",src_file_name);

	set1DDoubleCSV_Column(wave,src_file_name,length/2);

	// char *file_name;
	// file_name=getFilePath(csv_dir,"peak_of_fft_sinwave",csv_extension);

	// getPeak(wave,file_name,length/2);

	end_clock=clock();

	printf("(fft) caluculation finished. time=%f(sec)\n", (double)(end_clock-start_clock)/CLOCKS_PER_SEC);

	// free(wave);
	free(power);
	free(rot);
	free(y);

	return wave;

}
