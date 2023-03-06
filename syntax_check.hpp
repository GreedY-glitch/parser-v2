#pragma once


#include "abstract_parser_interface.hpp"


class syntax_check : protected program_data
{
    /* Флаги корректности синтаксиса */
    bool is_path;
    bool is_key;
    bool is_correct;

    /* Флаги на проверку порядка */
    bool first;
    bool second;

    void command_line_parameters();
public:
    syntax_check(int a, char** b) : is_path(false), 
                                    is_key(false), 
                                    is_correct(false),
                                    first(false),
                                    second(false) 
    {
        argc = a;
        argv = b;
    }

    explicit syntax_check() = default;

    ~syntax_check() = default;

    bool check_syntax();
};

void syntax_check::command_line_parameters()
{
    regular_path = "([/\\w]{1,}|[/\\w]{1,}[\\.][\\w]{1,})";
    std::regex regular_expr(regular_path);
    std::cmatch match;

    if (argc >= 4) {
        errors err;
        std::cerr << "Error: More than 4 arguments\n";
        exit(err.INCORRECT_ARGUMT); 
    }
    else 
        for (int i = 0; i < argc; i++) {
            string for_check = argv[i];

            if (std::regex_match(argv[1], match, regular_expr))
                first = true;
            if (argc > 2)
                if (strcmp(argv[2], keys.csames.c_str()) ||
                    strcmp(argv[2], keys.pstr.c_str())   ||
                    strcmp(argv[2], keys.send.c_str())   ||
                    strcmp(argv[2], keys.db.c_str()))
                    { second = true; }

            arguments.push_back(for_check);
        }
}

bool syntax_check::check_syntax()
{
    command_line_parameters();

    std::regex regular_expr(regular_path);
    std::cmatch match;

    vector<string>::const_iterator c_iter;
    for (c_iter = arguments.begin(); c_iter != arguments.end(); 
                    ++c_iter)
    {
        string arg = *c_iter;

        if (std::regex_match(arg.c_str(), match, regular_expr))
            is_path = true;
        if ((arg == keys.csames)      ||
                 (arg == keys.pstr)   ||
                 (arg == keys.send)   ||
                 (arg == keys.db)     ||
                 (arg == keys.help))
        { is_key = true; }
    }   

    if (!(first & second)) {
        errors err;
        std::cerr << "Error: Incorrect order or invalid key\n";
        exit(err.INCORRECT_SYNTAX);
    }

    if (is_path & is_key) {
        is_correct = true;
    }

    return is_correct;
    
}