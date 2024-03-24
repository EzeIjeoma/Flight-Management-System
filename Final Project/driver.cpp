#include "app.h"
#include "flightMgtSys.h"
#include "Flight.h"
#include <iostream>

using namespace std;

int main() {
    // Step 1: Register a user
    std::string userID = "user001";
    registerUser(userID, "John", "Doe", "johndoe@example.com", "password123", "customer");

    // Step 2: Add a flight
    addFlight("FL789", "Example Airline", "City X", "City Y", "10:00", "13:00", 30, 6, 5);

    // Step 3: Prepare passenger details
    std::map<std::string, Passenger> seatToPassengerMap;
    seatToPassengerMap["1A"] = Passenger("John Doe", "Passport123", "USA");
    seatToPassengerMap["1B"] = Passenger("Jane Doe", "Passport124", "USA");
    seatToPassengerMap["1C"] = Passenger("Jim Doe", "Passport125", "USA");

    // Step 4: Book the flight
    std::string flightNumber = "FL789";
    std::string ticketType = "Economy";
    std::string bookingDate = "2024-04-15";
    bool bookingResult = bookFlight(userID, flightNumber, ticketType, bookingDate, seatToPassengerMap);

    if (bookingResult) {
        std::cout << "Booking successful for flight " << flightNumber << std::endl;
    }
    else {
        std::cout << "Booking failed for flight " << flightNumber << std::endl;
    }

    displayFlightDetails(flightNumber);

    return 0;
}