#pragma once

#include "sames.hpp"
#include "syntax_check.hpp"


class user_interface : // virtual protected sames,
                       // virtual protected syntax_check,
                       protected program_data
{
private:
    string user_regular;
    /* Корректность отработки программы */
    bool end_flag;

    void user_input() noexcept;
public:
    explicit user_interface() : end_flag(false) {}
    virtual ~user_interface() = default;

    bool start(int, char**);
    /* Для ключа -help */
    void print_help() noexcept;
};

void user_interface::user_input() noexcept 
{
    std::cout << "Regular for check: ";
    std::cin >> user_regular;
}

bool user_interface::start(int a_c, char** a_v) 
{
    /* Проверяем синтаксис */
    syntax_check sc(a_c, a_v);

    if (sc.check_syntax()) {
        user_input();   /* Ввод данных пользователем */
        /* Объект класса для проверок строк */
        sames sm(user_regular);

        /* Проверка ключей */
        string path_to_file;
        try {
            if (strcmp(a_v[2], keys.csames.c_str()) == 0)
            {  
                path_to_file = a_v[1];
                sm.count_of_sames(path_to_file);
                // std::cout << path_to_file << "1\n";
            }
            else if (strcmp(a_v[2], keys.pstr.c_str()) == 0)
            {  
                path_to_file = a_v[1];
                // std::cout << a_v[2];
                sm.print_sames(path_to_file);
                // std::cout << path_to_file << "2\n";
            }
            else if (strcmp(a_v[2], keys.send.c_str()) == 0)
            {  
                path_to_file = a_v[1];
                sm.send_sames_to_file("a.txt", path_to_file);
                // std::cout << path_to_file << "3\n";
            }
            else if (strcmp(a_v[2], keys.help.c_str()) == 0)
            {
                path_to_file = a_v[1];
                /* Выводим документацию */
                std::cout << "All possible keys:\n";
                
                std::cout << keys.csames << std::endl;
                std::cout << keys.pstr << std::endl;
                std::cout << keys.send << std::endl;
                std::cout << keys.help << std::endl;

                std::cout << "Just for developers:\n";
                std::cout << keys.db  << " " << "/* This key will appear soon  */\n";

                std::cout << "Syntax:\n";
                std::cout << "<name_of_program> <path_to_file> <key>\n";
            }
            /* Реализовать отладку (в новой версии парсера ) */
        } catch (const std::out_of_range& ofr) {
            std::cerr << "Vector isn't created\n" << std::endl;
        }

        end_flag = true;
    } 
    else {
        errors err;
        std::cerr << "Fatal error: parser can't recognize your input\n";
        exit(err.FATAL_ERROR);
    }

    return end_flag;
}