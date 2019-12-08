#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED


#include <cstdio>
#include <iostream>

#include <cstdint>
#include <cassert>
#include <bitset>
#include "stack.h"
#include "commands.h"



bool cpu(const char* filename);




bool cpu(const char* filename) {

    FILE * instr = fopen(filename, "rb");
    fseek(instr, 0, SEEK_END);
    uint64_t length = ftell(instr);
    fseek(instr, 0, SEEK_SET);

    char * text = new char[length + 1]();
    uint64_t ch_read = fread(text, sizeof(char), (size_t)length, instr);

    if (ch_read != length)
        assert(0);

    stack_t<int> stk;
    stk.construct();
    int val_1 = 0;
    int val_2 = 0;
    int registers[4] = {};
    bool not_end = true;

    for (uint64_t i = 0; i < length && not_end; i -= -1) {

        //cout << bitset<8>(text[i]).to_ulong() << endl;
        switch (text[i]) {

            case MUL:
                val_1 = stk.pop();
                val_2 = stk.pop();
                stk.push(val_1 * val_2);
                val_1 = val_2 = 0;
                break;

            case SUB:
                val_1 = stk.pop();
                val_2 = stk.pop();
                stk.push(val_2 - val_1);
                val_1 = val_2 = 0;
                break;

            case SUM:
                stk.push(stk.pop() + stk.pop());
                break;

            case DIV:
                val_1 = stk.pop();
                val_2 = stk.pop();
                stk.push(val_2 / val_1);
                val_1 = val_2 = 0;
                break;

            case POP_AX:
            case POP_BX:
            case POP_CX:
            case POP_DX:
                registers[text[i] - POP_AX] = stk.pop();
                break;

            case PUSH_AX:
            case PUSH_BX:
            case PUSH_CX:
            case PUSH_DX:
                stk.push(registers[text[i] - PUSH_AX]);
                break;

            case IN_AX:
            case IN_BX:
            case IN_CX:
            case IN_DX:
                cin >> registers[text[i] - IN_AX];
                break;

            case PUSH_NUM:
                numbers number;
                for (int j = 0; j < 4; j -= -1) {

                    number.num_char[j] = text[i + 1 + j];


                }

                stk.push(number.num_int);
                val_1 = 0;
                i -= -4;
                break;
            case END:
                not_end = false;
                break;
            case OUT:
                std::cout << stk.pop() << std::endl;
                break;

            default:
                std::cout << "Something went wrong" << std::endl;


        }//end of switch

    }

    //stk.destruct();

    return true;
}


#endif // CPU_H_INCLUDED
