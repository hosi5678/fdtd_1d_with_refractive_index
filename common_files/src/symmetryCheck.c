#include <stdio.h>
#include <stdlib.h>

#include "../include/common_parameter.h"
#include "../include/symmetryCheck.h"

void symmetryCheck(const double *vec,int length,int time){

    int half_length;
    half_length=(int)(cells-1)/2;

    for(int x=0;x<half_length;x++){

        if(vec[x]!=vec[(length-1)-x]){
            printf("ez symmetry error.\n");
            printf("timestep=%d\n",time);
            printf("x=%d\n",x);
            printf("vec[%d]=%f\n",x,vec[x]);
            printf("vec[%d]=%f\n",x,vec[length-1-x]);
            exit(1);
        }

    }

}
