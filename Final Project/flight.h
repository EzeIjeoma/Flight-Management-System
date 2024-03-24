#pragma once

#include <string>
#include <map>
#include "seatInfo.h"

using namespace std;

class Flight
{
private:
	string flightNumber;
	string airlineName;
	string origin;
	string destination;
	string departureTime;
	string arrivalTime;
	map<string, SeatInfo> seats;
	void initializeSeats(int totalRows, int seatsPerRow, int businessRows);

public:
	Flight(const string& flightNumber, const string& airlineName, const string& origin,
		const string& destination, const string& departureTime, const string& arrivalTime,
		int totalRows, int seatsPerRow, int businessRows);
	string getFlightNumber() const;
	string getAirlineName() const;
	string getOrigin() const;
	string getDestination() const;
	string getDepartureTime() const;
	string getArrivalTime() const;
	string getSeatClass(const string& seatNumber) const;
	double getSeatPrice(const string& seatNumber) const;
	bool bookSeat(const string& seatNumber);
	const map<string, SeatInfo>* getSeats() const;

};

