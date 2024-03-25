#pragma once

#include <string>
#include <map>
#include "seatInfo.h"
#include "util.h"
#include "passenger.h"
#include "booking.h"
#include "ticket.h"

using namespace std;

class Flight
{
private:
	string flightNumber;
	string airlineName;
	string dateOfFlight; //yyyy-mm-dd
	string origin;
	string destination;
	string departureTime;
	string arrivalTime;
	double flightDuration;
	double businessPrice;
	double regularPrice;
	map<string, SeatInfo> seats;
	util::TwoDArrayADT<string> manifest;
	void initializeSeats(int totalRows, int seatsPerRow, int businessRows, double businessPrice, double regularPrice);

public:
	Flight(const string& flightNumber, const string& airlineName, const string& dateOfFlight, const string& origin,
		const string& destination, const string& departureTime, const string& arrivalTime,
		int totalRows, int seatsPerRow, int businessRows, double businessPrice, double regularPrice, double flightDuration);
	string getFlightNumber() const;
	string getAirlineName() const;
	string getDateOfFlight() const;
	string getOrigin() const;
	string getDestination() const;
	string getDepartureTime() const;
	string getArrivalTime() const;
	string getSeatClass(const string& seatNumber) const;
	double getSeatPrice(const string& seatNumber) const;
	double getFlightDuration() const;
	double getBusinessPrice() const;
	double getRegularPrice() const;
	bool bookSeat(const string& seatNumber);
	const map<string, SeatInfo>* getSeats() const;
	const util::TwoDArrayADT<string>& getManifest() const;
	void updateManifest(const std::string& targetFlightNumber, const std::vector<Booking>& bookings);
};

