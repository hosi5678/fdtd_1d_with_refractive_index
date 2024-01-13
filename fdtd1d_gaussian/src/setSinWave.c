#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#include "../../common_include/common_parameter.h"
#include "../../common_include/checkAlloc1DDouble.h"
#include "../../common_include/setSinWave.h"
#include "../../common_include/set1DDoubleCSV_Column.h"
#include "../../common_include/getFilePath.h"
#include "../../common_include/fft.h"
#include "../../common_include/getPeak.h"

double *setSinWave(int length){

	// usage :
	// length　データの長さ
	// angular frequency 角周波数、あるいは波長の数
	// usage(in main): setSinWave(16384,5);

	double *wave;

	char *file_name;

   double I0=pulseAmplitude;

   wave=checkAlloc1DDouble("sinwave set",length);

	for(int time=0;time<fft_length;time++){
		// wave[time]=I0*sin(2.0*pi*time*angular_frequency_num/(fft_length));
		// printf("wave[%d]=%f\n",time,wave[time]);
		wave[time]=sin(2.0*pi*time*3/fft_length);
	} 

	file_name=getFilePath(csv_dir,"input_sinWave_time",csv_extension);

	set1DDoubleCSV_Column(wave,file_name,fft_length);

	file_name=getFilePath(csv_dir,"after_fft_sinwave_freq",csv_extension);

	const double *fft_wave;

	fft_wave=fft(wave,file_name,fft_length);

	file_name=getFilePath(csv_dir,"getPeak_of_fft",csv_extension);

	getPeak(fft_wave,file_name,fft_length/2);


	// file_name=getFilePath(csv_dir,"input_sinWave_fft_freq",csv_extension);


	return wave;

}
