#pragma once

#include <string>
#include <vector>
#include "ticket.h"

using namespace std;

class Booking
{
private:
    string bookingID;
    string userID;
    string flightID; 
    vector<Ticket> tickets;
    string bookingDate;
    string status;

public:
    Booking(const string& bookingID, const string& userID, const string& flightID, const vector<Ticket>& ticket, const string& bookingDate, const string& status);
    string getBookingID() const;
    string getUserID() const;
    string getFlightID() const;
    vector<Passenger> getPassengers() const;
    string getBookingDate() const;
    string getStatus() const;
    void setStatus(const string& status);
};

