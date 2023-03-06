#pragma once


class errors {
public:
    explicit errors() = default;
   
    enum {
        INCORRECT_SYNTAX = -1,
        INCORRECT_ARGUMT = -2,
        CANT_OPEN_FILE   = 0xA,
        INVALID_KEY      = 0xB,
        FATAL_ERROR      = 0xC
    };
};