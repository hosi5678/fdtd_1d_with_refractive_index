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

void set_ey_timestep_csv(double const* const *ety_2d_plane,char *src_dir_path,int length){

    int file_name_path_length=strlen("./ey_timestep_cvs/ey_timestep_000000.csv");

    // printf("file_name_path_length=%d\n",file_name_path_length);

    for(int time=0;time<length;time++){

        FILE *fp;
        int fd,option,pmode;

        option= O_CREAT | O_TRUNC | O_RDWR ;
        pmode= S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH ;

        char *dir_path=(char *)calloc(strlen(src_dir_path)+1,sizeof(char));
        strcpy(dir_path,src_dir_path);

        // printf("dir_path=%s,len=%ld\n",src_dir_path,strlen(src_dir_path));

        char *file_path=(char *)calloc(strlen("ey_timestep_")+1,sizeof(char));
        strcpy(file_path,"ey_timestep_");

        // printf("file_path=%s,len=%ld\n",file_path,strlen(file_path));


        // buffer sizeを大きく取る。char file_number[20]は解放の必要なし。
        char file_number[20];
        snprintf(file_number,sizeof(file_number),"%06d",time);

        char *file_name;
        file_name=(char *)calloc( file_name_path_length + 1 ,sizeof(char) );

        strcpy(file_name,src_dir_path);
        strcat(file_name,file_path);
        strcat(file_name,file_number);
        strcat(file_name,csv_extension);

        set1DDoubleCSV_Row(ety_2d_plane[time],file_name,cells);

        // printf("file_name=%s,len=%ld\n",file_name,strlen(file_name));
        // fd=open(file_name , option , pmode);

        // if (fd != -1) {
        //     fp=fdopen(fd,"w");

        //     if(fp != NULL){

        //         // x axisの書き込み
        //         for(int x=0;x<cells;x++){
        //             if(x==cells-1){
        //                 fprintf(fp,"%d\n",x);
        //             }else{
        //                 fprintf(fp,"%d,",x);
        //             }
        //         }

        //         // ey値の書き込み
        //         for(int x=0;x<cells;x++){
        //             if(x==cells-1){
        //                 fprintf(fp,"%.20f\n",ety_2d_plane[time][x]);
        //             }else{
        //                 fprintf(fp,"%.20f,",ety_2d_plane[time][x]);
        //             }
        //         }

        //     }else{
        //         perror("error.. cannot open the file..");
        //         free(dir_path);
        //         free(file_path);
        //         free(file_name);
        //         return;  // エラーが発生した場合は関数を終了する
        //     }

        // }else{
        //     close(fd);
        // }


        // fclose(fp);
        free(dir_path);
        free(file_path);
        free(file_name);

    } // time step loop

}
