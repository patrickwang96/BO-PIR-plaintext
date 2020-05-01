//
// Created by Ruochen WANG on 1/5/2020.
//

#include <chrono>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <unistd.h>

//#define BOOST_ASIO_SEPARATE_COMPILATION

//#include "boost/asio/impl/src.hpp"
#include <boost/asio.hpp>
//#include "boost/asio/ssl/impl/src.hpp"

#include "pir.h"

using namespace std;

Record answer(RecordSet &db, vector<int> &queryset) {
    int n = db.size();
//    int j = sqrt(n);

    Record ans = 0;
    for (int i : queryset) {
        ans ^= db[i % n];
    }
    return ans;

}

#define CLOCK_START {start = std::chrono::steady_clock::now();}

#define CLOCK_END {end = std::chrono::steady_clock::now();}

#define ELAPSED std::chrono::duration<double, std::nano>(end - start).count()

void test_answer() {
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

}


int main() {

    using namespace boost::asio;
    typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
    io_service service;
    ip::tcp::endpoint ep(ip::tcp::v4(), 1234);
    ip::tcp::acceptor acc(service, ep);

    ip::tcp::socket sock(service);
    acc.accept(sock);


    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();

    RecordSet db = genDb(RECORD_COUNT);
    int j = sqrt(RECORD_COUNT) - 1;

    for (int k = K1; k < K2; k += STEP) {
        vector<int> querys(j * k);
        double time = 0;

        CLOCK_START
        for (int i = 0; i < NUM_TRAIL; i++) {
//            sock.read_some(buffer(querys));
            read(sock, buffer(querys), transfer_all());
            vector<uint8_t> ret(k);
            for (int n = 0; n < k; n++) {
                vector<int> cur(querys.begin() + n * j, querys.begin() + j * (n + 1));
                auto a = answer(db, cur);
                ret[i] = a.to_ulong();
            }
            sock.write_some(buffer(ret));
        }
        CLOCK_END
        time = ELAPSED;
        cout << "answer time is " << time / 1000000 / NUM_TRAIL << " ms" << endl;
    }


    sleep(10);

    return 0;
}