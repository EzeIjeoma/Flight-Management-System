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
    string getTicketID();
    Passenger getPassenger();
    string getFlightNumber();
    string getTicketType();
    string getSeatNumber();
    double getPrice();



};

