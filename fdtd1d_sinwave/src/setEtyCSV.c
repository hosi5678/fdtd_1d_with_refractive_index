#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../../common_include/common_parameter.h"
#include "../../common_include/setEtyCSV.h"

void setEtyCSV(double const *const *ety_2d_plane, char *src_file_name, int length) {

    FILE *fp;

    int fd, pmode, option; 

    option = O_CREAT | O_TRUNC | O_RDWR ;
    pmode  = S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH ;

    int file_name_len;
    file_name_len = strlen(src_file_name);

    char *file_name;
    file_name = (char *)calloc(file_name_len + 1, sizeof(char));

    strcpy(file_name, src_file_name);

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
            for (int x = 0; x < cells; x++) {
                if (x == cells - 1) {
                    fprintf(fp, "%d\n", x);
                } else {
                    fprintf(fp, "%d,", x);
                }
            }

            for (int time = 0; time < length; time++) {
                fprintf(fp, "%d,", time);  // timestepの書き込み
                for (int x = 0; x < cells; x++) {
                    if (x == cells - 1) {
                        fprintf(fp, "%.20f\n", ety_2d_plane[time][x]);
                    } else {
                        fprintf(fp, "%.20f,", ety_2d_plane[time][x]);
                    }
                }
            }

            free(file_name);
            close(fd);
            fclose(fp);
            // write here
        }

    }

}
