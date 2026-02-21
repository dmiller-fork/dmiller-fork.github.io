#include <stdio.h>
#include "../libastro.h"

int main(){
	int year = 2010;
	printf("lunar phase on Jan 1, 2010: %f\n", astro_getLunarPhase(year));
	return(0);
}
