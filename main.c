#include "temp_api.h"

int main(int argc, char *argv[])
{
    struct temperature_data* data = malloc(NUMBER_OF_LINE * sizeof(struct temperature_data));
    if (!data)
    {
        puts("Data reading error, the file is too large.");
        return -1;
    }
    int rez = 0, err = 0, value = 0;
    char* filename;
    while ((rez = getopt(argc, argv, "hf:m:r:as:")) != -1)
    {
        if (rez == 'h') // ключ h - выводим набор ключей приложения
        {
            print_information();
        }
        if (rez == 'f') // ключ f - считываем файл
        {
            err = read_file(data, optarg);
            filename = optarg;
            value = !value; 
        }
        if (rez == 'm') // ключ m - выводим статистику за месяц
        {
            if (err != -1)
            {
                print_table(data, NUMBER_OF_LINE, atoi(optarg));
            }
            value = 0;
        }
        if (rez == 'r' && err != -1) // ключ r - удаляем выбранную строку и перезаписываем файл
        {
            remove_lines(data, filename, atoi(optarg) - 1, err);
            value = 0;
        }
        if (rez == 'a' && err != -1) // ключ a - добавляем строку и перезаписываем файл
        {
            add_lines(data, filename, err);
            value = 0;
        }
        if (rez == 's' && err != -1) // ключ s - сортируем структуру и перезаписываем отсортированный файл
        {
            if(atoi(optarg) == 1) // 1 - сортируем структуру по температуре
            {
                sort_by_temperature(data, filename, err);
            }
            if(atoi(optarg) == 2) // 2 - сортируем структуру по дате
            {
                sort_by_date(data, filename, err);
            }
            value = 0;
        }
    }
    if (value == 1 && err != -1) // если ввели только название файла то выводим статистику по всему файлу
    {
        print_table(data, NUMBER_OF_LINE, 0);
    }
    if(argc == 1) // если ничего не ввели, то выводим набор ключей приложения
    {
        print_information();
    }
    free(data);
    return 0;
}
