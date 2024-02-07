#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../include/common_parameter.h"
#include "../include/set2DVecCSV.h"

void set2DVecCSV(
    char *dir,
    char *src_file_name,
    const double **plane,
    int x_length,
    int timestep
) {

    FILE *fp;

    int fd, pmode, option; 

    option = O_CREAT | O_TRUNC | O_RDWR ;
    pmode  = S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH ;

    int file_name_len;
    file_name_len = strlen(dir)+strlen(src_file_name);

    char *file_name;
    file_name = (char *)calloc(file_name_len + 1, sizeof(char));

    strcpy(file_name,dir);
    strcat(file_name, src_file_name);

    fd=open(file_name, option, pmode);

    if(fd == -1){
        perror("(in setEtyCSV) cant open the file..");
        exit(1);
    }else{

        fp=fdopen(fd,"w");

        if(NULL==fp){
            close(fd);
        }else{
            // write here

            // x軸の書き込み
            for (int x = 0; x < x_length; x++) {
                if (x == x_length - 1) {
                    fprintf(fp, "%d\n", x);
                } else {
                    fprintf(fp, "%d,", x);
                }
            }

            // x軸の書き込み
            for (int time = 0; time < timestep; time++) {
                fprintf(fp, "%d,", time);  // timestepの書き込み
                for (int x = 0; x < x_length; x++) {
                    if (x == x_length - 1) {
                        fprintf(fp, "%.20f\n", plane[time][x]);
                    } else {
                        fprintf(fp, "%.20f,", plane[time][x]);
                    }
                }
            }

            free(file_name);
            close(fd);
            fclose(fp);
        }

    }

}
