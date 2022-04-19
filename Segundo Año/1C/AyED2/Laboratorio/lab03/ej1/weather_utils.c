#include <stdlib.h>
#include "array_helpers.h"
#include "weather.h"

int lower_min_temperature(WeatherTable a) {
    int res = a[0][january][0]._min_temp;
    for (unsigned int year = 0u; year < YEARS; ++year) {
        for (month_t month = january; month <= december; ++month) {
            for (unsigned int day = 0u; day < DAYS; ++day) {
                int min_temp = a[year][month][day]._min_temp;
                if (min_temp < res) {
                    res = min_temp;
                }
            }
        }
    }
    return res;
}