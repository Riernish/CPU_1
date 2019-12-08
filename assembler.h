#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include <cstdio>
#include "commands.h"
#include "my_strtok.h"
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>


bool rewrite(const char*, char*);
bool str_eq(char *, const char*);
bool is_int(char*);
bool assemble(const char * input_file, const char * output_file);


bool assemble(const char * input_file, const char * output_file) {

    FILE * input = fopen(input_file, "rt");

    fseek(input, 0, SEEK_END);
    uint64_t length = ftell(input);
    fseek(input, 0, SEEK_SET);

    char * text = new char[length + 1]();

    uint32_t ch_read = fread(text, sizeof(char), (size_t)length, input);
    assert(ch_read);


    text[length] = '\0';

    rewrite(output_file, text);



    fclose(input);

    return true;
}

bool rewrite(const char* filename, char* text) {

    FILE* output = fopen(filename, "wb");

    char separators[] = " ,;\t\n";
    char* word = my_strtok(text, separators);
    int cmd_1 = 0;
    int cmd_2 = 0;
    numbers number;
    do {

        if (str_eq(word, "push")) {

            cmd_1 = PUSH;

        }
        if (str_eq(word, "pop")) {

            cmd_1 = POP;

        }
        if (str_eq(word, "sum")) {

            cmd_1 = SUM;

        }
        if (str_eq(word, "sub")) {

            cmd_1 = SUB;

        }
        if (str_eq(word, "mul")) {

            cmd_1 = MUL;

        }
        if (str_eq(word, "div")) {

            cmd_1 = DIV;

        }
        if (str_eq(word, "in")) {

            cmd_1 = IN;

        }
        if (str_eq(word, "out")) {

            cmd_1 = OUT;

        }
        if (str_eq(word, "end")) {

            cmd_1 = END;

        }
        switch (cmd_1) {

            case SUM:
            case SUB:
            case DIV:
            case MUL:
            case OUT:
            case END:
                cmd_2 = 0;
                break;

            case PUSH:
            case  POP:
            case   IN:  {

                word = my_strtok(NULL, separators);
                if (str_eq(word, "ax")) {

                    switch(cmd_1) {

                        case PUSH:
                            cmd_1 = PUSH_AX;
                            break;
                        case POP:
                            cmd_1 = POP_AX;
                            break;
                        case IN:
                            cmd_1 = IN_AX;
                            break;
                        default:
                            std::cout<<"Something went wrong"<<std::endl;

                    }

                }
                if (str_eq(word, "bx")) {

                    switch(cmd_1) {

                        case PUSH:
                            cmd_1 = PUSH_BX;
                            break;
                        case POP:
                            cmd_1 = POP_BX;
                            break;
                        case IN:
                            cmd_1 = IN_BX;
                            break;
                        default:
                            std::cout<<"Something went wrong"<<std::endl;

                    }

                }
                if (str_eq(word, "cx")) {

                    switch(cmd_1) {

                        case PUSH:
                            cmd_1 = PUSH_CX;
                            break;
                        case POP:
                            cmd_1 = POP_CX;
                            break;
                        case IN:
                            cmd_1 = IN_CX;
                            break;
                        default:
                            std::cout<<"Something went wrong"<<std::endl;

                    }

                }
                if (str_eq(word, "dx")) {

                    switch(cmd_1) {

                        case PUSH:
                            cmd_1 = PUSH_DX;
                            break;
                        case POP:
                            cmd_1 = POP_DX;
                            break;
                        case IN:
                            cmd_1 = IN_DX;
                            break;
                        default:
                            std::cout<<"Something went wrong"<<std::endl;

                    }

                }
                //std::cout << word << std::endl;
                if (is_int(word)) {

                    number.num_int = atoi(word);
                    cmd_1 = PUSH_NUM;
                    cmd_2 = 1;

                }

                break;

            }//end of PUSH, POP, IN cases
            default:
                assert(0);


        }//end of switch


        fwrite(&cmd_1, sizeof(char), 1, output);
        if (cmd_2) {

            fwrite(number.num_char, sizeof(char), 4, output);


        }

        cmd_1 = 0;
        cmd_2 = 0;

    } while ((word = my_strtok(NULL, separators)) != NULL);




    fclose(output);

    return true;
}
bool str_eq(char* str_1, const char* str_2) {

    if (str_1[0] == '\0')
        return (str_2[0] == '\0') ? true : false;

    int i = 0;
    for (i = 0; str_1[i] != '\0'; i -= -1) {

        if (str_1[i] != str_2[i])
            return false;

    }

    return (str_1[i] == str_2[i] && str_1[i] == '\0') ? true : false;

}

bool is_int(char* str) {

    int i = 0;
    for (i = 0; str[i] != '\0'; i -= -1) {

        if (str[i] < '0' || str[i] > '9')
            return false;

    }
    return (i == 0) ? false : true;

}


#endif // ASSEMBLER_H_INCLUDED
