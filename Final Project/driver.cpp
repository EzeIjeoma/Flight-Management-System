#include "app.h"
#include "flightMgtSys.h"
#include "Flight.h"
#include <iostream>
#include "util.h"

using namespace std;


int main() {
    // Creating a flight instance
    Flight myFlight("FL123", "JetAir", "New York", "London", "2024-06-15 10:00", "2024-06-15 22:00", 30, 6, 5, 500.00, 200.00);

    // Creating passengers
    Passenger passenger1("Alice Johnson", "P123456", "USA");
    Passenger passenger2("Bob Smith", "P654321", "Canada");
    Passenger passenger3("Charlie Brown", "P111222", "UK");

    // Creating tickets for these passengers on the same flight
    Ticket ticket1("T1", passenger1, "FL123", "Economy", "12A", 299.99);
    Ticket ticket2("T2", passenger2, "FL123", "Economy", "12B", 299.99);
    Ticket ticket3("T3", passenger3, "FL123", "Economy Plus", "3C", 399.99);

    // Assuming each ticket is part of separate bookings
    Booking booking1("B1", "U1", "FL123", { ticket1 }, "2024-06-14", "Confirmed");
    Booking booking2("B2", "U2", "FL123", { ticket2 }, "2024-06-14", "Confirmed");
    Booking booking3("B3", "U3", "FL123", { ticket3 }, "2024-06-14", "Confirmed");

    // Simulate adding bookings to a vector (could represent a database of bookings for the flight)
    std::vector<Booking> bookings = { booking1, booking2, booking3 };

    // Update the flight manifest with the bookings
    myFlight.updateManifest("FL123", bookings);

    // Use the getManifest method to access the updated manifest and print it
    const auto& manifest = myFlight.getManifest();
    manifest.print();

    return 0;
}