#include "app.h"
#include "flightMgtSys.h"
#include "Flight.h"
#include <iostream>
#include "util.h"

using namespace std;

// Function to print flight details for testing
void printFlights(const vector<Flight>& flights) {
    for (const auto& flight : flights) {
        std::cout << "Flight: " << flight.getFlightNumber()
            << ", Business Price: " << flight.getBusinessPrice()
            << ", Regular Price: " << flight.getRegularPrice()
            << ", Duration: " << flight.getFlightDuration() << " hours"
            << std::endl;
    }
    std::cout << "-----------------------------" << std::endl;
}

int main() {

    util::BinarySearchTree<User, std::string> usersBST;

    // Create some users
    User user1("001", "John", "Doe", "john.doe@example.com", "password123", "customer");
    User user2("002", "Jane", "Doe", "jane.doe@example.com", "password456", "customer");
    User user3("003", "Jim", "Beam", "jim.beam@example.com", "password789", "admin");

    // Add users to the BST using their email as the key
    usersBST.addItem(user1, user1.get_email());
    usersBST.addItem(user2, user2.get_email());
    usersBST.addItem(user3, user3.get_email());

    // Search for a user by email
    try {
        User foundUser = usersBST.searchByKey("jane.doe@example.com");
        cout << "User found: " << foundUser.get_first_name() << " " << foundUser.get_last_name() << endl;
    }
    catch (const std::runtime_error& e) {
        cout << e.what() << endl;
    }

    // Display all users in the BST
    cout << "All users in the BST:" << endl;
    vector<User> allUsers = usersBST.traverse();
    for (const auto& user : allUsers) {
        cout << user.get_first_name() << " " << user.get_last_name() << " - " << user.get_email() << endl;
    }

    return 0;











    //// Add some flights for testing purposes
    //addFlight("FL123", "Airline A", "2024-5-01", "City X", "City Y", "08:00", "11:00", 20, 6, 2, 1200.0, 800.0, 3.0);
    //addFlight("FL456", "Airline B", "2024-5-01", "City Z", "City K", "09:00", "12:00", 20, 6, 2, 1100.0, 700.0, 3.5);
    //addFlight("FL789", "Airline C", "2023-3-01", "City L", "City M", "10:00", "13:30", 20, 6, 2, 1300.0, 900.0, 3.5);
    //addFlight("FL012", "Airline D", "2024-8-01", "City N", "City O", "07:00", "10:00", 20, 6, 2, 1000.0, 750.0, 3.0);

    //// Test sorting by business price in ascending order
    //std::cout << "Sorted by business price (ascending):" << std::endl;
    //vector<Flight> sortedByBusinessPrice = sortFlightsByCriteria("businessPrice");
    //for (const auto& flight : sortedByBusinessPrice) {
    //    std::cout << "Flight: " << flight.getFlightNumber() << ", Business Price: " << flight.getBusinessPrice() << std::endl;
    //}
    //std::cout << std::endl;

    //// Test sorting by regular price in descending order
    //std::cout << "Sorted by regular price (descending):" << std::endl;
    //vector<Flight> sortedByRegularPrice = sortFlightsByCriteria("regularPrice", false);
    //for (const auto& flight : sortedByRegularPrice) {
    //    std::cout << "Flight: " << flight.getFlightNumber() << ", Regular Price: " << flight.getRegularPrice() << std::endl;
    //}
    //std::cout << std::endl;

    //// Test sorting by flight duration in ascending order
    //std::cout << "Sorted by flight duration (ascending):" << std::endl;
    //vector<Flight> sortedByDuration = sortFlightsByCriteria("flightDuration");
    //for (const auto& flight : sortedByDuration) {
    //    std::cout << "Flight: " << flight.getFlightNumber() << ", Duration: " << flight.getFlightDuration() << " hours" << std::endl;
    //}
    //std::cout << std::endl;

    //// Test sorting by airline name in ascending order
    //std::cout << "Sorted by airline name (ascending):" << std::endl;
    //vector<Flight> sortedByAirlineName = sortFlightsByCriteria("airlineName");
    //for (const auto& flight : sortedByAirlineName) {
    //    std::cout << "Flight: " << flight.getFlightNumber() << ", Airline: " << flight.getAirlineName() << std::endl;
    //}

    //// Test search by origin and destination
    //std::cout << "Search by origin and destination (City X to City Y):" << std::endl;
    //vector<Flight> searchResults = searchFlightsByOriginAndDestination("City X", "City Y");
    //printFlights(searchResults);

    //// Test sort by date of flight
    //std::cout << "Sorted by date of flight (ascending):" << std::endl;
    //vector<Flight> sortedByDate = sortFlightsByCriteria("dateOfFlight");
    //printFlights(sortedByDate);

    //// Test search by date
    //std::cout << "Search by date (2024-5-01):" << std::endl;
    //vector<Flight> searchResultsByDate = searchFlightsByDate("2024-5-01");
    //printFlights(searchResultsByDate);

    return 0;
}