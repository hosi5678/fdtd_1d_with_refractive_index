#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../include/set1DIntCSV_Column.h"

void set1DIntCSV_Column(const int *vec, const char *src_file_name, int length) {

    FILE *fp;

    int fd,option,pmode;

    option= O_CREAT | O_TRUNC | O_RDWR ;
    pmode= S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH ;

    int file_name_length;

    file_name_length = strlen(src_file_name);

    char *file_name;
    file_name = (char *)calloc(file_name_length + 1, sizeof(char) );

    strcpy(file_name, src_file_name);

    // printf("(in set csv file) file_name=%s\n",file_name);

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
            // write here
            for (int i = 0; i < length; i++) {
                fprintf( fp, "%d,%d\n" , i , vec[i] );
            }

            free(file_name);

            fclose(fp);
            // write here
        }

    }

}
