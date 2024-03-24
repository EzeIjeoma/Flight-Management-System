#pragma once

#include <string>
#include <vector>
using namespace std;


class Passenger
{
private:
	string name;
	string passportNumber;
	string passportIssueCountry;

public:
	Passenger();
	Passenger(const string& name, const string& passportNumber, const string& passportIssueCountry);
	string get_name() const;
	string get_passportNumber() const;
	string get_passportIssueCountry() const;
};

