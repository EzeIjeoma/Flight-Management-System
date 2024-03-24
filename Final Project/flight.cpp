#include "Flight.h"
#include <sstream>

Flight::Flight(const string& flightNumber, const string& airlineName, const string& origin,
    const string& destination, const string& departureTime, const string& arrivalTime,
    int totalRows, int seatsPerRow, int businessRows) : flightNumber(flightNumber), airlineName(airlineName), origin(origin),
    destination(destination), departureTime(departureTime), arrivalTime(arrivalTime) {
    initializeSeats(totalRows, seatsPerRow, businessRows);
}

void Flight::initializeSeats(int totalRows, int seatsPerRow, int businessRows) {
    string seatLetters = "ABCDEF"; 
    for (int row = 1; row <= totalRows; ++row) {
        string seatClass = (row <= businessRows) ? "Business" : "Economy";
        for (int seat = 0; seat < seatsPerRow; ++seat) {
            stringstream ss;
            ss << row << seatLetters[seat];
            double price = (seatClass == "Business") ? 200.0 : 100.0; 
            seats[ss.str()] = SeatInfo(false, seatClass, price);
        }
    }
}

string Flight::getFlightNumber() const {
    return flightNumber;
}

string Flight::getAirlineName() const {
    return airlineName;
}

string Flight::getOrigin() const {
    return origin;
}

string Flight::getDestination() const {
    return destination;
}

string Flight::getDepartureTime() const {
    return departureTime;
}

string Flight::getArrivalTime() const {
    return arrivalTime;
}

bool Flight::bookSeat(const string& seatNumber) {
    auto it = seats.find(seatNumber);
    if (it != seats.end()) { 
        if (!it->second.isBooked) { 
            it->second.isBooked = true; 
            return true; 
        }
    }
    return false; 
}

string Flight::getSeatClass(const string& seatNumber) const {
	auto it = seats.find(seatNumber);
    if (it != seats.end()) {
		return it->second.seatClass;
	}
	return "";
}

double Flight::getSeatPrice(const string& seatNumber) const {
	auto it = seats.find(seatNumber);
    if (it != seats.end()) {
		return it->second.price;
	}
	return 0.0;
}

const map<string, SeatInfo>* Flight::getSeats() const {
    return &seats;
}