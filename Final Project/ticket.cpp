#include "ticket.h"

Ticket::Ticket(const string& ticketID, const Passenger& passenger, const string& flightNumber,
    const string& ticketType, const string& seatNumber, double price)
    : ticketID(ticketID), passenger(passenger), flightNumber(flightNumber),
    ticketType(ticketType), seatNumber(seatNumber), price(price) {}

string Ticket::getTicketID() {
    return ticketID;
}

Passenger Ticket::getPassenger() {
    return passenger;
}

string Ticket::getFlightNumber() {
    return flightNumber;
}

string Ticket::getTicketType() {
    return ticketType;
}

string Ticket::getSeatNumber() {
    return seatNumber;
}

double Ticket::getPrice() {
    return price;
}