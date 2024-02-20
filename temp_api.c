#include "temp_api.h"

int write_file (struct temperature_data* info, char* filename, int size) // Запись в файл
{
    FILE* f = fopen(filename, "w+");
    int i;
    for (i = 0; i < size; i++)
    {
        fprintf (f, "%d-%d-%d, %d:%d, temp = %d\n", info[i].year, info[i].month, info[i].day, info[i].hour, info[i].minute, info[i].t);
    }
    fclose(f);
    return i;
}

float average_monthly_temperature (struct temperature_data* info, uint16_t year, uint8_t month, int size) // Средняя месячная температура
{
    float temp = 0;
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        if (info[i].year == year && info[i].month == month)
        {
            temp += info[i].t;
            j++;
        }
    }
    if (j == 0)
    {
        puts("There is no data on the temperature in the selected month.");
        return -999;
    }
    return temp/j;
}

int min_monthly_temperature (struct temperature_data* info, uint16_t year, uint8_t month, int size) // Минимальная месячная температура
{
    int min = info[0].t, counter = 0;
    for (int i = 0; i < size; i++)
    {
        if (info[i].year == year && info[i].month == month)
        {
            if (info[i].t <= min)
            {
                min = info[i].t;
                counter++;
            }
        }
    }
    if (counter == 0)
    {
        puts("There is no data on the temperature in the selected month.");
        return -999;
    }
    return min;
}

int max_monthly_temperature (struct temperature_data* info, uint16_t year, uint8_t month, int size) // Максимальная месячная температура
{
    int max = info[0].t, counter = 0;
    for (int i = 0; i < size; i++)
    {
        if (info[i].year == year && info[i].month == month)
        {
            if (info[i].t >= max)
            {
                max = info[i].t;
                counter++;
            }
        }
    }
    if (counter == 0)
    {
        puts("There is no data on the temperature in the selected month.");
        return -999;
    }
    return max;
}

float average_year_temperature (struct temperature_data* info, uint16_t year, int size) // Средняя годовая температура
{
    float temp = 0;
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        if (info[i].year == year)
        {
            temp += info[i].t;
            j++;
        }
    }
    if (j == 0)
    {
        puts("There is no data on the temperature in the selected year.");
        return -999;
    }
    return temp/j;
}

int min_year_temperature (struct temperature_data* info, uint16_t year, int size) // Минимальная годовая температура
{
    int min = info[0].t, counter = 0;
    for (int i = 0; i < size; i++)
    {
        if (info[i].year == year)
        {
            if (info[i].t <= min)
            {
                min = info[i].t;
                counter++;
            }
        }
    }
    if (counter == 0)
    {
        puts("There is no data on the temperature in the selected year.");
        return -999;
    }
    return min;
}

int max_year_temperature (struct temperature_data* info, uint16_t year, int size) // Максимальная годовая температура
{
    int max = info[0].t, counter = 0;
    for (int i = 0; i < size; i++)
    {
        if (info[i].year == year)
        {
            if (info[i].t >= max)
            {
                max = info[i].t;
                counter++;
            }
        }
    }
    if (counter == 0)
    {
        puts("There is no data on the temperature in the selected year.");
        return -999;
    }
    return max;
}

void change_struct_line (struct temperature_data* info, int i, int j) // Замена выбранных строк в структуре
{
    struct temperature_data value;
    value = info[i];
    info[i] = info[j];
    info[j] = value;
}

unsigned int date_to_int (struct temperature_data* info)
{
    return info->year << 24 | info->month << 16 | info->day << 8 | info->hour + info->minute;
}

void sort_by_date (struct temperature_data* info, int size) // Сортировка по возрастанию даты
{
    for(int i = 0; i < size; ++i)
    {
        for(int j = i; j < size; ++j)
        {
            if(date_to_int(info + i) >= date_to_int(info + j))
            {
                change_struct_line(info, i, j);
            }      
        }
    }
}

void sort_by_temperature (struct temperature_data* info, int size) // Сортировка по возрастанию температуры
{
    for(int i = 0; i < size; ++i)
    {
        for(int j = i; j < size; ++j)
        {
            if(info[i].t >= info[j].t)
            {
                change_struct_line(info, i, j);
            }      
        }
    }
}


