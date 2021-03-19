#pragma once
#include "stdafx.h"
#include "list.h"

int powInt(int x, int n) {
    int y = 1;
    for (int i = 0; i < n; i++) y *= x;
    return y;
}

class Polinom {
public:
    class Monom {
    public:
        int mult_val;

        struct VarT {
            char name; int power; 
            static function<bool(VarT, VarT)> isLessVar;
        };
        
        SortedList<VarT> vars{ VarT::isLessVar };
        static function<bool(Monom, Monom)> isLessMonom;
        

        static function<bool(char, VarT)> eqName;

        int valAtPoint(List<pair<char, int>> vals) {
            int control_sum = 0;
            int mult = 1;
            for (auto i = vals.begin; i != nullptr; i = i->next) {
                auto find_res = vars.find<char>(i->data.first, eqName);
                if (find_res) {
                    mult *= powInt(i->data.second, find_res->data.power);
                    ++control_sum;
                }
            }
            if (control_sum > vars.size)
                throw std::exception("Too many variables found (maybe some copies)");
            if (control_sum < vars.size)
                throw std::exception("Not all variables were initialized");
            return mult_val * mult;
        }
    };
    SortedList<Monom> data{ Monom::isLessMonom };

    void insetrMonom(Monom monom) {
        for (auto i = data.begin; i != nullptr; i = i->next) {
            auto i_d = i->data;
            //if ()
        }
    }
    void fromStr(string str) {
        enum class Input {
            mult, var, pow, var_or_mult
        };

        bool wait = true;
        Input input = Input::mult;

        string buff;
        Monom tmp_monom;
        for (auto i = str.begin(); i != str.end(); ++i) {
            auto isNum = [&]() -> bool { return (*i >= '0' && *i <= '9'); };
            auto isVar = [&]() -> bool { return (*i >= 'a' && *i <= 'z'); };
            auto isSpace = [&]() -> bool { return (*i == ' '); };
            if (input == Input::mult) {
                /*if (*i == ' ') {
                    continue;
                } else if (isNum()) {
                    state = States::num;
                } else if (isVar()) {
                    state = States::var;
                }*/
            } else if (state == Input::var) {
                if (isVar()) {
                    buff += *i;
                } else if (isVar()) {
                    if (input == Input::mult) {
                        tmp_monom.mult_val = std::stoi(buff);
                        buff.clear();
                    } else if (input == Input::pow) {
                        tmp_monom.vars.end->data.power = std::stoi(buff);
                        buff.clear();
                    }
                } else if (isSpace()) {
                    
                }
            } else {
                throw (std::exception("Unknown error"));
            }
        }
    }
    string toStr() {
        if (data.size == 0) return "0";
        string ret;
        for (auto i = data.begin; i != nullptr; i = i->next) {
            auto i_d = i->data;
            string monom_str;

            monom_str += std::to_string(i_d.mult_val);
            for (auto i = i_d.vars.begin; i != nullptr; i = i->next) {
                //if (!(i == i_d.vars.begin && i_d.mult_val == 1)) monom_str += "*";
                if (i->data.power != 0) {
                    monom_str += i->data.name;
                    if (i->data.power != 1) {
                        monom_str += "^";
                        monom_str += std::to_string(i->data.power);
                    }
                }
            }
            ret += monom_str;

            if (i != data.end) ret += " + ";
        }
        
        return ret;
    }
    //Polinom(List<Monom> data_) {
    //    data = data_;
    //}
    //Polinom(string str) {

    //}
    Polinom() {

    }

    // methods
    int valAtPoint(List<pair<char, int>> vals) {
        int sum = 0;
        for (auto i = data.begin; i != nullptr; i = i->next) sum += i->data.valAtPoint(vals);
        return sum;
    }
    Polinom derivative(char var, int n = 1) {
        if (n == 0) return *this;
        if (n < 0) throw std::exception("Bruh, bro that's cringe(((((");
        Polinom der;

        for (auto i = data.begin; i != nullptr; i = i->next) {
            auto i_d = i->data;
            auto vars_copy = i_d.vars.copy();
            auto find_res = vars_copy.find<char>(var, Polinom::Monom::eqName);
            if (find_res) {
                auto mult_val = i_d.mult_val * find_res->data.power;
                if (find_res->data.power == 1) vars_copy.remove(find_res);
                else --find_res->data.power;
                der.data.insert({mult_val, vars_copy});
            }
        }
        if (n == 1) {
            return der;
        } else {
            return der.derivative(var, n - 1);
        }
    }
    Polinom operator+(const Polinom& sec) {
        for (auto i = sec.data.begin; i != nullptr; i = i->next) {
            auto find_res = data.find<Monom>(i->data, [](Monom a, Monom b) -> bool {
                if (a.vars.size != b.vars.size) return false;
                for (auto i = a.vars.begin, j = b.vars.begin; i != nullptr; i = i->next, j = j->next)
                    if (i->data.name != j->data.name || i->data.power != i->data.power) return false;
                return true;
            });
            if (find_res) find_res->data.mult_val += i->data.mult_val;
            else data.insert(i->data);
        }
        return *this;
    }
};

function<bool(Polinom::Monom::VarT, Polinom::Monom::VarT)>  Polinom::Monom::VarT::isLessVar = [](Polinom::Monom::VarT a, Polinom::Monom::VarT b) -> bool {
    return a.name - 'a' < b.name - 'a';
};

function<bool(Polinom::Monom, Polinom::Monom)> Polinom::Monom::isLessMonom = [](Monom a, Monom b) -> bool {
    auto i = a.vars.begin, j = b.vars.begin;
    for (; i != nullptr && j != nullptr; i = i->next, j = j->next) {
        if (i->data.name != j->data.name) {
            if (i->data.power != i->data.power) return !(i->data.power < i->data.power);
            else return !(i->data.name < j->data.name);
        }
    }
    return !(i == nullptr);
};

function<bool(char, Polinom::Monom::VarT)> Polinom::Monom::eqName = [](char a, VarT b) -> bool { return a == b.name; };


