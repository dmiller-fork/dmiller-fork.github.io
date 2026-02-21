#include <stdio.h>
#include "../libastro.h"

int main(){
	int year = 2010;
	int day = 355;
	double angle = astro_getAngleFromWinterSolstice(year, day);
	printf("the angle is: %f\n", angle);
	return(0);
}
