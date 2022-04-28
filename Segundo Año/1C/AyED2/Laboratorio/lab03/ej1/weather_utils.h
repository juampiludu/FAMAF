#ifndef _WEATHER_UTILS_H
# define _WEATHER_UTILS_H

#include "array_helpers.h"

int lower_min_temperature(WeatherTable a);

void year_max_temperature(WeatherTable a, int output[YEARS]);

char* month_name(int month);

void month_precipitations(WeatherTable a);

#endif