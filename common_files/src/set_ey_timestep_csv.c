#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../include/common_parameter.h"
#include "../include/set_ey_timestep_csv.h"
#include "../include/set1DDoubleCSV_Row.h"
#include "../include/getFilePath.h"

void set_ey_timestep_csv(
    double const* const *ety_2d_plane,
    char *src_dir_path,
    int time_length,
    int x_length
){

    int file_name_path_length=strlen("./ey_timestep_cvs/ey_timestep_000000.csv");

    // printf("file_name_path_length=%d\n",file_name_path_length);

    for(int time=0;time<time_length;time++){

        FILE *fp;
        int fd,option,pmode;

        option= O_CREAT | O_TRUNC | O_RDWR ;
        pmode= S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH ;

        char *dir_path=(char *)calloc(strlen(src_dir_path)+1,sizeof(char));
        strcpy(dir_path,src_dir_path);

        char *file_path=(char *)calloc(strlen("ey_timestep_")+1,sizeof(char));
        strcpy(file_path,"ey_timestep_");

        // buffer sizeを大きく取る。char file_number[20]は解放の必要なし。
        char file_number[20];
        snprintf(file_number,sizeof(file_number),"%06d",time);

        char *file_name;
        file_name=(char *)calloc( file_name_path_length + 1 ,sizeof(char) );

        strcpy(file_name,src_dir_path);
        strcat(file_name,file_path);
        strcat(file_name,file_number);
        strcat(file_name,csv_extension);

        set1DDoubleCSV_Row(ety_2d_plane[time],file_name,x_length);

        // fclose(fp);
        free(dir_path);
        free(file_path);
        free(file_name);

    } // time step loop

}
