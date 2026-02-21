#include <stdio.h>
#include <math.h>
#include "libastro.h"

const double END_OF_2010 = 11.315;
const double LUNAR_MONTH = 29.530588;
const double SOLAR_YEAR = 365.242189;
static const char *constellations[] = {"Gemini", "Cancer", "Leo", "Virgo", "Libra", "Scorpio", "Sagittarius", "Capricorn", "Aquarius", "Pisces", "Aries", "Taurus"};


double astro_getDaysFromEpoch(int year)
{	
	int leap, i; 
	double day;
	if(year <= 2010){
		//count days backward to Jan 1 of year before epoch
		day = END_OF_2010 - 365;
		for(i = 2010; i > year; i--){
        	leap = (i%4 == 0 && i%100 != 0) || i%400 == 0;
        	day -= (leap) ? 366 : 365;
   		}
	} else {
		//count days forward to Jan 1 of year later than epoch
		day = END_OF_2010;
		for(i = 2011; i < year; i++){
            leap = (i%4 == 0 && i%100 != 0) || i%400 == 0;
            day += (leap) ? 366 : 365;
        }
	}
	return day;
}

double astro_getLunarPhase(int year)
{	
	double days = astro_getDaysFromEpoch(year);
	double phase;
	phase = fmod(days, LUNAR_MONTH);
	if (phase < 0) phase += LUNAR_MONTH;
	return phase;
}

double astro_getSolarPhase(int year)
{
	double days = astro_getDaysFromEpoch(year);
    double phase;
    phase = fmod(days, SOLAR_YEAR);
    if (phase < 0) phase += SOLAR_YEAR;
    return phase;
}

int astro_getFullMoonDays(int year, int days[], int len)
{
	int leap, days_in_year, i, j;
	double phase = astro_getLunarPhase(year);
	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
    days_in_year = (leap) ? 366 : 365;
	for(i=0, j=0; i<= days_in_year && j < len; i++){
		if(phase >= LUNAR_MONTH){
        	days[j] = i;
			phase -= LUNAR_MONTH;
			j++;
		}
		phase++;
	}
	return j;
}

double astro_getAngleFromWinterSolstice(int year, int day)
{
	double angle = astro_getSolarPhase(year);
	angle += fmod(day * 360.0 / SOLAR_YEAR,  360);
	if(angle > 360.0)
		angle -= 360.0;
	return(angle);
}

const char* astro_getConstellation(int year, int day)
{
    float angle = astro_getAngleFromWinterSolstice(year, day);
    return(constellations[(int) angle/30]);
}
