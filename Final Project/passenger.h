#pragma once


#include <string>
#include <vector>
using namespace std;


class Passenger
{
private:
	string passengerID;
	string name;
	int age;
	string passportNumber;

public:
	Passenger(const string& passengerID, const string& name, const int& age, const string& passportNumber);

	string get_passengerID();
	string get_name();
	int get_age();
	string get_passportNumber();
};

