#include <stdint.h>
#include <stdio.h>

struct temperature_data
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    int8_t t; 
};

int write_file (struct temperature_data* info, char* filename, int size);
float average_monthly_temperature (struct temperature_data* info, uint16_t year, uint8_t month, int size);
int min_monthly_temperature (struct temperature_data* info, uint16_t year, uint8_t month, int size);
int max_monthly_temperature (struct temperature_data* info, uint16_t year, uint8_t month, int size);
float average_year_temperature (struct temperature_data* info, uint16_t year, int size);
int min_year_temperature (struct temperature_data* info, uint16_t year, int size);
int max_year_temperature (struct temperature_data* info, uint16_t year, int size);
void change_struct_line (struct temperature_data* info, int i, int j);
unsigned int date_to_int (struct temperature_data* info);
void sort_by_date (struct temperature_data* info, int size);
void sort_by_temperature (struct temperature_data* info, int size);
