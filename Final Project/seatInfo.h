#pragma once

#include <string>
using namespace std;


class SeatInfo {
public:
    bool isBooked;
    string seatClass;
    double price;

    SeatInfo(bool isBooked, const string& seatClass, double price) : isBooked(isBooked), seatClass(seatClass), price(price) {}
};

