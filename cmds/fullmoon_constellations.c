#include <stdio.h>
#include "../libastro.h"
#include "../libs/libkr.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

int is_all_digits(const char *s);

#define SIZE 13
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s <year>\n", argv[0]);
        return 1;
    }
	if (!is_all_digits(argv[1])) {
    	fprintf(stderr, "invalid year\n");
    	return 1;
	}

    const int year = kr_atoi(argv[1]);

	if (year < 0 || year > 9999) {
        fprintf(stderr, "year must be a 4-digit integer: 0000-9999\n");
        return 1;
    }

	int month, day;
	int days[SIZE];
	int len = astro_getFullMoonDays(year, days, SIZE);
	for(int i=0; i<len; i++){
		kr_monthday(year, days[i], &month, &day);
		const char *constellation =astro_getConstellation(year, days[i]);
		printf(YELLOW "%04d-%02d-%02d " RESET "Full Moon in the Constellation: " YELLOW "%s\n", year, month, day, constellation);
	}
	printf("\n\n\n");
	return(0);
}

int is_all_digits(const char *s)
{
    if (*s == '\0')  /* empty string */
        return 0;

    while (*s != '\0') {
		if (*s == '-')
			;
        else if (*s < '0' || *s > '9')
            return 0;
        s++;
    }
    return 1;
}

