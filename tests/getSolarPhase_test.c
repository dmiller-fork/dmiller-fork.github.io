#include <stdio.h>
#include "../libastro.h"

int main(){
	int year = 2010;
	printf("Solar phase on Jan 1, 2010: %f\n", astro_getSolarPhase(year));
	return(0);
}
