#include <stdio.h>
#include "../libastro.h"

int main(){
	int year = 2010;
	printf("days from Jan 1, 2010 to epoch: %f\n", astro_getDaysFromEpoch(year));
	year = 2009;
	printf("days from Jan 1, 2009 to epoch: %f\n", astro_getDaysFromEpoch(year));
	year = 2026;
	printf("days from Jan 1, 2026 to epoch: %f\n", astro_getDaysFromEpoch(year));
	return(0);
}
