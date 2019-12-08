
#include "assembler.h"
#include "cpu.h"
#include <cstdint>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctime>
#include <iostream>

uint64_t time_change(const char* file);

int main() {

    uint64_t origin_time    = time_change("program_1.txt");
    uint64_t compiled_time  = time_change("output_1.bin");

    //std::cout << origin_time << " " << compiled_time << std::endl;

    if (origin_time >= compiled_time) {

        assemble("program_1.txt", "output_1.bin");
        std::cout << "assemble made" << std::endl;

    }
    cpu("output_1.bin");


    return 0;

}

uint64_t time_change(const char* file) {

    struct _stat st ;
    _stat(file, &st);

    return st.st_mtime;  //time of change


}
