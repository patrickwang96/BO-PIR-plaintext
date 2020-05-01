//
// Created by Ruochen WANG on 1/5/2020.
//

#include <chrono>
#include <iostream>
#include <cmath>
#include <cstdlib>
//#include "boost/asio/impl/src.hpp"
//#include "boost/asio/ssl/impl/src.hpp"

#include "pir.h"

using namespace std;

void answer(RecordSet &db, vector<int> &queryset) {
    int n = db.size();
//    int j = sqrt(n);

    Record ans = 0;
    for (int i : queryset) {
        ans ^= db[i % n];
    }

}

#define CLOCK_START {start = std::chrono::steady_clock::now();}

#define CLOCK_END {end = std::chrono::steady_clock::now();}

#define ELAPSED std::chrono::duration<double, std::nano>(end - start).count()

int main() {

    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();

    RecordSet db = genDb(RECORD_COUNT);
    int j = sqrt(RECORD_COUNT) - 1;
    vector<int> querys(j);
    for (int i = 0; i < j; i++) querys[i] = rand() % RECORD_COUNT;


    double time = 0;

    CLOCK_START
    for (int i = 0; i < K; i++)
        answer(db, querys);
    CLOCK_END
    time = ELAPSED;
    cout << "answer time is " << time / 1000000 << "ms" << endl;


    return 0;
}