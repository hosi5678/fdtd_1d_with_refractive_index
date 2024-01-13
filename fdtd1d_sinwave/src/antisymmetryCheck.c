#include <stdio.h>
#include <stdlib.h>

#include "../../common_include/common_parameter.h"
#include "../../common_include/antisymmetryCheck.h"

void antisymmetryCheck(const double *vec,int length,int time){

    int half_length;
    half_length=length/2;

    for(int x=0;x<half_length;x++){

        if(vec[x]!=-1.0*vec[(length-1)-x]){
            printf("hz symmetry error.\n");
            printf("timestep=%d\n",time);
            printf("x=%d\n",x);
            printf("vec[%d]=%f\n",x,vec[x]);
            printf("vec[%d]=%f\n",x,vec[length-1-x]);
            exit(1);
        }

    }

}
