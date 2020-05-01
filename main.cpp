#include <iostream>
#include <chrono>
#include <boost/asio.hpp>
#include "pir.h"

using namespace std;

#define CLOCK_START {start = std::chrono::steady_clock::now();}

#define CLOCK_END {end = std::chrono::steady_clock::now();}

#define ELAPSED std::chrono::duration<double, std::nano>(end - start).count()

int main() {
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();

    RecordSet db = genDb(RECORD_COUNT);
    int n = db.size();
    int sqrtn = sqrt(n);

//    vector<unordered_map<int, int>> maps;
    vector<vector<int>> S(L);
    vector<RecordSet> hintsets;
    vector<vector<int>> querys;
    vector<int> u(K);
    for (int i = 0; i < K; i++) u[i] = i;



    // setup network

    using namespace boost::asio;
    io_service service;
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 1234);
    ip::tcp::socket sock(service);
    sock.connect(ep);

    vector<int> total(K * (sqrtn - 1));
    for (int t = 0; t < NUM_TRAIL; t++) {
        hintsets = genLHintSets(db, L, S);
        querys = queryLSets(L, u, S);
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < (sqrtn-1); j++) {
                total[i * (sqrtn-1) + j] = querys[i][j];
            }
        }
        sock.write_some(buffer(total));

        vector<uint8_t> answer(K);
        sock.read_some(buffer(answer));
        for (auto a: answer) {
            decode(db[a]);
        }
    }

    return 0;
}
