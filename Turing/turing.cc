#include "turing.h"
#include <stdio.h>
#include <string.h>
#include "brainfuck.h"
#pragma warning(disable:4996)
extern "C" {
    TuringMachine* init(){
        TuringMachine* a_to_b = new TuringMachine("aaaa", {
            {"a", {{"b", rt}}},
            {"~", {RT}}
        });
        return a_to_b;
    }
    TuringMachine* initBrainfuck() {
        auto bf_tm = brainfuckTM();
        TuringMachine* p = new TuringMachine(bf_tm);
        return p;
    }
    void run(TuringMachine* tm, char* buf) {
        std::string st = tm->getRes(666);

        strcpy(buf, st.c_str());
    }
    void safeIterate(TuringMachine* tm) {
        tm->safeIterate();
    }
    void getStr(TuringMachine* tm, char* buf) {
        try {
            std::string st = tm->toStrUnity();
            strcpy(buf, st.c_str());
        } catch (const std::exception&) {
                
        }
    }
}
