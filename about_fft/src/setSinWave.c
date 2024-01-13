#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#include "../../common_include/common_parameter.h"
#include "../../common_include/checkAlloc1DDouble.h"
#include "../../common_include/setSinWave.h"
#include "../../common_include/set1DDoubleCSV_Column.h"
#include "../../common_include/getFilePath.h"

double *setSinWave(int length){

	// usage :
	// length　データの長さ
	// angular frequency 角周波数、あるいは波長の数
	// usage(in main): setSinWave(16384,5);

	static double *wave;

	char *file_name;

   double I0=pulseAmplitude;

   wave=checkAlloc1DDouble("sinwave set",length);

	for(int time=0;time<length;time++){
		wave[time]=I0*sin(2.0*pi*time*angular_frequency_num/(length));
		printf("wave[%d]=%f\n",time,wave[time]);
	} 

	file_name=getFilePath(csv_dir,"input_sinWave",csv_extension);

	set1DDoubleCSV_Column(wave,file_name,length);

	// file_name=getFilePath(csv_dir,"input_sinWave_fft_freq",csv_extension);


	return wave;

}
