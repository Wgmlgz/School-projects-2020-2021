#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <list>
#include <functional>

using std::vector;
using std::multiset;
using std::less;
using std::pair;
using std::endl;
using std::cout;
using std::cin;
int cells, requests;

class MemoryManager {
public:
    struct Area;
    struct AreaNP;
    Area* mem;
    multiset <AreaNP, std::less<>> free_mem;
    vector <Area*> req_mem;
    int cur_request = 0;

    MemoryManager(int cells, int requests);
    void solveRequest(int input);
};
struct MemoryManager::AreaNP {
    MemoryManager::Area* ar;
    AreaNP(MemoryManager::Area* ar_) {
        ar = ar_;
    }
    friend bool operator<(AreaNP const& a, AreaNP const& b) {
        cout << "dsfsdafs";
        if (a.ar->size == b.ar->size) {
            return a.ar->pos < b.ar->pos;
        }
        else {
            return a.ar->size < b.ar->size;
        }
    }
};
struct MemoryManager::Area {
        int size = 0;
        int pos = 0;
        bool free = true;
        Area* prev = nullptr;
        Area* next = nullptr;
        // long double id = 0;
        multiset<AreaNP, less<>>* ms;
        Area(multiset<AreaNP, less<>>* ms_) {
            ms = ms_;
        }
        pair<Area*, Area*> give(int sz) {
            auto sec = new Area(ms);
            // if (next) sec->id = (next->id - id) / 2 + id;
            // else sec->id = id + 1;
            free = false;

            sec->size = size - sz;
            sec->pos = sz + pos;
            size = sz;

            sec->next = next;
            next = sec;
            sec->prev = this;

            ms->erase(AreaNP(this));
            ms->insert(sec);
            return { this, sec };
        }
        void mergeNext() {
            ms->erase(this);
            ms->erase(next);
            // id = (next->id - id) / 2 + id;

            size += next->size;

            if (next->next) next->next->prev = this;
            next = next->next;


            ms->insert(this);
            delete next;
        }
        void mergePrev() {
            ms->erase(this);
            ms->erase(prev);
            pos = prev->pos;

            // id = (prev->id - id) / 2 + id;

            size += prev->size;

            if (prev->prev) prev->prev->next = this;
            next = prev->prev;

            
            ms->insert(this);
            delete prev;
        }
        void freeMem() {
            free = true;
            if (next) if (next->free) mergeNext();
            if (prev) if (prev->free) mergePrev();
            ms->insert(this);
        }
        void print() {
            auto t = this;
            while (t->prev != nullptr) t = t->prev;
            while (t) {
                cout << (t->free ? "f" : "u") << t->size << "(" << t->pos << ") ";
                t = t->next;
            }
            cout << "|";
            for (auto const& i : *ms) {
                std::cout << i->pos << ' ';
            }
            cout << endl;
        }
};

MemoryManager::MemoryManager(int cells, int requests) {
    mem = new Area(&free_mem);
    free_mem.insert(mem);
    mem->size = cells;
    req_mem.resize(requests);
}

void MemoryManager::solveRequest(int input) {
    if (input < 0) {
        if (req_mem[-input - 1]) req_mem[-input - 1]->freeMem();
    } else {
        auto place = *free_mem.rbegin();
        if (place->size >= input) {
            cout << place->pos + 1 << endl;
            auto t = place->give(input);
            req_mem[cur_request] = t.first;
        } else {
            req_mem[cur_request] = nullptr;
            cout << -1 << endl;
        }
    }
    ++cur_request;
    cout << endl;
    printf(" ");
    mem->print();
}


int main() {
    cin >> cells >> requests;
    MemoryManager MM(cells, requests);
    for (int i_ = 0; i_ < requests; ++i_) {
        int tmp_;
        cin >> tmp_;
        MM.solveRequest(tmp_);
    }
}
