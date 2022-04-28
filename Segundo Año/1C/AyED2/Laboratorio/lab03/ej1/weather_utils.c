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

void year_max_temperature(WeatherTable a, int output[YEARS]) {
    for (unsigned int year = 0u; year < YEARS; ++year) {
        int max_temp_year = a[year][january][0]._max_temp;
        for (month_t month = january; month <= december; ++month) {
            for (unsigned int day = 0u; day < DAYS; ++day) {
                int max_temp_day = a[year][month][day]._max_temp;
                if (max_temp_day > max_temp_year) {
                    max_temp_year = max_temp_day;
                    output[year] = max_temp_year;
                }
            }
        }
        // printf("La mayor temperatura en Córdoba del año %d fue de: %d\n", year + FST_YEAR, max_temp_year);
    }
    // printf("\n");
}

char* month_name(int month) {
    char* months[MONTHS] = {
        "Enero",
        "Febrero",
        "Marzo",
        "Abril",
        "Mayo",
        "Junio",
        "Julio",
        "Agosto",
        "Septiembre",
        "Octubre",
        "Noviembre",
        "Diciembre",
    };

    return months[month];
}

void month_precipitations(WeatherTable a) {
    int month_val = january;
    for (unsigned int year = 0u; year < YEARS; ++year) {
        int max_prec_month_year = a[year][january][0]._rainfall;
        for (month_t month = january; month <= december; ++month) {
            int max_month_prec = a[year][month][0]._rainfall;
            for (unsigned int day = 0u; day < DAYS; ++day) {
                int day_prec = a[year][month][day]._rainfall;
                max_month_prec += day_prec;
            }
            if (max_month_prec > max_prec_month_year) {
                max_prec_month_year = max_month_prec;
                month_val = month;
            }
        }
        printf("El mes con mayor precipitaciones del año %d es %s con %d\n", year + FST_YEAR, month_name(month_val), max_prec_month_year);
    }
    printf("\n");
}