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


// Flight Management
Flight* findFlightByID(const string& flightNumber);
bool bookFlight(const string& userID, const string& flightNumber, const string& ticketType, const string& bookingDate, const map<string, Passenger>& seatToPassengerMap);
void addFlight(const string& flightNumber, const string& airlineName, const string& dateOfFlight, const string& origin,
    const string& destination, const string& departureTime, const string& arrivalTime,
    int totalRows, int seatsPerRow, int businessRows, double businessPrice, double regularPrice, double flightDuration);
void displayFlightDetails(const string& flightNumber);
vector<Flight> sortFlightsByCriteria(const string& criterion, bool ascending = true);
vector<Flight> searchFlightsByOriginAndDestination(const string& origin, const string& destination);
vector<Flight> searchFlightsByDate(const string& date);


// User management
bool registerUser(const string& userId, const string& firstName, const string& lastName, const string& email, const string& password, const string& userType);
bool loginUser(const string& email, const string& password);
void logoutUser();
User* getCurrentSessionUser();


// Helper functions
User* findUserByEmail(const string& email);