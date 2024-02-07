#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../include/common_parameter.h"
#include "../include/set_vec_timestep_csv.h"
#include "../include/set1DDoubleCSV_Row.h"
#include "../include/getFilePath.h"

void set_vec_timestep_csv(
    const char *src_dir_path,
    const char *file_name_head,
    double *vec,
    int x_length,
    int timestep ) {

    int file_name_path_length=strlen("./ey_timestep_cvs/ey_timestep_000000.csv");

        FILE *fp;
        int fd,option,pmode;

        option= O_CREAT | O_TRUNC | O_RDWR ;
        pmode= S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH ;

        // dir pathをコピーする
        char *dir_path=(char *)calloc(strlen(src_dir_path)+1,sizeof(char));
        strcpy(dir_path,src_dir_path);

        // file_nameの先頭をコピーする
        char *file_path=(char *)calloc(strlen(file_name_head)+1,sizeof(char));
        strcpy(file_path,file_name_head);

        // fileの番号を6桁に0詰めで固定する
        // buffer sizeを大きく取る。char file_number[20]は解放の必要なし。
        char file_number[10];
        snprintf(file_number,sizeof(file_number),"%06d",timestep);

        char *file_name;
        file_name=(char *)calloc( file_name_path_length + 1 ,sizeof(char) );

        strcpy(file_name,src_dir_path);
        strcat(file_name,file_path);
        strcat(file_name,file_number);
        strcat(file_name,csv_extension);

        // printf("file_name=%s\n",file_name);

        fd=open(file_name, option, pmode);

        if(fd == -1){
           perror("can not open the file..");
           exit(1);
        }else{

        fp=fdopen(fd,"w");

        if(NULL==fp){
            perror(file_name);
            perror(" cannot file open..\n");
            free(file_name);
            close(fd);
        }else{

            // x axisの書き込み
            for (int x = 0; x < x_length; x++) {
                if(x==x_length-1){
                  fprintf(fp, "%d\n", x);
                }else{
                  fprintf(fp, "%d,", x);
                }
            }

            // dataの書き込み
            for (int x = 0; x < x_length; x++) {
                if(x==x_length-1){
                  fprintf(fp, "%.20f\n", vec[x]);
                }else{
                  fprintf(fp, "%.20f,", vec[x]);
                }
            }

            fclose(fp);
        }

    }

        free(dir_path);
        free(file_path);
        free(file_name);

}
