#include "../../common_include/swap.h"

void swap(double *a,double *b){

	double temp;

/*
	temp a b
	 a   a b
	 a   b b
	 a   b a
*/
	temp=*a;

	*a=*b;

	*b=temp;
}
