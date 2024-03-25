#include "ticket.h"

Ticket::Ticket(const string& ticketID, const Passenger& passenger, const string& flightNumber,
    const string& ticketType, const string& seatNumber, double price)
    : ticketID(ticketID), passenger(passenger), flightNumber(flightNumber),
    ticketType(ticketType), seatNumber(seatNumber), price(price) {}

string Ticket::getTicketID() const {
    return ticketID;
}

Passenger Ticket::getPassenger() const {
    return passenger;
}

string Ticket::getFlightNumber() const {
    return flightNumber;
}

string Ticket::getTicketType() const {
    return ticketType;
}

string Ticket::getSeatNumber() const {
    return seatNumber;
}

double Ticket::getPrice() const {
    return price;
}