#pragma once

#include "abstract_parser_interface.hpp"


class sames : virtual protected abstract_parser_interface,
              virtual protected program_data
{
    /* Флаг отправки совпадений */
    bool is_send;

public:
    explicit sames(string user_input) : is_send(false) {
        user_input_regular = user_input;
    }

    explicit sames() = default;
    virtual ~sames() = default;

    inline void count_of_sames(string) override;
    void print_sames(string) override;
    bool send_sames_to_file(string, string) override;

    /* Для отладки работы */
    /* debug = 1 */
    string& get_user_input(string) noexcept;
};


inline void sames::count_of_sames(string path) {
    in_file.open(path, std::ios::in | std::ios::binary);
    
    if (in_file.is_open()) {
        try {
            std::regex regular(user_input_regular);
            std::cmatch match;

            int count_of_matches = 0;
            while (!in_file.eof())  
            {
                string line;
                /* Считываем очередную строку из файла */
                getline (in_file, line);

                if (std::regex_match(line.c_str(), match, regular))
                    ++count_of_matches;
            }
            std::cout << "Count of matches: " << count_of_matches << "\n";
        } catch (const std::regex_error& re) {
            std::cerr << "Error: Incorrect regular\n";
        }

        in_file.close();
    }
    else {
        errors err;
        std::cerr << "Can't open file: " << path << std::endl;
        
        exit(err.CANT_OPEN_FILE);
    }
}

void sames::print_sames(string path) {
    in_file.open(path, std::ios::in | std::ios::binary);
    
    if (in_file.is_open()) {
        try {
            std::regex regular(user_input_regular);
            std::cmatch match;


            while (!in_file.eof())  
            {
                string line;
                /* Считываем очередную строку из файла */
                getline (in_file, line);

                if (std::regex_match(line.c_str(), match, regular))
                    std::cout << line << std::endl;
            }
            // std::cout << "Count of matches: " << count_of_matches << "\n";
            in_file.close();
        } catch (const std::regex_error& re) {
            std::cerr << "Incorrect regular\n";
        }
    }
    else {
        errors err;
        std::cerr << "Can't open file: " << path << std::endl;
        
        exit(err.INVALID_KEY);
    }
}

bool sames::send_sames_to_file(string to_send, string direct) {
    out_file.open(to_send, std::ios::app | 
                           std::ios::out | 
                           std::ios::binary);

    in_file.open(direct, std::ios::in | std::ios::binary);

    if (out_file.is_open() && in_file.is_open()) { 
        /* Работа */
        try {
            std::regex regular(user_input_regular);
            std::cmatch match;

            int in_conditional = 0;

            while (!in_file.eof())
            {   
                string line;
                /* Считываем строку из файла */
                getline(in_file, line);
                if (std::regex_match(line.c_str(), match, regular)) {
                    out_file << line;
                    out_file << "\n";

                    ++in_conditional;
                }
            }
            if (in_conditional > 0) is_send = true;
            
        } catch (const std::regex_error& re) {
            std::cerr << "Incorrect regular\n";
        }
        in_file.close();
        out_file.close();
    }
    else if (!out_file.is_open() || !in_file.is_open()) 
    {
        errors err;
        std::cerr << "Can't open a file\n";
        exit(err.CANT_OPEN_FILE);
    }
    else {
        errors err;
        std::cerr << "Fatal error\n";
        exit(err.FATAL_ERROR);
    }

    return is_send;
}

#if debug

string& sames::get_user_input(string input) noexcept {
    user_input_regular = input;
};

#endif 