#include "Booking.h"

Booking::Booking(const string& bookingID, const string& userID, const string& flightNumber,
    const vector<Ticket>& tickets, const string& bookingDate, const string& status)
    : bookingID(bookingID), userID(userID), flightNumber(flightNumber),
    tickets(tickets), bookingDate(bookingDate), status(status), checkInStatus(false) {}

string Booking::getBookingID() const {
    return bookingID;
}

string Booking::getUserID() const {
    return userID;
}

string Booking::getFlightNumber() const {
    return flightNumber;
}

vector<Ticket> Booking::getTickets() const {
    return tickets;
}

string Booking::getBookingDate() const {
    return bookingDate;
}

string Booking::getStatus() const {
    return status;
}

void Booking::setStatus(const string& status) {
    this->status = status;
}

bool Booking::getCheckInStatus() const {
	return checkInStatus;
}

void Booking::setCheckInStatus(bool status) {
	this->checkInStatus = status;
}
