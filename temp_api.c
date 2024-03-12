#include "temp_api.h"

int write_file(struct temperature_data *info, char *filename, int size) // Запись в файл
{
    FILE *f = fopen(filename, "w+");
    if (f == NULL)
    {
        printf("File opening error. Invalid file format.\n");
        return -1;
    }
    int i;
    for (i = 0; i < size; i++)
    {
        fprintf_line(info[i], f);
    }
    fclose(f);
    return i;
}

int read_file(struct temperature_data *info, char *filename) // Чтение файла
{
    FILE *f = fopen(filename, "r");
    int rezult_sscanf = 0, err_counter = 0;
    if (f == NULL)
    {
        printf("File opening error. Invalid file format.\n");
        return -1;
    }
    int i = 0;
    info[0].line_error[13] = 0;
    char line[LINE_SIZE];
    while (fgets(line, LINE_SIZE, f) && i < NUMBER_OF_LINE)
    {
        rezult_sscanf = sscanf(line, "%d;%d;%d;%d;%d;%d", &info[i].year, &info[i].month, &info[i].day, &info[i].hour, &info[i].minute, &info[i].t);
        if (rezult_sscanf == 6)
        {
            i++;
        }
        if (rezult_sscanf != -1 && rezult_sscanf < 6)
        {
            if (sscanf(line, "%*d;%d", &info[0].line_error[0]) == 1)
            {
                info[0].line_error[info[0].line_error[0]]++;
            } 
            err_counter++;
        }
    }
    fclose(f);
    return i;
}

int fprintf_line(struct temperature_data info, FILE *f) // Запись данных в файл
{
    fprintf(f, "%4d;%2d;%2d;%2d;%2d;%2d\n", info.year, info.month, info.day, info.hour, info.minute, info.t);
}

int add_lines(struct temperature_data *info, char *filename, int size) // Добавление новой строки к старому файлу в конец файла
{
    printf("\nPuts the year, month, day, hour, minute and temperature separated by a space and press enter.\n");
    scanf("%d %d %d %d %d %d", &info[size].year, &info[size].month, &info[size].day, &info[size].hour, &info[size].minute, &info[size].t);
    printf("Your data: Year = %d; month = %d; day = %d; hour = %d; minute = %d; temp = %d; added on the %d line in %s.\n", info[size].year, info[size].month, info[size].day, info[size].hour, info[size].minute, info[size].t, size + 1, filename);
    write_file(info, filename, size + 1);
    return size+1;
}

int remove_lines(struct temperature_data *info, char *filename, int line_number, int size) // Удаление строк и перезапись обратно в файл без этих строк
{
    int i = 0, j = 0, k = 0;
    for (i = 0; i < size; i++)
    {
        if (i != line_number)
        {
            info[j++] = info[i];
        }
        else
        {
            printf("You deleted the line %d - %4d;%2d;%2d;%2d;%2d;%2d\n", i + 1, info[i].year, info[i].month, info[i].day, info[i].hour, info[i].minute, info[i].t);
            k = 1;
        }
    }
    if (k == 1)
    {
        write_file(info, filename, j);
    }
    return i;
}

float average_monthly_temperature(struct temperature_data *info, uint8_t month, int size) // Средняя месячная температура
{
    float temp = 0;
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        if (info[i].month == month)
        {
            temp += info[i].t;
            j++;
        }
    }
    return temp / j;
}

int min_monthly_temperature(struct temperature_data *info, uint8_t month, int size) // Минимальная месячная температура
{
    int min = 99;
    for (int i = 0; i < size; i++)
    {
        if (info[i].month == month)
        {
            if (info[i].t <= min)
            {
                min = info[i].t;
            }
        }
    }
    return min;
}

int max_monthly_temperature(struct temperature_data *info, uint8_t month, int size) // Максимальная месячная температура
{
    int max = -99;
    for (int i = 0; i < size; i++)
    {
        if (info[i].month == month)
        {
            if (info[i].t >= max)
            {
                max = info[i].t;
            }
        }
    }
    return max;
}

float average_year_temperature(struct temperature_data *info, uint16_t year, int size) // Средняя годовая температура
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
    return temp / j;
}

int min_year_temperature(struct temperature_data *info, uint16_t year, int size) // Минимальная годовая температура
{
    int min = info[0].t;
    for (int i = 0; i < size; i++)
    {
        if (info[i].year == year)
        {
            if (info[i].t <= min)
            {
                min = info[i].t;
            }
        }
    }
    return min;
}

int max_year_temperature(struct temperature_data *info, uint16_t year, int size) // Максимальная годовая температура
{
    int max = info[0].t;
    for (int i = 0; i < size; i++)
    {
        if (info[i].year == year)
        {
            if (info[i].t >= max)
            {
                max = info[i].t;
            }
        }
    }
    return max;
}

void change_struct_line(struct temperature_data *info, int i, int j) // Замена выбранных строк в структуре
{
    struct temperature_data value;
    value = info[i];
    info[i] = info[j];
    info[j] = value;
}

unsigned int date_to_int(struct temperature_data *info)
{
    return info->year << 24 | info->month << 16 | info->day << 8 | info->hour + info->minute;
}

void sort_by_date(struct temperature_data *info, char *filename, int size) // Сортировка по возрастанию даты
{
    printf("\nProgress Bar (please wait 100%% or close(x) the command line):\n");
    float y = 0, x = 100/(float)size;
    for (int i = 0; i < size; ++i)
    {
        for (int j = i; j < size; ++j)
        {
            if (date_to_int(info + i) >= date_to_int(info + j))
            {
                change_struct_line(info, i, j);
            }
        }
        y += x;
        printf("%.5f%% \r", y);
    }
    printf("100.00000%% \r");
    printf("\nThe data is sorted by date(2) and overwritten into a file %s.\n", filename);
    write_file(info, filename, size);
}

void sort_by_temperature(struct temperature_data *info, char *filename, int size) // Сортировка по возрастанию температуры
{
    printf("\nProgress Bar (please wait 100%% or close(x) the command line):\n");
    float y = 0, x = 100/(float)size;
    for (int i = 0; i < size; ++i)
    {
        for (int j = i; j < size; ++j)
        {
            if (info[i].t >= info[j].t)
            {
                change_struct_line(info, i, j); 
            }
        }
        y += x;
        printf("%.5f%% \r", y);
    }
    printf("100.00000%% \r");
    printf("\nThe data is sorted by temperature(1) and overwritten into a file %s.\n", filename);
    write_file(info, filename, size);
}

void print_table(struct temperature_data *info, int size,  uint8_t month) // Печать таблицы данных по температуре
{
    int i = 0, err_count = 0;
    if (month == 0)
    {
        i = !i;
    }
    else
    {
        i = month;
    }
    printf("\n Year  Month  Avg_Month_Temp  Min_Month_Temp  Max_Month_Temp  Err_Data_Count\n");
    printf("------------------------------------------------------------------------------\n");
    for (i; i < 13; i++)
    {
        int j = 0;
        while (j < 68)
        {
            printf(" ");
            if (j == 0)
            {
                j += print_number(info->year);
            }
            if (j == 8)
            {
                j += print_number(i);
            }
            if (j == 18)
            {
                j += print_number(average_monthly_temperature(info, i, size));
            }
            if (j == 34)
            {
                j += print_number(min_monthly_temperature(info, i, size));
            }
            if (j == 50)
            {
                j += print_number(max_monthly_temperature(info, i, size));
            }
            if (j == 67)
            {
                print_number(info[0].line_error[i]);
                err_count += info[0].line_error[i];
            }
            j++;
        }
        printf("\n");
        if (month != 0)
        {
            break;
        }
    }
    printf("------------------------------------------------------------------------------\n");
    if (month == 0)
    {
        printf("In %d year, Average Temp = %.2f, Min Temp = %d, Max Temp = %d, Error Data = %d.\n", info->year, average_year_temperature(info, info->year, NUMBER_OF_LINE), min_year_temperature(info, info->year, NUMBER_OF_LINE), max_year_temperature(info, info->year, NUMBER_OF_LINE), err_count);
    }
}

int print_number (int value) // Ф-я печати одной переменной, возвращает количество символов в переменной
{
    printf("%d",value);
    int counter = 0;
    if (value <= 0)
    {
        counter++;
    }
    while (value != 0)
    {
        value /= 10;
        counter++;
    }
    return counter;
}

void print_information (void) // Ф-я печати обрабатываемых ключей приложения
{
    printf("\nTemperature sensor statistics for the year. Please enter the following keys.\n");
    puts("----------------------------------------------------------------------------");
    puts("-h for help.");
    puts("-f and the name of the file .csv to download this file.");
    puts("-m output of statistics for the specified month.");
    puts("-r and the number of the line to be deleted.");
    puts("-a to add a line.");
    puts("-s and the number 1 or 2 to sort by temperature(1) or date(2).");
    puts("Attention! If you have selected the keys - r, a, s, then the selected file -f will be overwritten.");
}
