#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/common_parameter.h"
#include "../include/setEps.h"
#include "../include/checkAlloc1DDouble.h"

double *setEps(int x_length){

    double *eps;

    printf("(in set eps) x_length=%d\n",x_length);

    eps=checkAlloc1DDouble("eps",x_length);

    for(int i=0;i<x_length;i++){
        eps[i]=eps0*pow(n_air,2.0);
    }

    if(x_length%2==1){ // ey

        int excite_point=(x_length-1)/2;

        for(int x=excite_point;x<=excite_point+reflactive_layer_half_side;x++){
            eps[x]=eps0*pow((double)n_glass,2.0);
        }

        for(int x=excite_point-reflactive_layer_half_side;x<excite_point;x++){
            eps[x]=eps[x_length-1-x];
        }

    }else{ // hz

        int excite_point=x_length/2;

        for(int x=excite_point;x<excite_point+reflactive_layer_half_side-1;x++){
            eps[x]=eps0*pow((double)n_glass,2.0);
        }

        for(int x=excite_point-reflactive_layer_half_side;x<excite_point;x++){
            eps[x]=eps[x_length-1-x];
        }

    }

    // for(int x=0;x<x_length;x++){
    //     printf("eps[%d]=%.20f\n",x,eps[x]);
    // }

    return eps;
}
