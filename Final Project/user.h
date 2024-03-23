#pragma once

#include <string>
#include <vector>
#include "booking.h"
using namespace std;

class User
{
private:
	string first_name;
	string last_name;
	string password;
	string email;
	string user_type;
	vector<Booking> bookings;


public:
	User(const string& first_name, const string& last_name, const string& password, const string& email, const string& user_type);

	string get_first_name();
	string get_last_name();
	string get_password();
	string get_email();
	string get_user_type();

	void set_password(string password);
	void set_email(string email);

	bool login(string username, string password);
	bool logout();
};