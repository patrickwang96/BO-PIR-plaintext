//
// Created by Ruochen WANG on 1/5/2020.
//

#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;


int main() {
    using namespace boost::asio;

    io_service service;
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 1234);
    ip::tcp::socket sock(service);

    sock.connect(ep);

    string input;

    cin >> input ;
    sock.write_some(buffer(input.c_str(), input.size()));
    return 0;


}

