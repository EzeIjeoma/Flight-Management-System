#pragma once

#include <string>
using namespace std;

class SeatInfo {
public:
    bool isBooked;
    string seatClass;
    double price;

    SeatInfo();
    SeatInfo(bool isBooked, const string& seatClass, double price);
    bool getIsBooked() const;
    string getSeatClass() const;
    double getPrice() const;
    void setIsBooked(bool isBooked);
    void setSeatClass(const string& seatClass);
    void setPrice(double price);
};
