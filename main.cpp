#include <iostream>
#include <chrono>
#include "pir.h"

using namespace std;

#define CLOCK_START {start = std::chrono::steady_clock::now();}

#define CLOCK_END {end = std::chrono::steady_clock::now();}

#define ELAPSED std::chrono::duration<double, std::nano>(end - start).count()

int main() {
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();

    RecordSet db = genDb(RECORD_COUNT);

//    vector<unordered_map<int, int>> maps;
    vector<vector<int>> S;
    vector<RecordSet> hintsets;
    vector<vector<int>> querys;
    vector<int> u(K);
    for (int i = 0; i < K; i++) u[i] = i;

    double time = 0;

    CLOCK_START
    hintsets = genLHintSets(db, L, S);
    CLOCK_END
    time = ELAPSED;
    cout << "preprocessing time is " << time / 1000000 << "ms" << endl;

    time = 0;
    CLOCK_START
    querys = queryLSets(L, u, S);
    CLOCK_END
    time = ELAPSED;
    cout << "query time is " << time / 1000000 << "ms" << endl;

    return 0;
}
