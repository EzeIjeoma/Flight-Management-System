#include "Flight.h"
#include <sstream>

Flight::Flight(const string& flightNumber, const string& airlineName, const string& dateOfFlight, const string& origin,
    const string& destination, const string& departureTime, const string& arrivalTime,
    int totalRows, int seatsPerRow, int businessRows, double businessPrice, double regularPrice, double flightDuration)
    : flightNumber(flightNumber), airlineName(airlineName), dateOfFlight(dateOfFlight), origin(origin), destination(destination),
    departureTime(departureTime), arrivalTime(arrivalTime), businessPrice(businessPrice), regularPrice(regularPrice), flightDuration(flightDuration),
    manifest(totalRows* seatsPerRow, 6, "") 
{
    initializeSeats(totalRows, seatsPerRow, businessRows, businessPrice, regularPrice);
}

void Flight::initializeSeats(int totalRows, int seatsPerRow, int businessRows, double businessPrice, double regularPrice) {
    string seatLetters = "ABCDEF";
    for (int row = 1; row <= totalRows; ++row) {
        string seatClass = (row <= businessRows) ? "Business" : "Economy";
        for (int seat = 0; seat < seatsPerRow; ++seat) {
            stringstream ss;
            ss << row << seatLetters[seat];
            double price = (seatClass == "Business") ? businessPrice : regularPrice; // Use passed prices
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

string Flight::getDateOfFlight() const {
	return dateOfFlight;
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

double Flight::getFlightDuration() const {
	return flightDuration;
}

double Flight::getBusinessPrice() const {
	return businessPrice;
}

double Flight::getRegularPrice() const {
	return regularPrice;
}

const map<string, SeatInfo>* Flight::getSeats() const {
    return &seats;
}

const util::TwoDArrayADT<string>& Flight::getManifest() const {
    return manifest;
}

void Flight::updateManifest(const std::string& targetFlightNumber, const std::vector<Booking>& bookings) {
    if (flightNumber != targetFlightNumber) {
        return;
    }

    manifest.EmptyList();
    for (const auto& booking : bookings) {
        if (booking.getFlightNumber() == targetFlightNumber) {
            std::vector<Ticket> tickets = booking.getTickets();

            for (const auto& ticket : tickets) {
                Passenger passenger = ticket.getPassenger();
                std::vector<std::string> ticketDetails = {
                    passenger.get_passportNumber(),
                    passenger.get_name(),
                    passenger.get_passportIssueCountry(),
                    ticket.getSeatNumber(),
                    ticket.getTicketType()
                };

                manifest.putItem(ticketDetails);
            }
        }
    }
}

