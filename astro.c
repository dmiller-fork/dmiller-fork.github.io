#include <stdio.h>
#include "libastro.h"
#include "libs/libkr.h"

int fullmoons_for_year(int year) {
    if (year < 0 || year > 9999) return -1;
	int SIZE = 13;
    int days[SIZE];
    int len = astro_getFullMoonDays(year, days, SIZE);

    for (int i = 0; i < len; i++) {
        int month, day;
        kr_monthday(year, days[i], &month, &day);
        const char *c = astro_getConstellation(year, days[i]);
        printf("%04d-%02d-%02d %s\n", year, month, day, c);
    }
    return len;
}
