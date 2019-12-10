#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

union numbers {

    int num_int;
    char num_char[4];

};

enum commands {

    PUSH        = 1,
    POP         ,
    IN          ,
    SUM         ,
    SUB         ,
    MUL         ,
    DIV         ,
    OUT         ,
    END         ,
    PUSH_NUM    ,
    PUSH_AX     ,
    PUSH_BX     ,
    PUSH_CX     ,
    PUSH_DX     ,
    POP_AX      ,
    POP_BX      ,
    POP_CX      ,
    POP_DX      ,
    IN_AX       ,
    IN_BX       ,
    IN_CX       ,
    IN_DX       ,


};


#endif // COMMANDS_H_INCLUDED
