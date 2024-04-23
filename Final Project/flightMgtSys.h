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
#include <fstream>
#include <cstdlib>
using namespace std;
using namespace chrono;

// Booking Management
vector<Booking> searchBookingsByStatus(const vector<Booking>& bookings, const string& status);
vector<Booking> searchBookingsByDate(const vector<Booking>& bookings, const string& date, bool searchBefore);
vector<Booking> searchBookingsByBookingID(const vector<Booking>& bookings, string& bookingID);
vector<Booking> searchBookingsByBookingDate(const vector<Booking>& bookings, string& date);
vector<Booking> searchBookingsByFlightDate(const vector<Booking>& bookings, const string& date, bool searchBefore);
vector<Booking> searchBookingsByFlightNumber(const vector<Booking>& bookings, string& flightNumber);
vector<Booking> searchBookingsByUser(const std::vector<Booking>& bookings, string& userId);
void sortBookingsByCriteria(vector<Booking>& bookingList, const string& criterion, bool ascending);
bool adminCancelBooking(const string bookingID);
bool keepCancellationRequest(const string bookingID);
bool requestBookingCancellation(const string bookingID);
Booking* findBookingByID(const string& bookingID);
bool bookFlight(const string& userID, const string& flightNumber, const string& ticketType, const string& bookingDate, const map<string, Passenger>& seatToPassengerMap, const string& bookingID = "");
Booking* getCancelledBooking();
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
util::TwoDArrayADT<string> getFlightManifest(const string& flightNumber);

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
string toUpper(string str);
string toLower(string str);
bool writeCSVToFile(const string& fileName, string& csvData, string& filepath);
string formatCSVContent(const string& content);
bool openExcel(const string& filePath);
int days_between_dates(const string& date1, const string& date2);

// Read and write data to files
void exportUsersToCSV(const string& filename);
void importUsersFromCSV(const string& filename);
void exportFlightsToCSV(const string& filename);
void importFlightsFromCSV(const string& filename);
void exportBookingsToCSV(const string& bookingsFilename, const string& ticketsFilename);
void importBookingsFromCSV(const string& bookingsFilename, const string& ticketsFilename);
