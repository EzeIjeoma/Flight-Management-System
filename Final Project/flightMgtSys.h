#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "user.h"
#include "flightAdmin.h"
#include "flight.h"
#include "passenger.h"
#include <sstream>
#include <ctime>
#include <chrono>
#include <iomanip>
using namespace std;

// Booking Management
vector<Booking> searchBookingsByStatus(const std::vector<Booking>& bookings, const std::string& status);
vector<Booking> searchBookingsByDate(const std::vector<Booking>& bookings, const std::string& date, bool searchBefore);
vector<Booking> searchBookingsByFlightDate(const vector<Booking>& bookings, const string& date, bool searchBefore);
vector<Booking> searchBookingsByUser(const std::vector<Booking>& bookings, const std::string& userId);
void sortBookingsByCriteria(vector<Booking>& bookingList, const string& criterion, bool ascending);
Booking* findBookingByID(const string& bookingID);
bool bookFlight(const string& userID, const string& flightNumber, const string& ticketType, const string& bookingDate, const map<string, Passenger>& seatToPassengerMap);
Booking* getRecentBooking();
vector<Booking>& getBookings();

// Flight Management
Flight* findFlightByID(const string& flightNumber);
void addFlight(const string& flightNumber, const string& airlineName, const string& dateOfFlight, const string& origin,
    const string& destination, const string& departureTime, const string& arrivalTime,
    int totalRows, int seatsPerRow, int businessRows, double businessPrice, double regularPrice, double flightDuration);
void displayFlightDetails(const string& flightNumber);
void sortFlightsByCriteria(vector<Flight>& flightList, const string& criterion, bool ascending = true);
vector<Flight> searchFlightsByOriginAndDestination(const vector<Flight>& flightList, const string& origin, const string& destination);
vector<Flight> searchFlightsByDate(const vector<Flight>& flightList, const string& date);
vector<Flight> getFlights();

// User management
bool registerUser(const string& userId, const string& firstName, const string& lastName, const string& email, const string& password, const string& userType);
bool loginUser(const string& email, const string& password);
void logoutUser();
User* getCurrentSessionUser();
bool createAdmin(const string& userId, const string& firstName, const string& lastName, const string& email, const string& password, const string& adminRole);
User* findUserByEmail(const string& email);
string getUserId();

// Helper functions
string currentDate();
string getCurrentDate();