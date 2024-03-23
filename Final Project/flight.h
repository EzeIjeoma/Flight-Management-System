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

public:
	string getFlightNumber() const;
	string getAirlineName() const;
	string getOrigin() const;
	string getDestination() const;
	string getDepartureTime() const;
	string getArrivalTime() const;
	double getPrice() const;
	map<string, bool> getSeats() const;

	void setPrice(double p);

};

