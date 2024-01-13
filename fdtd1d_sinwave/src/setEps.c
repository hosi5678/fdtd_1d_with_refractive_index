#include <stdio.h>
#include <stdlib.h>

#include "../../common_include/common_parameter.h"
#include "../../common_include/setEps.h"

double *setEps(int length){

    double *eps;

    eps=(double *)calloc(length,sizeof(double));

    if(NULL==eps){
        printf("can't allocate eps\n");
        exit(1);
    }

    for(int i=0;i<length;i++){
        eps[i]=eps0;
    }


    return eps;
}
