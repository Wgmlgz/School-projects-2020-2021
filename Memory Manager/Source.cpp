#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <list>
#include <functional>
#include <chrono>

const bool DEBUG = true;

using std::vector;
using std::multiset;
using std::less;
using std::pair;
using std::endl;
using std::cout;
using std::cin;
using time_p = std::chrono::time_point < std::chrono::steady_clock>;
int cells, requests;

struct Area {
    int size = 0;
    int pos = 0;
    bool free = true;
    int rec_n = -1;
    Area* prev = nullptr;
    Area* next = nullptr;
    ~Area() {
        if (prev) prev->next = next;
        if (next) next->prev = prev;
    }
};

// грязные трюки для дебага через яндекс контест
class Debugger {
public:
    int max_time;
    vector<uint64_t>* fuck_yandex_contest;
    // time_p start = std::chrono::high_resolution_clock::now();
    explicit Debugger(int max_time_) {
        max_time = max_time_;
    }
    void allocMem(int mb) {
        for (int i = 0; i < mb; ++i) {
            fuck_yandex_contest = new vector<uint64_t>(131073);
        }
    }
    void doError(int mb_er) {
        allocMem(mb_er);
        for (int ii = 0; ii < 100; ++ii) {
            --ii;
        }
    }
    void tick(int mb_er) {
        auto now = std::chrono::high_resolution_clock::now();
        // if ((now - start).count() > max_time) doError(mb_er);
    }
};

struct APtrComp {
    bool operator()(const Area* lhs, const Area* rhs) const {
        if (lhs->size == rhs->size)
            return lhs->pos > rhs->pos;
        else
            return lhs->size < rhs->size;
    }
};

class MemoryManager {
public:
    Debugger* db;
    struct AreaNP;
    Area* mem;
    multiset <Area*, APtrComp> free_mem;
    vector <Area*> req_mem;
    int cur_request = 0;

    MemoryManager(int cells, int requests, Debugger* db_) {
        db = db_;
        mem = new Area;
        free_mem.insert(mem);
        mem->size = cells;
        req_mem.resize(requests);
    }
    void solveRequest(int input);
    pair<Area*, Area*> give(Area* th,  int sz) {
        free_mem.erase(th);
        auto sec = new Area;
        th->free = false;

        sec->size = th->size - sz;
        sec->pos = sz + th->pos;
        th->size = sz;

        sec->next = th->next;
        th->next = sec;
        sec->prev = th;

        
        if (sec->size == 0) {
            th->next = nullptr;
            delete sec;
        } else {
            free_mem.insert(sec);
        }
        return { th, sec };
    }
    void mergeNext(Area* th) {
        free_mem.erase(th);
        free_mem.erase(th->next);

        th->size += th->next->size;

        delete th->next;
        free_mem.insert(th);
        mem = th;
    }
    void mergePrev(Area* th) {
        free_mem.erase(th);
        free_mem.erase(th->prev);
        th->pos = th->prev->pos;

        th->size += th->prev->size;

        delete th->prev;
        free_mem.insert(th);
        mem = th;
    }
    void freeMem(Area* th) {
        if (th->rec_n == 47) {
            cout << "";
        }
        free_mem.erase(th);
        th->free = true;
        free_mem.insert(th);
        if (th->next) if (th->next->free) mergeNext(th);
        if (th->prev) if (th->prev->free) mergePrev(th);
    }
    void print() {
        auto t = mem;
        while (t->prev != nullptr) t = t->prev;
        while (t) {
            cout << (t->free ? "f" : "u") << t->size << "(" << t->pos << "," << t->rec_n<< ") ";
            t = t->next;
        }
        cout << "|";
        for (auto const& i : free_mem) {
            std::cout << i->pos << ' ';
        }
        cout << endl;
    }
};

void MemoryManager::solveRequest(int input) {
    cout << "inp(" << cur_request << "): " << input << " ";
    if (input < 0) {
        try {
            if (req_mem[-input - 1]) freeMem(req_mem[-input - 1]);
        } catch (...) {
            db->doError(20);
        }
    } else {
        try {
            if (free_mem.empty()) {
                req_mem[cur_request] = nullptr;
                cout << -1 << endl;
            } else {
                auto place = *free_mem.rbegin();
                if (place->size >= input) {
                    cout << place->pos + 1 << endl;
                    auto t = give(place, input);
                    req_mem[cur_request] = t.first;
                    t.first->rec_n = cur_request;
                } else {
                    req_mem[cur_request] = nullptr;
                    cout << -1 << endl;
                }
            }
        } catch (...) {
            db->doError(40);
        }
    }
    ++cur_request;
    if (DEBUG) cout << endl;
    if (DEBUG) printf(" ");
    if (DEBUG) print();
}

void genInput() {
    cout << "--new--" << endl;
    auto db = Debugger(300);
    MemoryManager MM(84, 168, &db);
    vector<int> rec;
    vector<int> input;
    for (int i = 0; i < 168; ++i) {
        int r_type = rand() % 2;
        if (rec.size() == 0) r_type = 1;
        if (r_type == 1) {
            int sz = rand() % 90;
            rec.push_back(i + 1);
            input.push_back(sz);
            MM.solveRequest(sz);
        }
        else {
            int nm = rand() % rec.size();
            
            input.push_back(-nm);
            MM.solveRequest(-(rec[nm]));
            rec.erase(rec.begin() + nm);
        }
    }
    cout << "--end--" << endl;
}

int main() {
    while (1) {
        genInput();
    }
    /*auto db = Debugger(300);
    cin >> cells >> requests;
    MemoryManager MM(cells, requests, &db);
    try {
        for (int i_ = 0; i_ < requests; ++i_) {
            int tmp_;
            cin >> tmp_;
            MM.solveRequest(tmp_);
        }
    } catch (...) {
        db.doError(10);
    }*/
}
