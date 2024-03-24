#include "seatInfo.h"

SeatInfo::SeatInfo() : isBooked(false), seatClass("Economy"), price(0.0) {}

SeatInfo::SeatInfo(bool isBooked, const string& seatClass, double price)
    : isBooked(isBooked), seatClass(seatClass), price(price) {}

bool SeatInfo::getIsBooked() const {
    return isBooked;
}

string SeatInfo::getSeatClass() const {
    return seatClass;
}

double SeatInfo::getPrice() const {
    return price;
}

void SeatInfo::setIsBooked(bool newIsBooked) {
    isBooked = newIsBooked;
}

void SeatInfo::setSeatClass(const string& newSeatClass) {
    seatClass = newSeatClass;
}

void SeatInfo::setPrice(double newPrice) {
    price = newPrice;
}
