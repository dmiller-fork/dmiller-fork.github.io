#include <stdio.h>
#include "../libastro.h"

int main()
{
	int year = 2010;
	int day = 355;
	char* constellation = astro_getConstellation(year, day);
	printf("constellation is: %s\n", constellation);
	return(0);
}
