#include "turing.h"
#include <stdio.h>
#include <string.h>

extern "C" {
    TuringMachine* init(){
        TuringMachine* a_to_b = new TuringMachine("aaaa", {
            {"a", {{"b", rt}}},
            {"~", {ST}}
        });
        return a_to_b;
    }
    void run(TuringMachine* tm, char* buf) {
        std::string st = tm->getRes(666);

        strcpy(buf, st.c_str());
    }
}
