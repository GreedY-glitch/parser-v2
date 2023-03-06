#pragma once

#ifndef ABSTRACT_PARSER_INTERFACE
#define ABSTRACT_PARSER_INTERFACE


/* Для обработки ошибок */
#include "errors.hpp"

/* STL */
#include <string>
#include <vector>
#include <fstream>  /* Для работы с файлами */
#include <regex>
#include <iostream>


using std::string;
using std::vector;

using std::ofstream;
using std::ifstream;


/* Общий класс, от которого все
   Остальные будут наследоваться
*/
class abstract_parser_interface
{
protected:
    /* Для чтения и записи из файла / в файл */
    ofstream out_file;
    ifstream in_file;

    virtual inline void count_of_sames(string) = 0;
    virtual void print_sames(string) = 0;
    virtual bool send_sames_to_file(string, string) = 0;
};

class program_data 
{
protected:
    /* 
        Класс default записей программы 
        (Информация о программе)
    */
    class {

        string name_of_program = "parser";
        string version = "0.1";

    } info_about_program;

    /* Ключи для запуска парсера */
    class {
    
    public:
        string csames = "-csames";
        string pstr =   "-pstr";
        string send =   "-send";
        /* 
           Для вывода документации 
           Информация о парсере.
           Версия:
           Основные ключи
           Синтаксис
           Информация для разработчика (ключ -db)
        */
       
        /* 
            Для данного ключа реализовать синтаксис 
            <name of program> <-help>
        */
        string help =   "-help";

        /* Для отладки программы */
        string db   =   "-db";
    } keys ;


    /* Массив для записи аргументов */
    vector<string> arguments;
    /* 
       Строка для записи регулярного выражения 
       Для проверки корректности введенного пути
    */

    string regular_path;

    /* Строка для записи регулярки, введенной пользователем 
       Инициализируется в классе user_interface
    */

    string user_input_regular;

    
    /* Переменные из функции main */
    int argc; char** argv;
public:
    explicit program_data() = default;
    virtual ~program_data() = default;
};


#endif  // ABSTRACT_PARSER_INTERFACE