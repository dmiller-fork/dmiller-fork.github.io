#include <stdio.h>
#include "../libastro.h"

int main(){
	int year = 2010;
	int capacity = 13;
	int days[capacity];
	int len = astro_getFullMoonDays(year, days, capacity);
	for(int i = 0; i < len; i++)
		printf("full moon days: %d\n", days[i]);
	return(0);
}
