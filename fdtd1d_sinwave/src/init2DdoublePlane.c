#include <stdio.h>
#include <stdlib.h>

#include "../../common_include/init2DdoublePlane.h"

double **init2DdoublePlane(int y_length,int x_length){

    static double **plane;

    plane=(double **)calloc(y_length,sizeof(double *));

    // printf("sizeof double **=%ld\n",sizeof(plane));

    if(NULL==plane){
        printf("can't allocate 2D plane.\n");
        exit(1);
    }

    for(int y=0;y<y_length;y++){
        plane[y]=(double *)calloc(x_length,sizeof(double));

        if(NULL==plane[y]){
            printf("can't allocate 2D plane(y=%d)\n",y);
        }
    }

    return plane;

}
