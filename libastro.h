#ifndef LIBASTRO_H
double astro_getDaysFromEpoch(int year);
double astro_getLunarPhase(int year);
double astro_getSolarPhase(int year);
int astro_getFullMoonDays(int year, int days[], int len); //returns len of days_arr
double astro_getAngleFromWinterSolstice(int year, int day);
const char* astro_getConstellation(int year, int day);
#endif
