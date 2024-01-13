#include <stdio.h>
#include <stdlib.h>

#include "../../common_include/setSigma.h"
#include "../../common_include/common_parameter.h"

double *setSigma(int length){

    double *sigma;

    sigma=(double *)calloc(length,sizeof(double));

    if(NULL==sigma){
        printf("can't allocate sigma.\n");
        exit(1);
    }

    for(int i=0;i<length;i++){
        sigma[i]=0.0;
    }

    return sigma;

}
