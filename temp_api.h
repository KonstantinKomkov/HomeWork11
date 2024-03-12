#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define LINE_SIZE 25           // Количество данных в одной строке
#define NUMBER_OF_LINE 600000  // Количество строк в файле

struct temperature_data
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    int t;
    int line_error[13];
};

int write_file (struct temperature_data* info, char* filename, int size);
int read_file (struct temperature_data* info, char* filename);
int remove_lines (struct temperature_data* info, char* filename, int line_number, int size);
int fprintf_line (struct temperature_data info, FILE* f);
int add_lines(struct temperature_data *info, char *filename, int size);
float average_monthly_temperature (struct temperature_data* info, uint8_t month, int size);
int min_monthly_temperature (struct temperature_data* info, uint8_t month, int size);
int max_monthly_temperature (struct temperature_data* info, uint8_t month, int size);
float average_year_temperature (struct temperature_data* info, uint16_t year, int size);
int min_year_temperature (struct temperature_data* info, uint16_t year, int size);
int max_year_temperature (struct temperature_data* info, uint16_t year, int size);
void change_struct_line (struct temperature_data* info, int i, int j);
unsigned int date_to_int (struct temperature_data* info);
void sort_by_date (struct temperature_data* info, char* filename, int size);
void sort_by_temperature (struct temperature_data* info, char* filename, int size);
void print_table (struct temperature_data* info, int size, uint8_t month);
int print_number (int value);
void print_information (void);

