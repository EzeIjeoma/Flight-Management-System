#pragma once

#include <string>
#include "passenger.h"

using namespace std;

class Ticket
{
private:
    string ticketID;
    Passenger passenger;
    string flightNumber;
    string ticketType;
    string seatNumber;
    double price;
public:
    Ticket(const string& ticketID, const Passenger& passenger, const string& flightNumber, const string& ticketType, const string& seatNumber, double price);
    string getTicketID();
    Passenger getPassenger();
    string getFlightNumber();
    string getTicketType();
    string getSeatNumber();
    double getPrice();
};

