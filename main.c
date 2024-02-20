#include "temp_api.h"

int main ()
{
    struct temperature_data data[100];
    int n = 6;
    data[0].year = 2013; data[0].month = 11; data[0].day = 5; data[0].hour = 12; data[0].minute = 48; data[0].t = -1;
    data[1].year = 2017; data[1].month = 9; data[1].day = 2; data[1].hour = 13; data[1].minute = 1; data[1].t = 7;
    data[2].year = 2013; data[2].month = 12; data[2].day = 10; data[2].hour = 14; data[2].minute = 2; data[2].t = -7;
    data[3].year = 2018; data[3].month = 11; data[3].day = 15; data[3].hour = 21; data[3].minute = 3; data[3].t = 3;
    data[4].year = 2019; data[4].month = 1; data[4].day = 28; data[4].hour = 6; data[4].minute = 4; data[4].t = -17;
    data[5].year = 2013; data[5].month = 8; data[5].day = 11; data[5].hour = 12; data[5].minute = 31; data[5].t = 21;
    printf("Average 11 month Temp = %.3f\n", average_monthly_temperature(data, 2013, 11, n));
    printf("Min 11 month Temp = %d\n", min_monthly_temperature(data, 2013, 11, n));
    printf("Max 11 month Temp = %d\n", max_monthly_temperature(data, 2013, 11, n));
    printf("Average 2013 year Temp = %.3f\n", average_year_temperature(data, 2013, n));
    printf("Min 2013 year Temp = %d\n", min_year_temperature(data, 2013, n));
    printf("Max 2013 year Temp = %d\n", max_year_temperature(data, 2013, n));
    sort_by_temperature(data, n);
    write_file(data, "Temp_Data.txt", n);
    return 0;
}