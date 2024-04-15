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
    string flightNumber; 
    vector<Ticket> tickets;
    string bookingDate;
    string status;
    bool checkInStatus;

public:
    Booking(const string& bookingID, const string& userID, const string& flightNumber, const vector<Ticket>& ticket, const string& bookingDate, const string& status);
    string getBookingID() const;
    string getUserID() const;
    string getFlightNumber() const;
    string getBookingDate() const;
    string getStatus() const;
    void setStatus(const string& status);
    vector<Ticket> getTickets() const;
    bool getCheckInStatus() const;
    void setCheckInStatus(bool status);
    void addTicket(const Ticket& ticket);
};

